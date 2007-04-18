//%includeGuardStart {
#ifndef MAURHEENGAME_H
#define MAURHEENGAME_H
//%includeGuardStart } PJDNvu01wwB43OSvfrDDlA
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenGame.h
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
//%Header } iRYtUfghvqSGlSCpYzfNyw
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
