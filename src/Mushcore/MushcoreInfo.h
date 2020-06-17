//%includeGuardStart {
#ifndef MUSHCOREINFO_H
#define MUSHCOREINFO_H
//%includeGuardStart } Ez8pYYNhqaFZHrLyeQoTFA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreInfo.h
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
//%Header } 8J9tU8sspLn8tcxo/Ak/vg
/*
 * $Id: MushcoreInfo.h,v 1.14 2006/07/28 16:52:25 southa Exp $
 * $Log: MushcoreInfo.h,v $
 * Revision 1.14  2006/07/28 16:52:25  southa
 * Options work
 *
 * Revision 1.13  2006/06/01 15:39:44  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/07/29 11:53:41  southa
 * MushcoreMaptor created
 *
 * Revision 1.11  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 * Revision 1.10  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:14  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/04/06 12:35:23  southa
 * Fixes for release
 *
 * Revision 1.5  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.4  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/11 17:44:27  southa
 * Mushcore fixes
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/11/15 18:58:33  southa
 * Configuration mode
 *
 * Revision 1.1  2002/11/14 17:29:08  southa
 * Config database
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreSingleton.h"

class MushcoreInfo : public MushcoreSingleton<MushcoreInfo>
{
public:
    virtual ~MushcoreInfo() {}
    virtual std::string PlatformNameGet(void);
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageName(void) { return PackageNameGet(); }
    virtual std::string PackageVersionGet(void);
    virtual std::string PackageIDGet(void);
    virtual std::string PackageID(void) { return PackageIDGet(); }
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
