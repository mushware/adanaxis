/*
 * $Id: GameRouter.h,v 1.7 2002/12/07 18:32:15 southa Exp $
 * $Log: GameRouter.h,v $
 * Revision 1.7  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.6  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 * Revision 1.5  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.4  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
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

class GameRouter : public MustlHandler
{
public:
    static inline GameRouter& Instance(void);

    void MessageHandle(MustlData& ioData, MustlLink& inLink, U32 inType);

protected:
    void IDTransferHandle(MustlData& ioData, MustlLink& inLink);
    void NetObjectHandle(MustlData& ioData, const MustlLink& inLink);
    void ControlDataHandle(MustlData& ioData, const MustlLink& inLink);
    
private:
    static auto_ptr<GameRouter> m_instance;
};

inline GameRouter&
GameRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new GameRouter);
    return *m_instance;
}
