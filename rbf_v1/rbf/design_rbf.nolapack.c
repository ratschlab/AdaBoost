#include <math.h>
#include "design_rbf.h"
/*#include <ieeefp.h>*/

#ifdef MULTI_CPU
#define NUM_CPUS 2
#else
#define NUM_CPUS 1
#endif

#ifndef NULL
#define NULL (void *)0 
#endif

#define ZERO_THRESH 100

#if NUM_CPUS!=1
#include <pthread.h>
#include <thread.h>
#endif

struct thread_data
{
	double *X, *C, *H, *Inp, *sigma ;
	unsigned int n1, n2, m ; 
        unsigned int js, je ; /* defines the matrix stripe */
} ;

void *rbf_thread_func(void * P) 
{
	struct thread_data *TD=(struct thread_data*) P ;
	double *X=TD->X, 
               *C=TD->C, 
               *H=TD->H, 
               *Inp=TD->Inp, 
	       *sigma=TD->sigma ;
	unsigned int n1=TD->n1, 
                     n2=TD->n2, 
		     m=TD->m,
		     js=TD->js,
		     je=TD->je,
		     j,i,k ;

	if (Inp)
	  for (j=js; j<je; j++)
	  {
	    double sqr_sigma_j=sqr(sigma[j]) ;
	    double f1 ;
	    for (i=0; i<n1; i++)
	    {
	      double sum=0 ;
	      unsigned int mi=m*i, mj=m*j ;
	      for (k=0; k<m; k++) 
	      {
		register double q = X[mi + k] - C[mj + k] ; 
		sum = sum + q*q ;
	      } ;
	      sum /= sqr_sigma_j ;
	      f1=sum;
	      if ((sum>ZERO_THRESH) || (sqr_sigma_j==0))
		H[j*n1 + i] = 0 ;
	      else
		H[j*n1 + i] = exp( - sum ) ;
	      Inp[j*n1 + i] = sum ;
	      /* fprintf(stderr, "%f:%i  ", f1, fpclass(sum)==FP_PINF) ; */
	    } ;
	  } 
	else
	  for (j=js; j<je; j++)
          {
	    double sqr_sigma_j=sqr(sigma[j]) ;
	    for (i=0; i<n1; i++)
	    {
	      double sum=0 ;
	      unsigned int mi=i*m, mj=j*m;
	      for (k=0; k<m; k++) 
	      {
		register double q = X[mi + k] - C[mj + k] ;
		sum = sum + q*q ;
	      } ;
	      sum/=sqr_sigma_j ;
	      if (sum>ZERO_THRESH)
		H[j*n1 + i] = 0 ;
	      else
		H[j*n1 + i] = exp( - sum ) ;
	    } ;
	  } ;
	return NULL ;
} 


void design_rbf(double * X, double * C, double *H, double *Inp, double *sigma,
	     unsigned int n1, unsigned int n2, unsigned int m)
{
  unsigned int i,j,k, n2_nc = n2/NUM_CPUS ;
  struct thread_data TD[NUM_CPUS] ;
#if NUM_CPUS!=1
  pthread_t tid[NUM_CPUS] ;
  void *status ;
#endif
  
  /* prepare the structure */
  TD[0].X=X ; TD[0].C=C ; TD[0].H=H ; TD[0].Inp=Inp ; 
  TD[0].sigma = sigma;
  TD[0].n1=n1 ; TD[0].n2=n2 ; TD[0].m=m ;

#if NUM_CPUS!=1
  /* create the threads */
  for (k=0; k<NUM_CPUS; k++)
  {
    TD[k]=TD[0] ;
    TD[k].js=k*n2_nc ;
    if (k+1==NUM_CPUS)
	TD[k].je=n2 ;
    else
	TD[k].je=(k+1)*n2_nc ;

    thr_create(NULL, 0, rbf_thread_func, (void*)&TD[k], PTHREAD_SCOPE_SYSTEM, &tid[k]) ;
  } ;
  
  /* wait for finishing all threads */
  for (k=0; k<NUM_CPUS; k++)
	pthread_join(tid[k], &status) ;
#else
  /* simply call the ,,thread''-function */
  TD[0].js=0 ; TD[0].je=n2 ;
  rbf_thread_func((void *)&TD[0]) ;
#endif
}


