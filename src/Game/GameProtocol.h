/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaNetLink;

class GameProtocol
{
public:
    static void SendObject(MediaNetLink& inLink, CorePickle& inObj, const string& inRemoteName);

private:
};
