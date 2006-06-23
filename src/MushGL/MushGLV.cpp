//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLV.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } NYmv5MZn7NEYPYHpc3JV8Q
/*
 * $Id: MushGLV.cpp,v 1.13 2006/06/01 20:12:59 southa Exp $
 * $Log: MushGLV.cpp,v $
 * Revision 1.13  2006/06/01 20:12:59  southa
 * Initial texture caching
 *
 * Revision 1.12  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.10  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 * Revision 1.9  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.8  2005/06/13 17:34:56  southa
 * Adanaxis creation
 *
 * Revision 1.7  2005/06/08 20:59:51  southa
 * X11 release
 *
 * Revision 1.6  2005/06/03 13:36:44  southa
 * win32 build fixes
 *
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

#include "MushGLBuffers.h"
#include "MushGLStandard.h"
#include "MushGLState.h"
#include "MushGLUtil.h"

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
    m_hasActiveTexture(false),
    m_fpActiveTexture(NULL),
    m_fpClientActiveTexture(NULL),
    m_numTextureUnits(0),
    m_hasS3TC(false),
    m_contextNum(0),
    m_contextValid(false)
{
}

void *
MushGLV::GetProcAddressWithARB(const std::string& inName) const
{
    void *fnPtr = NULL;
    if (!PlatformMiscUtils::FunctionPointerGetIfExists(fnPtr, inName))
    {
    	if (!PlatformMiscUtils::FunctionPointerGetIfExists(fnPtr, inName+"ARB"))
		{
			throw MushcoreRequestFail("Unknown symbol '"+inName+"'/'"+inName+"ARB'");
		}
    }
    return fnPtr;
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

    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "SAFE_MODE"))
    {
        if (pScalar->U32Get())
        {
            safeMode = true;
        }
    }

    {
        GLint texUnits = 0;
        glGetIntegerv(GL_MAX_TEXTURE_UNITS, &texUnits);
        m_numTextureUnits = texUnits;
    }
    
    if (!safeMode && m_extensions.find(" GL_ARB_vertex_buffer_object ") != string::npos)
    {
        try
        {   
            m_fpBindBuffer = (tfpBindBuffer) GetProcAddressWithARB("glBindBuffer");
            m_fpBufferData = (tfpBufferData) GetProcAddressWithARB("glBufferData");
            m_fpBufferSubData = (tfpBufferSubData) GetProcAddressWithARB("glBufferSubData");
            m_fpDeleteBuffers = (tfpDeleteBuffers) GetProcAddressWithARB("glDeleteBuffers");
            m_fpGenBuffers = (tfpGenBuffers) GetProcAddressWithARB("glGenBuffers");
            m_fpMapBuffer = (tfpMapBuffer) GetProcAddressWithARB("glMapBuffer");
            m_fpUnmapBuffer = (tfpUnmapBuffer) GetProcAddressWithARB("glUnmapBuffer");
            m_fpGetBufferParameteriv = (tfpGetBufferParameteriv) GetProcAddressWithARB("glGetBufferParameteriv");

            m_hasVertexBuffer = true;
        }
        catch (MushcoreNonFatalFail &e)
        {
            MushcoreLog::Sgl().InfoLog() << "OpenGL symbol missing: " << e.what() << endl;
        }
    }
    
    if (!safeMode && m_extensions.find(" GL_ARB_multitexture ") != string::npos)
    {
        try
        {   
            m_fpActiveTexture = (tfpActiveTexture) GetProcAddressWithARB("glActiveTexture");
            m_fpClientActiveTexture = (tfpClientActiveTexture) GetProcAddressWithARB("glClientActiveTexture");

            m_hasActiveTexture = true;
        }
        catch (MushcoreNonFatalFail &e)
        {
            MushcoreLog::Sgl().InfoLog() << "OpenGL symbol missing: " << e.what() << endl;
        }
    }
    
	if (!safeMode && m_extensions.find(" GL_EXT_texture_compression_s3tc ") != string::npos)
    {
		m_hasS3TC = true;
	}
	else
	{
		m_hasS3TC = false;
	}
	
    m_contextValid = true;
    MushGLState::Sgl().ResetWriteAll();
}

void
MushGLV::BufferValidate(Mushware::U32 inSize) const
{
	GLint bufferSize = 0;
	GetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
	MushGLUtil::ThrowIfGLError();
	MUSHCOREASSERT(inSize <= static_cast<U32>(bufferSize));
}

void
MushGLV::DrawArraysVerify(GLenum inMode, GLint inFirst, GLsizei inCount) const
{
	MushGLUtil::CheckGLError(); // Discard any outstanding errors
	
	GLvoid *pVertexArray, *pColourArray, *pTexCoordArray;
	glGetPointerv(GL_VERTEX_ARRAY_POINTER, &pVertexArray);
	MushGLUtil::ThrowIfGLError();
	glGetPointerv(GL_COLOR_ARRAY_POINTER, &pColourArray);
	MushGLUtil::ThrowIfGLError();
	glGetPointerv(GL_TEXTURE_COORD_ARRAY_POINTER, &pTexCoordArray);
	MushGLUtil::ThrowIfGLError();

	if (MushGLState::Sgl().VertexArray())
	{
		MushGLState::tVertexArrayBuffer *pVertexBuffer = MushGLState::Sgl().DebugVertexBuffer();
		MUSHCOREASSERT(pVertexBuffer != NULL);
		
		if (pVertexBuffer->IsVertexBuffer())
		{
			U32 requiredSize = reinterpret_cast<U32>(pVertexArray) + inFirst + inCount;
			// cout << "pVertexArray=" << pVertexArray << ", inFirst=" << inFirst << ", inCount=" << inCount << ", Size()=" << pVertexBuffer->Size() << endl;
		    MUSHCOREASSERT(requiredSize <= pVertexBuffer->Size());
			
			pVertexBuffer->Bind();
			BufferValidate(sizeof(MushGLBuffers::tVertex) * requiredSize);
		}
		else
		{
			throw MushcoreRequestFail("Debug check not supported");	
		}
	}

	if (MushGLState::Sgl().ColourArray())
	{
		MushGLState::tColourArrayBuffer *pColourBuffer = MushGLState::Sgl().DebugColourBuffer();
		MUSHCOREASSERT(pColourBuffer != NULL);
		
		if (pColourBuffer->IsVertexBuffer())
		{
			U32 requiredSize = reinterpret_cast<U32>(pColourArray) + inFirst + inCount;

			// cout << "pColourArray=" << pColourArray << ", inFirst=" << inFirst << ", inCount=" << inCount << ", Size()=" << pColourBuffer->Size() << endl;
		    MUSHCOREASSERT(reinterpret_cast<U32>(pColourArray) + inFirst + inCount <= pColourBuffer->Size());

			pColourBuffer->Bind();
			BufferValidate(sizeof(MushGLBuffers::tColour) * requiredSize);
		}
		else
		{
			throw MushcoreRequestFail("Debug check not supported");	
		}
	}

	for (U32 i=0; i < MushGLState::Sgl().NumTexCoordArrays(); ++i)
	{
		if (MushGLState::Sgl().TexCoordArray(i))
		{
			U32 requiredSize = reinterpret_cast<U32>(pTexCoordArray) + inFirst + inCount;

			MushGLState::tTexCoordArrayBuffer *pTexCoordBuffer = MushGLState::Sgl().DebugTexCoordBuffer();
			MUSHCOREASSERT(pTexCoordBuffer != NULL);
			
			if (pTexCoordBuffer->IsVertexBuffer())
			{
				// cout << "pTexCoordArray=" << pTexCoordArray << ", inFirst=" << inFirst << ", inCount=" << inCount << ", Size()=" << pTexCoordBuffer->Size() << endl;
				MUSHCOREASSERT(reinterpret_cast<U32>(pTexCoordArray) + inFirst + inCount <= pTexCoordBuffer->Size());
				pTexCoordBuffer->Bind();
				BufferValidate(sizeof(MushGLBuffers::tTexCoord) * requiredSize);
			}
			else
			{
				throw MushcoreRequestFail("Debug check not supported");	
			}
		}
	}
	
	//MUSHCOREASSERT(false);
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
    ioOut << "fpGetBufferParameteriv=" << (void *)m_fpGetBufferParameteriv << ", ";
    ioOut << "hasActiveTexture=" << m_hasActiveTexture << ", ";
    ioOut << "fpActiveTexture=" << (void *)m_fpActiveTexture << ", ";
    ioOut << "fpClientActiveTexture=" << (void *)m_fpClientActiveTexture << ", ";
    ioOut << "vendor=" << m_vendor << ", ";
    ioOut << "renderer=" << m_renderer << ", ";
    ioOut << "version=" << m_version << ", ";
    ioOut << "extensions=" << m_extensions << ", ";
    ioOut << "numTextureUnits=" << m_numTextureUnits << ", ";
    ioOut << "hasS3TC=" << m_hasS3TC << ", ";
    ioOut << "contextNum=" << m_contextNum << ", ";
    ioOut << "contextValid=" << m_contextValid;
    ioOut << "]";
}
//%outOfLineFunctions } Y3RNvFGT1cWxEFFkOnxnaQ
