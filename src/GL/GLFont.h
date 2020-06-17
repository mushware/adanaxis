//%includeGuardStart {
#ifndef GLFONT_H
#define GLFONT_H
//%includeGuardStart } ccyhK1cX2OJx5rLJQ4RL2g
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLFont.h
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
//%Header } A5s6oG/vZ1o8eaLshjjZbg
/*
 * $Id: GLFont.h,v 1.17 2007/04/18 09:22:06 southa Exp $
 * $Log: GLFont.h,v $
 * Revision 1.17  2007/04/18 09:22:06  southa
 * Header and level fixes
 *
 * Revision 1.16  2006/06/01 15:38:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.13  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.12  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.11  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:08:20  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.8  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.6  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/09 17:09:02  southa
 * InfernalDialogue added
 *
 * Revision 1.2  2002/08/08 18:20:29  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "mushMushcore.h"

#include "GLTextureRef.h"

class GLFont
{
public:
    GLFont(const std::string& inName);

    void RenderCharacter(Mushware::U32 inChar) const;
    void RenderString(const std::string& inStr, Mushware::tVal inAlign=-1.0) const;
    Mushware::tVal StringLengthGet(const std::string& inStr) const;
    void ShapeSet(Mushware::U32 inXNum, Mushware::U32 inYNum);
    void SizeSet(Mushware::tVal inXNum, Mushware::tVal inYNum);
        
    static void Install(void);
    static MushcoreScalar LoadFontMap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);

private:
    const std::string m_name;
    const GLTextureRef m_texRef;
    Mushware::U32 m_xMapSize;
    Mushware::U32 m_yMapSize;
    Mushware::tVal m_xUsedSize;
    Mushware::tVal m_yUsedSize;
    Mushware::U32 m_xNum; // Must be integer types
    Mushware::U32 m_yNum;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
