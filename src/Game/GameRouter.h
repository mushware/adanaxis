/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameRouter
{
public:
    static inline GameRouter& Instance(void);



private:
    static auto_ptr<GameRouter> m_instance;
};

inline  GameRouter&
GameRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new GameRouter);
    return *m_instance;
}

