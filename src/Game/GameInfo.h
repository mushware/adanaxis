/*
 * $Id$
 * $Log$
 */

#include "Mushcore.h"

class GameInfo : public MushcoreInfo
{
public:
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);
    virtual std::string PackageIDGet(void);

    static void Install(void);
};
