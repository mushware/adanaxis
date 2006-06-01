//%includeGuardStart {
#ifndef GAMEROUTER_H
#define GAMEROUTER_H
//%includeGuardStart } IAInd09ZuYgsv6UH6RoDZQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameRouter.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } /KFDqjYZBhl5D1wx/12F/w
/*
 * $Id: GameRouter.h,v 1.22 2005/05/19 13:02:03 southa Exp $
 * $Log: GameRouter.h,v $
 * Revision 1.22  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.21  2005/03/13 00:34:46  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.20  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.19  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.18  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.17  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.16  2003/08/21 23:08:53  southa
 * Fixed file headers
 *
 * Revision 1.15  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.14  2003/01/18 17:05:46  southa
 * Singleton work
 *
 * Revision 1.13  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.12  2003/01/17 13:30:39  southa
 * Source conditioning and build fixes
 *
 * Revision 1.11  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
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

#include "mushMushcore.h"

#ifdef MUSHWARE_USE_MUSTL
#include "mushMustl.h"
#endif

class MustlData;
class MustlLink;

#ifdef MUSHWARE_USE_MUSTL
class GameRouter : public MustlMessageHandler, public MushcoreSingleton<GameRouter>
#else
class GameRouter : public MushcoreSingleton<GameRouter>
#endif
{
public:
    virtual ~GameRouter() {}
    virtual void MessageHandle(MustlData& ioData, MustlLink& inLink, Mushware::U32 inType);

protected:
    virtual void IDTransferHandle(MustlData& ioData, MustlLink& inLink);
    virtual void NetObjectHandle(MustlData& ioData, const MustlLink& inLink);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
