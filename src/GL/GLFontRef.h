/*
* $Id: GLFontRef.h,v 1.1 2002/08/08 13:39:09 southa Exp $
* $Log: GLFontRef.h,v $
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
