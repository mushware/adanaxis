//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMultiFacet.cpp
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
//%Header } KDrzMM/sHV2WFHQjP9ctgQ
/*
 * $Id: MushModelMultiFacet.cpp,v 1.3 2005/02/10 12:34:10 southa Exp $
 * $Log: MushModelMultiFacet.cpp,v $
 * Revision 1.3  2005/02/10 12:34:10  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.1  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 */

#include "MushModelMultiFacet.h"

#include "MushModelIO.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushModelMultiFacet);

MushcoreScalar 
MushModelMultiFacet::MushModelMultiFacetLoad(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: MushModelMultiFacetLoad(name, filename)"));
    }
    std::string nameStr;
    std::string filename;
    ioCommand.PopParam(nameStr);
    ioCommand.PopParam(filename);
    
    ifstream fileStream(filename.c_str());
    if (!fileStream) throw(MushcoreFileFail(filename, "Could not load file"));
    
    MushcoreXMLIStream fileXML(fileStream);
    
    // Ignore name for the moment
    fileXML >> MushcoreData<MushModelMultiFacet>::Sgl();
    
    return MushcoreScalar(0);
}

MushcoreScalar 
MushModelMultiFacet::MushModelMultiFacetSave(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: MushModelMultiFacetSave(name, filename)"));
    }
    std::string nameStr;
    std::string filename;
    ioCommand.PopParam(nameStr);
    ioCommand.PopParam(filename);
    
    ofstream fileStream(filename.c_str());
    if (!fileStream) throw(MushcoreFileFail(filename, "Could not open file for write"));
    
    MushcoreXMLOStream fileXML(fileStream);
    
    // Ignore name for the moment
    fileXML << MushcoreData<MushModelMultiFacet>::Sgl();
    
    return MushcoreScalar(0);
}

MushcoreScalar 
MushModelMultiFacet::MushModelMultiFacetPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: MushModelMultiFacetPrint(name)"));
    }
    std::string nameStr;
    ioCommand.PopParam(nameStr);
    
    MushcoreXMLOStream fileXML(ioEnv.Out());
    
    // Ignore name for the moment
    fileXML << MushcoreData<MushModelMultiFacet>::Sgl();
    
    return MushcoreScalar(0);
}

void
MushModelMultiFacet::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("MushModelMultiFacetLoad", MushModelMultiFacetLoad);
    MushcoreInterpreter::Sgl().HandlerAdd("MushModelMultiFacetSave", MushModelMultiFacetSave);
    MushcoreInterpreter::Sgl().HandlerAdd("MushModelMultiFacetPrint", MushModelMultiFacetPrint);
}

namespace { MushcoreInstaller Installer(MushModelMultiFacet::Install); }

void
MushModelMultiFacet::NullFunction(void)
{
}

//%outOfLineFunctions {

const char *MushModelMultiFacet::AutoNameGet(void) const
{
    return "MushModelMultiFacet";
}

MushcoreVirtualObject *MushModelMultiFacet::AutoClone(void) const
{
    return new MushModelMultiFacet(*this);
}

MushcoreVirtualObject *MushModelMultiFacet::AutoCreate(void) const
{
    return new MushModelMultiFacet;
}

MushcoreVirtualObject *MushModelMultiFacet::AutoVirtualFactory(void)
{
    return new MushModelMultiFacet;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushModelMultiFacet", MushModelMultiFacet::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushModelMultiFacet::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "facets=" << m_facets;
    ioOut << "]";
}
bool
MushModelMultiFacet::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "facets")
    {
        ioIn >> m_facets;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushModelMultiFacet::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("facets");
    ioOut << m_facets;
}
//%outOfLineFunctions } LEUhvRLj/Y4UT0+CKANgUA
