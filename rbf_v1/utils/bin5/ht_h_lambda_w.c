#include <math.h>
#include "ht_h_lambda_w.h"
#include <stdio.h>
#ifdef MULTI_CPU
#define NUM_CPUS 2
#else
#define NUM_CPUS 1
#endif

#ifndef NULL
#define NULL (void *)0 
#endif

#define PAR_THRESH  50

#if NUM_CPUS!=1
#include <pthread.h>
#include <thread.h>
#endif

#define CACHE       100000 

struct thread_data
{
	double *x, *z, lambda, *gamma ;
	unsigned int n, m ; 
        unsigned int js, je ; /* defines the matrix stripe */
} ;

void *ht_h_lambda_w_thread_func(void * P) 
{
	struct thread_data *TD=(struct thread_data*) P ;
	double *x=TD->x, 
               *z=TD->z,
	       lambda=TD->lambda, q,
	       *gamma=TD->gamma ;
	unsigned int n=TD->n, 
		     m=TD->m,
		     js=TD->js,
		     i,r,ks;
	register unsigned int ke,
		     je=TD->je ;

	q=(1.0*CACHE-1.0*n*n/NUM_CPUS)/(1.0*m*(n+1.0)) ;
	r=(int)(q*m) ;
	if (r<3) r=5 ;
	/*fprintf(stderr, "q=%f, r=%i", q, r) ; */
	
	for (i=0; i<n; i++)
	{
	     register unsigned int in=i*n, j ;
	     for (j=js; j<je; j++)
	     {
      		z[in + j] = 0.0 ;
    	     } ;
	     if ((i>=js) && (i<je))
	        z[in+i]=lambda ;
	} ;
        for (ks=0; ks<m; ks+=r)
	{
	  if (ks+r>m)
	     ke=m ;
	  else
	     ke=ks+r ;
	  /*printf("\nr=%i,ks=%i,ke=%i,m=%i,n=%i", r, ks, ke, m, n) ; */
	  for (i=0; i<n; i++)
	  {
	     register unsigned int im=i*m, j, in=i*n ;
	     for (j=js; j<je; j++)
	     {
     		register double sum=0 ;
		register unsigned int k, jm=j*m ;
      		for (k=ks; k<ke; k++) 
			sum = sum + x[im+k] * x[jm+k] * gamma[k] ;
      		z[in + j] = z[in + j] + sum ;
    	     } ;
	  } ;
	} ;
	return NULL ;
} 


/***************************************************************
 * performs a memory efficient weighted matrix multiplication
 * A=H'*(Gamma.*H)
 ***************************************************************/

void ht_h_lambda_w(double * x, double lambda, double *z, double *gamma, 
		   unsigned int n, unsigned int m)
{
  unsigned int k, n_nc = n/NUM_CPUS ;
  struct thread_data TD[NUM_CPUS] ;
#if NUM_CPUS!=1
  pthread_t tid[NUM_CPUS] ;
  void *status ;
#endif

  /* prepare the structure */
  TD[0].x=x ; TD[0].lambda=lambda ; TD[0].z=z ; 
  TD[0].gamma=gamma ; TD[0].n=n ; TD[0].m=m ;

#if NUM_CPUS!=1
  if (n>PAR_THRESH)
  {
    /* create the threads */
    for (k=0; k<NUM_CPUS; k++)
    {
      TD[k]=TD[0] ;
      TD[k].js=k*n_nc ;
      if (k+1==NUM_CPUS)
	  TD[k].je=n ;
      else
	  TD[k].je=(k+1)*n_nc ;

      thr_create(NULL, 0, ht_h_lambda_w_thread_func, (void*)&TD[k], PTHREAD_SCOPE_SYSTEM, &tid[k]) ;
    } ;
  
    /* wait for finishing all threads */
    for (k=0; k<NUM_CPUS; k++)
      pthread_join(tid[k], &status) ;

  } else
  {
    /* simply call the ,,thread''-function */
    TD[0].js=0 ; TD[0].je=n ;
    ht_h_lambda_w_thread_func((void *)&TD[0]) ;
  } ;
  
#else
  /* simply call the ,,thread''-function */
  TD[0].js=0 ; TD[0].je=n ;
  ht_h_lambda_w_thread_func((void *)&TD[0]) ;
#endif
} 


