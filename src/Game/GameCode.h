//%includeGuardStart {
#ifndef GAMECODE_H
#define GAMECODE_H
//%includeGuardStart } pCjxWkBzU0f8Yj5V0a9Leg
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameCode.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 0feoAns5ywCDzpsxFDC5Dg
/*
 * $Id$
 * $Log$
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
