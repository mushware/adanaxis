//%includeGuardStart {
#ifndef ADANAXISINFO_H
#define ADANAXISINFO_H
//%includeGuardStart } bJ/F2yu+Erlor+0OAZ7ebw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisInfo.h
 *
 * Copyright: Andy Southgate 2005-2006
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
//%Header } raxX4NIc/HtrwZuCsXO7ww
/*
 * $Id: AdanaxisInfo.h,v 1.2 2005/06/14 13:25:33 southa Exp $
 * $Log: AdanaxisInfo.h,v $
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "mushMushcore.h"

class AdanaxisInfo : public MushcoreInfo
{
public:
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);

    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
