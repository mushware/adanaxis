/*
 * $Id$
 * $Log$
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
