//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlLog.cpp
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
//%Header } KjT3LxkDY1BmxNidA5LFmg
/*
 * $Id: MustlLog.cpp,v 1.15 2006/06/01 15:39:52 southa Exp $
 * $Log: MustlLog.cpp,v $
 * Revision 1.15  2006/06/01 15:39:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.14  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.13  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.12  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:09:27  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/02/04 19:07:12  southa
 * Build fixes
 *
 * Revision 1.9  2003/01/20 10:45:30  southa
 * Singleton tidying
 *
 * Revision 1.8  2003/01/17 12:20:40  southa
 * Fixed auto_ptr duplication
 *
 * Revision 1.7  2003/01/17 00:41:03  southa
 * Configuration updates from POST data
 *
 * Revision 1.6  2002/12/29 20:59:59  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/12/17 12:53:34  southa
 * Mustl library
 *
 * Revision 1.3  2002/12/14 15:04:34  southa
 * Mustl fixes
 *
 * Revision 1.2  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:26  southa
 * Created Mustl
 *
 * Revision 1.5  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.4  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.3  2002/11/08 11:54:40  southa
 * Web fixes
 *
 * Revision 1.2  2002/11/07 00:53:37  southa
 * localweb work
 *
 * Revision 1.1  2002/11/04 15:50:31  southa
 * Network log
 *
 */

#include "MustlLog.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

MustlLog MustlLog::m_gMustlLogInstance;

MushcoreInstaller MustlLogInstaller(MustlLog::Install);

MustlLog::MustlLog() :
    m_outStream(NULL),
    m_netLog(true),
    m_webLog(true),
    m_verboseLog(false),
    m_trafficLog(false),
    m_logFullIP(false)
{
    m_nullStream = new ostringstream;
}

MustlLog::~MustlLog()
{
    if (m_outStream != NULL) delete m_outStream;
    delete m_nullStream;
}

ostream&
MustlLog::Log(void)
{
    ostream *retStream;
    if (m_outStream == NULL)
    {
        retStream = &cout;
    }
    else
    {
        retStream = m_outStream;
    }
    *retStream << MustlTimer::Sgl().CurrentMsecGet() << ": ";
    return *retStream;
}

ostream&
MustlLog::NetLog(void)
{
    if (m_netLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

ostream&
MustlLog::WebLog(void)
{
    if (m_webLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

ostream&
MustlLog::VerboseLog(void)
{
    if (m_verboseLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

ostream&
MustlLog::TrafficLog(void)
{
    if (m_trafficLog)
    {
        return Log();
    }
    else
    {
        m_nullStream->clear();
        return *m_nullStream;
    }
}

void
MustlLog::OpenFile(const string& inName)
{
    MUSTLASSERT(false);
}

void
MustlLog::CloseFile(void)
{
    if (m_outStream != NULL) delete m_outStream;
    m_outStream=NULL;
}

void
MustlLog::UpdateHandler(void)
{
    cerr << "MustlLog::UpdateHandler called" << endl;
    MushcoreScalar configValue;
    if (MustlConfig::Sgl().GetIfExists(configValue, "mustlnetlog"))
    {
        Sgl().NetLogSet(configValue.BoolGet());
    }
    if (MustlConfig::Sgl().GetIfExists(configValue, "mustlweblog"))
    {
        Sgl().WebLogSet(configValue.BoolGet());
    }
    if (MustlConfig::Sgl().GetIfExists(configValue, "mustlverboselog"))
    {
        Sgl().VerboseLogSet(configValue.BoolGet());
    }
    if (MustlConfig::Sgl().GetIfExists(configValue, "mustltrafficlog"))
    {
        Sgl().TrafficLogSet(configValue.BoolGet());
    }
    if (MustlConfig::Sgl().GetIfExists(configValue, "mustlcommandlog"))
    {
        if (configValue.BoolGet())
        {
            MushcoreInterpreter::Sgl().LogFunctionSet(LogString);
        }
        else
        {
            MushcoreInterpreter::Sgl().LogFunctionSet(NULL);
        }      
    }
}

void
MustlLog::LogString(const string& inStr)
{
    Sgl().Log() << inStr << endl;
}

void
MustlLog::Install(void)
{
    MustlConfig::Sgl().UpdateHandlerAdd(UpdateHandler);
}

void
MustlLog::NullFunction(void)
{
}
