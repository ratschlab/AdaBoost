function MSE=mse_distr(Out, DestOut, Distr) 
% MSE=mse_distr(Out, DestOut, Distr) 
% 
% Computes the mean-squared-error

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

%#realonly
%#inbounds

s=sum(Distr) ;
if abs(s-1)>10*eps,
	Distr=Distr/s ;
end ;

[dim,p]=size(DestOut) ;
if dim>1,
	MSE=sum( sum((Out-DestOut).^2) .* Distr ) ;
else
	MSE=sum( ((Out-DestOut).^2) .* Distr )  ;
end ;
