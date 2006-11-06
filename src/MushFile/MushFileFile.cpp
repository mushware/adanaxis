//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileFile.cpp
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
//%Header } s347TUOP6TwsXJmaLdEs1g
/*
 * $Id$
 * $Log$
 */

#include "MushFileFile.h"

std::string
MushFileFile::Name(void) const
{
    return m_filename.Name();
}

void
MushFileFile::OpenForRead(const std::string& inName)
{
    m_filename.NameSet(inName);
    m_filename.ResolveForRead();
    
    if (m_filename.SourceIsMush())
    {
        throw MushcoreLogicFail("Mush not supported yet");
    }
    else if (m_filename.SourceIsFile())
    {
        
    }
}

std::string
MushFileFile::PlainFilename(void)
{
    if (!m_filename.SourceIsFile())
    {
        throw MushcoreFileFail(m_filename.Name(), "File is nor a plain file");
    }
    return m_filename.Name();
}

//%outOfLineFunctions {

const char *MushFileFile::AutoName(void) const
{
    return "MushFileFile";
}

MushcoreVirtualObject *MushFileFile::AutoClone(void) const
{
    return new MushFileFile(*this);
}

MushcoreVirtualObject *MushFileFile::AutoCreate(void) const
{
    return new MushFileFile;
}

MushcoreVirtualObject *MushFileFile::AutoVirtualFactory(void)
{
    return new MushFileFile;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushFileFile", MushFileFile::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushFileFile::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "filename=" << m_filename << ", ";
    ioOut << "sourceType=" << m_sourceType;
    ioOut << "]";
}
bool
MushFileFile::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "filename")
    {
        ioIn >> m_filename;
    }
    else if (inTagStr == "sourceType")
    {
        ioIn >> m_sourceType;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushFileFile::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("filename");
    ioOut << m_filename;
    ioOut.TagSet("sourceType");
    ioOut << m_sourceType;
}
//%outOfLineFunctions } +aM+XJSJ1q4HkK8y42d4ww
