/*
 * $Id: GameRouter.h,v 1.3 2002/11/25 15:44:03 southa Exp $
 * $Log: GameRouter.h,v $
 * Revision 1.3  2002/11/25 15:44:03  southa
 * CreateObject message decoding
 *
 * Revision 1.2  2002/11/25 12:06:18  southa
 * Received net message routing
 *
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

    void MessageHandle(MediaNetData& ioData, const MediaNetLink& inLink, U32 inType);

protected:
    void CreateObjectHandle(MediaNetData& ioData, const MediaNetLink& inLink);
    
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
