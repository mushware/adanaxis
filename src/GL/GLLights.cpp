/*
 * $Id$
 * $Log$
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
    glLoadIdentity();
    GLfloat white[4]={1,1,1,1};
    GLfloat black[4]={0,0,0,1};
    GLfloat transparent[4]={0,0,0,0};
    GLfloat position[4]={0,0,0,1};
    glTranslatef(1.5,0.5,-1);
    GLenum lightEnum=GL_LIGHT0+inNum;
    glLightfv(lightEnum, GL_AMBIENT, transparent);
    glLightfv(lightEnum, GL_DIFFUSE, white);
    glLightfv(lightEnum, GL_SPECULAR, white);
    glLightfv(lightEnum, GL_POSITION, position);
    glLighti(lightEnum, GL_SPOT_CUTOFF, 180);
    GLfloat direction[3]={0,0,1};
    glLightfv(lightEnum, GL_SPOT_DIRECTION, direction);
    glLightf(lightEnum, GL_SPOT_EXPONENT, 128);
    glLightf(lightEnum, GL_CONSTANT_ATTENUATION, 0.01);
    glLightf(lightEnum, GL_LINEAR_ATTENUATION, 0);
    glLightf(lightEnum, GL_QUADRATIC_ATTENUATION, 1.0);
    
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