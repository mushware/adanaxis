/*
 * $Id: GLLights.cpp,v 1.3 2002/10/07 17:49:44 southa Exp $
 * $Log: GLLights.cpp,v $
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

    if (m_cache[slot].modified)
    {
        GLfloat diffuse[4]={m_lightingFactor,m_lightingFactor,m_lightingFactor,1};
        GLfloat specular[4]={m_lightingFactor,m_lightingFactor,m_lightingFactor,1};
        GLfloat transparent[4]={0,0,0,0};

        glLightfv(lightEnum, GL_AMBIENT, transparent);
        glLightfv(lightEnum, GL_DIFFUSE, diffuse);
        glLightfv(lightEnum, GL_SPECULAR, specular);

        glLighti(lightEnum, GL_SPOT_CUTOFF, 180);
        GLfloat direction[3]={0,0,1};
        glLightfv(lightEnum, GL_SPOT_DIRECTION, direction);
        glLightf(lightEnum, GL_SPOT_EXPONENT, 4);
        glLightf(lightEnum, GL_CONSTANT_ATTENUATION, 0.01);
        glLightf(lightEnum, GL_LINEAR_ATTENUATION, 0);
        glLightf(lightEnum, GL_QUADRATIC_ATTENUATION, 0.4);
        m_cache[slot].modified=false;
        cerr << "Wrote data for light " << inNum << " to slot " << slot << endl;
    }        

    COREASSERT(m_cache[slot].value == inNum);
    
    const GLLightDef& def = m_lights[inNum];
    GLfloat position[4]={def.pos.x, def.pos.y, def.pos.z, 1};
    glLightfv(lightEnum, GL_POSITION, position);

    if (!m_cache[slot].enabled)
    {
        m_cache[slot].enabled=true;
        glEnable(GL_LIGHT0+inNum);
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
    cerr << "Took light cache slot " << slot << " for light " << inNum << endl;
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
            cerr << "Invalidated cache slot " << i << endl;
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
