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
 * $Id$
 * $Log$
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

    static MUSHCORE_DECLARE_INLINE bool SingletonExists(void);
    static MUSHCORE_DECLARE_INLINE void SingletonDelete(void);

private:
    static SingletonType *m_instance;
};

template<class SingletonType>
inline SingletonType&
MushcoreSingleton<SingletonType>::Instance(void)
{
    if (m_instance == NULL)
    {
#ifdef MUSHCORE_SINGLETON_TESTING
        cerr << "Created singleton " << typeid(SingletonType).name() << endl;
#endif
        m_instance = new SingletonType;
    }
    return *m_instance;
}

template<class SingletonType>
inline bool
MushcoreSingleton<SingletonType>::SingletonExists(void)
{
    return (m_instance != NULL);
}

template<class SingletonType>
inline void
MushcoreSingleton<SingletonType>::SingletonDelete(void)
{
    if (m_instance != NULL)
    {
#ifdef MUSHCORE_SINGLETON_TESTING
        cerr << "Deleted singleton " << typeid(SingletonType).name() << endl;
#endif
        delete m_instance;
        m_instance = NULL;
    }
}
#endif
