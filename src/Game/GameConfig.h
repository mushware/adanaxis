#ifndef GAMECONFIG_H
#define GAMECONFIG_H
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
 * $Id: GameConfig.h,v 1.2 2002/10/17 15:50:58 southa Exp $
 * $Log: GameConfig.h,v $
 * Revision 1.2  2002/10/17 15:50:58  southa
 * Config saving, pause and quit
 *
 * Revision 1.1  2002/10/15 14:02:30  southa
 * Mode changes
 *
 */

#include "mushCore.h"

class GameConfig
{
public:
    static GameConfig& Instance(void) {return *((m_instance==NULL)?m_instance=new GameConfig:m_instance);}
    
    U32 DisplayModeGet(void) const { return m_displayMode; }
    void DisplayModeSet(U32 inMode);
    void DisplayModeSetDefault(void);

protected:
    GameConfig();

private:
    void SaveToFile(void) const;

    U32 m_displayMode;
        
    static GameConfig *m_instance;
};
#endif
