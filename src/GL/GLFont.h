//%includeGuardStart {
#ifndef GLFONT_H
#define GLFONT_H
//%includeGuardStart } ccyhK1cX2OJx5rLJQ4RL2g
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLFont.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KSzePMmD/JfanCcqUvkxTQ
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
