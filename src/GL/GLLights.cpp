/*
 * $Id: GLLights.cpp,v 1.2 2002/10/07 12:15:35 southa Exp $
 * $Log: GLLights.cpp,v $
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

GLLights::GLLights()
{
    cerr << "Max lights available=" << GL_MAX_LIGHTS << endl;
}

void
GLLights::LightAdd(U32 inNum, const GLLightDef& inDef)
{
    if (inNum < m_lights.size() && m_lightEnabled[inNum])
    {
        LightDisable(inNum);
    }
    if (inNum >= m_lights.size())
    {
        m_lights.resize(inNum+1);
        m_lightEnabled.resize(inNum+1, false);
    }
    m_lights[inNum]=inDef;
}
    
void
GLLights::LightEnable(U32 inNum)
{
    if (inNum >= m_lights.size())
    {
        throw(LogicFail("Light number too big"));
    }
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    // glLoadIdentity();
    GLfloat diffuse[4]={1.0,1.0,1.0,1};
    GLfloat specular[4]={1.0,1.0,1.0,1};
    GLfloat transparent[4]={0,0,0,0};
    GLfloat position[4]={30,10,2,1};
    GLenum lightEnum=GL_LIGHT0+inNum;
    glLightfv(lightEnum, GL_AMBIENT, transparent);
    glLightfv(lightEnum, GL_DIFFUSE, diffuse);
    glLightfv(lightEnum, GL_SPECULAR, specular);
    glLightfv(lightEnum, GL_POSITION, position);
    glLighti(lightEnum, GL_SPOT_CUTOFF, 180);
    GLfloat direction[3]={0,0,1};
    glLightfv(lightEnum, GL_SPOT_DIRECTION, direction);
    glLightf(lightEnum, GL_SPOT_EXPONENT, 4);
    glLightf(lightEnum, GL_CONSTANT_ATTENUATION, 0.01);
    glLightf(lightEnum, GL_LINEAR_ATTENUATION, 0);
    glLightf(lightEnum, GL_QUADRATIC_ATTENUATION, 0.4);
    
    glEnable(GL_LIGHT0+inNum);
    glPopMatrix();
    
    m_lightEnabled[inNum]=true;
    GLUtils::CheckGLError();
}    

void
GLLights::LightDisable(U32 inNum)
{
    if (inNum >= m_lights.size())
    {
        throw(LogicFail("Light number too big"));
    }
    glDisable(GL_LIGHT0+inNum);
    m_lightEnabled[inNum]=false;
}

void
GLLights::DisableAll(void)
{
    for (U32 i=0; i<m_lights.size(); ++i)
    {
        LightDisable(i);
    }
}