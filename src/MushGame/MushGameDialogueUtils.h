//%includeGuardStart {
#ifndef MUSHGAMEDIALOGUEUTILS_H
#define MUSHGAMEDIALOGUEUTILS_H
//%includeGuardStart } BHJFI+AsgSb1foZeqscgEA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDialogueUtils.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } MIxrxZgr/TAeVG+WRRUt0Q
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameDialogue.h"

#include "API/mushGame.h"

class MushGameDialogueUtils
{
public:
    static void NamedDialoguesAdd(MushcoreData<MushGameDialogue>& outDialogues,
                                  const std::string& inRegExp);
    static void MoveAndRender(MushcoreData<MushGameDialogue>& ioDialogues,
                              GameAppHandler& inAppHandler);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
