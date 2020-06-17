//%includeGuardStart {
#ifndef MUSTL_H
#define MUSTL_H
//%includeGuardStart } +ma131Bw15+7b52E1NNUuA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/Mustl.h
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
//%Header } OCDeZ0grycgh2H5a8MyPgw
/*
 * $Id: Mustl.h,v 1.13 2006/06/01 15:39:49 southa Exp $
 * $Log: Mustl.h,v $
 * Revision 1.13  2006/06/01 15:39:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:09:19  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.7  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.6  2003/01/14 20:46:10  southa
 * Post data handling
 *
 * Revision 1.5  2003/01/14 17:38:21  southa
 * Mustl web configuration
 *
 * Revision 1.4  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/12 18:38:24  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.5  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.4  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 * Revision 1.3  2002/11/03 18:43:09  southa
 * Network fixes
 *
 * Revision 1.2  2002/11/02 11:22:51  southa
 * Simplified UDP send and receive
 *
 * Revision 1.1  2002/10/31 15:52:15  southa
 * First network code
 *
 */

#include "MustlAddress.h"
#include "MustlConfig.h"
#include "MustlConfigDef.h"
#include "MustlConfigDefBool.h"
#include "MustlConfigDefMenuString.h"
#include "MustlConfigDefPassword.h"
#include "MustlConfigDefString.h"
#include "MustlConfigDefU32.h"
#include "MustlConfigDefVal.h"
#include "MustlData.h"
#include "MustlFail.h"
#include "MustlID.h"
#include "MustlIDNull.h"
#include "MustlIDString.h"
#include "MustlLink.h"
#include "MustlLog.h"
#include "MustlMessageHandler.h"
#include "MustlPlatform.h"
#include "MustlProtocol.h"
#include "MustlRouter.h"
#include "MustlServer.h"
#include "MustlTimer.h"
#include "MustlUtils.h"
#include "MustlWebLink.h"
#include "MustlWebRouter.h"
#include "MustlWebServer.h"

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
