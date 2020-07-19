//%includeGuardStart {
#ifndef MUSHGLUTIL_H
#define MUSHGLUTIL_H
//%includeGuardStart } rAQ4jcchYa85P6BeLBYvlA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLUtil.h
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
//%Header } jcIxJhMlDzC6z5XG3/RdnA
/*
 * $Id: MushGLUtil.h,v 1.8 2007/03/09 19:50:13 southa Exp $
 * $Log: MushGLUtil.h,v $
 * Revision 1.8  2007/03/09 19:50:13  southa
 * Resident textures
 *
 * Revision 1.7  2006/09/07 16:38:51  southa
 * Vertex shader
 *
 * Revision 1.6  2006/09/07 10:02:37  southa
 * Shader interface
 *
 * Revision 1.5  2006/07/08 16:05:58  southa
 * Ruby menus and key handling
 *
 * Revision 1.4  2006/06/30 15:05:33  southa
 * Texture and buffer purge
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

#include "API/mushMushMesh.h"

#include "MushGLAppHandler.h"

class MushGLUtil
{
public:
    static void IdentityPrologue(void);
    static void IdentityEpilogue(void);
    static void OrthoPrologue(void);
    static void OrthoEpilogue(void);
    static void UnitaryPrologue(void);
    static void UnitaryEpilogue(void);
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
    static void ShaderPurge(void);
    static void TexturePurge(void);
    static void TexturePurgeNonResident(void);
    static void Purge(void);
    static void PurgeNonResident(void);
    
    static void ShaderTest(void);

    static void ColourSet(const Mushware::t4Val& inColour);
    
    static void ProjectionMatrixSet(const Mushware::t4x4Val& inMatrix);
    static void ModelViewMatrixSet(const Mushware::t4x4Val& inMatrix);
    
    static std::string DataTypeToString(GLenum inType);
    
private:
    typedef GLfloat tGLMatrix[16];
    static void MatrixToGL(tGLMatrix& outMatrix, const Mushware::t4x4Val& inMatrix);

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
    for (Mushware::U32 i=0; i < 10; ++i) {
        GLenum glErr=glGetError();
        if (glErr == GL_NO_ERROR)
        {
            return;
        }
		GLErrorWriteToLog(glErr, inMessage);
	}
    GLErrorWriteToLog(GL_INVALID_OPERATION, "Too many errors - abandoning");
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
