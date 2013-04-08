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
 * $Revision: 1.1 $  $Date: 1999/10/13 07:13:34 $
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
/*#include <floatingpoint.h>*/

#ifndef MATLAB4
#define mexFuncConst const
#define Matrix mxArray
#else
#define mexFuncConst 
#define mxCreateDoubleMatrix mxCreateFull
#define mxREAL 0
#endif

#define KILL_THRESH 1e-10 

/*****************************************************************
  the weighted least squares solver (sample weights)
 *****************************************************************/

void ls_solve_w(double a[], int m, int n, int k, double b[], 
		double eta[], double lambda, double x[], double f[])
{
  double *z=calloc(n*n, sizeof(double)) ;
  double *y=calloc(n*k, sizeof(double)) ;
  double Norm_m=0 ;
  register unsigned int j ;
  register unsigned int i ;
  double problem_fixed=0.0 ;
  double suc, g, lambda_sum ;

  double sum=0 ;
  for (i=0; i<m; i++)
    sum+=eta[i] ;

  for (i=0; i<k; i++)
    matr_mult_At_b_w(a, m, n, 1, eta, &b[i*m], &y[i*n]) ;
  ht_h_lambda_w(a, 0, z, eta, n, m) ;

  /* check matrix  ... */
  lambda_sum=lambda*sum ;
  for (i=0; i<n; i++)
    Norm_m+=z[i*(n+1)]  ;
  Norm_m/=n ;
  /* printf("Mean: %1.2f", Norm_m) ;*/
  for (i=0; i<n; i++)
  {
    double Elem=z[i*(n+1)] ;
    /*printf("%1.2e, ", sqrt(Elem)/Norm_m) ; */
    /* ... and work around this problem */
    if (Elem/Norm_m < KILL_THRESH)
    {
      z[i*(n+1)]=1 ;
      problem_fixed=1.0 ;
      /*printf("ls_solve_w: warning: killing column %i of A (%1.2e)\n", i, sqrt(Elem)/Norm_m) ; */
    }
    else
      if (i>0) /* assuming b in as the first variable in w */
	z[i*(n+1)]=Elem+lambda_sum ; /* so we don't want to regularize */
  } ;

  linsys_solve(z, n, k, y, x, 0, &suc) ;
  g=lambda*sum + 1e-20 ;
  *f=0.0 ;
  while (suc>0)
  {
    for (i=1; i<n; i++) /* assuming b as the first variable in w */
      z[i*(n+1)]+=+g ;
    *f+=g ;
    linsys_solve(z, n, k, y, x, 0, &suc) ;
    g*=2 ;
    /* printf("g=%1.2e,  f=%1.2e/n", g, *f) ;*/
  } ;
  if (*f!=0.0) 
    *f+=*f/sum+lambda ;
  else
    *f=-1.0*problem_fixed ;
  /*printf("%1.2e\n", *f) ;*/
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
  double *a, *b, *x, lambda, *eta, *f ;
  unsigned int m, n, k; 
 
  if ((nrhs!=4) || (nlhs!=2))
  {
    mexErrMsgTxt("[x,f]=ls_solve_w(A, b, eta, lambda)") ;
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
  plhs[1]=(mxArray*)mxCreateDoubleMatrix(1, 1, mxREAL) ; 
  f = mxGetPr(plhs[1]);
  *f=0 ;

  /*fprintf(stderr, "%i", ieee_handler("set", "all", SIGFPE_DEFAULT)) ;*/
  /*ieee_handler("set", "inexact", SIGFPE_DEFAULT);*/
  /*ieee_handler("clear", "all", SIGFPE_ABORT);*/
  /*(void) ieee_handler("set", "inexact", SIGFPE_IGNORE);*/

  ls_solve_w(a, m, n, k, b, eta, lambda, x, f) ;
} 

#endif



