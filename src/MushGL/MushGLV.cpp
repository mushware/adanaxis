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
 * $Id: MushGLV.cpp,v 1.3 2005/01/29 18:27:31 southa Exp $
 * $Log: MushGLV.cpp,v $
 * Revision 1.3  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 * Revision 1.2  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
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
    m_hasVertexBuffer(false),
    m_fpBindBuffer(NULL),
    m_fpBufferData(NULL),
    m_fpBufferSubData(NULL),
    m_fpDeleteBuffers(NULL),
    m_fpGenBuffers(NULL),
    m_fpMapBuffer(NULL),
    m_fpUnmapBuffer(NULL),
    m_contextNum(0)
{
}

void
MushGLV::Acquaint()
{
    ++m_contextNum;
    m_vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    m_renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    m_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    m_extensions = std::string(" ")+reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS))+" ";
    
    void *fnPtr;

    if (m_extensions.find(" GL_ARB_vertex_buffer_object ") != string::npos)
    {
        try
        {
            PlatformMiscUtils::FunctionPointerGet(fnPtr, "glBindBuffer");
            m_fpBindBuffer = (tfpBindBuffer)fnPtr;
            PlatformMiscUtils::FunctionPointerGet(fnPtr, "glBufferData");
            m_fpBufferData = (tfpBufferData)fnPtr;
            PlatformMiscUtils::FunctionPointerGet(fnPtr, "glBufferSubData");
            m_fpBufferSubData = (tfpBufferSubData)fnPtr;
            PlatformMiscUtils::FunctionPointerGet(fnPtr, "glDeleteBuffers");
            m_fpDeleteBuffers = (tfpDeleteBuffers)fnPtr;
            PlatformMiscUtils::FunctionPointerGet(fnPtr, "glGenBuffers");
            m_fpGenBuffers = (tfpGenBuffers)fnPtr;
            PlatformMiscUtils::FunctionPointerGet(fnPtr, "glMapBuffer");
            m_fpMapBuffer = (tfpMapBuffer)fnPtr;
            PlatformMiscUtils::FunctionPointerGet(fnPtr, "glUnmapBuffer");
            m_fpUnmapBuffer = (tfpUnmapBuffer)fnPtr;

            m_hasVertexBuffer = true;
        }
        catch (MushcoreNonFatalFail &e)
        {
            MushcoreLog::Sgl().InfoLog() << "OpenGL symbol missing: " << e.what() << endl;
        }
    }
}

//%outOfLineFunctions {
void
MushGLV::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "hasVertexBuffer=" << m_hasVertexBuffer << ", ";
    ioOut << "fpBindBuffer=" << (void *)m_fpBindBuffer << ", ";
    ioOut << "fpBufferData=" << (void *)m_fpBufferData << ", ";
    ioOut << "fpBufferSubData=" << (void *)m_fpBufferSubData << ", ";
    ioOut << "fpDeleteBuffers=" << (void *)m_fpDeleteBuffers << ", ";
    ioOut << "fpGenBuffers=" << (void *)m_fpGenBuffers << ", ";
    ioOut << "fpMapBuffer=" << (void *)m_fpMapBuffer << ", ";
    ioOut << "fpUnmapBuffer=" << (void *)m_fpUnmapBuffer << ", ";
    ioOut << "vendor=" << m_vendor << ", ";
    ioOut << "renderer=" << m_renderer << ", ";
    ioOut << "version=" << m_version << ", ";
    ioOut << "extensions=" << m_extensions << ", ";
    ioOut << "contextNum=" << m_contextNum;
    ioOut << "]";
}
//%outOfLineFunctions } Hy0vCXDf3BKDouVKwtdIeQ
