#ifndef MUSHCOREINFO_H
#define MUSHCOREINFO_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MushcoreInfo.h,v 1.6 2003/04/06 12:35:23 southa Exp $
 * $Log: MushcoreInfo.h,v $
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
    virtual std::string PlatformNameGet(void);
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);
    virtual std::string PackageIDGet(void);
};

#endif
