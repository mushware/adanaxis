//%includeGuardStart {
#ifndef TESSERACTTRAINERGAME_H
#define TESSERACTTRAINERGAME_H
//%includeGuardStart } 9KogAsv7BlOFZlEAflixJg
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerGame.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } LlaQFXhrKwucd7Jrlj3s9g
/*
 * $Id: TesseractTrainerGame.h,v 1.5 2005/02/26 17:53:45 southa Exp $
 * $Log: TesseractTrainerGame.h,v $
 * Revision 1.5  2005/02/26 17:53:45  southa
 * Plane sets and pairs
 *
 * Revision 1.4  2005/02/13 22:44:08  southa
 * Tesseract stuff
 *
 * Revision 1.3  2005/02/10 12:34:20  southa
 * Template fixes
 *
 * Revision 1.2  2005/02/03 21:03:09  southa
 * Build fixes
 *
 * Revision 1.1  2005/02/03 15:46:58  southa
 * Quaternion work
 *
 */

#include "mushMushcore.h"
#include "mushGame.h"
#include "mushGL.h"

#include "TesseractTrainerHypercube.h"
#include "TesseractTrainerHypersphere.h"
#include "TesseractTrainerPlanePair.h"

//:generate virtual standard ostream xml1
class TesseractTrainerGame : public GameBase
{
public:
    TesseractTrainerGame();
    virtual ~TesseractTrainerGame();
    virtual void Process(GameAppHandler& inAppHandler);
    virtual void Display(GameAppHandler& inAppHandler);
    virtual void ScriptFunction(const std::string& inName, GameAppHandler& inAppHandler) const;
    virtual void SwapIn(GameAppHandler& inAppHandler);
    virtual void SwapOut(GameAppHandler& inAppHandler);
    
    static MushcoreScalar TesseractTrainerLoadGame(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
protected:
    void Reorientate(void);
    
private:
    TesseractTrainerHypercube m_hypercube; //:ignore
    TesseractTrainerHypersphere m_hypersphere; //:ignore
    TesseractTrainerPlanePair m_planepair; //:ignore
    Mushware::tQValPair m_orientation;
    Mushware::tQValPair m_angVel;
    std::vector<Mushware::t4GLVal> m_colours;
    Mushware::tVal m_lastChangeMsec;

//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } FwEN8XJox/Ejr30NeyHzCg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const TesseractTrainerGame& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Ne7gA9Ns8W1PJVMieMH/9A
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
