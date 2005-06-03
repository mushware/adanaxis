//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLV.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } k7YzD6cuxRNSZv9q4zzcpw
/*
 * $Id: MushGLV.cpp,v 1.5 2005/05/19 13:02:09 southa Exp $
 * $Log: MushGLV.cpp,v $
 * Revision 1.5  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.4  2005/04/10 00:09:22  southa
 * Registration
 *
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
    bool safeMode = false;
    const MushcoreScalar *pScalar = NULL;

    ++m_contextNum;
    m_vendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    m_renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    m_version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    m_extensions = std::string(" ")+reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS))+" ";
    
    void *fnPtr;

    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "SAFE_MODE"))
    {
        if (pScalar->U32Get())
        {
            safeMode = true;
        }
    }

    if (!safeMode && m_extensions.find(" GL_ARB_vertex_buffer_object ") != string::npos)
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
