//%includeGuardStart {
#ifndef TESSERACTTRAINERGAME_H
#define TESSERACTTRAINERGAME_H
//%includeGuardStart } 9KogAsv7BlOFZlEAflixJg
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerGame.h
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
//%Header } U1cXqMOosj3AC5lmbiib+Q
/*
 * $Id: TesseractTrainerGame.h,v 1.16 2006/05/11 10:43:18 southa Exp $
 * $Log: TesseractTrainerGame.h,v $
 * Revision 1.16  2006/05/11 10:43:18  southa
 * Project updates
 *
 * Revision 1.15  2005/06/20 14:30:39  southa
 * Adanaxis work
 *
 * Revision 1.14  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.13  2005/04/19 23:25:43  southa
 * Mode switching and recognition
 *
 * Revision 1.12  2005/04/19 19:23:14  southa
 * Save and load config
 *
 * Revision 1.11  2005/04/11 23:31:42  southa
 * Startup and registration screen
 *
 * Revision 1.10  2005/03/28 18:59:33  southa
 * Dialogues for Tesseract Trainer
 *
 * Revision 1.9  2005/03/25 22:04:50  southa
 * Dialogue and MushcoreIO fixes
 *
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

#include "TesseractTrainerConfig.h"
#include "TesseractTrainerHypercube.h"
#include "TesseractTrainerHypersphere.h"
#include "TesseractTrainerPlanePair.h"
#include "TesseractTrainerPlaneSet.h"

//:generate virtual standard ostream xml1 nocopy
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
    virtual void Init(GameAppHandler& inAppHandler);
    
    static MushcoreScalar TesseractTrainerLoadGame(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
protected:
    void Reorientate(void);
    void RenderView(GameAppHandler& inAppHandler, Mushware::tVal inStereo);
    void NamedDialoguesAdd(const std::string& inRegExp);
    bool RegCheck(void);
    
private:
    enum
    {
        kRegTimeMsec = 5*60*1000
    };
    bool m_inited; //:ignore
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
    Mushware::tVal m_lastRegCheckMsec;
    Mushware::tVal m_modeKeypressMsec;
    Mushware::U32 m_newMode;
    
    MushcoreData<GameDialogue> m_dialogues;
    
    TesseractTrainerConfig m_config;
    
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
operator<<(std::ostream& ioOut, const TesseractTrainerGame& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Ne7gA9Ns8W1PJVMieMH/9A
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
