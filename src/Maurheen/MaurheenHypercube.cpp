//%Header {
/*****************************************************************************
*
* File: src/Maurheen/MaurheenWorm.cpp
*
* This file contains original work by Andy Southgate.  Contact details can be
* found at http://www.mushware.com/.  This file was placed in the Public
* Domain by Andy Southgate and Mushware Limited in 2002-2004.
*
* This software carries NO WARRANTY of any kind.
*
****************************************************************************/
//%Header } dnkP76FJ2EDluhnPYobJxw
/*
 * $Id: MaurheenHypercube.cpp,v 1.2 2004/11/17 23:43:47 southa Exp $
 * $Log: MaurheenHypercube.cpp,v $
 * Revision 1.2  2004/11/17 23:43:47  southa
 * Added outer product
 *
 * Revision 1.1  2004/10/31 23:34:06  southa
 * Hypercube rendering test
 *
 *
 */

#include "MaurheenHypercube.h"

#include "mushMushcore.h"

using namespace Mushware;
using namespace std;

void
MaurheenHypercube::Create(tVal frame)
{
    t4Val scale(0.2,0.2,0.20,0.2);
    tVal move=0.05;
    tVal move_1m = 1-move;
    
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
                                m_vertices.push_back(t4Val(vert[0]*scale[0], vert[1]*scale[1], vert[2]*scale[2], vert[3]*scale[3]));
                            }
                        }
                    }
                }
            }
        }
    }

    // File the zero order group (vertices in facets)
    m_facetGroup.OrderPush();
    for (U32 face=0; face<8; ++face)
    {
        t4Val centroid(0,0,0,0);
        for (U32 k=0; k<24; ++k)
        {
            centroid += m_vertices[face*24+k];
        }
        centroid /= 24;
        
        for (U32 facet=0; facet<6; ++facet)
        {
            m_facetGroup.GroupPush();
            
            U32 base=face*24+facet*4;
            m_facetGroup.IndexPush(base);
            m_facetGroup.IndexPush(base+1);
            m_facetGroup.IndexPush(base+3);
            m_facetGroup.IndexPush(base+2);
            
            for (U32 k=0; k<4; ++k)
            {
                m_vertices[base+k] *= move_1m;
                m_vertices[base+k] += move * centroid;
            }
        }
    }
    
    // fill the first order group (facets in facets)
    m_facetGroup.OrderPush();
    for (U32 face=0; face<8; ++face)
    {
        m_facetGroup.GroupPush();
        for (U32 facet=0; facet<6; ++facet)
        {
            m_facetGroup.IndexPush(face*6 + facet);
        }
    }
    
    for (U32 i=0; i<6; ++i)
    {
        MushMeshPreMatrix<tVal, 4, 4> rotate = MushMeshTools::RotateInAxis(i, cos((i+1)*(1.0+frame/30.0))*4*sin(frame/4));
        for (U32 j=0; j<m_vertices.size(); ++j)
        {
            m_vertices[j] = rotate * m_vertices[j];
        }
    }
}

void
MaurheenHypercube::Render(tVal frame)
{
    tVal ang0=0.0;
    tVal ang1=M_PI*(2.0/3);
    tVal ang2=M_PI*(4.0/3);
    
    
    MushMeshVector<tVal, 4> vec0(cos(ang0), cos(ang1), cos(ang2), 0);
    MushMeshVector<tVal, 4> vec1(sin(ang0), sin(ang1), sin(ang2), 0);
    MushMeshVector<tVal, 4> vec2(0, 0, 0, 1);
    
    if ((int)frame % 30 < 0)
    {
        vec0 = MushMeshVector<tVal, 4>(1,0,0,0);
        vec1 = MushMeshVector<tVal, 4>(0,1,0,0);
        vec2 = MushMeshVector<tVal, 4>(0,0,1,0);
    }        
    
    MushMeshPreMatrix<tVal, 4, 3> preMatrix
    (
        vec0, vec1, vec2
    );
    
    
    // orderOne iterator (which we don't iterate through) points to the face order grouping
    // This is a vector of vectors of indices.  Indices index into the orderZero array.
    // Each individual vector represents a face
    tFacetGroup::tOrderReverseIterator orderOne = m_facetGroup.OrderRBegin();
    
    
    // This iterator (which we don't iterate through) points to the facet order grouping
    // This is a vector of vectors of indices.  Indices index into the vertex array.
    // Each individual vector represents a facet
    tFacetGroup::tOrderIterator orderZero = m_facetGroup.OrderBegin();

    glDisable(GL_CULL_FACE);
    float black[4] = {0,0,0,0};
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, black);
    glFogf(GL_FOG_START,3.5);
    glFogf(GL_FOG_END,4.5);
    glFogi(GL_FOG_MODE,GL_LINEAR);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glShadeModel(GL_SMOOTH);

    tVal colour=100*sin(frame*0.001);
    
    // Iterator itrFace takes us through each face one by one.  *faceIter is a vector of facet indices
    for (tFacetGroup::tSuperGroupIterator itrFace = orderOne->begin(); itrFace != orderOne->end(); ++itrFace)
    {
        colour += sin(frame*0.0037);
        
        tVal red   = 0.5+0.5*cos(M_PI*(colour*1.03+frame*0.0071));
        tVal green = 0.5+0.5*cos(M_PI*(colour*1.07+frame*0.0113));
        tVal blue  = 0.5+0.5*cos(M_PI*(colour*1.11+frame*0.0157));
        tVal alpha  = 0.05+0.95*pow(0.5+0.5*sin(colour*3.31+frame*0.0093), 4);
        
        // Iterator itrSubFace takes us through each facet index for the face referred to by faceIter.
        // *itrSubFace is a facet index
        for (tFacetGroup::tGroupIterator itrSubFace = itrFace->begin(); itrSubFace != itrFace->end(); ++itrSubFace)
        {
            tFacetGroup::tGroup& facet = (*orderZero)[*itrSubFace];
#if 1
            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            GLState::ColourSet(red, green, blue, 0.1*alpha);
            glDisable(GL_FOG);
            glBegin(GL_TRIANGLE_FAN);
            
            for (tFacetGroup::tGroupIterator vertIter = facet.begin(); vertIter != facet.end(); ++vertIter)
            {

                t3GLVal vert = preMatrix * m_vertices[*vertIter];
                tVal scale = 1;
                GLState::ColourSet(scale*red, scale*green, scale*blue, 0.15*alpha);
                glVertex3fv(&vert.X());
            }
            glEnd(); 
#endif            
#if 1            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glEnable(GL_FOG);
            glBegin(GL_LINE_LOOP);
            
            for (tFacetGroup::tGroupIterator vertIter = facet.begin(); vertIter != facet.end(); ++vertIter)
            {
                
                t3GLVal vert = preMatrix * m_vertices[*vertIter];
                tVal scale = 1;
                GLState::ColourSet(scale*red, scale*green, scale*blue, 1.5*alpha);
                glVertex3fv(&vert.X());
            }
            glEnd(); 
#endif
        }
    }
}

