//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenWorm.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } uKWW6YpLXI8sGgYmUXtlaw
/*
 * $Id: MaurheenWorm.cpp,v 1.3 2005/05/19 13:02:07 southa Exp $
 * $Log: MaurheenWorm.cpp,v $
 * Revision 1.3  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.2  2004/03/07 20:33:54  southa
 * Graphics tuning
 *
 * Revision 1.1  2004/03/07 12:05:56  southa
 * Rendering work
 *
 */

#include "MaurheenWorm.h"

using namespace Mushware;
using namespace std;

void
MaurheenWorm::Create(tVal frame)
{
    m_length=20;
    m_order=40;
    m_vertices.SizeSet(t2U32(m_order+1, m_length));
    m_normals.SizeSet(t2U32(m_order+1, m_length));
    m_texCoords.SizeSet(t2U32(m_order+1, m_length));
    for (U32 x=0; x<m_order+1; ++x)
    {
        for (U32 y=0; y<m_length; ++y)
        {
            tVal angle=2*M_PI*x/m_order;
            tVal scale = (4.0+sin(frame+y/2.0))*0.06*sin((M_PI * y) / (m_length-1));
            
            t3GLVal& vertex =  m_vertices.WRefGet(x,y);
            vertex.XSet(scale*sin(angle));
            vertex.YSet(1*((y - static_cast<tGLVal>(m_length)/2) / m_length));
            vertex.ZSet(scale*cos(angle));

            t3GLVal& normal = m_normals.WRefGet(x,y);
            normal.XSet(sin(angle));
            normal.YSet(vertex.Y()/2);
            normal.ZSet(cos(angle));
            
            t2GLVal& texCoord =  m_texCoords.WRefGet(x,y);
            texCoord.XSet(0.8*(1-(1.0*x)/m_order));
            texCoord.YSet((1.0*y)/(m_length-1));
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
            glNormal3fv(&m_normals.RefGet(x, y).X());
            glTexCoord2fv(&m_texCoords.RefGet(x, y).X());
            glVertex3fv(&m_vertices.RefGet(x, y).X());
            glNormal3fv(&m_normals.RefGet(x, y+1).X());
            glTexCoord2fv(&m_texCoords.RefGet(x, y+1).X());
            glVertex3fv(&m_vertices.RefGet(x, y+1).X());
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

