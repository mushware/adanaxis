#ifndef GLAPPSIGNAL_H
#define GLAPPSIGNAL_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/



/*
 * $Id: GLAppSignal.h,v 1.3 2002/07/06 18:04:17 southa Exp $
 * $Log: GLAppSignal.h,v $
 * Revision 1.3  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
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
#endif
