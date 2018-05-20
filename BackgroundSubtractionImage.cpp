#include "BackgroundSubtractionImage.h"

void BackgroundSubtractionImage(Mat frame, vector<vector<vector<GMMGaussian> > >& images) {
	for (int i = 0; i < frame.rows; i++) { 
		for (int j = 0; j < frame.cols; j++) { 
			//int currFrame = frame.at<uchar>(i, j);
			frame.at<uchar>(i, j) = (uchar)BackgroundSubtractionPixel(frame.at<uchar>(i, j), images[i][j]);
			//if (frame.at<uchar>(i, j) == BLACK) { frame.at<uchar>(i, j) = currFrame; }
			//else frame.at<uchar>(i, j) = BLACK;
		} 
	}			
	//connectedComponents(frame);
}

int BackgroundSubtractionPixel(int pixel, vector<GMMGaussian>& image) {
	bool b = false;
	for (int k = 0; k < gaussiansPerPixel; k++) {
		double avg = 0;
		image[k].significant++;
		image[k].hist.push_back(pixel);
		if (image[k].significant == history + 1) { image[k].significant = history; image[k].hist.erase(image[k].hist.begin()); }
		for (int i = 0; i < image[k].significant; i++)avg = avg + image[k].hist[i];
		avg = avg / image[k].significant;
		image[k].avg = avg;
		if (image[k].variance == 0) {
			image[k].mu = pixel;
			image[k].variance = initialVariance;
			updateWeights( k, image);
			b = true;
			break;
		}
		else if( (abs(avg - image[k].mu)) <= 2.5*sqrt(image[k].variance)) {
			double beta = learningRate * alpha(avg, image[k]);
			image[k].mu = (1 - beta)*image[k].mu + beta*avg;
			image[k].variance = max(25.0,(1 - beta)*image[k].variance + beta*(avg - image[k].mu)*(avg - image[k].mu));
			updateWeights( k, image);
			b = true;
			break;
		}
	}
	
	if (b == false) {
		int k = getMinWeightGaussian(image);
		image[k].mu = image[k].avg;
		//image[k].variance = initialVariance;
		updateWeights(k, image);
	}

	double sorted[gaussiansPerPixel][2];
	for (int i = 0; i < gaussiansPerPixel; i++) {
		if (image[i].variance != 0) {
			sorted[i][0] = image[i].weight / sqrt(image[i].variance);
			sorted[i][1] = image[i].weight;
		}
		else {
			sorted[i][0] = 0;
			sorted[i][1] = 0;
		}
		for (int j = i - 1; j >= 0; j--) {
			if (sorted[j][0] >= sorted[j + 1][0])break;
			else {
				double temp1 = sorted[j][0]; sorted[j][0] = sorted[j + 1][0]; sorted[j + 1][0] = temp1;
				double temp2 = sorted[j][1]; sorted[j][1] = sorted[j + 1][1]; sorted[j + 1][1] = temp2;
			}
		}
	}

	double sum = 0;
	for (int i = 0; i < backgroundGaussiansPerPixel; i++)sum += sorted[i][1];
	if (sum >= THRESHOLD) {
		return BLACK;
	}
	else {
		return WHITE;
	}
}

void updateWeights( int k, vector<GMMGaussian>& image) {
	for (int i = 0; i < gaussiansPerPixel; i++) {
			if (i == k) {
				image[i].weight = (1 - learningRate)*image[i].weight + learningRate;
			}
			else {
				image[i].weight = (1 - learningRate)*image[i].weight;
			}
	}
}

double alpha(int pixel, GMMGaussian& image) {
	double pow = -abs((pixel - image.mu)*(pixel - image.mu) / (2 * image.variance));
	return 1.0 / (sqrt(2 * PI * image.variance)) * exp(pow);
}

int getMinWeightGaussian(vector<GMMGaussian>& image) {
	float weight = 1000000000;
	int index = 0;
	for (int i = 0; i < gaussiansPerPixel; i++) {
		if (image[i].weight < weight) {
			weight = image[i].weight/image[i].variance;
			index = i;
		}
	}
	return index;
}

void connectedComponents(Mat frame) {
	for (int i = 2 * components; i < row - 2 * components; i++) {
		for (int j = 2 * components; j < col - 2 * components; j++) {
			int count = 0;
			for (int k = i - components / 2; k <= i + components / 2; k++) {
				for (int m = j - components / 2; m <= j + components / 2; m++) {
					count += frame.at<uchar>(k, m) / 255;
				}
			}
			if (count >= componentThreshold)frame.at<uchar>(i, j) = 255; else frame.at<uchar>(i, j) = 0;
		}
	}
}