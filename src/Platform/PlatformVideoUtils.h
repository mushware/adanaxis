/*
 * $Id: PlatformVideoUtils.h,v 1.1 2002/10/14 18:13:18 southa Exp $
 * $Log: PlatformVideoUtils.h,v $
 * Revision 1.1  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 */

#include "mushCore.h"

class GLModeDef;

class PlatformVideoUtils
{
public:
    PlatformVideoUtils();
    static PlatformVideoUtils& Instance(void) {return *((m_instance==NULL)?m_instance=new PlatformVideoUtils:m_instance);}
    const GLModeDef& ModeDefGet(U32 inNum);
    U32 PreviousModeDef(U32 inNum) const;
    U32 NextModeDef(U32 inNum) const;
    U32 DefaultModeGet(void) const;
    void RenderModeInfo(U32 inNum) const;
    static void VBLWait(void);
    
private:
    vector<GLModeDef> m_modeDefs;
    static PlatformVideoUtils *m_instance;
};
