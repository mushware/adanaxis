#ifndef COREENV_H
#define COREENV_H
/*
 * $Id: CoreEnv.h,v 1.2 2002/05/28 22:36:44 southa Exp $
 * $Log: CoreEnv.h,v $
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

    void PushConfig(const CoreConfig& inConfig);
    void PopConfig(const CoreConfig& inConfig);
    const CoreScalar& VariableGet(const string& inName) const;
    
private:
    CoreEnv() {}
    static CoreEnv *m_instance;
    vector<const CoreConfig *> m_config;
};
#endif
