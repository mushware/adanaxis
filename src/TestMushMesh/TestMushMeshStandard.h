//%includeGuardStart {
#ifndef TESTMUSHMESHSTANDARD_H
#define TESTMUSHMESHSTANDARD_H
//%includeGuardStart } W1k1jF6GZUYd6q1MA9D7LQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshStandard.h
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
//%Header } Thhd451+Uw5oCuW9+FveAg
/*
 * $Id: TestMushMeshStandard.h,v 1.6 2005/05/19 13:02:23 southa Exp $
 * $Log: TestMushMeshStandard.h,v $
 * Revision 1.6  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/07 11:14:15  southa
 * Snapshot fixes
 *
 * Revision 1.4  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.3  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/15 12:23:10  southa
 * MushMeshArray neighbour testing and subdivision work
 *
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
#elif defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#else
#include "Mushcore/Mushcore.h"
#endif

#if defined(HAVE_MUSHMESH_MUSHMESH_H)
#include <MushMesh/MushMesh.h>
#elif defined(HAVE_MUSHMESH_H)
#include <MushMesh.h>
#else
#include "MushMesh/MushMesh.h"
#endif

#if defined(HAVE_MUSHMESHLIBRARY_MUSHMESHLIBRARY_H)
#include <MushMeshLibrary/MushMeshLibrary.h>
#elif defined(HAVE_MUSHMESHLIBRARY_H)
#include <MushMeshLibrary.h>
#else
#include "MushMeshLibrary/MushMeshLibrary.h"
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
