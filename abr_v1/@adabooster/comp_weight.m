function [bb, delta, ok]=comp_weight(bb, It, output, dataset, Distr, EpsT)
%[bb, delta, ok]=comp_weight(bb, It, output, dataset, Distr, EpsT)

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

delta_ubound=1e4 ;
delta_ubound_start=10 ;

switch get_use_sign_output(bb),
  case 2,
  bb.last_output=sigmoid(output) ;
case 1,
  bb.last_output=sign(output) ;
case 0,
  bb.last_output=output ;
otherwise,
  error('???') ;
end ;
  
vw=get_vote_weight(bb,1:It-1) ;
vws=sum(vw) ;
P.vws=vws ;
P.fin_hyp=bb.fin_hyp ;
P.last_output=bb.last_output ;
P.labels=get_train(dataset,2) ;
P.bb=bb ;

% find delta minimizing the error function G
ubound=delta_ubound_start ; 
ok=0 ;
while (ubound<delta_ubound) & ~ok,
  delta=fmin('erfunc', 0, ubound, [0, erfunc(0,P)*1e-7], P) ;
  % check wheter it is on the upper bound or not
  ok=(abs(delta-ubound)>1e-1) & (erfunc(delta,P)>0);
  ubound=ubound*5 ;
end ;

% check whether it was on one of the bounds
if (delta/(delta+vws)<1e-5) | (~ok),
  ok=0 ;
  return ;
end ;

ok=1 ;

% update the unnormalized final hypotheses
bb.fin_hyp = bb.fin_hyp + delta*bb.last_output ;
