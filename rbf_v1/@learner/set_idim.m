function [lrn,old_idim]=set_idim(lrn, new_idim)
% [lrn, old_idim]=learner.set_idim(lrn, new_idim)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

old_idim=lrn.idim ;
lrn.idim=new_idim ;
