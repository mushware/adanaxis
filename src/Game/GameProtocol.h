//%includeGuardStart {
#ifndef GAMEPROTOCOL_H
#define GAMEPROTOCOL_H
//%includeGuardStart } 9Utdw7esszYs/6+AswxmPA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameProtocol.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KpPbooo+WmuTQJm5BO2hWA
/*
 * $Id: GameProtocol.h,v 1.15 2003/09/17 19:40:33 southa Exp $
 * $Log: GameProtocol.h,v $
 * Revision 1.15  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:08:52  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.12  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.10  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/12/12 14:00:40  southa
 * Created Mustl
 *
 * Revision 1.8  2002/12/09 23:59:58  southa
 * Network control
 *
 * Revision 1.7  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.6  2002/12/06 17:38:01  southa
 * ControlData message unpacking
 *
 * Revision 1.5  2002/12/06 11:11:16  southa
 * Send control information
 *
 * Revision 1.4  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 * Revision 1.3  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.2  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.1  2002/11/24 23:18:24  southa
 * Added type name accessor to MushcorePickle
 *
 */

#include "Mushcore.h"

#include "GameControlFrameDef.h"

class MustlData;

class GameProtocol
{
public:
    enum tMessageType
    {
        kMessageTypeIDTransfer,
        kMessageTypeCreateObject,
        kMessageTypeDeleteObject,
        kMessageTypeControlData
    };

    static void CreateObjectCreate(MustlData& ioData, MushcorePickle& inObj, const std::string& inRemoteName);
    static void DeleteObjectCreate(MustlData& ioData, MushcorePickle& inObj, const std::string& inRemoteName);
    
private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
