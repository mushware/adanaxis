#ifndef MUSTLCONFIGDEFU32_H
#define MUSTLCONFIGDEFU32_H
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

// Unsigned integer input as text field
class MustlConfigDefU32 : public MustlConfigDef
{
public:
    MustlConfigDefU32(Mustl::U32 inValue, Mustl::U32 inLowLimit, Mustl::U32 inHighLimit);

    virtual ~MustlConfigDefU32();
    virtual const MushcoreScalar ValueGet(void) const;
    virtual void ValueSet(const MushcoreScalar& inValue );
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData);
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName);

    static MushcoreScalar MustlConfigUnsigned(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    Mustl::U32 m_value;
    Mustl::U32 m_lowLimit;
    Mustl::U32 m_highLimit;
};
#endif
