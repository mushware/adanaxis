/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GLModeDef;

class PlatformVideoUtils
{
public:
    PlatformVideoUtils();
    static PlatformVideoUtils& Instance(void) {return *((m_instance==NULL)?m_instance=new PlatformVideoUtils:m_instance);}
    const GLModeDef& ModeDefGet(U32 inNum);

private:
    vector<GLModeDef> m_modeDefs;
    static PlatformVideoUtils *m_instance;
};
