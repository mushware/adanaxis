//%includeGuardStart {
#ifndef GLFONTREF_H
#define GLFONTREF_H
//%includeGuardStart } wUK6hMbgy/tpf0fSBXIhYw
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLFontRef.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nAX018VRFSthbRWjHMLK1w
/*
* $Id: GLFontRef.h,v 1.8 2003/08/21 23:08:21 southa Exp $
* $Log: GLFontRef.h,v $
* Revision 1.8  2003/08/21 23:08:21  southa
* Fixed file headers
*
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
