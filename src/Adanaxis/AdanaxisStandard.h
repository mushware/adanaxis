//%includeGuardStart {
#ifndef ADANAXISSTANDARD_H
#define ADANAXISSTANDARD_H
//%includeGuardStart } TLqsFapGK+RvGkKMgZQ8nQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisStandard.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } J1Ivq58IhQNdFhYFAdJc+A
/*
 * $Id: AdanaxisStandard.h,v 1.6 2006/08/01 17:21:30 southa Exp $
 * $Log: AdanaxisStandard.h,v $
 * Revision 1.6  2006/08/01 17:21:30  southa
 * River demo
 *
 * Revision 1.5  2006/06/22 19:07:28  southa
 * Build fixes
 *
 * Revision 1.4  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:55  southa
 * Adanaxis creation
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#include <Mushcore/MushcoreIO.h>
#elif defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#include <MushcoreIO.h>
#else
#include "Mushcore/Mushcore.h"
#include "Mushcore/MushcoreIO.h"
#endif

#if defined(HAVE_MUSHMESH_MUSHMESH_H)
#include <MushMesh/MushMesh.h>
#elif defined(HAVE_MUSHMESH_H)
#include <MushMesh.h>
#else
#include "MushMesh/MushMesh.h"
#endif

#if defined(HAVE_MUSHRUBY_MUSHRUBY_H)
#include <MushRuby/MushRuby.h>
#elif defined(HAVE_MUSHRUBY_H)
#include <MushRuby.h>
#else
#include "MushRuby/MushRuby.h"
#endif

#include "mushGame.h"
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
