/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: CoreEnv.cpp,v 1.10 2002/07/07 13:44:18 southa Exp $
 * $Log: CoreEnv.cpp,v $
 * Revision 1.10  2002/07/07 13:44:18  southa
 * Screen size config variables
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
 * Revision 1.6  2002/05/30 14:41:13  southa
 * GameData and loadtilemap command
 *
 * Revision 1.5  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.4  2002/05/24 16:23:09  southa
 * Config and typenames
 *
 * Revision 1.3  2002/05/10 16:39:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/08 22:48:14  southa
 * Added first avarisse code
 *
 * Revision 1.1  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 */

#include "CoreEnv.h"
#include "CoreException.h"
#include "CoreScalar.h"
#include "CoreConfig.h"

CoreEnv::CoreEnv *CoreEnv::m_instance=NULL;

void
CoreEnv::PushConfig(CoreConfig& inConfig)
{
    m_config.push_back(&inConfig);
}

void
CoreEnv::PopConfig(CoreConfig& inConfig)
{
    if (m_config.empty())
    {
        throw(LogicFail("Attempt to pop config from empty environment"));
    }
    if (m_config.back() != &inConfig)
    {
        throw(LogicFail("Popped config does not match pushed"));
    }
    m_config.pop_back();
}

const CoreScalar&
CoreEnv::VariableGet(const string& inName) const
{
    static const CoreScalar undefined;
    for (vector<CoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        const CoreScalar *pScalar;
        if ((*p)->GetIfExists(&pScalar, inName))
        {
            return *pScalar;
        }
    }
    return undefined;
}

bool
CoreEnv::VariableGetIfExists(const CoreScalar** outScalar, const string& inName) const
{
    for (vector<CoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        if ((*p)->GetIfExists(outScalar, inName))
        {
            return true;
        }
    }
    return false;
}

bool
CoreEnv::VariableGetIfExists(string &outValue, const string& inName) const
{
    for (vector<CoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        const CoreScalar *pScalar;
        if ((*p)->GetIfExists(&pScalar, inName))
        {
            outValue=pScalar->StringGet();
            return true;
        }
        
    }
    return false;
}

bool
CoreEnv::VariableGetIfExists(U32 &outValue, const string& inName) const
{
    for (vector<CoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        const CoreScalar *pScalar;
        if ((*p)->GetIfExists(&pScalar, inName))
        {
            outValue=pScalar->U32Get();
            return true;
        }
    }
    return false;
}

bool
CoreEnv::VariableGetIfExists(tVal &outValue, const string& inName) const
{
    for (vector<CoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        const CoreScalar *pScalar;
        if ((*p)->GetIfExists(&pScalar, inName))
        {
            outValue=pScalar->ValGet();
            return true;
        }
    }
    return false;
}

bool
CoreEnv::VariableGetIfExists(bool &outValue, const string& inName) const
{
    for (vector<CoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        const CoreScalar *pScalar;
        if ((*p)->GetIfExists(&pScalar, inName))
        {
            outValue=pScalar->BoolGet();
            return true;
        }
    }
    return false;
}

bool
CoreEnv::VariableExists(const string& inName) const
{
    for (vector<CoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        if ((*p)->Exists(inName))
        {
            return true;
        }
    }
    return false;
}

void
CoreEnv::VariableSet(const string& inName, const string& inValue)
{
    COREASSERT(m_config.size() > 0);
    m_config.back()->Set(inName, inValue);
}

