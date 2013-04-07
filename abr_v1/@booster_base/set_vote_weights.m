function bob=set_vote_weights(bob, vote_weights, idx) 
% bob=booster_base.set_vote_weights(bob, vote_weights[, idx]) 

% Copyright (c) 1998  GMD Berlin - All rights reserved
% THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD Berlin
% The copyright notice above does not evidence any
% actual or intended publication of this work.

if nargin==2,
  bob.vote_weights=vote_weights ;
else
  bob.vote_weights(idx)=vote_weights ;
end ;

