//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLAppHandler.cpp
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
//%Header } xL9VlEtTnUt/VTSN/FnklQ
/*
 * $Id: GLAppHandler.cpp,v 1.27 2006/07/31 11:01:37 southa Exp $
 * $Log: GLAppHandler.cpp,v $
 * Revision 1.27  2006/07/31 11:01:37  southa
 * Music and dialogues
 *
 * Revision 1.26  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.25  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.24  2004/01/02 21:13:04  southa
 * Source conditioning
 *
 * Revision 1.23  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.22  2003/08/21 23:08:17  southa
 * Fixed file headers
 *
 * Revision 1.21  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.20  2003/01/09 14:56:57  southa
 * Created Mushcore
 *
 * Revision 1.19  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.18  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.17  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.16  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.15  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.14  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.13  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.12  2002/06/20 15:50:29  southa
 * Subclassed GLAppHandler
 *
 * Revision 1.11  2002/06/06 15:00:44  southa
 * Mouse fixes
 *
 * Revision 1.10  2002/06/06 13:36:13  southa
 * Mouse handling
 *
 * Revision 1.9  2002/06/05 16:29:51  southa
 * Mouse control
 *
 * Revision 1.8  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 * Revision 1.7  2002/05/24 18:10:43  southa
 * MushcoreXML and game map
 *
 * Revision 1.6  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.5  2002/05/10 16:41:42  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/05/08 16:31:20  southa
 * Created API directory
 *
 * Revision 1.3  2002/03/21 22:07:54  southa
 * Initial wrangle application handler
 *
 * Revision 1.2  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "GLAppHandler.h"
#include "GLStandard.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

//%outOfLineFunctions {

const char *GLAppHandler::AutoName(void) const
{
    return "GLAppHandler";
}

MushcoreVirtualObject *GLAppHandler::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'GLAppHandler'");;
}

MushcoreVirtualObject *GLAppHandler::AutoCreate(void) const
{
    throw MushcoreRequestFail("Cannot create abstract 'GLAppHandler'");
}

MushcoreVirtualObject *GLAppHandler::AutoVirtualFactory(void)
{
    throw MushcoreRequestFail("Cannot create abstract 'GLAppHandler'");
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GLAppHandler", GLAppHandler::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GLAppHandler::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushcoreAppHandler::AutoPrint(ioOut);
    ioOut << "]";
}
bool
GLAppHandler::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushcoreAppHandler::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
GLAppHandler::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushcoreAppHandler::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } FHe6FKetTHEk2d7NfkOtCg
