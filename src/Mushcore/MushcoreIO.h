/*
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"

// Special cases to avoid printing U8s as chars
inline std::ostream&
operator<<(std::ostream& ioOut, const std::vector<Mushware::U8>& inObj)
{
    std::vector<Mushware::U8>::const_iterator pEnd = inObj.end();
    std::vector<Mushware::U8>::const_iterator p = inObj.begin();

    ioOut << "[";
    while (p != pEnd)
    {
        ioOut << static_cast<Mushware::U32>(*p);
        ++p;
        if (p != pEnd)
        {
            ioOut << ", ";
        }
    }
    ioOut << "]";
    return ioOut;
}

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::vector<T>& inObj)
{
    std::vector<T>::const_iterator pEnd = inObj.end();
    std::vector<T>::const_iterator p = inObj.begin();

    ioOut << "[";
    while (p != pEnd)
    {
        ioOut << *p;
        ++p;
        if (p != pEnd)
        {
            ioOut << ", ";
        }
    }
    ioOut << "]";
    return ioOut;
}
