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
 * $Id: CoreEnv.cpp,v 1.6 2002/05/30 14:41:13 southa Exp $
 * $Log: CoreEnv.cpp,v $
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
CoreEnv::PushConfig(const CoreConfig& inConfig)
{
    m_config.push_back(&inConfig);
}

void
CoreEnv::PopConfig(const CoreConfig& inConfig)
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
    for (vector<const CoreConfig *>::const_reverse_iterator p = m_config.rbegin();
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

