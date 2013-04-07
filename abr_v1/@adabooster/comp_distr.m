function Distr=comp_distr(bb, delta, out, dataset, Distr, Protocol, It) ;
% Distr=adabooster.comp_distr(bb, delta, out, dataset, Distr, Protocol, It) ;
%

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

M=bb.fin_hyp .* get_train(dataset,2) ;

vw=get_vote_weight(bb,1:It) ;
vws=sum(vw) ;

GG= - M - max(M) ;
Distr=exp(GG) ;

Distr=Distr/sum(Distr) ;











