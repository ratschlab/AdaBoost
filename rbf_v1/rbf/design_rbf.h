#ifndef __design_rbf_h
#define __design_rbf_h

#include "mex.h"
#include <math.h>
#include <assert.h>
#include <stdio.h>

#ifndef MATLAB4
#define mexFuncConst const
#else
#define mxArray Matrix 
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif

void mexFunction(
    int		nlhs,		/* number of expected outputs */
    mxArray	*plhs[],	/* matrix pointer array returning outputs */
    int		nrhs,		/* number of inputs */
    mexFuncConst mxArray *prhs[]	/* matrix pointer array for inputs */
) ;

void design_rbf(double * X, double * C, double *H, double *Inp, double *sigma,
	     unsigned int n1, unsigned int n2, unsigned int m) ;

#define sqr(x) ((x)*(x))

#endif // __design_rbf_h

