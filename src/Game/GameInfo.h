/*
 * $Id: GameInfo.h,v 1.1 2003/03/11 22:15:09 southa Exp $
 * $Log: GameInfo.h,v $
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
