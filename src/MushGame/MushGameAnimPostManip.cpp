//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAnimPostManip.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } slrkoNIBI9nz7vtTH5Yo6g
/*
 * $Id: MushGameAnimPostManip.cpp,v 1.4 2005/07/14 16:55:08 southa Exp $
 * $Log: MushGameAnimPostManip.cpp,v $
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
