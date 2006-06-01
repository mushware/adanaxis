//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePiece.cpp
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
//%Header } ThyMTpw4iuSxluVCFjz9jQ
/*
 * $Id: MushPiePiece.cpp,v 1.13 2005/07/02 00:42:38 southa Exp $
 * $Log: MushPiePiece.cpp,v $
 * Revision 1.13  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.12  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.11  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.10  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.9  2005/02/10 12:34:13  southa
 * Template fixes
 *
 * Revision 1.8  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.7  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 * Revision 1.6  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.5  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.4  2004/01/04 14:36:37  southa
 * Handle 'inline' in source conditioner
 *
 * Revision 1.3  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.2  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#include "MushPiePiece.h"

using namespace Mushware;

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePiece::tSleepState& outObj)
{
    U32 value;
    ioIn >> value;
    outObj = static_cast<MushPiePiece::tSleepState>(value);
}

//%outOfLineFunctions {

const char *MushPiePiece::AutoName(void) const
{
    return "MushPiePiece";
}

MushcoreVirtualObject *MushPiePiece::AutoClone(void) const
{
    return new MushPiePiece(*this);
}

MushcoreVirtualObject *MushPiePiece::AutoCreate(void) const
{
    return new MushPiePiece;
}

MushcoreVirtualObject *MushPiePiece::AutoVirtualFactory(void)
{
    return new MushPiePiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePiece", MushPiePiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
MushPiePiece::AutoEquals(const MushPiePiece& inObj) const
{
    return 1
        && (m_sleepState == inObj.m_sleepState)
        && (m_formRef == inObj.m_formRef)
    ;
}
void
MushPiePiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "sleepState=" << m_sleepState << ", ";
    ioOut << "formRef=" << m_formRef;
    ioOut << "]";
}
bool
MushPiePiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "sleepState")
    {
        ioIn >> m_sleepState;
    }
    else if (inTagStr == "formRef")
    {
        ioIn >> m_formRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushPiePiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("sleepState");
    ioOut << m_sleepState;
    ioOut.TagSet("formRef");
    ioOut << m_formRef;
}
//%outOfLineFunctions } hZq8x7Ci/G3KAyC1Z5rB/Q
