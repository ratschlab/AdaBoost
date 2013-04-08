/*
 * Author: Sebastian Mika, GMD First
 * $Id: symeigx.c,v 1.1 1999/09/08 05:30:01 raetsch_cvs Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include "symeigx.h"

void symeigx(double a[],    
	      int n,         
	      double d[],    
	      double v[],    
	      int    ell,
	      int    *fl)
{
  int    itype    =   1;
  char   jobz     = 'v';
  char   range    = 'i';
  char   uplo     = 'l';
  char   trans    = 't';
  char   side     = 'l';
  char   diag     = 'n';
  char   under    = 'u';
  int    nfound;
  int    *ifail;
  int    info;
  int    neig;
  double abstol   =  2.0 * DLAMCH(under);
  double one      =  1.0;
  double zero     =  0.0;

#ifdef CBLAS
  double *work;
  int    lwork;
  int    *iwork;            
  char   *dsytrd  = "DSYTRD";
  int    monei    = -1;
  /*  int    nell     = n-ell+1;
      int    n1       = n;*/
  int    nell     = 1;
  int    n1       = ell ;
#else
  /*int    nell     = n-ell;
    int    n1       = n-1;*/
  int    nell     = 0;
  int    n1       = ell-1;
#endif
  
  ifail = (int *) malloc(sizeof(int) * n);

#ifdef CBLAS
  lwork = ilaenv_(&itype, dsytrd, &uplo, &n, 
		  &monei, &monei, &monei, 6L, 1L);
  lwork = (lwork+3)*n;
  if (lwork < 8*n)
    lwork = 8*n;
  iwork = (int *) malloc(sizeof(int) * n * 5);
  work  = (double *) malloc(sizeof(double) * lwork);
  dsyevx_(&jobz,&range,&uplo,&n,a,&n,&zero,&zero,&nell,&n1,
	  &abstol,&nfound,d,v,&n,work,&lwork,iwork,ifail,&info);
  free(iwork);
  free(work);
#else
  dsyevx(jobz, range, uplo, n, a, n, zero, zero, nell, n1, abstol, &nfound,
	 d, v, n, ifail, &info);
#endif
  
  neig = ell;
  if (info > 0)
    neig = info - 1;
  
  free(ifail);
  printf("%i\n", nfound) ;
  *fl = 1;
  if (info < 0) 
    {
      fprintf(stderr, "sygvx: Illegal argument %i.\n", info);
      *fl = -1;
    }
  else if ((info > 0) && (info <= n))
    {
      fprintf(stderr, "sygvx: Convergence failure.\n");
      *fl = -1;
    }
  else if (info > n)
    {
      fprintf(stderr,
	      "sygvx: Leading minor of order %i of B not pos. def.\n", 
	      info-n);
      *fl = -1;
    }
  
  return;
}





