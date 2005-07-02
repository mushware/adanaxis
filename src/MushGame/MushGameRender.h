//%includeGuardStart {
#ifndef MUSHGAMERENDER_H
#define MUSHGAMERENDER_H
//%includeGuardStart } XiswxIPXAt8y2emYXbfSKw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameRender.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } 758vG5RYBv9QjPDnAkLDSw
/*
 * $Id: MushGameRender.h,v 1.1 2005/06/29 11:11:15 southa Exp $
 * $Log: MushGameRender.h,v $
 * Revision 1.1  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 */

#include "MushGameRender.h"

class MushGameCamera;
class MushGameLogic;

//:generate standard ostream xml1
class MushGameRender : public MushcoreVirtualObject
{
public:
    virtual ~MushGameRender() {}
    virtual void GroupingNameSet(const std::string& inName) { m_groupingName = inName; }

    virtual void FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera);
    
private:
    std::string m_groupingName; //:read

//%classPrototypes {
public:
    const std::string& GroupingName(void) const { return m_groupingName; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } LwveyIxAwfx75093rFgjKg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameRender& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Sfh3sa00ACUii0SCfVWg5g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
