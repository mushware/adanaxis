//%includeGuardStart {
#ifndef MUSHCOREVIRTUALOBJECT_H
#define MUSHCOREVIRTUALOBJECT_H
//%includeGuardStart } A9fCmryMnprUYlvNkdoI2g
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreVirtualObject.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } gEh/hbSKsNzMvyNOGorB3w
/*
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"

#include "MushcoreObject.h"

class MushcoreXMLIStream;
class MushcoreXMLOStream;

// General base class for objects with virtual functions

class MushcoreVirtualObject : public MushcoreObject
{
public:
    virtual const char *AutoNameGet(void) const = 0;
    virtual MushcoreVirtualObject *AutoClone(void) const = 0;
    virtual MushcoreVirtualObject *AutoCreate(void) const = 0;

    virtual void AutoPrint(std::ostream& ioOut) const = 0;
    virtual void AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr) = 0;
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const = 0;
};

inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreVirtualObject& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
