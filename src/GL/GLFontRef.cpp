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
 * $Id: GLFontRef.cpp,v 1.8 2003/01/20 10:45:23 southa Exp $
 * $Log: GLFontRef.cpp,v $
 * Revision 1.8  2003/01/20 10:45:23  southa
 * Singleton tidying
 *
 * Revision 1.7  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.6  2003/01/12 17:32:50  southa
 * Mushcore work
 *
 * Revision 1.5  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.4  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "GLFontRef.h"
#include "GLData.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLFont *
GLFontRef::FontGet(void) const
{
    if (m_fontPtr == NULL)
    {
        GetReference();
    }
    return m_fontPtr;
}

void
GLFontRef::GetReference(void) const
{
    m_fontPtr=GLData::Sgl().FontGet(m_name);
    if (m_fontPtr == NULL)
    {
        throw(MushcoreReferenceFail("Attempt to access non-existent font '"+m_name+"'"));
    }
}

bool
GLFontRef::Exists(void) const
{
    return (m_fontPtr != NULL || GLData::Sgl().FontGet(m_name) != NULL);
}
