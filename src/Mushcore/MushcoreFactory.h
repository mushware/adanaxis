//%includeGuardStart {
#ifndef MUSHCOREFACTORY_H
#define MUSHCOREFACTORY_H
//%includeGuardStart } Z+MZF0GNXp9ZSAZTknuPjg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFactory.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } PCqvrnn/p0THwedPuNPI9g
/*
 * $Id: MushcoreFactory.h,v 1.1 2003/10/02 23:33:38 southa Exp $
 * $Log: MushcoreFactory.h,v $
 * Revision 1.1  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 */

#include "MushcoreStandard.h"
#include "MushcoreSingleton.h"
#include "MushcoreVirtualObject.h"
#include "MushcoreIO.h"

//:generate ostream
class MushcoreFactory : public MushcoreSingleton<MushcoreFactory>
{
public:
    typedef MushcoreVirtualObject *(* tFactoryPtr)(void) ;
    typedef std::map<std::string, tFactoryPtr> tFactoryMap;
    
    void FactoryAdd(const std::string& inName, tFactoryPtr inPtr);
    MushcoreVirtualObject *ObjectCreate(const std::string& inName) const;
    
private:
    tFactoryMap m_factories;
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreFactory& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LqoVPNELHsXwHf/xHX8fpA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
