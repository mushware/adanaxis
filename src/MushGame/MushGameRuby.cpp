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
 * $Id: MushGameRuby.cpp,v 1.3 2006/07/08 16:05:59 southa Exp $
 * $Log: MushGameRuby.cpp,v $
 * Revision 1.3  2006/07/08 16:05:59  southa
 * Ruby menus and key handling
 *
 * Revision 1.2  2006/07/07 18:13:59  southa
 * Menu start and stop
 *
 * Revision 1.1  2006/07/07 07:57:29  southa
 * Key translation
 *
 */

#include "MushGameRuby.h"

#include "MushGameAppHandler.h"
#include "MushGameAxisDef.h"
#include "MushGameKeyDef.h"
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

Mushware::tRubyValue
MushGameRuby::Quit(Mushware::tRubyValue inSelf)
{
    MushGameUtil::LogicWRef().QuitModeEnter();
    return kRubyQnil;
}

Mushware::tRubyValue
MushGameRuby::AxisKeySymbol(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue axisID(inArg0);
    
    U32 axisNum = axisID.U32() / 4;
    U32 subType = axisID.U32() % 4;
    
    const MushGameAxisDef& axisRef = MushGameUtil::AppHandler().AxisDef(axisNum);
    
    U32 symbolValue = 0;
    switch (subType)
    {
        case 0:
        {
            symbolValue = axisRef.DownKey();
        }
        break;
            
        case 1:
        {
            symbolValue = axisRef.UpKey();
        }
        break;
        
        case 2:
        {
            symbolValue = axisRef.RequiredKey();
        }
        break;
            
        default:
        {
            ostringstream message;
            message << "Bad axis symbol number " << axisID.U32();
            MushRubyUtil::Raise(message.str());
        }
        break;
    }    

    return MushRubyValue(symbolValue).Value();
}

void
MushGameRuby::MethodsInstall(void)
{
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cKeySymbolToName", KeySymbolToName);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cGameModeEnter", GameModeEnter);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cQuit", Quit);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cAxisKeySymbol", AxisKeySymbol);
}
