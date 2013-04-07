function bob=set_boosted_learner(bob, boosted_learner, idx) 
% bob=booster_base.set_boosted_learner(bob, boosted_learner[, idx]) 

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

if nargin==2,
  bob.boosted_learners=boosted_learner ;
elseif nargin==3,
  bob.boosted_learners{idx}=boosted_learner ;
end ;  
