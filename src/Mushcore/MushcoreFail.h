#ifndef MUSHCOREFAIL_H
#define MUSHCOREFAIL_H
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
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"

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
    MushcoreFatalFail(const std::string& inMessage) :
    MushcoreFail(inMessage)
    {}
};

// Logical programming errors, similar to assert failures
class MushcoreLogicFail : public MushcoreFatalFail
{
public:
    MushcoreLogicFail(const std::string &inMessage) :
    MushcoreFatalFail(inMessage)
    {}
};

// Fatal resource failure
class MushcoreResourceFail : public MushcoreFatalFail
{
public:
    MushcoreResourceFail(const std::string &inMessage) :
    MushcoreFatalFail(inMessage)
    {}
};

// *********************************************
// Non-fatal errors - recovery might be possible
// *********************************************

class MushcoreNonFatalFail : public MushcoreFail
{
public:
    MushcoreNonFatalFail(const std::string& inMessage) :
    MushcoreFail(inMessage)
    {}
};

// A MushcoreCommand failed
class MushcoreCommandFail : public MushcoreNonFatalFail
{
public:
    MushcoreCommandFail(const std::string &inMessage) :
    MushcoreNonFatalFail(inMessage)
    {}
};

// A data item, expression or value failed
class MushcoreDataFail : public MushcoreNonFatalFail
{
public:
    MushcoreDataFail(const std::string &inMessage) :
    MushcoreNonFatalFail(inMessage)
    {}
};

// A device failed
class MushcoreDeviceFail : public MushcoreNonFatalFail
{
public:
    MushcoreDeviceFail(const std::string &inMessage) :
    MushcoreNonFatalFail(inMessage)
    {}
};

// All file-based failures
class MushcoreFileFail: public MushcoreNonFatalFail
{
public:
    MushcoreFileFail(const std::string& inFilename, const std::string& inMessage) :
        MushcoreNonFatalFail(inMessage+" ("+inFilename+")")
        {}
};

// A reference to or specifier of a data object failed
class MushcoreReferenceFail : public MushcoreNonFatalFail
{
public:
    MushcoreReferenceFail(const std::string &inMessage) :
        MushcoreNonFatalFail(inMessage)
        {}
};

// Syntax errors, including XML failures
class MushcoreSyntaxFail : public MushcoreNonFatalFail
{
public:
    MushcoreSyntaxFail(const std::string &inMessage) :
    MushcoreNonFatalFail(inMessage)
    {}
};

// Request failed.  Includes verification requests
class MushcoreRequestFail : public MushcoreNonFatalFail
{
public:
    MushcoreRequestFail(const std::string &inMessage) :
    MushcoreNonFatalFail(inMessage)
    {}
};

#endif
