//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerHypercube.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } tvE8OYNg7opzgRevdZ3rwA
/*
 * $Id$
 * $Log$
 */

#include "TesseractTrainerHypercube.h"

#include "mushMushcore.h"

#include "MushMeshDivide.h"

using namespace Mushware;
using namespace std;

void
TesseractTrainerHypercube::Create(tVal frame)
{
    t4Val scale(0.2,0.2,0.20,0.2);
    tVal move=0.05;
    tVal move_1m = 1-move;
    MushMeshGroup buildGroup;
    std::vector<tVertex> buildVertices;

    
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
                                buildVertices.push_back(t4Val(vert[0]*scale[0], vert[1]*scale[1], vert[2]*scale[2], vert[3]*scale[3]));
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
    
#if 1
    
    std::vector<tVertex> vertices(m_vertices);
    
    for (U32 i=0; i<6; ++i)
    {
        MushMeshPreMatrix<tVal, 4, 4> rotate = MushMeshTools::RotateInAxis(i, cos((i+1)*(1.0+frame/30.0))*4*sin(frame/4));
        for (U32 j=0; j<vertices.size(); ++j)
        {
            vertices[j] = rotate * vertices[j];
        }
    }
    

    
    
    const MushMeshGroup::tSuperGroup& srcOne = m_facetGroup.SuperGroup(1);
 
    glDisable(GL_CULL_FACE);
    float black[4] = {0,0,0,0};
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, black);
    glFogf(GL_FOG_START, 3.7);
    glFogf(GL_FOG_END, 4.3);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glShadeModel(GL_SMOOTH);

    tVal colour=0;
    
    for (MushMeshGroup::tSuperGroupConstItr itrSrcFace = srcOne.begin(); itrSrcFace != srcOne.end(); ++itrSrcFace)
    {
        colour += 1;
        
        tVal red   = 0.5+0.5*(cos(4*M_PI*cos(M_PI*colour*0.117)*sin(frame*0.013)));
        tVal green = 0.5+0.5*(cos(4*M_PI*cos(M_PI*colour*0.137)*sin(frame*0.017)));
        tVal blue  = 1 - red;//pow(cos(M_PI*(colour*0.625+frame*0.0157)), 2);
        tVal alpha  = 0.05+0.95*pow(sin(4*M_PI*cos(M_PI*colour*0.25)*sin(frame*0.01)), 4);
        
        red = green = blue = 1;
        alpha = 0.5;
        
        if (colour == 1)
        {
            blue = green = 0.5;
        }
        else if (colour == 3)
        {
            red = blue = 0.5;
        }
        else if (colour == 5)
        {
            red = green = 0.5;
        }
        else
        {
            
        }
        // Iterator itrSubFace takes us through each facet index for the face referred to by faceIter.
        // *itrSubFace is a facet index
        for (MushMeshGroup::tGroupConstItr itrSrcFacet = itrSrcFace->begin(); itrSrcFacet != itrSrcFace->end(); ++itrSrcFacet)
        {
            const MushMeshGroup::tGroup& facet = m_facetGroup.GroupAtSuperGroupGroup(0, *itrSrcFacet);

#if 1            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glEnable(GL_FOG);
            glBegin(GL_LINE_LOOP);
            
            for (MushMeshGroup::tGroupConstItr vertIter = facet.begin(); vertIter != facet.end(); ++vertIter)
            {
                
                t3GLVal vert = preMatrix * vertices[*vertIter];
                tVal scale = 1;
                GLState::ColourSet(scale*red, scale*green, scale*blue, 1.5*alpha);
                glVertex3fv(&vert.X());
            }
            glEnd(); 
#endif
#if 1
            
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            GLState::ColourSet(red, green, blue, 0.1*alpha);
            glEnable(GL_FOG);
            glBegin(GL_TRIANGLE_FAN);
            
            for (MushMeshGroup::tGroupConstItr vertIter = facet.begin(); vertIter != facet.end(); ++vertIter)
            {
                
                t3GLVal vert = preMatrix * vertices[*vertIter];
                tVal scale = 1;
                GLState::ColourSet(scale*red, scale*green, scale*blue, 0.15*alpha);
                glVertex3fv(&vert.X());
            }
            glEnd(); 
#endif            
        }
    }
#endif
}

