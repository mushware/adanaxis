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
 * $Id$
 * $Log$
 */

#include "MaurheenWorm.h"

using namespace Mushware;
using namespace std;

void
MaurheenWorm::Create(tVal frame)
{
    m_length=10;
    m_order=5;
    m_vertices.SizeSet(t2U32(m_order+1, m_length));
    for (U32 x=0; x<m_order+1; ++x)
    {
        for (U32 y=0; y<m_length; ++y)
        {
            tVal angle=2*M_PI*x/m_order;
            tVal scale = 0.2*sin((M_PI * y) / (m_length-1));
            
            t3GLVal& vertex =  m_vertices.WRefGet(x,y);
            vertex.XSet(scale*sin(angle));
            vertex.YSet(1*((y - static_cast<tGLVal>(m_length)/2) / m_length));
            vertex.ZSet(scale*cos(angle));
        }
    }
}

void
MaurheenWorm::Render(void)
{
    U32 xSize = m_vertices.SizeGet().X();
    U32 ySize = m_vertices.SizeGet().Y();
    
    for (U32 y=0; y<ySize-1; ++y)
    {
#if 1
        glBegin(GL_TRIANGLE_STRIP);
        for (U32 x=0; x<xSize; ++x)
        {
            // cout << m_vertices.RefGet(x, y) << ", " << m_vertices.RefGet(x, y+1) << endl;
            glVertex3fv(&m_vertices.RefGet(x, y).X());
            glNormal3fv(&m_vertices.RefGet(x, y).X());
            glVertex3fv(&m_vertices.RefGet(x, y+1).X());
            glNormal3fv(&m_vertices.RefGet(x, y+1).Y());
       }
        glEnd();
#else
        glBegin(GL_LINES);
        for (U32 x=0; x<xSize-1; ++x)
        {
            // cout << m_vertices.RefGet(x, y) << ", " << m_vertices.RefGet(x, y+1) << endl;
            glVertex3fv(&m_vertices.RefGet(x, y).X());
            glVertex3fv(&m_vertices.RefGet(x, y+1).X());
            glVertex3fv(&m_vertices.RefGet(x, y+1).X());
            glVertex3fv(&m_vertices.RefGet(x+1, y).X());
            glVertex3fv(&m_vertices.RefGet(x+1, y).X());
            glVertex3fv(&m_vertices.RefGet(x, y).X());
            glVertex3fv(&m_vertices.RefGet(x, y+1).X());
            glVertex3fv(&m_vertices.RefGet(x+1, y+1).X());
        }
        glEnd();        
#endif
        
    }
}

