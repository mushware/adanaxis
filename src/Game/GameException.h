#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H
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
 * $Id: GameException.h,v 1.2 2002/12/20 13:17:39 southa Exp $
 * $Log: GameException.h,v $
 * Revision 1.2  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/13 01:07:25  southa
 * Mustl work
 *
 */

#include "mushCore.h"

#include "Mustl.h"

// Blanket exception to cover all non-fatal network failures
class NetworkFail : public MustlFail
{
public:
    NetworkFail(const std::string& inMessage);
};

inline
NetworkFail::NetworkFail(const std::string& inMessage) :
    MustlFail(inMessage)
{}



#endif
