//%includeGuardStart {
#ifndef MUSHCOREXMLOSTREAM_H
#define MUSHCOREXMLOSTREAM_H
//%includeGuardStart } bPT5GEbKVMd5EIUcx4WzZA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLOStream.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } f2F46K8LXdioFTimaPJHmQ
/*
 * $Id: MushcoreXMLOStream.h,v 1.9 2003/09/27 17:50:49 southa Exp $
 * $Log: MushcoreXMLOStream.h,v $
 * Revision 1.9  2003/09/27 17:50:49  southa
 * XML null pointer handling
 *
 * Revision 1.8  2003/09/25 20:02:25  southa
 * XML pointer work
 *
 * Revision 1.7  2003/09/24 19:03:23  southa
 * XML map IO
 *
 * Revision 1.6  2003/09/23 22:57:57  southa
 * XML vector handling
 *
 * Revision 1.5  2003/09/22 19:58:13  southa
 * Prebuild in makefiles
 *
 * Revision 1.4  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.3  2003/09/21 09:56:38  southa
 * Re-added
 *
 * Revision 1.1  2003/09/21 09:51:09  southa
 * Stream autogenerators
 *
 */

#include "MushcoreStandard.h"
#include "MushcoreXMLStream.h"
#include "MushcoreUtil.h"

class MushcoreXMLConsumer;

class MushcoreXMLOStream : public MushcoreXMLStream
{
public:
    explicit MushcoreXMLOStream(std::ostream& inPStream);
    std::ostream& OStreamGet() { return m_pStream; }

    template<class T> void PointerPrint(const T *inPtr);
    
private:
    std::ostream& m_pStream;
};

template<class T>
inline void
MushcoreXMLOStream::PointerPrint(const T *inPtr)
{
    if (inPtr == NULL)
    {
        OStreamGet() << "NULL";
    }
    else
    {
        *this << *inPtr;
    }
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const T& inObj)
{
    ioOut.OStreamGet() << inObj;
    return ioOut;
}

template<>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushcoreXMLConsumer& inObj)
{
    ioOut << inObj;
    return ioOut;
}

template<>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const Mushware::U8& inU8)
{
    ioOut << static_cast<Mushware::U32>(inU8);
    return ioOut;
}

template<>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::string& inStr)
{
    ioOut.OStreamGet() << '"' << MushcoreUtil::XMLMetaInsert(inStr) << '"';
    return ioOut;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::vector<T>& inObj)
{
    std::vector<T>::const_iterator pEnd = inObj.end();
    std::vector<T>::const_iterator p = inObj.begin();

    ioOut.OStreamGet() << "(";
    while (p != pEnd)
    {
        ioOut << *p;
        ++p;
        if (p != pEnd)
        {
            ioOut.OStreamGet() << ',';
        }
    }
    ioOut.OStreamGet() << ")";
    return ioOut;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::vector<T *>& inObj)
{
    std::vector<T *>::const_iterator pEnd = inObj.end();
    std::vector<T *>::const_iterator p = inObj.begin();

    ioOut.OStreamGet() << "(";
    while (p != pEnd)
    {
        ioOut.PointerPrint(*p);
        ++p;
        if (p != pEnd)
        {
            ioOut.OStreamGet() << ',';
        }
    }
    ioOut.OStreamGet() << ")";
    return ioOut;
}

template<class T, class U>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::map<T, U>& inObj)
{
    std::map<T, U>::const_iterator pEnd = inObj.end();
    std::map<T, U>::const_iterator p = inObj.begin();

    ioOut.OStreamGet() << "(";
    while (p != pEnd)
    {
        ioOut << p->first << "=" << p->second;
        ++p;
        if (p != pEnd)
        {
            ioOut.OStreamGet() << ',';
        }
    }
    ioOut.OStreamGet() << ")";
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
