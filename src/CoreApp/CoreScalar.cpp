/*
 * $Id: CoreScalar.cpp,v 1.4 2002/05/10 16:39:37 southa Exp $
 * $Log: CoreScalar.cpp,v $
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
#include <strstream>
void
CoreScalar::Get(tVal& outVal) const
{
    switch (m_tag)
    {
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
        case kVal:
        {
            char buf[256];
            buf[sizeof(buf)-1]='\0';
            ostrstream out(buf, sizeof(buf)-1);
            out << m_val;
            outStr=buf;
        }
        break;
            
        case kString:
            outStr=m_string;
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
        