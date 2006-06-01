//%includeGuardStart {
#ifndef MUSTLCONFIGDEFBOOL_H
#define MUSTLCONFIGDEFBOOL_H
//%includeGuardStart } w36f6rY+ZnfHVf9NbtxwRQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefBool.h
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Lyt7h5waJbFN3uTWonHp0w
/*
 * $Id: MustlConfigDefBool.h,v 1.6 2005/05/19 13:02:18 southa Exp $
 * $Log: MustlConfigDefBool.h,v $
 * Revision 1.6  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
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
