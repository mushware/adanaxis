//%includeGuardStart {
#ifndef TESTMUSHPIEPIECES_H
#define TESTMUSHPIEPIECES_H
//%includeGuardStart } m33WbJWvRZbCH8H/4tVjHg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushPie/TestMushPiePieces.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } COeZzImM4EJJdfHjXmcd1A
/*
 * $Id$
 * $Log$
 */

#include "TestMushPieStandard.h"

class TestMushPiePieces
{
public:
    static MushPiePosicity TestPosMake(Mushware::tVal inKey);
    static MushcoreScalar TestPieces(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
