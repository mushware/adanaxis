//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAxisDef.cpp
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
//%Header } 2CFncbRjYIdlO9JtmJIUgg
/*
 * $Id$
 * $Log$
 */

#include "MushGameAxisDef.h"

using namespace Mushware;
using namespace std;

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
        m_vel += m_accel * inAmount;
        MushcoreUtil::Constrain(m_vel, -m_velLimit, m_velLimit);
    }
    else
    {
        PosConstrainAndSet(m_pos + m_accel * inAmount);
    }
}

void
MushGameAxisDef::Decelerate(Mushware::tVal inAmount)
{
    tVal change = m_accel * inAmount;
    
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
    ioOut << "useDevice=" << m_useDevice << ", ";
    ioOut << "useKeys=" << m_useKeys << ", ";
    ioOut << "useBounds=" << m_useBounds << ", ";
    ioOut << "integrate=" << m_integrate << ", ";
    ioOut << "deviceNum=" << m_deviceNum << ", ";
    ioOut << "deviceAxisNum=" << m_deviceAxisNum << ", ";
    ioOut << "upKey=" << m_upKey << ", ";
    ioOut << "downKey=" << m_downKey << ", ";
    ioOut << "upKeyTime=" << m_upKeyTime << ", ";
    ioOut << "downKeyTime=" << m_downKeyTime << ", ";
    ioOut << "requiredKeys=" << m_requiredKeys << ", ";
    ioOut << "disallowedKeys=" << m_disallowedKeys << ", ";
    ioOut << "minBound=" << m_minBound << ", ";
    ioOut << "maxBound=" << m_maxBound << ", ";
    ioOut << "axisName=" << m_axisName << ", ";
    ioOut << "pos=" << m_pos << ", ";
    ioOut << "vel=" << m_vel << ", ";
    ioOut << "accel=" << m_accel << ", ";
    ioOut << "velLimit=" << m_velLimit << ", ";
    ioOut << "posHasMoved=" << m_posHasMoved;
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
    else if (inTagStr == "useDevice")
    {
        ioIn >> m_useDevice;
    }
    else if (inTagStr == "useKeys")
    {
        ioIn >> m_useKeys;
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
    else if (inTagStr == "upKey")
    {
        ioIn >> m_upKey;
    }
    else if (inTagStr == "downKey")
    {
        ioIn >> m_downKey;
    }
    else if (inTagStr == "upKeyTime")
    {
        ioIn >> m_upKeyTime;
    }
    else if (inTagStr == "downKeyTime")
    {
        ioIn >> m_downKeyTime;
    }
    else if (inTagStr == "requiredKeys")
    {
        ioIn >> m_requiredKeys;
    }
    else if (inTagStr == "disallowedKeys")
    {
        ioIn >> m_disallowedKeys;
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
    else if (inTagStr == "accel")
    {
        ioIn >> m_accel;
    }
    else if (inTagStr == "velLimit")
    {
        ioIn >> m_velLimit;
    }
    else if (inTagStr == "posHasMoved")
    {
        ioIn >> m_posHasMoved;
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
    ioOut.TagSet("useDevice");
    ioOut << m_useDevice;
    ioOut.TagSet("useKeys");
    ioOut << m_useKeys;
    ioOut.TagSet("useBounds");
    ioOut << m_useBounds;
    ioOut.TagSet("integrate");
    ioOut << m_integrate;
    ioOut.TagSet("deviceNum");
    ioOut << m_deviceNum;
    ioOut.TagSet("deviceAxisNum");
    ioOut << m_deviceAxisNum;
    ioOut.TagSet("upKey");
    ioOut << m_upKey;
    ioOut.TagSet("downKey");
    ioOut << m_downKey;
    ioOut.TagSet("upKeyTime");
    ioOut << m_upKeyTime;
    ioOut.TagSet("downKeyTime");
    ioOut << m_downKeyTime;
    ioOut.TagSet("requiredKeys");
    ioOut << m_requiredKeys;
    ioOut.TagSet("disallowedKeys");
    ioOut << m_disallowedKeys;
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
    ioOut.TagSet("accel");
    ioOut << m_accel;
    ioOut.TagSet("velLimit");
    ioOut << m_velLimit;
    ioOut.TagSet("posHasMoved");
    ioOut << m_posHasMoved;
}
//%outOfLineFunctions } 7VIyx05fxBpyG6QD+Jl62Q
