//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileRuby.cpp
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
//%Header } eDanUv+oK5eOEEiPwWQ+Pg
/*
 * $Id$
 * $Log$
 */

#include "MushFileRuby.h"

#include "MushFileLibrary.h"

MUSHRUBYEMPTYOBJ_INSTANCE(6000);

MUSHRUBY_INSTALL(MushFileRuby);

using namespace Mushware;
using namespace std;

Mushware::tRubyValue
MushFileRuby::LibraryAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue param0(inArg0);
    
    MushFileLibrary::Sgl().LibraryAdd(param0.String());
    
    return kRubyQnil;
}    

Mushware::tRubyValue
MushFileRuby::LibraryDump(Mushware::tRubyValue inSelf)
{
    MushcoreXMLOStream xmlOut(std::cout);
    xmlOut << MushFileLibrary::Sgl();
    
    return kRubyQnil;
}    

void
MushFileRuby::MushFileInstall(void)
{
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cLibraryAdd", LibraryAdd);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cLibraryDump", LibraryDump);
}
