//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameBase.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } vT7mcksRZ1cMS0uENGSqEQ
/*
 * $Id: MushGameBase.cpp,v 1.11 2007/03/08 11:00:29 southa Exp $
 * $Log: MushGameBase.cpp,v $
 * Revision 1.11  2007/03/08 11:00:29  southa
 * Level epilogue
 *
 * Revision 1.10  2007/03/07 16:59:44  southa
 * Khazi spawning and level ends
 *
 * Revision 1.9  2006/12/14 15:59:24  southa
 * Fire and cutscene fixes
 *
 * Revision 1.8  2006/11/25 21:26:33  southa
 * Display mode definitions
 *
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

#include "MushGameIntern.h"

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
        MushGLUtil::PurgeNonResident();
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
    else if (inSignal.keyValue == MediaKeyboard::kKey_ESCAPE && inSignal.keyDown)
    {
        if (!LogicRef().Ref().IsMenuMode())
        {
            LogicRef().WRef().MenuModeEnter();
        }
        keyHandled = true;
    }
    else if (LogicRef().Ref().IsCutSceneMode())
    {
        MushRubyExec::Sgl().Call(VolatileDataRef().Ref().RubyGame(), MushGameIntern::Sgl().mCutSceneKeypress(),
                                 MushRubyValue(inSignal.keyValue),
                                 MushRubyValue(inSignal.keyModifier),
                                 MushRubyValue(inSignal.keyDown));
    }
    else if (LogicRef().Ref().IsEpilogueMode())
    {
        MushRubyExec::Sgl().Call(VolatileDataRef().Ref().RubyGame(), MushGameIntern::Sgl().mEpilogueKeypress(),
                                 MushRubyValue(inSignal.keyValue),
                                 MushRubyValue(inSignal.keyModifier),
                                 MushRubyValue(inSignal.keyDown));
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
 
