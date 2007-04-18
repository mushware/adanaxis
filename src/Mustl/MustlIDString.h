//%includeGuardStart {
#ifndef MUSTLIDSTRING_H
#define MUSTLIDSTRING_H
//%includeGuardStart } ZHIE4rhi6rfNBTIYMoc0Nw
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlIDString.h
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
//%Header } qIVUdOQz22NMFIpY//AumA
/*
 * $Id: MustlIDString.h,v 1.9 2006/06/01 15:39:52 southa Exp $
 * $Log: MustlIDString.h,v $
 * Revision 1.9  2006/06/01 15:39:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:26  southa
 * Fixed file headers
 *
 * Revision 1.4  2002/12/29 20:30:56  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlID.h"

class MustlData;

class MustlIDString : public MustlID
{
public:
    explicit MustlIDString(const std::string& inName) : m_name(inName) {}
    explicit MustlIDString(MustlData& ioData);
    virtual ~MustlIDString();
    virtual MustlID *Clone(void) const;
    virtual void Pack(MustlData& ioData) const;
    virtual void Unpack(MustlData& ioData);
    virtual void Print(std::ostream& ioOut) const;

private:
    std::string m_name;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
