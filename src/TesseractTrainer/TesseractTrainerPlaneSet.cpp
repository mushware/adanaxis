//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPlaneSet.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6or7cGI6GTbVWHPnRbyYCA
/*
 * $Id: TesseractTrainerPlaneSet.cpp,v 1.1 2005/02/26 17:53:49 southa Exp $
 * $Log: TesseractTrainerPlaneSet.cpp,v $
 * Revision 1.1  2005/02/26 17:53:49  southa
 * Plane sets and pairs
 *
 */

#include "TesseractTrainerPlaneSet.h"

#include "TesseractTrainerPixelSource.h"

#include "mushMushcore.h"

#include "MushMeshDivide.h"

using namespace Mushware;
using namespace std;

void
TesseractTrainerPlaneSet::Create(tVal frame, const std::vector<Mushware::t4GLVal>& inColours)
{
    m_colours = inColours;
    
    t4Val scale(0.25,0.25,0.25,0.25);
    MushMeshGroup buildGroup;
    std::vector<tVertex> buildVertices;
    std::vector<t2Val> buildTexCoords;
    
    // 24 vertices, four for each plane
    for (U32 i=0; i<4; ++i)
    {
        for (U32 j=i+1; j<4; ++j)
        {
            tVertex vert(0,0,0,0);
            
            vert.Set(-1, i);
            vert.Set(-1, j);
            buildVertices.push_back(vert.ElementwiseProduct(scale));
            
            vert.Set( 1, i);
            vert.Set(-1, j);
            buildVertices.push_back(vert.ElementwiseProduct(scale));
            
            vert.Set( 1, i);
            vert.Set( 1, j);
            buildVertices.push_back(vert.ElementwiseProduct(scale));
            
            vert.Set(-1, i);
            vert.Set( 1, j);
            buildVertices.push_back(vert.ElementwiseProduct(scale)); 
        }
    }
    
    // File the zero order group (vertices in facets)
    buildGroup.SuperGroupPush();
    for (U32 face=0; face<6; ++face)
    {
        for (U32 facet=0; facet<1; ++facet)
        {
            buildGroup.GroupPush();
            
            U32 base=face*4;
            buildGroup.ValuePush(base);
            buildGroup.ValuePush(base+1);
            buildGroup.ValuePush(base+2);
            buildGroup.ValuePush(base+3);
        }
    }
    
    
    // fill the first order group (facets in facets)
    buildGroup.SuperGroupPush();
    
#if 0    
    buildGroup.GroupPush();
    buildGroup.ValuePush(0);
    buildGroup.GroupPush();
    buildGroup.ValuePush(5);
    
#else
    for (U32 face=0; face<6; ++face)
    {
        buildGroup.GroupPush();
        for (U32 facet=0; facet<1; ++facet)
        {
            buildGroup.ValuePush(face);
        }
    }
#endif
    
    for (U32 i=0; i<buildVertices.size(); i += 4)
    {
        m_texCoords.push_back(t2Val(0,0));
        m_texCoords.push_back(t2Val(0,1));
        m_texCoords.push_back(t2Val(1,1));
        m_texCoords.push_back(t2Val(1,0));
    }
    
    MushMeshGroup buildGroup2;
    std::vector<tVertex> buildVertices2;
    
    m_vertices = buildVertices;
    m_facetGroup = buildGroup;
    
    // Create texture reference
    m_textureRef.NameSet("plane-target1");
}

void
TesseractTrainerPlaneSet::Render(tVal frame)
{
    tVal ang0=0.0;
    tVal ang1=M_PI*(2.0/3);
    tVal ang2=M_PI*(4.0/3);
    
    
    MushMeshVector<tVal, 4> vec0(cos(ang0), cos(ang1), cos(ang2), 0);
    MushMeshVector<tVal, 4> vec1(sin(ang0), sin(ang1), sin(ang2), 0);
    MushMeshVector<tVal, 4> vec2(0, 0, 0, 1);
    
    if ((int)frame % 60 > 60)
    {
        vec0 = MushMeshVector<tVal, 4>(1,0,0,0);
        vec1 = MushMeshVector<tVal, 4>(0,1,0,0);
        vec2 = MushMeshVector<tVal, 4>(0,0,0,1);
    }        
    
    MushMeshPreMatrix<tVal, 4, 3> preMatrix
        (
         vec0, vec1, vec2
         );
    
#if 1
    
    std::vector<tVertex> vertices(m_vertices);
    
    for (U32 j=0; j<vertices.size(); ++j)
    {
        m_orientation.InPlaceRotate(vertices[j]);
    }
    
    const MushMeshGroup::tSuperGroup& srcOne  = m_facetGroup.SuperGroup(1);
    const MushMeshGroup::tSuperGroup& srcZero = m_facetGroup.SuperGroup(0);
    
    glDisable(GL_CULL_FACE);
    float black[4] = {0,0,0,0};
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, black);
    glFogf(GL_FOG_START, 3.7);
    glFogf(GL_FOG_END, 4.3);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DITHER);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    GLState::BindTexture(m_textureRef.BindingNameGet());
    
    U32 colourNum=0;
    
    for (U32 i=0; i<srcOne.size(); ++i)
    {
        for (U32 j=0; j<srcOne[i].size(); ++j)
        {
            U32 zeroIndex = srcOne[i][j];
            
            
#if 1            
            GLState::ModulationSet(GLState::kModulationNone);
            GLState::BlendSet(GLState::kBlendAccumulate);
            GLState::TextureDisable();
            glEnable(GL_FOG);
            glBegin(GL_LINE_LOOP);
            
            for (U32 k=0; k<srcZero[zeroIndex].size(); ++k)
            {
                t3GLVal vert = preMatrix * vertices[srcZero[zeroIndex][k]];
                glColor4fv(&m_colours[colourNum].X());
                glVertex3fv(&vert.X());
            }
            glEnd(); 
#endif
#if 1
            
            GLState::ModulationSet(GLState::kModulationColour);
            GLState::BlendSet(GLState::kBlendAccumulate);
            glEnable(GL_FOG);
            GLState::TextureEnable();
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glBegin(GL_TRIANGLE_FAN);
            
            for (U32 k=0; k<srcZero[zeroIndex].size(); ++k)
            {
                t3GLVal vert = preMatrix * vertices[srcZero[zeroIndex][k]];
                t2GLVal texCoord = m_texCoords[srcZero[zeroIndex][k]];
                
                glColor4fv(&m_colours[colourNum].X());
                glTexCoord2fv(&texCoord.X());
                glVertex3fv(&vert.X());
            }
            glEnd(); 
            
            GLState::TextureDisable();
            
#endif
            
        }
        if (colourNum+1 < m_colours.size())
        {
            ++colourNum;
        }
    }
#endif
}

