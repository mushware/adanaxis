//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDef.cpp
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
//%Header } 1oohjJmGlNzRvy+gVTjxog
/*
 * $Id: MustlConfigDef.cpp,v 1.10 2006/06/01 15:39:50 southa Exp $
 * $Log: MustlConfigDef.cpp,v $
 * Revision 1.10  2006/06/01 15:39:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:21  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.4  2003/01/17 12:20:40  southa
 * Fixed auto_ptr duplication
 *
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/14 20:46:11  southa
 * Post data handling
 *
 * Revision 1.1  2003/01/14 12:40:10  southa
 * Moved ConfigDefs into Mustl
 *
 */

#include "MustlConfigDef.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

// Include the subclasses for installation purposes
#include "MustlConfigDefBool.h"
#include "MustlConfigDefMenuString.h"
#include "MustlConfigDefPassword.h"
#include "MustlConfigDefString.h"
#include "MustlConfigDefU32.h"
#include "MustlConfigDefVal.h"

using namespace Mustl;
using namespace std;

// Instantiate the MustlConfigDef database
MUSHCORE_DATA_INSTANCE(MustlConfigDef);

MustlConfigDef::~MustlConfigDef()
{
}

void
MustlConfigDef::SelectPrologue(ostream& ioOut, const string& inName)
{
    ioOut << "<select name=\"" << MustlUtils::MakeWebSafe(inName) << "\">" << endl;
}

void
MustlConfigDef::SelectOption(ostream& ioOut, const string& inName, const string& inValue, bool inSelected)
{
    ioOut << "<option ";
    if (inSelected) ioOut << "selected ";
    ioOut << "value=\"" << MustlUtils::MakeWebSafe(inValue) << "\">";
    ioOut << MustlUtils::MakeWebSafe(inName);
    ioOut << "</option>" << endl;
}

void
MustlConfigDef::SelectOption(ostream& ioOut, const string& inName, U32 inValue, bool inSelected)
{
    ostringstream value;
    value << inValue;
    SelectOption(ioOut, inName, value.str(), inSelected);
}

void
MustlConfigDef::SelectEpilogue(ostream& ioOut)
{
    ioOut << "</select>" << endl;
}

void
MustlConfigDef::NullFunction(void)
{
    MustlConfigDefBool::NullFunction();
    MustlConfigDefMenuString::NullFunction();
    MustlConfigDefPassword::NullFunction();
    MustlConfigDefString::NullFunction();
    MustlConfigDefU32::NullFunction();
    MustlConfigDefVal::NullFunction();
}
