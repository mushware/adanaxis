#ifndef GLLIGHTS_H
#define GLLIGHTS_H
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
 * $Id: GLLights.h,v 1.4 2002/10/10 18:25:13 southa Exp $
 * $Log: GLLights.h,v $
 * Revision 1.4  2002/10/10 18:25:13  southa
 * Light links and test lights
 *
 * Revision 1.3  2002/10/08 17:13:16  southa
 * Tiered maps
 *
 * Revision 1.2  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.1  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
*/

#include "mushCore.h"
#include "GLStandard.h"

#include "GLLightDef.h"

class GLLights
{
public:
    enum
    {
        kMaxLights=8,
        kInvalidLight
    };
    GLLights();
    void LightAdd(U32 inNum, const GLLightDef& inDef);
    const GLLightDef& LightGet(U32 inNum);
    void LightEnable(U32 inNum);
    void LightDisable(U32 inNum);
    void DisableAll(void);
    void LightingFactorSet(tVal inFactor);
    void AmbientLightingSet(tVal inAmbient);
    void InvalidateAll(void);

private:
    U32 LightCache(U32 inNum);
    void CacheInvalidate(U32 inNum);
    
    class CacheEntry
    {
    public:
        U32 value;
        U32 age;
        bool enabled;
        bool modified;
    };
    vector<GLLightDef> m_lights;
    tVal m_lightingFactor;
    tVal m_ambientLighting;
    vector<CacheEntry> m_cache;
    U32 m_cacheTime;
};
#endif
