/*
 * $Id: GameProtocol.h,v 1.2 2002/11/25 10:43:28 southa Exp $
 * $Log: GameProtocol.h,v $
 * Revision 1.2  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.1  2002/11/24 23:18:24  southa
 * Added type name accessor to CorePickle
 *
 */

#include "mushCore.h"

class MediaNetData;

class GameProtocol
{
public:
    enum tMessageType
    {
        kMessageTypeInvalid,
        kMessageTypeCreateObject,
        kMessageTypeDeleteObject
    };

    static void CreateObjectCreate(MediaNetData& ioData, CorePickle& inObj, const string& inRemoteName);
    static void DeleteObjectCreate(MediaNetData& ioData, CorePickle& inObj, const string& inRemoteName);

private:
};
