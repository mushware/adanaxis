#ifndef COREGLOBALCONFIG_H
#define COREGLOBALCONFIG_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreGlobalConfig.h,v 1.6 2002/08/27 08:56:17 southa Exp $
 * $Log: CoreGlobalConfig.h,v $
 * Revision 1.6  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
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
