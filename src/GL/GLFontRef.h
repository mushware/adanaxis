#ifndef GLFONTREF_H
#define GLFONTREF_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
* $Id: GLFontRef.h,v 1.3 2002/08/27 08:56:19 southa Exp $
* $Log: GLFontRef.h,v $
* Revision 1.3  2002/08/27 08:56:19  southa
* Source conditioning
*
* Revision 1.2  2002/08/09 17:09:02  southa
* GameDialogue added
*
* Revision 1.1  2002/08/08 13:39:09  southa
* Text rendering
*
*/

#include "mushCore.h"

class GLFont;

class GLFontRef
{
public:
    GLFontRef(): m_fontPtr(NULL) {}
    explicit GLFontRef(const string& inName, tVal inSize=1.0): m_name(inName), m_size(inSize), m_fontPtr(NULL) {}
    void NameSet(const string& inName) {m_name=inName; m_fontPtr=NULL;}
    const string& NameGet(void) const {return m_name;}
    tVal SizeGet(void) const {return m_size;}
    GLFont *FontGet(void) const;
    bool Exists(void) const;

private:
    void GetReference(void) const;
    string m_name;
    tVal m_size;
    mutable GLFont *m_fontPtr;
};
#endif
