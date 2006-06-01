//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameGraphicModel.cpp
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
//%Header } Qod0cnDO9izAs88yby707Q
/*
 * $Id: GameGraphicModel.cpp,v 1.20 2005/05/19 13:02:02 southa Exp $
 * $Log: GameGraphicModel.cpp,v $
 * Revision 1.20  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.19  2004/01/02 11:56:59  southa
 * MushPie created
 *
 * Revision 1.18  2004/01/01 23:04:02  southa
 * XCode fixes
 *
 * Revision 1.17  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:08:46  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/01/13 14:31:58  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.14  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.13  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.12  2003/01/07 17:13:42  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.11  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/11/24 23:18:23  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.8  2002/10/22 20:42:04  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/17 16:41:21  southa
 * Initialisation fix and player facet
 *
 * Revision 1.6  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.5  2002/10/14 15:13:39  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.4  2002/10/14 13:03:00  southa
 * Display list test
 *
 * Revision 1.3  2002/10/12 17:34:20  southa
 * Wall edges
 *
 * Revision 1.2  2002/10/12 15:25:18  southa
 * Facet renderer
 *
 * Revision 1.1  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 */

#include "GameGraphicModel.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

GameGraphicModel::~GameGraphicModel()
{
    if (m_listContext != 0)
    {
        U32 size=m_listName.size();
        for (U32 i=0; i<size; ++i)
        {
            glDeleteLists(m_listName[i], 1);
        }
    }
}

void
GameGraphicModel::Render(void)
{
    U32 facetSize=m_facets.size();

    for (U32 i=0; i<facetSize; ++i)
    {
        FacetDef& facetDef=m_facets[i];
        U32 arraySize=facetDef.vertices.SizeGet();
        if (facetDef.texRef.Exists())
        {
            if (facetDef.texRef.TextureGet()->NeedsAlpha())
            {
                GLState::BlendSet(GLState::kBlendTransparent);
            }
            else
            {
                GLState::BlendSet(GLState::kBlendSolid);
            }
            GLState::BindTexture(facetDef.texRef.BindingNameGet());
            GLState::TextureEnable();
            if (m_listContext == GLUtils::ListContextGet())
            {
                MUSHCOREASSERT(glIsList(m_listName[i]));
                glCallList(m_listName[i]);
            }
            else
            {
                m_listName[i]=glGenLists(1);
                GLRender::VertexArraySet(facetDef.vertices.ArrayGet());
                GLRender::TexCoordArraySet(facetDef.texCoords.ArrayGet());
                GLRender::NormalArraySet(facetDef.normals.ArrayGet());
                glNewList(m_listName[i], GL_COMPILE);
                GLRender::DrawArrays(facetDef.type, arraySize);
                glEndList();
                glCallList(m_listName[i]);
            }
        }
    }
    m_listContext=GLUtils::ListContextGet();
}

void
GameGraphicModel::HandleTextureEnd(MushcoreXML& inXML)
{
    m_currentTexRef.NameSet(inXML.TopData());
}

void
GameGraphicModel::HandleFacetsStart(MushcoreXML& inXML)
{
    string typeStr=inXML.GetAttribOrThrow("type").StringGet();

    m_facets.push_back(FacetDef());
    m_listName.push_back(0); // Make space for list names

    if (typeStr == "points")
    {
        m_facets.back().type=GL_POINTS;
    }
    else if (typeStr == "linestrip")
    {
        m_facets.back().type=GL_LINE_STRIP;
    }
    else if (typeStr == "lineloop")
    {
        m_facets.back().type=GL_LINE_LOOP;
    }
    else if (typeStr == "lines")
    {
        m_facets.back().type=GL_LINES;
    }
    else if (typeStr == "trianglestrip")
    {
        m_facets.back().type=GL_TRIANGLE_STRIP;
    }
    else if (typeStr == "trianglefan")
    {
        m_facets.back().type=GL_TRIANGLE_FAN;
    }
    else if (typeStr == "triangles")
    {
        m_facets.back().type=GL_TRIANGLES;
    }
    else if (typeStr == "quadstrip")
    {
        m_facets.back().type=GL_QUAD_STRIP;
    }
    else if (typeStr == "quads")
    {
        m_facets.back().type=GL_QUADS;
    }
    else if (typeStr == "polygon")
    {
        m_facets.back().type=GL_POLYGON;
    }
    else
    {
        inXML.Throw("Unknown facet type '"+typeStr+"'");
    }

    m_facetPositionOffset=GLVector(0,0,0);
    m_facetTexCoordOffset=GLPoint(0,0);

    m_pickleState = kPickleFacets;
}

void
GameGraphicModel::HandleFacetsEnd(MushcoreXML& inXML)
{
    m_facets.back().texRef=m_currentTexRef;
    m_pickleState = kPickleData;
}

void
GameGraphicModel::HandleOffsetEnd(MushcoreXML& inXML)
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
GameGraphicModel::HandleFacetOffsetEnd(MushcoreXML& inXML)
{
    string typeStr=inXML.GetAttribOrThrow("type").StringGet();
    if (typeStr == "position")
    {
        m_facetPositionOffset.Unpickle(inXML);
    }
    else if (typeStr == "texture")
    {
        m_facetTexCoordOffset.Unpickle(inXML);
    }
    else
    {
        inXML.Throw("Bad type for offset '"+typeStr+"'");
    }
}


void
GameGraphicModel::HandleVertexEnd(MushcoreXML& inXML)
{
    const char *failMessage="Bad format for vertex.  Should be <vertex>0,0,2:0,0.5</vertex>";
    istringstream data(inXML.TopData());
    GLVector vertex;
    GLPoint texCoord;
    GLVector normal(GLVector(0,0,1));
    char colon;
    vertex.Unpickle(data);
    if (!(data >> colon) || colon != ':') inXML.Throw(failMessage);
    texCoord.Unpickle(data);
    if ((data >> colon) && colon == ':')
    {
        normal.Unpickle(data);
    }
    if (normal.Magnitude() > 0)
    {
        normal /= normal.Magnitude();
    }
    vertex += m_positionOffset;
    vertex += m_facetPositionOffset;
    texCoord += m_texCoordOffset;
    texCoord += m_facetTexCoordOffset;   
    m_facets.back().vertices.Push(vertex);
    m_facets.back().texCoords.Push(texCoord);
    m_facets.back().normals.Push(normal);    
};

void
GameGraphicModel::HandleGraphicEnd(MushcoreXML& inXML)
{
    inXML.StopHandler();
    UnpickleEpilogue();
}

void
GameGraphicModel::NullHandler(MushcoreXML& inXML)
{
}

void
GameGraphicModel::Pickle(ostream& inOut, const string& inPrefix) const
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

    m_startTable[kPickleData]["offset"] = &GameGraphicModel::NullHandler;
    m_endTable[kPickleData]["offset"] = &GameGraphicModel::HandleOffsetEnd;
    m_startTable[kPickleFacets]["offset"] = &GameGraphicModel::NullHandler;
    m_endTable[kPickleFacets]["offset"] = &GameGraphicModel::HandleFacetOffsetEnd;
    m_startTable[kPickleFacets]["vertex"] = &GameGraphicModel::NullHandler;
    m_endTable[kPickleFacets]["vertex"] = &GameGraphicModel::HandleVertexEnd;

    m_endTable[kPickleData]["graphic"] = &GameGraphicModel::HandleGraphicEnd;
    m_pickleState=kPickleData;
    m_baseThreaded=0;
    m_positionOffset=GLVector(0,0,0);
    m_texCoordOffset=GLPoint(0,0);
}

void
GameGraphicModel::Unpickle(MushcoreXML& inXML)
{
    UnpicklePrologue();
    inXML.ParseStream(*this);
}

void
GameGraphicModel::UnpickleEpilogue(void)
{
    for (U32 i=0; i<m_facets.size(); ++i)
    {
        m_facets[i].vertices.Build();
        m_facets[i].texCoords.Build();
        m_facets[i].normals.Build();
    }
    GameGraphic::UnpickleEpilogue();
    m_startTable.resize(0);
    m_endTable.resize(0);
}

void
GameGraphicModel::XMLStartHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_startTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_startTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
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
GameGraphicModel::XMLEndHandler(MushcoreXML& inXML)
{
ElementFunctionMap::iterator p2 = m_endTable[m_pickleState].find(inXML.TopTag());

    if (p2 != m_endTable[m_pickleState].end())
    {
        (this->*p2->second)(inXML);
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
GameGraphicModel::XMLDataHandler(MushcoreXML& inXML)
{
}

char *
GameGraphicModel::TypeNameGet(void) const
{
    return "gamegraphicmodel";
}
