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
 * $Id: CoreConfig.cpp,v 1.14 2002/12/17 12:53:33 southa Exp $
 * $Log: CoreConfig.cpp,v $
 * Revision 1.14  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.13  2002/11/24 23:18:03  southa
 * Added type name accessor to CorePickle
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

#include "CoreConfig.h"
#include "CoreException.h"

using namespace Mushware;

void
CoreConfig::Set(const string& inName, const CoreScalar& inValue)
{
    m_config[inName]=inValue;
}

const CoreScalar&
CoreConfig::Get(const string& inName) const
{
    map<string, CoreScalar>::const_iterator p = m_config.find(inName);
    
    if (p == m_config.end())
    {
        ostringstream out;
        out << "Config element '" << inName << "' not found";
        throw (ConfigFail(out.str()));
    }
    return p->second;
}

bool
CoreConfig::GetIfExists(const CoreScalar **outScalar, const string& inName) const
{
    map<string, CoreScalar>::const_iterator p = m_config.find(inName);
    if (p == m_config.end())
    {
        return false;
    }
    else
    {
        *outScalar=&p->second;
        return true;
    }
}

bool
CoreConfig::Exists(const string& inName) const
{
    return m_config.find(inName) != m_config.end();
}
