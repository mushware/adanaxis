#ifndef GAMEDIALOGUE_H
#define GAMEDIALOGUE_H
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
 * $Id: GameDialogue.h,v 1.11 2002/11/24 23:18:16 southa Exp $
 * $Log: GameDialogue.h,v $
 * Revision 1.11  2002/11/24 23:18:16  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.10  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/26 12:44:37  southa
 * Timed rewards and sound tweaks
 *
 * Revision 1.7  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.6  2002/08/19 22:18:36  southa
 * Display of time differences
 *
 * Revision 1.5  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.4  2002/08/15 13:39:31  southa
 * CoreData and CoreDatRef
 *
 * Revision 1.3  2002/08/13 18:29:04  southa
 * Tidied GameDialogue code
 *
 * Revision 1.2  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 * Revision 1.1  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 */

#include "GameMotion.h"
#include "mushCore.h"
#include "mushGL.h"
#include "mushMedia.h"

class GameDialogue : public GLRenderable, public CorePickle, protected CoreXMLHandler
{
public:
    virtual void Pickle(std::ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    virtual string TypeNameGet(void) {return "dialogue";}
    virtual void Render(void) const;
    virtual void Move(void);
    virtual GLRenderable *Clone(void) const { return new GameDialogue(*this); }
    virtual bool ExpiredGet(void) { return m_expired; }
    virtual void TextSet(Mushware::U32 inWhich, const string& inStr);
    virtual void ExpireNow();
    
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
    void HandleSoundEnd(CoreXML& inXML);
    void HandleKillSoundEnd(CoreXML& inXML);
    void HandleSoundStreamEnd(CoreXML& inXML);
    void HandleDialogueEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<string, void (GameDialogue::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
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
        Mushware::tVal startTime;
        Mushware::tVal endTime;
        Mushware::tVal fadeTime;
        Mushware::tVal startSize;
        Mushware::tVal midSize;
        Mushware::tVal endSize;
    };

    class FunctionSpec
    {
    public:
        string name;
        Mushware::tVal startTime;
    };

    class SoundSpec
    {
    public:
        CoreDataRef<MediaSound> soundRef;
        Mushware::tVal startTime;
    };

    class SoundStreamSpec
    {
    public:
        CoreDataRef<MediaSoundStream> soundStreamRef;
        Mushware::U32 loop;
        Mushware::tVal startTime;
    };

    StringSpec m_currentSpec;
    std::vector<StringSpec> m_strings;
    std::vector<SoundSpec> m_sounds;
    std::vector<SoundStreamSpec> m_soundStreams;
    GLFontRef m_fontRef;
    GameMotion m_motion;
    string m_killSound;
    Mushware::tVal m_age;
    bool m_expired;
//    CoreScript m_script;
};
#endif
