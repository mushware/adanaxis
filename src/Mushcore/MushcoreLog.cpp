//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreLog.cpp
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
//%Header } MhAxjeeiZYWSC7gGEzyqDA
/*
 * $Id: MushcoreLog.cpp,v 1.9 2007/04/18 09:23:10 southa Exp $
 * $Log: MushcoreLog.cpp,v $
 * Revision 1.9  2007/04/18 09:23:10  southa
 * Header and level fixes
 *
 * Revision 1.8  2006/08/02 15:41:47  southa
 * Prerelease work
 *
 * Revision 1.7  2006/06/01 15:39:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.5  2005/06/23 13:56:59  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/23 11:58:29  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.1  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 */

#include "MushcoreLog.h"

#include "MushcoreInfo.h"
#include "MushcoreSTL.h"
#include "MushcoreUtil.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushcoreLog);

MushcoreLog::MushcoreLog() :
    m_errorStream(NULL),
    m_stdStream(NULL),
    m_xmlErrorStream(NULL),
    m_xmlStdStream(NULL),
    m_enableErrorLog(true),
#ifdef MUSHCORE_DEBUG
    m_enableWarningLog(true),
    m_enableInfoLog(true),
#else
    m_enableWarningLog(true),
    m_enableInfoLog(true),
#endif
    m_errorHeaderDone(false),
    m_stdHeaderDone(false)
{
    m_nullStream = new ostringstream;
}

MushcoreLog::~MushcoreLog()
{
    delete m_nullStream;
    delete m_xmlErrorStream;
    delete m_xmlStdStream;    
}

void
MushcoreLog::HeaderWrite(ostream& ioOut, const std::string inLogName)
{
    ioOut << MushcoreUtil::LogTimeString() << ": Package " << MushcoreInfo::Sgl().PackageID() << " " << inLogName << endl;
}

void
MushcoreLog::PackageHasChanged(void)
{
    m_errorHeaderDone = false;
    m_stdHeaderDone = false;
}

ostream&
MushcoreLog::ErrorStream(void)
{
    ostream *retStream;
    if (m_errorStream == NULL)
    {
        retStream = &std::cerr;
    }
    else
    {
        retStream = m_errorStream;
    }
    if (!m_errorHeaderDone)
    {
        HeaderWrite(*retStream, "error log");
        m_errorHeaderDone = true;
    }
    return *retStream;
}

ostream&
MushcoreLog::StdStream(void)
{
    ostream *retStream;
    if (m_stdStream == NULL)
    {
        retStream = &std::cout;
    }
    else
    {
        retStream = m_stdStream;
    }
    if (!m_stdHeaderDone)
    {
        HeaderWrite(*retStream, "standard log");
        m_stdHeaderDone = true;
    }
    return *retStream;
}

MushcoreXMLOStream&
MushcoreLog::XMLErrorStream(void)
{
    if (m_xmlErrorStream == NULL)
    {
        m_xmlErrorStream = new MushcoreXMLOStream(ErrorStream());
    }
    
    return *m_xmlErrorStream;
}

MushcoreXMLOStream&
MushcoreLog::XMLStdStream(void)
{
    if (m_xmlStdStream == NULL)
    {
        m_xmlStdStream = new MushcoreXMLOStream(StdStream());
    }
    
    return *m_xmlStdStream;
}

ostream&
MushcoreLog::ErrorLog(void)
{
    ostream *retStream;
    if (m_enableErrorLog)
    {
        retStream = &ErrorStream();
    }
    else
    {
        m_nullStream->clear();
        retStream = m_nullStream;
    }
    *retStream << MushcoreUtil::LogTimeString() << ": Error: ";
    return *retStream;
}

ostream&
MushcoreLog::WarningLog(void)
{
    ostream *retStream;
    if (m_enableWarningLog)
    {
        retStream = &ErrorStream();
    }
    else
    {
        m_nullStream->clear();
        retStream = m_nullStream;
    }
    *retStream << MushcoreUtil::LogTimeString() << ": Warning: ";
    return *retStream;
}

ostream&
MushcoreLog::InfoLog(void)
{
    ostream *retStream;
    if (m_enableInfoLog)
    {
        retStream = &StdStream();
    }
    else
    {
        m_nullStream->clear();
        retStream = m_nullStream;
    }
    *retStream << MushcoreUtil::LogTimeString() << ": Info: ";
    return *retStream;
}

MushcoreXMLOStream&
MushcoreLog::XMLErrorLog(void)
{
    MushcoreXMLOStream *retStream = &XMLErrorStream();
    retStream->OStream() << MushcoreUtil::LogTimeString() << ": Error: ";
    return *retStream;
}


MushcoreXMLOStream&
MushcoreLog::XMLWarningLog(void)
{
    MushcoreXMLOStream *retStream = &XMLErrorStream();
    retStream->OStream() << MushcoreUtil::LogTimeString() << ": Warning: ";
    return *retStream;
}

MushcoreXMLOStream&
MushcoreLog::XMLInfoLog(void)
{
    MushcoreXMLOStream *retStream = &XMLStdStream();
    retStream->OStream() << MushcoreUtil::LogTimeString() << ": Info: ";
    return *retStream;
}
