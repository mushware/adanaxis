/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

template<class RefType> class MediaRef
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
    mutable RefType *m_fontPtr;
};
