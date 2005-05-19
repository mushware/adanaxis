//%includeGuardStart {
#ifndef MUSHCORESINGLETON_H
#define MUSHCORESINGLETON_H
//%includeGuardStart } N4QiWRXFs9FO88BV25m5cw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreSingleton.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jjB23GsrqS9ioq7odHW8KQ
/*
 * $Id: MushcoreSingleton.h,v 1.8 2005/05/18 15:53:27 southa Exp $
 * $Log: MushcoreSingleton.h,v $
 * Revision 1.8  2005/05/18 15:53:27  southa
 * Made buildable using gcc 4.0/Mac OS X 10.4
 *
 * Revision 1.7  2004/01/02 21:13:13  southa
 * Source conditioning
 *
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
    if (!MushcoreAbstractSingleton<SingletonType>::SingletonExists())
    {
        SingletonUncheckedNew();
    }
    return *MushcoreAbstractSingleton<SingletonType>::SingletonPtrGet();
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
