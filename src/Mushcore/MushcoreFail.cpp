//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFail.cpp
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
//%Header } n8vxHRhqtLZcdhzaYr/aEA
/*
 * $Id: MushcoreFail.cpp,v 1.8 2006/06/01 15:39:43 southa Exp $
 * $Log: MushcoreFail.cpp,v $
 * Revision 1.8  2006/06/01 15:39:43  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.6  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.5  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:11  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/14 17:38:21  southa
 * Mustl web configuration
 *
 * Revision 1.2  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.1  2003/01/12 17:32:59  southa
 * Mushcore work
 *
 */

#include "MushcoreFail.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

// Most of the constructors here act as trigger functions

MushcoreFail::MushcoreFail(const string& inMessage) :
    m_message(inMessage)
{
}

const char * 
MushcoreFail::what() const throw()
{
    return m_message.c_str();
}

MushcoreFatalFail::MushcoreFatalFail(const string &inMessage) :
    MushcoreFail(inMessage)
{
}

MushcoreLogicFail::MushcoreLogicFail(const string &inMessage):
    MushcoreFatalFail(inMessage)
{
}

MushcoreResourceFail::MushcoreResourceFail(const string &inMessage):
    MushcoreFatalFail(inMessage)
{
}

MushcoreNonFatalFail::MushcoreNonFatalFail(const string &inMessage) :
    MushcoreFail(inMessage)
{
}

MushcoreCommandedExitFail::MushcoreCommandedExitFail(const string &inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}

MushcoreCommandFail::MushcoreCommandFail(const string &inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}

MushcoreDataFail::MushcoreDataFail(const string &inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}

MushcoreDeviceFail::MushcoreDeviceFail(const string &inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}

MushcoreFileFail::MushcoreFileFail(const string& inFilename, const string& inMessage) :
    MushcoreNonFatalFail(inMessage+" ("+inFilename+")")
{
}

MushcoreReferenceFail::MushcoreReferenceFail(const string &inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}

MushcoreRequestFail::MushcoreRequestFail(const string &inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}

MushcoreSyntaxFail::MushcoreSyntaxFail(const string &inMessage) :
    MushcoreNonFatalFail(inMessage)
{
}


