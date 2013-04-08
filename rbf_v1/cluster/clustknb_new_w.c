#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "clustknb_new_w.h"
#include "../utils2/sqdist/sqdist.h"

#define BIG            1e+30
#define MUSRECALC
 
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
 

void clustknb_new_w(double *XData, unsigned int k, double *Weights,
                    unsigned int use_old_mus, double *mus_start, double *mus, 
                    double *R, unsigned int XSize, unsigned int XDim, 
		    unsigned int disp) 
{
    unsigned int i, changed=1 ;
    const unsigned int XDimk=XDim*k ;
    unsigned int Iter=0 ;

    unsigned int *ClList = (unsigned int*) calloc(XSize, sizeof(unsigned int)) ;
    double *SetWeigths = (double*) calloc(k, sizeof(double)) ;
    double *oldmus = (double*) calloc(XDimk, sizeof(double)) ;
    double *dists = (double*) calloc(k*XSize, sizeof(double)) ;
    double norm_oldmus_mus ;

    /* ClList=zeros(XSize,1) ; */
    for (i=0; i<XSize; i++) ClList[i]=0 ;
    /* SetWeigths=zeros(k,1) ; */
    for (i=0; i<k; i++) SetWeigths[i]=0 ;
    
    /* mus=zeros(XDim, k) ; */
    for (i=0; i<XDimk; i++) mus[i]=0 ;

    if (!use_old_mus)
    {
        /* random clustering (select random subsets) */
        /*  ks=ceil(rand(1,XSize)*k) ;
	 *  for i=1:k,
	 *	actks= (ks==i) ;
	 *	c=sum(actks) ;
	 *	SetWeigths(i)=c ;
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
	    double weight=Weights[i] ;
            
            SetWeigths[Cl]+=weight ;
            ClList[i]=Cl ;

            for (j=0; j<XDim; j++)
              mus[Cl*XDim+j] += weight*XData[i*XDim+j] ;
        } ;
        for (i=0; i<k; i++)
        {
            unsigned int j ;
            
            if (SetWeigths[i]!=0.0)
              for (j=0; j<XDim; j++)
                mus[i*XDim+j] /= SetWeigths[i] ;
        } ;
    }
    else 
    {
        assert(mus_start!=NULL) ;

        sqdist(mus_start, XData, dists, k, XSize, XDim) ;

        for (i=0; i<XSize; i++)
        {
            double mini=dists[i*k] ;
            unsigned int Cl = 0, j ;
            
            for (j=1; j<k; j++)
              if (dists[i*k+j]<mini)
              {
                Cl=j ;
                mini=dists[i*k+j] ;
              } ;
            ClList[i]=Cl ;
        } ;
    
        /* Compute the sum of all points belonging to a cluster 
         * and count the points */
        for (i=0; i<XSize; i++) 
        {
            const unsigned int Cl = ClList[i] ;
            unsigned int j ;
	    double weight=Weights[i] ;
            SetWeigths[Cl]+=weight ;
#ifndef MUSRECALC
            for (j=0; j<XDim; j++)
              mus[Cl*XDim+j] += weight*XData[i*XDim+j] ;
#endif
        } ;
#ifndef MUSRECALC
        /* normalization to get the mean */ 
        for (i=0; i<k; i++)
            if (SetWeigths[i]!=0.0)
            {
	      unsigned int j ;
	      for (j=0; j<XDim; j++)
                  mus[i*XDim+j] /= SetWeigths[i] ;
	    } ;
#endif
    } ;

    for (i=0; i<XDimk; i++) oldmus[i]=-1 ;

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
	    double weight=Weights[i] ;

            for (j=0; j<XDim; j++)
              mus[Cl*XDim+j] += weight*XData[i*XDim+j] ;
        } ;
        for (i=0; i<k; i++)
        {
            unsigned int j ;
            
            if (SetWeigths[i]!=0.0)
              for (j=0; j<XDim; j++)
                mus[i*XDim+j] /= SetWeigths[i] ;
        } ;
#endif

        for (i=0; i<XSize; i++)
        {
	    /* ks=ceil(rand(1,XSize)*XSize) ; */
	    const unsigned int Pat=(int) rand()%XSize ;
            const unsigned int ClList_Pat=ClList[Pat], Pat_XDim=Pat*XDim ;
            unsigned int imini, j ;
            double mini, weight ;
    
	    weight=Weights[Pat] ;

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

              /* SetWeigths(imini) = SetWeigths(imini) + weight ; */
	      SetWeigths[imini]+= weight ;
              /* SetWeigths(j)     = SetWeigths(j)     - weight ; */
	      SetWeigths[ClList_Pat]-= weight ;

              /* mu_new=mu_old + (x - mu_old)/(n+1) */
	      /* mus(:,imini)=mus(:,imini) + (XData(:,i) - mus(:,imini)) * (weight / SetWeigths(imini)) ; */
              for (j=0; j<XDim; j++)
                 mus[imini*XDim+j] += (XData[Pat*XDim+j] - mus[imini*XDim+j]) *(weight / SetWeigths[imini]) ;

              /* mu_new = mu_old - (x - mu_old)/(n-1) */
              /* if SetWeigths(j)~=0 */
	      if (SetWeigths[ClList_Pat]!=0.0)
	          /* mus(:,j)=mus(:,j) - (XData(:,i) - mus(:,j)) * (weight/SetWeigths(j)) ; */
		  for (j=0; j<XDim; j++)
		      mus[ClList_Pat*XDim+j]-=(XData[Pat*XDim+j]-mus[ClList_Pat*XDim+j])*(weight/SetWeigths[ClList_Pat]);
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
        R[i]=(0.7*sqrt(rmin1)+0.3*sqrt(rmin2)) ;
	/*	printf("\n(%f, %f->%f)", sqrt(rmin1), sqrt(rmin2), R[i]) ;*/
    } ;
 
    free(ClList) ;
    free(SetWeigths) ;
    free(oldmus) ;
    free(dists) ;
} 
                                                  
