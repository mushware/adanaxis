//%includeGuardStart {
#ifndef MUSTLCONFIGDEFPASSWORD_H
#define MUSTLCONFIGDEFPASSWORD_H
//%includeGuardStart } Yt9Q0GvDgG4ttZ4LjOM3iA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefPassword.h
 *
 * Copyright Andy Southgate 2002-2004
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } WuTaXpGuulfyudsH9E2MLg
/*
 * $Id: MustlConfigDefPassword.h,v 1.5 2003/10/04 12:44:36 southa Exp $
 * $Log: MustlConfigDefPassword.h,v $
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
