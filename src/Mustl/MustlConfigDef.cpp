//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDef.cpp
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
//%Header } NyTxYUUeQUA6TxeHdCngTw
/*
 * $Id: MustlConfigDef.cpp,v 1.8 2004/01/02 21:13:14 southa Exp $
 * $Log: MustlConfigDef.cpp,v $
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
