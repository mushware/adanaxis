/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/




/*
 * $Id: CoreScalar.cpp,v 1.10 2002/08/07 13:36:46 southa Exp $
 * $Log: CoreScalar.cpp,v $
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

#include "CoreScalar.h"
#include "CoreException.h"

void
CoreScalar::Get(tVal& outVal) const
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
            throw "CoreScalar value fault";
    }
}

void
CoreScalar::Get(string& outStr) const 
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
            throw "CoreScalar value fault";
    }
}

void
CoreScalar::Get(bool& outBool) const
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
            throw "CoreScalar value fault";
    }
}

bool
CoreScalar::SlowEquals(const CoreScalar& inScalar) const
{
    string str1;
    string str2;

    Get(str1);
    inScalar.Get(str2);
    return str1 == str2;
}

void
CoreScalar::ostreamPrint(ostream& inOut) const
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
            throw "CoreScalar value fault";
    }
}
