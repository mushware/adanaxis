#ifndef MUSHCOREABSTRACTSINGLETON_H
#define MUSHCOREABSTRACTSINGLETON_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreAbstractSingleton.h,v 1.2 2003/01/20 15:38:27 southa Exp $
 * $Log: MushcoreAbstractSingleton.h,v $
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
SingletonType *MushcoreAbstractSingleton< SingletonType >::m_pSingleton=NULL; \
MushcoreAbstractSingleton< SingletonType >::SingletonDestroyer MushcoreAbstractSingleton< SingletonType >::m_singletonDestroyer

template<class SingletonType> class MushcoreAbstractSingleton
{
public:
    class SingletonDestroyer
    {
    public:
        MUSHCORE_DECLARE_INLINE ~SingletonDestroyer()
		{
			SingletonDestroy();
		}
    };
    
    static MUSHCORE_DECLARE_INLINE SingletonType& Sgl(void);

    static MUSHCORE_DECLARE_INLINE void SingletonCreate(SingletonType *inObj);
    static MUSHCORE_DECLARE_INLINE void SingletonMutate(SingletonType *inObj);
    static MUSHCORE_DECLARE_INLINE void SingletonDestroy(void);
    static MUSHCORE_DECLARE_INLINE bool SingletonExists(void);
    
protected:
    static MUSHCORE_DECLARE_INLINE SingletonType *SingletonPtrGet(void);
    static MUSHCORE_DECLARE_INLINE void SingletonPtrSet(SingletonType *inObj);
    static MUSHCORE_DECLARE_INLINE void SingletonUncheckedNew(void);
    static MUSHCORE_DECLARE_INLINE void SingletonUncheckedDelete(void);

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

#endif
