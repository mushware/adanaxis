#ifndef MUSHCOREENV_H
#define MUSHCOREENV_H
#ifndef COREENV_H
#define COREENV_H
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
 * $Id: MushcoreEnv.h,v 1.14 2002/12/29 20:30:51 southa Exp $
 * $Log: MushcoreEnv.h,v $
 * Revision 1.14  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.13  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/11/07 11:59:02  southa
 * Web commands
 *
 * Revision 1.11  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/31 16:27:15  southa
 * Collision checking work
 *
 * Revision 1.7  2002/07/07 13:44:18  southa
 * Screen size config variables
 *
 * Revision 1.6  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.5  2002/07/02 14:27:12  southa
 * First floor std::map designer build
 *
 * Revision 1.4  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/30 14:41:13  southa
 * GameData and loadtilemap command
 *
 * Revision 1.2  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "MushcoreStandard.h"

class MushcoreConfig;
class MushcoreScalar;

class MushcoreEnv
{
public:
    static MushcoreEnv& Instance(void) {return *((m_instance==NULL)?m_instance=new MushcoreEnv:m_instance);}

    void PushConfig(MushcoreConfig& inConfig);
    void PopConfig(MushcoreConfig& inConfig);
    const MushcoreScalar& VariableGet(const std::string& inName) const;
    bool VariableGetIfExists(const MushcoreScalar** outScalar, const std::string& inName) const;
    bool VariableGetIfExists(std::string& outValue, const std::string& inName) const;
    bool VariableGetIfExists(Mushware::tVal& outValue, const std::string& inName) const;
    bool VariableGetIfExists(Mushware::U32& outValue, const std::string& inName) const;
    bool VariableGetIfExists(bool& outValue, const std::string& inName) const;
    bool VariableExists(const std::string& inName) const;
    void VariableSet(const std::string& inName, const std::string& inValue);
    std::ostream& Out(void) const;
    void OutSet(std::ostream& inOut);
    void OutReset(void);
    
private:
    MushcoreEnv();

    std::ostream *m_outStream;
    bool m_outSet;
    std::vector<MushcoreConfig *> m_config;
    static MushcoreEnv *m_instance;
};
#endif
#endif
