#include <math.h>
#include <stdlib.h>
#include <assert.h>

#include "clustknb_new.h"
#include "../utils/sqdist.h"

#define BIG            1e+30
#define MUSRECALC
#define CHUSI          2000
 
#ifdef WITHMAIN 
 
#define XDim 10 
#define XSize 5000  
#define k 20  
 
void main() 
{ 
    double A[XDim*XSize] ; 
    double C[XDim*k] ; 
    double R[k] ; 
    unsigned int i,q,r ; 
 
    for (i=0; i < XSize*XDim; i++) 
        A[i]=rand() / (RAND_MAX + 1.0) ; 
 
if (0) 
{ 
    printf("A=\n") ; 
    for (q=0; q<XSize; q++) 
    { 
        for (r=0; r<XDim; r++) 
            printf("%f,", A[q*XDim+r]) ; 
        printf("\n") ; 
    } 
} ; 
    clustknb_new(A, k, 0, NULL, C, R, XSize, XDim) ; 
 
}  
 
#undef XDim 
#undef XSize 
#undef k 
#endif 
 

void clustknb_new(double *XData, unsigned int k, 
                  double *mus, double *R, unsigned int XSize, 
                  unsigned int XDim, unsigned int disp) 
{
    unsigned int i, changed=1 ;
    const unsigned int XDimk=XDim*k ;
    unsigned long Iter=0 ;

    unsigned int *ClList = (unsigned int*) calloc(XSize, sizeof(unsigned int)) ;
    unsigned int *SetCounts = (unsigned int*) calloc(k, sizeof(unsigned int)) ;
    double *dists = (double*) calloc(k, sizeof(double)) ;

    /* ClList=zeros(XSize,1) ; */
    for (i=0; i<XSize; i++) ClList[i]=0 ;
    /* SetCounts=zeros(k,1) ; */
    for (i=0; i<k; i++) SetCounts[i]=0 ;
    
    /* mus=zeros(XDim, k) ; */
    for (i=0; i<XDimk; i++) mus[i]=0 ;

    /* random clustering (select random subsets) */
    /*  ks=ceil(rand(1,XSize)*k) ;
     *  for i=1:k,
     *	actks= (ks==i) ;
     *	c=sum(actks) ;
     *	SetCounts(i)=c ;
     *
     *	ClList(actks)=i*ones(1, c) ;
     *
     *	if ~mus_recalc,
     *		if c>1
     *			mus(:,i) = sum(XData(:,actks)')'/c ;
     *		elseif c>0
     *			mus(:,i) = XData(:,actks) ;
     *		end ;
     *	end ;
     *   end ; */

    for (i=0; i<XSize; i++) 
      {
	const unsigned int Cl= (int) ( rand()%k ) ;
	unsigned int j ;
	
	SetCounts[Cl]++ ;
	ClList[i]=Cl ;
	
	for (j=0; j<XDim; j++)
	  mus[Cl*XDim+j] += XData[i*XDim+j] ;
      } ;
    for (i=0; i<k; i++)
      {
	unsigned int j ;
	
	if (SetCounts[i]!=0)
	  for (j=0; j<XDim; j++)
	    mus[i*XDim+j] /= SetCounts[i] ;
        } ;

    while (changed && (Iter<10000))
    {
        Iter++ ;
	if (Iter==9999)
	  printf("Oops\n") ;
        if (disp)
	  printf("Assignment of %i patterns changed.\n", changed) ;
        changed=0 ;

#ifdef MUSRECALC
	/* mus=zeros(XDim, k) ; */
	for (i=0; i<XDimk; i++) mus[i]=0 ;

        for (i=0; i<XSize; i++) 
        {
            unsigned int j ;
            unsigned int Cl=ClList[i] ;

            for (j=0; j<XDim; j++)
              mus[Cl*XDim+j] += XData[i*XDim+j] ;
        } ;
        for (i=0; i<k; i++)
        {
            unsigned int j ;
            
            if (SetCounts[i]!=0)
              for (j=0; j<XDim; j++)
                mus[i*XDim+j] /= SetCounts[i] ;
        } ;
#endif

        for (i=0; i<XSize; i++)
        {
	    /* ks=ceil(rand(1,XSize)*XSize) ; */
	    const unsigned int Pat=(int) rand()%XSize ;
            const unsigned int ClList_Pat=ClList[Pat], Pat_XDim=Pat*XDim ;
            unsigned int imini, j ;
            double mini ;
    
            /* compute the distance of this point to all centers */
            /* dists=sqdist(mus',XData) ; */
            sqdist(mus, &XData[Pat*XDim], dists, k, 1, XDim) ;

	    /* [mini,imini]=min(dists(:,i)) ; */
            imini=0 ; mini=dists[0] ;
            for (j=1; j<k; j++)
              if (dists[j]<mini)
              {
                mini=dists[j] ;
                imini=j ;
              } ;
        
            if (imini!=ClList_Pat)
            {
              unsigned int j ;

	      changed= changed + 1 ;

              /* SetCounts(imini) = SetCounts(imini) + 1 ; */
	      SetCounts[imini]++ ;
              /* SetCounts(j)     = SetCounts(j)     - 1 ; */
	      SetCounts[ClList_Pat]-- ;

              /* mu_new=mu_old + (x - mu_old)/(n+1) */
	      /* mus(:,imini)=mus(:,imini) + (XData(:,i) - mus(:,imini)) / SetCounts(imini) ; */
              for (j=0; j<XDim; j++)
                 mus[imini*XDim+j] += (XData[Pat*XDim+j] - mus[imini*XDim+j]) / SetCounts[imini] ;

              /* mu_new=mu_old - (x - mu_old)/(n-1) */
              /* if SetCounts(j)~=0 */
	      if (SetCounts[ClList_Pat]!=0)
	          /* mus(:,j)=mus(:,j) - (XData(:,i) - mus(:,j)) / SetCounts(j) ; */
		  for (j=0; j<XDim; j++)
		      mus[ClList_Pat*XDim+j]-=(XData[Pat*XDim+j] - mus[ClList_Pat*XDim+j]) / SetCounts[ClList_Pat] ;
              else
	          /*  mus(:,j)=zeros(XDim,1) ; */
                  for (j=0; j<XDim; j++)
                      mus[ClList_Pat*XDim+j]=0 ;

	      /* ClList(i)= imini ; */
              ClList[Pat] = imini ;
            } ;
        } ;
    } ;

    /* compute the ,,variances'' of the clusters */
    for (i=0; i<k; i++)
    {
        double rmin1, rmin2 ;
        unsigned int j ;
	rmin1=BIG ;
	rmin2=BIG ;

        for (j=0; j<k; j++) 
        {
            if (j!=i)
            {
                unsigned int l ;
                double dist = 0 ;

                for (l=0; l<XDim; l++)
                  dist+=sqr(mus[i*XDim+l]-mus[j*XDim+l]) ;
		/*		printf("%f,", sqrt(dist)) ;*/
                if ((dist<rmin2) && (dist>=rmin1))
		  rmin2=dist ;
                if (dist<rmin1) 
		{
		  rmin2=rmin1 ;
		  rmin1=dist ;
		} ;
            } ;
	} ;
        R[i]=0.7*sqrt(rmin1)+0.3*sqrt(rmin2) ;
	/*	printf("\n(%f, %f->%f)", sqrt(rmin1), sqrt(rmin2), R[i]) ;*/
    } ;

    free(ClList) ;
    free(SetCounts) ;
    free(dists) ;
} 
