function boosted_learner=get_boosted_learner(bob, idx) 
% boosted_learner=booster_base.get_boosted_learner(bob[, idx]) 

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

if nargin==1,
  boosted_learner=bob.boosted_learners ;
elseif nargin==2,
  boosted_learner=bob.boosted_learners{idx} ;
end ;
