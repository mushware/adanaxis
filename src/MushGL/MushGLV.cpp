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
 * $Id: MushGLV.cpp,v 1.1 2004/09/20 21:50:47 southa Exp $
 * $Log: MushGLV.cpp,v $
 * Revision 1.1  2004/09/20 21:50:47  southa
 * Added GLV
 *
 */

#include "MushGLV.h"
#include "MushGLStandard.h"

#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushGLV);

MushGLV::MushGLV() :
    m_fpBindBuffer(NULL)
{
}

void
MushGLV::Acquaint()
{
    m_vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    m_renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    m_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    m_extensions = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
    
    void *fnPtr;
    if (PlatformMiscUtils::FunctionPointerGetIfExists(fnPtr, "glBindBuffer"))
    {
        m_fpBindBuffer = (tfpBindBuffer)fnPtr;
        cout << "Found function at " << fnPtr << endl;
    }
    else
    {
        cout << "failed to find function" << endl;
    }
}

//%outOfLineFunctions {
void
MushGLV::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "fpBindBuffer=" << (void *)m_fpBindBuffer << ", ";
    ioOut << "vendor=" << m_vendor << ", ";
    ioOut << "renderer=" << m_renderer << ", ";
    ioOut << "version=" << m_version << ", ";
    ioOut << "extensions=" << m_extensions;
    ioOut << "]";
}
//%outOfLineFunctions } ltALzkImmeRSCMstKHzgCg
