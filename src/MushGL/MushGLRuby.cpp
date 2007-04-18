//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLRuby.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } LgKmonBzdIr7E9yNc7qvXw
/*
 * $Id: MushGLRuby.cpp,v 1.1 2006/12/11 13:28:24 southa Exp $
 * $Log: MushGLRuby.cpp,v $
 * Revision 1.1  2006/12/11 13:28:24  southa
 * Snapshot
 *
 */

#include "MushGLRuby.h"

#include "MushGLUtil.h"

#include "API/mushMushMeshRuby.h"

MUSHRUBYEMPTYOBJ_INSTANCE(7000);

MUSHRUBY_INSTALL(MushGLRuby);

using namespace Mushware;
using namespace std;

Mushware::tRubyValue
MushGLRuby::ViewExtent(Mushware::tRubyValue inSelf)
{
    tRubyValue retVal = MushMeshRubyVector::NewInstance();
    
    t2Val screenRatios( MushGLUtil::ScreenRatios() );
    MushMeshRubyVector::WRef(retVal) = t4Val(screenRatios.X() / 2, screenRatios.Y() / 2, 0, 0);
    return retVal;
}

void
MushGLRuby::MushGLInstall(void)
{
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cViewExtent", ViewExtent);
}
