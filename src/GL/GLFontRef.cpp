/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLFontRef.cpp,v 1.3 2002/10/22 20:42:00 southa Exp $
 * $Log: GLFontRef.cpp,v $
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

using namespace Mushware;

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
    m_fontPtr=GLData::Instance().FontGet(m_name);
    if (m_fontPtr == NULL)
    {
        throw(ReferenceFail("Attempt to access non-existent font '"+m_name+"'"));
    }
}

bool
GLFontRef::Exists(void) const
{
    return (m_fontPtr != NULL || GLData::Instance().FontGet(m_name) != NULL);
}
