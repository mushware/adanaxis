#ifndef MUSHCOREINFO_H
#define MUSHCOREINFO_H
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
 * $Id: MushcoreInfo.h,v 1.3 2003/01/11 17:44:27 southa Exp $
 * $Log: MushcoreInfo.h,v $
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

class MushcoreInfo
{
public:
    static MushcoreInfo& Sgl(void);
    static void Mutate(MushcoreInfo *inInfo);

    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);
    virtual std::string PackageIDGet(void);

private:
    static MushcoreInfo *m_instance;
};

inline MushcoreInfo&
MushcoreInfo::Sgl(void)
{
    if (m_instance == NULL)
    {
        m_instance = new MushcoreInfo;
    }
    return *m_instance;
}
#endif
