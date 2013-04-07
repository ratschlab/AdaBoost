function [params, cen_count, OutDim]=rbfm2p(C, R, w)
% [params, cen_count, OutDim]=rbfm2p(C, R)
% [params, cen_count, OutDim]=rbfm2p(C, R, w)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

%#realonly
%#inbounds

cen_count=size(R,2) ;

if nargin==3
	OutDim=size(w,2) ;
	params=[R' ; reshape(w, [prod(size(w)),1]) ; reshape(C,[prod(size(C)),1])] ;
else
	params=[R' ; reshape(C, [prod(size(C)),1])] ;
end ;
