#ifndef MUSHCOREABSTRACTSINGLETON_H
#define MUSHCOREABSTRACTSINGLETON_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MushcoreAbstractSingleton.h,v 1.4 2003/02/05 17:06:37 southa Exp $
 * $Log: MushcoreAbstractSingleton.h,v $
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
SingletonType *MushcoreAbstractSingleton< SingletonType >::m_pSingleton=NULL; \
MushcoreAbstractSingleton< SingletonType >::SingletonDestroyer MushcoreAbstractSingleton< SingletonType >::m_singletonDestroyer

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

#endif
