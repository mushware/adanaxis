#ifndef COREGLOBALCONFIG_H
#define COREGLOBALCONFIG_H
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
 * $Id: CoreGlobalConfig.h,v 1.2 2002/05/30 14:41:15 southa Exp $
 * $Log: CoreGlobalConfig.h,v $
 * Revision 1.2  2002/05/30 14:41:15  southa
 * GameData and loadtilemap command
 *
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
#endif
