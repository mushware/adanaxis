#ifndef MUSTLCONFIGDEFVAL_H
#define MUSTLCONFIGDEFVAL_H
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

// Floating point input as text field
class MustlConfigDefVal : public MustlConfigDef
{
public:
    MustlConfigDefVal(Mustl::tVal inValue, Mustl::tVal inLowLimit, Mustl::tVal inHighLimit);

    virtual ~MustlConfigDefVal();
    virtual const MushcoreScalar ValueGet(void) const;
    virtual void ValueSet(const MushcoreScalar& inValue );
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

    static MushcoreScalar MustlConfigFloat(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
Mustl::tVal m_value;
Mustl::tVal m_lowLimit;
Mustl::tVal m_highLimit;
};

#endif
