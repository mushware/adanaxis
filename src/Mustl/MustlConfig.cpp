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
 * $Id: MustlConfig.cpp,v 1.3 2003/01/13 23:05:22 southa Exp $
 * $Log: MustlConfig.cpp,v $
 * Revision 1.3  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.2  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.1  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 */

#include "MustlConfig.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

auto_ptr<MustlConfig> MustlConfig::m_instance;

MustlConfig::MustlConfig() :
    m_config(new MushcoreConfig)
{
}

MustlConfig::~MustlConfig()
{
    delete m_config;
}

void
MustlConfig::Set(const string& inName, const MushcoreScalar& inValue)
{
    m_config->Set(inName, inValue);
}

void
MustlConfig::Set(const string& inName, const string& inStr)
{
    m_config->Set(inName, inStr);
}

void
MustlConfig::Set(const string& inName, const Mustl::U32& inValue)
{
    m_config->Set(inName, inValue);
}

const MushcoreScalar&
MustlConfig::Get(const string& inName) const
{
    return m_config->Get(inName);
}

bool
MustlConfig::GetIfExists(const MushcoreScalar **outScalar, const string& inName) const
{
    return m_config->GetIfExists(outScalar, inName);
}

bool
MustlConfig::Exists(const std::string& inName) const
{
    return m_config->Exists(inName);
}


