//%includeGuardStart {
#ifndef MUSHGAMEAXISDEF_H
#define MUSHGAMEAXISDEF_H
//%includeGuardStart } bEIVn8C9ABx91BXeBBNCrA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameAxisDef.h
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
//%Header } NnTJcSPyQCJazbsDD4KfIg
/*
 * $Id: MushGameAxisDef.h,v 1.7 2006/07/12 11:22:42 southa Exp $
 * $Log: MushGameAxisDef.h,v $
 * Revision 1.7  2006/07/12 11:22:42  southa
 * Advanced control menu
 *
 * Revision 1.6  2006/07/11 19:49:06  southa
 * Control menu
 *
 * Revision 1.5  2006/07/11 12:37:52  southa
 * Control configuration
 *
 * Revision 1.4  2006/07/08 16:05:59  southa
 * Ruby menus and key handling
 *
 * Revision 1.3  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/08 12:07:07  southa
 * MushGaem control work
 *
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
    enum
    {
        kDeviceNone   = 0,
        kDeviceMouse0 = 1,
        kDeviceMouse1 = 2,
        kDeviceStick0 = 3,
        kDeviceStick1 = 4
    };
    
    MushGameAxisDef() :
        m_useBounds(false),
        m_integrate(false),
        m_deviceNum(0),
        m_deviceAxisNum(0),
        m_deviceSensitivity(1),
        m_pos(0),
        m_vel(0),
        m_accel(1),
        m_velLimit(1),
        m_posHasMoved(true),
        m_deviceAccelerate(false)
    {}
    
    Mushware::U32 NumUpKeys(void) const { return m_upKeys.size(); }
    void UpKeysResize(Mushware::U32 inSize) { m_upKeys.resize(inSize); }
    Mushware::U32 UpKey(Mushware::U32 inIndex) const;
    void UpKeySet(Mushware::U32 inValue, Mushware::U32 inIndex);

    Mushware::U32 NumDownKeys(void) const { return m_downKeys.size(); }
    void DownKeysResize(Mushware::U32 inSize) { m_downKeys.resize(inSize); }
    Mushware::U32 DownKey(Mushware::U32 inIndex) const;
    void DownKeySet(Mushware::U32 inValue, Mushware::U32 inIndex);

    Mushware::U32 NumRequiredKeys(void) const { return m_requiredKeys.size(); }
    void RequiredKeysResize(Mushware::U32 inSize) { m_requiredKeys.resize(inSize); }
    Mushware::U32 RequiredKey(Mushware::U32 inIndex) const;
    void RequiredKeySet(Mushware::U32 inValue, Mushware::U32 inIndex);
    
    void Accelerate(Mushware::tVal inAmount);
    void DeviceAccelerate(Mushware::tVal inAmount);
    void DeviceSet(Mushware::tVal inAmount);
            
    void Decelerate(Mushware::tVal inAmount);
    void ApplyIntegration(Mushware::tVal inAmount);
    void PosConstrainAndSet(Mushware::tVal inPos);
    
    void Reset(void);
    
    bool UseDevice(void) const { return m_deviceNum != 0; }
    bool UseKeys(void) const { return m_upKeys.size() != 0 || m_downKeys.size() != 0; }
    
private:
    // Static configuration
    bool m_useBounds; //:readwrite
    bool m_integrate; //:readwrite

    Mushware::U32 m_deviceNum; //:readwrite
    Mushware::U32 m_deviceAxisNum; //:readwrite
    Mushware::tVal m_deviceSensitivity; //:readwrite
    Mushware::tVal m_deviceDamping; //:readwrite
    Mushware::tVal m_velLimit; //:readwrite
    Mushware::tVal m_accel; //:readwrite
    
    std::vector<Mushware::U32> m_upKeys; //:readwrite
    std::vector<Mushware::U32> m_downKeys; //:readwrite
    
    std::vector<Mushware::U32> m_requiredKeys; //:readwrite
    
    Mushware::tVal m_minBound; //:readwrite
    Mushware::tVal m_maxBound; //:readwrite

    std::string m_axisName; //:readwrite
    
    // Dynamic data
    Mushware::tVal m_pos; //:read
    Mushware::tVal m_vel; //:readwrite
    bool m_posHasMoved; //:readwrite
    bool m_deviceAccelerate;
    
//%classPrototypes {
public:
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
    const Mushware::tVal& VelLimit(void) const { return m_velLimit; }
    void VelLimitSet(const Mushware::tVal& inValue) { m_velLimit=inValue; }
    const Mushware::tVal& Accel(void) const { return m_accel; }
    void AccelSet(const Mushware::tVal& inValue) { m_accel=inValue; }
    const std::vector<Mushware::U32>& UpKeys(void) const { return m_upKeys; }
    void UpKeysSet(const std::vector<Mushware::U32>& inValue) { m_upKeys=inValue; }
    const std::vector<Mushware::U32>& DownKeys(void) const { return m_downKeys; }
    void DownKeysSet(const std::vector<Mushware::U32>& inValue) { m_downKeys=inValue; }
    const std::vector<Mushware::U32>& RequiredKeys(void) const { return m_requiredKeys; }
    void RequiredKeysSet(const std::vector<Mushware::U32>& inValue) { m_requiredKeys=inValue; }
    const Mushware::tVal& MinBound(void) const { return m_minBound; }
    void MinBoundSet(const Mushware::tVal& inValue) { m_minBound=inValue; }
    const Mushware::tVal& MaxBound(void) const { return m_maxBound; }
    void MaxBoundSet(const Mushware::tVal& inValue) { m_maxBound=inValue; }
    const std::string& AxisName(void) const { return m_axisName; }
    void AxisNameSet(const std::string& inValue) { m_axisName=inValue; }
    const Mushware::tVal& Pos(void) const { return m_pos; }
    const Mushware::tVal& Vel(void) const { return m_vel; }
    void VelSet(const Mushware::tVal& inValue) { m_vel=inValue; }
    const bool& PosHasMoved(void) const { return m_posHasMoved; }
    void PosHasMovedSet(const bool& inValue) { m_posHasMoved=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } aKdOYzMKittI9MgH1dNPpA
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
