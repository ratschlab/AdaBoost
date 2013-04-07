function E=erfunc(delta, P)
% E=erfunc(delta, P)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

vi=P.vi+delta*P.Distr ;
zeta=(vi/sum(vi)).^2 ;

E=sum(exp( (0.5-P.phi)*P.vws ...
           - (P.fin_hyp+delta*P.last_output).* P.labels/2 ...
           - P.lambda*zeta*(P.vws+delta))) ;

