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
 * $Id: MushcoreXMLOStream.h,v 1.14 2003/10/03 23:39:34 southa Exp $
 * $Log: MushcoreXMLOStream.h,v $
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

class MushcoreXMLOStream : public MushcoreXMLStream
{
public:
    explicit MushcoreXMLOStream(std::ostream& inPStream);
    virtual ~MushcoreXMLOStream() {}
    std::ostream& OStreamGet() { return m_pStream; }
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
    std::string localTag = ioOut.OpeningTagWrite(inObj.AutoNameGet());
    ioOut.OStreamGet() << std::endl;
    inObj.AutoXMLPrint(ioOut);
    ioOut.ClosingTagWrite(localTag);
    return ioOut;
}

inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const char *inChar)
{
    ioOut.OStreamGet() << inChar;
    return ioOut;
}

inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const Mushware::U32& inU32)
{
    std::string localTag = ioOut.OpeningTagWrite();
    ioOut.OStreamGet() << inU32;
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

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
