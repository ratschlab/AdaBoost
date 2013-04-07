function [ax, bx, cx, fa, fb, fc]=mnbrak(co, ax,bx,cx,x,xi) 
% [ax, bx, cx, fa, fb, fc]=cg_optimizable.mnbrak(co, ax,bx,cx,x,xi) 
% 
% brakets a minimum
%	(see Numerical Recipes for C, page 400)
%
% adapeted to ,,one-direction'' xi from a starting point x
% 

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

%#realonly
%#inbounds

% Constants
GOLD=1.618034 ;
GLIMIT=1000.0 ;
TINY=1.0e-8 ;

[fa]=err_func(co, x+ax*xi) ;
[fb]=err_func(co, x+bx*xi) ;

if fb>fa,
	dum=ax ; ax=bx ; bx=dum ;
	dum=fb ; fb=fa ; fa=dum ;
end ;

cx=bx+GOLD*(bx-ax) ;

[fc]=err_func(co, x+cx*xi) ;

iter=0 ;
while fb>fc
	iter=iter+1 ;
	if iter>co.mnbrak_max_iter, 
		warning(sprintf('to many iterations in mnbrak (set to %i)', co.mnbrak_max_iter)) ; 
	end ;
	r=(bx-ax)*(fb-fc);
	q=(bx-cx)*(fb-fa);
	u=(bx)-((bx-cx)*q-(bx-ax)*r)/(2.0*max([abs(q-r),TINY])*sign(q-r));
	ulim=(bx)+GLIMIT*(cx-bx);
	if (bx-u)*(u-cx)>0.0,
		[fu]=err_func(co, x+u*xi) ;
		if (fu < fc) 
			ax=bx;
			bx=u;
			fa=fb;
			fb=fu;
			return;
		elseif (fu> fb) 
			cx=u;
			fc=fu;
			return;
		end
		u=cx+GOLD*(cx-bx);
		[fu]=err_func(co, x+u*xi);
	elseif (cx-u)*(u-ulim)>0.0,
		[fu]=err_func(co, x+u*xi) ;
		if fu<fc,
			bx=cx ; cx=u ; u=cx+GOLD*(cx-bx) ;
			fb=fc ; fc=fu ; [fu]=err_func(co, x+u*xi) ;
		end
	elseif (u-ulim)*(ulim-cx)>=0.0 
		u=ulim;
		[fu]=err_func(co, x+u*xi) ;
	else
		u=(cx)+GOLD*(cx-bx);
		[fu]=err_func(co, x+u*xi) ;	
	end ;

	ax=bx ; bx=cx ; cx=u ;
	fa=fb ; fb=fc ; fc=fu ;
end
