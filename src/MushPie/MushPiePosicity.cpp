//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosicity.cpp
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
//%Header } P1Dww4FiAS1JPyDYIL9OYQ
/*
 * $Id: MushPiePosicity.cpp,v 1.9 2006/06/01 15:39:37 southa Exp $
 * $Log: MushPiePosicity.cpp,v $
 * Revision 1.9  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.7  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/06/16 17:25:40  southa
 * Client/server work
 *
 * Revision 1.5  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/25 19:13:50  southa
 * GameDialogue work
 *
 * Revision 1.3  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPiePosicity.h"

using namespace Mushware;

//%outOfLineFunctions {

const char *MushPiePosicity::AutoName(void) const
{
    return "MushPiePosicity";
}

MushcoreVirtualObject *MushPiePosicity::AutoClone(void) const
{
    return new MushPiePosicity(*this);
}

MushcoreVirtualObject *MushPiePosicity::AutoCreate(void) const
{
    return new MushPiePosicity;
}

MushcoreVirtualObject *MushPiePosicity::AutoVirtualFactory(void)
{
    return new MushPiePosicity;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushPiePosicity", MushPiePosicity::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
MushPiePosicity::AutoEquals(const MushPiePosicity& inObj) const
{
    return 1
        && (m_angPos == inObj.m_angPos)
        && (m_angVel == inObj.m_angVel)
        && (m_pos == inObj.m_pos)
        && (m_vel == inObj.m_vel)
    ;
}
void
MushPiePosicity::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "angPos=" << m_angPos << ", ";
    ioOut << "angVel=" << m_angVel << ", ";
    ioOut << "pos=" << m_pos << ", ";
    ioOut << "vel=" << m_vel;
    ioOut << "]";
}
bool
MushPiePosicity::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "angPos")
    {
        ioIn >> m_angPos;
    }
    else if (inTagStr == "angVel")
    {
        ioIn >> m_angVel;
    }
    else if (inTagStr == "pos")
    {
        ioIn >> m_pos;
    }
    else if (inTagStr == "vel")
    {
        ioIn >> m_vel;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushPiePosicity::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("angPos");
    ioOut << m_angPos;
    ioOut.TagSet("angVel");
    ioOut << m_angVel;
    ioOut.TagSet("pos");
    ioOut << m_pos;
    ioOut.TagSet("vel");
    ioOut << m_vel;
}
//%outOfLineFunctions } idsK+Gclj+9CkS88anChQQ
