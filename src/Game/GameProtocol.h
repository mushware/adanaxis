/*
 * $Id: GameProtocol.h,v 1.1 2002/11/24 23:18:24 southa Exp $
 * $Log: GameProtocol.h,v $
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
        kMessageTypeCreateObject
    };

    static void CreateObjectCreate(MediaNetData& ioData, CorePickle& inObj, const string& inRemoteName);

private:
};
