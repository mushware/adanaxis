#ifndef GLCOLOUR_H
#define GLCOLOUR_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: GLColour.h,v 1.5 2002/08/27 08:56:19 southa Exp $
 * $Log: GLColour.h,v $
 * Revision 1.5  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/09 17:09:02  southa
 * GameDialogue added
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

#include "mushCore.h"
#include "GLUtils.h"

class GLColour
{
public:
    GLColour() {}
    GLColour(tVal inRed, tVal inGreen, tVal inBlue, tVal inAlpha=1.0)
    {
        m_col[0]=inRed;
        m_col[1]=inGreen;
        m_col[2]=inBlue;
        m_col[3]=inAlpha;
    }
    void Apply(void) const { GLUtils::ColourSet(m_col[0], m_col[1], m_col[2], m_col[3]); }
    tVal RedGet(void) const { return m_col[0]; }
    tVal GreenGet(void) const { return m_col[1]; }
    tVal BlueGet(void) const { return m_col[2]; }
    tVal AlphaGet(void) const { return m_col[3]; }
    typedef GLfloat tGLfloat4[4];
    const tGLfloat4& ArrayGet(void) const { return m_col; }
    
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);

    const GLColour& operator+=(const GLColour& inCol)
    {
        m_col[0]+=inCol.m_col[0];
        m_col[1]+=inCol.m_col[1];
        m_col[2]+=inCol.m_col[2];
        m_col[3]+=inCol.m_col[3];
        return *this;
    }
    const GLColour& operator*=(tVal inVal)
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

inline const GLColour operator*(const GLColour& a, tVal b)
{
    GLColour retCol(a);
    return retCol*=b;
}

inline const GLColour operator*(tVal a, const GLColour& b)
{
    GLColour retCol(b);
    return retCol*=a;
}

#endif
