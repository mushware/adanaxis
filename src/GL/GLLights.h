#ifndef GLLIGHTS_H
#define GLLIGHTS_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLLights.h,v 1.5 2002/10/22 20:42:00 southa Exp $
 * $Log: GLLights.h,v $
 * Revision 1.5  2002/10/22 20:42:00  southa
 * Source conditioning
 *
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

#include "GLStandard.h"
#include "mushCore.h"

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
    void LightAdd(Mushware::U32 inNum, const GLLightDef& inDef);
    const GLLightDef& LightGet(Mushware::U32 inNum);
    void LightEnable(Mushware::U32 inNum);
    void LightDisable(Mushware::U32 inNum);
    void DisableAll(void);
    void LightingFactorSet(Mushware::tVal inFactor);
    void AmbientLightingSet(Mushware::tVal inAmbient);
    void InvalidateAll(void);

private:
    Mushware::U32 LightCache(Mushware::U32 inNum);
    void CacheInvalidate(Mushware::U32 inNum);
    
    class CacheEntry
    {
    public:
        Mushware::U32 value;
        Mushware::U32 age;
        bool enabled;
        bool modified;
    };
    std::vector<GLLightDef> m_lights;
    Mushware::tVal m_lightingFactor;
    Mushware::tVal m_ambientLighting;
    std::vector<CacheEntry> m_cache;
    Mushware::U32 m_cacheTime;
};
#endif
