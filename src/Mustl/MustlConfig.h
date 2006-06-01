//%includeGuardStart {
#ifndef MUSTLCONFIG_H
#define MUSTLCONFIG_H
//%includeGuardStart } 7exiga1YnbGZM6fIhLkgTA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfig.h
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
//%Header } ZTr3NR70xbkbl/wUqunTCg
/*
 * $Id: MustlConfig.h,v 1.12 2005/05/19 13:02:17 southa Exp $
 * $Log: MustlConfig.h,v $
 * Revision 1.12  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:09:21  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.7  2003/01/17 00:41:03  southa
 * Configuration updates from POST data
 *
 * Revision 1.6  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.5  2003/01/14 20:46:11  southa
 * Post data handling
 *
 * Revision 1.4  2003/01/14 17:38:21  southa
 * Mustl web configuration
 *
 * Revision 1.3  2003/01/14 12:40:10  southa
 * Moved ConfigDefs into Mustl
 *
 * Revision 1.2  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.1  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 */

#include "MustlStandard.h"

class MushcoreConfig;
class MushcoreScalar;

class MustlConfig
{
public:
    typedef void (*tUpdateHandler)(void);
    
    ~MustlConfig();
    
    MushcoreScalar Get(const std::string& inName) const;
    bool GetIfExists(MushcoreScalar& outScalar, const std::string& inName) const;
    void PostDataHandle(const std::string& inData);
    void UpdateHandlerAdd(tUpdateHandler inHandler);

    static MustlConfig& Sgl(void);
    static void Install(void);
    static void NullFunction(void);
    
protected:
    MustlConfig();
    
private:
    void UpdateHandlersCall(void) const;

    std::list<tUpdateHandler> m_updateHandlers;
    
    static MustlConfig *m_instance;
};

inline MustlConfig&
MustlConfig::Sgl(void)
{
    if (m_instance == NULL)
    {
        m_instance = new MustlConfig;
    }
    return *m_instance;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
