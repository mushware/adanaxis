//%includeGuardStart {
#ifndef GAMEREWARDS_H
#define GAMEREWARDS_H
//%includeGuardStart } X8QK/A4gGDCWC+ItBQXJ0w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameRewards.h
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
//%Header } 7hCYL0p5epy4ngfItJmuiw
/*
 * $Id: GameRewards.h,v 1.18 2006/06/01 15:38:59 southa Exp $
 * $Log: GameRewards.h,v $
 * Revision 1.18  2006/06/01 15:38:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.16  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.15  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.14  2003/10/04 18:12:13  southa
 * Readded
 *
 * Revision 1.12  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:08:53  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.9  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.8  2003/01/09 14:57:03  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.6  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/11/24 23:18:25  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.4  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.1  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 */

#include "mushMushcore.h"

class GameRewards : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    GameRewards(): m_lastTimeValid(false) {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    
    bool JudgementPass(Mushware::tVal inRatio);
    bool TimeCountdownPass(Mushware::tVal inTime);
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleJudgementEnd(MushcoreXML& inXML);
    void HandleTimedEnd(MushcoreXML& inXML);
    void HandleRewardsEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };
        
    typedef std::map<std::string, void (GameRewards::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle

    class TimeJudgement
    {
    public:
        Mushware::tVal ratio;
        std::string dialogueName;
    };

    class TimedCount
    {
    public:
        Mushware::tVal time;
        std::string dialogueName;
    };

    std::vector<TimeJudgement> m_judgements;
    std::vector<TimedCount> m_times;
    Mushware::tVal m_lastTime;
    Mushware::tVal m_lastTimeValid;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
