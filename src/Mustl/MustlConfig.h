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
 * $Id: MustlConfig.h,v 1.2 2003/01/13 23:05:22 southa Exp $
 * $Log: MustlConfig.h,v $
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
    void Set(const std::string& inName, const MushcoreScalar& inValue);
    void Set(const std::string& inName, const std::string& inStr);
    void Set(const std::string& inName, const Mustl::U32& inValue);
    
    const MushcoreScalar& Get(const std::string& inName) const;
    bool GetIfExists(const MushcoreScalar **outScalar, const std::string& inName) const;
    bool Exists(const std::string& inName) const;
    
    static MustlConfig& Instance(void);
    static void Install(void);

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
