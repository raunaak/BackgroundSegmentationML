#ifndef GMMGAUSSIAN_H
#define GMMGAUSSIAN_H

#include "GlobalVariables.h"
#include <vector>

using namespace std; 

typedef struct GMMGaussian
{
	double variance = 0;
	double mu;
	double weight = 1.0/gaussiansPerPixel;
	vector<int> hist;
	int significant = 0;
	double avg;
}GMM;

#endif // !1