#ifndef GAMEGLOBALCONFIG_H
#define GAMEGLOBALCONFIG_H
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
 * $Id: GameGlobalConfig.h,v 1.1 2002/05/28 13:05:55 southa Exp $
 * $Log: GameGlobalConfig.h,v $
 * Revision 1.1  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "mushCore.h"

class GameGlobalConfig : public CoreConfig
{
public:
    static GameGlobalConfig& Instance(void) {return *((m_instance==NULL)?m_instance=new GameGlobalConfig:m_instance);}

private:
    static GameGlobalConfig *m_instance;
};
#endif
