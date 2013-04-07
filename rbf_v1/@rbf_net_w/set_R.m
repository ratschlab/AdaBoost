function rn=set_R(rn, R)
% rn=rbf_net_base.set_R(rn, R)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

rn.R=R ;

if length(R)~=get_num_cen(rn)
%  deb_output('num_cen corected.') ;
  rn=set_num_cen(rn, length(R)) ;
end ;
