#ifndef MUSTLCONFIG_H
#define MUSTLCONFIG_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MustlConfig.h,v 1.7 2003/01/17 00:41:03 southa Exp $
 * $Log: MustlConfig.h,v $
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
#endif
