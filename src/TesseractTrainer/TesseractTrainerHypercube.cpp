//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerHypercube.cpp
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
//%Header } UPjbxJfVdMAA3pCMM5UD+w
/*
 * $Id: TesseractTrainerHypercube.cpp,v 1.9 2006/06/01 15:39:59 southa Exp $
 * $Log: TesseractTrainerHypercube.cpp,v $
 * Revision 1.9  2006/06/01 15:39:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.7  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.6  2005/04/11 23:31:42  southa
 * Startup and registration screen
 *
 * Revision 1.5  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.4  2005/02/26 17:53:46  southa
 * Plane sets and pairs
 *
 * Revision 1.3  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 * Revision 1.2  2005/02/03 21:03:10  southa
 * Build fixes
 *
 * Revision 1.1  2005/02/03 15:46:58  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerHypercube.h"

#include "TesseractTrainerPixelSource.h"

#include "mushMushcore.h"

using namespace Mushware;
using namespace std;

void
TesseractTrainerHypercube::Create(tVal frame, const std::vector<Mushware::t4GLVal>& inColours)
{
    m_colours = inColours;
    
    t4Val scale(0.2,0.2,0.2,0.2);
    tVal move=0.05;
    tVal move_1m = 1-move;
    MushMeshGroup buildGroup;
    std::vector<tVertex> buildVertices;
    std::vector<t2Val> buildTexCoords;
    
    for (U32 face=0; face<8; ++face)
    {
        t4Val vert;
        vert.Set((face%2)?1:-1, face/2);

        for (U32 facet=0; facet<8; ++facet)
        {
            if (face / 2 != facet / 2)
            {
                vert.Set((facet%2)?1:-1, facet/2);

                for (U32 square=0; square<8; ++square)
                {
                    if (face / 2 != square / 2 &&
                        facet / 2 != square / 2)
                    {
                        vert.Set((square%2)?1:-1, square/2);
                        
                        for (U32 line=square; line<8; ++line)
                        {
                            if (face / 2 != line / 2 &&
                                facet / 2 != line / 2 &&
                                square / 2 != line / 2)
                            {
                                vert.Set((line%2?1:-1), line/2);
                                buildVertices.push_back(vert.ElementwiseProduct(scale));
                            }
                        }
                    }
                }
            }
        }
    }

    // File the zero order group (vertices in facets)
    buildGroup.SuperGroupPush();
    for (U32 face=0; face<8; ++face)
    {
        t4Val centroid(0,0,0,0);
        for (U32 k=0; k<24; ++k)
        {
            centroid += buildVertices[face*24+k];
        }
        centroid /= 24;
        
        for (U32 facet=0; facet<6; ++facet)
        {
            buildGroup.GroupPush();
            
            U32 base=face*24+facet*4;
            buildGroup.ValuePush(base);
            buildGroup.ValuePush(base+1);
            buildGroup.ValuePush(base+3);
            buildGroup.ValuePush(base+2);
            
            for (U32 k=0; k<4; ++k)
            {
                buildVertices[base+k] *= move_1m;
                buildVertices[base+k] += move * centroid;
            }
        }
    }
    
    // fill the first order group (facets in facets)
    buildGroup.SuperGroupPush();
    for (U32 face=0; face<8; ++face)
    {
        buildGroup.GroupPush();
        for (U32 facet=0; facet<6; ++facet)
        {
            buildGroup.ValuePush(face*6 + facet);
        }
    }
    
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
    //MushMeshDivide::Divide(buildVertices2, buildGroup2, buildVertices, buildGroup, 0.5);
    //MushMeshDivide::Divide(m_vertices, m_facetGroup, buildVertices, buildGroup, 0.5);


    
#if 0
    for (U32 i=0; i<m_vertices.size(); i += 4)
    {
        tVertex centroid(0,0,0,0);
        for (U32 j=0; j<4; ++j)
        {
            centroid += m_vertices[j+i]/4;
        }
        for (U32 j=0; j<4; ++j)
        {
            m_vertices[j+i] = 0.95*m_vertices[j+i]+0.05*centroid;
        }
    }
#endif
    
    
    
    // Create texture
    TesseractTrainerPixelSource pixelSource;
    
    MushcoreData<GLTexture>::Sgl().Give("texproc1", new GLTextureProc(pixelSource));
    m_textureRef.NameSet("texproc1");
}

void
TesseractTrainerHypercube::Render(tVal frame)
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
    
    std::vector<tVertex> vertices(m_vertices);
    
    for (U32 j=0; j<vertices.size(); ++j)
    {
        m_orientation.VectorRotate(vertices[j]);
    }
    
    const MushMeshGroup::tSuperGroup& srcOne = m_facetGroup.SuperGroup(1);
 
    glDisable(GL_CULL_FACE);

    glEnable(GL_FOG);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DITHER);
    
    GLState::BindTexture(m_textureRef.Get()->BindingNameGet());
    
    U32 colourNum=0;
    U32 faceNum=0;
    
    for (MushMeshGroup::tSuperGroupConstItr itrSrcFace = srcOne.begin(); itrSrcFace != srcOne.end(); ++itrSrcFace)
    {
        ++faceNum;
        if (faceNum > m_renderFaces) break;
        
        // Iterator itrSubFace takes us through each facet index for the face referred to by faceIter.
        // *itrSubFace is a facet index
        for (MushMeshGroup::tGroupConstItr itrSrcFacet = itrSrcFace->begin(); itrSrcFacet != itrSrcFace->end(); ++itrSrcFacet)
        {
            const MushMeshGroup::tGroup& facet = m_facetGroup.GroupAtSuperGroupGroup(0, *itrSrcFacet);

            if (m_renderFaceOutlines)
            {
                GLState::ModulationSet(GLState::kModulationNone);
                GLState::BlendSet(GLState::kBlendAccumulate);
                GLState::TextureDisable();
                glEnable(GL_FOG);
                glBegin(GL_LINE_LOOP);
                
                for (MushMeshGroup::tGroupConstItr vertIter = facet.begin(); vertIter != facet.end(); ++vertIter)
                {
                    
                    t3GLVal vert = preMatrix * vertices[*vertIter];
                    glColor4fv(&m_colours[colourNum].X());
                    glVertex3fv(&vert.X());
                }
                glEnd(); 
            }
            
            if (m_renderFaceTextures)
            {
                GLState::ModulationSet(GLState::kModulationColour);
                GLState::BlendSet(GLState::kBlendAccumulate);
                glEnable(GL_FOG);
                GLState::TextureEnable();
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                glBegin(GL_TRIANGLE_FAN);
                
                for (U32 i=0; i<facet.size(); ++i)
                {
                    t3GLVal vert = preMatrix * vertices[facet[i]];
                    t2GLVal texCoord = m_texCoords[i];

                    glColor4fv(&m_colours[colourNum].X());
                    glTexCoord2fv(&texCoord.X());
                    glVertex3fv(&vert.X());
                }
                glEnd(); 
                
                GLState::TextureDisable();
            }
            
        }
        
        if (colourNum+1 < m_colours.size())
        {
            ++colourNum;
        }
    }

}

