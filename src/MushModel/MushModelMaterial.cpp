//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMaterial.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } kMzPo0tNkdWRsyion9xovw
/*
 * $Id: MushModelMaterial.cpp,v 1.1 2004/01/07 18:01:19 southa Exp $
 * $Log: MushModelMaterial.cpp,v $
 * Revision 1.1  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 */

#include "MushModelMaterial.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushModelMaterial);

MushcoreScalar 
MushModelMaterial::MushModelMaterialLoad(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: MushModelMaterialLoad(name, filename)"));
    }
    std::string nameStr;
    std::string filename;
    ioCommand.PopParam(nameStr);
    ioCommand.PopParam(filename);
    
    ifstream fileStream(filename.c_str());
    if (!fileStream) throw(MushcoreFileFail(filename, "Could not load file"));
    
    MushcoreXMLIStream fileXML(fileStream);
    
    // Ignore name for the moment
    fileXML >> MushcoreData<MushModelMaterial>::Sgl();
    
    return MushcoreScalar(0);
}

MushcoreScalar 
MushModelMaterial::MushModelMaterialSave(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: MushModelMaterialSave(name, filename)"));
    }
    std::string nameStr;
    std::string filename;
    ioCommand.PopParam(nameStr);
    ioCommand.PopParam(filename);
    
    ofstream fileStream(filename.c_str());
    if (!fileStream) throw(MushcoreFileFail(filename, "Could not open file for write"));
    
    MushcoreXMLOStream fileXML(fileStream);
    
    // Ignore name for the moment
    fileXML << MushcoreData<MushModelMaterial>::Sgl();
    
    return MushcoreScalar(0);
}

MushcoreScalar 
MushModelMaterial::MushModelMaterialPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: MushModelMaterialPrint(name)"));
    }
    std::string nameStr;
    ioCommand.PopParam(nameStr);
    
    MushcoreXMLOStream fileXML(ioEnv.Out());
    
    // Ignore name for the moment
    fileXML << MushcoreData<MushModelMaterial>::Sgl();
    
    return MushcoreScalar(0);
}

void
MushModelMaterial::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("MushModelMaterialLoad", MushModelMaterialLoad);
    MushcoreInterpreter::Sgl().HandlerAdd("MushModelMaterialSave", MushModelMaterialSave);
    MushcoreInterpreter::Sgl().HandlerAdd("MushModelMaterialPrint", MushModelMaterialPrint);
}

namespace { MushcoreInstaller Installer(MushModelMaterial::Install); }

void
MushModelMaterial::NullFunction(void)
{
}
//%outOfLineFunctions {
const char *MushModelMaterial::AutoNameGet(void) const
{
    return "MushModelMaterial";
}
MushModelMaterial *MushModelMaterial::AutoClone(void) const
{
    return new MushModelMaterial(*this);
}
MushModelMaterial *MushModelMaterial::AutoCreate(void) const
{
    return new MushModelMaterial;
}
MushcoreVirtualObject *MushModelMaterial::AutoVirtualFactory(void)
{
    return new MushModelMaterial;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushModelMaterial", MushModelMaterial::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushModelMaterial::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "textureName=" << m_textureName;
    ioOut << "]";
}
bool
MushModelMaterial::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "textureName")
    {
        ioIn >> m_textureName;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushModelMaterial::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("textureName");
    ioOut << m_textureName;
}
//%outOfLineFunctions } DQ23xlzxb4kAzi+CjNluTw
