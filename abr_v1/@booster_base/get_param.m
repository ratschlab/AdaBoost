function [params]=get_param(bb) ;
% [params]=get_param(bb) ;

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

if bb.num_param==0,
  params=cell(0,0) ;
elseif bb.num_param==1 ;
  params{1}=bb.param1 ;
else
  params{1}=bb.param1 ;
  params{2}=bb.param2 ;
end ;
