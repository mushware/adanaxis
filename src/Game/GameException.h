#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameException.h,v 1.4 2003/01/11 13:03:13 southa Exp $
 * $Log: GameException.h,v $
 * Revision 1.4  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.3  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.2  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/13 01:07:25  southa
 * Mustl work
 *
 */

#include "Mushcore.h"

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
