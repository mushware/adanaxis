#ifndef MUSTLCONFIGDEFMENUSTRING_H
#define MUSTLCONFIGDEFMENUSTRING_H
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
 * $Id: MustlConfigDefMenuString.h,v 1.1 2003/01/14 12:40:10 southa Exp $
 * $Log: MustlConfigDefMenuString.h,v $
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

#endif