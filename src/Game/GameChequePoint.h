#ifndef GAMECHEQUEPOINT_H
#define GAMECHEQUEPOINT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameChequePoint.h,v 1.5 2002/10/22 20:42:02 southa Exp $
 * $Log: GameChequePoint.h,v $
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

#include "mushCore.h"

class GameEventStandingOn;

class GameChequePoint : public CorePickle, protected CoreXMLHandler
{
public:
    virtual ~GameChequePoint() {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    U32 SequenceGet(void) { return m_sequence; }
    tVal ParTimeGet(void) { return m_parTime; }
    tVal AddTimeGet(void) { return m_addTime; }
    void StandingOnHandler(const GameEventStandingOn& inEvent);
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void Triggered(void);
    
    void HandleSequenceEnd(CoreXML& inXML);
    void HandleMapValueEnd(CoreXML& inXML);
    void HandleActionEnd(CoreXML& inXML);
    void HandleParTimeEnd(CoreXML& inXML);
    void HandleAddTimeEnd(CoreXML& inXML);
    void HandleChequePointEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef map<string, void (GameChequePoint::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;

    U32 m_sequence;
    vector<U32> m_mapValues;
    string m_action;
    tVal m_parTime;
    tVal m_addTime;
};

inline ostream& operator<<(ostream &inOut, const GameChequePoint& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
