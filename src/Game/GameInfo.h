//%includeGuardStart {
#ifndef GAMEINFO_H
#define GAMEINFO_H
//%includeGuardStart } xuW7aOgY537aYBFCtpOy+g
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameInfo.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } hiixk1c31tPCzwMmFzo7dg
/*
 * $Id: GameInfo.h,v 1.3 2003/08/21 23:08:47 southa Exp $
 * $Log: GameInfo.h,v $
 * Revision 1.3  2003/08/21 23:08:47  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.1  2003/03/11 22:15:09  southa
 * Added GameInfo
 *
 */

#include "Mushcore.h"

class GameInfo : public MushcoreInfo
{
public:
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);

    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
