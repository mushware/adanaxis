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
 * $Id: TesseractTrainerGame.h,v 1.8 2005/03/13 00:34:48 southa Exp $
 * $Log: TesseractTrainerGame.h,v $
 * Revision 1.8  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.7  2005/03/08 01:24:10  southa
 * Quaternion slerp between orientations
 *
 * Revision 1.6  2005/02/27 01:01:32  southa
 * Eigenplane markers
 *
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
#include "TesseractTrainerPlaneSet.h"

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
    void RenderView(GameAppHandler& inAppHandler, Mushware::tVal inStereo);
    
private:
    TesseractTrainerHypercube m_hypercube; //:ignore
    TesseractTrainerHypersphere m_hypersphere; //:ignore
    TesseractTrainerPlanePair m_planepair; //:ignore
    TesseractTrainerPlaneSet m_planeset; //:ignore
    std::vector<Mushware::tQValPair> m_orientations;
    std::vector<Mushware::tQValPair> m_angVels;
    Mushware::U32 m_current;
    Mushware::U32 m_previous;
    std::vector<Mushware::t4GLVal> m_colours;
    Mushware::tVal m_lastChangeMsec;
    
    MushcoreData<GameDialogue> m_dialogues;
    
    Mushware::tVal m_ttRotationChangeMsec;
    Mushware::tVal m_ttRealignMsec;
    Mushware::tVal m_ttLineWidth;
    Mushware::tVal m_ttPointSize;
    Mushware::tVal m_ttObjectDistance;

    Mushware::U32 m_ttRenderFaces;
    bool m_ttRenderFaceOutlines;
    bool m_ttRenderFaceTextures;
    bool m_ttRenderFacePoints;
    bool m_ttRenderRotationPlanes;
    bool m_ttRenderBasicPlanes;
    bool m_ttRenderStereo;
    Mushware::tVal m_ttStereoEyeSeparation;
    Mushware::tVal m_ttStereoImageSeparation;
    
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
