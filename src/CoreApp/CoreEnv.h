#ifndef COREENV_H
#define COREENV_H
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
 * $Id: CoreEnv.h,v 1.8 2002/07/31 16:27:15 southa Exp $
 * $Log: CoreEnv.h,v $
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
 * First floor map designer build
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

#include "CoreStandard.h"

class CoreConfig;
class CoreScalar;

class CoreEnv
{
public:
    static CoreEnv& Instance(void) {return *((m_instance==NULL)?m_instance=new CoreEnv:m_instance);}

    void PushConfig(CoreConfig& inConfig);
    void PopConfig(CoreConfig& inConfig);
    const CoreScalar& VariableGet(const string& inName) const;
    bool VariableGetIfExists(const CoreScalar** outScalar, const string& inName) const;
    bool VariableGetIfExists(string& outValue, const string& inName) const;
    bool VariableGetIfExists(tVal& outValue, const string& inName) const;
    bool VariableGetIfExists(U32& outValue, const string& inName) const;
    bool VariableGetIfExists(bool& outValue, const string& inName) const;
    bool VariableExists(const string& inName) const;
    void VariableSet(const string& inName, const string& inValue);
    
private:
    CoreEnv() {}
    static CoreEnv *m_instance;
    vector<CoreConfig *> m_config;
};
#endif
