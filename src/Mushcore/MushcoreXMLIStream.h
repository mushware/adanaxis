//%includeGuardStart {
#ifndef MUSHCOREXMLISTREAM_H
#define MUSHCOREXMLISTREAM_H
//%includeGuardStart } 4GDI2rjRWblNFqvrMDV7ag
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLIStream.h
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
//%Header } QZNov6vf1irc8tAhC1nh9g
/*
 * $Id: MushcoreXMLIStream.h,v 1.29 2005/06/30 14:26:36 southa Exp $
 * $Log: MushcoreXMLIStream.h,v $
 * Revision 1.29  2005/06/30 14:26:36  southa
 * Adanaxis work
 *
 * Revision 1.28  2005/06/24 10:30:14  southa
 * MushGame camera work
 *
 * Revision 1.27  2005/06/16 10:49:00  southa
 * Client/server work
 *
 * Revision 1.26  2005/06/14 13:25:35  southa
 * Adanaxis work
 *
 * Revision 1.25  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.24  2005/03/25 22:04:50  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.23  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 * Revision 1.22  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.21  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.20  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.19  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.18  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.17  2004/01/02 17:31:48  southa
 * MushPie work and XML fixes
 *
 * Revision 1.16  2003/10/15 12:26:59  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.15  2003/10/14 10:46:05  southa
 * MeshMover creation
 *
 * Revision 1.14  2003/10/11 10:39:19  southa
 * gcc3.3 fixes
 *
 * Revision 1.13  2003/10/03 23:39:34  southa
 * XML polymorphs
 *
 * Revision 1.12  2003/10/02 23:33:39  southa
 * XML polymorphic objects
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
 * Revision 1.5  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.4  2003/09/21 23:15:08  southa
 * XML input stream improvements
 *
 * Revision 1.3  2003/09/21 18:49:41  southa
 * XML input stream work
 *
 * Revision 1.2  2003/09/21 15:57:12  southa
 * XML autogenerator work
 *
 * Revision 1.1  2003/09/21 11:46:10  southa
 * XML input stream
 *
 */

#include "MushcoreStandard.h"
#include "MushcoreXMLStream.h"
#include "MushcoreUtil.h"

class MushcoreVirtualObject;

class MushcoreXMLIStream : public MushcoreXMLStream
{
public:
    explicit MushcoreXMLIStream(std::istream& inPStream);
    virtual ~MushcoreXMLIStream();

    std::string DataUntilTake(const std::string& inStr);
    const std::string& TagNameGet(void) const { return m_tagName; }
    Mushware::U8 ByteGet(void);
    Mushware::U8 ByteTake(void);
    
    template<class T> void ObjectRead(T *& outpObj);   
    template<class T> void ObjectRead(std::vector<T>& inVector);
    template<class T> void ObjectRead(std::vector<T *>& inVector);
    template<class T> void ObjectRead(std::list<T>& inVector);
    template<class T> void ObjectRead(std::list<T *>& inVector);
    template<class T> void ObjectRead(std::deque<T>& inVector);
    template<class T> void ObjectRead(std::deque<T *>& inVector);
    template<class T, class U> void ObjectRead(std::map<T, U>& inMap);
    template<class T, class U> void ObjectRead(std::map<T, U *>& inMap);

    void ObjectReadVirtual(MushcoreVirtualObject *& outpObj);
    void ObjectReadVirtual(MushcoreVirtualObject& outObj);

    void ObjectRead(Mushware::U64& outU64);
    void ObjectRead(Mushware::U32& outU32);
    void ObjectRead(Mushware::U8& outU8);
    void ObjectRead(Mushware::tVal& outObj);
    void ObjectRead(Mushware::tXMLVal& outObj);
    void ObjectRead(std::string& outStr);

    bool CompositePrologue(void);
    void CompositeEpilogue(bool inHasTag);
    
    void Throw(const std::string& inMessage) const;
    
protected:

    Mushware::U32 TagGet(std::string& outTag, const std::string& inStr, Mushware::U32 inPos = 0);
    const std::string& TagDataGet(void) const { return m_tagData; }
    
    void InputFetch(void);

private:
    bool VirtualIs(MushcoreVirtualObject *inpObj) { return true; }
    bool VirtualIs(void *inpObj) { return false; }
    MushcoreVirtualObject *AllocateVirtual(void);
        
    std::istream& m_inStream;
    std::string m_tagName;
    std::string m_contentStr;
    std::string m_indentStr;
    std::string m_tagData;
    Mushware::U32 m_contentStart;
    Mushware::U32 m_contentLineNum;
};

inline Mushware::U8
MushcoreXMLIStream::ByteGet(void)
{
    if (m_contentStart >= m_contentStr.size())
    {
        InputFetch();
    }
    return m_contentStr[m_contentStart];
}

inline Mushware::U8
MushcoreXMLIStream::ByteTake(void)
{
    if (m_contentStart >= m_contentStr.size())
    {
        InputFetch();
    }
    // cout << "took '" << m_contentStr[m_contentStart] << "'" << endl;
    return m_contentStr[m_contentStart++];
}

inline void
operator>>(MushcoreXMLIStream& ioIn, Mushware::U64& outObj)
{
    ioIn.ObjectRead(outObj);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, Mushware::U32& outObj)
{
    ioIn.ObjectRead(outObj);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, Mushware::U8& outObj)
{
    ioIn.ObjectRead(outObj);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, Mushware::tVal& outObj)
{
    ioIn.ObjectRead(outObj);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, Mushware::tXMLVal& outObj)
{
    ioIn.ObjectRead(outObj);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, bool& outObj)
{
    Mushware::tXMLVal xmlVal;
    ioIn.ObjectRead(xmlVal);
    outObj = !(!xmlVal);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, std::string& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::vector<T>& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::vector<T *>& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::list<T>& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::list<T *>& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::deque<T>& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::deque<T *>& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T, class U>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::map<T, U>& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T, class U>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::map<T, U *>& outObj)
{
    ioIn.ObjectRead(outObj);
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, T *& outpObj)
{
    ioIn.ObjectRead(outpObj);
}

template<class T>
inline void
MushcoreXMLIStream::ObjectRead(T *& outpObj)
{
    if (VirtualIs(outpObj))
    {
        ObjectReadVirtual(reinterpret_cast<MushcoreVirtualObject *&>(outpObj));
    }
    else
    {
        if (m_contentStr.substr(m_contentStart, 4) == "NULL")
        {
            outpObj = NULL;
            m_contentStart += 4;;
        }
        else
        {
            if (outpObj == NULL)
            {
                outpObj = new T;
            }
            *this >> *outpObj;
        }
    }
}

/* Specialises the above.  The above still catches all cases derived from
 * MushcoreVirtualObject, but the above won't compile for plain
 * MushcoreVirtualObject because it can't be allocated by the new.
 */
template<>
inline void
MushcoreXMLIStream::ObjectRead(MushcoreVirtualObject *& outpObj)
{
    ObjectReadVirtual(outpObj);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, MushcoreVirtualObject& outObj)
{
    ioIn.ObjectReadVirtual(outObj);
}

inline void
operator>>(MushcoreXMLIStream& ioIn, MushcoreVirtualObject *& outpObj)
{
    ioIn.ObjectReadVirtual(outpObj);
}

template<class T>
inline void
operator>>(MushcoreXMLIStream& ioIn, std::auto_ptr<T>& outaObj)
{
    T *pObj = outaObj.get();
    ioIn >> pObj;
    if (pObj != outaObj.get())
    {
        outaObj.reset(pObj);
    }
}

template<class T>
inline void
MushcoreXMLIStream::ObjectRead(std::vector<T>& inVector)
{
    // Decode the (x,y,z) sequence
    bool hasTag = CompositePrologue();

    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            inVector.push_back(T());
            try
            {
                *this >> inVector.back();
            }
            catch (...)
            {
                // Remove partially written object
                inVector.pop_back();
                throw;
            }
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in vector");
            }
        }
    }
    CompositeEpilogue(hasTag);
}

template<class T>
inline void
MushcoreXMLIStream::ObjectRead(std::vector<T *>& inVector)
{
    // Decode the (x,y,z) sequence

    bool hasTag = CompositePrologue();

    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            T *newPtr = NULL;
            *this >> newPtr;
            inVector.push_back(newPtr);

            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in vector");
            }
        }
    }
    CompositeEpilogue(hasTag);
}

// List functions are a direct copy of vector functions
template<class T>
inline void
MushcoreXMLIStream::ObjectRead(std::list<T>& inVector)
{
    // Decode the (x,y,z) sequence
    bool hasTag = CompositePrologue();
    
    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            inVector.push_back(T());
            try
            {
                *this >> inVector.back();
            }
            catch (...)
            {
                // Remove partially written object
                inVector.pop_back();
                throw;
            }
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in list");
            }
        }
    }
    CompositeEpilogue(hasTag);
}

template<class T>
inline void
MushcoreXMLIStream::ObjectRead(std::list<T *>& inVector)
{
    // Decode the (x,y,z) sequence
    
    bool hasTag = CompositePrologue();
    
    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            T *newPtr = NULL;
            *this >> newPtr;
            inVector.push_back(newPtr);
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in list");
            }
        }
    }
    CompositeEpilogue(hasTag);
}

// Deque functions are a direct copy of vector functions
template<class T>
inline void
MushcoreXMLIStream::ObjectRead(std::deque<T>& inVector)
{
    // Decode the (x,y,z) sequence
    bool hasTag = CompositePrologue();
    
    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            inVector.push_back(T());
            try
            {
                *this >> inVector.back();
            }
            catch (...)
            {
                // Remove partially written object
                inVector.pop_back();
                throw;
            }
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in deque");
            }
        }
    }
    CompositeEpilogue(hasTag);
}

template<class T>
inline void
MushcoreXMLIStream::ObjectRead(std::deque<T *>& inVector)
{
    // Decode the (x,y,z) sequence
    
    bool hasTag = CompositePrologue();
    
    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            T *newPtr = NULL;
            *this >> newPtr;
            inVector.push_back(newPtr);
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in deque");
            }
        }
    }
    CompositeEpilogue(hasTag);
}

template<class T, class U>
inline void
MushcoreXMLIStream::ObjectRead(std::map<T, U>& inMap)
{
    bool hasTag = CompositePrologue();

    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            T keyValue;
            *this >> keyValue;

            if (ByteTake() != '=')
            {
                Throw("Bad separator in map");
            }
            // Read completely before setting the map, in case of exception
            U valueValue;
            *this >> valueValue;
            inMap[keyValue] = valueValue;
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in map");
            }
        }
    }
    CompositeEpilogue(hasTag);
}

template<class T, class U>
inline void
MushcoreXMLIStream::ObjectRead(std::map<T, U *>& inMap)
{
    bool hasTag = CompositePrologue();
    
    if (ByteGet() == ')')
    {
        // Consume the end marker
        ByteTake();
    }
    else
    {
        for (;;)
        {
            T keyValue;
            *this >> keyValue;
            
            if (ByteTake() != '=')
            {
                Throw("Bad separator in map");
            }
            
            // Read completely before setting the map, in case of exception
            U *valuePtr = NULL;
            *this >> valuePtr;
            inMap[keyValue] = valuePtr;
            
            Mushware::U8 nextByte = ByteTake();
            if (nextByte == ',')
            {
            }
            else if (nextByte == ')')
            {
                return;
            }
            else
            {
                Throw("Bad delimiter in map");
            }
        }
    }
    CompositeEpilogue(hasTag);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
