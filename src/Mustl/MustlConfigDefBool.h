//%includeGuardStart {
#ifndef MUSTLCONFIGDEFBOOL_H
#define MUSTLCONFIGDEFBOOL_H
//%includeGuardStart } w36f6rY+ZnfHVf9NbtxwRQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefBool.h
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
//%Header } uzNkDpmMmUbP2efBth/2fg
/*
 * $Id: MustlConfigDefBool.h,v 1.3 2003/08/21 23:09:22 southa Exp $
 * $Log: MustlConfigDefBool.h,v $
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
    static void NullFunction(void);

private:
        bool m_value;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
