//%includeGuardStart {
#ifndef MUSTLCONFIGDEFMENUSTRING_H
#define MUSTLCONFIGDEFMENUSTRING_H
//%includeGuardStart } fU0g6ilEAovZfCAubGA6wQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefMenuString.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 87sWeu/4n1/IS8FzP6JxCw
/*
 * $Id: MustlConfigDefMenuString.h,v 1.3 2003/08/21 23:09:22 southa Exp $
 * $Log: MustlConfigDefMenuString.h,v $
 * Revision 1.3  2003/08/21 23:09:22  southa
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

// String selected from a menu
class MustlConfigDefMenuString : public MustlConfigDefString
{
public:
    explicit MustlConfigDefMenuString(const std::string& inValue, const std::string& inMenu="");
    virtual ~MustlConfigDefMenuString();
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

    static MushcoreScalar MustlConfigMenuString(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    static void NullFunction(void);

private:
std::string m_menu;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
