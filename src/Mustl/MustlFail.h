#ifndef MUSTLFAIL_H
#define MUSTLFAIL_H
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
 * $Id: MustlFail.h,v 1.4 2003/01/07 17:13:44 southa Exp $
 * $Log: MustlFail.h,v $
 * Revision 1.4  2003/01/07 17:13:44  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.3  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.2  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 */

#include "MustlStandard.h"

#if defined(HAVE_MUSHCORE_MUSHCORE_H)
#include <Mushcore/MushcoreFail.h>
#else
#if defined(HAVE_MUSHCORE_H)
#include <MushcoreFail.h>
#else
#include "MushcoreFail.h"
#endif
#endif

class MustlFail : public MushcoreNonFatalFail
{
public:
    MustlFail(const std::string &inMessage);
};
#endif
