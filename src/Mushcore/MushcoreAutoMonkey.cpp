//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAutoMonkey.cpp
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
//%Header } 4YNheJwZj3RDgh8UebGH3w
/*
 * $Id: MushcoreAutoMonkey.cpp,v 1.9 2006/10/16 14:36:51 southa Exp $
 * $Log: MushcoreAutoMonkey.cpp,v $
 * Revision 1.9  2006/10/16 14:36:51  southa
 * Deco handling
 *
 * Revision 1.8  2006/06/01 15:39:41  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.6  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.5  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:04  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/20 12:23:22  southa
 * Code and interface tidying
 *
 * Revision 1.2  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:59:50  southa
 * More build fixes
 *
 * Revision 1.6  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:12:53  southa
 * Name changed to MushcoreAutoMonkey
 *
 * Revision 1.7  2002/06/27 12:36:01  southa
 * Build process fixes
 *
 * Revision 1.6  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.4  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 * Revision 1.3  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 * Revision 1.2  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.1  2002/02/23 11:43:34  southa
 * Added MushcoreAutoMonkey
 *
 */

#include "MushcoreAutoMonkey.h"

#include "MushcoreFactory.h"
#include "MushcoreFail.h"
#include "MushcoreInstaller.h"
#include "MushcoreSwitches.h"

#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreAutoMonkey::~MushcoreAutoMonkey()
{
    --*m_refCtrPtr;
    MUSHCORE_IFMONKEYTESTING(cerr << "Automonkey destroyed, refcount to " << ReferenceCountGet() << endl);
    if (*m_refCtrPtr == 0)
    {
        delete m_refCtrPtr;
        m_refCtrPtr=NULL;
        MUSHCORE_IFMONKEYTESTING(cerr << "MushcoreAutoMonkey workspace freed" << endl); 
    }
}

MushcoreAutoMonkey::MushcoreAutoMonkey(const MushcoreAutoMonkey& inMonkey) :
    MushcoreVirtualObject()
{
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    ++*m_refCtrPtr;
    MUSHCORE_IFMONKEYTESTING(cerr << "Automonkey copied, refcount to " << ReferenceCountGet() << endl);
}

void
MushcoreAutoMonkey::Swap(MushcoreAutoMonkey& inMonkey)
{
    U32 *temp=m_refCtrPtr;
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    inMonkey.m_refCtrPtr=temp;
}

MushcoreAutoMonkey&
MushcoreAutoMonkey::operator=(const MushcoreAutoMonkey& inMonkey)
{
    MushcoreAutoMonkey temp(inMonkey);
    Swap(temp);
    return *this;
}

bool
MushcoreAutoMonkey::FreeInDestructor(void *inDataPtr) const
{
    if (*m_refCtrPtr < 1) throw(MushcoreLogicFail("MushcoreAutoMonkey fault"));
    MUSHCORE_IFMONKEYTESTING(cerr << "Automonkey InDestructorFree, refcount is " << ReferenceCountGet() << endl);
    return (*m_refCtrPtr == 1  && inDataPtr != NULL);
}

bool
MushcoreAutoMonkey::FreeInDestructor(void) const
{
    if (*m_refCtrPtr < 1) throw(MushcoreLogicFail("MushcoreAutoMonkey fault"));
    MUSHCORE_IFMONKEYTESTING(cerr << "Automonkey InDestructorFree, refcount is " << ReferenceCountGet() << endl);
    return (*m_refCtrPtr == 1);
}

//%outOfLineFunctions {

const char *MushcoreAutoMonkey::AutoName(void) const
{
    return "MushcoreAutoMonkey";
}

MushcoreVirtualObject *MushcoreAutoMonkey::AutoClone(void) const
{
    return new MushcoreAutoMonkey(*this);
}

MushcoreVirtualObject *MushcoreAutoMonkey::AutoCreate(void) const
{
    return new MushcoreAutoMonkey;
}

MushcoreVirtualObject *MushcoreAutoMonkey::AutoVirtualFactory(void)
{
    return new MushcoreAutoMonkey;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushcoreAutoMonkey", MushcoreAutoMonkey::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushcoreAutoMonkey::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    if (m_refCtrPtr == NULL)
    {
        ioOut << "refCtrPtr=NULL" ;
    }
    else
    {
        ioOut << "refCtrPtr=" << *m_refCtrPtr;
    }
    ioOut << "]";
}
bool
MushcoreAutoMonkey::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "refCtrPtr")
    {
        ioIn >> m_refCtrPtr;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushcoreAutoMonkey::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("refCtrPtr");
    ioOut << m_refCtrPtr;
}
//%outOfLineFunctions } S9ru3nQVTKdEmMTITyvLEg
