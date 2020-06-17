//%includeGuardStart {
#ifndef MAURHEENSTANDARD_H
#define MAURHEENSTANDARD_H
//%includeGuardStart } eGZvmJVCleze7dyFJx60ig
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenStandard.h
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
//%Header } Zn3ZpAOX2UA0kRYKLSQ9Uw
/*
 * $Id: MaurheenStandard.h,v 1.4 2006/06/22 19:07:30 southa Exp $
 * $Log: MaurheenStandard.h,v $
 * Revision 1.4  2006/06/22 19:07:30  southa
 * Build fixes
 *
 * Revision 1.3  2006/06/01 15:39:12  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.1  2004/03/07 12:05:56  southa
 * Rendering work
 *
 */

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

#if defined(HAVE_MUSHPIE_MUSHPIE_H)
#include <MushPie/MushPie.h>
#elif defined(HAVE_MUSHPIE_H)
#include <MushPie.h>
#else
#include "MushPie/MushPie.h"
#endif

#if defined(HAVE_MUSHMODEL_MUSHMODEL_H)
#include <MushModel/MushModel.h>
#elif defined(HAVE_MUSHMODEL_H)
#include <MushModel.h>
#else
#include "MushModel/MushModel.h"
#endif

#include "mushGame.h"
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
