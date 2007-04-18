//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenHypersphere.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } euHbxQfJureYfD9qAKmzAw
/*
 * $Id: MaurheenHypersphere.cpp,v 1.7 2006/06/01 15:39:12 southa Exp $
 * $Log: MaurheenHypersphere.cpp,v $
 * Revision 1.7  2006/06/01 15:39:12  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.5  2005/02/03 21:02:57  southa
 * Build fixes
 *
 * Revision 1.4  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.3  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 * Revision 1.2  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
 * Revision 1.1  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 */

#include "MaurheenHypersphere.h"

#include "mushMushcore.h"

#include "MushMeshDivide.h"

using namespace Mushware;
using namespace std;

MaurheenHypersphere::MaurheenHypersphere()
{
}

void
MaurheenHypersphere::Create(tVal frame)
{
    t4Val scale(0.4,0.4,0.4,0.4);

    m_vertexBuffer.ClearAndResize(kNumVertices);
    m_colourBuffer.ClearAndResize(kNumVertices);
    
    for (U32 i=0; i<kNumVertices; ++i)
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
            
            //MushMeshOps::Normalise(vec);
            
        } while (fabs(vec.X()) < 0.15 ||
                 fabs(vec.Y()) < 0.15 ||
                 fabs(vec.Z()) < 0.15 ||
                 fabs(vec.W()) < 0.15, 0
                 );

        m_vertices.push_back(vec);
    }
    
    t4GLVal colourOffset = t4GLVal(0.5, 0.5, 0.5, 0.5);
    
    for (U32 attempts=0;;)
    {
        m_colourBuffer.MapReadWrite();
        for (U32 i=0; i<kNumVertices; ++i)
        {
            t4GLVal colour = m_vertices[i]*1 + colourOffset;
            colour.WSet(0.2+0.8*(double)(rand())/RAND_MAX);
            if (fabs(m_vertices[i].X()) < 0.5 &&
                fabs(m_vertices[i].Y()) < 0.5 &&
                fabs(m_vertices[i].Z()) < 0.5 &&
                fabs(m_vertices[i].W()) < 0.5)
            {
                colour.WSet(1);
            }
            else
            {
                colour.WSet(0.1);
            }
            
                
            m_colourBuffer.Set(colour, i);
        }
        if (m_colourBuffer.AttemptUnmap()) break;
        if (attempts++ > 100) throw MushcoreRequestFail("Cannot unmap");
    }
    glColorPointer(4, GL_FLOAT, 0, m_colourBuffer.AddrForGLGet());
    
    for (U32 i=0; i<kNumVertices; ++i)
    {
        for (U32 j=0; j<4; ++j)
        {
            m_vertices[i].Set(m_vertices[i][j]*scale[j], j);
        }
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
    
    if ((int)frame % 60 > 60)
    {
        vec0 = MushMeshVector<tVal, 4>(1,0,0,0);
        vec1 = MushMeshVector<tVal, 4>(0,1,0,0);
        vec2 = MushMeshVector<tVal, 4>(0,0,0,1);
    }        
    
    static std::vector<tVertex> vertices(m_vertices.size());
    
    t4x4Val rotate(t4x4Val::Identity());
    
    for (U32 i=0; i<6; ++i)
    {
        rotate = MushMeshTools::MatrixRotateInAxis(i, cos((i+1)*(1.0+frame/30.0))*4*sin(frame/4)) * rotate;
    }
    
    if (1)
    {
        for (U32 j=0; j<vertices.size(); ++j)
        {
            vertices[j] = rotate * m_vertices[j];
        }
    }
    
    MushMeshPreMatrix<tVal, 4, 3> preMatrix
        (
         vec0, vec1, vec2
         );
    

    tVal distance = 4;

    t3GLVal vertOffset = t3GLVal(0,0,0*distance);
    
    float black[4] = {0,0,0,0};
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, black);
    glFogf(GL_FOG_START, 3.7);
    glFogf(GL_FOG_END, 4.3);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    GLState::ColourSet(1,1,1,0.33);

    if (1)
    {
        for (U32 attempts=0;;)
        {
            m_vertexBuffer.MapReadWrite();
            for (U32 i=0; i<kNumVertices; ++i)
            {
                m_vertexBuffer.Set(vertOffset + preMatrix * vertices[i], i);
            }
            if (m_vertexBuffer.AttemptUnmap())
            {
                break;
            }
            if (attempts++ > 100) throw MushcoreRequestFail("Cannot unmap");
        }
    }

    glVertexPointer(3, GL_FLOAT, 0, m_vertexBuffer.AddrForGLGet());
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glDrawArrays(GL_POINTS, 0, vertices.size());

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

}

