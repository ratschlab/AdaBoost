function [bb,ok]=do_learn(bb, dataset)
% bb=adabooster.do_learn(bb, dataset)
%
% global Protocol Distr Booster

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

global Protocol Distr Booster;

% number of tries to find a good enough base hypothesis
MAXWEAKFAILTRYS=20 ;

% store the sizes
p=get_train_size(dataset) ;

omax=max(get_train(dataset,2)) ;
omin=min(get_train(dataset,2)) ;
if (omax~=1) | (omin~=-1), 
  error(sprintf('class labels not ok (omax:%i, omin:%i)', omax, omin)) ; 
end ;

% Initialize
Distr=ones(1,p)/p ;
bb=set_last_distr(bb, Distr) ;
It=0 ;
dataset_t=data_w(reduce(dataset, get_train_size(dataset),0,0)) ;

[bb, Protocol]=init_learn(bb, dataset) ;

while 1,
  % count the iterations
  It=It+1 ;
  
  if get_boost_steps(bb)~=0 & It>get_boost_steps(bb),
    break ;
  end ;
  
  % save the weights to the dataset
  dataset_t=set_sampl_weights(dataset_t, Distr) ;
  TIt=0 ; ok=0;
  while (~ok) & (TIt<MAXWEAKFAILTRYS),
    TIt=TIt+1 ;
    
    % start the weak learner
    if isa(get_proto(bb), 'learner_w')==0,
      boot_set = bootstrap(dataset_t) ;
      wl=train_weak(bb, boot_set);
    else
      wl=train_weak(bb, dataset_t);
    end ;
    
    out=calc_output(wl, get_train(dataset_t,1)) ;

    % store the computed learner
    bb=set_boosted_learner(bb, wl, It) ;
  
    % compute the vote weight and store it for later computations of the final 
    % hypothesis
    [bb, delta, ok]=comp_weight(bb, It, out, dataset, Distr) ;
    if ~ok, fprintf(1,'*') ; end ;
  end ;
  
  % check weak learner success
  if TIt>=MAXWEAKFAILTRYS,
    delta
    Protocol=report(bb, It, delta, Distr, dataset, Protocol, 1) ;
    break ;
  end ;
    
  bb=set_vote_weights(bb, delta, It) ;

  % write Protocol 
  Protocol=report(bb, It, delta, Distr, dataset, Protocol) ;
  Booster=bb ;
  
  % compute new distribution ... 
  Distr=comp_distr(bb, delta, out, dataset, Distr, Protocol, It) ;

  % ... and it can be usefull if we save it ... 
  bb=set_last_distr(bb, Distr) ;
end ;    

bb=finish_learn(bb) ;
