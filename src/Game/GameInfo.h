#ifndef GAMEINFO_H
#define GAMEINFO_H
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
 * $Id: GameInfo.h,v 1.2 2003/04/06 12:35:23 southa Exp $
 * $Log: GameInfo.h,v $
 * Revision 1.2  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.1  2003/03/11 22:15:09  southa
 * Added GameInfo
 *
 */

#include "Mushcore.h"

class GameInfo : public MushcoreInfo
{
public:
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);

    static void Install(void);
};
#endif
