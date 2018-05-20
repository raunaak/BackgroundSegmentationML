#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include "GMMGaussian.h"
#include "GlobalVariables.h"
#include "BackgroundSubtractionImage.h"

using namespace std;
using namespace cv;

/*int main() {
	Mat image;
	image = imread("mem.jpg", CV_LOAD_IMAGE_GRAYSCALE);   // Read the file

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.
	waitKey(0);
	BackgroundSubtractionImage(image);

	imshow("Display window", image);
	waitKey(0);
	return 0;
}*/

Mat frame;

Mat gray;

vector<vector<vector<GMMGaussian> > > images(row, vector<vector<GMMGaussian> >(col, vector <GMMGaussian>(gaussiansPerPixel)));

int main(int argc, char* argv[])
{
	int i = 0;
	int fourcc = -1;
	VideoCapture cap("umcp.mpg"); // open the video file for reading
	//CV_FOURCC('D', 'I', 'V', 'X') //CV_FOURCC('P', 'I', 'M', '1')
	VideoWriter output;
	const String str = "Raunak_Lohiya.mkv";
	int fcc = CV_FOURCC('D', 'I', 'V', '3');
	int fps = 25;
	cv::Size frameSize(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	output.open(str, fcc, fps, frameSize, false);

	const string NAME = "E:/sem6/machine learning/assignments/assn1/output1.mpg";   // Form the new name with container
	//int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

	//Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
	//VideoWriter output(NAME, cap.get(CV_CAP_PROP_FOURCC), cap.get(CV_CAP_PROP_FPS), frameSize, true);

	//output.open(NAME, ex, cap.get(CV_CAP_PROP_FPS), S, true);
	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}
	if (!output.isOpened()) //if not initialize the VideoWriter successfully, exit the program
	{
		cout << "ERROR: Failed to write the video" << endl;
		return -1;
	}
	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
	
	while (1)
	{
		
		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		cvtColor(frame, gray, CV_BGR2GRAY);

		BackgroundSubtractionImage(gray, images);

		imshow("MyVideo", gray); //show the frame in "MyVideo" window

		output.write(gray);

		//imshow("MyVideo", frame);
		//output.write(frame);

		if (waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}

	}

	return 0;

}