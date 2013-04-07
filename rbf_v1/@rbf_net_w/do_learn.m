function rn=do_learn(rn, dataset, do_cluster, dummy)
% rn=rbf_net_lscr_w.do_learn(rn, dataset, do_cluster, dummy)
%
% global RBFNET_CG_TEMP_DATA ;

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

global RBFNET_CG_TEMP_DATA ;

dataset=data_w(dataset) ;
dataset=thresh(dataset) ;

% if do_cluster, then start clustering
if nargin>2,
  if do_cluster,
    rn=cluster(rn, dataset) ;
  end ;
end ;
mk_tempdata(rn) ;

% make a parameter vector
p=rbfm2p(get_C(rn), get_R(rn)) ;

rn=set_distr(rn, get_sampl_weights(dataset)) ;

if get_max_iter(rn)>0,
  % start cg-optimization
  [rn, np, fret, iter]=optimize(rn, p, dataset) ;

  [C, R]=rbfp2m(np, get_num_cen(rn)) ;
  rn=set_C(rn, C) ;
  rn=set_R(rn, R) ;
end ;
% just compute the outweights
[rn]=calc_weights(rn, dataset) ;

mk_tempdata(rn) ;
rn=set_distr(rn, []) ;
