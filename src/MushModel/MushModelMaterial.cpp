//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMaterial.cpp
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
//%Header } nqeyBQNpQKSL3+W2ZwLgKQ
/*
 * $Id: MushModelMaterial.cpp,v 1.8 2006/06/01 15:39:35 southa Exp $
 * $Log: MushModelMaterial.cpp,v $
 * Revision 1.8  2006/06/01 15:39:35  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
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
