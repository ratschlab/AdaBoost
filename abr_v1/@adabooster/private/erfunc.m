function E=erfunc(delta, P)
% E=erfunc(delta, P)

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

E=sum(exp( -(P.fin_hyp+delta*P.last_output).* P.labels )) ;
       

