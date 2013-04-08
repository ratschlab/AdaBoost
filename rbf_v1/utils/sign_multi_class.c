static char mc_version[] = "MATLAB Compiler 1.2 Jan 17 1998 infun";
/*
 *  MATLAB Compiler: 1.2
 *  Date: Jan 17 1998
 *  Arguments: -ir sign_multi_class 
 */
#ifndef ARRAY_ACCESS_INLINING
#error You must use the -inline option when compiling MATLAB compiler generated code with MEX or MBUILD
#endif
#ifndef MATLAB_COMPILER_GENERATED_CODE
#define MATLAB_COMPILER_GENERATED_CODE
#endif

#include <math.h>
#include "mex.h"
#include "mcc.h"

/***************** Compiler Assumptions ****************
 *
 *       I0_         	integer scalar temporary
 *       I1_         	integer scalar temporary
 *       IM0_        	integer vector/matrix temporary
 *       i           	integer scalar
 *       idx         	integer vector/matrix
 *       length      	<function>
 *       max         	<function>
 *       out         	real vector/matrix
 *       s_out       	integer vector/matrix
 *       sign_multi_class	<function being defined>
 *       size        	<function>
 *       tmp         	real vector/matrix
 *       zeros       	<function>
 *******************************************************/

void
mexFunction(
    int nlhs_,
    mxArray *plhs_[],
    int nrhs_,
    const mxArray *prhs_[]
)
{
   mxArray *Mplhs_[2];
   mxArray *Mprhs_[1];
   

   if (nrhs_ > 1 )
   {
      mexErrMsgTxt( "Too many input arguments." );
   }

   if (nlhs_ > 1 )
   {
      mexErrMsgTxt( "Too many output arguments." );
   }

   {
      mxArray s_out;
      mxArray out;
      mxArray tmp;
      mxArray idx;
      int i = 0;
      mxArray IM0_;
      int I0_ = 0;
      int I1_ = 0;
      
      mccRealInit(out);
      mccImport(&out, ((nrhs_>0) ? prhs_[0] : 0), 0, 0);
      mccIntInit(s_out);
      mccRealInit(tmp);
      mccIntInit(idx);
      mccIntInit(IM0_);
      
      /* % s_out=sign_multi_class(out) */
      
      /* s_out=zeros(size(out)) ; */
      if(mccNOTSET(&out))
      {
         mexErrMsgTxt( "variable out undefined, line 4" );
      }
      mccSize(&IM0_, &out);
      mccZeros(&s_out, &IM0_);
      /* [tmp,idx]=max(out) ; */
      Mprhs_[0] = &out;
      Mplhs_[0] = &tmp;
      Mplhs_[1] = &idx;
      mccCallMATLAB(2, Mplhs_, 1, Mprhs_, "max", 5);
      /* for i=1:length(idx), */
      I1_ = mccGetLength(&idx);
      for (I0_ = 1; I0_ <= I1_; I0_ = I0_ + 1)
      {
         i = I0_;
         /* s_out(idx(i),i)=1 ; */
         mccIPR(&s_out)[(((int)((int)mccIPR(&idx)[(i-1)]))-1) + mccM(&s_out)*(i-1)] = 1;
         /* end ; */
      }
      mccReturnFirstValue(&plhs_[0], &s_out);
   }
   return;
}
