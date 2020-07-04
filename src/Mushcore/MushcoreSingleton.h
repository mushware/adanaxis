//%includeGuardStart {
#ifndef MUSHCORESINGLETON_H
#define MUSHCORESINGLETON_H
//%includeGuardStart } N4QiWRXFs9FO88BV25m5cw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreSingleton.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } ifmIYG92AjqOZ/XsLHNjXg
/*
 * $Id: MushcoreSingleton.h,v 1.10 2006/06/01 15:39:47 southa Exp $
 * $Log: MushcoreSingleton.h,v $
 * Revision 1.10  2006/06/01 15:39:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:16  southa
 * Mac release work
 *
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
