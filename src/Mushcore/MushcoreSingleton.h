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

#include "MushcoreAbstractSingleton.h"

template<class SingletonType> class MushcoreSingleton : public MushcoreAbstractSingleton<SingletonType>
{
public:
    static MUSHCORE_DECLARE_INLINE SingletonType& Sgl(void);
    
protected:
    static MUSHCORE_DECLARE_INLINE void SingletonUncheckedNew(void);
};

template<class SingletonType>
inline SingletonType&
MushcoreSingleton<SingletonType>::Sgl(void)
{
    if (!SingletonExists())
    {
        SingletonUncheckedNew();
    }
    return *SingletonPtrGet();
}


template<class SingletonType>
inline void
MushcoreSingleton<SingletonType>::SingletonUncheckedNew(void)
{
    SingletonPtrSet(new SingletonType);

#ifdef MUSHCORE_SINGLETON_TESTING
    cerr << "Created " << typeid(SingletonType).name() << " singleton " << endl;
#endif
}
#endif
