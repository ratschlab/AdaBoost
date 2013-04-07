function rn=set_C(rn, C)
% rn=rbf_net_base.get_C(rn, C)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

rn.C=C ;
if size(C,2)~=get_num_cen(rn)
%  deb_output('num_cen corected.') ;
  rn=set_num_cen(rn, size(C,2)) ;
end ;
if size(C,2)~=get_idim(rn),
%  deb_output('idim corrected') ;
  rn.learner=set_idim(rn.learner, size(C,1)) ;
end ;
