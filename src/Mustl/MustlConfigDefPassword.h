//%includeGuardStart {
#ifndef MUSTLCONFIGDEFPASSWORD_H
#define MUSTLCONFIGDEFPASSWORD_H
//%includeGuardStart } Yt9Q0GvDgG4ttZ4LjOM3iA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefPassword.h
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
//%Header } VTbVXE/BbcSSS/yR/c6wSg
/*
 * $Id: MustlConfigDefPassword.h,v 1.8 2006/06/01 15:39:51 southa Exp $
 * $Log: MustlConfigDefPassword.h,v $
 * Revision 1.8  2006/06/01 15:39:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.6  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.5  2003/10/04 12:44:36  southa
 * File renaming
 *
 * Revision 1.4  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:23  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.1  2003/01/14 12:40:10  southa
 * Moved ConfigDefs into Mustl
 *
 */

#include "MustlConfigDef.h"
#include "MustlConfigDefString.h"
#include "MustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

// Password std::string input as text field (value not displayed)
class MustlConfigDefPassword : public MustlConfigDefString
{
public:
    explicit MustlConfigDefPassword(const std::string& inValue);
    virtual ~MustlConfigDefPassword();
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

    static MushcoreScalar MustlConfigPassword(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    static void NullFunction(void);

private:
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
