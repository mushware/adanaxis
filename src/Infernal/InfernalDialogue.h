//%includeGuardStart {
#ifndef INFERNALDIALOGUE_H
#define INFERNALDIALOGUE_H
//%includeGuardStart } z9cb2iqguhGreRKr9PsZPA
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalDialogue.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } NTlBsF8zSsqlWwKY37gwHQ
/*
 * $Id: InfernalDialogue.h,v 1.1 2003/10/04 15:32:10 southa Exp $
 * $Log: InfernalDialogue.h,v $
 * Revision 1.1  2003/10/04 15:32:10  southa
 * Module split
 *
 * Revision 1.19  2003/10/04 12:22:59  southa
 * File renaming
 *
 * Revision 1.18  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.17  2003/08/21 23:08:43  southa
 * Fixed file headers
 *
 * Revision 1.16  2003/02/05 17:06:36  southa
 * Build fixes
 *
 * Revision 1.15  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.14  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.12  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/24 23:18:16  southa
 * Added type name accessor to MushcorePickle
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
 * MushcoreData and MushcoreDatRef
 *
 * Revision 1.3  2002/08/13 18:29:04  southa
 * Tidied InfernalDialogue code
 *
 * Revision 1.2  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 * Revision 1.1  2002/08/09 17:09:04  southa
 * InfernalDialogue added
 *
 */

#include "InfernalMotion.h"
#include "Mushcore.h"
#include "mushGL.h"
#include "mushMedia.h"

class InfernalDialogue : public GLRenderable, public MushcorePickle, protected MushcoreXMLHandler
{
public:
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    virtual std::string TypeNameGet(void) {return "dialogue";}
    virtual void Render(void) const;
    virtual void Move(void);
    virtual GLRenderable *Clone(void) const { return new InfernalDialogue(*this); }
    virtual bool ExpiredGet(void) { return m_expired; }
    virtual void TextSet(Mushware::U32 inWhich, const std::string& inStr);
    virtual void ExpireNow();
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleTextEnd(MushcoreXML& inXML);
    void HandleStartColourEnd(MushcoreXML& inXML);
    void HandleMidColourEnd(MushcoreXML& inXML);
    void HandleEndColourEnd(MushcoreXML& inXML);
    void HandleSizesEnd(MushcoreXML& inXML);
    void HandleFontEnd(MushcoreXML& inXML);
    void HandleStartTimeEnd(MushcoreXML& inXML);
    void HandleEndTimeEnd(MushcoreXML& inXML);
    void HandleFadeTimeEnd(MushcoreXML& inXML);
    void HandleMotionStart(MushcoreXML& inXML);
    void HandleSoundEnd(MushcoreXML& inXML);
    void HandleKillSoundEnd(MushcoreXML& inXML);
    void HandleSoundStreamEnd(MushcoreXML& inXML);
    void HandleDialogueEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<std::string, void (InfernalDialogue::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    // End of pickle

    class StringSpec
    {
    public:
        GLString string;
        InfernalMotionSpec motionSpec;
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
        std::string name;
        Mushware::tVal startTime;
    };

    class SoundSpec
    {
    public:
        MushcoreDataRef<MediaSound> soundRef;
        Mushware::tVal startTime;
    };

    class SoundStreamSpec
    {
    public:
        MushcoreDataRef<MediaSoundStream> soundStreamRef;
        Mushware::U32 loop;
        Mushware::tVal startTime;
    };

    StringSpec m_currentSpec;
    std::vector<StringSpec> m_strings;
    std::vector<SoundSpec> m_sounds;
    std::vector<SoundStreamSpec> m_soundStreams;
    GLFontRef m_fontRef;
    InfernalMotion m_motion;
    std::string m_killSound;
    Mushware::tVal m_age;
    bool m_expired;
//    MushcoreScript m_script;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
