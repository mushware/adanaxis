#ifndef MUSHCOREGLOBALCONFIG_H
#define MUSHCOREGLOBALCONFIG_H
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
 * $Id: MushcoreGlobalConfig.h,v 1.2 2003/01/11 13:03:17 southa Exp $
 * $Log: MushcoreGlobalConfig.h,v $
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
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

#include "MushcoreConfig.h"

class MushcoreGlobalConfig : public MushcoreConfig
{
public:
    static MushcoreGlobalConfig& Instance(void) {return *((m_instance==NULL)?m_instance=new MushcoreGlobalConfig:m_instance);}
    static void Install(void);
    static void NullFunction(void);
    
private:
    static MushcoreGlobalConfig *m_instance;
};
#endif
