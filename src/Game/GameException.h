//%includeGuardStart {
#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H
//%includeGuardStart } TTpbuvFrG1hUXsIMkVJGvA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameException.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } kFBHkZfYMwvwo44EWWcSBA
/*
 * $Id: GameException.h,v 1.5 2003/08/21 23:08:44 southa Exp $
 * $Log: GameException.h,v $
 * Revision 1.5  2003/08/21 23:08:44  southa
 * Fixed file headers
 *
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



//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
