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
 * $Id$
 * $Log$
 */

#include "MustlStandard.h"

class MustlConfig
{
public:
    static MustlConfig& Instance(void);
    static void Install(void);

protected:
    MustlConfig() {}
    
private:
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
