#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H
#include <vector>
#include "GMMGaussian.h"

static const int row = 240; //number of rows in image frame 240

static const int col = 352; //number of columns in image frame 352

static const int gaussiansPerPixel = 4; //number of guassians per pixel

static const double learningRate = 0.6; //affect of current pixel in mu and variance of the current gaussian

static const double initialVariance = 49; //variance is initialized with 49 for all gaussians

static const int BLACK = 0; //constant for black color

static const int WHITE = 255; //constant for white color

static const double PI = 3.14159265; //constant for PI

static const double THRESHOLD = 0.95; //threshold for determining background

static const int components = 5;

static const int componentThreshold = (int)(components*components*0.33);

static const int history = 10; // number of frames necessary

static const int backgroundGaussiansPerPixel = 1; //number of gaussians corresponding to background per pixel
#endif // !GLOBALVARIABLES_H