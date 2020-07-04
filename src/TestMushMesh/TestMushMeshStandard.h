//%includeGuardStart {
#ifndef TESTMUSHMESHSTANDARD_H
#define TESTMUSHMESHSTANDARD_H
//%includeGuardStart } W1k1jF6GZUYd6q1MA9D7LQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshStandard.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } ks1p/QQG82cvMMvpnnXMzQ
/*
 * $Id: TestMushMeshStandard.h,v 1.9 2006/06/22 19:07:38 southa Exp $
 * $Log: TestMushMeshStandard.h,v $
 * Revision 1.9  2006/06/22 19:07:38  southa
 * Build fixes
 *
 * Revision 1.8  2006/06/01 15:40:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
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

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
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
