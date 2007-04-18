//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAppHandler.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } viB+23+9q1b7disbAvOTtQ
/*
 * $Id: MushcoreAppHandler.cpp,v 1.11 2006/07/31 11:01:39 southa Exp $
 * $Log: MushcoreAppHandler.cpp,v $
 * Revision 1.11  2006/07/31 11:01:39  southa
 * Music and dialogues
 *
 * Revision 1.10  2006/06/01 15:39:41  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:04  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/20 15:38:27  southa
 * Created MushcoreTest
 *
 * Revision 1.4  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.3  2003/01/11 17:44:27  southa
 * Mushcore fixes
 *
 * Revision 1.2  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.12  2002/12/29 20:59:50  southa
 * More build fixes
 *
 * Revision 1.11  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/11/18 11:31:13  southa
 * Return to game mode
 *
 * Revision 1.9  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/24 16:41:14  southa
 * Fixed for mingw32
 *
 * Revision 1.3  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 * Revision 1.2  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "MushcoreAppHandler.h"

#include "MushcoreAppSignal.h"
#include "MushcoreFactory.h"
#include "MushcoreInstaller.h"
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreAppHandler *MushcoreAppHandler::m_instance = NULL;

void
MushcoreAppHandler::Mutate(MushcoreAppHandler *inAppHandler)
{
    delete(m_instance);
    m_instance=inAppHandler;
}

void
MushcoreAppHandler::Initialise(void)
{
}

void
MushcoreAppHandler::MainLoop(void)
{
    Idle();
}

void
MushcoreAppHandler::Idle(void)
{
}

void
MushcoreAppHandler::Signal(const MushcoreAppSignal& inSignal)
{
    switch (inSignal.SigNumberGet())
    {
        case MushcoreAppSignal::kQuit:
            exit(0);
            break;

        case MushcoreAppSignal::kEscape:
            Signal(MushcoreAppSignal(MushcoreAppSignal::kQuit));
            break;
            
        default:
#ifdef MUSHCORE_DEBUG
            cerr << "Unhandled MushcoreApp signal 0x" << hex << inSignal.SigNumberGet() << dec << endl;
#endif
            break;
    }
}
//%outOfLineFunctions {

const char *MushcoreAppHandler::AutoName(void) const
{
    return "MushcoreAppHandler";
}

MushcoreVirtualObject *MushcoreAppHandler::AutoClone(void) const
{
    return new MushcoreAppHandler(*this);
}

MushcoreVirtualObject *MushcoreAppHandler::AutoCreate(void) const
{
    return new MushcoreAppHandler;
}

MushcoreVirtualObject *MushcoreAppHandler::AutoVirtualFactory(void)
{
    return new MushcoreAppHandler;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushcoreAppHandler", MushcoreAppHandler::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushcoreAppHandler::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushcoreAppHandler::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushcoreAppHandler::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } OGZ4jEiU/SCETT1y6JT1bg
