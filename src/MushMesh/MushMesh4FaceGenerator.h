//%includeGuardStart {
#ifndef MUSHMESH4FACEGENERATOR_H
#define MUSHMESH4FACEGENERATOR_H
//%includeGuardStart } 2RTTtTj6B5mu2E8ooCbfhA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4FaceGenerator.h
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
//%Header } p2KIeWd+9kk4NUfaSN9FvA
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

//:generate virtual standard ostream xml1
class MushMesh4FaceGenerator : public MushcoreVirtualObject
{
public:
    
private:
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4FaceGenerator& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Mjb9aCFGtTazjxF65hAq/w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
