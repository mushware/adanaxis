/*
 * $Id: CoreScalar.cpp,v 1.3 2002/05/09 17:10:38 southa Exp $
 * $Log: CoreScalar.cpp,v $
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
CoreScalar::Get(Val& outVal)
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
CoreScalar::Get(string& outStr)
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
        