static char mc_version[] = "MATLAB Compiler 1.0 infun";
/*
 *  MATLAB Compiler: 1.0
 *  Date: Oct 20, 1995
 *  Arguments: -ir comp_w 
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
/* static array S2_ (1 x 16) text, line 60: 'Y <-> H mismatch' */
static double S2__r_[] =
{
         89,   32,   60,   45,   62,   32,   72,   32,
        109,  105,  115,  109,   97,  116,   99,  104,
};
static Matrix S2_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 16, S2__r_, 0, -1, 0, {0} };
/* static array S3_ (1 x 18) text, line 73: 'parameter mismatch' */
static double S3__r_[] =
{
        112,   97,  114,   97,  109,  101,  116,  101,
        114,   32,  109,  105,  115,  109,   97,  116,
         99,  104,
};
static Matrix S3_ = { {0}, mxFULL, mxDOUBLE, mxSTRING, 0,
        1, 18, S3__r_, 0, -1, 0, {0} };

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
 *       C           	real vector/matrix
 *       H           	real vector/matrix
 *       H_in        	real vector/matrix
 *       R           	real vector/matrix
 *       RM0_        	real vector/matrix temporary
 *       XData       	real vector/matrix
 *       YData       	real vector/matrix
 *       comp_w      	<function being defined>
 *       csize       	integer scalar
 *       design      	<function>
 *       error       	<function>
 *       indim       	integer scalar
 *       indim1      	integer scalar
 *       nargin      	<function>
 *       outdim      	integer scalar
 *       phsize1     	integer scalar
 *       phsize2     	integer scalar
 *       pinv        	<function>
 *       pinvH       	real vector/matrix
 *       size        	<function>
 *       w           	real vector/matrix
 *       xsize       	integer scalar
 *       ysize       	integer scalar
 *******************************************************/
   Matrix w;
   Matrix H;
   Matrix pinvH;
   Matrix C;
   Matrix R;
   Matrix XData;
   Matrix YData;
   Matrix H_in;
   int indim;
   int xsize;
   int outdim;
   int ysize;
   int indim1;
   int csize;
   int phsize1;
   int phsize2;
   Matrix RM0_;
   
   mccRealInit(C);
   mccImport(&C, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
   mccRealInit(R);
   mccImport(&R, ((nrhs_>1) ? prhs_[1] : 0), 0, 0);
   mccRealInit(XData);
   mccImport(&XData, ((nrhs_>2) ? prhs_[2] : 0), 0, 0);
   mccRealInit(YData);
   mccImportCopy(&YData, ((nrhs_>3) ? prhs_[3] : 0), 0, 0);
   mccRealInit(H_in);
   mccImport(&H_in, ((nrhs_>4) ? prhs_[4] : 0), 0, 0);
   mccRealInit(w);
   mccRealInit(H);
   mccRealInit(pinvH);
   mccRealInit(RM0_);
   
   /* % Computes the optimal weight vector for a RBF-network without regularisation */
   /* % with the pseudoinverse of H */
   
   /* % [w, H, pinvH]=comp_w(C, R, XData, YData)  */
   
   /* % Input */
   /* % C         List of centres (Indim-by-m: [c_1 c_2 ... c_m]) (passed to design) */
   /* % R         Scale factors: scalar, n-vector, or n-by-n matrix (passed to design) */
   /* % XData    Input training data (Indim-by-p: [x_1 x_2 x_3 ... x_p]) */
   /* % YData    Output training data (Outdim-by-p: [y_1 y_2 ... y_p]) */
   
   /* % [weights, pinvH]=comp_w(H_In, YData)  */
   
   /* % Input */
   /* % H_in     Designmatrix  (p-by-m: [h_1(x_1) h2(x_1) ... h_m(x_1) ; ... ; h_p(x_1) ... ]) */
   /* % YData    Output training data (n-by-p: [y_1 y_2 ... y_p]) */
   
   /* % weights=comp_w(H, pinvH, YData)  */
   
   /* % Input */
   /* % pinvH	Pseudoinverse of Designmatrix  (m-by-p)   */
   /* % YData    Output training data (Outdim-by-p) */
   
   /* % Output */
   /* % w         optimal weight vector (Outdim-by-m) */
   /* % H         Design matrix (p-by-m) */
   /* % pinvH	    Pseudoinverse of Designmatrix (m-by-p)  */
   
   /* if nargin>=4, */
   if ((mccNargin() >= 4))
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
      /* if nargin>4 */
      if ((mccNargin() > 4))
      {
         /* H=H_in ; */
         mccCopy(&H, &H_in);
         /* else */
      }
      else
      {
         /* H=design(XData, C, R) ; */
         Mprhs_[0] = &XData;
         Mprhs_[1] = &C;
         Mprhs_[2] = &R;
         Mplhs_[0] = &H;
         mccCallMATLAB(1, Mplhs_, 3, Mprhs_, "design", 46);
         /* end ; */
      }
      
      /* % computer pseudoinverse */
      /* pinvH=pinv(H) ; */
      Mprhs_[0] = &H;
      Mplhs_[0] = &pinvH;
      mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "pinv", 50);
      
      /* elseif nargin==2 */
   }
   else
   {
      if ((mccNargin() == 2))
      {
         /* % */
         /* [outdim, ysize]=size(R) ; */
         mccGetMatrixSize(&outdim,&ysize, &R);
         /* [phsize1, phsize2]=size(C) ; */
         mccGetMatrixSize(&phsize1,&phsize2, &C);
         
         /* YData=R ; */
         mccCopy(&YData, &R);
         /* % C is the design-matrix */
         /* if phsize1~=ysize, */
         if ((phsize1 != ysize))
         {
            /* error('Y <-> H mismatch') ; */
            mccError(&S2_);
            /* end ; */
         }
         /* pinvH=pinv(C) ; */
         Mprhs_[0] = &C;
         Mplhs_[0] = &pinvH;
         mccCallMATLAB(1, Mplhs_, 1, Mprhs_, "pinv", 62);
         
         /* %else */
         /* %     % C is the pseudoinverse of the design-matrix */
         /* %     if phsize2~=ysize, */
         /* %           error('Y <-> pinvH mismatch') ; */
         /* %     end ; */
         /* %     pinvH=C ; */
         /* %end ; */
         
         /* else  */
      }
      else
      {
         /* error('parameter mismatch') ; */
         mccError(&S3_);
         /* end ;  */
      }
   }
   
   /* w=pinvH*YData' ; */
   mccConjTrans(&RM0_, &YData);
   mccRealMatrixMultiply(&w, &pinvH, &RM0_);
   
   mccReturnFirstValue(&plhs_[0], &w);
   mccReturnValue(&plhs_[1], &H);
   mccReturnValue(&plhs_[2], &pinvH);
   return;
}
                                            