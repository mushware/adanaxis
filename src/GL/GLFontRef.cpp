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
 * $Id: GLFontRef.cpp,v 1.1 2002/08/08 13:39:09 southa Exp $
 * $Log: GLFontRef.cpp,v $
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "GLFontRef.h"
#include "GLData.h"

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
