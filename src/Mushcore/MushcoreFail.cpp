//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFail.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } mqj0VSm1Z/7KBGIMhopetA
/*
 * $Id: MushcoreFail.cpp,v 1.6 2004/01/02 21:13:12 southa Exp $
 * $Log: MushcoreFail.cpp,v $
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


