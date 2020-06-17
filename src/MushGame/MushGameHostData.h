//%includeGuardStart {
#ifndef MUSHGAMEHOSTDATA_H
#define MUSHGAMEHOSTDATA_H
//%includeGuardStart } 5c+vKr5P06k1yJwzw7n0Xw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameHostData.h
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
//%Header } 1qQX38k3C357kKhniVVGYA
/*
 * $Id: MushGameHostData.h,v 1.2 2006/06/01 15:39:22 southa Exp $
 * $Log: MushGameHostData.h,v $
 * Revision 1.2  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/21 15:57:47  southa
 * MushGame work
 *
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
