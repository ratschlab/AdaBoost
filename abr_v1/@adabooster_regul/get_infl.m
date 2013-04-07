function infl=get_infl(bb) 
% infl=get_infl(bb) 

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

vw=get_vote_weights(bb) ;
vws=sum(vw) ;
infl=bb.vi/vws ;
