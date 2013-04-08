/*
 * File:        ls_solve_w.c
 * Purpose:     
 *
 * Author:      Gunnar Raetsch
 * Created:     01/02/98
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

#ifndef MATLAB4
#define mexFuncConst const
#define Matrix mxArray
#else
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif

void ls_solve_w(double a[], int m, int n, int k, double b[], 
		double eta[], double lambda, double x[])
{
  double *z=calloc(n*n, sizeof(double)) ;
  double *y=calloc(n*k, sizeof(double)) ;
  register unsigned int j ;
  register unsigned int i ;

  double sum=0 ;
  for (i=0; i<m; i++)
    sum+=eta[i] ;

  for (i=0; i<k; i++)
	matr_mult_At_b_w(a, m, n, 1, eta, &b[i*m], &y[i*n]) ;
  /*  ht_h_lambda_w(a, lambda*sum, z, eta, n, m) ;*/

  /* linsys_solve(z, n, k, y, x, 0) ;*/

  free(y) ;
  free(z) ;
}

#ifndef LS_SOLVE_NOMEX
void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *a, *b, *x, lambda, *eta ;
  unsigned int m, n, k; 

  if ((nrhs!=4) || (nlhs!=1))
  {
    mexErrMsgTxt("x=ls_solve_w(A, b, eta, lambda)") ;
    return ;
  } ;

  a=mxGetPr(prhs[0]) ; assert(a!=0) ; 
  b=mxGetPr(prhs[1]) ; assert(b!=0) ;
  eta=mxGetPr(prhs[2]) ; assert(etha!=0) ;
  lambda=*mxGetPr(prhs[3]) ; 

  n=mxGetN(prhs[0]) ;
  m=mxGetM(prhs[0]) ;
  k=mxGetN(prhs[1]) ;

  if ((mxGetM(prhs[1])!=m))
  {
    mexErrMsgTxt("Dimension error (arg 2).");
    return ;
  } ;
  if ((mxGetM(prhs[2])!=m) | (mxGetN(prhs[2])!=1))
  {
    mexErrMsgTxt("Dimension error (arg 3).");
    return ;
  } ;
  if ((mxGetM(prhs[3])!=1) | (mxGetN(prhs[3])!=1))
  {
    mexErrMsgTxt("Dimension error (arg 4).");
    return ;
  } ;

  plhs[0]=(mxArray*)mxCreateDoubleMatrix(n, k, mxREAL) ; 
  
  x = mxGetPr(plhs[0]);
  ls_solve_w(a, m, n, k, b, eta, lambda, x) ;
  /*  for (m=0; m<100; m++)
    {
      x = (double*)calloc(10000, sizeof(double)) ;
      { 
	int i ;
	x[0]=1;
	x[1]=0 ;
	for (i=3; i<100; i++) x[i]=x[0]/x[1];
	if (x[0]!=1)
	  ls_solve_w(a, m, n, k, b, eta, lambda, x) ; 
      } ;
      free(x) ;
    } ;
  */
} 

#endif















