//%includeGuardStart {
#ifndef GLAPPSIGNAL_H
#define GLAPPSIGNAL_H
//%includeGuardStart } CvdEEBCrta1/dmo/cPMNvA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLAppSignal.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vQ2UEPvvcZY1QyRzx08+Jw
/*
 * $Id: GLAppSignal.h,v 1.12 2003/08/21 23:08:18 southa Exp $
 * $Log: GLAppSignal.h,v $
 * Revision 1.12  2003/08/21 23:08:18  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.10  2003/01/09 14:56:57  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 09:01:22  southa
 * Corrected KeyboardSignal constructor
 *
 * Revision 1.6  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/17 10:41:50  southa
 * Designer fixes
 *
 * Revision 1.4  2002/08/07 13:36:46  southa
 * Conditioned source
 *
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

#include "GLKeys.h"
#include "Mushcore.h"

class GLAppSignal: public MushcoreAppSignal
{
public:
    GLAppSignal(Mushware::U32 inSigNumber): MushcoreAppSignal(inSigNumber) {}
    enum GLSigNumber
    {
        kDisplay=0x100,
        kVisible,
        kNotVisible,
        kKeyboard
    };
};

class GLKeyboardSignal: public MushcoreAppSignal
{
public:
    GLKeyboardSignal(bool inKeyDown, GLKeys inKeyValue, Mushware::tVal inMouseX, Mushware::tVal inMouseY):
        MushcoreAppSignal(GLAppSignal::kKeyboard),
        keyDown(inKeyDown),
        keyValue(inKeyValue),
        mouseX(inMouseX),
        mouseY(inMouseY)
        {}
    bool keyDown;
    GLKeys keyValue;
    Mushware::tVal mouseX;
    Mushware::tVal mouseY;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
