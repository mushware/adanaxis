//%includeGuardStart {
#ifndef INFERNALROUTER_H
#define INFERNALROUTER_H
//%includeGuardStart } jWV6eVEu8iBfS1zcznjhqA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalRouter.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } y93vGFiaLTzZGoBb1nB26A
/*
 * $Id: InfernalRouter.h,v 1.2 2004/01/02 21:13:09 southa Exp $
 * $Log: InfernalRouter.h,v $
 * Revision 1.2  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/04 15:32:11  southa
 * Module split
 *
 */

#include "mushMushcore.h"
#include "mushMustl.h"

#include "mushGame.h"

class InfernalRouter : public GameRouter
{
public:
    virtual void MessageHandle(MustlData& ioData, MustlLink& inLink, Mushware::U32 inType);

protected:
    void ControlDataHandle(MustlData& ioData, const MustlLink& inLink); 

};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
