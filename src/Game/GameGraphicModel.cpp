/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id$
 * $Log$
 */

#include "GameGraphicModel.h"

void
GameGraphicModel::Render(void)
{
    if (m_currentTexRef.Exists())
    {
        GLUtils::PushMatrix();

        //GLUtils::Translate(m_offset);
        if (m_currentTexRef.TextureGet()->NeedsAlpha())
        {
            GLUtils::BlendSet(GLUtils::kBlendTransparent);
        }
        else
        {
            GLUtils::BlendSet(GLUtils::kBlendSolid);
        }
        // GLUtils::DrawSprite(*m_texRef.TextureGet(), m_rectangle);
        GLUtils::PopMatrix();
    }    
}

void
GameGraphicModel::HandleTextureEnd(CoreXML& inXML)
{
    m_currentTexRef.NameSet(inXML.TopData());
}

void
GameGraphicModel::HandleFacetsStart(CoreXML& inXML)
{
    m_pickleState = kPickleFacets;

    m_facets.push_back(FacetDef());
    m_facets.back().texRef=m_currentTexRef;
}

void
GameGraphicModel::HandleFacetsEnd(CoreXML& inXML)
{
    m_pickleState = kPickleData;
}

void
GameGraphicModel::HandleOffsetEnd(CoreXML& inXML)
{
    string typeStr=inXML.GetAttribOrThrow("type").StringGet();
    if (typeStr == "position")
    {
        m_positionOffset.Unpickle(inXML);
    }
    else if (typeStr == "texture")
    {
        m_texCoordOffset.Unpickle(inXML);
    }
    else
    {
        inXML.Throw("Bad type for offset '"+typeStr+"'");
    }
}

void
GameGraphicModel::HandleVertexEnd(CoreXML& inXML)
{
    const char *failMessage="Bad format for vertex.  Should be <vertex>0,0,2:0,0.5</vertex>";
    istringstream data(inXML.TopData());
    GLVector vertex;
    GLPoint texCoord;

    char colon;
    vertex.Unpickle(data);
    if (!(data >> colon) || colon != ':') inXML.Throw(failMessage);
    texCoord.Unpickle(data);
    vertex += m_positionOffset;
    texCoord += m_texCoordOffset;   
    m_facets.back().vertices.Push(vertex);
    m_facets.back().vertices.Build(vertex); // working here
    m_facets.back().texCoords.Push(texCoord);    
};

void
GameGraphicModel::HandleGraphicEnd(CoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameGraphicModel::NullHandler(CoreXML& inXML)
{
}

void
GameGraphicModel::Pickle(ostream& inOut, const string& inPrefix="") const
{
    inOut << inPrefix << "<!-- Incomplete -->" << endl;
}

void
GameGraphicModel::UnpicklePrologue(void)
{
    GameGraphic::UnpicklePrologue();
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);
    m_startTable[kPickleData]["texture"] = &GameGraphicModel::NullHandler;
    m_endTable[kPickleData]["texture"] = &GameGraphicModel::HandleTextureEnd;
    m_startTable[kPickleData]["facets"] = &GameGraphicModel::HandleFacetsStart;
    m_endTable[kPickleFacets]["facets"] = &GameGraphicModel::HandleFacetsEnd;

    m_startTable[kPickleFacets]["offset"] = &GameGraphicModel::NullHandler;
    m_endTable[kPickleFacets]["offset"] = &GameGraphicModel::HandleOffsetEnd;
    m_startTable[kPickleFacets]["vertex"] = &GameGraphicModel::NullHandler;
    m_endTable[kPickleFacets]["vertex"] = &GameGraphicModel::HandleVertexEnd;

    m_endTable[kPickleData]["graphic"] = &GameGraphicModel::HandleGraphicEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_positionOffset=GLVector(0,0,0);
    m_texCoordOffset=GLPoint(0,0);
}

void
GameGraphicModel::Unpickle(CoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameGraphicModel::UnpickleEpilogue(void)
{
    GameGraphic::UnpickleEpilogue();
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GameGraphicModel::XMLStartHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p != m_startTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
//        if (m_pickleState == kPickleData)
//        {
//            GameGraphic::XMLStartHandler(inXML);
//            m_pickleState=kPickleWithinBase;
//            ++m_baseThreaded;
//        }
//        else
        {
            ostringstream message;
            message << "Unexpected tag <" << inXML.TopTag() << "> in GraphicModel.  Potential matches are";
ElementFunctionMap::iterator p = m_startTable[m_pickleState].begin();
            while (p != m_startTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameGraphicModel::XMLEndHandler(CoreXML& inXML)
{
ElementFunctionMap::iterator p = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p != m_endTable[m_pickleState].end())
    {
        (this->*p->second)(inXML);
    }
    else
    {
//        if (m_pickleState == kPickleWithinBase)
//        {
//          GameGraphic::XMLEndHandler(inXML);
//            --m_baseThreaded;
//            if (m_baseThreaded == 0)
//            {
//                m_pickleState=kPickleData;
//            }
//        }
//        else
        {
            ostringstream message;
            message << "Unexpected end of tag </" << inXML.TopTag() << "> in GraphicModel.  Potential matches are";
ElementFunctionMap::iterator p = m_endTable[m_pickleState].begin();
            while (p != m_endTable[m_pickleState].end())
            {
                message << " <" << p->first << ">";
                p++;
            }
            inXML.Throw(message.str());
        }
    }
}

void
GameGraphicModel::XMLDataHandler(CoreXML& inXML)
{
}
