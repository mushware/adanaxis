/*
 * $Id: CoreGlobalConfig.h,v 1.1 2002/05/28 13:07:04 southa Exp $
 * $Log: CoreGlobalConfig.h,v $
 * Revision 1.1  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "CoreConfig.h"

class CoreGlobalConfig : public CoreConfig
{
public:
    static CoreGlobalConfig& Instance(void) {return *((m_instance==NULL)?m_instance=new CoreGlobalConfig:m_instance);}
    static void Install(void);
    
private:
    static CoreGlobalConfig *m_instance;
};
