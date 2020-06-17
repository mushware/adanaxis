//%includeGuardStart {
#ifndef MUSHCORELOG_H
#define MUSHCORELOG_H
//%includeGuardStart } Lz/+CPk+eWXGveU5A8W9jw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreLog.h
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
//%Header } A//1FGka2q6X4W5AWExTtQ
/*
 * $Id: MushcoreLog.h,v 1.7 2006/06/01 15:39:45 southa Exp $
 * $Log: MushcoreLog.h,v $
 * Revision 1.7  2006/06/01 15:39:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.5  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.4  2005/06/23 11:58:29  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.1  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreFail.h"
#include "MushcoreSingleton.h"
#include "MushcoreXMLOStream.h"

//:generate
class MushcoreLog : public MushcoreSingleton<MushcoreLog>
{
public:
    MushcoreLog();
    ~MushcoreLog();
    
    std::ostream& ErrorLog(void);
    std::ostream& WarningLog(void);
    std::ostream& InfoLog(void);
    MushcoreXMLOStream& XMLErrorLog(void);
    MushcoreXMLOStream& XMLWarningLog(void);
    MushcoreXMLOStream& XMLInfoLog(void);
    
    void HeaderWrite(std::ostream& ioOut, const std::string inLogName);
    void PackageHasChanged(void);
    
protected:
    std::ostream& ErrorStream(void);
    std::ostream& StdStream(void);
    MushcoreXMLOStream& XMLErrorStream(void);
    MushcoreXMLOStream& XMLStdStream(void);
    
private:
    MUSHCORE_NOCOPY(MushcoreLog);
    std::ofstream *m_errorStream;
    std::ofstream *m_stdStream;
    MushcoreXMLOStream *m_xmlErrorStream;
    MushcoreXMLOStream *m_xmlStdStream;
    
    std::ostream *m_nullStream;
    
    bool m_enableErrorLog; //:readwrite
    bool m_enableWarningLog; //:readwrite
    bool m_enableInfoLog; //:readwrite
    bool m_errorHeaderDone;
    bool m_stdHeaderDone;
//%classPrototypes {
public:
    const bool& EnableErrorLog(void) const { return m_enableErrorLog; }
    void EnableErrorLogSet(const bool& inValue) { m_enableErrorLog=inValue; }
    const bool& EnableWarningLog(void) const { return m_enableWarningLog; }
    void EnableWarningLogSet(const bool& inValue) { m_enableWarningLog=inValue; }
    const bool& EnableInfoLog(void) const { return m_enableInfoLog; }
    void EnableInfoLogSet(const bool& inValue) { m_enableInfoLog=inValue; }
//%classPrototypes } MZ4jgKhQvs0+TVUvwQK45Q
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
