#include <math.h>
#include "sqdist.h"

#ifdef MULTI_CPU
#define NUM_CPUS 2
#else
#define NUM_CPUS 1
#endif

#ifndef NULL
#define NULL (void *)0 
#endif

#define PAR_THRESH  10

#if NUM_CPUS!=1
#include <pthread.h>
#include <thread.h>
#endif

struct thread_data
{
	double * x, *y, *z ;
	unsigned int n1, n2, m ; 
        unsigned int js, je ; /* defines the matrix stripe */
} ;

void *sqdist_thread_func(void * P) 
{
	struct thread_data *TD=(struct thread_data*) P ;
	double *x=TD->x, 
               *y=TD->y, 
               *z=TD->z ;
	unsigned int n1=TD->n1, 
                     n2=TD->n2, 
		     m=TD->m,
		     js=TD->js,
		     je=TD->je,
		     j,i,k ;

   	for (j=js; j<je; j++)
    		for (i=0; i<n1; i++)
    		{
      			double sum=0 ;
      			for (k=0; k<m; k++) 
				sum = sum + sqr(x[i*m + k] - y[m*j + k]);
      			z[j*n1 + i] = sum ;
    		} ;
	return NULL ;
} 


void sqdist(double * x, double * y, double *z,
	     unsigned int n1, unsigned int n2, unsigned int m)
{
  unsigned int i,j,k, n2_nc = n2/NUM_CPUS ;
  struct thread_data TD[NUM_CPUS] ;
#if NUM_CPUS!=1
  pthread_t tid[NUM_CPUS] ;
  void *status ;
#endif
  
  /* prepare the structure */
  TD[0].x=x ; TD[0].y=y ; TD[0].z=z ; 
  TD[0].n1=n1 ; TD[0].n2=n2 ; TD[0].m=m ;

#if NUM_CPUS!=1
  if (n2>PAR_THRESH)
  {
    /* create the threads */
    for (k=0; k<NUM_CPUS; k++)
    {
      TD[k]=TD[0] ;
      TD[k].js=k*n2_nc ;
      if (k+1==NUM_CPUS)
	  TD[k].je=n2 ;
      else
	  TD[k].je=(k+1)*n2_nc ;

      thr_create(NULL, 0, sqdist_thread_func, (void*)&TD[k], PTHREAD_SCOPE_SYSTEM, &tid[k]) ;
    } ;
  
    /* wait for finishing all threads */
    for (k=0; k<NUM_CPUS; k++)
      pthread_join(tid[k], &status) ;

  } else
  {
    /* simply call the ,,thread''-function */
    TD[0].js=0 ; TD[0].je=n2 ;
    sqdist_thread_func((void *)&TD[0]) ;
  } ;
  
#else
  /* simply call the ,,thread''-function */
  TD[0].js=0 ; TD[0].je=n2 ;
  sqdist_thread_func((void *)&TD[0]) ;
#endif
}

