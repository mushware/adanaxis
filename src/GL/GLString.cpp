/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GLString.cpp,v 1.7 2003/01/13 14:31:55 southa Exp $
 * $Log: GLString.cpp,v $
 * Revision 1.7  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.6  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/09 17:09:02  southa
 * GameDialogue added
 *
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "GLString.h"
#include "GLFont.h"
#include "GLUtils.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLString::GLString(const string& inValue, const GLFontRef& inFont, tVal inAlign):
    m_fontRef(inFont),
    m_value(inValue),
    m_alignment(inAlign)
{
}

void
GLString::Render(void) const
{
    tVal size=m_fontRef.SizeGet();
    GLUtils::PushMatrix();
    GLUtils::Scale(size, size, 1);
    m_fontRef.FontGet()->RenderString(m_value, m_alignment);
    GLUtils::PopMatrix();
}
