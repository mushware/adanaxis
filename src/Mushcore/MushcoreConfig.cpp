/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreConfig.cpp,v 1.4 2003/01/17 13:30:40 southa Exp $
 * $Log: MushcoreConfig.cpp,v $
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
    map<string, MushcoreScalar>::const_iterator p = m_config.find(inName);
    
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
    map<string, MushcoreScalar>::const_iterator p = m_config.find(inName);
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
