#ifndef GAMEMOTION_H
#define GAMEMOTION_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameMotion.h,v 1.2 2002/08/07 13:36:50 southa Exp $
 * $Log: GameMotion.h,v $
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/23 14:10:47  southa
 * Added GameMotion
 *
 */

#include "mushCore.h"
#include "mushGL.h"

#include "GameMotionSpec.h"

class GameMotion : public CorePickle, protected CoreXMLHandler
{
public:
    virtual ~GameMotion() {}
    const GameMotionSpec& MotionSpecGet(void) const { return m_motionSpec; }
    void MotionSpecSet(const GameMotionSpec& inSpec) { m_motionSpec = inSpec; }

    void Render(void) const;

    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) {return "motion";}

protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleRectEnd(CoreXML& inXML);
    void HandlePositionEnd(CoreXML& inXML);
    void HandleDeltaEnd(CoreXML& inXML);
    void HandleMotionEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef map<string, void (GameMotion::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;

    GameMotionSpec m_motionSpec;
};
#endif
