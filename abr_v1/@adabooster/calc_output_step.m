function [ys, y_nets]=calc_output_step(bb, XData, maxbs)
% [ys, y_nets]=adabooster.calc_output_step(rn, XData, maxbs)
% 
% parameter            class
% bb                   rbf_net_ls        
% XData                double matrix
% ys                   double matrix     Ausgabevektoren (booststeps-by-p)
% y_nets               double matrix     Ausgabevektoren (booststeps-by-p)
%

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

if nargin<3,
  maxbs=get_boost_steps(bb) ;
end ;

sum_weights=0 ;
ys=zeros(min(maxbs, get_boost_steps(bb)), size(XData,2)) ;
y_nets=ys ;
y=0 ;

for i=1:min(maxbs, get_boost_steps(bb))
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
  ys(i,:)=y./sum_weights ;
  y_nets(i,:)=y_net ;
end ;

if ~isa(net, 'learner')
  ys=ys(1:i-1,:) ;
  y_nets=y_nets(1:i-1,:) ;
end ;




