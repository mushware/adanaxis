/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id$
 * $Log$
 */

#include "MustlConfigDef.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlMushcore.h"

using namespace Mustl;
using namespace std;

auto_ptr< MushcoreData<MustlConfigDef> > MushcoreData<MustlConfigDef>::m_instance;

MustlConfigDef::~MustlConfigDef()
{
}


// -----

// -----

// -----


// -----

// -----


// -----

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
