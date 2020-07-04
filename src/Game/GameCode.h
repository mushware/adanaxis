//%includeGuardStart {
#ifndef GAMECODE_H
#define GAMECODE_H
//%includeGuardStart } pCjxWkBzU0f8Yj5V0a9Leg
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameCode.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } i+tSHq6Dt0rIaCUAzXRcoQ
/*
 * $Id: GameCode.h,v 1.4 2006/06/01 15:38:56 southa Exp $
 * $Log: GameCode.h,v $
 * Revision 1.4  2006/06/01 15:38:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:02:01  southa
 * Mac release work
 *
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const GameCode& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } K8CLjRgN1XOmuCfQNz5rfQ
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
