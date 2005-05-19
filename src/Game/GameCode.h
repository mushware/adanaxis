//%includeGuardStart {
#ifndef GAMECODE_H
#define GAMECODE_H
//%includeGuardStart } pCjxWkBzU0f8Yj5V0a9Leg
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameCode.h
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
//%Header } GLiSUgquXCKOJW/VVo02MQ
/*
 * $Id: GameCode.h,v 1.1 2005/04/11 23:31:41 southa Exp $
 * $Log: GameCode.h,v $
 * Revision 1.1  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 */

#include "mushMushcore.h"

//:generate virtual standard basic ostream xml1
class GameCode : public MushcoreVirtualObject
{
public:
    virtual ~GameCode() {}

    std::string Code(void) const;
    void CodeSet(const std::string& inStr);
private:
    std::string m_code;
    std::string m_crypt;
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const GameCode& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } VPSrEZ+WP4qVJ9wr13QTQg
};
//%inlineHeader {

inline bool
operator==(const GameCode& inA, const GameCode& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const GameCode& inA, const GameCode& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const GameCode& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } S8VhOtJSQWpUI67tpNyIrg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
