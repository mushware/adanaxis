/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "GLKeys.h"

class GLAppSignal: public CoreAppSignal
{
public:
    GLAppSignal(U32 inSigNumber): CoreAppSignal(inSigNumber) {}
    enum GLSigNumber
    {
        kDisplay=0x100,
        kVisible,
        kNotVisible,
        kKeyboard
    };
};

class GLKeyboardSignal: public CoreAppSignal
{
public:
    GLKeyboardSignal(bool inKeyDown, GLKeys inKeyValue, S32 inMouseX, S32 inMouseY):
        CoreAppSignal(GLAppSignal::kKeyboard),
        keyDown(inKeyDown),
        keyValue(inKeyValue),
        mouseX(inMouseX),
        mouseY(inMouseY)
        {}
    bool keyDown;
    GLKeys keyValue;
    S32 mouseX;
    S32 mouseY;
};
