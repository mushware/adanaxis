//%includeGuardStart {
#ifndef INFERNALSTANDARD_H
#define INFERNALSTANDARD_H
//%includeGuardStart } ulOAN1Ly/JYyzPqGP7P/bg
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalStandard.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nh/Ox41GRW79N1VNMOuYsg
/*
 * $Id: InfernalStandard.h,v 1.1 2004/01/07 18:01:18 southa Exp $
 * $Log: InfernalStandard.h,v $
 * Revision 1.1  2004/01/07 18:01:18  southa
 * MushModel and Infernal work
 *
 */

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
