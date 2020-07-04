//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRecords.cpp
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
//%Header } XjtpaCHDXRQ4Owk1qWbflg
/*
 * $Id: AdanaxisRecords.cpp,v 1.5 2007/06/27 11:56:43 southa Exp $
 * $Log: AdanaxisRecords.cpp,v $
 * Revision 1.5  2007/06/27 11:56:43  southa
 * Debian packaging
 *
 * Revision 1.4  2007/04/18 12:44:36  southa
 * Cache purge fix and pre-release tweaks
 *
 * Revision 1.3  2007/04/18 09:22:03  southa
 * Header and level fixes
 *
 * Revision 1.2  2007/04/16 08:41:08  southa
 * Level and header mods
 *
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
AdanaxisRecords::RecordTime(Mushware::U32 inDifficulty, const std::string& inName) const
{
    tMsec retVal = 0;

    tRecordTimeSet::const_iterator p = m_recordTimeSet.find(inDifficulty);

    if (p != m_recordTimeSet.end())
    {
        tRecordTimes::const_iterator q = p->second.find(inName);
        if (q != p->second.end())
        {
            retVal = q->second;
        }
    }
    return retVal;
}

void
AdanaxisRecords::RecordTimeSet(Mushware::U32 inDifficulty, const std::string& inName, Mushware::tMsec inTime)
{
    tRecordTimes& recRef = m_recordTimeSet[inDifficulty];
    recRef[inName] = inTime;
    Save();
}

std::string
AdanaxisRecords::DerivedFilename(void)
{
    std::string retVal;

    const MushcoreScalar *pScalar = NULL;
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "RECORDS_PATH"))
    {
        retVal = pScalar->StringGet() + "/" + MushcoreInfo::Sgl().PackageName() + "records.xml";
    }
    else
    {
        throw MushcoreRequestFail("RECORDS_PATH not set");
    }
    return retVal;
}

void
AdanaxisRecords::Save(void)
{
    m_checksum = ChecksumCalc();

    try
    {
        AutoFileSave(DerivedFilename());
    }
    catch (MushcoreFail& e)
    {
        MushcoreLog::Sgl().ErrorLog() << "Saving records: " << e.what() << endl;
    }
}

void
AdanaxisRecords::Load(void)
{
    try
    {
        if (!AutoFileIfExistsLoad(DerivedFilename()))
        {
            MushcoreLog::Sgl().InfoLog() << "Creating new records file '" << DerivedFilename() << "'" << endl;
            m_recordTimeSet.clear();
            Save();
        }
        if (m_version != kVersion)
        {
            m_version = kVersion;
            throw MushcoreDataFail("Incompatible records file version - discarding");
        }
    }
    catch (MushcoreFail& e)
    {
        m_recordTimeSet.clear();
        MushcoreLog::Sgl().ErrorLog() << "Loading records: " << e.what() << endl;
    }
}

void
AdanaxisRecords::AutoInputPrologue(MushcoreXMLIStream& ioIn)
{
    m_recordTimeSet.clear();
}

void
AdanaxisRecords::AutoInputEpilogue(MushcoreXMLIStream& ioIn)
{
    if (m_checksum != ChecksumCalc())
    {
#ifndef MUSHCORE_DEBUG
        // Debug allows falsified record file
        m_recordTimeSet.clear();
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
    for (tRecordTimeSet::const_iterator p = m_recordTimeSet.begin();
         p != m_recordTimeSet.end(); ++p)
    {
        const tRecordTimes& recRef = p->second;

        for (tRecordTimes::const_iterator q = recRef.begin();
             q != recRef.end(); ++q)
        {
            for (U32 i=0; i<q->first.size(); ++i)
            {
                checksum += q->first[i];
            }
            checksum ^= checksum << 9;
            checksum ^= q->second;
            checksum ^= checksum >> 11;
        }
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
    ioOut << "recordTimeSet=" << m_recordTimeSet << ", ";
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
    else if (inTagStr == "recordTimeSet")
    {
        ioIn >> m_recordTimeSet;
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
    ioOut.TagSet("recordTimeSet");
    ioOut << m_recordTimeSet;
    ioOut.TagSet("checksum");
    ioOut << m_checksum;
}
//%outOfLineFunctions } iK+WNp2Yr7Q4wzyLAVjyGw
