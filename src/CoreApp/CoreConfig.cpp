/*
 * $Id: CoreConfig.cpp,v 1.4 2002/05/30 14:41:13 southa Exp $
 * $Log$
 */

#include "CoreConfig.h"
#include "CoreException.h"

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
CoreConfig::ConfigExists(const string& inName) const
{
    return m_config.find(inName) != m_config.end();
}

void
CoreConfig::Pickle(ostream& inOut) const
{}

void
CoreConfig::Unpickle(CoreXML& inXML)
{}
