//%includeGuardStart {
#ifndef MUSHMESHQUATERNION_H
#define MUSHMESHQUATERNION_H
//%includeGuardStart } MfXOjt39LkittUvhd8Gq+A
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshQuaternion.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } rIcABVZ9p6NF41BMv39r2Q
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMeshVector.h"

template<class T>
class MushMeshQuaternion : public MushMeshVector<T, 4>
{
    
};

namespace Mushware
{
    typedef MushMeshQuaternion<Mushware::tVal> tQVal;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
