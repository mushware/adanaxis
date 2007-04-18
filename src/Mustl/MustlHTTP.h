//%includeGuardStart {
#ifndef MUSTLHTTP_H
#define MUSTLHTTP_H
//%includeGuardStart } ygAtBr/HcT1nWLv6mmg08w
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlHTTP.h
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
//%Header } Hkm7uRnQSY0WUaQA6IqoZQ
/*
 * $Id: MustlHTTP.h,v 1.9 2006/06/01 15:39:52 southa Exp $
 * $Log: MustlHTTP.h,v $
 * Revision 1.9  2006/06/01 15:39:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:25  southa
 * Fixed file headers
 *
 * Revision 1.4  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.2  2002/11/12 17:05:01  southa
 * Tidied localweb server
 *
 * Revision 1.1  2002/11/07 00:53:37  southa
 * localweb work
 *
 */

#include "MustlStandard.h"

class MustlData;

class MustlHTTP
{
public:
    MustlHTTP();
    ~MustlHTTP();
    void Reply200(void);
    void ContentTypeHTML(void);
    void ContentType(const std::string& inStr);
    void Endl(void);
    void Header(void);
    void Footer(void);
    void AllowCachingSet(void) { m_allowCaching=true; }
    std::ostream& Out(void) { return *m_content; }
    void ContentGet(MustlData& outData);
    
private:
    std::ostream *m_content;
    Mustl::U32 m_refresh;    
    std::string m_title;
    bool m_allowCaching;
    static const char m_endl[3];
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
