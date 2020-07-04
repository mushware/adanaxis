//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisEvents.cpp
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
//%Header } clXvnksj6CT/xwxOeg372g
/*
 * $Id: AdanaxisEvents.cpp,v 1.3 2007/04/18 09:22:00 southa Exp $
 * $Log: AdanaxisEvents.cpp,v $
 * Revision 1.3  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/11/03 18:46:32  southa
 * Damage effectors
 *
 * Revision 1.1  2006/11/02 09:47:33  southa
 * Player weapon control
 *
 */

#include "AdanaxisEvents.h"

#include "AdanaxisIntern.h"

#include "API/mushMushMeshRuby.h"

MUSHCORE_SINGLETON_INSTANCE(AdanaxisEvents);

using namespace Mushware;
using namespace std;

MushRubyValue
AdanaxisEvents::EventFireMake(const MushMeshPosticity& inPost)
{
    MushRubyValue retVal( MushRubyUtil::ClassNewInstance(AdanaxisIntern::Sgl().AdanaxisEventFire()) );
    
    {
        tRubyValue value = MushRubyUtil::InstanceVar(retVal.Value(), MushRubyIntern::ATm_post());
        if (value == kRubyQnil)
        {
            throw MushcoreDataFail("No attribute @m_post in EventFireMake");
        }
        MushMeshRubyPost::WRef(value) = inPost;
    }
    
    return retVal;
}

MushRubyValue
AdanaxisEvents::EventKeyStateMake(void)
{
    MushRubyValue retVal( MushRubyUtil::ClassNewInstance(AdanaxisIntern::Sgl().AdanaxisEventKeyState()) );
    return retVal;
}    

void
AdanaxisEvents::EventKeyStateAddState(MushRubyValue& ioEvent, Mushware::U32 inNum, bool inState)
{
    MushRubyValue keyNum( MushRubyUtil::InstanceVar(ioEvent.Value(), AdanaxisIntern::Sgl().ATm_keyNum()) );
    MushRubyUtil::ArrayPush(keyNum, MushRubyValue(inNum));
    MushRubyValue state( MushRubyUtil::InstanceVar(ioEvent.Value(), AdanaxisIntern::Sgl().ATm_state()) );
    MushRubyUtil::ArrayPush(state, MushRubyValue(inState));
}

//%outOfLineFunctions {

const char *AdanaxisEvents::AutoName(void) const
{
    return "AdanaxisEvents";
}

MushcoreVirtualObject *AdanaxisEvents::AutoClone(void) const
{
    return new AdanaxisEvents(*this);
}

MushcoreVirtualObject *AdanaxisEvents::AutoCreate(void) const
{
    return new AdanaxisEvents;
}

MushcoreVirtualObject *AdanaxisEvents::AutoVirtualFactory(void)
{
    return new AdanaxisEvents;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisEvents", AdanaxisEvents::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisEvents::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
AdanaxisEvents::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisEvents::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } XtjvCuPkXj2ZvlO3AvBPFQ
