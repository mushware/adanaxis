//%includeGuardStart {
#ifndef MUSHPIEFORM_H
#define MUSHPIEFORM_H
//%includeGuardStart } chr+rdZQI8cOcPal/mrI9Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieForm.h
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
//%Header } ZcQFAMzkFCt5kxrBF4AW2g
/*
 * $Id: MushPieForm.h,v 1.6 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPieForm.h,v $
 * Revision 1.6  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:12  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/10 20:29:35  southa
 * Form and rendering work
 *
 * Revision 1.1  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 */

#include "MushPieStandard.h"

class MushPieSignal;

//:generate virtual standard ostream xml1
class MushPieForm : public MushcoreVirtualObject
{
public:
    typedef MushcoreData<MushPieForm, Mushware::U32> tData;
    typedef MushcoreDataRef<MushPieForm, Mushware::U32> tDataRef;
    
    MushPieForm() {}
    virtual ~MushPieForm() {}
    
    virtual void SignalHandle(const MushPieSignal& inSignal);
    virtual void WriteableSignalHandle(MushPieSignal& inSignal);
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPieForm& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } t8f6LLmjLkfX4mZD/ckOag
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
