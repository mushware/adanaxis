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
 * $Id: GLColour.h,v 1.4 2002/08/09 17:09:02 southa Exp $
 * $Log: GLColour.h,v $
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
    GLColour(tVal inRed, tVal inGreen, tVal inBlue, tVal inAlpha=1.0) :
        m_red(inRed),
        m_green(inGreen),
        m_blue(inBlue),
        m_alpha(inAlpha)
        {}
    void Apply(void) const { GLUtils::ColourSet(m_red, m_green, m_blue, m_alpha); }
    tVal RedGet(void) const { return m_red; }
    tVal GreenGet(void) const { return m_green; }
    tVal BlueGet(void) const { return m_blue; }
    tVal AlphaGet(void) const { return m_alpha; }
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);

    const GLColour& operator+=(const GLColour& inCol)
    {
        m_red+=inCol.m_red;
        m_green+=inCol.m_green;
        m_blue+=inCol.m_blue;
        m_alpha+=inCol.m_alpha;
        return *this;
    }
    const GLColour& operator*=(tVal inVal)
    {
        m_red*=inVal;
        m_green*=inVal;
        m_blue*=inVal;
        m_alpha*=inVal;
        return *this;
    }

private:
    tVal m_red;
    tVal m_green;
    tVal m_blue;
    tVal m_alpha;
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
