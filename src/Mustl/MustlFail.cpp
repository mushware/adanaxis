//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlFail.cpp
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8kcpP7d8CjZwKwlI8CfzXA
/*
 * $Id: MustlFail.cpp,v 1.7 2003/08/21 23:09:24 southa Exp $
 * $Log: MustlFail.cpp,v $
 * Revision 1.7  2003/08/21 23:09:24  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/02/04 14:54:51  southa
 * Build fixes
 *
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

