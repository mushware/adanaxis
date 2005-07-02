//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMaterial.cpp
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
//%Header } x23JuTdZeZ6lv0VI6tjnsA
/*
 * $Id: MushModelMaterial.cpp,v 1.6 2005/06/20 14:30:37 southa Exp $
 * $Log: MushModelMaterial.cpp,v $
 * Revision 1.6  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.4  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:09  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/08 22:41:10  southa
 * MushModel commands
 *
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

const char *MushModelMaterial::AutoName(void) const
{
    return "MushModelMaterial";
}

MushcoreVirtualObject *MushModelMaterial::AutoClone(void) const
{
    return new MushModelMaterial(*this);
}

MushcoreVirtualObject *MushModelMaterial::AutoCreate(void) const
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
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
//%outOfLineFunctions } EdHz5AmFcPFumZinjr3cjQ
