//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreConfig.cpp
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
//%Header } E6YY1qH1eeSZTOvQMaZIig
/*
 * $Id: MushcoreConfig.cpp,v 1.11 2006/06/01 15:39:42 southa Exp $
 * $Log: MushcoreConfig.cpp,v $
 * Revision 1.11  2006/06/01 15:39:42  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:09  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.5  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.4  2003/01/17 13:30:40  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.2  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.16  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.15  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.13  2002/11/24 23:18:03  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.12  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.11  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.9  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.8  2002/07/02 14:27:12  southa
 * First floor map designer build
 *
 * Revision 1.7  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.6  2002/06/04 14:11:21  southa
 * Traits loader first stage
 *
 * Revision 1.5  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 */

#include "MushcoreConfig.h"
#include "MushcoreFail.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

const MushcoreScalar&
MushcoreConfig::Get(const string& inName) const
{
    map<std::string, MushcoreScalar>::const_iterator p = m_config.find(inName);
    
    if (p == m_config.end())
    {
        ostringstream message;
        message << "Config element '" << inName << "' not found";
        throw (MushcoreDataFail(message.str()));
    }
    return p->second;
}

bool
MushcoreConfig::GetIfExists(const MushcoreScalar *& outScalar, const string& inName) const
{
    map<std::string, MushcoreScalar>::const_iterator p = m_config.find(inName);
    if (p == m_config.end())
    {
        return false;
    }
    else
    {
        outScalar=&p->second;
        return true;
    }
}

bool
MushcoreConfig::Exists(const string& inName) const
{
    return m_config.find(inName) != m_config.end();
}
