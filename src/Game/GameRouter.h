/*
 * $Id: GameRouter.h,v 1.1 2002/11/25 10:43:28 southa Exp $
 * $Log: GameRouter.h,v $
 * Revision 1.1  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 */

#include "mushCore.h"
#include "mushMedia.h"

class GameRouter : public MediaNetHandler
{
public:
    static inline GameRouter& Instance(void);

    void MessageHandle(MediaNetData& ioData, U32 inType);

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

