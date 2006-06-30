//%includeGuardStart {
#ifndef MUSHGLUTIL_H
#define MUSHGLUTIL_H
//%includeGuardStart } rAQ4jcchYa85P6BeLBYvlA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLUtil.h
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
//%Header } 0OQkM+NcUqCBag3zq+cczA
/*
 * $Id: MushGLUtil.h,v 1.3 2006/06/01 20:12:59 southa Exp $
 * $Log: MushGLUtil.h,v $
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

#include "API/mushMushMesh.h"

#include "MushGLAppHandler.h"

class MushGLUtil
{
public:
    static void IdentityPrologue(void);
    static void IdentityEpilogue(void);
    static void OrthoPrologue(void);
    static void OrthoEpilogue(void);
    static void DisplayPrologue(void);
    static void DisplayEpilogue(void);
    static void ClearScreen(void);
    static MushGLAppHandler& AppHandler(void);
    
    static const Mushware::t2Val ScreenSize(void);
    static const Mushware::t2Val ScreenRatios(void);

    static Mushware::tVal LongestScreenAxis(void);
    static Mushware::tVal ScreenAspectRatio(void);

	static void ThrowIfGLError(void);
	static void ThrowIfGLError(const std::string& inMessage);
	static void CheckGLError(void);
	static void CheckGLError(const std::string& inMessage);
	
	static std::string TextureCacheFilename(const std::string& inName);
	
    static void BufferPurge(void);
    static void TexturePurge(void);
    static void Purge(void);
    
private:
	static void ThrowGLError(GLenum inGLErr);
	static void ThrowGLError(GLenum inGLErr, const std::string& inMessage);
	static void GLErrorWriteToLog(GLenum inGLErr);
	static void GLErrorWriteToLog(GLenum inGLErr, const std::string& inMessage);
	static std::string GLErrorString(const GLenum inGLErr);
	static Mushware::U32 m_glErrorCount;
};

inline void
MushGLUtil::ThrowIfGLError(void)
{
    GLenum glErr=glGetError();
    if (glErr != GL_NO_ERROR)
	{
		ThrowGLError(glErr);
	}
}

inline void
MushGLUtil::ThrowIfGLError(const std::string& inMessage)
{
    GLenum glErr=glGetError();
    if (glErr != GL_NO_ERROR)
	{
		ThrowGLError(glErr, inMessage);
	}
}

inline void
MushGLUtil::CheckGLError(void)
{
    GLenum glErr=glGetError();
    if (glErr != GL_NO_ERROR)
	{
		GLErrorWriteToLog(glErr);
	}
}

inline void
MushGLUtil::CheckGLError(const std::string& inMessage)
{
    GLenum glErr=glGetError();
    if (glErr != GL_NO_ERROR)
	{
		GLErrorWriteToLog(glErr, inMessage);
	}
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
