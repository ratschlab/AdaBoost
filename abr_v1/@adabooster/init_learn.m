function [bb, Protocol]=init_learn(bb, dataset)
% [bb, Protocol]=init_learn(bb, dataset)
%
% performs some initializations before learning

%   G. Raetsch 10.12.99
%   Copyright (c) 1998,1999  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.
%   Please see COPYRIGHT.txt for details.

Protocol=[] ;
bb=set_boosted_learner(bb, cell(1,get_boost_steps(bb))) ;
bb=set_vote_weights(bb, zeros(1,get_boost_steps(bb))) ;
bb.fin_hyp = 0 ;

