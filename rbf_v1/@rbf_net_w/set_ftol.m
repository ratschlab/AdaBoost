function [co, old_ftol]=set_ftol(co, new_ftol) ;
% [co, old_ftol]=cg_optimizable.set_ftol(co, new_ftol) ;
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

old_ftol=co.ftol ;
co.ftol=new_ftol ;