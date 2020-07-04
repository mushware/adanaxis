//%includeGuardStart {
#ifndef GAMERECORDS_H
#define GAMERECORDS_H
//%includeGuardStart } SUT8MQPOsiKcepqAIXksCw
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameRecords.h
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
//%Header } /aelfjHw3D0b+97Xkkv/Uw
/*
 * $Id: GameRecords.h,v 1.20 2006/06/01 15:38:59 southa Exp $
 * $Log: GameRecords.h,v $
 * Revision 1.20  2006/06/01 15:38:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.19  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.18  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.17  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.16  2003/10/04 18:12:13  southa
 * Readded
 *
 * Revision 1.14  2003/10/04 12:23:02  southa
 * File renaming
 *
 * Revision 1.13  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:53  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.10  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.9  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/11/24 23:18:24  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.5  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/24 10:52:47  southa
 * World records
 *
 * Revision 1.2  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.1  2002/08/19 21:42:38  southa
 * Display of records and lap/split times
 *
 */

#include "GameTimer.h"
#include "mushMushcore.h"

class GameRecords : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    GameRecords();

    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    void SplitTimeSet(Mushware::U32 inWhich, GameTimer::tMsec inMsec);
    void SplitTimePropose(Mushware::U32 inWhich, GameTimer::tMsec inMsec);
    GameTimer::tMsec SplitTimeGet(Mushware::U32 inWhich) const;
    bool SplitTimeValid(Mushware::U32 inWhich) const;
    void LapTimeSet(GameTimer::tMsec inMsec);
    void LapTimePropose(GameTimer::tMsec inMsec);
    GameTimer::tMsec LapTimeGet(void) const;
    bool LapTimeValid(void) const;
    void RaceTimeSet(GameTimer::tMsec inMsec);
    void RaceTimePropose(GameTimer::tMsec inMsec);
    GameTimer::tMsec RaceTimeGet(void) const;
    bool RaceTimeValid(void) const;
    bool RecordsPropose(const GameRecords& inRecords);
    void Reset(void);

protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleRecordsStart(MushcoreXML& inXML);
    void HandleSplitTimeEnd(MushcoreXML& inXML);
    void HandleLapTimeEnd(MushcoreXML& inXML);
    void HandleRaceTimeEnd(MushcoreXML& inXML);
    void HandleRecordsEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<std::string, void (GameRecords::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle
    
    std::vector<GameTimer::tMsec> m_splitTimes;
    std::vector<bool> m_splitTimeValid;
    GameTimer::tMsec m_lapTime;
    bool m_lapTimeValid;
    GameTimer::tMsec m_raceTime;
    bool m_raceTimeValid;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
