#ifndef MUSHCORESINGLETONCONCRETE_H
#define MUSHCORESINGLETONCONCRETE_H
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

#include "MushcoreSingleton.h"

template<class SingletonType> class MushcoreSingletonConcrete : public MushcoreSingleton<SingletonType>
{
public:
    static MUSHCORE_DECLARE_INLINE SingletonType& Instance(void);
    
protected:
    static MUSHCORE_DECLARE_INLINE void SingletonUncheckedNew(void);
};

template<class SingletonType>
inline SingletonType&
MushcoreSingletonConcrete<SingletonType>::Instance(void)
{
    if (!SingletonExists())
    {
        SingletonUncheckedNew();
    }
    return *SingletonPtrGet();
}


template<class SingletonType>
inline void
MushcoreSingletonConcrete<SingletonType>::SingletonUncheckedNew(void)
{
    SingletonPtrSet(new SingletonType);

#ifdef MUSHCORE_SINGLETON_TESTING
    cerr << "Created concrete " << typeid(SingletonType).name() << " singleton " << endl;
#endif
}
#endif
