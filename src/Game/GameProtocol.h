/*
 * $Id: GameProtocol.h,v 1.8 2002/12/09 23:59:58 southa Exp $
 * $Log: GameProtocol.h,v $
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
 * Added type name accessor to CorePickle
 *
 */

#include "mushCore.h"

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

    static void CreateObjectCreate(MustlData& ioData, CorePickle& inObj, const string& inRemoteName);
    static void DeleteObjectCreate(MustlData& ioData, CorePickle& inObj, const string& inRemoteName);
    
private:
};
