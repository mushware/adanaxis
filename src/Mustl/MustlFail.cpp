//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlFail.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } MLk2BXIY0G7rn6IB1tQtzw
/*
 * $Id: MustlFail.cpp,v 1.11 2006/06/01 15:39:51 southa Exp $
 * $Log: MustlFail.cpp,v $
 * Revision 1.11  2006/06/01 15:39:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
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

