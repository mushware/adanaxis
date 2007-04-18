//%includeGuardStart {
#ifndef MUSHCOREINFO_H
#define MUSHCOREINFO_H
//%includeGuardStart } Ez8pYYNhqaFZHrLyeQoTFA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInfo.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } ANn1dyJ2X5Nkzsyg0S2Zfg
/*
 * $Id: MushcoreInfo.h,v 1.14 2006/07/28 16:52:25 southa Exp $
 * $Log: MushcoreInfo.h,v $
 * Revision 1.14  2006/07/28 16:52:25  southa
 * Options work
 *
 * Revision 1.13  2006/06/01 15:39:44  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/07/29 11:53:41  southa
 * MushcoreMaptor created
 *
 * Revision 1.11  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 * Revision 1.10  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:14  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.5  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.4  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/11 17:44:27  southa
 * Mushcore fixes
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/11/15 18:58:33  southa
 * Configuration mode
 *
 * Revision 1.1  2002/11/14 17:29:08  southa
 * Config database
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreSingleton.h"

class MushcoreInfo : public MushcoreSingleton<MushcoreInfo>
{
public:
    virtual ~MushcoreInfo() {}
    virtual std::string PlatformNameGet(void);
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageName(void) { return PackageNameGet(); }
    virtual std::string PackageVersionGet(void);
    virtual std::string PackageIDGet(void);
    virtual std::string PackageID(void) { return PackageIDGet(); }
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
