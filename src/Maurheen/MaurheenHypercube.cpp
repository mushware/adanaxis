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
 * $Id: MaurheenWorm.cpp,v 1.2 2004/03/07 20:33:54 southa Exp $
 * $Log: MaurheenWorm.cpp,v $
 *
 */

#include "MaurheenHypercube.h"

using namespace Mushware;
using namespace std;

void
MaurheenHypercube::Create(tVal frame)
{
    tVal scale=0.2;
    for (U32 i=0; i<16; ++i)
    {
        m_vertices.push_back(t4GLVal(scale*(i%2)-(scale/2),
                                     scale*((i/2)%2)-(scale/2),
                                     scale*((i/4)%2)-(scale/2),
                                     scale*((i/8)%2)-(scale/2)));
        m_definition.push_back(t4U32(i%2, (i/2)%2, (i/4)%2, (i/8)%2));
    }
    
    for (U32 i=0; i<6; ++i)
    {
        MushMeshPreMatrix<tVal, 4, 4> rotate = MushMeshTools::RotateInAxis(i, cos((i+1)*(1.0+frame/30.0))*0.5*sin(frame/0.5));
        for (U32 j=0; j<16; ++j)
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
    

        
    for (U32 i=0; i<16; ++i)
    {
        for (U32 j=i+1; j<16; ++j)
        {
            U32 diffCount = 0;
            for (U32 k=0; k<4; ++k)
            {
                if (m_definition[i][k] == m_definition[j][k])
                {
                    ++diffCount;
                }
            }
            if (diffCount == 3)
            {
                if (m_definition[i].X() > 0 && m_definition[j].X() > 0 &&
                    m_definition[i].Y() > 0 && m_definition[j].Y() > 0)
                {
                    GLState::ColourSet(0.0,1.0,0.0,1.0);
                }
                else if (m_definition[i].X() > 0 && m_definition[j].X() > 0)
                {
                    GLState::ColourSet(1.0,0.0,0.0,1.0);
                }
                else if (m_definition[i].Y() > 0 && m_definition[j].Y() > 0)
                {
                    GLState::ColourSet(0.0,0.0,1.0,1.0);
                }
                else
                {
                    GLState::ColourSet(1.0,1.0,1.0,0.3);
                }
                glBegin(GL_LINES);

                t3GLVal start = preMatrix * m_vertices[i];
                t3GLVal end = preMatrix * m_vertices[j];
                    
                glVertex3fv(&start.X());
                glVertex3fv(&end.X());

                glEnd(); 
                //cout << start << ", " << end << endl;
            }
        }
    }
}

