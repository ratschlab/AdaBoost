function [bob, old_proto]=set_proto(bob, new_proto) 
% [bob, old_proto]=booster_base.set_proto(bob, new_proto) 

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

old_proto=bob.proto ;
bob.proto=new_proto ;
