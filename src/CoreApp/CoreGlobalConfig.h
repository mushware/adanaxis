/*
 * $Id$
 * $Log$
 */

#include "CoreConfig.h"

class CoreGlobalConfig : public CoreConfig
{
public:
    static CoreGlobalConfig& Instance(void) {return *((m_instance==NULL)?m_instance=new CoreGlobalConfig:m_instance);}

private:
    static CoreGlobalConfig *m_instance;
};
