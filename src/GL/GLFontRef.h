/*
* $Id$
* $Log$
*/

#include "mushCore.h"

class GLFont;

class GLFontRef
{
public:
    GLFontRef(): m_fontPtr(NULL) {}
    GLFontRef(const string& inName): m_name(inName), m_fontPtr(NULL) {}
    void NameSet(const string& inName) {m_name=inName; m_fontPtr=NULL;}
    const string& NameGet(void) const {return m_name;}
    GLFont *FontGet(void) const;
    bool Exists(void) const;

private:
    void GetReference(void) const;
    string m_name;
    mutable GLFont *m_fontPtr;
};

