#ifndef MUSHCORESINGLETON_H
#define MUSHCORESINGLETON_H
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
 * $Id: MushcoreSingleton.h,v 1.4 2003/02/05 17:06:38 southa Exp $
 * $Log: MushcoreSingleton.h,v $
 * Revision 1.4  2003/02/05 17:06:38  southa
 * Build fixes
 *
 * Revision 1.3  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreAbstractSingleton.h"

template<class SingletonType> class MushcoreSingleton : public MushcoreAbstractSingleton<SingletonType>
{
public:
    static inline SingletonType& Sgl(void);
    
protected:
    static inline void SingletonUncheckedNew(void);
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
