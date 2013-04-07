function bb=finish_learn(bb)
% bb=finish_learn(bb)
%
% clear some variables

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

w=get_vote_weights(bb) ;
THRESH=1e-8;

if sum(w<=THRESH)>0
  fprintf(1,sprintf('\nremoving %i useless hypothesis\n',sum(w<=THRESH))) ;
  wls=get_boosted_learner(bb) ;
  wls_new=cell(1,get_boost_steps(bb));
  w_new=zeros(1,get_boost_steps(bb)) ;
  j=0 ;
  for i=1:length(w),
    if w(i)>THRESH,
      j=j+1 ;
      wls_new{j}=wls{i} ;
      w_new(j)=w(i) ;
    end ;
  end ;
  fprintf(1,sprintf('holding now %i usefull hypothesis\n',j)) ;
  bb=set_boosted_learner(bb, wls_new) ;
  bb=set_vote_weights(bb, w_new) ;
end ;
  
bb.last_output=[] ;
bb.fin_hyp=0 ;

