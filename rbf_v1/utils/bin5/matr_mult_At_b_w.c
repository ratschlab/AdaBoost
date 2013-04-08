/*
 * File:        matr_mult_At_b_w.c
 * Purpose:     performs a weighted matrix multiplication
 *
 * Author:      Gunnar Raetsch
 * Created:     1/2/98
 * Updated:     
 *
 * 
 * Copyright (c) 1997  GMD Berlin - All rights reserved
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
 * The copyright notice above does not evidence any
 * actual or intended publication of this work.
 *
 * $Revision: 1.1 $  $Date: 1999/09/08 05:30:25 $
 */

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "mex.h"
#include <assert.h>
#include "matrix.h"
#include "matr_mult_At_b_w.h"
/*#include "floatingpoint.h"*/

#ifndef MATLAB4
#define mexFuncConst const
#define Matrix mxArray
#else
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif


/*********************************************************************
 * matrix vector multiplication
 *   y=A'*(gamma.*b)         A \in \R^{m x n}  b,gamma \in \R^{m x 1} 
 *********************************************************************/ 

void matr_mult_At_b_w(double a[], int m, int n, int k, double gamma[], 
		      double b[], double y[])
{
  register unsigned int i, j, l;
  /*  (void) ieee_handler("set", "inexact", SIGFPE_IGNORE);*/
  for (l=0; l<k; l++)
    for (i=0; i<n; i++)
    {
      register double sum=0.0 ;
      for (j=0; j<m; j++)
	sum+=a[j+i*m]*b[j+l*m]*gamma[j+l*m] ;
      y[i+l*n]=sum ;
    } ;
} 

#ifndef MATR_MULT_AT_B_NOMEX
void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *a, *b, *y, *gamma ;
  unsigned int m, n, k; 

  if ((nrhs!=3) || (nlhs!=1))
  {
    mexErrMsgTxt("y=matr_mult_At_b_w(A, gamma, b)") ;
    return ;
  } ;

  a=mxGetPr(prhs[0]) ; assert(a!=0) ; 
  gamma=mxGetPr(prhs[1]) ; assert(gamma!=0) ;
  b=mxGetPr(prhs[2]) ; assert(b!=0) ;

  n=mxGetN(prhs[0]) ;
  m=mxGetM(prhs[0]) ;
  k=mxGetN(prhs[1]) ;

  if ((mxGetM(prhs[1])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 2).");
    return ;
  } ;
  if ((mxGetM(prhs[2])!=m) | (mxGetN(prhs[2])!=k))
  {
    mexErrMsgTxt("Dimension error (arg 3).");
    return ;
  } ;

  plhs[0]=(mxArray*)mxCreateDoubleMatrix(n, k, mxREAL) ; 
  y = mxGetPr(plhs[0]);
    
  matr_mult_At_b_w(a, m, n, k, gamma, b, y) ;
} 

#endif
