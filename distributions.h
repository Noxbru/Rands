#ifndef DISTRIBUTIONS
#define DISTRIBUTIONS

#include "rands.h"

#include <stdlib.h>
#include <math.h>
#include <limits.h>

void box_muller(double *a, double *b);
void polar_method(double *a, double *b);
unsigned int poisson(double mean);
double chi2(unsigned int n);

#endif
