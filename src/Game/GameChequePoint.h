#ifndef GAMECHEQUEPOINT_H
#define GAMECHEQUEPOINT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameChequePoint.h,v 1.9 2003/01/09 14:56:59 southa Exp $
 * $Log: GameChequePoint.h,v $
 * Revision 1.9  2003/01/09 14:56:59  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.7  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/11/24 23:18:05  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.5  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/21 10:12:21  southa
 * Time down counter
 *
 * Revision 1.2  2002/08/20 11:43:25  southa
 * GameRewards added
 *
 * Revision 1.1  2002/08/18 20:44:33  southa
 * Initial chequepoint work
 *
 */

#include "Mushcore.h"

class GameEventStandingOn;

class GameChequePoint : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    virtual ~GameChequePoint() {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    Mushware::U32 SequenceGet(void) { return m_sequence; }
    Mushware::tVal ParTimeGet(void) { return m_parTime; }
    Mushware::tVal AddTimeGet(void) { return m_addTime; }
    void StandingOnHandler(const GameEventStandingOn& inEvent);
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void Triggered(void);
    
    void HandleSequenceEnd(MushcoreXML& inXML);
    void HandleMapValueEnd(MushcoreXML& inXML);
    void HandleActionEnd(MushcoreXML& inXML);
    void HandleParTimeEnd(MushcoreXML& inXML);
    void HandleAddTimeEnd(MushcoreXML& inXML);
    void HandleChequePointEnd(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<string, void (GameChequePoint::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;

    Mushware::U32 m_sequence;
    std::vector<U32> m_mapValues;
    std::string m_action;
    Mushware::tVal m_parTime;
    Mushware::tVal m_addTime;
};

inline std::ostream& operator<<(std::ostream &inOut, const GameChequePoint& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
