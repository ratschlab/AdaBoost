static char mc_version[] = "MATLAB Compiler 1.0 infun";
/*
 *  MATLAB Compiler: 1.0
 *  Date: Oct 20, 1995
 *  Arguments: bootstrap 
 *  *** suppressing complex case: no complex arguments ***
 */
#include <math.h>
#include "mex.h"
#include "mcc.h"

/* static array S0_ (1 x 45) text, line 17: 'different count of sample...' */
static double S0__r_[] =
{
        100,  105,  102,  102,  101,  114,  101,  110,
        116,   32,   99,  111,  117,  110,  116,   32,
        111,  102,   32,  115,   97,  109,  112,  108,
        101,  115,   32,  105,  110,   32,   88,   68,
         97,  116,   97,   32,   97,  110,  100,   32,
         89,   68,   97,  116,   97,
};
static Matrix S0_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 45, S0__r_, 0, -1, 0, {0} };
/* static array S1_ (1 x 21) text, line 23: 'not enough parameters' */
static double S1__r_[] =
{
        110,  111,  116,   32,  101,  110,  111,  117,
        103,  104,   32,  112,   97,  114,   97,  109,
        101,  116,  101,  114,  115,
};
static Matrix S1_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 21, S1__r_, 0, -1, 0, {0} };
/* static array S2_ (1 x 17) text, line 53: 'round-off-problem' */
static double S2__r_[] =
{
        114,  111,  117,  110,  100,   45,  111,  102,
        102,   45,  112,  114,  111,   98,  108,  101,
        109,
};
static Matrix S2_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 17, S2__r_, 0, -1, 0, {0} };

void
mexFunction(
    int nlhs_,
    Matrix *plhs_[],
    int nrhs_,
    Matrix *prhs_[]
)
{
   int ci_, i_, j_;
   unsigned flags_;
   Matrix *Mplhs_[32], *Mprhs_[32];
/***************** Compiler Assumptions ****************
 *
 *       CumProb     	real vector/matrix
 *       Indexs      	real vector/matrix
 *       Prob        	real vector/matrix
 *       R0_         	real scalar temporary
 *       RM0_        	real vector/matrix temporary
 *       RM1_        	real vector/matrix temporary
 *       SMALL       	real scalar
 *       Size        	real vector/matrix
 *       XData       	real vector/matrix
 *       XSet        	real vector/matrix
 *       YData       	real vector/matrix
 *       YSet        	real vector/matrix
 *       abs         	<function>
 *       any         	<function>
 *       bootstrap   	<function being defined>
 *       ceil        	<function>
 *       eps         	<function>
 *       error       	<function>
 *       i           	integer scalar
 *       j           	integer scalar
 *       nargin      	<function>
 *       rand        	<function>
 *       realization 	real vector/matrix
 *       samples     	integer scalar
 *       size        	<function>
 *       sum         	<function>
 *       uniform     	integer scalar
 *       zeros       	<function>
 *******************************************************/
   Matrix XSet;
   Matrix YSet;
   Matrix Indexs;
   Matrix XData;
   Matrix YData;
   Matrix Prob;
   Matrix Size;
   double SMALL;
   int samples;
   int uniform;
   Matrix CumProb;
   int i;
   Matrix realization;
   int j;
   Matrix RM0_;
   double R0_;
   Matrix RM1_;
   
   mccRealInit(XData);
   mccImport(&XData, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
   mccRealInit(YData);
   mccImport(&YData, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
   mccRealInit(Prob);
   mccImportCopy(&Prob, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
   mccRealInit(Size);
   mccImportCopy(&Size, ((nrhs_>3) ? prhs_[3] : 0), 0, 0);
   mccRealInit(XSet);
   mccRealInit(YSet);
   mccRealInit(Indexs);
   mccRealInit(CumProb);
   mccRealInit(realization);
   mccRealInit(RM0_);
   mccRealInit(RM1_);
   
   /* % [XSet, YSet, Indexs]=bootstrap(XData, YData,    */
   /* % Prob=ones(1,size(XData), Size=size(XData,2)) */
   
   /* % Creates a bootstrap-samples-set of size 'Size'  */
   
   /* % #realonly */
   /* % #inbounds */
   
   /* SMALL=1e4*eps ; */
   SMALL = (1e4 * mcmEps());
   
   /* % save the count of samples  */
   /* samples=size(XData,2) ; */
   samples = mccGetDimensionSize(&XData, 2);
   
   /* % verify this */
   /* if samples~=size(YData,2), */
   if ((samples != mccGetDimensionSize(&YData, 2)))
   {
      /* error('different count of samples in XData and YData') ; */
      mccError(&S0_);
      /* end ; */
   }
   
   /* % handle default parameters */
   /* if nargin<2, */
   if ((mccNargin() < 2))
   {
      /* % not enough parameters */
      /* error('not enough parameters') ; */
      mccError(&S1_);
      /* end ; */
   }
   /* if nargin<3,  */
   if ((mccNargin() < 3))
   {
      /* % uniform distribution */
      /* % Prob=ones(1, samples)./samples ; */
      /* uniform=1 ; */
      uniform = 1;
      /* else */
   }
   else
   {
      /* % normalize the give distribution */
      /* Prob=Prob./(sum(Prob)+eps) ; */
      mccSum(&RM0_, &Prob);
      R0_ = mcmEps();
      {
         int m_=1, n_=1, cx_ = 0;
         double t_;
         double *p_Prob;
         int I_Prob=1;
         double *p_1Prob;
         int I_1Prob=1;
         double *p_RM0_;
         int I_RM0_=1;
         m_ = mcmCalcResultSize(m_, &n_, Prob.m, Prob.n);
         m_ = mcmCalcResultSize(m_, &n_, RM0_.m, RM0_.n);
         mccAllocateMatrix(&Prob, m_, n_);
         I_Prob = (Prob.m != 1 || Prob.n != 1);
         p_Prob = Prob.pr;
         I_1Prob = (Prob.m != 1 || Prob.n != 1);
         p_1Prob = Prob.pr;
         I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
         p_RM0_ = RM0_.pr;
         for (j_=0; j_<n_; ++j_)
         {
            for (i_=0; i_<m_; ++i_, p_Prob+=I_Prob, p_1Prob+=I_1Prob, p_RM0_+=I_RM0_)
            {
               *p_Prob = (*p_1Prob / (double) (*p_RM0_ + R0_));
               ;
            }
         }
      }
      Prob.dmode = mxNUMBER;
      /* if any( Prob - 1/samples > 1e-8 ), */
      R0_ = (1 / (double) samples);
      RM0_.dmode = mxNUMBER;
      {
         int m_=1, n_=1, cx_ = 0;
         double t_;
         double *p_RM0_;
         int I_RM0_=1;
         double *p_Prob;
         int I_Prob=1;
         m_ = mcmCalcResultSize(m_, &n_, Prob.m, Prob.n);
         mccAllocateMatrix(&RM0_, m_, n_);
         I_RM0_ = (RM0_.m != 1 || RM0_.n != 1);
         p_RM0_ = RM0_.pr;
         I_Prob = (Prob.m != 1 || Prob.n != 1);
         p_Prob = Prob.pr;
         for (j_=0; j_<n_; ++j_)
         {
            for (i_=0; i_<m_; ++i_, p_RM0_+=I_RM0_, p_Prob+=I_Prob)
            {
               *p_RM0_ = ((*p_Prob - R0_) > 1e-8);
               ;
            }
         }
      }
      RM0_.dmode = mxNUMBER;
      mccAny(&RM1_, &RM0_);
      if (mccIfCondition(&RM1_))
      {
         /* uniform=0 ; */
         uniform = 0;
         /* else */
      }
      else
      {
         /* uniform=1 ; */
         uniform = 1;
         /* end ; */
      }
      /* end ; */
   }
   /* if nargin<4, */
   if ((mccNargin() < 4))
   {
      /* % the bootstrap size equals the size of the given set defaultly */
      /* Size=samples ; */
      {
         double tr_ = samples;
         mccAllocateMatrix(&Size, 1, 1);
         *Size.pr = tr_;
      }
      Size.dmode = mxNUMBER;
      /* end ; */
   }
   
   /* % optimization for uniform distributions */
   /* if ~uniform, */
   if ((double)(!uniform))
   {
      /* % compute the cumulative propability */
      /* CumProb=zeros(1,samples) ; */
      mccZerosMN(&CumProb, 1, samples);
      /* CumProb(1)=Prob(1) ; */
      CumProb.pr[(1-1)] = (Prob.pr[(1-1)]);
      CumProb.dmode = mxNUMBER;
      /* for i=2:samples, */
      for (i = 2; i <= samples; i = i + 1)
      {
         /* CumProb(i)=CumProb(i-1)+Prob(i) ; */
         CumProb.pr[(i-1)] = ((CumProb.pr[((i-1)-1)]) + (Prob.pr[(i-1)]));
         CumProb.dmode = mxNUMBER;
         /* end ; */
      }
      /* if abs(CumProb(samples)-1)>SMALL, */
      if ((fabs(((CumProb.pr[(samples-1)]) - 1)) > SMALL))
      {
         /* % CumProb(samples)-1 */
         /* error('round-off-problem') ; */
         mccError(&S2_);
         /* end ; */
      }
      /* end ; */
   }
   
   /* % not fast, but it works */
   /* realization=rand(1,Size) ; */
   Mprhs_[0] = mccTempMatrix((double)(1), 0., mxNUMBER);
   Mprhs_[1] = &Size;
   Mplhs_[0] = &realization;
   mccCallMATLAB(1, Mplhs_, 2, Mprhs_, "rand", 58);
   /* if uniform, */
   if ((double)uniform)
   {
      /* Indexs=ceil(samples*realization) ; */
      RM1_.dmode = mxNUMBER;
      {
         int m_=1, n_=1, cx_ = 0;
         double t_;
         double *p_RM1_;
         int I_RM1_=1;
         double *p_realization;
         int I_realization=1;
         m_ = mcmCalcResultSize(m_, &n_, realization.m, realization.n);
         mccAllocateMatrix(&RM1_, m_, n_);
         I_RM1_ = (RM1_.m != 1 || RM1_.n != 1);
         p_RM1_ = RM1_.pr;
         I_realization = (realization.m != 1 || realization.n != 1);
         p_realization = realization.pr;
         for (j_=0; j_<n_; ++j_)
         {
            for (i_=0; i_<m_; ++i_, p_RM1_+=I_RM1_, p_realization+=I_realization)
            {
               *p_RM1_ = (samples * *p_realization);
               ;
            }
         }
      }
      RM1_.dmode = mxNUMBER;
      mccCeil(&Indexs, &RM1_);
      /* else */
   }
   else
   {
      /* Indexs=zeros(1,Size) ; */
      mccZerosMN(&Indexs, 1, ((int)*Size.pr));
      /* for j=1:Size, */
      for (j = 1; j <= *Size.pr; j = j + 1)
      {
         /* Indexs(j)=sum(CumProb<=realization(j)) + 1 ; */
         R0_ = (realization.pr[(j-1)]);
         RM1_.dmode = mxNUMBER;
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_RM1_;
            int I_RM1_=1;
            double *p_CumProb;
            int I_CumProb=1;
            m_ = mcmCalcResultSize(m_, &n_, CumProb.m, CumProb.n);
            mccAllocateMatrix(&RM1_, m_, n_);
            I_RM1_ = (RM1_.m != 1 || RM1_.n != 1);
            p_RM1_ = RM1_.pr;
            I_CumProb = (CumProb.m != 1 || CumProb.n != 1);
            p_CumProb = CumProb.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_RM1_+=I_RM1_, p_CumProb+=I_CumProb)
               {
                  *p_RM1_ = (*p_CumProb <= R0_);
                  ;
               }
            }
         }
         RM1_.dmode = mxNUMBER;
         Indexs.pr[(j-1)] = (IntRealVectorSum(&RM1_) + 1);
         Indexs.dmode = mxNUMBER;
         /* end ; */
      }
      /* end ; */
   }
   
   /* XSet=XData(:, Indexs) ; */
   mccFindRowIndex(&RM1_, &Indexs, &XData);
   {
      int m_=1, n_=1, cx_ = 0;
      double t_;
      double *p_XSet;
      int I_XSet=1;
      double *p_XData;
      int I_XData=1;
      double *p_RM1_;
      int I_RM1_=1;
      m_ = mcmCalcResultSize(m_, &n_, XData.m, (RM1_.m * RM1_.n));
      mccAllocateMatrix(&XSet, m_, n_);
      I_XSet = (XSet.m != 1 || XSet.n != 1);
      p_XSet = XSet.pr;
      I_RM1_ = (RM1_.m != 1 || RM1_.n != 1);
      p_RM1_ = RM1_.pr;
      for (j_=0; j_<n_; ++j_, p_RM1_ += I_RM1_)
      {
         p_XData = XData.pr + XData.m * ((int)(*p_RM1_ - .5)) + 0;
         for (i_=0; i_<m_; ++i_, p_XSet+=I_XSet, p_XData+=I_XData)
         {
            *p_XSet = *p_XData;
            ;
         }
      }
   }
   XSet.dmode = XData.dmode;
   /* YSet=YData(:, Indexs) ; */
   mccFindRowIndex(&RM1_, &Indexs, &YData);
   {
      int m_=1, n_=1, cx_ = 0;
      double t_;
      double *p_YSet;
      int I_YSet=1;
      double *p_YData;
      int I_YData=1;
      double *p_RM1_;
      int I_RM1_=1;
      m_ = mcmCalcResultSize(m_, &n_, YData.m, (RM1_.m * RM1_.n));
      mccAllocateMatrix(&YSet, m_, n_);
      I_YSet = (YSet.m != 1 || YSet.n != 1);
      p_YSet = YSet.pr;
      I_RM1_ = (RM1_.m != 1 || RM1_.n != 1);
      p_RM1_ = RM1_.pr;
      for (j_=0; j_<n_; ++j_, p_RM1_ += I_RM1_)
      {
         p_YData = YData.pr + YData.m * ((int)(*p_RM1_ - .5)) + 0;
         for (i_=0; i_<m_; ++i_, p_YSet+=I_YSet, p_YData+=I_YData)
         {
            *p_YSet = *p_YData;
            ;
         }
      }
   }
   YSet.dmode = YData.dmode;
   mccReturnFirstValue(&plhs_[0], &XSet);
   mccReturnValue(&plhs_[1], &YSet);
   mccReturnValue(&plhs_[2], &Indexs);
   return;
}
                                              