//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFactory.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } fRAO6DWnsWUaSgkVerqMzQ
/*
 * $Id: MushcoreFactory.cpp,v 1.8 2006/06/01 15:39:43 southa Exp $
 * $Log: MushcoreFactory.cpp,v $
 * Revision 1.8  2006/06/01 15:39:43  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/06/21 13:10:52  southa
 * MushGame work
 *
 * Revision 1.6  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.4  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
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
#include "MushcoreInterpreter.h"
#include "MushcoreInstaller.h"
#include "MushcoreSTL.h"
#include "MushcoreVirtualObject.h"
#include "MushcoreXMLOStream.h"

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

bool
MushcoreFactory::Exists(const std::string& inName) const
{
    tFactoryMap::const_iterator p = m_factories.find(inName);
    
    if (p == m_factories.end())
    {
        return false;
    }
    else
    {
        return true;
    }
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
