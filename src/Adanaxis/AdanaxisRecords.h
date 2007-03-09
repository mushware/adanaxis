//%includeGuardStart {
#ifndef ADANAXISRECORDS_H
#define ADANAXISRECORDS_H
//%includeGuardStart } OInaA1ENw7SKm1GiMAbRsA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRecords.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Df9k0e151CbU+TZgMvWYvg
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisStandard.h"

//:generate standard ostream xml1
class AdanaxisRecords : public MushcoreSingleton<AdanaxisRecords>, public MushcoreVirtualObject
{
public:
    AdanaxisRecords();
    virtual ~AdanaxisRecords() {}
    virtual Mushware::tMsec RecordTime(const std::string& inName) const;
    virtual void RecordTimeSet(const std::string& inName, Mushware::tMsec inTime);

    virtual void Load(void);
    
    virtual void AutoInputPrologue(MushcoreXMLIStream& ioIn);   
    virtual void AutoInputEpilogue(MushcoreXMLIStream& ioIn);   
    virtual void AutoOutputPrologue(MushcoreXMLOStream& ioOut) const;

protected:
    virtual void Save(void);
    
private:
    enum
    {
        kVersion = 20070309
    };
    typedef std::map< std::string, Mushware::tMsec > tRecordTimes;
    
    Mushware::U32 ChecksumCalc(void) const;

    Mushware::U32 m_version; //:read
    tRecordTimes m_recordTimes;
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
