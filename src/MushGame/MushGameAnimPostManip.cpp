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
 * $Id$
 * $Log$
 */

#include "MushGameAnimPostManip.h"

using namespace Mushware;
using namespace std;

void
MushGameAnimPostManip::PostAdjust(MushMeshPosticity& ioPost)
{
    MushGLAppHandler& appHandler(MushGLUtil::AppHandler());
    
    ioPost.VelWRef().ToAdditiveIdentitySet();
    ioPost.AngVelWRef().ToRotationIdentitySet();
    
    tVal posSpeed = 0.1;
    tVal angSpeed = 0.02;
    
    if (appHandler.KeyStateGet('q')) ioPost.VelWRef() -= t4Val(posSpeed,0,0,0);
    if (appHandler.KeyStateGet('a')) ioPost.VelWRef() += t4Val(posSpeed,0,0,0);
    if (appHandler.KeyStateGet('w')) ioPost.VelWRef() -= t4Val(0,posSpeed,0,0);
    if (appHandler.KeyStateGet('s')) ioPost.VelWRef() += t4Val(0,posSpeed,0,0);
    if (appHandler.KeyStateGet('e')) ioPost.VelWRef() -= t4Val(0,0,posSpeed,0);
    if (appHandler.KeyStateGet('d')) ioPost.VelWRef() += t4Val(0,0,posSpeed,0);
    if (appHandler.KeyStateGet('r')) ioPost.VelWRef() -= t4Val(0,0,0,posSpeed);
    if (appHandler.KeyStateGet('f')) ioPost.VelWRef() += t4Val(0,0,0,posSpeed);
    
    ioPost.AngVelWRef().OuterMultiplyBy(ioPost.AngPos().ConjugateGet());
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

    ioPost.AngPos().InPlaceRotate(ioPost.VelWRef());
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
    else 
    {
        return false;
    }
    return true;
}
void
MushGameAnimPostManip::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } S5a28pn8TSdMWitkwrp2Sg
