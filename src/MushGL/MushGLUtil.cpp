//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLUtil.cpp
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
//%Header } vl7jY3WxF4VnrsvzzFB2Cw
/*
 * $Id: MushGLUtil.cpp,v 1.2 2006/06/01 15:39:18 southa Exp $
 * $Log: MushGLUtil.cpp,v $
 * Revision 1.2  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 */

#include "MushGLUtil.h"

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
MushGLUtil::DisplayPrologue(void)
{
    MushGLAppHandler& appHandler(AppHandler());
    switch (appHandler.CurrentModeDefGet().SyncGet())
    {
        case GLModeDef::kSyncHard:
            // glFinish();
        case GLModeDef::kSyncSoft:
            PlatformVideoUtils::VBLWait();
        default:
            appHandler.SwapBuffers();
    }
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

std::string
MushGLUtil::TextureCacheFilename(const std::string& inName)
{
	return MushcoreEnv::Sgl().VariableGet("GLOBAL_CACHE_PATH").StringGet()+"/"+inName+".tiff";
}
