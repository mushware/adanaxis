#ifndef MUSTLCONFIGDEFBOOL_H
#define MUSTLCONFIGDEFBOOL_H
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

// Boolean value displayed as checkbox
class MustlConfigDefBool : public MustlConfigDef
{
public:
    explicit MustlConfigDefBool(bool inValue);

    virtual ~MustlConfigDefBool();
    virtual const MushcoreScalar ValueGet(void) const;
    virtual void ValueSet(const MushcoreScalar& inValue);
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

    static MushcoreScalar MustlConfigBool(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
        bool m_value;
};
#endif
