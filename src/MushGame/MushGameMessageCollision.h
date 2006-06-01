//%includeGuardStart {
#ifndef MUSHGAMEMESSAGECOLLISION_H
#define MUSHGAMEMESSAGECOLLISION_H
//%includeGuardStart } QPQrOeEYWhDLCHjfAmk7Gg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageCollision.h
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
//%Header } IoZErpHTPH1ESqVhq+g9og
/*
 * $Id: MushGameMessageCollision.h,v 1.1 2005/08/01 13:09:58 southa Exp $
 * $Log: MushGameMessageCollision.h,v $
 * Revision 1.1  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageCollision : public MushGameMessage
{
public:
    explicit MushGameMessageCollision(const std::string& inID = "") :
        MushGameMessage(inID)
    {}

private:
    std::string m_objectName1; //:readwrite
    std::string m_objectName2; //:readwrite
    
//%classPrototypes {
public:
    const std::string& ObjectName1(void) const { return m_objectName1; }
    void ObjectName1Set(const std::string& inValue) { m_objectName1=inValue; }
    const std::string& ObjectName2(void) const { return m_objectName2; }
    void ObjectName2Set(const std::string& inValue) { m_objectName2=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } /hQHOIrqK2QxgkAgwJRPTQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageCollision& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 7rke0whDQgrG8sneg+XDNw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
