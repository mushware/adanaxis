//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenHypersphere.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } xxX+iSBjqDjjRTp/Knkivw
/*
 * $Id: MaurheenHypersphere.cpp,v 1.3 2005/01/26 00:48:46 southa Exp $
 * $Log: MaurheenHypersphere.cpp,v $
 */

#include "MaurheenHypersphere.h"

#include "mushMushcore.h"

#include "MushMeshDivide.h"

using namespace Mushware;
using namespace std;

void
MaurheenHypersphere::Create(tVal frame)
{
    t4Val scale(0.4,0.4,0.4,0.4);

    for (U32 i=0; i<10000; ++i)
    {
        tVertex vec(2,0,0,0);
        do
        {
            do
            {
                for (U32 j=0; j<4; ++j)
                {
                    vec.Set(1-2*((double)rand()/RAND_MAX), j);
                }
            } while (vec*vec > 1 || vec*vec < 0.01);
            
            MushMeshOps::Normalise(vec);
            
        } while (fabs(vec.X()) < 0.2 ||
                 fabs(vec.Y()) < 0.2 ||
                 fabs(vec.Z()) < 0.2 ||
                 fabs(vec.W()) < 0.2,0
                 );
        
        for (U32 j=0; j<4; ++j)
        {
            vec.Set(vec[j]*scale[j], j);
        }
        m_vertices.push_back(vec);
    }
}

void
MaurheenHypersphere::Render(tVal frame)
{
    tVal ang0=0.0;
    tVal ang1=M_PI*(2.0/3);
    tVal ang2=M_PI*(4.0/3);
    
    
    MushMeshVector<tVal, 4> vec0(cos(ang0), cos(ang1), cos(ang2), 0);
    MushMeshVector<tVal, 4> vec1(sin(ang0), sin(ang1), sin(ang2), 0);
    MushMeshVector<tVal, 4> vec2(0, 0, 0, 1);
    
    if ((int)frame % 60 > 30)
    {
        vec0 = MushMeshVector<tVal, 4>(1,0,0,0);
        vec1 = MushMeshVector<tVal, 4>(0,1,0,0);
        vec2 = MushMeshVector<tVal, 4>(0,0,0,1);
    }        
    
    std::vector<tVertex> vertices(m_vertices);
    
    for (U32 i=0; i<6; ++i)
    {
        MushMeshPreMatrix<tVal, 4, 4> rotate = MushMeshTools::RotateInAxis(i, cos((i+1)*(1.0+frame/30.0))*4*sin(frame/4));
        for (U32 j=0; j<vertices.size(); ++j)
        {
            vertices[j] = rotate * vertices[j];
        }
    }
    
    MushMeshPreMatrix<tVal, 4, 3> preMatrix
        (
         vec0, vec1, vec2
         );
    
    float black[4] = {0,0,0,0};
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, black);
    glFogf(GL_FOG_START,3.5);
    glFogf(GL_FOG_END,4.5);
    glFogi(GL_FOG_MODE,GL_LINEAR);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    GLState::ColourSet(1,1,1,0.33);

    glBegin(GL_POINTS);
    
    for (U32 i=0; i<vertices.size(); ++i)
    {
        t3GLVal vert = preMatrix * vertices[i];
        t4GLVal colour = m_vertices[i] + t4GLVal(0.5, 0.5, 0.5, 0.5);
        glColor3fv(&colour.X()); // Just use the first three; no alpha
        glVertex3fv(&vert.X());
    }
    
    glEnd();
    
    
}

