//%includeGuardStart {
#ifndef INFERNALSTANDARD_H
#define INFERNALSTANDARD_H
//%includeGuardStart } ulOAN1Ly/JYyzPqGP7P/bg
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalStandard.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } LFutKxI4aHZ5o+Mgt8fYQw
/*
 * $Id: InfernalStandard.h,v 1.5 2006/06/22 19:07:30 southa Exp $
 * $Log: InfernalStandard.h,v $
 * Revision 1.5  2006/06/22 19:07:30  southa
 * Build fixes
 *
 * Revision 1.4  2006/06/01 15:39:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.1  2004/01/07 18:01:18  southa
 * MushModel and Infernal work
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
