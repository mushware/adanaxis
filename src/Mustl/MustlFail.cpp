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
 * $Id: MustlFail.cpp,v 1.5 2003/01/16 15:58:01 southa Exp $
 * $Log: MustlFail.cpp,v $
 * Revision 1.5  2003/01/16 15:58:01  southa
 * Mustl exception handling
 *
 * Revision 1.4  2003/01/14 17:38:21  southa
 * Mustl web configuration
 *
 * Revision 1.3  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.2  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 */

#include "MustlFail.h"

#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

MustlFail::MustlFail(const string& inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}

MustlPermanentFail::MustlPermanentFail(const string& inMessage) :
    MustlFail(inMessage)
{
}

MustlTemporaryFail::MustlTemporaryFail(const string& inMessage) :
    MustlFail(inMessage)
{
}

MustlAddressFail::MustlAddressFail(const string& inMessage) :
    MustlPermanentFail(inMessage)
{
}

MustlConnectionFail::MustlConnectionFail(const string& inMessage) :
    MustlPermanentFail(inMessage)
{
}

MustlMessageFail::MustlMessageFail(const string& inMessage) :
    MustlPermanentFail(inMessage)
{
}

MustlSocketFail::MustlSocketFail(const string& inMessage) :
    MustlPermanentFail(inMessage)
{
}

MustlSocketOrUDPFail::MustlSocketOrUDPFail(const string& inMessage) :
    MustlSocketFail(inMessage)
{
}

