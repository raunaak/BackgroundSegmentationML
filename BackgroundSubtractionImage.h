#ifndef BACKGROUNDSUBTRACIONIMAGE_H
#define BACKGROUNDSUBTRACTIONIMAGE_H

#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <vector>
#include <functional>
#include <algorithm>
#include "GMMGaussian.h"
#include "GlobalVariables.h"

using namespace std;
using namespace cv;
using std::vector;

void BackgroundSubtractionImage(Mat frame, vector<vector<vector<GMMGaussian> > >& images);

int BackgroundSubtractionPixel(int pixel, vector<GMMGaussian>& image);

void updateWeights( int k, vector<GMMGaussian>& images);

int getMinWeightGaussian(vector<GMMGaussian>& image);

double alpha(int pixel, GMMGaussian& image);

void connectedComponents(Mat frame);
#endif