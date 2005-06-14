//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameConfigBase.cpp
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
//%Header } zlEUQXfSjpEXuKmYV4vLFg
/*
 * $Id$
 * $Log$
 */

#include "MushGameConfigBase.h"

using namespace Mushware;
using namespace std;

MushGameConfigBase::MushGameConfigBase()
{
    ToDefaultSet();
}

void
MushGameConfigBase::ToDefaultSet(void)
{
    m_version = 0;
    m_safeMode = 0;
}

void
MushGameConfigBase::AutoInputPrologue(MushcoreXMLIStream& ioIn)
{
    ToDefaultSet();    
}

void
MushGameConfigBase::AutoOutputPrologue(MushcoreXMLOStream& ioOut) const
{
    ioOut.OStream() << "<!-- Saved by " << MushcoreInfo::Sgl().PackageID() <<
        " " << MushcoreUtil::LogTimeString() << " -->" << endl;
}

//%outOfLineFunctions {
void
MushGameConfigBase::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "version=" << m_version << ", ";
    ioOut << "safeMode=" << m_safeMode;
    ioOut << "]";
}
bool
MushGameConfigBase::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "safeMode")
    {
        ioIn >> m_safeMode;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushGameConfigBase::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("version");
    ioOut << m_version;
    ioOut.TagSet("safeMode");
    ioOut << m_safeMode;
}
//%outOfLineFunctions } nx60ldBnkSzSnxwo7OU3RQ
