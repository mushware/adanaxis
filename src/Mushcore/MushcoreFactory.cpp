//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFactory.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 5yrDa+Xrdt7jgCyT3G1cRw
/*
 * $Id: MushcoreFactory.cpp,v 1.3 2004/01/04 17:02:30 southa Exp $
 * $Log: MushcoreFactory.cpp,v $
 * Revision 1.3  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.2  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 */

#include "MushcoreFactory.h"

#include "MushcoreCommand.h"
#include "MushcoreEnv.h"
#include "MushcoreFail.h"
#include "MushcoreIO.h"
#include "MushcoreSTL.h"
#include "MushcoreVirtualObject.h"

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

void
MushcoreFactory::TemplatesPrint(std::ostream& ioOut) const
{
    MushcoreXMLOStream xmlOStream(ioOut);
    for (tFactoryMap::const_iterator p = m_factories.begin();
         p != m_factories.end(); ++p)
    {
        xmlOStream << MushcoreFactory::Sgl().ObjectCreate(p->first);            
    }
}

void
MushcoreFactory::TypesPrint(std::ostream& ioOut) const
{
    for (tFactoryMap::const_iterator p = m_factories.begin();
         p != m_factories.end(); ++p)
    {
        ioOut << p->first << endl;            
    }
}

MushcoreScalar
MushcoreFactory::XMLTemplatePrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() == 0)
    {
        Sgl().TemplatesPrint(ioEnv.Out());
    }
    else
    {
        if (ioCommand.NumParams() != 1)
        {
            throw(MushcoreCommandFail("Usage: MushcoreXMLTemplatePrint(typename)"));
        }
        
        string typeStr;
        ioCommand.PopParam(typeStr);
        
        MushcoreXMLOStream xmlOStream(ioEnv.Out());
        xmlOStream << MushcoreFactory::Sgl().ObjectCreate(typeStr);
    }
    return MushcoreScalar(0);    
}  

MushcoreScalar
MushcoreFactory::XMLTypesPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv)
{
    if (ioCommand.NumParams() != 0)
    {
        throw(MushcoreCommandFail("Usage: MushcoreXMLTemplatePrint(typename)"));
    }
    Sgl().TypesPrint(ioEnv.Out());
    return MushcoreScalar(0);    
}

void
MushcoreFactory::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("MushcoreXMLTemplatePrint", XMLTemplatePrint);
    MushcoreInterpreter::Sgl().HandlerAdd("MushcoreXMLTypesPrint", XMLTypesPrint);
}

namespace { MushcoreInstaller Installer(MushcoreFactory::Install); }

//%outOfLineFunctions {
void
MushcoreFactory::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "factories=" << m_factories;
    ioOut << "]";
}
//%outOfLineFunctions } 2QjCkKfEfqjgNBvYXpWbBg
