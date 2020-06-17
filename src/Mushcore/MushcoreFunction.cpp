//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFunction.cpp
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
//%Header } vZAlK2BXuAdhamoijoDoLQ
/*
 * $Id: MushcoreFunction.cpp,v 1.11 2006/06/01 15:39:44 southa Exp $
 * $Log: MushcoreFunction.cpp,v $
 * Revision 1.11  2006/06/01 15:39:44  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:12  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.5  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.4  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.10  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.9  2002/09/07 09:54:01  southa
 * Tweaks to Mandrake RPM
 *
 * Revision 1.8  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.1  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 */

#include "MushcoreFunction.h"

#include "MushcoreFail.h"
#include "MushcoreInterpreter.h"
#include "MushcoreScalar.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

void
MushcoreFunction::ThrowErrorExecute(void) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        MushcoreInterpreter::Sgl().Execute(m_commands[i]);
    }
}

void
MushcoreFunction::CoalesceErrorsExecute(void) const
{
    string failStr;
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        try
        {
            MushcoreInterpreter::Sgl().Execute(m_commands[i]);
        }
        catch (MushcoreNonFatalFail& e)
        {
            failStr += ": ";
            failStr += e.what();
        }
    }
    if (failStr != "")
    {
        throw(MushcoreCommandFail("Command(s) failed"+failStr));
    }
}

void
MushcoreFunction::Print(ostream& inOut) const
{
    for (U32 i=0; i<m_commands.size(); ++i)
    {
        inOut << m_commands[i] << endl;
    }
}
