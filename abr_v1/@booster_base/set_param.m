function [bob, old_param]=set_param(bob, index, new_param) 
% [bob, old_param]=booster_base.set_param(bob, index, new_param)

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

if index==1,
  old_param1=bob.param1 ;
  bob.param1=new_param ;
elseif index==2,
  old_param2=bob.param2 ;
  bob.param2=new_param ;
end ;  
