static char mc_version[] = "MATLAB Compiler 1.0 infun";
/*
 *  MATLAB Compiler: 1.0
 *  Date: Oct 20, 1995
 *  Arguments: -i comp_w_r 
 */
#include <math.h>
#include "mex.h"
#include "mcc.h"

/* static array S0_ (1 x 40) text, line 36: 'X and Y must have same nu...' */
static double S0__r_[] =
{
         88,   32,   97,  110,  100,   32,   89,   32,
        109,  117,  115,  116,   32,  104,   97,  118,
        101,   32,  115,   97,  109,  101,   32,  110,
        117,  109,   98,  101,  114,   32,  111,  102,
         32,   99,  111,  108,  117,  109,  110,  115,
};
static Matrix S0_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 40, S0__r_, 0, -1, 0, {0} };
/* static array S1_ (1 x 40) text, line 39: 'C and X must have same nu...' */
static double S1__r_[] =
{
         67,   32,   97,  110,  100,   32,   88,   32,
        109,  117,  115,  116,   32,  104,   97,  118,
        101,   32,  115,   97,  109,  101,   32,  110,
        117,  109,   98,  101,  114,   32,  111,  102,
         32,   99,  111,  108,  117,  109,  110,  115,
};
static Matrix S1_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 40, S1__r_, 0, -1, 0, {0} };
/* static array S2_ (1 x 9) text, line 67: 'not impl.' */
static double S2__r_[] =
{
        110,  111,  116,   32,  105,  109,  112,  108,
         46,
};
static Matrix S2_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 9, S2__r_, 0, -1, 0, {0} };
/* static array S3_ (1 x 16) text, line 75: 'Y <-> H mismatch' */
static double S3__r_[] =
{
         89,   32,   60,   45,   62,   32,   72,   32,
        109,  105,  115,  109,   97,  116,   99,  104,
};
static Matrix S3_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 16, S3__r_, 0, -1, 0, {0} };
/* static array S4_ (1 x 20) text, line 81: 'Y <-> pinvH mismatch' */
static double S4__r_[] =
{
         89,   32,   60,   45,   62,   32,  112,  105,
        110,  118,   72,   32,  109,  105,  115,  109,
         97,  116,   99,  104,
};
static Matrix S4_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 20, S4__r_, 0, -1, 0, {0} };
/* static array S5_ (1 x 18) text, line 87: 'parameter mismatch' */
static double S5__r_[] =
{
        112,   97,  114,   97,  109,  101,  116,  101,
        114,   32,  109,  105,  115,  109,   97,  116,
         99,  104,
};
static Matrix S5_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 18, S5__r_, 0, -1, 0, {0} };
/* static array S6_ (1 x 40) text, line 36: 'X and Y must have same nu...' */
static double S6__r_[] =
{
         88,   32,   97,  110,  100,   32,   89,   32,
        109,  117,  115,  116,   32,  104,   97,  118,
        101,   32,  115,   97,  109,  101,   32,  110,
        117,  109,   98,  101,  114,   32,  111,  102,
         32,   99,  111,  108,  117,  109,  110,  115,
};
static Matrix S6_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 40, S6__r_, 0, -1, 0, {0} };
/* static array S7_ (1 x 40) text, line 39: 'C and X must have same nu...' */
static double S7__r_[] =
{
         67,   32,   97,  110,  100,   32,   88,   32,
        109,  117,  115,  116,   32,  104,   97,  118,
        101,   32,  115,   97,  109,  101,   32,  110,
        117,  109,   98,  101,  114,   32,  111,  102,
         32,   99,  111,  108,  117,  109,  110,  115,
};
static Matrix S7_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 40, S7__r_, 0, -1, 0, {0} };
/* static array S8_ (1 x 9) text, line 67: 'not impl.' */
static double S8__r_[] =
{
        110,  111,  116,   32,  105,  109,  112,  108,
         46,
};
static Matrix S8_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 9, S8__r_, 0, -1, 0, {0} };
/* static array S9_ (1 x 16) text, line 75: 'Y <-> H mismatch' */
static double S9__r_[] =
{
         89,   32,   60,   45,   62,   32,   72,   32,
        109,  105,  115,  109,   97,  116,   99,  104,
};
static Matrix S9_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 16, S9__r_, 0, -1, 0, {0} };
/* static array S10_ (1 x 20) text, line 81: 'Y <-> pinvH mismatch' */
static double S10__r_[] =
{
         89,   32,   60,   45,   62,   32,  112,  105,
        110,  118,   72,   32,  109,  105,  115,  109,
         97,  116,   99,  104,
};
static Matrix S10_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 20, S10__r_, 0, -1, 0, {0} };
/* static array S11_ (1 x 18) text, line 87: 'parameter mismatch' */
static double S11__r_[] =
{
        112,   97,  114,   97,  109,  101,  116,  101,
        114,   32,  109,  105,  115,  109,   97,  116,
         99,  104,
};
static Matrix S11_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 18, S11__r_, 0, -1, 0, {0} };

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
   for (ci_=i_=0; i_<nrhs_; ++i_)
   {
      if (prhs_[i_]->pi)
      {
         ci_ = 1;
         break;
      }
      if (prhs_[i_]->pr)
      {
         break;
      }
   }
   if (ci_)
   {
/***************** Compiler Assumptions ****************
 *
 *       A           	complex vector/matrix
 *       C           	complex vector/matrix
 *       CM0_        	complex vector/matrix temporary
 *       CM1_        	complex vector/matrix temporary
 *       CM2_        	complex vector/matrix temporary
 *       H           	complex vector/matrix
 *       HH          	complex vector/matrix
 *       R           	complex vector/matrix
 *       RM0_        	real vector/matrix temporary
 *       RM1_        	real vector/matrix temporary
 *       XData       	complex vector/matrix
 *       YData       	complex vector/matrix
 *       comp_w_r    	<function being defined>
 *       csize       	integer scalar
 *       design      	<function>
 *       diag        	<function>
 *       dummy       	integer scalar
 *       error       	<function>
 *       hhsize      	integer scalar
 *       indim       	integer scalar
 *       indim1      	integer scalar
 *       inv         	<function>
 *       invA        	complex vector/matrix
 *       lambda      	complex vector/matrix
 *       nargin      	<function>
 *       nargout     	<function>
 *       ones        	<function>
 *       outdim      	integer scalar
 *       phsize1     	integer scalar
 *       phsize2     	integer scalar
 *       pinv        	<function>
 *       pinvH       	complex vector/matrix
 *       size        	<function>
 *       w           	complex vector/matrix
 *       xsize       	integer scalar
 *       ysize       	integer scalar
 *******************************************************/
      Matrix w;
      Matrix H;
      Matrix invA;
      Matrix C;
      Matrix R;
      Matrix XData;
      Matrix YData;
      Matrix lambda;
      int indim;
      int xsize;
      int outdim;
      int ysize;
      int indim1;
      int csize;
      Matrix HH;
      int dummy;
      int hhsize;
      Matrix A;
      int phsize1;
      int phsize2;
      Matrix pinvH;
      Matrix CM0_;
      Matrix RM0_;
      Matrix RM1_;
      Matrix CM1_;
      Matrix CM2_;
      
      mccComplexInit(C);
      mccImport(&C, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
      mccComplexInit(R);
      mccImport(&R, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
      mccComplexInit(XData);
      mccImport(&XData, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
      mccComplexInit(YData);
      mccImportCopy(&YData, ((nrhs_>3) ? prhs_[3] : 0), 0, 0);
      mccComplexInit(lambda);
      mccImport(&lambda, ((nrhs_>4) ? prhs_[4] : 0), 0, 0);
      mccComplexInit(w);
      mccComplexInit(H);
      mccComplexInit(invA);
      mccComplexInit(HH);
      mccComplexInit(A);
      mccComplexInit(pinvH);
      mccComplexInit(CM0_);
      mccRealInit(RM0_);
      mccRealInit(RM1_);
      mccComplexInit(CM1_);
      mccComplexInit(CM2_);
      
      /* % Computes the optimal weight vector for a RBF-network with regularisation */
      /* % with the pseudoinverse of H */
      
      /* % [w, H, invA]=comp_w_r(C, R, XData, YData, lambda)  */
      
      /* % Input */
      /* % C         List of centres (Indim-by-m: [c_1 c_2 ... c_m]) (passed to design) */
      /* % R         Scale factors: scalar, n-vector, or n-by-n matrix (passed to design) */
      /* % XData    Input training data (Indim-by-p: [x_1 x_2 x_3 ... x_p]) */
      /* % YData    Output training data (Outdim-by-p: [y_1 y_2 ... y_p]) */
      
      /* % [weights, invA, lambda]=comp_w(H_In, YData, old_lambda)  */
      
      /* % Input */
      /* % H_in     Designmatrix  (p-by-m: [h_1(x_1) h2(x_1) ... h_m(x_1) ; ... ; h_p(x_1) ... ]) */
      /* % YData    Output training data (n-by-p: [y_1 y_2 ... y_p]) */
      
      /* % [weights, lambda]=comp_w(H_In, invA, YData, old_lambda)  */
      
      /* % Input */
      /* % pinvH	   Pseudoinverse of Designmatrix  (m-by-p)   */
      /* % YData    Output training data (Outdim-by-p) */
      
      /* % Output */
      /* % w         optimal weight vector (Outdim-by-m) */
      /* % H         Design matrix (p-by-m) */
      /* % pinvH		Pseudoinverse of Designmatrix (m-by-p)  */
      
      /* if nargin==5, */
      if ((mccNargin() == 5))
      {
         /* % check dimensions */
         /* [indim, xsize]=size(XData) ; */
         mccGetMatrixSize(&indim,&xsize, &XData);
         /* [outdim, ysize]=size(YData) ; */
         mccGetMatrixSize(&outdim,&ysize, &YData);
         /* [indim1, csize]=size(C) ; */
         mccGetMatrixSize(&indim1,&csize, &C);
         /* if xsize~=ysize, */
         if ((xsize != ysize))
         {
            /* error('X and Y must have same number of columns') ; */
            mccError(&S0_);
            /* end ; */
         }
         /* if indim1~=indim */
         if ((indim1 != indim))
         {
            /* error('C and X must have same number of columns') ; */
            mccError(&S1_);
            /* end ; */
         }
         
         /* % design */
         /* H=design(XData, C, R) ; */
         Mprhs_[0] = &XData;
         Mprhs_[1] = &C;
         Mprhs_[2] = &R;
         Mplhs_[0] = &H;
         mccCallMATLAB(1, Mplhs_, 3, Mprhs_, "design", 43);
         
         /* HH=H'*H ; */
         mccConjTrans(&CM0_, &H);
         mccMultiply(&HH, &CM0_, &H);
         /* [dummy,hhsize]=size(HH) ; */
         mccGetMatrixSize(&dummy,&hhsize, &HH);
         
         /* % compute inverse of variance matrix A */
         /* %%% */
         /* A=HH + lambda*diag(ones(1,hhsize)) ; */
         mccOnesMN(&RM0_, 1, hhsize);
         Mprhs_[0] = &RM0_;
         Mplhs_[0] = &RM1_;
         mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "diag", 50);
         mccMultiply(&CM0_, &lambda, &RM1_);
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_A;
            int I_A=1;
            double *q_A;
            double *p_HH;
            int I_HH=1;
            double *q_HH;
            double *p_CM0_;
            int I_CM0_=1;
            double *q_CM0_;
            m_ = mcmCalcResultSize(m_, &n_, HH.m, HH.n);
            m_ = mcmCalcResultSize(m_, &n_, CM0_.m, CM0_.n);
            mccAllocateMatrix(&A, m_, n_);
            I_A = (A.m != 1 || A.n != 1);
            p_A = A.pr;
            q_A = A.pi;
            I_HH = (HH.m != 1 || HH.n != 1);
            p_HH = HH.pr;
            q_HH = HH.pi;
            I_CM0_ = (CM0_.m != 1 || CM0_.n != 1);
            p_CM0_ = CM0_.pr;
            q_CM0_ = CM0_.pi;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_A+=I_A, q_A+=I_A, p_HH+=I_HH, q_HH+=I_HH, p_CM0_+=I_CM0_, q_CM0_+=I_CM0_)
               {
                  *p_A = (*p_HH + *p_CM0_);
                  *q_A = (*q_HH + *q_CM0_);
                  ;
               }
            }
         }
         A.dmode = mxNUMBER;
         /* invA=inv(A) ; */
         Mprhs_[0] = &A;
         Mplhs_[0] = &invA;
         mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "inv", 51);
         /* %i2A=iA^2 ; */
         
         /* % compute projection matrix */
         /* %%% */
         /* %P=H*iA*H' ; */
         /* %P=eye(size(P)) - P ; */
         /* %P2=P^2 ;  */
         
         /* w=invA*H'*YData' ; */
         mccConjTrans(&CM0_, &H);
         mccMultiply(&CM1_, &invA, &CM0_);
         mccConjTrans(&CM2_, &YData);
         mccMultiply(&w, &CM1_, &CM2_);
         
         /* % compute new lambda  */
         /* %lambda_old=YData*P2*YData'*trace(iA-lambda_old*i2A)/(w'*iA*w*trace(P))  */
         
         /* elseif nargin==2 */
      }
      else
      {
         if ((mccNargin() == 2))
         {
            /* % */
            /* error('not impl.') ; */
            mccError(&S2_);
            /* [ysize, outdim]=size(YData) ; */
            mccGetMatrixSize(&ysize,&outdim, &YData);
            /* [phsize1, phsize2]=size(C) ; */
            mccGetMatrixSize(&phsize1,&phsize2, &C);
            
            /* YData=R ; */
            mccCopy(&YData, &R);
            /* if nargout==2 */
            if ((mccNargout() == 2))
            {
               /* % C is the design-matrix */
               /* if phsize1~=ysize, */
               if ((phsize1 != ysize))
               {
                  /* error('Y <-> H mismatch') ; */
                  mccError(&S3_);
                  /* end ; */
               }
               /* pinvH=pinv(C) ; */
               Mprhs_[0] = &C;
               Mplhs_[0] = &pinvH;
               mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "pinv", 77);
               /* else */
            }
            else
            {
               /* % C is the pseudoinverse of the design-matrix */
               /* if phsize2~=ysize, */
               if ((phsize2 != ysize))
               {
                  /* error('Y <-> pinvH mismatch') ; */
                  mccError(&S4_);
                  /* end ; */
               }
               /* pinvH=C ; */
               mccCopy(&pinvH, &C);
               /* end ; */
            }
            
            /* else  */
         }
         else
         {
            /* error('parameter mismatch') ; */
            mccError(&S5_);
            /* end ;  */
         }
      }
      
      mccReturnFirstValue(&plhs_[0], &w);
      mccReturnValue(&plhs_[1], &H);
      mccReturnValue(&plhs_[2], &invA);
   }
   else
   {
/***************** Compiler Assumptions ****************
 *
 *       A           	complex vector/matrix
 *       C           	real vector/matrix
 *       CM0_        	complex vector/matrix temporary
 *       CM1_        	complex vector/matrix temporary
 *       H           	complex vector/matrix
 *       HH          	complex vector/matrix
 *       R           	real vector/matrix
 *       RM0_        	real vector/matrix temporary
 *       RM1_        	real vector/matrix temporary
 *       RM2_        	real vector/matrix temporary
 *       XData       	real vector/matrix
 *       YData       	real vector/matrix
 *       comp_w_r    	<function being defined>
 *       csize       	integer scalar
 *       design      	<function>
 *       diag        	<function>
 *       dummy       	integer scalar
 *       error       	<function>
 *       hhsize      	integer scalar
 *       indim       	integer scalar
 *       indim1      	integer scalar
 *       inv         	<function>
 *       invA        	complex vector/matrix
 *       lambda      	real vector/matrix
 *       nargin      	<function>
 *       nargout     	<function>
 *       ones        	<function>
 *       outdim      	integer scalar
 *       phsize1     	integer scalar
 *       phsize2     	integer scalar
 *       pinv        	<function>
 *       pinvH       	real vector/matrix
 *       size        	<function>
 *       w           	complex vector/matrix
 *       xsize       	integer scalar
 *       ysize       	integer scalar
 *******************************************************/
      Matrix w;
      Matrix H;
      Matrix invA;
      Matrix C;
      Matrix R;
      Matrix XData;
      Matrix YData;
      Matrix lambda;
      int indim;
      int xsize;
      int outdim;
      int ysize;
      int indim1;
      int csize;
      Matrix HH;
      int dummy;
      int hhsize;
      Matrix A;
      int phsize1;
      int phsize2;
      Matrix pinvH;
      Matrix CM0_;
      Matrix RM0_;
      Matrix RM1_;
      Matrix RM2_;
      Matrix CM1_;
      
      mccRealInit(C);
      mccImport(&C, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
      mccRealInit(R);
      mccImport(&R, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
      mccRealInit(XData);
      mccImport(&XData, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
      mccRealInit(YData);
      mccImportCopy(&YData, ((nrhs_>3) ? prhs_[3] : 0), 0, 0);
      mccRealInit(lambda);
      mccImport(&lambda, ((nrhs_>4) ? prhs_[4] : 0), 0, 0);
      mccComplexInit(w);
      mccComplexInit(H);
      mccComplexInit(invA);
      mccComplexInit(HH);
      mccComplexInit(A);
      mccRealInit(pinvH);
      mccComplexInit(CM0_);
      mccRealInit(RM0_);
      mccRealInit(RM1_);
      mccRealInit(RM2_);
      mccComplexInit(CM1_);
      
      /* % Computes the optimal weight vector for a RBF-network with regularisation */
      /* % with the pseudoinverse of H */
      
      /* % [w, H, invA]=comp_w_r(C, R, XData, YData, lambda)  */
      
      /* % Input */
      /* % C         List of centres (Indim-by-m: [c_1 c_2 ... c_m]) (passed to design) */
      /* % R         Scale factors: scalar, n-vector, or n-by-n matrix (passed to design) */
      /* % XData    Input training data (Indim-by-p: [x_1 x_2 x_3 ... x_p]) */
      /* % YData    Output training data (Outdim-by-p: [y_1 y_2 ... y_p]) */
      
      /* % [weights, invA, lambda]=comp_w(H_In, YData, old_lambda)  */
      
      /* % Input */
      /* % H_in     Designmatrix  (p-by-m: [h_1(x_1) h2(x_1) ... h_m(x_1) ; ... ; h_p(x_1) ... ]) */
      /* % YData    Output training data (n-by-p: [y_1 y_2 ... y_p]) */
      
      /* % [weights, lambda]=comp_w(H_In, invA, YData, old_lambda)  */
      
      /* % Input */
      /* % pinvH	   Pseudoinverse of Designmatrix  (m-by-p)   */
      /* % YData    Output training data (Outdim-by-p) */
      
      /* % Output */
      /* % w         optimal weight vector (Outdim-by-m) */
      /* % H         Design matrix (p-by-m) */
      /* % pinvH		Pseudoinverse of Designmatrix (m-by-p)  */
      
      /* if nargin==5, */
      if ((mccNargin() == 5))
      {
         /* % check dimensions */
         /* [indim, xsize]=size(XData) ; */
         mccGetMatrixSize(&indim,&xsize, &XData);
         /* [outdim, ysize]=size(YData) ; */
         mccGetMatrixSize(&outdim,&ysize, &YData);
         /* [indim1, csize]=size(C) ; */
         mccGetMatrixSize(&indim1,&csize, &C);
         /* if xsize~=ysize, */
         if ((xsize != ysize))
         {
            /* error('X and Y must have same number of columns') ; */
            mccError(&S6_);
            /* end ; */
         }
         /* if indim1~=indim */
         if ((indim1 != indim))
         {
            /* error('C and X must have same number of columns') ; */
            mccError(&S7_);
            /* end ; */
         }
         
         /* % design */
         /* H=design(XData, C, R) ; */
         Mprhs_[0] = &XData;
         Mprhs_[1] = &C;
         Mprhs_[2] = &R;
         Mplhs_[0] = &H;
         mccCallMATLAB(1, Mplhs_, 3, Mprhs_, "design", 43);
         
         /* HH=H'*H ; */
         mccConjTrans(&CM0_, &H);
         mccMultiply(&HH, &CM0_, &H);
         /* [dummy,hhsize]=size(HH) ; */
         mccGetMatrixSize(&dummy,&hhsize, &HH);
         
         /* % compute inverse of variance matrix A */
         /* %%% */
         /* A=HH + lambda*diag(ones(1,hhsize)) ; */
         mccOnesMN(&RM0_, 1, hhsize);
         Mprhs_[0] = &RM0_;
         Mplhs_[0] = &RM1_;
         mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "diag", 50);
         mccRealMatrixMultiply(&RM2_, &lambda, &RM1_);
         {
            int m_=1, n_=1, cx_ = 0;
            double t_;
            double *p_A;
            int I_A=1;
            double *q_A;
            double *p_HH;
            int I_HH=1;
            double *q_HH;
            double *p_RM2_;
            int I_RM2_=1;
            m_ = mcmCalcResultSize(m_, &n_, HH.m, HH.n);
            m_ = mcmCalcResultSize(m_, &n_, RM2_.m, RM2_.n);
            mccAllocateMatrix(&A, m_, n_);
            I_A = (A.m != 1 || A.n != 1);
            p_A = A.pr;
            q_A = A.pi;
            I_HH = (HH.m != 1 || HH.n != 1);
            p_HH = HH.pr;
            q_HH = HH.pi;
            I_RM2_ = (RM2_.m != 1 || RM2_.n != 1);
            p_RM2_ = RM2_.pr;
            for (j_=0; j_<n_; ++j_)
            {
               for (i_=0; i_<m_; ++i_, p_A+=I_A, q_A+=I_A, p_HH+=I_HH, q_HH+=I_HH, p_RM2_+=I_RM2_)
               {
                  *p_A = (*p_HH + *p_RM2_);
                  *q_A = (*q_HH + 0.);
                  ;
               }
            }
         }
         A.dmode = mxNUMBER;
         /* invA=inv(A) ; */
         Mprhs_[0] = &A;
         Mplhs_[0] = &invA;
         mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "inv", 51);
         /* %i2A=iA^2 ; */
         
         /* % compute projection matrix */
         /* %%% */
         /* %P=H*iA*H' ; */
         /* %P=eye(size(P)) - P ; */
         /* %P2=P^2 ;  */
         
         /* w=invA*H'*YData' ; */
         mccConjTrans(&CM0_, &H);
         mccMultiply(&CM1_, &invA, &CM0_);
         mccConjTrans(&RM2_, &YData);
         mccMultiply(&w, &CM1_, &RM2_);
         
         /* % compute new lambda  */
         /* %lambda_old=YData*P2*YData'*trace(iA-lambda_old*i2A)/(w'*iA*w*trace(P))  */
         
         /* elseif nargin==2 */
      }
      else
      {
         if ((mccNargin() == 2))
         {
            /* % */
            /* error('not impl.') ; */
            mccError(&S8_);
            /* [ysize, outdim]=size(YData) ; */
            mccGetMatrixSize(&ysize,&outdim, &YData);
            /* [phsize1, phsize2]=size(C) ; */
            mccGetMatrixSize(&phsize1,&phsize2, &C);
            
            /* YData=R ; */
            mccCopy(&YData, &R);
            /* if nargout==2 */
            if ((mccNargout() == 2))
            {
               /* % C is the design-matrix */
               /* if phsize1~=ysize, */
               if ((phsize1 != ysize))
               {
                  /* error('Y <-> H mismatch') ; */
                  mccError(&S9_);
                  /* end ; */
               }
               /* pinvH=pinv(C) ; */
               Mprhs_[0] = &C;
               Mplhs_[0] = &pinvH;
               mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "pinv", 77);
               /* else */
            }
            else
            {
               /* % C is the pseudoinverse of the design-matrix */
               /* if phsize2~=ysize, */
               if ((phsize2 != ysize))
               {
                  /* error('Y <-> pinvH mismatch') ; */
                  mccError(&S10_);
                  /* end ; */
               }
               /* pinvH=C ; */
               mccCopy(&pinvH, &C);
               /* end ; */
            }
            
            /* else  */
         }
         else
         {
            /* error('parameter mismatch') ; */
            mccError(&S11_);
            /* end ;  */
         }
      }
      
      mccReturnFirstValue(&plhs_[0], &w);
      mccReturnValue(&plhs_[1], &H);
      mccReturnValue(&plhs_[2], &invA);
   }
   return;
}
              