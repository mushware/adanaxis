//%includeGuardStart {
#ifndef MUSTLCONFIGDEFU32_H
#define MUSTLCONFIGDEFU32_H
//%includeGuardStart } Aoz/Z46x7W98zJP70GPGdQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlConfigDefU32.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } 7h2+VvUnT8WqHj0EV3tLyQ
/*
 * $Id: MustlConfigDefU32.h,v 1.7 2006/06/01 15:39:51 southa Exp $
 * $Log: MustlConfigDefU32.h,v $
 * Revision 1.7  2006/06/01 15:39:51  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:14  southa
 * Source conditioning
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
 * Revision 1.1  2003/01/14 12:40:11  southa
 * Moved ConfigDefs into Mustl
 *
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
    static void NullFunction(void);

private:
    Mustl::U32 m_value;
    Mustl::U32 m_lowLimit;
    Mustl::U32 m_highLimit;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
