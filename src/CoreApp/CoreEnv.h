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
 * $Id: CoreEnv.h,v 1.12 2002/11/07 11:59:02 southa Exp $
 * $Log: CoreEnv.h,v $
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
    bool VariableGetIfExists(Mushware::tVal& outValue, const string& inName) const;
    bool VariableGetIfExists(Mushware::U32& outValue, const string& inName) const;
    bool VariableGetIfExists(bool& outValue, const string& inName) const;
    bool VariableExists(const string& inName) const;
    void VariableSet(const string& inName, const string& inValue);
    std::ostream& Out(void) const;
    void OutSet(std::ostream& inOut);
    void OutReset(void);
    
private:
    CoreEnv();

    std::ostream *m_outStream;
    bool m_outSet;
    std::vector<CoreConfig *> m_config;
    static CoreEnv *m_instance;
};
#endif
