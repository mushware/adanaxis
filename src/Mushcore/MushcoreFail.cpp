/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MushcoreFail.cpp,v 1.3 2003/01/14 17:38:21 southa Exp $
 * $Log: MushcoreFail.cpp,v $
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


