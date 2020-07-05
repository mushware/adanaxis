//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerPlaneSet.cpp
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
//%Header } brOTC149DY4wlZ+0YnGxlg
/*
 * $Id: TesseractTrainerPlaneSet.cpp,v 1.7 2006/06/01 15:40:00 southa Exp $
 * $Log: TesseractTrainerPlaneSet.cpp,v $
 * Revision 1.7  2006/06/01 15:40:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.5  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.4  2005/04/11 23:31:43  southa
 * Startup and registration screen
 *
 * Revision 1.3  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.2  2005/02/27 01:01:32  southa
 * Eigenplane markers
 *
 * Revision 1.1  2005/02/26 17:53:49  southa
 * Plane sets and pairs
 *
 */

#include "TesseractTrainerPlaneSet.h"

#include "TesseractTrainerPixelSource.h"

#include "mushMushcore.h"

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
        m_orientation.VectorRotate(vertices[j]);
    }
    
    const MushMeshGroup::tSuperGroup& srcOne  = m_facetGroup.SuperGroup(1);
    const MushMeshGroup::tSuperGroup& srcZero = m_facetGroup.SuperGroup(0);
    
    glDisable(GL_CULL_FACE);

    glEnable(GL_FOG);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DITHER);
    
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

