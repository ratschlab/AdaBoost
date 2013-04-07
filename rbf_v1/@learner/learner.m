function lrn=learner(idim, odim)
% Constructor for the learner class
%
% lrn=learner()
% lrn=learner(learner)
% lrn=learner(idim, odim)

%   G. Raetsch 1.6.98
%   Copyright (c) 1998  GMD Berlin - All rights reserved
%   THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE of GMD FIRST Berlin
%   The copyright notice above does not evidence any
%   actual or intended publication of this work.

if nargin==0
	lrn.idim=1 ;
	%deb_output(sprintf('lrn.idim was set to %i', lrn.idim)) ;
	lrn.odim=1 ;
	%deb_output(sprintf('lrn.odim was set to %i', lrn.odim)) ;
	lrn=class(lrn, 'learner') ;
elseif isa(idim, 'learner') & (nargin==1),
	lrn=idim ;
elseif nargin==2,
	lrn.idim=idim ;
	lrn.odim=odim ;
	lrn=class(lrn, 'learner') ;
elseif nargin==1,
	lrn.idim=idim ;
	lrn.odim=1 ;
	deb_output(sprintf('lrn.odim was set to %i', lrn.odim)) ;
	lrn=class(lrn, 'learner') ;
end ;
