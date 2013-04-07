function [xmin, fmin, iter]=brent_1d(co, ax,bx,cx, ps, xi)
% [xmin, fmin, iter]=cg_optimizable.brent_1d(co, ax,bx,cx, ps, xi)
%
% brents one-dimensional minimization
% (from Numerical Recipes in C, page 404)
%

%#realonly
%#inbounds

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

xmin=0.0 ;
fmin=0.0 ;

% Constants
CGOLD=0.3819660 ;
ZEPS=1e-8 ;

% a<b
if ax<cx, 
	a=ax; b=cx; 
else 
	a=cx; b=ax; 
end ; 

% Initializations ...
e=0.0 ;
x=bx ; w=bx ; v=bx ;

fw=0.0 ;
fv=0.0 ;
fx=0.0 ;

[fw]=err_func(co, ps+x*xi) ; fv=fw; fx=fw ;

xm=0.0 ;
tol1=0.0 ;
tol2=0.0 ;
d=0.0 ;

for iter=1:co.brent_max_iter,
	xm=0.5*(a+b);
	tol1=co.brent_tol*abs(x)+ZEPS ;
	tol2=2.0*tol1;
	if abs(x-xm) <= tol2-0.5*(b-a),
		xmin=x ;
		fmin=fx ;
		return ;
	end ;

	if abs(e)>tol1,
		r=(x-w)*(fx-fv);
		q=(x-v)*(fx-fw);
		p=(x-v)*q-(x-w)*r;
		q=2.0*(q-r);
		if q>0.0, 
			p = -p; 
		end ;
		q=abs(q);
		etemp=e;
		e=d;
		if (abs(p)>=abs(0.5*q*etemp)) | (p<=q*(a-x)) | (p>=q*(b-x)),
			if x>=xm, 
				e=a-x ; 
			else 
				e=b-x; 
			end ;
			d=CGOLD*e ;
		else 
			d=p/q;
			u=x+d;
			if (u-a<tol2) | (b-u<tol2),
				d=tol1*sign(xm-x);
			end ;
		end ;
	else 
		if e>=xm, 
			e=a-x ; 
		else 
			e=b-x ;
		end ;
		d=CGOLD*e ;
	end ;

	if abs(d) >= tol1, 
		u=x+d ;
	else 
		u=x+tol1*sign(d) ;
	end ; 

	[fu]=err_func(co, ps+u*xi) ;

	if fu<=fx,
		if u>=x, 
			a=x; 
		else 
			b=x; 
		end ;
		v=w; w=x; x=u ;
		fv=fw; fw=fx; fx=fu ;
	else 
		if u<x, 
			a=u; 
		else 
			b=u; 
		end ;

		if (fu<=fw) | (w==x), 
			v=w;
			w=u;
			fv=fw;
			fw=fu;
		else 
			if (fu<=fv) | (v==x) | (v==w), 
				v=u;
				fv=fu;
			end ;
		end ;
	end ;
end ;

xmin=x ;
fmin=fx ;



