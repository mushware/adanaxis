//%includeGuardStart {
#ifndef MUSHCOREPIPE_H
#define MUSHCOREPIPE_H
//%includeGuardStart } b5NU7DxOeru55TF0pY1A6w
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcorePipe.h
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
//%Header } V673evBt8atoG2oqzRL1Hg
/*
 * $Id: MushcorePipe.h,v 1.2 2005/06/20 16:14:31 southa Exp $
 * $Log: MushcorePipe.h,v $
 * Revision 1.2  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 14:25:46  southa
 * Pipe and ordered data work
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreAutoBool.h"
#include "MushcoreFail.h"
#include "MushcoreSingleton.h"
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"

/* This pipe allows Give and TopGet/TopDelete from different threads.  However only
 * a single thread can add, and a single thread can take
 */

//:generate nonvirtual inline ostream
template<class T>
class MushcorePipe : public MushcoreSingleton< MushcorePipe<T> >
{
public:
    MushcorePipe(Mushware::U32 inSize = MushcorePipe::kDefaultSize);
    ~MushcorePipe();
    void Give(T *ioObj);
    bool TopGet(const T *& outRef);
    bool TopGet(T *& outRef) { return TopGet(*const_cast<const T **>(&outRef)); }
    void TopDelete();
    void NotAccessingSoGrow(const Mushware::U32 inLimit);
    
private:
    enum
    {
        kDefaultSize = 256
    };
    
    std::vector<T *> m_values;
    
    Mushware::U32 m_readIndex;
    Mushware::U32 m_writeIndex;

    bool m_readThreaded;
    bool m_writeThreaded;
    
    Mushware::U32 m_highWaterMark; //:read
//%classPrototypes {
public:
    const Mushware::U32& HighWaterMark(void) const { return m_highWaterMark; }
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } VMHzhqMNnzqnWRyMmaN6iA
};


template<class T>
MushcorePipe<T>::MushcorePipe(Mushware::U32 inSize) :
    m_values(inSize),
    m_readIndex(0),
    m_writeIndex(0),
    m_readThreaded(false),
    m_writeThreaded(false),
    m_highWaterMark(0)
{
}

template<class T>
MushcorePipe<T>::~MushcorePipe()
{
    T *pDelete;
    while (TopGet(pDelete))
    {
        TopDelete();
    }
}

template<class T>
inline void
MushcorePipe<T>::Give(T *ioObj)
{
    MUSHCOREASSERT(ioObj != NULL);
    
    Mushware::U32 newIndex = 0;
    
    try
    {
        if (m_writeThreaded)
        {
            throw MushcoreLogicFail("Thread clash within Give");  
        }
        
        MushcoreAutoBool autoBool(m_writeThreaded);
        
        newIndex = m_writeIndex + 1;
        if (newIndex >= m_values.size())
        {
            newIndex = 0;   
        }
            
        if (newIndex == m_readIndex)
        {
            throw MushcoreRequestFail("Queue full - object discarded");  
        }
        MUSHCOREASSERT(m_writeIndex < m_values.size());
        m_values[m_writeIndex] = ioObj;
    }
    catch (...)
    {
        // Prevent memory leak.  All exceptions will discard the object
        delete ioObj;
        throw;
    }
    m_writeIndex = newIndex;
    MUSHCOREASSERT(m_writeIndex < m_values.size());
}

template<class T>
inline bool
MushcorePipe<T>::TopGet(const T *& outRef)
{
    if (m_readThreaded)
    {
        throw MushcoreLogicFail("Thread clash within Take");  
    }
    
    MushcoreAutoBool autoBool(m_readThreaded);
    
    bool retVal = false;
    
    if (m_readIndex != m_writeIndex)
    {
        MUSHCOREASSERT(m_readIndex < m_values.size());

        outRef = m_values[m_readIndex];
        retVal = true;
    }
    
    return retVal;
}

template<class T>
inline void
MushcorePipe<T>::TopDelete(void)
{
    if (m_readThreaded)
    {
        throw MushcoreLogicFail("Thread clash within Take");  
    }
    
    MushcoreAutoBool autoBool(m_readThreaded);
    
    if (m_readIndex == m_writeIndex)
    {
        throw MushcoreLogicFail("TopDelete from empty pipe");        
    }
       
    MUSHCOREASSERT(m_readIndex < m_values.size());
    MUSHCOREASSERT(m_values[m_readIndex] != NULL);

    delete m_values[m_readIndex];
    m_values[m_readIndex] = NULL;
    
    Mushware::U32 newIndex = m_readIndex + 1;
    if (newIndex >= m_values.size())
    {
        newIndex = 0;   
    }
    m_readIndex = newIndex;    
    MUSHCOREASSERT(m_readIndex < m_values.size());
}

template<class T>
inline void
MushcorePipe<T>::NotAccessingSoGrow(const Mushware::U32 inLimit)
{
    if (m_readThreaded || m_writeThreaded)
    {
        throw MushcoreLogicFail("Thread clash within NotAccessingSoGrow");  
    }
    MushcoreAutoBool readBool(m_readThreaded);
    MushcoreAutoBool writeBool(m_writeThreaded);
    
    Mushware::U32 readLimit = m_writeIndex;

    if (readLimit < m_readIndex)
    {
        readLimit += m_values.size();
    }
    MUSHCOREASSERT(readLimit >= m_readIndex);
    
    Mushware::U32 filledEntries = readLimit - m_readIndex;
    
    if (filledEntries > m_highWaterMark)
    {
        m_highWaterMark = filledEntries;   
    }
    
    if (m_values.size() * 2 <= inLimit && (2+filledEntries)*4 >= m_values.size()*3)
    {
        // More than 75% full so resize
        Mushware::U32 oldSize = m_values.size();
        if (m_values.size() == 0)
        {
            m_values.resize(1);
        }
        else
        {
            m_values.resize(m_values.size() * 2);
        }
        if (m_writeIndex < m_readIndex)
        {
            // This fixes the effect of moving the wrapping point
            for (Mushware::U32 i=0; i<m_writeIndex; ++i)
            {
                MUSHCOREASSERT(i < m_values.size());
                MUSHCOREASSERT(i+oldSize < m_values.size());
                MUSHCOREASSERT(m_values[i] != NULL);

                m_values[i+oldSize] = m_values[i];
                m_values[i] = NULL;
            }
            m_writeIndex += oldSize;
        }
    }
    
    MUSHCOREASSERT(m_readIndex < m_values.size());
    MUSHCOREASSERT(m_writeIndex < m_values.size());
}
//%inlineHeader {
template<class T>
inline std::ostream&
operator<<(std::ostream& ioOut, const MushcorePipe<T>& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
template<class T>
inline void
MushcorePipe<T>::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "values=" << m_values << ", ";
    ioOut << "readIndex=" << m_readIndex << ", ";
    ioOut << "writeIndex=" << m_writeIndex << ", ";
    ioOut << "readThreaded=" << m_readThreaded << ", ";
    ioOut << "writeThreaded=" << m_writeThreaded << ", ";
    ioOut << "highWaterMark=" << m_highWaterMark;
    ioOut << "]";
}
//%inlineHeader } 003BMAJbRp6ZbabZoDu/pw

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
