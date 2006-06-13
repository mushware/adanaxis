//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshRuby/MushMeshRubyExtrusion.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /kiEURAeyvrOK+Fzi1sNTg
/*
 * $Id$
 * $Log$
 */

#include "MushMeshRubyExtrusion.h"

#include "MushMeshRubyRuby.h"

using namespace Mushware;
using namespace std;

MUSHRUBYOBJ_INSTANCE(MushMeshLibraryExtrusionContext);

MUSHRUBYOBJ_INITIALIZE(MushMeshLibraryExtrusionContext)(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	return inSelf;
}

void
MushMeshRubyExtrusion::RubyInstall(void)
{
	ObjInstall("MushExtrusion");
}

MUSHRUBY_INSTALL(MushMeshRubyExtrusion);
