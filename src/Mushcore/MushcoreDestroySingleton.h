#ifndef MUSHCOREDESTROYSINGLETON_H
#define MUSHCOREDESTROYSINGLETON_H
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

#define MUSHCORE_DESTROY_SINGLETON_INSTANCE(SingletonType) \
namespace { MushcoreDestroySingleton<SingletonType> destroyer; };

template<class SingletonType> class MushcoreDestroySingleton
{
public:
    MUSHCORE_DECLARE_INLINE ~MushcoreDestroySingleton();

private:
};

template<class SingletonType>
inline
MushcoreDestroySingleton<SingletonType>::~MushcoreDestroySingleton(void)
{
    MushcoreSingleton<SingletonType>::SingletonDelete();
}
#endif
