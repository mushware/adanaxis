//%includeGuardStart {
#ifndef GAMEUTILS_H
#define GAMEUTILS_H
//%includeGuardStart } tnIW58cbpoexh5GV89K1gQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 1HRLY36l0fDdeXDF6UkrqA
/*
 * $Id$
 * $Log$
 */

#include "mushMushcore.h"

class GameUtils
{
public:
    static Mushware::U32 Rotate(Mushware::U32 inVal, Mushware::U32 inRot);
    static bool CodeVerify(const std::string& inCode);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
