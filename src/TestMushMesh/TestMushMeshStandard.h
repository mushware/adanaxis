//%includeGuardStart {
#ifndef TESTMUSHMESHSTANDARD_H
#define TESTMUSHMESHSTANDARD_H
//%includeGuardStart } W1k1jF6GZUYd6q1MA9D7LQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshStandard.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } HU4NhFLQ2laR8JEiClGoXA
/*
 * $Id: TestMushMeshStandard.h,v 1.1 2003/10/14 13:07:26 southa Exp $
 * $Log: TestMushMeshStandard.h,v $
 * Revision 1.1  2003/10/14 13:07:26  southa
 * MushMesh vector creation
 *
 */

// Include everything we might need to keep things simple

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore.h"
#endif
#endif

#if defined(HAVE_MUSHMESH_MUSHMESH_H)
#include <MushMesh/MushMesh.h>
#else
#if defined(HAVE_MUSHMESH_H)
#include <MushMesh.h>
#else
#include "MushMesh.h"
#endif
#endif

#include <list>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include <fstream>
#include <iomanip>
#include <iostream>

#ifdef HAVE_SSTREAM
#include <sstream>
#else
#include "sstream"
#endif

#include <typeinfo>

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <ctime>
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
