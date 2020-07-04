//%includeGuardStart {
#ifndef MUSHFILESTANDARD_H
#define MUSHFILESTANDARD_H
//%includeGuardStart } oWG3143JIAQhJhABgtpLng
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileStandard.h
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
//%Header } abEP8DstkjSLL7YgoAr2jw
/*
 * $Id: MushFileStandard.h,v 1.3 2007/06/14 01:03:53 southa Exp $
 * $Log: MushFileStandard.h,v $
 * Revision 1.3  2007/06/14 01:03:53  southa
 * win32 build fixes
 *
 * Revision 1.2  2007/04/18 09:22:33  southa
 * Header and level fixes
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#if defined(HAVE_CONFIG_H)  && !defined(MUSHWARE_CONFIG_H)
#define MUSHWARE_CONFIG_H 1
#include "config.h"
#endif

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/Mushcore.h>
#include <Mushcore/MushcoreIO.h>
#elif defined(HAVE_MUSHCORE_H)
#include <Mushcore.h>
#include <MushcoreIO.h>
#else
#include "Mushcore/Mushcore.h"
#include "Mushcore/MushcoreIO.h"
#endif

namespace MushFile
{
    enum tSourceType
    {
        kSourceTypeInvalid,
        kSourceTypeNone,
        kSourceTypeNull,
        kSourceTypeFile,
        kSourceTypeMush
    };
};

inline void
operator>>(MushcoreXMLIStream& ioIn, MushFile::tSourceType& outObj)
{
    Mushware::tXMLVal xmlVal;
    ioIn.ObjectRead(xmlVal);
    outObj = static_cast<MushFile::tSourceType>(static_cast<Mushware::U32>(xmlVal));
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
