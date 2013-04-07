function display(rn)
%

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

display(rn.learner) ;
disp('rbf_net_w object') ;
disp(sprintf('  number of centers: %i', rn.num_cen)) ;
disp(sprintf('  lambda: %1.2e', rn.lambda)) ;
disp(sprintf('  Maximum number of iterations: %i', rn.max_iter)) ;
