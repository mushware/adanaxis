/*
 * $Id$
 * $Log$
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
    U32 m_displayMode;
        
    static GameConfig *m_instance;
};
