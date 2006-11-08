//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAxisDef.cpp
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
//%Header } MJLMNaraKdT0cf2Xdn+zyg
/*
 * $Id: MushGameAxisDef.cpp,v 1.7 2006/07/12 11:22:41 southa Exp $
 * $Log: MushGameAxisDef.cpp,v $
 * Revision 1.7  2006/07/12 11:22:41  southa
 * Advanced control menu
 *
 * Revision 1.6  2006/07/11 19:49:05  southa
 * Control menu
 *
 * Revision 1.5  2006/07/11 12:37:52  southa
 * Control configuration
 *
 * Revision 1.4  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/08 12:07:07  southa
 * MushGaem control work
 *
 * Revision 1.2  2005/07/07 16:54:17  southa
 * Control tweaks
 *
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameAxisDef.h"

using namespace Mushware;
using namespace std;

Mushware::U32
MushGameAxisDef::UpKey(Mushware::U32 inIndex) const
{
    MushcoreUtil::DebugBoundsCheck(inIndex, m_upKeys.size());
    return m_upKeys[inIndex];
}

void
MushGameAxisDef::UpKeySet(Mushware::U32 inValue, Mushware::U32 inIndex)
{
    MushcoreUtil::DebugBoundsCheck(inIndex, m_upKeys.size());
    m_upKeys[inIndex] = inValue;
}

Mushware::U32
MushGameAxisDef::DownKey(Mushware::U32 inIndex) const
{
    MushcoreUtil::DebugBoundsCheck(inIndex, m_downKeys.size());
    return m_downKeys[inIndex];
}

void
MushGameAxisDef::DownKeySet(Mushware::U32 inValue, Mushware::U32 inIndex)
{
    MushcoreUtil::DebugBoundsCheck(inIndex, m_downKeys.size());
    m_downKeys[inIndex] = inValue;
}

Mushware::U32
MushGameAxisDef::RequiredKey(Mushware::U32 inIndex) const
{
    MushcoreUtil::DebugBoundsCheck(inIndex, m_requiredKeys.size());
    return m_requiredKeys[inIndex];
}

void
MushGameAxisDef::RequiredKeySet(Mushware::U32 inValue, Mushware::U32 inIndex)
{
    MushcoreUtil::DebugBoundsCheck(inIndex, m_requiredKeys.size());
    m_requiredKeys[inIndex] = inValue;
}

void
MushGameAxisDef::PosConstrainAndSet(Mushware::tVal inPos)
{
    tVal newPos = inPos;

    if (m_useBounds)
    {
        MushcoreUtil::Constrain(newPos, m_minBound, m_maxBound);
    }
    
    if (m_pos != newPos)
    {
        m_posHasMoved = true;
        m_pos = newPos;
    }
}

void
MushGameAxisDef::Accelerate(Mushware::tVal inAmount)
{
    if (m_integrate)
    {
        if (m_vel * inAmount < 0)
        {
            // Acceleration against the direction of movement, so decelerate as well
            Decelerate(fabs(inAmount));
        }
        m_vel += m_accel * inAmount;
        MushcoreUtil::Constrain(m_vel, -m_velLimit, m_velLimit);
    }
    else
    {
        PosConstrainAndSet(m_pos + m_accel * inAmount);
    }
    
    if (inAmount != 0)
    {
        m_deviceAccelerate = false;
    }
}

void
MushGameAxisDef::DeviceAccelerate(Mushware::tVal inAmount)
{
    if (m_integrate)
    {
        m_vel += m_deviceSensitivity * inAmount;
        MushcoreUtil::Constrain(m_vel, -m_velLimit, m_velLimit);
    }
    else
    {
        PosConstrainAndSet(m_pos + m_deviceSensitivity * inAmount);
    }
    
    if (inAmount != 0)
    {
        m_deviceAccelerate = true;
    }
}

void
MushGameAxisDef::DeviceSet(Mushware::tVal inAmount)
{
    m_vel = m_velLimit * inAmount;
}

void
MushGameAxisDef::Decelerate(Mushware::tVal inAmount)
{
    tVal change = m_accel * inAmount;
    
    if (m_deviceAccelerate)
    {
        change *= m_deviceDamping;
    }
        
    if (change > fabs(m_vel))
    {
        m_vel = 0;
    }
    else if (m_vel > 0)
    {
        m_vel -= change;
    }
    else
    {
        m_vel += change;
    }
}

void
MushGameAxisDef::ApplyIntegration(Mushware::tVal inAmount)
{
    PosConstrainAndSet(m_pos + m_vel * inAmount);
}    

void
MushGameAxisDef::Reset(void)
{
    m_pos = 0;
    m_vel = 0;
    m_posHasMoved = true;
    m_deviceAccelerate = false;
}

//%outOfLineFunctions {

const char *MushGameAxisDef::AutoName(void) const
{
    return "MushGameAxisDef";
}

MushcoreVirtualObject *MushGameAxisDef::AutoClone(void) const
{
    return new MushGameAxisDef(*this);
}

MushcoreVirtualObject *MushGameAxisDef::AutoCreate(void) const
{
    return new MushGameAxisDef;
}

MushcoreVirtualObject *MushGameAxisDef::AutoVirtualFactory(void)
{
    return new MushGameAxisDef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameAxisDef", MushGameAxisDef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameAxisDef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "useBounds=" << m_useBounds << ", ";
    ioOut << "integrate=" << m_integrate << ", ";
    ioOut << "deviceNum=" << m_deviceNum << ", ";
    ioOut << "deviceAxisNum=" << m_deviceAxisNum << ", ";
    ioOut << "deviceSensitivity=" << m_deviceSensitivity << ", ";
    ioOut << "deviceDamping=" << m_deviceDamping << ", ";
    ioOut << "velLimit=" << m_velLimit << ", ";
    ioOut << "accel=" << m_accel << ", ";
    ioOut << "upKeys=" << m_upKeys << ", ";
    ioOut << "downKeys=" << m_downKeys << ", ";
    ioOut << "requiredKeys=" << m_requiredKeys << ", ";
    ioOut << "minBound=" << m_minBound << ", ";
    ioOut << "maxBound=" << m_maxBound << ", ";
    ioOut << "axisName=" << m_axisName << ", ";
    ioOut << "pos=" << m_pos << ", ";
    ioOut << "vel=" << m_vel << ", ";
    ioOut << "posHasMoved=" << m_posHasMoved << ", ";
    ioOut << "deviceAccelerate=" << m_deviceAccelerate;
    ioOut << "]";
}
bool
MushGameAxisDef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "useBounds")
    {
        ioIn >> m_useBounds;
    }
    else if (inTagStr == "integrate")
    {
        ioIn >> m_integrate;
    }
    else if (inTagStr == "deviceNum")
    {
        ioIn >> m_deviceNum;
    }
    else if (inTagStr == "deviceAxisNum")
    {
        ioIn >> m_deviceAxisNum;
    }
    else if (inTagStr == "deviceSensitivity")
    {
        ioIn >> m_deviceSensitivity;
    }
    else if (inTagStr == "deviceDamping")
    {
        ioIn >> m_deviceDamping;
    }
    else if (inTagStr == "velLimit")
    {
        ioIn >> m_velLimit;
    }
    else if (inTagStr == "accel")
    {
        ioIn >> m_accel;
    }
    else if (inTagStr == "upKeys")
    {
        ioIn >> m_upKeys;
    }
    else if (inTagStr == "downKeys")
    {
        ioIn >> m_downKeys;
    }
    else if (inTagStr == "requiredKeys")
    {
        ioIn >> m_requiredKeys;
    }
    else if (inTagStr == "minBound")
    {
        ioIn >> m_minBound;
    }
    else if (inTagStr == "maxBound")
    {
        ioIn >> m_maxBound;
    }
    else if (inTagStr == "axisName")
    {
        ioIn >> m_axisName;
    }
    else if (inTagStr == "pos")
    {
        ioIn >> m_pos;
    }
    else if (inTagStr == "vel")
    {
        ioIn >> m_vel;
    }
    else if (inTagStr == "posHasMoved")
    {
        ioIn >> m_posHasMoved;
    }
    else if (inTagStr == "deviceAccelerate")
    {
        ioIn >> m_deviceAccelerate;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGameAxisDef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("useBounds");
    ioOut << m_useBounds;
    ioOut.TagSet("integrate");
    ioOut << m_integrate;
    ioOut.TagSet("deviceNum");
    ioOut << m_deviceNum;
    ioOut.TagSet("deviceAxisNum");
    ioOut << m_deviceAxisNum;
    ioOut.TagSet("deviceSensitivity");
    ioOut << m_deviceSensitivity;
    ioOut.TagSet("deviceDamping");
    ioOut << m_deviceDamping;
    ioOut.TagSet("velLimit");
    ioOut << m_velLimit;
    ioOut.TagSet("accel");
    ioOut << m_accel;
    ioOut.TagSet("upKeys");
    ioOut << m_upKeys;
    ioOut.TagSet("downKeys");
    ioOut << m_downKeys;
    ioOut.TagSet("requiredKeys");
    ioOut << m_requiredKeys;
    ioOut.TagSet("minBound");
    ioOut << m_minBound;
    ioOut.TagSet("maxBound");
    ioOut << m_maxBound;
    ioOut.TagSet("axisName");
    ioOut << m_axisName;
    ioOut.TagSet("pos");
    ioOut << m_pos;
    ioOut.TagSet("vel");
    ioOut << m_vel;
    ioOut.TagSet("posHasMoved");
    ioOut << m_posHasMoved;
    ioOut.TagSet("deviceAccelerate");
    ioOut << m_deviceAccelerate;
}
//%outOfLineFunctions } Ot1uiEK/rxgrsaE/ac/Rpw
