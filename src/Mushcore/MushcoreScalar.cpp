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
 * $Id: MushcoreScalar.cpp,v 1.14 2002/12/29 20:59:52 southa Exp $
 * $Log: MushcoreScalar.cpp,v $
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
#include "MushcoreException.h"

using namespace Mushware;
using namespace std;

void
MushcoreScalar::Get(tVal& outVal) const
{
    switch (m_tag)
    {
        case kNone:
            throw(ExpressionFail("Use of undefined value"));
            break;
            
        case kVal:
            outVal=m_val;
            break;

        case kString:
            outVal=atof(m_string.c_str());
            break;

        default:
            throw "MushcoreScalar value fault";
    }
}

void
MushcoreScalar::Get(string& outStr) const 
{
    switch (m_tag)
    {
        case kNone:
            throw(ExpressionFail("Use of undefined value"));
            break;

        case kVal:
        {
            ostringstream strm;
            strm << m_val;
            outStr=strm.str();
        }
        break;
            
        case kString:
            outStr=m_string;
            break;
            
        default:
            throw "MushcoreScalar value fault";
    }
}

void
MushcoreScalar::Get(bool& outBool) const
{
    switch (m_tag)
    {
        case kNone:
            throw(ExpressionFail("Use of undefined value"));
            break;

        case kVal:
        {
            outBool=!(!m_val);
        }
            break;

        case kString:
            if (m_string == "1" || m_string == "true" || m_string == "TRUE")
            {
                outBool = true;
            }
            else if (m_string == "0" || m_string == "false" || m_string == "FALSE")
            {
                outBool = false;
            }
            else
            {
                throw(ExpressionFail("Cannot get boolean value from '"+m_string+"'"));
            }
            break;

        default:
            throw "MushcoreScalar value fault";
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
MushcoreScalar::ostreamPrint(ostream& inOut) const
{
    switch (m_tag)
    {
        case kNone:
            inOut << "undefined";
            break;

        case kVal:
            inOut << m_val;
            break;

        case kString:
            inOut << m_string;
            break;

        default:
            throw "MushcoreScalar value fault";
    }
}
