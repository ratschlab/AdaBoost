function [co, p, fret, its]=optimize(co, p, param)
% [co, p, fret, iter]=cg_optimizable.optimize(co, p)
%
% The Fletcher-Reeves-Polak-Ribiere-Conjugate Gradient Algorithm
% 	(from Numerical Recipes in C, page 422)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

%#realonly
%#inbounds 

% set parameter
co.param=param ;

[fp]=err_func(co, p) ;
[xi]=grad_func(co, p) ;
EPS=1.0e-8 ;

g=-xi ;
h=g ;
xi=h ;

if nargin<5,
	P=[] ;
end ;	

fret=fp ;
its=0 ;
hist=[] ;
for its=1:co.max_iter,
	[p,xi,fret]=linmin(co, p, xi); 
	
	if 2.0*abs(fret-fp)<= co.ftol*(abs(fret)+abs(fp)+EPS)
		co.param=[] ;		
		return;
	end ;
		
	[fp]=err_func(co, p);
	[xi]=grad_func(co, p) ;

	gg=g'*g ;

	dgg=(xi+g)'*xi ;

	if gg == 0.0, 
		return ; 
	end ;
	gam=dgg/gg;
	
	g=-xi ;
	h=g+gam*h ;
	xi=h ;
end ;

co.param=[] ;

