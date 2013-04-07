function [bb, delta, ok]=comp_weight(bb, It, output, dataset, Distr)
%[bb, BetaT, ok]=comp_weight(bb, It, output, dataset, Distr)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

delta_ubound=10 ;
switch  get_use_sign_output(bb),
  case 2,
    bb.adabooster.last_output=sigmoid(output) ;
  case 1,
    bb.adabooster.last_output=sign(output) ;
  case 0,
    bb.adabooster.last_output=output ;
  otherwise,
    error('???') ;
end ;

if It==1,
  bb.adabooster.fin_hyp = 0 ;
  bb.vi=0 ;
end

vw=get_vote_weight(bb,1:It-1) ;
vws=sum(vw) ;
P.vws=vws ;
P.fin_hyp=bb.adabooster.fin_hyp ;
P.last_output=bb.adabooster.last_output ;
P.phi=bb.phi ;
P.lambda=bb.lambda ;
P.labels=get_train(dataset,2) ;
P.vi=bb.vi ;
P.Distr=Distr ;

delta=fmin('erfunc', 0, delta_ubound, [0, 1.e-5], P) ;
ok=(delta/(vws+delta))>1e-5 ;
if ~ok,
  return ;
end ;

% compute the unnormalized final hypotheses
bb.adabooster.fin_hyp = bb.adabooster.fin_hyp + delta*bb.adabooster.last_output ;

% compute the weighting of the patterns in the last steps
bb.vi=bb.vi+delta*Distr ;

