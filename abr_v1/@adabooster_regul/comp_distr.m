function Distr=comp_distr(bb, It, dataset, uDistr, delta) ;
% Distr=adabooster.comp_distr(bb, It, dataset) ;
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

M=bb.adabooster.fin_hyp .* get_train(dataset,2) ;

vw=get_vote_weight(bb,1:It) ;
vws=sum(vw) ;

zeta=(bb.vi/sum(bb.vi)).^2 ;

GG= (0.5-bb.phi)*vws - M/2 - bb.lambda*zeta*vws ;
GG=GG-max(GG) ;
Distr=exp(GG) ;

