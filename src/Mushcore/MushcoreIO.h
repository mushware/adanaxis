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
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } AqRkhzf74kOxwRFo7CMCSw
/*
 * $Id: MushcoreIO.h,v 1.6 2003/10/17 12:27:19 southa Exp $
 * $Log: MushcoreIO.h,v $
 * Revision 1.6  2003/10/17 12:27:19  southa
 * Line end fixes and more mesh work
 *
 * Revision 1.5  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.4  2003/10/11 10:39:19  southa
 * gcc3.3 fixes
 *
 * Revision 1.3  2003/09/21 09:51:08  southa
 * Stream autogenerators
 *
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
    typename std::vector<T>::const_iterator pEnd = inObj.end();
    typename std::vector<T>::const_iterator p = inObj.begin();

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

#ifndef MIMIC_VALARRAY
// valarray output
template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushwareValarray<T>& inObj)
{
    Mushware::U32 size = inObj.size();
    ioOut << "[";
    for (Mushware::U32 i=0; i < size; ++i)
    {
        ioOut << inObj[i];
        if (i + 1 < size)
        {
            ioOut << ", ";
        }
    }
    ioOut << "]";
    return ioOut;
}
#endif

// std::map output
template <class T, class U>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::map<T, U>& inObj)
{
    typename std::map<T, U>::const_iterator pEnd = inObj.end();
    typename std::map<T, U>::const_iterator p = inObj.begin();

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
