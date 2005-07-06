//%includeGuardStart {
#ifndef MUSHCOREIO_H
#define MUSHCOREIO_H
//%includeGuardStart } QhMmTg7Nf9Xugp/Ykvainw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreIO.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } NNj6hj9phwRQNaj45QYBKA
/*
 * $Id: MushcoreIO.h,v 1.13 2005/07/01 14:59:00 southa Exp $
 * $Log: MushcoreIO.h,v $
 * Revision 1.13  2005/07/01 14:59:00  southa
 * Mushcore auto_ptr and binary string fixes
 *
 * Revision 1.12  2005/06/30 14:26:36  southa
 * Adanaxis work
 *
 * Revision 1.11  2005/06/16 10:49:00  southa
 * Client/server work
 *
 * Revision 1.10  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.9  2004/09/26 19:42:05  southa
 * Added MushMesh, fixed typenames and release target
 *
 * Revision 1.8  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.7  2004/01/02 21:13:12  southa
 * Source conditioning
 *
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

// std::auto_ptr output
template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::auto_ptr<T>& inObj)
{
    if (inObj.get() ==  NULL)
    {
        ioOut << "NULL";   
    }
    else
    {
        ioOut << *inObj.get();
    }
    return ioOut;
}

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

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::vector<T *>& inObj)
{
    typename std::vector<T *>::const_iterator pEnd = inObj.end();
    typename std::vector<T *>::const_iterator p = inObj.begin();
    
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

// std::list output (copy of vector)
template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::list<T>& inObj)
{
    typename std::list<T>::const_iterator pEnd = inObj.end();
    typename std::list<T>::const_iterator p = inObj.begin();
    
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

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::list<T *>& inObj)
{
    typename std::list<T *>::const_iterator pEnd = inObj.end();
    typename std::list<T *>::const_iterator p = inObj.begin();
    
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


// std::deque output (copy of vector)
template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::deque<T>& inObj)
{
    typename std::deque<T>::const_iterator pEnd = inObj.end();
    typename std::deque<T>::const_iterator p = inObj.begin();
    
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

template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::deque<T *>& inObj)
{
    typename std::deque<T *>::const_iterator pEnd = inObj.end();
    typename std::deque<T *>::const_iterator p = inObj.begin();
    
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

#ifndef MUSHCORE_MIMIC_VALARRAY
// valarray output
template <class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushwareValarray<T *>& inObj)
{
    Mushware::U32 size = inObj.size();
    ioOut << "[";
    for (Mushware::U32 i=0; i < size; ++i)
    {
        if (inObj[i] == NULL)
        {
            ioOut << "NULL";
        }
        else
        {
            ioOut << *inObj[i];
        }
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

template <class T, class U>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::map<T, U *>& inObj)
{
    typename std::map<T, U *>::const_iterator pEnd = inObj.end();
    typename std::map<T, U *>::const_iterator p = inObj.begin();
    
    ioOut << "[";
    while (p != pEnd)
    {
        if (p->second == NULL)
        {
            ioOut << p->first << " => NULL";
        }
        else
        {
            ioOut << p->first << " => " << *p->second;
        }
            
        ++p;
        if (p != pEnd)
        {
            ioOut << ", ";
        }
    }
    ioOut << "]";
    return ioOut;
}

// std::pair output
template <class T, class U>
inline std::ostream&
operator<<(std::ostream& ioOut, const std::pair<T, U>& inObj)
{
    ioOut << "[";
    ioOut << inObj.first << " => " << inObj.second;
    ioOut << "]";
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
