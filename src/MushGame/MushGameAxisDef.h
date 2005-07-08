//%includeGuardStart {
#ifndef MUSHGAMEAXISDEF_H
#define MUSHGAMEAXISDEF_H
//%includeGuardStart } bEIVn8C9ABx91BXeBBNCrA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAxisDef.h
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
//%Header } NprwN+FyryU9/ZcPzxfcPA
/*
 * $Id: MushGameAxisDef.h,v 1.1 2005/07/06 19:08:27 southa Exp $
 * $Log: MushGameAxisDef.h,v $
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameStandard.h"

#include "API/mushGL.h"
#include "API/mushMushGL.h"

//:generate standard ostream xml1
class MushGameAxisDef : public MushcoreVirtualObject
{
public:
    MushGameAxisDef() :
        m_useDevice(false),
        m_useKeys(false),
        m_useBounds(false),
        m_integrate(false),
        m_deviceSensitivity(1),
        m_requiredKey(0),
        m_pos(0),
        m_vel(0),
        m_accel(1),
        m_velLimit(1),
        m_posHasMoved(true),
        m_deviceAccelerate(false)
    {}
    
    void Accelerate(Mushware::tVal inAmount);
    void DeviceAccelerate(Mushware::tVal inAmount);
    void Decelerate(Mushware::tVal inAmount);
    void ApplyIntegration(Mushware::tVal inAmount);
    void PosConstrainAndSet(Mushware::tVal inPos);
    
private:
    // Static configuration
    bool m_useDevice; //:readwrite
    bool m_useKeys; //:readwrite
    bool m_useBounds; //:readwrite
    bool m_integrate; //:readwrite

    Mushware::U32 m_deviceNum; //:readwrite
    Mushware::U32 m_deviceAxisNum; //:readwrite
    Mushware::tVal m_deviceSensitivity; //:readwrite
    Mushware::tVal m_deviceDamping; //:readwrite
    
    GLKeys m_upKey; //:readwrite
    GLKeys m_downKey; //:readwrite
    
    Mushware::U32 m_requiredKey; //:readwrite
    
    Mushware::tVal m_minBound; //:readwrite
    Mushware::tVal m_maxBound; //:readwrite

    std::string m_axisName; //:readwrite
    
    // Dynamic data
    Mushware::tVal m_pos; //:read
    Mushware::tVal m_vel; //:readwrite
    Mushware::tVal m_accel; //:readwrite
    Mushware::tVal m_velLimit; //:readwrite
    bool m_posHasMoved; //:readwrite
    bool m_deviceAccelerate;
    
//%classPrototypes {
public:
    const bool& UseDevice(void) const { return m_useDevice; }
    void UseDeviceSet(const bool& inValue) { m_useDevice=inValue; }
    const bool& UseKeys(void) const { return m_useKeys; }
    void UseKeysSet(const bool& inValue) { m_useKeys=inValue; }
    const bool& UseBounds(void) const { return m_useBounds; }
    void UseBoundsSet(const bool& inValue) { m_useBounds=inValue; }
    const bool& Integrate(void) const { return m_integrate; }
    void IntegrateSet(const bool& inValue) { m_integrate=inValue; }
    const Mushware::U32& DeviceNum(void) const { return m_deviceNum; }
    void DeviceNumSet(const Mushware::U32& inValue) { m_deviceNum=inValue; }
    const Mushware::U32& DeviceAxisNum(void) const { return m_deviceAxisNum; }
    void DeviceAxisNumSet(const Mushware::U32& inValue) { m_deviceAxisNum=inValue; }
    const Mushware::tVal& DeviceSensitivity(void) const { return m_deviceSensitivity; }
    void DeviceSensitivitySet(const Mushware::tVal& inValue) { m_deviceSensitivity=inValue; }
    const Mushware::tVal& DeviceDamping(void) const { return m_deviceDamping; }
    void DeviceDampingSet(const Mushware::tVal& inValue) { m_deviceDamping=inValue; }
    const GLKeys& UpKey(void) const { return m_upKey; }
    void UpKeySet(const GLKeys& inValue) { m_upKey=inValue; }
    const GLKeys& DownKey(void) const { return m_downKey; }
    void DownKeySet(const GLKeys& inValue) { m_downKey=inValue; }
    const Mushware::U32& RequiredKey(void) const { return m_requiredKey; }
    void RequiredKeySet(const Mushware::U32& inValue) { m_requiredKey=inValue; }
    const Mushware::tVal& MinBound(void) const { return m_minBound; }
    void MinBoundSet(const Mushware::tVal& inValue) { m_minBound=inValue; }
    const Mushware::tVal& MaxBound(void) const { return m_maxBound; }
    void MaxBoundSet(const Mushware::tVal& inValue) { m_maxBound=inValue; }
    const std::string& AxisName(void) const { return m_axisName; }
    void AxisNameSet(const std::string& inValue) { m_axisName=inValue; }
    const Mushware::tVal& Pos(void) const { return m_pos; }
    const Mushware::tVal& Vel(void) const { return m_vel; }
    void VelSet(const Mushware::tVal& inValue) { m_vel=inValue; }
    const Mushware::tVal& Accel(void) const { return m_accel; }
    void AccelSet(const Mushware::tVal& inValue) { m_accel=inValue; }
    const Mushware::tVal& VelLimit(void) const { return m_velLimit; }
    void VelLimitSet(const Mushware::tVal& inValue) { m_velLimit=inValue; }
    const bool& PosHasMoved(void) const { return m_posHasMoved; }
    void PosHasMovedSet(const bool& inValue) { m_posHasMoved=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ZoGBtbVdD3Gl8+O+HLw+vw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameAxisDef& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } KHwaU3TYqAoHxH1hu7xbUQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
