/*
 * $Id$
 * $Log$
 */

#include "CoreScalar.hp"

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
        