//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFail.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 9FNcVfXAunweEDAMePP1NA
/*
 * $Id: MushcoreFail.cpp,v 1.4 2003/08/21 23:09:11 southa Exp $
 * $Log: MushcoreFail.cpp,v $
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


