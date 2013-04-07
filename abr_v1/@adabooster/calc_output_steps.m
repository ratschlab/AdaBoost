function [ys, y_nets]=calc_output_steps(bb, XData, steps)
% [ys, y_nets]=adabooster.calc_output_steps(rn, XData, steps)
% 
% parameter            class
% bb                   rbf_net_ls        
% XData                double matrix
% steps                index vector 
% ys                   double matrix     Ausgabevektoren (booststeps-by-p)
% y_nets               double matrix     Ausgabevektoren (booststeps-by-p)
%

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

tmp_size=length(steps) ;
sum_weights=0 ;
ys=zeros(tmp_size, size(XData,2)) ;
if nargout>1,
  y_nets=ys ;
end ;
y=0 ;

j=0 ;
for i=1:min([get_boost_steps(bb) length(get_boosted_learner(bb)) length(get_vote_weights(bb))]) ;
  net=get_boosted_learner(bb, i) ;
  if ~isa(net, 'learner'),
    break ;
  end ;
  switch bb.use_sign_output,
  case 2,
    y_net=sigmoid(calc_output(net, XData)) ;
  case 1,
    y_net=sign(calc_output(net, XData)) ;
  case 0,
    y_net=calc_output(net, XData) ;
  otherwise,
    error('???') ;
  end ;
  sum_weights=sum_weights+get_vote_weight(bb,i) ;
  
  y=y+y_net*get_vote_weight(bb,i) ;

  if any(i==steps),
    j=j+1 ;
    ys(j,:)=y./sum_weights ;
    if nargout>1,
      y_nets(j,:)=y_net ;
    end ;
  end ;
end ;

j_ok=j ;
if max(steps)>=i,
  idxs=find(steps>i) ;
  for idx=idxs,
    j=j+1 ;
    ys(j,:)=y./sum_weights ;
    if nargout>1,
      error('not implemented') ;
    end ;
  end ;  
else
  if (j~=length(steps))
     keyboard,
  end ;
end ;


