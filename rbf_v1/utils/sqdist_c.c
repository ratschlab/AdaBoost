/*
 * File:        sqdist_c.c
 * Purpose:     matlab interface 
 *
 * Author:      Alex J. Smola, Gunnar R"atsch
 * Created:     10/16/97
 * Updated:     10/27/97
 *
 * z = sqdist(x, y)
 * fast ordering is assumed (each column is a vector)
 * (this is FORTRAN, hence we have _row_ ordering as we use C)
 * 
 * Copyright (c) 1997  GMD Berlin - All rights reserved
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
 * The copyright notice above does not evidence any
 * actual or intended publication of this work.
 *
 * modified code from Mathworks and Rob Vanderbei
 *
 * compile with
 Matlab 4 LINUX
  cc -O4 -c sqdist_.c -o sqdist.lx.o
  cmex4 -DMATLAB4 sqdist_c.c sqdist.lx.o -o sqdist_c4
 Matlab 5 LINUX
  cc -O4 -c sqdist_.c -o sqdist.lx.o
  cmex5 sqdist_c.c sqdist.lx.o -output sqdist_c5
 Matlab 4 SUN
  cc -c -fast -DMULTI_CPU -xO5 -xautopar -xtarget=ultra1/2200 -xloopinfo -lpthread -lthread sqdist_.c -o sqdist.sun.o
  cmex4 -L/home/solaris/opt/SUNWspro/SC4.0/lib -lmtsk -lpthread -lthread -DMATLAB4 sqdist_c.c sqdist.sun.o -o sqdist_c4
 Matlab 5 SUN
  cc -c -fast -DMULTI_CPU -xO5 -xautopar -xtarget=ultra1/2200 -xloopinfo -lpthread -lthread sqdist_.c -o sqdist.sun.o
  cmex5 -L/home/solaris/opt/SUNWspro/SC4.0/lib -lmtsk sqdist_c.c sqdist.sun.o -output sqdist_c5 
 Matlab 4 SGI
  cc -c -O2 sqdist_.c -o sqdist.sgi.o
  cmex4 -DMATLAB4 sqdist_c.c sqdist.sgi.o -o sqdist_c4
 Matlab 5 SUN
  cc -c -O2 sqdist_.c -o sqdist.sgi.o
  cmex5 sqdist_c.c sqdist.sgi.o -output sqdist_c5 
 *
 */

#include "mex.h"
#include <math.h>
#include <stdio.h>
#include "sqdist.h"

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
)
{
    double *x=NULL, *y=NULL, *z=NULL;
    double sigma = 1;
    unsigned int n1=0, n2=0, m=0;
    mxArray *zM ;

    if ((nrhs > 2) || (nrhs < 2)) {
      mexErrMsgTxt("Usage: z = sqdist(x, y)");
      return;
    }
    /* sanity checks for right hand side and variable initialization */
    switch (nrhs) {
    case 2:
      if (mxGetM(prhs[1]) != 0 || mxGetN(prhs[1]) != 0) {
	if (!mxIsNumeric(prhs[1]) 
	    || mxIsComplex(prhs[1]) 
	    || !mxIsDouble(prhs[1]) 
	    || mxIsSparse(prhs[1]) ) {
	  mexErrMsgTxt("Second argument (y) must be "
		       "a matrix.");
	  return;
	}
	if (m != 0 && m != mxGetM(prhs[1])) {
	  mexErrMsgTxt("Dimension error (arg 2 and later).");
	  return;
	}
	m = mxGetM(prhs[1]);
	n2 = mxGetN(prhs[1]);

	y = mxGetPr(prhs[1]);
      }
    case 1:
      if (mxGetM(prhs[0]) != 0 || mxGetN(prhs[0]) != 0) {
	if (!mxIsNumeric(prhs[0]) 
	    || mxIsComplex(prhs[0]) 
	    || !mxIsDouble(prhs[0]) 
	    || mxIsSparse(prhs[0]) ) {
	  mexErrMsgTxt("First argument (x) must be "
		       "a matrix.");
	  return;
	}
	if (m != 0 && m != mxGetM(prhs[0])) {
	  mexErrMsgTxt("Dimension error (arg 1 and later).");
	  return;
	}
	m = mxGetM(prhs[0]);
	n1 = mxGetN(prhs[0]);

	x = mxGetPr(prhs[0]);
      }
      break;
    }

    if (nlhs != 1) {
      mexErrMsgTxt("Usage: z = sqdist(x, y)");
      return;
    }

    plhs[0]=(mxArray*)mxCreateDoubleMatrix(n1, n2, mxREAL) ; 
    z = mxGetPr(plhs[0]);
    
    sqdist(x, y, z, n1, n2, m);
}





