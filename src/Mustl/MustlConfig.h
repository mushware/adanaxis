//%includeGuardStart {
#ifndef MUSTLCONFIG_H
#define MUSTLCONFIG_H
//%includeGuardStart } 7exiga1YnbGZM6fIhLkgTA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfig.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jzVKfORJ+LaRcKpuHLDOaw
/*
 * $Id: MustlConfig.h,v 1.9 2003/08/21 23:09:21 southa Exp $
 * $Log: MustlConfig.h,v $
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
