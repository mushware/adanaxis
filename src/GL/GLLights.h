/*
 * $Id: GLLights.h,v 1.1 2002/10/06 22:09:58 southa Exp $
 * $Log: GLLights.h,v $
 * Revision 1.1  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
*/

#include "mushCore.h"
#include "GLStandard.h"

class GLLightDef;

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
    void LightingFactorSet(tVal inFactor) { m_lightingFactor = inFactor; InvalidateAll(); }
    void AmbientLightingSet(tVal inAmbient) { m_ambientLighting = inAmbient; InvalidateAll(); }

private:
    U32 LightCache(U32 inNum);
    void CacheInvalidate(U32 inNum);
    void InvalidateAll(void);
    
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
