//%includeGuardStart {
#ifndef GLAPPSIGNAL_H
#define GLAPPSIGNAL_H
//%includeGuardStart } CvdEEBCrta1/dmo/cPMNvA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLAppSignal.h
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
//%Header } lXEJ1avZJY9+z/jgGDifiA
/*
 * $Id: GLAppSignal.h,v 1.19 2006/07/08 16:05:55 southa Exp $
 * $Log: GLAppSignal.h,v $
 * Revision 1.19  2006/07/08 16:05:55  southa
 * Ruby menus and key handling
 *
 * Revision 1.18  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.16  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.15  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.14  2004/01/02 21:13:04  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
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

#include "mushMushcore.h"

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
    GLKeyboardSignal(bool inKeyDown, Mushware::S32 inKeyValue, Mushware::U32 inKeyModifier, Mushware::tVal inMouseX, Mushware::tVal inMouseY):
        MushcoreAppSignal(GLAppSignal::kKeyboard),
        keyDown(inKeyDown),
        keyValue(inKeyValue),
        keyModifier(inKeyModifier),
        mouseX(inMouseX),
        mouseY(inMouseY)
        {}
    
    bool KeyDown(void) const { return keyDown; }
    Mushware::S32 KeyValue(void) const { return keyValue; }
    Mushware::U32 KeyModifier(void) const { return keyModifier; }
    Mushware::tVal MouseX(void) const { return mouseX; }
    Mushware::tVal MouseY(void) const { return mouseY; }
    
    bool keyDown;
    Mushware::S32 keyValue;
    Mushware::U32 keyModifier;
    Mushware::tVal mouseX;
    Mushware::tVal mouseY;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
