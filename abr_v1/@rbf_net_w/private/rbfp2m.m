function [C,R,w]=rbfp2m(param, cen_count, OutDim)
% [C,R]=rbfp2m(param, cen_count, OutDim)
% [C,R,w]=rbfp2m(param, cen_count, OutDim)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

R=param(1:cen_count)' ;

if nargout==3,
	if nargin<3,
		OutDim=1 ;
		deb_output('rbfp2m: OutDim set to 1') ;
	end ;
	b=0 ;
	InDim=length(param)/cen_count-1-OutDim ;
	if InDim~=ceil(InDim),
		InDim=(length(param)-OutDim*(cen_count+1))/cen_count-1 ;
		if InDim~=ceil(InDim),
			size(OutDim)
			length(param)
			size(InDim)
			error('rbfp2m: format error (1)') ;
		end ;
		b=1 ;
	end ;
	w=param(cen_count+1:(1+OutDim)*(cen_count+b)-b) ;
	size1w=length(w)/OutDim ;
	if ceil(size1w)~=size1w,
		OutDim
		lengthw=length(w)
		size1w
		error('rbfp2m: format error (2)') ;
	end ;
	w=reshape(w, size1w, OutDim) ;
	C=reshape(param((1+OutDim)*(cen_count+b)+1-b:length(param)), [InDim, cen_count]) ;	

else
	InDim=length(param)/cen_count-1 ;
	C=reshape(param(cen_count+1:length(param)),[InDim, cen_count]) ;
end ;

