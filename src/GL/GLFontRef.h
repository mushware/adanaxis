#ifndef GLFONTREF_H
#define GLFONTREF_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
* $Id: GLFontRef.h,v 1.7 2003/01/11 13:03:11 southa Exp $
* $Log: GLFontRef.h,v $
* Revision 1.7  2003/01/11 13:03:11  southa
* Use Mushcore header
*
* Revision 1.6  2002/12/29 20:30:52  southa
* Work for gcc 3.1 build
*
* Revision 1.5  2002/12/20 13:17:35  southa
* Namespace changes, licence changes and source conditioning
*
* Revision 1.4  2002/10/22 20:42:00  southa
* Source conditioning
*
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

#include "Mushcore.h"

class GLFont;

class GLFontRef
{
public:
    GLFontRef(): m_fontPtr(NULL) {}
    explicit GLFontRef(const std::string& inName, Mushware::tVal inSize=1.0): m_name(inName), m_size(inSize), m_fontPtr(NULL) {}
    void NameSet(const std::string& inName) {m_name=inName; m_fontPtr=NULL;}
    const std::string& NameGet(void) const {return m_name;}
    Mushware::tVal SizeGet(void) const {return m_size;}
    GLFont *FontGet(void) const;
    bool Exists(void) const;

private:
    void GetReference(void) const;
    std::string m_name;
    Mushware::tVal m_size;
    mutable GLFont *m_fontPtr;
};
#endif
