//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRecords.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.2, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8WzeEMAQ5nxR3CIRoKJp9Q
/*
 * $Id: AdanaxisRecords.cpp,v 1.1 2007/03/09 19:50:11 southa Exp $
 * $Log: AdanaxisRecords.cpp,v $
 * Revision 1.1  2007/03/09 19:50:11  southa
 * Resident textures
 *
 */

#include "AdanaxisRecords.h"

MUSHCORE_SINGLETON_INSTANCE(AdanaxisRecords);

using namespace Mushware;
using namespace std;

AdanaxisRecords::AdanaxisRecords() :
    m_version(kVersion)
{
}

Mushware::tMsec
AdanaxisRecords::RecordTime(const std::string& inName) const
{
    tRecordTimes::const_iterator p = m_recordTimes.find(inName);
    return (p == m_recordTimes.end()) ? 0 : p->second;
}

void
AdanaxisRecords::RecordTimeSet(const std::string& inName, Mushware::tMsec inTime)
{
    m_recordTimes[inName] = inTime;
    Save();    
}

void
AdanaxisRecords::Save(void)
{
    m_checksum = ChecksumCalc();

    const MushcoreScalar *pScalar = NULL;    
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "RECORDS_FILENAME"))
    {
        try
        {
            AutoFileSave(pScalar->StringGet());
        }
        catch (MushcoreFail& e)
        {
            MushcoreLog::Sgl().ErrorLog() << "Saving records: " << e.what() << endl;
        }
    }
}

void
AdanaxisRecords::Load(void)
{
    const MushcoreScalar *pScalar = NULL;
    
    try
    {
        if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "RECORDS_FILENAME"))
        {
            if (!AutoFileIfExistsLoad(pScalar->StringGet()))
            {
                MushcoreLog::Sgl().InfoLog() << "Creating new records file '" << pScalar->StringGet() << "'" << endl;
                m_recordTimes.clear();
                Save();
            }
            if (m_version != kVersion)
            {
                m_version = kVersion;
                throw MushcoreDataFail("Incompatible records file version - discarding");
            }
        }
    }
    catch (MushcoreFail& e)
    {
        m_recordTimes.clear();
        MushcoreLog::Sgl().ErrorLog() << "Loading records: " << e.what() << endl;
    }
}

void
AdanaxisRecords::AutoInputPrologue(MushcoreXMLIStream& ioIn)
{
    m_recordTimes.clear();
}

void
AdanaxisRecords::AutoInputEpilogue(MushcoreXMLIStream& ioIn)
{
    if (m_checksum != ChecksumCalc())
    {
#ifndef MUSHCORE_DEBUG
        // Debug allows falsified record file
        m_recordTimes.clear();
#endif
        MushcoreLog::Sgl().ErrorLog() << "Invalid records file" << endl;
    }
}

void
AdanaxisRecords::AutoOutputPrologue(MushcoreXMLOStream& ioOut) const
{
    ioOut.OStream() << "<!-- Saved by " << MushcoreInfo::Sgl().PackageID() <<
    " " << MushcoreUtil::LogTimeString() << " -->" << endl;
}

Mushware::U32
AdanaxisRecords::ChecksumCalc(void) const
{
    U32 checksum = 473623;
    for (tRecordTimes::const_iterator p = m_recordTimes.begin();
         p != m_recordTimes.end(); ++p)
    {
        for (U32 i=0; i<p->first.size(); ++i)
        {
            checksum += p->first[i];
        }
        checksum ^= checksum << 9;
        checksum ^= p->second;
        checksum ^= checksum >> 11;
    }
    return checksum;
}

//%outOfLineFunctions {

const char *AdanaxisRecords::AutoName(void) const
{
    return "AdanaxisRecords";
}

MushcoreVirtualObject *AdanaxisRecords::AutoClone(void) const
{
    return new AdanaxisRecords(*this);
}

MushcoreVirtualObject *AdanaxisRecords::AutoCreate(void) const
{
    return new AdanaxisRecords;
}

MushcoreVirtualObject *AdanaxisRecords::AutoVirtualFactory(void)
{
    return new AdanaxisRecords;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisRecords", AdanaxisRecords::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisRecords::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "version=" << m_version << ", ";
    ioOut << "recordTimes=" << m_recordTimes << ", ";
    ioOut << "checksum=" << m_checksum;
    ioOut << "]";
}
bool
AdanaxisRecords::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "version")
    {
        ioIn >> m_version;
    }
    else if (inTagStr == "recordTimes")
    {
        ioIn >> m_recordTimes;
    }
    else if (inTagStr == "checksum")
    {
        ioIn >> m_checksum;
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisRecords::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("version");
    ioOut << m_version;
    ioOut.TagSet("recordTimes");
    ioOut << m_recordTimes;
    ioOut.TagSet("checksum");
    ioOut << m_checksum;
}
//%outOfLineFunctions } liWk3gsDVlLq6aLs1NPwbA
