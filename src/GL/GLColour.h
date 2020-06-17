//%includeGuardStart {
#ifndef GLCOLOUR_H
#define GLCOLOUR_H
//%includeGuardStart } MYzbFxu3DP+5yIuQQQRoPg
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLColour.h
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
//%Header } 2cIFi7vKrrNNtqyU+7c/pA
/*
 * $Id: GLColour.h,v 1.21 2006/06/01 20:12:58 southa Exp $
 * $Log: GLColour.h,v $
 * Revision 1.21  2006/06/01 20:12:58  southa
 * Initial texture caching
 *
 * Revision 1.20  2006/06/01 15:38:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.19  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.18  2005/03/25 19:13:48  southa
 * GameDialogue work
 *
 * Revision 1.17  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.16  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.15  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.14  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:08:19  southa
 * Fixed file headers
 *
 * Revision 1.12  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.11  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.9  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 * Revision 1.6  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.5  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/09 17:09:02  southa
 * InfernalDialogue added
 *
 * Revision 1.3  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.2  2002/08/01 16:47:09  southa
 * First multi-box collsion checking
 *
 * Revision 1.1  2002/07/18 11:40:34  southa
 * Overplotting and movement
 *
 */

#include "GLState.h"
#include "mushMushcore.h"

#include "mushMushMesh.h"

class GLColour
{
public:
    GLColour() {}
    GLColour(Mushware::tVal inRed, Mushware::tVal inGreen, Mushware::tVal inBlue, Mushware::tVal inAlpha=1.0)
    {
        m_col[0]=inRed;
        m_col[1]=inGreen;
        m_col[2]=inBlue;
        m_col[3]=inAlpha;
    }
    virtual ~GLColour() {}

    void Apply(void) const { GLState::ColourSet(m_col[0], m_col[1], m_col[2], m_col[3]); }
    Mushware::tVal RedGet(void) const { return m_col[0]; }
    Mushware::tVal GreenGet(void) const { return m_col[1]; }
    Mushware::tVal BlueGet(void) const { return m_col[2]; }
    Mushware::tVal AlphaGet(void) const { return m_col[3]; }
    typedef GLfloat tGLfloat4[4];
    const tGLfloat4& ArrayGet(void) const { return m_col; }
    
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);

    const GLColour& operator+=(const GLColour& inCol)
    {
        m_col[0]+=inCol.m_col[0];
        m_col[1]+=inCol.m_col[1];
        m_col[2]+=inCol.m_col[2];
        m_col[3]+=inCol.m_col[3];
        return *this;
    }
    const GLColour& operator*=(Mushware::tVal inVal)
    {
        m_col[0]*=inVal;
        m_col[1]*=inVal;
        m_col[2]*=inVal;
        m_col[3]*=inVal;
        return *this;
    }

private:
    GLfloat m_col[4];
};

inline const GLColour operator+(const GLColour& a, const GLColour& b)
{
    GLColour retCol(a);
    return retCol+=b;
}

inline const GLColour operator*(const GLColour& a, Mushware::tVal b)
{
    GLColour retCol(a);
    return retCol*=b;
}

inline const GLColour operator*(Mushware::tVal a, const GLColour& b)
{
    GLColour retCol(b);
    return retCol*=a;
}

inline std::ostream&
operator<<(std::ostream& ioOut, const GLColour& inCol)
{
    Mushware::t4Val valueVec(inCol.RedGet(), inCol.GreenGet(), inCol.BlueGet(), inCol.AlphaGet());
    
    ioOut << valueVec;
    
    return ioOut;
}

inline void
operator>>(MushcoreXMLIStream& ioIn, GLColour& outObj)
{
    Mushware::t4Val valueVec;
    
    ioIn >> valueVec;

    outObj = GLColour(valueVec[0], valueVec[1], valueVec[2], valueVec[3]);
}

inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const GLColour& inCol)
{
    Mushware::t4Val valueVec(inCol.RedGet(), inCol.GreenGet(), inCol.BlueGet(), inCol.AlphaGet());

    ioOut << valueVec;
    
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
