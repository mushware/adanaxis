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
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0wC7hEfj2Np3orVXs4Kqzg
/*
 * $Id$
 * $Log$
 */

#include "Mushcore.h"
#include "Mustl.h"

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
