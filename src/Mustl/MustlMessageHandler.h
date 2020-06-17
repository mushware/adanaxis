//%includeGuardStart {
#ifndef MUSTLMESSAGEHANDLER_H
#define MUSTLMESSAGEHANDLER_H
//%includeGuardStart } eoVFM54gveFyGhSDCR2BDA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlMessageHandler.h
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
//%Header } 6KLxfrG72ctbp4kXm554Cw
/*
 * $Id: MustlMessageHandler.h,v 1.8 2006/06/01 20:13:01 southa Exp $
 * $Log: MustlMessageHandler.h,v $
 * Revision 1.8  2006/06/01 20:13:01  southa
 * Initial texture caching
 *
 * Revision 1.7  2006/06/01 15:39:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:27  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.1  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.3  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 * Revision 1.2  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.1  2002/11/25 12:06:18  southa
 * Received net message routing
 *
 */

#include "MustlStandard.h"

class MustlData;
class MustlLink;

class MustlMessageHandler
{
public:
	virtual ~MustlMessageHandler() {}
    virtual void MessageHandle(MustlData& ioData, MustlLink& inLink, Mustl::U32 inType) = 0;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
