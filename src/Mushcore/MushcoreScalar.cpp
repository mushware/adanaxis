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
 * $Id: MushcoreScalar.cpp,v 1.4 2003/01/20 12:23:23 southa Exp $
 * $Log: MushcoreScalar.cpp,v $
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.14  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.13  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.11  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.9  2002/07/31 16:27:15  southa
 * Collision checking work
 *
 * Revision 1.8  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.7  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.6  2002/05/28 13:05:56  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.5  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.4  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.2  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.1  2002/03/04 22:30:49  southa
 * Interpreter work
 *
 */

#include "MushcoreScalar.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

void
MushcoreScalar::ValAsStringGet(string& outStr) const
{
    ostringstream valStream;
    valStream << m_longVal;
    outStr = valStream.str();
}

void
MushcoreScalar::StringAsValGet(tLongVal& outVal) const
{
    istringstream strStream(m_stringVal);
    if (!(strStream >> outVal))
    {
        throw(MushcoreDataFail("Cannot get numeric value from '"+m_stringVal+"'"));
    }
}

void
MushcoreScalar::StringAsBoolGet(bool& outBool) const
{
    istringstream strStream(m_stringVal);
    if (!(strStream >> outBool))
    {
        throw(MushcoreDataFail("Cannot get boolean value from '"+m_stringVal+"'"));
    }    
}

bool
MushcoreScalar::SlowEquals(const MushcoreScalar& inScalar) const
{
    string str1;
    string str2;

    Get(str1);
    inScalar.Get(str2);
    return str1 == str2;
}

void
MushcoreScalar::Print(ostream& ioOut) const
{
    switch (m_typeTag)
    {
        case kTypeTagNone:
            ioOut << "undefined";
            break;

        case kTypeTagLongVal:
            ioOut << m_longVal;
            break;

        case kTypeTagString:
            ioOut << m_stringVal;
            break;

        default:
            throw MushcoreLogicFail("MushcoreScalar value fault");
    }
}

