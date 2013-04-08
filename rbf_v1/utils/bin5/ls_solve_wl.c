/*
 * File:        linsys_solve.c
 * Purpose:     solves linear programming problem
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

#include "ls_solve_w.h"
#include "linsys_solve.h"
#include "matr_mult_At_b_w.h"
#include "ht_h_lambda_w.h"

#ifndef MATLAB4
#define mexFuncConst const
#define Matrix mxArray
#else
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif

/*****************************************************************
  the weighted least squares solver 
 *****************************************************************/

void ls_solve_wl(double a[], int m, int n, int k, double b[], 
		double eta[], double theta[], double lambda,
		double x[])
{
  double *z_j=calloc(n*n, sizeof(double)) ;
  double *y_j=calloc(n, sizeof(double)) ;
  double *gamma_j=calloc(m, sizeof(double)) ;
  register unsigned int j ;

  for (j=0; j<k; j++)
  {
    register unsigned int i ;
    double sum=0 ;
    for (i=0; i<m; i++)
    {
      gamma_j[i]=eta[i]*theta[i+j*k] ;
      sum+=gamma_j[i] ;
    } ;

    matr_mult_At_b_w(a, m, n, 1, gamma_j, &b[j*m], y_j) ;
    ht_h_lambda_w(a, lambda*sum, z_j, gamma_j, n, m) ;
    linsys_solve(z_j, n, 1, y_j, &x[j*n], 0) ;
  } ;

  free(gamma_j) ;
  free(y_j) ;
  free(z_j) ;
}


#ifndef LS_SOLVE_NOMEX
void
mexFunction(
    int nlhs,
    Matrix *plhs[],
    int nrhs,
    mexFuncConst Matrix *prhs[])
{
  double *a, *b, *x, lambda, *eta, *theta ;
  unsigned int m, n, k; 

  if ((nrhs!=5) || (nlhs!=1))
  {
    mexErrMsgTxt("x=ls_solve_wl(A, b, eta, theta, lambda)") ;
    return ;
  } ;

  a=mxGetPr(prhs[0]) ; assert(a!=0) ; 
  b=mxGetPr(prhs[1]) ; assert(b!=0) ;
  eta=mxGetPr(prhs[2]) ; assert(etha!=0) ;
  theta=mxGetPr(prhs[3]) ; assert(theta!=0) ;
  lambda=*mxGetPr(prhs[4]) ; 

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
  if ((mxGetM(prhs[3])!=m) | (mxGetN(prhs[3])!=k))
  {
    mexErrMsgTxt("Dimension error (arg 4).");
    return ;
  } ;
  if ((mxGetM(prhs[4])!=1) | (mxGetN(prhs[4])!=1))
  {
    mexErrMsgTxt("Dimension error (arg 5).");
    return ;
  } ;

  plhs[0]=(mxArray*)mxCreateDoubleMatrix(n, k, mxREAL) ; 
  x = mxGetPr(plhs[0]);
    
  ls_solve_wl(a, m, n, k, b, eta, theta, lambda, x) ;
} 

#endif
