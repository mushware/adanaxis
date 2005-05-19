//%includeGuardStart {
#ifndef GLLIGHTS_H
#define GLLIGHTS_H
//%includeGuardStart } DRkgI1OOoPC9U/rDXo+b9w
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLLights.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } O/xP6nvt+MZSqc/z0/Gy2Q
/*
 * $Id: GLLights.h,v 1.11 2004/01/06 20:46:49 southa Exp $
 * $Log: GLLights.h,v $
 * Revision 1.11  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.10  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.9  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:23  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
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
#include "mushMushcore.h"

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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
