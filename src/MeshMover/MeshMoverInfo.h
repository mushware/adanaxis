//%includeGuardStart {
#ifndef MESHMOVERINFO_H
#define MESHMOVERINFO_H
//%includeGuardStart } sYQqECwUfvhbPyNMAFHF2g
//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverInfo.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } GG4SneuiHuSXnptr98+C4Q
/*
 * $Id$
 * $Log$
 */

#include "Mushcore.h"

class MeshMoverInfo : public MushcoreInfo
{
public:
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);

    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
