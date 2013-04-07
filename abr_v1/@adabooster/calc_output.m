function y=calc_output(bb, XData)
% y=adabooster.calc_output(rn, XData)
% 
% parameter            class
% bb                   rbf_net_ls        
% XData                double matrix
% y                    double matrix     Ausgabevektoren (Outdim-by-p)
%

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

sum_weights=0 ;
y=0 ;
for i=1:min([get_boost_steps(bb), length(get_vote_weights(bb))]) ;
  net=get_boosted_learner(bb, i) ;
  if ~isa(net, 'learner'),
    break ;
  end ;
  y_net=calc_output(net, XData) ;
  
  sum_weights=sum_weights+get_vote_weight(bb,i) ;

  switch bb.use_sign_output,
    case 2,
      y=y+sigmoid(y_net)*get_vote_weight(bb,i) ;
    case 1,
      y=y+sign(y_net)*get_vote_weight(bb,i) ;
    case 0,
      y=y+y_net*get_vote_weight(bb,i) ;
    otherwise,
      error('???') ;
  end ;
end ;
y=y./sum_weights ;
	




