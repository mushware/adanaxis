/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameGlobalConfig : public CoreConfig
{
public:
    static GameGlobalConfig& Instance(void) {return *((m_instance==NULL)?m_instance=new GameGlobalConfig:m_instance);}

private:
    static GameGlobalConfig *m_instance;
};
