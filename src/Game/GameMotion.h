/*
 * $Id$
 * $Log$
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
