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
 * $Id: MushcoreEnv.cpp,v 1.6 2003/01/20 17:03:21 southa Exp $
 * $Log: MushcoreEnv.cpp,v $
 * Revision 1.6  2003/01/20 17:03:21  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.5  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.4  2003/01/17 13:30:40  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/12 17:32:59  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.17  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.16  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.15  2002/11/07 11:59:02  southa
 * Web commands
 *
 * Revision 1.14  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.11  2002/07/31 16:27:15  southa
 * Collision checking work
 *
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

#include "MushcoreEnv.h"
#include "MushcoreConfig.h"
#include "MushcoreFail.h"
#include "MushcoreScalar.h"

#include "MushcoreSTL.h"

#include "MushcoreGlobalConfig.h"

using namespace Mushware;
using namespace std;

MushcoreEnv *MushcoreEnv::m_instance=NULL;

MushcoreEnv::MushcoreEnv() :
    m_outStream(&cerr),
    m_outSet(false)
{
}

void
MushcoreEnv::PushConfig(MushcoreConfig& inConfig)
{
    m_config.push_back(&inConfig);
}

void
MushcoreEnv::PopConfig(MushcoreConfig& inConfig)
{
    if (m_config.empty())
    {
        throw(MushcoreLogicFail("Attempt to pop config from empty environment"));
    }
    if (m_config.back() != &inConfig)
    {
        throw(MushcoreLogicFail("Popped config does not match pushed"));
    }
    m_config.pop_back();
}

const MushcoreScalar&
MushcoreEnv::VariableGet(const string& inName) const
{
    static const MushcoreScalar undefined;
    for (vector<MushcoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        const MushcoreScalar *pScalar;
        if ((*p)->GetIfExists(pScalar, inName))
        {
            return *pScalar;
        }
    }
    return undefined;
}

bool
MushcoreEnv::VariableGetIfExists(const MushcoreScalar *& outScalar, const string& inName) const
{
    for (vector<MushcoreConfig *>::const_reverse_iterator p = m_config.rbegin();
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
MushcoreEnv::VariableExists(const string& inName) const
{
    for (vector<MushcoreConfig *>::const_reverse_iterator p = m_config.rbegin();
         p != m_config.rend(); ++p)
    {
        if ((*p)->Exists(inName))
        {
            return true;
        }
    }
    return false;
}

ostream&
MushcoreEnv::Out(void) const
{
    if (m_outStream == NULL)
    {
        throw(MushcoreLogicFail("Write to uninitialised output stream"));
    }
    return *m_outStream;
}

void
MushcoreEnv::OutSet(ostream& inOut)
{
    if (m_outSet)
    {
        throw(MushcoreLogicFail("Multiple MushcoreEnv::OutSets"));
    }
    
    m_outStream = &inOut;
    m_outSet=true;
}

void
MushcoreEnv::OutReset(void)
{
    if (!m_outSet)
    {
        throw(MushcoreLogicFail("MushcoreEnv::OutReset without OutSet"));
    }
    m_outStream = &cerr;
    m_outSet = false;
}

void
MushcoreEnv::NullFunction(void)
{
    // Make sure that the global config is linked in if Env is
    MushcoreGlobalConfig::NullFunction();
}
