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
 * $Id: TesseractTrainerGame.h,v 1.1 2005/02/03 15:46:58 southa Exp $
 * $Log: TesseractTrainerGame.h,v $
 * Revision 1.1  2005/02/03 15:46:58  southa
 * Quaternion work
 *
 */

#include "mushMushcore.h"
#include "mushGame.h"
#include "mushGL.h"

#include "TesseractTrainerHypercube.h"
#include "TesseractTrainerHypersphere.h"

//:generate standard xml1 ostream
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
    
private:
    TesseractTrainerHypercube m_hypercube;
    TesseractTrainerHypersphere m_hypersphere;
    Mushware::tQValPair m_orientaton;

//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual TesseractTrainerGame *AutoClone(void) const;
    virtual TesseractTrainerGame *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } uwtJ7cbGh16AtQbbRliYrg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const TesseractTrainerGame& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } J9a4pcj4v7Z1RrYy6lz3BQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
