//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLUtil.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } zd/YwL/o/GJvmh6dpZTZdw
/*
 * $Id: MushGLUtil.cpp,v 1.10 2007/03/09 19:50:13 southa Exp $
 * $Log: MushGLUtil.cpp,v $
 * Revision 1.10  2007/03/09 19:50:13  southa
 * Resident textures
 *
 * Revision 1.9  2006/11/25 21:26:32  southa
 * Display mode definitions
 *
 * Revision 1.8  2006/09/07 16:38:51  southa
 * Vertex shader
 *
 * Revision 1.7  2006/09/07 10:02:37  southa
 * Shader interface
 *
 * Revision 1.6  2006/07/08 16:05:58  southa
 * Ruby menus and key handling
 *
 * Revision 1.5  2006/06/30 15:05:33  southa
 * Texture and buffer purge
 *
 * Revision 1.4  2006/06/02 18:14:36  southa
 * Texture caching
 *
 * Revision 1.3  2006/06/01 20:12:59  southa
 * Initial texture caching
 *
 * Revision 1.2  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 */

#include "MushGLUtil.h"

#include "MushGLBuffers.h"
#include "MushGLShader.h"
#include "MushGLTexture.h"

#include "API/mushPlatform.h"

using namespace Mushware;
using namespace std;

Mushware::U32 MushGLUtil::m_glErrorCount = 0;

MushGLAppHandler&
MushGLUtil::AppHandler(void)
{
    MushGLAppHandler *pAppHandler=dynamic_cast<MushGLAppHandler *>(&MushcoreAppHandler::Sgl());
    if (pAppHandler == NULL)
    {
        throw MushcoreRequestFail("AppHandler of wrong type for ScreenSize");
    }
    return *pAppHandler;
}

void
MushGLUtil::IdentityPrologue(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
MushGLUtil::IdentityEpilogue(void)
{
}

void
MushGLUtil::OrthoPrologue(void)
{
    // The screen should be enclosed by a square with corners (-0.5,-0.5) and
    // (0.5,0.5) with aspect ratio 1.  The screen is a rectangle within the square
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    t2Val screenRatios(ScreenRatios()*0.5);
    gluOrtho2D(-screenRatios.X(),screenRatios.X(),-screenRatios.Y(),screenRatios.Y());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
MushGLUtil::OrthoEpilogue(void)
{
}

void
MushGLUtil::UnitaryPrologue(void)
{
    // The screen should be enclosed by a square with corners (-0.5,-0.5) and
    // (0.5,0.5).  The screen is the square
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5,0.5,-0.5,0.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
MushGLUtil::UnitaryEpilogue(void)
{
}

void
MushGLUtil::DisplayPrologue(void)
{
    MushGLAppHandler& appHandler(AppHandler());
    appHandler.SwapBuffers();
}

void
MushGLUtil::DisplayEpilogue(void)
{
    glDrawBuffer(GL_BACK);
}

void
MushGLUtil::ClearScreen(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

const t2Val
MushGLUtil::ScreenSize(void)
{
    MushGLAppHandler& appHandler(AppHandler());
    return t2Val(appHandler.ScreenWidth(), appHandler.ScreenHeight());
}

const t2Val
MushGLUtil::ScreenRatios(void)
{
    return ScreenSize() / LongestScreenAxis();
}

tVal
MushGLUtil::ScreenAspectRatio(void)
{
    t2Val screenSize(ScreenSize());
    
    return screenSize.X() / screenSize.Y();
}

tVal
MushGLUtil::LongestScreenAxis(void)
{
    t2Val screenSize(ScreenSize());
    if (screenSize.X() > screenSize.Y())
    {
        return screenSize.X();
    }
    else
    {
        return screenSize.Y();
    }
}


void
MushGLUtil::ThrowGLError(GLenum inGLErr)
{
	ThrowGLError(inGLErr, "");
}

void
MushGLUtil::ThrowGLError(GLenum inGLErr, const std::string& inMessage)
{
	if (inMessage == "")
	{
		throw MushcoreDeviceFail(GLErrorString(inGLErr));
	}
	else
	{
		throw MushcoreDeviceFail(inMessage+": "+GLErrorString(inGLErr));
	}
}

void
MushGLUtil::GLErrorWriteToLog(GLenum inGLErr)
{
	GLErrorWriteToLog(inGLErr, "");
}

void
MushGLUtil::GLErrorWriteToLog(GLenum inGLErr, const std::string& inMessage)
{
	if (m_glErrorCount == 100)
	{
		MushcoreLog::Sgl().WarningLog() << "(No more GL errors will be reported)";
	}
	else if (m_glErrorCount < 100)
	{
		if (inMessage == "")
		{
			MushcoreLog::Sgl().WarningLog() << GLErrorString(inGLErr);
		}
		else
		{
			MushcoreLog::Sgl().WarningLog() << inMessage << ": " << GLErrorString(inGLErr);
		}		
	}
	++m_glErrorCount;
}

std::string
MushGLUtil::GLErrorString(const GLenum inGLErr)
{
	std::string errorString;
	
    switch (inGLErr)
    {
        case GL_NO_ERROR:
            break;
			
        case GL_INVALID_ENUM:
            errorString = "GL invalid enum";
            break;
			
        case GL_INVALID_VALUE:
            errorString = "GL invalid value";
            break;
			
        case GL_INVALID_OPERATION:
            errorString = "GL invalid operation";
            break;
			
        case GL_STACK_OVERFLOW:
            errorString = "GL stack overflow";
            break;
			
        case GL_STACK_UNDERFLOW:
            errorString = "GL stack underflow";
            break;
			
        case GL_OUT_OF_MEMORY:
            errorString = "GL out of memory";
            break;
			
        case GL_TABLE_TOO_LARGE:
            errorString = "GL table too large";
            break;
			
        default:
		{
			std::ostringstream messageStream;
            messageStream << "Unknown GL error " << inGLErr;
			errorString = messageStream.str();
		}
        break;
    }
	return errorString;
}

void
MushGLUtil::BufferPurge(void)
{
    for (MushGLBuffers::tData::iterator p = MushGLBuffers::tData::Sgl().begin();
         p != MushGLBuffers::tData::Sgl().end(); ++p)
    {
        MUSHCOREASSERT(p->second != NULL);
        p->second->Purge();   
    }
    for (MushGLBuffers::tSharedData::iterator p = MushGLBuffers::tSharedData::Sgl().begin();
         p != MushGLBuffers::tSharedData::Sgl().end(); ++p)
    {
        MUSHCOREASSERT(p->second != NULL);
        p->second->Purge();   
    }
}

void
MushGLUtil::ShaderPurge(void)
{
    typedef MushcoreData<MushGLShader> tData;
    for (tData::iterator p = tData::Sgl().begin(); p != tData::Sgl().end(); ++p)
    {
        MUSHCOREASSERT(p->second != NULL);
        p->second->Purge();   
    }
}

void
MushGLUtil::TexturePurge(void)
{
    typedef MushcoreData<MushGLTexture> tData;
    for (tData::iterator p = tData::Sgl().begin(); p != tData::Sgl().end(); ++p)
    {
        MUSHCOREASSERT(p->second != NULL);
        p->second->Purge();   
    }
}

void
MushGLUtil::TexturePurgeNonResident(void)
{
    typedef MushcoreData<MushGLTexture> tData;
    for (tData::iterator p = tData::Sgl().begin(); p != tData::Sgl().end(); ++p)
    {
        MUSHCOREASSERT(p->second != NULL);
        if (!p->second->Resident())
        {
            p->second->Purge();
        }
    }
}

void
MushGLUtil::Purge(void)
{
    BufferPurge();
    ShaderPurge();
    TexturePurge();
}

void
MushGLUtil::PurgeNonResident(void)
{
    BufferPurge();
    ShaderPurge();
    TexturePurgeNonResident();
}

void
MushGLUtil::ShaderTest(void)
{
    typedef MushcoreData<MushGLShader> tData;
    for (tData::iterator p = tData::Sgl().begin(); p != tData::Sgl().end(); ++p)
    {
        MUSHCOREASSERT(p->second != NULL);
        p->second->Test();
        MushcoreLog::Sgl().InfoLog() << "Shader " << p->first << " OK" << endl;
    }
}

void
MushGLUtil::ColourSet(const Mushware::t4Val& inColour)
{
    glColor4f(inColour.X(), inColour.Y(), inColour.Z(), inColour.W());   
}

void
MushGLUtil::MatrixToGL(tGLMatrix& outMatrix, const Mushware::t4x4Val& inMatrix)
{
    MUSHCOREASSERT(sizeof(outMatrix)/sizeof(outMatrix[0]) == 16);
    outMatrix[0] = inMatrix.RCGet(0,0);
    outMatrix[1] = inMatrix.RCGet(1,0);
    outMatrix[2] = inMatrix.RCGet(2,0);
    outMatrix[3] = inMatrix.RCGet(3,0);
    outMatrix[4] = inMatrix.RCGet(0,1);
    outMatrix[5] = inMatrix.RCGet(1,1);
    outMatrix[6] = inMatrix.RCGet(2,1);
    outMatrix[7] = inMatrix.RCGet(3,1);
    outMatrix[8] = inMatrix.RCGet(0,2);
    outMatrix[9] = inMatrix.RCGet(1,2);
    outMatrix[10] = inMatrix.RCGet(2,2);
    outMatrix[11] = inMatrix.RCGet(3,2);
    outMatrix[12] = inMatrix.RCGet(0,3);
    outMatrix[13] = inMatrix.RCGet(1,3);
    outMatrix[14] = inMatrix.RCGet(2,3);
    outMatrix[15] = inMatrix.RCGet(3,3);
}

void
MushGLUtil::ProjectionMatrixSet(const Mushware::t4x4Val& inMatrix)
{
    tGLMatrix glMatrix;
    MatrixToGL(glMatrix, inMatrix);
    
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glMatrix);
}

void
MushGLUtil::ModelViewMatrixSet(const Mushware::t4x4Val& inMatrix)
{
    tGLMatrix glMatrix;
    MatrixToGL(glMatrix, inMatrix);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glMatrix);
}

std::string
MushGLUtil::DataTypeToString(GLenum inType)
{
    std::string retVal;
    
    switch (inType)
    {
        case GL_FLOAT:
            retVal = "GL_FLOAT";
            break;
            
        case GL_FLOAT_VEC2_ARB:
            retVal = "GL_FLOAT_VEC2_ARB";
            break;
            
        case GL_FLOAT_VEC3_ARB:
            retVal = "GL_FLOAT_VEC3_ARB";
            break;
            
        case GL_FLOAT_VEC4_ARB:
            retVal = "GL_FLOAT_VEC4_ARB";
            break;
            
        case GL_INT:
            retVal = "GL_INT";
            break;
            
        case GL_INT_VEC2_ARB:
            retVal = "GL_INT_VEC2_ARB";
            break;
            
        case GL_INT_VEC3_ARB:
            retVal = "GL_INT_VEC3_ARB";
            break;
            
        case GL_INT_VEC4_ARB:
            retVal = "GL_INT_VEC4_ARB";
            break;
            
        case GL_FLOAT_MAT2_ARB:
            retVal = "GL_FLOAT_MAT2_ARB";
            break;
            
        case GL_FLOAT_MAT3_ARB:
            retVal = "GL_FLOAT_MAT3_ARB";
            break;
            
        case GL_FLOAT_MAT4_ARB:
            retVal = "GL_FLOAT_MAT4_ARB";
            break;

        case GL_SAMPLER_1D_ARB:
            retVal = "GL_SAMPLER_1D_ARB";
            break;
            
        case GL_SAMPLER_2D_ARB:
            retVal = "GL_SAMPLER_2D_ARB";
            break;
            
        case GL_SAMPLER_3D_ARB:
            retVal = "GL_SAMPLER_3D_ARB";
            break;
            
        default:
            ostringstream typeStream;
            typeStream << "Unknown (" << inType << ")";
            retVal = typeStream.str();
            break;
    }
    return retVal;
}
