#ifndef GAMETRAITS_H
#define GAMETRAITS_H
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
 * $Id: GameTraits.h,v 1.16 2003/01/11 17:07:52 southa Exp $
 * $Log: GameTraits.h,v $
 * Revision 1.16  2003/01/11 17:07:52  southa
 * Mushcore library separation
 *
 * Revision 1.15  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.14  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.12  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.10  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
 * Revision 1.9  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.8  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.7  2002/08/27 08:56:27  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/08 14:22:03  southa
 * Rotated desks
 *
 * Revision 1.4  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.1  2002/06/04 14:12:26  southa
 * Traits loader first stage
 *
 */

#include "Mushcore.h"

class GameTraits : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    GameTraits(): m_traitsValid(false) {}
    virtual ~GameTraits() {}
    void Verify(void);
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    
protected:
    Mushware::U32 NumberOfTraitsGet(void) const;
    GameTraits& TraitsGet(Mushware::U32 inIndex) const;
    const std::string TraitsNameGet(void) const;

    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);    
    
private:
    void NullHandler(MushcoreXML& inXML);
    void HandleBaseEnd(MushcoreXML& inXML);
    void HandleTraitsEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<string, void (GameTraits::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;

    void RebuildTraits(void) const;
        
    std::vector<string> m_baseNames;
    mutable std::string m_failMessage;
    mutable bool m_traitsValid;
    mutable std::vector<GameTraits *> m_baseTraits;
};

inline Mushware::U32
GameTraits::NumberOfTraitsGet(void) const
{
    if (!m_traitsValid) RebuildTraits();
    return m_baseTraits.size();
}

inline GameTraits&
GameTraits::TraitsGet(Mushware::U32 inIndex) const
{
    if (!m_traitsValid)
    {
        throw(MushcoreLogicFail("Use of invalid traits"));
    }
    MUSHCOREASSERT(inIndex < m_baseTraits.size());
    return *m_baseTraits[inIndex];
}

inline std::ostream& operator<<(std::ostream &inOut, const GameTraits& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}


#endif
