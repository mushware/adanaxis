/*
 * $Id: GameDialogue.h,v 1.2 2002/08/10 12:34:48 southa Exp $
 * $Log: GameDialogue.h,v $
 * Revision 1.2  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 * Revision 1.1  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 */

#include "mushCore.h"
#include "mushGL.h"
#include "GameMotion.h"

class GameDialogue : public GLRenderable, public CorePickle, protected CoreXMLHandler
{
public:
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) {return "dialogue";}
    virtual void Render(void) const;
    virtual void Move(void);
    virtual GLRenderable *Clone(void) const { return new GameDialogue(*this); }
    virtual bool ExpiredGet(void) { return m_expired; }
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:

    void NullHandler(CoreXML& inXML);
    void HandleTextEnd(CoreXML& inXML);
    void HandleStartColourEnd(CoreXML& inXML);
    void HandleMidColourEnd(CoreXML& inXML);
    void HandleEndColourEnd(CoreXML& inXML);
    void HandleSizesEnd(CoreXML& inXML);
    void HandleFontEnd(CoreXML& inXML);
    void HandleStartTimeEnd(CoreXML& inXML);
    void HandleEndTimeEnd(CoreXML& inXML);
    void HandleFadeTimeEnd(CoreXML& inXML);
    void HandleMotionStart(CoreXML& inXML);
    void HandleDialogueEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef map<string, void (GameDialogue::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle

    class StringSpec
    {
    public:
        GLString string;
        GameMotionSpec motionSpec;
        GLColour startColour;
        GLColour midColour;
        GLColour endColour;
        tVal startTime;
        tVal endTime;
        tVal fadeTime;
        tVal startSize;
        tVal midSize;
        tVal endSize;
    };

    StringSpec m_currentSpec;
    vector<StringSpec> m_specs;
    GLFontRef m_fontRef;
    GameMotion m_motion;
    tVal m_age;
    bool m_expired;
};
