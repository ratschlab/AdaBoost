function Protocol=report(bb, idx, EpsT, Distr, dataset, Protocol, flag)
% Protocol=adabooster.report(bb, idx, EpsT, Distr, dataset, Protocol, flag)

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

if nargin<7,
  flag=0 ;
end ;

if 1,
  tce=mean(bb.fin_hyp.*get_train(dataset,2)<=0) ;
  vw=get_vote_weight(bb,1:idx) ;
  vws=sum(vw) ;
  report=sprintf('It:%i   TCE:%1.2e   vws:%1.2e', idx, tce, vws) ;
  disp(report) ;
else
  fprintf(1,'.') ;
end ;

Protocol=[] ;


