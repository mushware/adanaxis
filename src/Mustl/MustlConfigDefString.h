//%includeGuardStart {
#ifndef MUSTLCONFIGDEFSTRING_H
#define MUSTLCONFIGDEFSTRING_H
//%includeGuardStart } RAV4SQQySW8dGVJWN0x0oA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefString.h
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
//%Header } f9af2qq6MP1feHd08tm8fg
/*
 * $Id: MustlConfigDefString.h,v 1.3 2003/08/21 23:09:23 southa Exp $
 * $Log: MustlConfigDefString.h,v $
 * Revision 1.3  2003/08/21 23:09:23  southa
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
    static void NullFunction(void);

private:
std::string m_value;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
