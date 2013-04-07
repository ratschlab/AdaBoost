function [pmin, xi, fret, temp_data]=linmin(co, p, xi)
% [pmin, xi, fret]=cg_optimizable.linmin(co, p, xi) 
%
% Line Minimization 
% 	(from Numerial Recipes in C, page 418)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

%#realonly
%#inbounds

ax=0.0;
xx=1.0;
bx=10.0 ;

[ax, xx, bx]=mnbrak(co, ax, xx, bx, p, xi) ;
[xmin, fret]=brent(co, ax, xx, bx, p, xi);
	
xi=xmin*xi ;
pmin=p+xi ;	
