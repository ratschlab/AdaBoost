function MSE=mse(Out, DestOut) 
% MSE=mse(Out, DestOut) 
% 
% Computes the mean-squared-error
%   Please see COPYRIGHT.txt for details.

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

%#realonly
%#inbounds

[dim,p]=size(DestOut) ;
MSE=sum(sum((Out-DestOut).^2))/p ;
