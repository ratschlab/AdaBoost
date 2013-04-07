function [bob, old_boost_steps]=set_boost_steps(bob, new_boost_steps) 
% [bob, old_boost_steps]=booster_base.set_boost_steps(bob, new_boost_steps) 

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

old_boost_steps=bob.boost_steps ;
bob.boost_steps=new_boost_steps ;
