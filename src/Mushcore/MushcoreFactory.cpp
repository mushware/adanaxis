//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFactory.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } G/PInNICRCoN5D47RGPOmw
/*
 * $Id$
 * $Log$
 */

#include "MushcoreFactory.h"

#include "MushcoreFail.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushcoreFactory);

void
MushcoreFactory::FactoryAdd(const std::string& inName, tFactoryPtr inPtr)
{
    m_factories[inName] = inPtr;
}

MushcoreVirtualObject *
MushcoreFactory::ObjectCreate(const std::string& inName) const
{
    tFactoryMap::const_iterator p = m_factories.find(inName);

    if (p == m_factories.end())
    {
        throw MushcoreReferenceFail("Unknown object type '"+inName+"' - cannot create");
    }
    return p->second();
}
//%outOfLineFunctions {
void
MushcoreFactory::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "factories=" << m_factories;
    ioOut << "]";
}
//%outOfLineFunctions } 2QjCkKfEfqjgNBvYXpWbBg
