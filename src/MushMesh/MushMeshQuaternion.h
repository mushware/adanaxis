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
 * $Id: MushMeshQuaternion.h,v 1.1 2004/01/04 17:02:30 southa Exp $
 * $Log: MushMeshQuaternion.h,v $
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshVector.h"

template<class T>
class MushMeshQuaternion : public MushMeshVector<T, 4>
{
public:
    MushMeshQuaternion() {}
    MushMeshQuaternion(const T& in0, const T& in1, const T& in2, const T& in3)
    {
        m_value[0] = in0;
        m_value[1] = in1;
        m_value[2] = in2;
        m_value[3] = in3;
    }
};

namespace Mushware
{
    typedef MushMeshQuaternion<Mushware::tVal> tQVal;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
