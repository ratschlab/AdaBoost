function rn=rbf_net_w(num_cen, lambda, idim, odim)
% Constructor for the rbf_net_w class
%
% rn=rbf_net_base()
% rn=rbf_net_base(net)
% rn=rbf_net_base(num_cen, lambda, idim, odim)
%
% BASECLASS(ES): learner, learner_w

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

% cg stuff
rn.max_iter = 10 ;
rn.param    = [] ;
rn.ftol     = 1e-8 ;
rn.brent_tol= 1.0e-6 ;
rn.brent_max_iter=100 ;
rn.mnbrak_max_iter=100 ;

if nargin==0
  rn.num_cen=0 ;
  idim=0 ;
  odim=0 ;
  rn.w=[] ;
  rn.R=[] ;
  rn.C=[] ;
  rn.lambda=1e-7 ;
elseif isa(num_cen, 'rbf_net_w') & (nargin==1),
  rn=num_cen ;
  return ;
elseif nargin==4,
  rn.num_cen=num_cen ;
  rn.w=zeros(num_cen, odim) ;
  rn.R=zeros(1, num_cen) ;
  rn.C=zeros(idim, num_cen) ;
  rn.lambda=lambda ;
elseif nargin==3,
  rn.num_cen=num_cen ;
  odim=1 ;
  rn.w=zeros(num_cen, odim) ;
  rn.R=zeros(1, rn.num_cen) ;
  rn.C=zeros(idim, rn.num_cen) ;
  rn.lambda=lambda ;
elseif nargin==2,
  rn.num_cen=num_cen ;
  idim=1 ;
  odim=1 ;
  rn.w=zeros(num_cen, odim) ;
  rn.R=zeros(1, num_cen) ;
  rn.C=zeros(idim, num_cen) ;
  rn.lambda=lambda ;
elseif nargin==1,
  rn.num_cen=num_cen ;
  idim=1 ;
  odim=1 ;
  rn.w=zeros(num_cen, odim) ;
  rn.R=zeros(1, num_cen) ;
  rn.C=zeros(idim, num_cen) ;
  rn.lambda=1e-7 ;
end ;

rn=class(rn, 'rbf_net_w', learner(idim, odim), learner_w) ;
