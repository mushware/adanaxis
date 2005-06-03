#ifndef MUSTLCONFIGDEFPASSWORD_H
#define MUSTLCONFIGDEFPASSWORD_H
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
 * $Id: MustlConfigDefPassword.h,v 1.1 2003/01/14 12:40:10 southa Exp $
 * $Log: MustlConfigDefPassword.h,v $
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

#endif
