#ifndef MUSTLCONFIGDEFSTRING_H
#define MUSTLCONFIGDEFSTRING_H
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

#include "MustlConfigDef.h"
#include "MustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

// String input as text field
class MustlConfigDefString : public MustlConfigDef
{
public:
    explicit MustlConfigDefString(const std::string& inValue);
    virtual ~MustlConfigDefString();

    virtual const MushcoreScalar ValueGet(void) const;
    virtual void ValueSet(const MushcoreScalar& inValue);
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

    static MushcoreScalar MustlConfigString(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
std::string m_value;
};

#endif
