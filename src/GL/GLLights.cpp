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
 * $Id: GLLights.cpp,v 1.11 2002/12/20 13:17:35 southa Exp $
 * $Log: GLLights.cpp,v $
 * Revision 1.11  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.9  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.8  2002/10/11 14:01:10  southa
 * Lighting work
 *
 * Revision 1.7  2002/10/10 22:47:57  southa
 * Full light definitions
 *
 * Revision 1.6  2002/10/10 18:25:13  southa
 * Light links and test lights
 *
 * Revision 1.5  2002/10/08 17:13:16  southa
 * Tiered maps
 *
 * Revision 1.4  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.3  2002/10/07 17:49:44  southa
 * Multiple values per map element
 *
 * Revision 1.2  2002/10/07 12:15:35  southa
 * First specular lighting
 *
 * Revision 1.1  2002/10/06 22:09:58  southa
 * Initial lighting test
 *
 */

#include "GLLights.h"

#include "GLLightDef.h"
#include "GLUtils.h"

using namespace Mushware;
using namespace std;

GLLights::GLLights() :
    m_lightingFactor(1.0),
    m_ambientLighting(0.2)
{
    CacheEntry entry;
    entry.value=kInvalidLight;
    entry.age=0;
    entry.enabled=false;
    entry.modified=false;
    
    m_cache.resize(kMaxLights, entry);
    m_cacheTime=1;
}

void
GLLights::AmbientLightingSet(tVal inAmbient)
{
    if (m_ambientLighting != inAmbient)
    {
        InvalidateAll();
    }
    m_ambientLighting = inAmbient;
}

void
GLLights::LightingFactorSet(tVal inFactor)
{
    if (m_lightingFactor != inFactor)
    {
        InvalidateAll();
    }
    m_lightingFactor = inFactor;
}

void
GLLights::LightAdd(U32 inNum, const GLLightDef& inDef)
{
    GLint numLights;
    glGetIntegerv(GL_MAX_LIGHTS, &numLights);
    COREASSERT(numLights >= kMaxLights);

    if (inNum < m_lights.size())
    {
        CacheInvalidate(inNum);
    }
    if (inNum >= m_lights.size())
    {
        m_lights.resize(inNum+1);
    }
    m_lights[inNum]=inDef;
}

const GLLightDef&
GLLights::LightGet(U32 inNum)
{
    if (inNum >= m_lights.size())
    {
        throw(ReferenceFail("Light number too big"));
    }
    return m_lights[inNum];
}

void
GLLights::LightEnable(U32 inNum)
{
    U32 slot;

    try
    {
        slot=LightCache(inNum);
    }
    catch (ResourceFail& e)
    {
        cerr << "Lighting fail: " << e.what() << endl;
        return;
    }

    COREASSERT(slot < kMaxLights);
    
    GLenum lightEnum=GL_LIGHT0+slot;
    COREASSERT(m_cache[slot].value == inNum);

    const GLLightDef& def = m_lights[inNum];
    
    if (m_cache[slot].modified)
    {
        glLightfv(lightEnum, GL_AMBIENT, def.AmbientGet().ArrayGet());
        glLightfv(lightEnum, GL_DIFFUSE, def.DiffuseGet().ArrayGet());
        glLightfv(lightEnum, GL_SPECULAR, def.SpecularGet().ArrayGet());

        glLightf(lightEnum, GL_SPOT_CUTOFF, def.CutoffGet());
        const GLVector& dir=def.DirectionGet();
        GLfloat direction[3]={dir.x, dir.y, dir.z};
        glLightfv(lightEnum, GL_SPOT_DIRECTION, direction);
        glLightf(lightEnum, GL_SPOT_EXPONENT, def.ExponentGet());
        glLightf(lightEnum, GL_CONSTANT_ATTENUATION, def.ConstantGet());
        glLightf(lightEnum, GL_LINEAR_ATTENUATION, def.LinearGet());
        glLightf(lightEnum, GL_QUADRATIC_ATTENUATION, def.QuadraticGet());
        m_cache[slot].modified=false;
        // cerr << "Wrote data for light " << inNum << " to slot " << slot << endl;
    }        

    const GLVector& pos = def.PositionGet();
    GLfloat position[4]={pos.x, pos.y, pos.z, 1};
    glLightfv(lightEnum, GL_POSITION, position);
    
    if (!m_cache[slot].enabled)
    {
        m_cache[slot].enabled=true;
        glEnable(lightEnum);
    }
    GLUtils::CheckGLError();
}    

U32
GLLights::LightCache(U32 inNum)
{
    if (inNum >= m_lights.size())
    {
        throw(LogicFail("Light number too big"));
    }
    
    for (U32 i=0; i<kMaxLights; ++i)
    {
        if (m_cache[i].value == inNum)
        {
            return i;
        }
    }
    // Throw out an old cache entry
    U32 slot=0;
    U32 slotAge=0;
    bool found=false;
    for (U32 i=0; i<kMaxLights; ++i)
    {
        if (!m_cache[i].enabled)
        {
            // Found free slot
            if (!found)
            {
                slot=i;
                slotAge=m_cache[i].age;
                found=true;
            }
            else if (m_cache[i].age < slotAge)
            {
                slot=i;
                slotAge=m_cache[i].age;
            }
        }
    }
    if (!found)
    {
        throw(ResourceFail("No free slot in light cache"));
    }
    m_cache[slot].age=m_cacheTime;
    m_cache[slot].value=inNum;
    m_cache[slot].modified=true;
    COREASSERT(!m_cache[slot].enabled);
    m_cacheTime++;
    // cerr << "Took light cache slot " << slot << " for light " << inNum << endl;
    return slot;
}

void
GLLights::LightDisable(U32 inNum)
{
    for (U32 i=0; i<kMaxLights; ++i)
    {
        if (m_cache[i].value == inNum &&
            m_cache[i].enabled)
        {
            glDisable(GL_LIGHT0+i);
            m_cache[i].enabled=false;
            return;
        }
    }
    throw(LogicFail("Disable of light not in cache"));
}

void
GLLights::CacheInvalidate(U32 inNum)
{
    for (U32 i=0; i<kMaxLights; ++i)
    {
        if (m_cache[i].value == inNum)
        {
            // cerr << "Invalidated cache slot " << i << endl;
            m_cache[i].modified=true;
        }
    }
}

void
GLLights::DisableAll(void)
{
    for (U32 i=0; i<kMaxLights; ++i)
    {
        if (m_cache[i].enabled)
        {
            LightDisable(m_cache[i].value);
        }
    }
}

void
GLLights::InvalidateAll(void)
{
    for (U32 i=0; i<kMaxLights; ++i)
    {
        m_cache[i].modified = true;
    }
}
