/*
 * $Id$
 * $Log$
*/

#include "mushCore.h"
#include "GLStandard.h"

class GLLightDef;

class GLLights
{
public:
    GLLights();
    void LightAdd(U32 inNum, const GLLightDef& inDef);
    void LightEnable(U32 inNum);
    void LightDisable(U32 inNum);
    void DisableAll(void);

private:
    vector<GLLightDef> m_lights;
    vector<bool> m_lightEnabled;
    U32 m_numLights;
};

