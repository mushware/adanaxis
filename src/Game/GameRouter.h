#ifndef GAMEROUTER_H
#define GAMEROUTER_H
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
 * $Id: GameRouter.h,v 1.10 2002/12/29 20:30:54 southa Exp $
 * $Log: GameRouter.h,v $
 * Revision 1.10  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.9  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/12/12 14:00:40  southa
 * Created Mustl
 *
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

#include "Mushcore.h"

#include "mushMedia.h"

class GameRouter : public MustlHandler
{
public:
    static inline GameRouter& Instance(void);

    void MessageHandle(MustlData& ioData, MustlLink& inLink, Mushware::U32 inType);

protected:
    void IDTransferHandle(MustlData& ioData, MustlLink& inLink);
    void NetObjectHandle(MustlData& ioData, const MustlLink& inLink);
    void ControlDataHandle(MustlData& ioData, const MustlLink& inLink);
    
private:
    static std::auto_ptr<GameRouter> m_instance;
};

inline GameRouter&
GameRouter::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new GameRouter);
    return *m_instance;
}
#endif
