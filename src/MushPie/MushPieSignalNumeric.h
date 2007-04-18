//%includeGuardStart {
#ifndef MUSHPIESIGNALNUMERIC_H
#define MUSHPIESIGNALNUMERIC_H
//%includeGuardStart } GfddsmMvUhs6Hi7kTC+NGA
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieSignalNumeric.h
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
//%Header } y1vXGP36o3DqHnKCOpC86g
/*
 * $Id: MushPieSignalNumeric.h,v 1.6 2006/06/01 15:39:37 southa Exp $
 * $Log: MushPieSignalNumeric.h,v $
 * Revision 1.6  2006/06/01 15:39:37  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/20 14:30:38  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:17  southa
 * Template fixes
 *
 * Revision 1.2  2005/02/03 21:03:06  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 */

#include "MushPieStandard.h"

#include "MushPieSignal.h"

//:generate virtual standard ostream xml1
class MushPieSignalNumeric : public MushPieSignal
{
public:
    MushPieSignalNumeric() : m_eventNumber(0) {}
    explicit MushPieSignalNumeric(Mushware::U32 inEventNumber) : m_eventNumber(inEventNumber) {}
    virtual ~MushPieSignalNumeric() {}
    
private:
    Mushware::U32 m_eventNumber; //:read
//%classPrototypes {
public:
    const Mushware::U32& EventNumber(void) const { return m_eventNumber; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } egGqU3I0I02Erbk8xb1a9A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPieSignalNumeric& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } woqyvkQc0XgwBloUTmMO1A
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
