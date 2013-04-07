function [cles, cles_nets]=get_class_errors_step(bb, dataset)
% [cles, cles_nets]=adabooster.get_class_errors_step(rn, dataset)
% 
% parameter            class
% bb                   rbf_net_ls        
% dataset              data
%

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

sum_weights=0 ;
steps=min([get_boost_steps(bb), ...
             length(get_boosted_learner(bb)), ...
             length(get_vote_weights(bb))]) ;
cles=zeros(3, steps) ;
cles_nets=cles ;
y_tr=0 ;
y_test=0 ;
y_val=0 ;

for i=1:steps
  net=get_boosted_learner(bb, i) ;
  if ~isa(net, 'learner'),
    break ;
  end ;

  switch bb.use_sign_output,
    case 2,    
      y_net_tr=sigmoid(calc_output(net, get_train(dataset,1))) ;
      if get_test_size(dataset)~=0,
	y_net_test=sigmoid(calc_output(net, get_test(dataset,1))) ;
      else
	y_net_test=0 ;
      end ;
      if get_val_size(dataset)~=0,
	y_net_val=sigmoid(calc_output(net, get_val(dataset,1))) ;
      else
	y_net_val=0 ;
      end ;
    case 1,  
      y_net_tr=sign(calc_output(net, get_train(dataset,1))) ;
      if get_test_size(dataset)~=0,
	y_net_test=sign(calc_output(net, get_test(dataset,1))) ;
      else
	y_net_test=0 ;
      end ;
      if get_val_size(dataset)~=0,
	y_net_val=sign(calc_output(net, get_val(dataset,1))) ;
      else
	y_net_val=0 ;
      end ;
    case 0,
      y_net_tr=calc_output(net, get_train(dataset,1)) ;
      if get_test_size(dataset)~=0,
	y_net_test=calc_output(net, get_test(dataset,1)) ;
      else
	y_net_test=0 ;
      end ;
      if get_val_size(dataset)~=0,
	y_net_val=calc_output(net, get_val(dataset,1)) ;
      else
	y_net_val=0 ;
      end ;
    otherwise,
      error('???') ;
  end ;

  sum_weights=sum_weights+get_vote_weight(bb,i) ;
  
  y_tr=y_tr+y_net_tr*get_vote_weight(bb,i) ;
  y_test=y_test+y_net_test*get_vote_weight(bb,i) ;
  y_val=y_val+y_net_val*get_vote_weight(bb,i) ;
  
  cles(1,i)=sum(get_train(dataset,2)~=sign(y_tr)) ;
  cles_nets(1,i)=sum(get_train(dataset,2)~=sign(y_net_tr)) ;

  if get_test_size(dataset)>0,
    cles(2,i)=sum(get_test(dataset,2)~=sign(y_test)) ;
    cles_nets(2,i)=sum(get_test(dataset,2)~=sign(y_net_test)) ;
  else  
    cles(2,i)=-1 ;
    cles_nets(2,i)=-1 ;
  end ;
  
  if get_val_size(dataset)>0,
    cles(3,i)=sum(get_val(dataset,2)~=sign(y_val)) ;
    cles_nets(3,i)=sum(get_val(dataset,2)~=sign(y_net_val)) ;
  else
    cles(3,i)=-1 ;
    cles_nets(3,i)=-1 ;
  end ;
end ;

if ~isa(net, 'learner')
  cles=cles(:, 1:i-1) ;
  cles_nets=cles(:, 1:i-1) ;
end ;

cles(1,:)=cles(1,:)/get_train_size(dataset) ;
if get_test_size(dataset)>0,
  cles(2,:)=cles(2,:)/get_test_size(dataset) ;
end ;
if get_val_size(dataset)>0,
  cles(3,:)=cles(3,:)/get_val_size(dataset) ;
end ;

cles_nets(1,:)=cles_nets(1,:)/get_train_size(dataset) ;
if get_test_size(dataset)>0,
  cles_nets(2,:)=cles_nets(2,:)/get_test_size(dataset) ;
end ;
if get_val_size(dataset)>0,
  cles_nets(3,:)=cles_nets(3,:)/get_val_size(dataset) ;
end ;
