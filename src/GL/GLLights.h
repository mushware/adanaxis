//%includeGuardStart {
#ifndef GLLIGHTS_H
#define GLLIGHTS_H
//%includeGuardStart } DRkgI1OOoPC9U/rDXo+b9w
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLLights.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } icylj/TvlLfBWaiCBdSgow
/*
 * $Id: GLLights.h,v 1.13 2006/06/01 15:38:51 southa Exp $
 * $Log: GLLights.h,v $
 * Revision 1.13  2006/06/01 15:38:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:01:59  southa
 * Mac release work
 *
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
