/*
 * $Id$
 * $Log$
 */

#include "MustlStandard.h"

class MustlPlatformError
{
public:
    typedef int tErrorCode;
    static void Throw(const std::string& inPrefix);
    static void Throw(tErrorCode inCode, const std::string& inPrefix);
};
