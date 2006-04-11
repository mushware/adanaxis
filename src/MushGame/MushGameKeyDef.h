//%includeGuardStart {
#ifndef MUSHGAMEKEYDEF_H
#define MUSHGAMEKEYDEF_H
//%includeGuardStart } FPnfrK3k0geW7xPq0CuVmQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameKeyDef.h
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
//%Header } peWMqmrFcS8gCDJQFOQtUg
/*
 * $Id: MushGameKeyDef.h,v 1.1 2005/07/11 16:37:46 southa Exp $
 * $Log: MushGameKeyDef.h,v $
 * Revision 1.1  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 */

#include "MushGameStandard.h"

#include "API/mushGL.h"
#include "API/mushMushGL.h"

//:generate standard ostream xml1
class MushGameKeyDef : public MushcoreVirtualObject
{
public:
    MushGameKeyDef();
    virtual ~MushGameKeyDef() {}
    
private:
    Mushware::U32 m_keyValue; //:readwrite
    bool m_state; //:readwrite
    bool m_stateHasChanged; //:readwrite
    std::string m_keyName; //:readwrite
//%classPrototypes {
public:
    const Mushware::U32& KeyValue(void) const { return m_keyValue; }
    void KeyValueSet(const Mushware::U32& inValue) { m_keyValue=inValue; }
    const bool& State(void) const { return m_state; }
    void StateSet(const bool& inValue) { m_state=inValue; }
    const bool& StateHasChanged(void) const { return m_stateHasChanged; }
    void StateHasChangedSet(const bool& inValue) { m_stateHasChanged=inValue; }
    const std::string& KeyName(void) const { return m_keyName; }
    void KeyNameSet(const std::string& inValue) { m_keyName=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 86+5lJLiqv5rpSM6tKnM5Q
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameKeyDef& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } HD31tEMdQd0RKbAawQkhWw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
