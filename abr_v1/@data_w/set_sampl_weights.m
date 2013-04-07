function [daw,old_sampl_weights]=set_sampl_weights(daw, new_sampl_weights)
% [daw, old_sampl_weights]=data_w.set_sampl_weights(daw, new_sampl_weights)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

old_sampl_weights=daw.sampl_weights ;
daw.sampl_weights=new_sampl_weights ;
