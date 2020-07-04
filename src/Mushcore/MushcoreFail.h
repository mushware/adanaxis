//%includeGuardStart {
#ifndef MUSHCOREFAIL_H
#define MUSHCOREFAIL_H
//%includeGuardStart } 8X8UXHE1XKehSv0Twn8MDQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFail.h
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
//%Header } LwHorU3NxWZYYh2Ou+JuWQ
/*
 * $Id: MushcoreFail.h,v 1.10 2006/06/01 15:39:43 southa Exp $
 * $Log: MushcoreFail.h,v $
 * Revision 1.10  2006/06/01 15:39:43  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/06/20 14:30:38  southa
 * Adanaxis work
 *
 * Revision 1.8  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.6  2003/10/19 15:59:34  southa
 * Edge manipulation
 *
 * Revision 1.5  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:11  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/17 13:30:40  southa
 * Source conditioning and build fixes
 *
 * Revision 1.2  2003/01/14 17:38:21  southa
 * Mustl web configuration
 *
 * Revision 1.1  2003/01/12 17:32:59  southa
 * Mushcore work
 *
 */

// This file does not include MustlStandard.h, and is available to clients
// which want to generate Mushcore exceptions without #including #Mushcore.h itself

#include <stdexcept>
#include <string>

// Base class for all Mushware exceptions
class MushcoreFail : public std::exception
{
public:
    virtual ~MushcoreFail() throw() {}
    virtual const char *what() const throw();
    
protected:
    explicit MushcoreFail(const std::string& inMessage); // Allow Instantiation of subclasses only

private:
    std::string m_message;
};

// *******************************************
// Fatal errors - program should probably halt
// *******************************************

class MushcoreFatalFail : public MushcoreFail
{
public:
    MushcoreFatalFail(const std::string& inMessage);
};

// Logical programming errors, similar to assert failures
class MushcoreLogicFail : public MushcoreFatalFail
{
public:
    MushcoreLogicFail(const std::string &inMessage);
};

// Fatal resource failure
class MushcoreResourceFail : public MushcoreFatalFail
{
public:
    MushcoreResourceFail(const std::string &inMessage);
};

// *********************************************
// Non-fatal errors - recovery might be possible
// *********************************************

class MushcoreNonFatalFail : public MushcoreFail
{
public:
    MushcoreNonFatalFail(const std::string& inMessage);
};

// A MushcoreCommand failed
class MushcoreCommandFail : public MushcoreNonFatalFail
{
public:
    MushcoreCommandFail(const std::string &inMessage);
};

// A data item, expression or value failed
class MushcoreDataFail : public MushcoreNonFatalFail
{
public:
    MushcoreDataFail(const std::string &inMessage);
};

// A device failed
class MushcoreDeviceFail : public MushcoreNonFatalFail
{
public:
    MushcoreDeviceFail(const std::string &inMessage);
};

// All file-based failures
class MushcoreFileFail: public MushcoreNonFatalFail
{
public:
    MushcoreFileFail(const std::string& inFilename, const std::string& inMessage);
};

// A reference to or specifier of a data object failed
class MushcoreReferenceFail : public MushcoreNonFatalFail
{
public:
    MushcoreReferenceFail(const std::string &inMessage);
};

// Request failed.  Includes verification requests
class MushcoreRequestFail : public MushcoreNonFatalFail
{
public:
    MushcoreRequestFail(const std::string &inMessage);
};

// Syntax errors, including XML failures
class MushcoreSyntaxFail : public MushcoreNonFatalFail
{
public:
    MushcoreSyntaxFail(const std::string &inMessage);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
