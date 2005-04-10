//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerHypersphere.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KlSGDEnGkB9koN4E0FK9Tw
/*
 * $Id: TesseractTrainerHypersphere.cpp,v 1.5 2005/03/13 00:34:48 southa Exp $
 * $Log: TesseractTrainerHypersphere.cpp,v $
 * Revision 1.5  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.4  2005/02/26 17:53:47  southa
 * Plane sets and pairs
 *
 * Revision 1.3  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 * Revision 1.2  2005/02/03 21:03:10  southa
 * Build fixes
 *
 * Revision 1.1  2005/02/03 15:46:59  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerHypersphere.h"

#include "mushMushcore.h"

using namespace Mushware;
using namespace std;

TesseractTrainerHypersphere::TesseractTrainerHypersphere() :
    m_numVertices(0),
    m_renderFaces(0)
{
}

void
TesseractTrainerHypersphere::Create(tVal frame, const std::vector<Mushware::t4GLVal>& inColours)
{
    t4Val scale(0.2,0.2,0.2,0.2);
    scale *= 0.95;

    m_numVertices = MushcoreEnv::Sgl().VariableGet("TT_TEXTURE_POINTS").U32Get();

    m_vertexBuffer.ClearAndResize(m_numVertices);
    m_colourBuffer.ClearAndResize(m_numVertices);
    m_colourBuffer.MapReadWrite();
    m_vertices.resize(0);
    
    for (U32 i=0; i<m_numVertices; ++i)
    {
        tVertex vec(0,0,0,0);
        t4GLVal colour(1,1,1,1);
        {
            bool accept = true;

            do
            {
                for (U32 j=0; j<4; ++j)
                {
                    vec.Set(1-2*((double)rand()/RAND_MAX), j);
                }
                
                U32 type = (i*8 / m_numVertices) & ~1;

                if (type < inColours.size())
                {
                    colour = inColours[type];
                }
                
                switch (type)
                {
                    case 0:
                        vec.XSet(-1);
                        break;
                        
                    case 1:
                        vec.XSet(1);
                        break;
                        
                    case 2:
                        vec.YSet(-1);
                        break;
                        
                    case 3:
                        vec.YSet(1);
                        break;
                        
                    case 4:
                        vec.ZSet(-1);
                        break;
                        
                    case 5:
                        vec.ZSet(1);
                        break;
                        
                    case 6:
                        vec.WSet(-1);
                        break;
                        
                    case 7:
                        vec.WSet(1);
                        break;
                        
                    default:
                        colour = t4GLVal(1,1,1,0.2*((double)rand()/RAND_MAX));
                        break;
                }
            } while (!accept);
            

        }
        
        m_colourBuffer.Set(colour, i);
        m_vertices.push_back(vec);
    }
    
    m_colourBuffer.AttemptUnmap();

    glColorPointer(4, GL_FLOAT, 0, m_colourBuffer.AddrForGLGet());
    
    for (U32 i=0; i<m_numVertices; ++i)
    {
        m_vertices[i].InPlaceElementwiseMultiply(scale);
    }
}

void
TesseractTrainerHypersphere::Render(tVal frame)
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
    
    std::vector<tVertex> vertices(m_vertices);
    
    for (U32 j=0; j < m_numVertices; ++j)
    {
        m_orientation.InPlaceRotate(vertices[j]);
    }
    
    
    MushMeshPreMatrix<tVal, 4, 3> preMatrix
        (
         vec0, vec1, vec2
         );
    

    tVal distance = 4;

    t3GLVal vertOffset = t3GLVal(0,0,0*distance);
    
    glEnable(GL_FOG);

    GLState::BlendSet(GLState::kBlendTransparent);
    GLState::ColourSet(1,1,1,0.33);

    if (1)
    {
        for (U32 attempts=0;;)
        {
            m_vertexBuffer.MapReadWrite();
            for (U32 i=0; i<m_numVertices; ++i)
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

    m_vertexBuffer.Bind();
    glVertexPointer(3, GL_FLOAT, 0, m_vertexBuffer.AddrForGLGet());
    m_colourBuffer.Bind();
    glColorPointer(4, GL_FLOAT, 0, m_colourBuffer.AddrForGLGet());
    
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_POINTS, 0, vertices.size() * m_renderFaces / 8);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

}

