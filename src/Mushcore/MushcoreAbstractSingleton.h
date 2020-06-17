//%includeGuardStart {
#ifndef MUSHCOREABSTRACTSINGLETON_H
#define MUSHCOREABSTRACTSINGLETON_H
//%includeGuardStart } q4zmtcQLslETVqi2OBKgtw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAbstractSingleton.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } TYrqs3fE5Q0q7a8LCo1x2g
/*
 * $Id: MushcoreAbstractSingleton.h,v 1.11 2006/06/01 15:39:40 southa Exp $
 * $Log: MushcoreAbstractSingleton.h,v $
 * Revision 1.11  2006/06/01 15:39:40  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.9  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.8  2005/05/18 15:53:27  southa
 * Made buildable using gcc 4.0/Mac OS X 10.4
 *
 * Revision 1.7  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:03  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.3  2003/02/04 12:24:49  southa
 * Build fix
 *
 * Revision 1.2  2003/01/20 15:38:27  southa
 * Created MushcoreTest
 *
 * Revision 1.1  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.2  2003/01/18 17:05:47  southa
 * Singleton work
 *
 * Revision 1.1  2003/01/18 13:33:59  southa
 * Created MushcoreAbstractSingleton
 *
 */

#include "MushcoreStandard.h"

#ifdef MUSHCORE_SINGLETON_TESTING
#include <typeinfo>
#endif

#define MUSHCORE_SINGLETON_INSTANCE(SingletonType) \
template<> SingletonType *MushcoreAbstractSingleton< SingletonType >::m_pSingleton=NULL; \
template<> MushcoreAbstractSingleton< SingletonType >::SingletonDestroyer MushcoreAbstractSingleton< SingletonType >::m_singletonDestroyer

#define MUSHCORE_SINGLETON_INSTANCE2(SingletonType1, SingletonType2) \
template<> SingletonType1, SingletonType2 *MushcoreAbstractSingleton< SingletonType1, SingletonType2 >::m_pSingleton=NULL; \
template<> MushcoreAbstractSingleton< SingletonType1, SingletonType2 >::SingletonDestroyer MushcoreAbstractSingleton< SingletonType1, SingletonType2 >::m_singletonDestroyer

template<class SingletonType> class MushcoreAbstractSingleton
{
public:
    class SingletonDestroyer
    {
    public:
        inline ~SingletonDestroyer()
		{
			SingletonDestroy();
		}
    };
    
    static inline SingletonType& Sgl(void);

    static inline void SingletonCreate(SingletonType *inObj);
    static inline void SingletonMutate(SingletonType *inObj);
    static inline void SingletonDestroy(void);
    static inline bool SingletonExists(void);
    
protected:
    static inline SingletonType *SingletonPtrGet(void);
    static inline void SingletonPtrSet(SingletonType *inObj);
    static inline void SingletonUncheckedNew(void);
    static inline void SingletonUncheckedDelete(void);

private:        
        
    static SingletonType *m_pSingleton;
    static SingletonDestroyer m_singletonDestroyer;
};

template<class SingletonType>
inline SingletonType *
MushcoreAbstractSingleton<SingletonType>::SingletonPtrGet(void)
{
    return m_pSingleton;
}

template<class SingletonType>
inline void
MushcoreAbstractSingleton<SingletonType>::SingletonPtrSet(SingletonType *inObj)
{
    m_pSingleton = inObj;
}

template<class SingletonType>
inline void
MushcoreAbstractSingleton<SingletonType>::SingletonUncheckedNew(void)
{
    SingletonPtrSet(SingletonType::SingletonFactory());

#ifdef MUSHCORE_SINGLETON_TESTING
    cerr << "Created abstract " << typeid(SingletonType).name() << " singleton as " << typeid(*SingletonPtrGet()).name() << endl;
#endif
}

template<class SingletonType>
inline void
MushcoreAbstractSingleton<SingletonType>::SingletonUncheckedDelete(void)
{
    MUSHCOREASSERT(SingletonPtrGet() != NULL);
    delete SingletonPtrGet();
    SingletonPtrSet(NULL);

#ifdef MUSHCORE_SINGLETON_TESTING
    cerr << "Deleted " << typeid(SingletonType).name() << " singleton" << endl;
#endif
}

template<class SingletonType>
inline SingletonType&
MushcoreAbstractSingleton<SingletonType>::Sgl(void)
{
    if (!SingletonExists())
    {
        SingletonUncheckedNew();
    }
    return *SingletonPtrGet();
}

template<class SingletonType>
inline void
MushcoreAbstractSingleton<SingletonType>::SingletonCreate(SingletonType *inObj)
{
    if (SingletonExists())
    {
        SingletonUncheckedDelete();
    }
    SingletonPtrSet(inObj);
}

template<class SingletonType>
inline void
MushcoreAbstractSingleton<SingletonType>::SingletonMutate(SingletonType *inObj)
{
    SingletonDestroy();
    SingletonPtrSet(inObj);
    
#ifdef MUSHCORE_SINGLETON_TESTING
    cerr << "Mutated " << typeid(SingletonType).name() << " singleton to " << typeid(inObj).name() << endl;
#endif
}

template<class SingletonType>
inline void
MushcoreAbstractSingleton<SingletonType>::SingletonDestroy(void)
{
    if (SingletonExists())
    {
        SingletonUncheckedDelete();
    }
}

template<class SingletonType>
inline bool
MushcoreAbstractSingleton<SingletonType>::SingletonExists(void)
{
    return (SingletonPtrGet() != NULL);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
