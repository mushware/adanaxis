#ifndef MUSHCORESINGLETON_H
#define MUSHCORESINGLETON_H
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
 * $Id: MushcoreSingleton.h,v 1.1 2003/01/18 13:33:59 southa Exp $
 * $Log: MushcoreSingleton.h,v $
 * Revision 1.1  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 */

#include "MushcoreStandard.h"

#define MUSHCORE_SINGLETON_TESTING 1

#ifdef MUSHCORE_SINGLETON_TESTING
#include <typeinfo>
#endif

#define MUSHCORE_SINGLETON_INSTANCE(SingletonType) \
SingletonType *MushcoreSingleton< SingletonType >::m_instance=NULL

template<class SingletonType> class MushcoreSingleton
{
public:
    static MUSHCORE_DECLARE_INLINE SingletonType& Instance(void);

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
    static SingletonType *m_instance;
};

template<class SingletonType>
inline SingletonType *
MushcoreSingleton<SingletonType>::SingletonPtrGet(void)
{
    return m_instance;
}

template<class SingletonType>
inline void
MushcoreSingleton<SingletonType>::SingletonPtrSet(SingletonType *inObj)
{
    m_instance = inObj;
}

template<class SingletonType>
inline void
MushcoreSingleton<SingletonType>::SingletonUncheckedNew(void)
{
    SingletonPtrSet(SingletonType::SingletonFactory());

#ifdef MUSHCORE_SINGLETON_TESTING
    cerr << "Created " << typeid(SingletonType).name() << " singleton as " << typeid(*SingletonPtrGet()).name() << endl;
#endif
}

template<class SingletonType>
inline void
MushcoreSingleton<SingletonType>::SingletonUncheckedDelete(void)
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
MushcoreSingleton<SingletonType>::Instance(void)
{
    if (!SingletonExists())
    {
        SingletonUncheckedNew();
    }
    return *SingletonPtrGet();
}

template<class SingletonType>
inline void
MushcoreSingleton<SingletonType>::SingletonCreate(SingletonType *inObj)
{
    if (SingletonExists())
    {
        SingletonUncheckedDelete();
    }
    SingletonPtrSet(inObj);
}

template<class SingletonType>
inline void
MushcoreSingleton<SingletonType>::SingletonMutate(SingletonType *inObj)
{
    SingletonDestroy();
    SingletonPtrSet(inObj);
    
#ifdef MUSHCORE_SINGLETON_TESTING
    cerr << "Mutated " << typeid(SingletonType).name() << " singleton to " << typeid(inObj).name() << endl;
#endif
}

template<class SingletonType>
inline void
MushcoreSingleton<SingletonType>::SingletonDestroy(void)
{
    if (SingletonExists())
    {
        SingletonUncheckedDelete();
    }
}

template<class SingletonType>
inline bool
MushcoreSingleton<SingletonType>::SingletonExists(void)
{
    return (SingletonPtrGet() != NULL);
}


#endif
