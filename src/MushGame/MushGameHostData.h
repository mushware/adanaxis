//%includeGuardStart {
#ifndef MUSHGAMEHOSTDATA_H
#define MUSHGAMEHOSTDATA_H
//%includeGuardStart } 5c+vKr5P06k1yJwzw7n0Xw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostData.h
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
//%Header } pCUk/HFm4O1zWaBur4XPQg
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameHostSaveData.h"
#include "MushGameHostVolatileData.h"

//:generate virtual standard ostream xml1
class MushGameHostData : public MushcoreVirtualObject
{
public:
    MushGameHostData(const std::string& inName="");
    virtual ~MushGameHostData() {}
    virtual void GroupingNameSet(const std::string& inName) { m_saveDataRef.NameSet(inName); m_volatileDataRef.NameSet(inName); }
private:
    MushcoreDataRef<MushGameHostSaveData> m_saveDataRef; //:readwrite :wref
    MushcoreDataRef<MushGameHostVolatileData> m_volatileDataRef; //:readwrite :wref
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameHostSaveData>& SaveDataRef(void) const { return m_saveDataRef; }
    void SaveDataRefSet(const MushcoreDataRef<MushGameHostSaveData>& inValue) { m_saveDataRef=inValue; }
    // Writable reference for m_saveDataRef
    MushcoreDataRef<MushGameHostSaveData>& SaveDataRefWRef(void) { return m_saveDataRef; }
    const MushcoreDataRef<MushGameHostVolatileData>& VolatileDataRef(void) const { return m_volatileDataRef; }
    void VolatileDataRefSet(const MushcoreDataRef<MushGameHostVolatileData>& inValue) { m_volatileDataRef=inValue; }
    // Writable reference for m_volatileDataRef
    MushcoreDataRef<MushGameHostVolatileData>& VolatileDataRefWRef(void) { return m_volatileDataRef; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } b7rti8X5CFMZEAwzxFE81w
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameHostData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hx8FOByEOLaKNLfCdHG1zg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
