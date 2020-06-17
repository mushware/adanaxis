//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalForm.cpp
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
//%Header } coDZBGPGBoLbH70QxksfTA
/*
 * $Id: InfernalForm.cpp,v 1.9 2006/06/01 15:39:03 southa Exp $
 * $Log: InfernalForm.cpp,v $
 * Revision 1.9  2006/06/01 15:39:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.7  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/06/16 17:25:38  southa
 * Client/server work
 *
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/10 12:34:01  southa
 * Template fixes
 *
 * Revision 1.3  2005/02/03 21:02:55  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.1  2004/01/07 18:01:18  southa
 * MushModel and Infernal work
 *
 */

#include "InfernalForm.h"

#include "InfernalSTL.h"

#include "mushMushcoreIO.h"
#include "mushPie.h"

using namespace Mushware;
using namespace std;

inline void
operator>>(MushcoreXMLIStream& ioIn, MushPieForm *& outpObj)
{
    ioIn.ObjectRead(reinterpret_cast<InfernalForm *&>(outpObj)); // FIXME
}

void
InfernalForm::SignalHandle(const MushPieSignal& inSignal)
{
    bool signalHandled = false;
    
    const MushPieSignalNumeric *pSignalNumeric = dynamic_cast<const MushPieSignalNumeric *>(&inSignal);
    if (pSignalNumeric != NULL)
    {
        switch (pSignalNumeric->EventNumber())
        {
            case kSignalRender:
                Render();
                signalHandled = true;
                break;
                
            default:
                // No action
                break;
        }
    }
    
    if (!signalHandled)
    {
        MushPieForm::SignalHandle(inSignal);
    }
}

void
InfernalForm::Render(void)
{
    // Iterate through the facets, drawing them
    
    MushModelMaterial *pLastMaterial = NULL;
    
    MushModelMultiFacet::tConstIterator pFacetsEnd = m_modelRef.RefGet().FacetsEnd();
    for (MushModelMultiFacet::tConstIterator pFacet = m_modelRef.RefGet().FacetsBegin(); pFacet != pFacetsEnd; ++pFacet)
    {
        if (pFacet->MaterialRef().Exists())
        {
            const MushModelMaterial& newMaterialRef = pFacet->MaterialRef().RefGet();
            
            if (pLastMaterial != &newMaterialRef)
            {
                // Material has changed so update the texture binding
                ++m_facetContextIndex;
                if (m_facetContextIndex >= m_facetContexts.size())
                {
                    // Creating a new context
                    m_facetContexts.resize(m_facetContextIndex + 1);
                    InfernalFacetContext& contextRef = m_facetContexts[m_facetContextIndex];
                    contextRef.TextureRefSet(GLTextureRef(newMaterialRef.TextureName()));
                    contextRef.ArraySizeSet(3*pFacet->Vertices().size());
                    contextRef.RenderTypeImport(pFacet->RenderType());
                    contextRef.VerticesImport(pFacet->Vertices());
                }
                InfernalFacetContext& contextRef = m_facetContexts[m_facetContextIndex];
                
                const GLTextureRef& texRef = contextRef.TextureRef();
                if (texRef.TextureGet()->NeedsAlpha())
                {
                    GLState::BlendSet(GLState::kBlendTransparent);
                }
                else
                {
                    GLState::BlendSet(GLState::kBlendSolid);
                }
                GLState::BindTexture(texRef.BindingNameGet());
                GLState::TextureEnable();
                
                if (contextRef.ListContextNum() == GLUtils::ListContextGet())
                {
                    MUSHCOREASSERT(glIsList(contextRef.ListName()));
                    glCallList(contextRef.ListName());
                }
                else
                {
                    contextRef.ListNameSet(glGenLists(1));
                    GLRender::VertexArraySet(&contextRef.Vertices()[0]);
                    GLRender::TexCoordArraySet(&contextRef.TexCoords()[0]);
                    GLRender::NormalArraySet(&contextRef.Normals()[0]);
                    glNewList(contextRef.ListName(), GL_COMPILE);
                    GLRender::DrawArrays(contextRef.RenderType(), contextRef.ArraySize());
                    glEndList();
                    glCallList(contextRef.ListName());
                    contextRef.ListContextNumSet(GLUtils::ListContextGet());
                }
            }
        }
    }
}

MushcoreScalar 
InfernalForm::InfernalFormLoad(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: InfernalFormLoad(name, filename)"));
    }
    std::string nameStr;
    std::string filename;
    ioCommand.PopParam(nameStr);
    ioCommand.PopParam(filename);
    
    ifstream fileStream(filename.c_str());
    if (!fileStream) throw(MushcoreFileFail(filename, "Could not load file"));
    
    MushcoreXMLIStream fileXML(fileStream);
    
    // Ignore name for the moment
    fileXML >> MushPieForm::tData::Sgl();
    
    return MushcoreScalar(0);
}

MushcoreScalar 
InfernalForm::InfernalFormSave(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: InfernalFormSave(name, filename)"));
    }
    std::string nameStr;
    std::string filename;
    ioCommand.PopParam(nameStr);
    ioCommand.PopParam(filename);
    
    ofstream fileStream(filename.c_str());
    if (!fileStream) throw(MushcoreFileFail(filename, "Could not open file for write"));
    
    MushcoreXMLOStream fileXML(fileStream);
    
    // Ignore name for the moment
    fileXML << MushPieForm::tData::Sgl();
    
    return MushcoreScalar(0);
}

MushcoreScalar 
InfernalForm::InfernalFormPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: InfernalFormPrint(name)"));
    }
    std::string nameStr;
    ioCommand.PopParam(nameStr);
    
    MushcoreXMLOStream fileXML(ioEnv.Out());
    
    // Ignore name for the moment
    fileXML << MushPieForm::tData::Sgl();
    
    return MushcoreScalar(0);
}

void
InfernalForm::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("InfernalFormLoad", InfernalFormLoad);
    MushcoreInterpreter::Sgl().HandlerAdd("InfernalFormSave", InfernalFormSave);
    MushcoreInterpreter::Sgl().HandlerAdd("InfernalFormPrint", InfernalFormPrint);
}

namespace { MushcoreInstaller Installer(InfernalForm::Install); }


//%outOfLineFunctions {

const char *InfernalForm::AutoName(void) const
{
    return "InfernalForm";
}

MushcoreVirtualObject *InfernalForm::AutoClone(void) const
{
    return new InfernalForm(*this);
}

MushcoreVirtualObject *InfernalForm::AutoCreate(void) const
{
    return new InfernalForm;
}

MushcoreVirtualObject *InfernalForm::AutoVirtualFactory(void)
{
    return new InfernalForm;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("InfernalForm", InfernalForm::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
InfernalForm::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushPieForm::AutoPrint(ioOut);
    ioOut << "modelRef=" << m_modelRef << ", ";
    ioOut << "facetContexts=" << m_facetContexts << ", ";
    ioOut << "facetContextIndex=" << m_facetContextIndex;
    ioOut << "]";
}
bool
InfernalForm::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "modelRef")
    {
        ioIn >> m_modelRef;
    }
    else if (inTagStr == "facetContexts")
    {
        ioIn >> m_facetContexts;
    }
    else if (inTagStr == "facetContextIndex")
    {
        ioIn >> m_facetContextIndex;
    }
    else if (MushPieForm::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
InfernalForm::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushPieForm::AutoXMLPrint(ioOut);
    ioOut.TagSet("modelRef");
    ioOut << m_modelRef;
    ioOut.TagSet("facetContexts");
    ioOut << m_facetContexts;
    ioOut.TagSet("facetContextIndex");
    ioOut << m_facetContextIndex;
}
//%outOfLineFunctions } dz8CZXYbvrj/nSW6Pos+GQ
