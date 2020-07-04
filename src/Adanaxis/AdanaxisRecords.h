//%includeGuardStart {
#ifndef ADANAXISRECORDS_H
#define ADANAXISRECORDS_H
//%includeGuardStart } OInaA1ENw7SKm1GiMAbRsA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRecords.h
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
//%Header } pizda36pBJgWev/x8OvAsQ
/*
 * $Id: AdanaxisRecords.h,v 1.5 2007/06/27 11:56:43 southa Exp $
 * $Log: AdanaxisRecords.h,v $
 * Revision 1.5  2007/06/27 11:56:43  southa
 * Debian packaging
 *
 * Revision 1.4  2007/06/15 12:45:50  southa
 * Prerelease work
 *
 * Revision 1.3  2007/04/18 09:22:03  southa
 * Header and level fixes
 *
 * Revision 1.2  2007/04/16 08:41:08  southa
 * Level and header mods
 *
 * Revision 1.1  2007/03/09 19:50:12  southa
 * Resident textures
 *
 */

#include "AdanaxisStandard.h"

//:generate standard ostream xml1
class AdanaxisRecords : public MushcoreSingleton<AdanaxisRecords>, public MushcoreVirtualObject
{
public:
    AdanaxisRecords();
    virtual ~AdanaxisRecords() {}
    virtual Mushware::tMsec RecordTime(Mushware::U32 inDifficulty, const std::string& inName) const;
    virtual void RecordTimeSet(Mushware::U32 inDifficulty, const std::string& inName, Mushware::tMsec inTime);

    virtual void Load(void);

    virtual void AutoInputPrologue(MushcoreXMLIStream& ioIn);
    virtual void AutoInputEpilogue(MushcoreXMLIStream& ioIn);
    virtual void AutoOutputPrologue(MushcoreXMLOStream& ioOut) const;

protected:
    virtual void Save(void);
    virtual std::string DerivedFilename(void);

private:
    enum
    {
        kVersion = 20070615
    };
    typedef std::map< std::string, Mushware::tMsec > tRecordTimes;
    typedef std::map< Mushware::U32, tRecordTimes > tRecordTimeSet;
    Mushware::U32 ChecksumCalc(void) const;

    Mushware::U32 m_version; //:read
    tRecordTimeSet m_recordTimeSet;
    Mushware::U32 m_checksum;

//%classPrototypes {
public:
    const Mushware::U32& Version(void) const { return m_version; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Fde0Ga82nxooJ/bzHTwYPA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisRecords& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } TY4ckOTkI1kzU/MvMUFH3Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
