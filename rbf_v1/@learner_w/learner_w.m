function lrn=learner_w(l)
% Constructor for the learner_w class
%
% lrn=learner_w()
% lrn=learner_w(learner_w)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

lrn.Distr=[] ;
if nargin==0
	lrn=class(lrn, 'learner_w') ;
elseif isa(l, 'learner_w') & (nargin==1),
	lrn=l ;
end ;
