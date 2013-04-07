function display(bob)
% booster_base.display(bob)

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

display(bob.learner) ;

disp('booster_base object') ;
disp(sprintf(' number of boosting steps: %i', bob.boost_steps)) ;
disp(sprintf(' prototype class: %s', class(bob.proto))) ;
disp(sprintf(' number of parameters to do_learn: %i', bob.num_param)) ;
