//%includeGuardStart {
#ifndef MUSTLCONFIGDEFVAL_H
#define MUSTLCONFIGDEFVAL_H
//%includeGuardStart } W9HYr3SP2UPdI0+/Fk7yug
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefVal.h
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
//%Header } 37TLwPtMjFjqzaby0HFkeQ
/*
 * $Id: MustlConfigDefVal.h,v 1.3 2003/08/21 23:09:24 southa Exp $
 * $Log: MustlConfigDefVal.h,v $
 * Revision 1.3  2003/08/21 23:09:24  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.1  2003/01/14 12:40:11  southa
 * Moved ConfigDefs into Mustl
 *
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
    static void NullFunction(void);

private:
    Mustl::tVal m_value;
    Mustl::tVal m_lowLimit;
    Mustl::tVal m_highLimit;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
