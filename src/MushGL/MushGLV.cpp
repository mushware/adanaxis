//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLV.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 3XIr5cTD30rcFqo9UL9xaQ
/*
 * $Id$
 * $Log$
 */

#include "MushGLV.h"
#include "MushGLStandard.h"

MushGLV::MushGLV()
{
}

void
MushGLV::Acquaint()
{
    m_vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    m_renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    m_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    m_extensions = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
    std::cout << "Vendor: " << m_vendor << std::endl;
    std::cout << "Renderer: " << m_renderer << std::endl;
    std::cout << "Version: " << m_version << std::endl;
    std::cout << "Extensions: " << m_extensions << std::endl;
}
//%outOfLineFunctions {
void
MushGLV::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "vendor=" << m_vendor << ", ";
    ioOut << "renderer=" << m_renderer << ", ";
    ioOut << "version=" << m_version << ", ";
    ioOut << "extensions=" << m_extensions;
    ioOut << "]";
}
//%outOfLineFunctions } MnoBURhpIqyQKkqyHcMhMA
