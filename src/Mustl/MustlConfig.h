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
 * $Id: MustlConfig.h,v 1.3 2003/01/14 12:40:10 southa Exp $
 * $Log: MustlConfig.h,v $
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
    ~MustlConfig();
    void PostDataHandle(const std::string& inData);
    
    static MustlConfig& Instance(void);

protected:
    MustlConfig();
    
private:
    MushcoreConfig *m_config;
    
    static std::auto_ptr<MustlConfig> m_instance;
};

inline MustlConfig&
MustlConfig::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new MustlConfig);
    return *m_instance;
}
#endif
