/*
 * $Id: GLLights.h,v 1.2 2002/10/08 11:58:52 southa Exp $
 * $Log: GLLights.h,v $
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
