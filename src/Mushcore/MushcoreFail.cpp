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
 * $Id: MushcoreFail.cpp,v 1.1 2003/01/12 17:32:59 southa Exp $
 * $Log: MushcoreFail.cpp,v $
 * Revision 1.1  2003/01/12 17:32:59  southa
 * Mushcore work
 *
 */

#include "MushcoreFail.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

MushcoreFail::MushcoreFail(const string& inMessage) :
    m_message(inMessage)
{
}

const char * 
MushcoreFail::what() const throw()
{
    return m_message.c_str();
}
