//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRuby.cpp
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
//%Header } yY7ZZkvIHHOoUzJzTAQPOQ
/*
 * $Id: MushGameRuby.cpp,v 1.1 2006/07/07 07:57:29 southa Exp $
 * $Log: MushGameRuby.cpp,v $
 * Revision 1.1  2006/07/07 07:57:29  southa
 * Key translation
 *
 */

#include "MushGameRuby.h"

#include "MushGameAppHandler.h"
#include "MushGameUtil.h"

#include "API/mushMedia.h"

MUSHRUBYEMPTYOBJ_INSTANCE(4000);

MUSHRUBY_INSTALL(MushGameRuby);

using namespace Mushware;
using namespace std;

Mushware::tRubyValue
MushGameRuby::KeySymbolToName(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue keyValue(inArg0);
    return MushRubyValue(MediaKeyboard::KeySymbolToName(keyValue.U32())).Value();
}

Mushware::tRubyValue
MushGameRuby::GameModeEnter(Mushware::tRubyValue inSelf)
{
    MushGameUtil::LogicWRef().GameModeEnter();
    return kRubyQnil;
}

void
MushGameRuby::MethodsInstall(void)
{
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cKeySymbolToName", KeySymbolToName);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cGameModeEnter", GameModeEnter);
}
