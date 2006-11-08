//%includeGuardStart {
#ifndef MUSHGAMEKEYDEF_H
#define MUSHGAMEKEYDEF_H
//%includeGuardStart } FPnfrK3k0geW7xPq0CuVmQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameKeyDef.h
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
//%Header } 0XyESJoYf4vvwzHYpkSADw
/*
 * $Id: MushGameKeyDef.h,v 1.5 2006/11/02 12:23:22 southa Exp $
 * $Log: MushGameKeyDef.h,v $
 * Revision 1.5  2006/11/02 12:23:22  southa
 * Weapon selection
 *
 * Revision 1.4  2006/07/12 11:22:42  southa
 * Advanced control menu
 *
 * Revision 1.3  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2006/04/11 23:30:08  southa
 * Created MushRuby from ruby-1.8.4
 *
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
    
    Mushware::U32 NumKeyValues(void) const { return m_keyValues.size(); }
    void KeyValuesResize(Mushware::U32 inSize) { m_keyValues.resize(inSize); }
    Mushware::U32 KeyValue(Mushware::U32 inIndex) const;
    void KeyValueSet(Mushware::U32 inValue, Mushware::U32 inIndex);
    
    void Reset(void);
    
private:
    std::vector<Mushware::U32> m_keyValues; //:read
    bool m_state; //:readwrite
    bool m_stateHasChanged; //:readwrite
    std::string m_keyName; //:readwrite
    
//%classPrototypes {
public:
    const std::vector<Mushware::U32>& KeyValues(void) const { return m_keyValues; }
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
//%classPrototypes } tTSECx/WwNVIVgkGSZUeFQ
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
