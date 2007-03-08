//%includeGuardStart {
#ifndef MUSHFILESTANDARD_H
#define MUSHFILESTANDARD_H
//%includeGuardStart } oWG3143JIAQhJhABgtpLng
//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileStandard.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } TXLH7M18EUaGKmZciXm8Lg
/*
 * $Id$
 * $Log$
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
        kSourceTypeFile,
        kSourceTypeMush
    };
};

inline void
operator>>(MushcoreXMLIStream& ioIn, MushFile::tSourceType& outObj)
{
    Mushware::tXMLVal xmlVal;
    ioIn.ObjectRead(xmlVal);
    outObj = static_cast<MushFile::tSourceType>(xmlVal);
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw