/*
 * $Id: GameConfig.h,v 1.1 2002/10/15 14:02:30 southa Exp $
 * $Log: GameConfig.h,v $
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
