//%includeGuardStart {
#ifndef ADANAXISUTIL_H
#define ADANAXISUTIL_H
//%includeGuardStart } xu4PJKjPyonUX1Z4uvxgtQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisUtil.h
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } h0Ba5isJoX+glev7XNkQ4g
/*
 * $Id: AdanaxisUtil.h,v 1.1 2005/06/30 16:29:24 southa Exp $
 * $Log: AdanaxisUtil.h,v $
 * Revision 1.1  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisLogic.h"

class AdanaxisAppHandler;

class AdanaxisUtil
{
public:
    static void TestPiecesCreate(AdanaxisLogic& ioLogic);
    static AdanaxisAppHandler& AppHandler(void);

};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
