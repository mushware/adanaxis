//%includeGuardStart {
#ifndef MUSHCORESINGLETON_H
#define MUSHCORESINGLETON_H
//%includeGuardStart } N4QiWRXFs9FO88BV25m5cw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreSingleton.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0v/Ao4e1eUt3CGt7KXHrzg
/*
 * $Id: MushcoreSingleton.h,v 1.6 2003/09/17 19:40:36 southa Exp $
 * $Log: MushcoreSingleton.h,v $
 * Revision 1.6  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:17  southa
 * Fixed file headers
 *
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
