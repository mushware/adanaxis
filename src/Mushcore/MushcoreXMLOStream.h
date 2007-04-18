//%includeGuardStart {
#ifndef MUSHCOREXMLOSTREAM_H
#define MUSHCOREXMLOSTREAM_H
//%includeGuardStart } bPT5GEbKVMd5EIUcx4WzZA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLOStream.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } hl5DZk50F3T2awuLEdyFgQ
/*
 * $Id: MushcoreXMLOStream.h,v 1.27 2006/06/01 15:39:49 southa Exp $
 * $Log: MushcoreXMLOStream.h,v $
 * Revision 1.27  2006/06/01 15:39:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.26  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.25  2005/07/01 14:59:00  southa
 * Mushcore auto_ptr and binary string fixes
 *
 * Revision 1.24  2005/06/30 14:26:36  southa
 * Adanaxis work
 *
 * Revision 1.23  2005/06/20 14:30:38  southa
 * Adanaxis work
 *
 * Revision 1.22  2005/06/16 10:49:00  southa
 * Client/server work
 *
 * Revision 1.21  2005/06/14 13:25:35  southa
 * Adanaxis work
 *
 * Revision 1.20  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.19  2005/03/25 19:13:50  southa
 * GameDialogue work
 *
 * Revision 1.18  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.17  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
 * Revision 1.16  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.15  2003/10/11 10:39:19  southa
 * gcc3.3 fixes
 *
 * Revision 1.14  2003/10/03 23:39:34  southa
 * XML polymorphs
 *
 * Revision 1.13  2003/10/02 23:33:39  southa
 * XML polymorphic objects
 *
 * Revision 1.12  2003/10/01 23:18:27  southa
 * XML object handling
 *
 * Revision 1.11  2003/09/30 22:11:30  southa
 * XML objects within objects
 *
 * Revision 1.10  2003/09/29 21:48:37  southa
 * XML work
 *
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
#include "MushcoreVirtualObject.h"

//#include <iomanip>

class MushcoreXMLOStream : public MushcoreXMLStream
{
public:
    explicit MushcoreXMLOStream(std::ostream& inPStream);
    virtual ~MushcoreXMLOStream() {}
    std::ostream& OStreamGet() { return m_pStream; }
    std::ostream& OStream() { return OStreamGet(); }
    std::string OpeningTagWrite(const std::string& inType="");
    void ClosingTagWrite(const std::string& inStr);
    const std::string& TagGet(void) { return m_tagStr; }
    void TagSet(const std::string& inStr) { m_tagStr = inStr; }
    
private:
    std::ostream& m_pStream;
    std::string m_tagStr;
};

inline std::string
MushcoreXMLOStream::OpeningTagWrite(const std::string& inType)
{
    std::string localTag = m_tagStr;
    if (localTag != "")
    {
        OStreamGet() << '<' << localTag;
        if (inType != "")
        {
            OStreamGet() << " type=\"" << inType << "\"";
        }	
        OStreamGet() << '>';
    }
    m_tagStr = "";
    return localTag;
}

inline void
MushcoreXMLOStream::ClosingTagWrite(const std::string& inStr)
{
    if (inStr != "")
    {
        OStreamGet() << "</" << inStr << ">" << std::endl;
    }
}

inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushcoreVirtualObject& inObj)
{
    if (ioOut.TagGet() == "") ioOut.TagSet("obj");
    std::string localTag = ioOut.OpeningTagWrite(inObj.AutoName());
    ioOut.OStreamGet() << std::endl;
    inObj.AutoOutputPrologue(ioOut);
    inObj.AutoXMLPrint(ioOut);
    ioOut.ClosingTagWrite(localTag);
    inObj.AutoOutputEpilogue(ioOut);
    return ioOut;
}

inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const char *inChar)
{
    ioOut.OStreamGet() << inChar;
    return ioOut;
}

// Numeric operator uses largest numerical type
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const double& inObj)
{
    std::string localTag = ioOut.OpeningTagWrite();

    std::ostream& ostreamRef = ioOut.OStreamGet();
    std::streamsize oldPrecision = ostreamRef.precision(20);
    ostreamRef << inObj;
    ostreamRef.precision(oldPrecision);
        
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::string& inStr)
{
    std::string localTag = ioOut.OpeningTagWrite();
    ioOut.OStreamGet() << '"' << MushcoreUtil::XMLMetaInsert(inStr) << '"';
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, T *inpObj)
{
    if (inpObj == NULL)
    {
        std::string localTag = ioOut.OpeningTagWrite();
        ioOut.OStreamGet() << "NULL";
        ioOut.ClosingTagWrite(localTag);
    }
    else
    {
        ioOut << *inpObj;
    }
    return ioOut;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::auto_ptr<T>& inaObj)
{
    if (inaObj.get() == NULL)
    {
        std::string localTag = ioOut.OpeningTagWrite();
        ioOut.OStreamGet() << "NULL";
        ioOut.ClosingTagWrite(localTag);
    }
    else
    {
        ioOut << *inaObj.get();
    }
    return ioOut;
}


template<>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, MushcoreVirtualObject *inpObj)
{
    if (inpObj == NULL)
    {
        std::string localTag = ioOut.OpeningTagWrite();
        ioOut.OStreamGet() << "NULL";
        ioOut.ClosingTagWrite(localTag);
    }
    else
    {
        if (ioOut.TagGet() == "")
        {
            ioOut.TagSet("obj");
        }
        ioOut << *inpObj;
    }
    return ioOut;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::vector<T>& inObj)
{
    typename std::vector<T>::const_iterator pEnd = inObj.end();
    typename std::vector<T>::const_iterator p = inObj.begin();

    std::string localTag = ioOut.OpeningTagWrite();
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
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::vector<T *>& inObj)
{
    typename std::vector<T *>::const_iterator pEnd = inObj.end();
    typename std::vector<T *>::const_iterator p = inObj.begin();

    std::string localTag = ioOut.OpeningTagWrite();
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
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

// List functions are a direct copy of vector functions
template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::list<T>& inObj)
{
    typename std::list<T>::const_iterator pEnd = inObj.end();
    typename std::list<T>::const_iterator p = inObj.begin();
    
    std::string localTag = ioOut.OpeningTagWrite();
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
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::list<T *>& inObj)
{
    typename std::list<T *>::const_iterator pEnd = inObj.end();
    typename std::list<T *>::const_iterator p = inObj.begin();
    
    std::string localTag = ioOut.OpeningTagWrite();
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
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

// Deque functions are a direct copy of vector functions
template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::deque<T>& inObj)
{
    typename std::deque<T>::const_iterator pEnd = inObj.end();
    typename std::deque<T>::const_iterator p = inObj.begin();
    
    std::string localTag = ioOut.OpeningTagWrite();
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
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::deque<T *>& inObj)
{
    typename std::deque<T *>::const_iterator pEnd = inObj.end();
    typename std::deque<T *>::const_iterator p = inObj.begin();
    
    std::string localTag = ioOut.OpeningTagWrite();
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
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

template<class T, class U>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::map<T, U>& inObj)
{
    typename std::map<T, U>::const_iterator pEnd = inObj.end();
    typename std::map<T, U>::const_iterator p = inObj.begin();

    std::string localTag = ioOut.OpeningTagWrite();
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
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

template<class T, class U>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::pair<T, U>& inObj)
{
    std::string localTag = ioOut.OpeningTagWrite();
    ioOut.OStreamGet() << "(";

    ioOut << inObj.first << "=" << inObj.second;
    
    ioOut.OStreamGet() << ")";
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
