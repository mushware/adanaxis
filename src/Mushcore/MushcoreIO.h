//%includeGuardStart {
#ifndef MUSHCOREIO_H
#define MUSHCOREIO_H
//%includeGuardStart } QhMmTg7Nf9Xugp/Ykvainw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreIO.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Xy+fzSH8daL6jemhQN4e2A
/*
 * $Id: MushcoreIO.h,v 1.2 2003/09/17 19:40:35 southa Exp $
 * $Log: MushcoreIO.h,v $
 * Revision 1.2  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.1  2003/09/17 19:10:44  southa
 * Created
 *
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

// std::vector output
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

// std::map output
template <class T, class U>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::map<T, U>& inObj)
{
    std::map<T, U>::const_iterator pEnd = inObj.end();
    std::map<T, U>::const_iterator p = inObj.begin();

    ioOut << "[";
    while (p != pEnd)
    {
        ioOut << p->first << " => " << p->second;
        ++p;
        if (p != pEnd)
        {
            ioOut << ", ";
        }
    }
    ioOut << "]";
    return ioOut;
}



//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
