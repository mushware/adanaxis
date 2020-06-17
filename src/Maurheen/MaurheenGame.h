//%includeGuardStart {
#ifndef MAURHEENGAME_H
#define MAURHEENGAME_H
//%includeGuardStart } PJDNvu01wwB43OSvfrDDlA
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenGame.h
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
//%Header } 5YsxotJBRRDRptr9QmOEEg
/*
 * $Id: MaurheenGame.h,v 1.7 2006/06/01 15:39:11 southa Exp $
 * $Log: MaurheenGame.h,v $
 * Revision 1.7  2006/06/01 15:39:11  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/10 12:34:02  southa
 * Template fixes
 *
 * Revision 1.3  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 * Revision 1.2  2004/03/07 12:05:56  southa
 * Rendering work
 *
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
 */

#include "mushMushcore.h"
#include "mushGame.h"
#include "mushGL.h"

#include "MaurheenHypercube.h"
#include "MaurheenHypersphere.h"

//:generate virtual standard xml1 ostream
class MaurheenGame : public GameBase
{
public:
    MaurheenGame();
    virtual ~MaurheenGame();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);
    
    static MushcoreScalar MaurheenLoadGame(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
protected:
    
private:
    MaurheenHypercube m_hypercube; //:ignore
    MaurheenHypersphere m_hypersphere; //:ignore

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
operator<<(std::ostream& ioOut, const MaurheenGame& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } J9a4pcj4v7Z1RrYy6lz3BQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
