/*
 * $Id$
 * $Log$
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
    void Apply(void) const { GLUtils::SetColour(m_red, m_green, m_blue, m_alpha); }

private:
    tVal m_red;
    tVal m_green;
    tVal m_blue;
    tVal m_alpha;
};
