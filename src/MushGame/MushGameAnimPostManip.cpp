//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAnimPostManip.cpp
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
//%Header } sIos+GhHExpN+Ar8I1BZqA
/*
 * $Id: MushGameAnimPostManip.cpp,v 1.6 2006/06/01 15:39:19 southa Exp $
 * $Log: MushGameAnimPostManip.cpp,v $
 * Revision 1.6  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.4  2005/07/14 16:55:08  southa
 * Mesh library work
 *
 * Revision 1.3  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.2  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 */

#include "MushGameAnimPostManip.h"

#include "API/mushMushGL.h"

using namespace Mushware;
using namespace std;

MushGameAnimPostManip::MushGameAnimPostManip() :
    m_posSpeed(0.1),
    m_angSpeed(0.02)
{
        
}

void
MushGameAnimPostManip::PostAdjust(MushMeshPosticity& ioPost)
{
    MushGLAppHandler& appHandler(MushGLUtil::AppHandler());
    
    ioPost.VelWRef().ToAdditiveIdentitySet();
    ioPost.AngVelWRef().ToRotationIdentitySet();
    
    tVal posSpeed = m_posSpeed;
    tVal angSpeed = m_angSpeed;
    
    m_posSpeed = 0.1 + m_posSpeed / 2;
    
    if (appHandler.KeyStateGet('q')) ioPost.VelWRef() -= t4Val(posSpeed,0,0,0);
    if (appHandler.KeyStateGet('a')) ioPost.VelWRef() += t4Val(posSpeed,0,0,0);
    if (appHandler.KeyStateGet('w')) ioPost.VelWRef() -= t4Val(0,posSpeed,0,0);
    if (appHandler.KeyStateGet('s')) ioPost.VelWRef() += t4Val(0,posSpeed,0,0);
    if (appHandler.KeyStateGet('e')) ioPost.VelWRef() -= t4Val(0,0,posSpeed,0);
    if (appHandler.KeyStateGet('d')) ioPost.VelWRef() += t4Val(0,0,posSpeed,0);
    if (appHandler.KeyStateGet('r')) { ioPost.VelWRef() -= t4Val(0,0,0,posSpeed); m_posSpeed += 0.8; }
    if (appHandler.KeyStateGet('f')) { ioPost.VelWRef() += t4Val(0,0,0,posSpeed); m_posSpeed += 0.8; }
    
    ioPost.AngVelWRef().OuterMultiplyBy(ioPost.AngPos().Conjugate());
    if (appHandler.KeyStateGet('t')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(0, -angSpeed));
    if (appHandler.KeyStateGet('g')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(0, +angSpeed));
    if (appHandler.KeyStateGet('y')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(1, -angSpeed));
    if (appHandler.KeyStateGet('h')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(1, +angSpeed));
    if (appHandler.KeyStateGet('u')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(2, -angSpeed));
    if (appHandler.KeyStateGet('j')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(2, +angSpeed));
    if (appHandler.KeyStateGet('i')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(3, -angSpeed));
    if (appHandler.KeyStateGet('k')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(3, +angSpeed));
    if (appHandler.KeyStateGet('o')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(4, -angSpeed));
    if (appHandler.KeyStateGet('l')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(4, +angSpeed));
    if (appHandler.KeyStateGet('p')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(5, -angSpeed));
    if (appHandler.KeyStateGet(';')) ioPost.AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis(5, +angSpeed));
    ioPost.AngVelWRef().OuterMultiplyBy(ioPost.AngPos());

    ioPost.AngPos().VectorRotate(ioPost.VelWRef());
    ioPost.AngPosWRef().InPlaceNormalise();
    ioPost.AngVelWRef().InPlaceNormalise();
}

//%outOfLineFunctions {

const char *MushGameAnimPostManip::AutoName(void) const
{
    return "MushGameAnimPostManip";
}

MushcoreVirtualObject *MushGameAnimPostManip::AutoClone(void) const
{
    return new MushGameAnimPostManip(*this);
}

MushcoreVirtualObject *MushGameAnimPostManip::AutoCreate(void) const
{
    return new MushGameAnimPostManip;
}

MushcoreVirtualObject *MushGameAnimPostManip::AutoVirtualFactory(void)
{
    return new MushGameAnimPostManip;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameAnimPostManip", MushGameAnimPostManip::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameAnimPostManip::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "posSpeed=" << m_posSpeed << ", ";
    ioOut << "angSpeed=" << m_angSpeed;
    ioOut << "]";
}
bool
MushGameAnimPostManip::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "posSpeed")
    {
        ioIn >> m_posSpeed;
    }
    else if (inTagStr == "angSpeed")
    {
        ioIn >> m_angSpeed;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameAnimPostManip::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("posSpeed");
    ioOut << m_posSpeed;
    ioOut.TagSet("angSpeed");
    ioOut << m_angSpeed;
}
//%outOfLineFunctions } 2i0/L0ngk9ZwuIPsoJdCUw
