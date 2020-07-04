//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenWorm.cpp
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
//%Header } kyLSzdUBBM75RiV7t4FOCA
/*
 * $Id: MaurheenWorm.cpp,v 1.4 2006/06/01 15:39:12 southa Exp $
 * $Log: MaurheenWorm.cpp,v $
 * Revision 1.4  2006/06/01 15:39:12  southa
 * DrawArray verification and fixes
 *
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

