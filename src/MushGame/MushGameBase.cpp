//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameBase.cpp
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
//%Header } 72jYu/IZevqg7bsvRKLvxw
/*
 * $Id: MushGameBase.cpp,v 1.7 2006/11/01 13:04:21 southa Exp $
 * $Log: MushGameBase.cpp,v $
 * Revision 1.7  2006/11/01 13:04:21  southa
 * Initial weapon handling
 *
 * Revision 1.6  2006/07/28 11:14:28  southa
 * Records for multiple spaces
 *
 * Revision 1.5  2006/07/12 11:22:42  southa
 * Advanced control menu
 *
 * Revision 1.4  2006/07/08 16:05:59  southa
 * Ruby menus and key handling
 *
 * Revision 1.3  2006/07/07 18:13:58  southa
 * Menu start and stop
 *
 * Revision 1.2  2006/07/04 16:55:27  southa
 * Ruby key handling
 *
 * Revision 1.1  2006/06/30 15:05:34  southa
 * Texture and buffer purge
 *
 */

#include "MushGameBase.h"

#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGameBase);

void
MushGameBase::SwapIn(MushGameAppHandler& inHandler)
{
    
}

void
MushGameBase::SwapOut(MushGameAppHandler& inHandler)
{
    if (MushGLV::Sgl().ContextValid())
    {
        MushGLUtil::Purge();
        MushGLV::Sgl().Purge();
    }
}

bool
MushGameBase::KeyboardSignal(const GLKeyboardSignal& inSignal, MushGameAppHandler& inHandler)
{
    bool keyHandled = false;
    if (LogicRef().Ref().IsMenuMode())
    {
        // Add keypress to the queue
        MushRubyExec::Sgl().Call(VolatileDataRef().Ref().RubyGame(), MushRubyIntern::mKeypress(),
                                 MushRubyValue(inSignal.keyValue),
                                 MushRubyValue(inSignal.keyModifier),
                                 MushRubyValue(inSignal.keyDown));
    }
    else if (inSignal.keyValue == 27 && inSignal.keyDown)
    {
        if (LogicRef().Ref().IsGameMode())
        {
            LogicRef().WRef().MenuModeEnter();
        }
        keyHandled = true;
    }
    return keyHandled;
}

void
MushGameBase::ControlsToDefaultSet(MushGameAppHandler& inHandler)
{
    // Override this
}

const GLModeDef&
MushGameBase::DisplayModeDef(void) const
{
    throw MushcoreLogicFail("DisplayModeDef not overridden");    
}

//%outOfLineFunctions {

const char *MushGameBase::AutoName(void) const
{
    return "MushGameBase";
}

MushcoreVirtualObject *MushGameBase::AutoClone(void) const
{
    return new MushGameBase(*this);
}

MushcoreVirtualObject *MushGameBase::AutoCreate(void) const
{
    return new MushGameBase;
}

MushcoreVirtualObject *MushGameBase::AutoVirtualFactory(void)
{
    return new MushGameBase;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameBase", MushGameBase::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameBase::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "saveDataRef=" << m_saveDataRef << ", ";
    ioOut << "volatileDataRef=" << m_volatileDataRef << ", ";
    ioOut << "clientRef=" << m_clientRef << ", ";
    ioOut << "serverRef=" << m_serverRef << ", ";
    ioOut << "logicRef=" << m_logicRef;
    ioOut << "]";
}
bool
MushGameBase::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "saveDataRef")
    {
        ioIn >> m_saveDataRef;
    }
    else if (inTagStr == "volatileDataRef")
    {
        ioIn >> m_volatileDataRef;
    }
    else if (inTagStr == "clientRef")
    {
        ioIn >> m_clientRef;
    }
    else if (inTagStr == "serverRef")
    {
        ioIn >> m_serverRef;
    }
    else if (inTagStr == "logicRef")
    {
        ioIn >> m_logicRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameBase::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("saveDataRef");
    ioOut << m_saveDataRef;
    ioOut.TagSet("volatileDataRef");
    ioOut << m_volatileDataRef;
    ioOut.TagSet("clientRef");
    ioOut << m_clientRef;
    ioOut.TagSet("serverRef");
    ioOut << m_serverRef;
    ioOut.TagSet("logicRef");
    ioOut << m_logicRef;
}
//%outOfLineFunctions } hwWjLLy9iy8Vpe18UyWrHg
 
