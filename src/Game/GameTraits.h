#ifndef GAMETRAITS_H
#define GAMETRAITS_H
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
 * $Id: GameTraits.h,v 1.10 2002/11/24 23:54:36 southa Exp $
 * $Log: GameTraits.h,v $
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

#include "mushCore.h"

class GameTraits : public CorePickle, protected CoreXMLHandler
{
public:
    GameTraits(): m_traitsValid(false) {}
    virtual ~GameTraits() {}
    void Verify(void);
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    
protected:
    U32 NumberOfTraitsGet(void) const;
    GameTraits& TraitsGet(U32 inIndex) const;
    const string TraitsNameGet(void) const;

    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);    
    
private:
    void NullHandler(CoreXML& inXML);
    void HandleBaseEnd(CoreXML& inXML);
    void HandleTraitsEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef map<string, void (GameTraits::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;

    void RebuildTraits(void) const;
        
    vector<string> m_baseNames;
    mutable string m_failMessage;
    mutable bool m_traitsValid;
    mutable vector<GameTraits *> m_baseTraits;
};

inline U32
GameTraits::NumberOfTraitsGet(void) const
{
    if (!m_traitsValid) RebuildTraits();
    return m_baseTraits.size();
}

inline GameTraits&
GameTraits::TraitsGet(U32 inIndex) const
{
    if (!m_traitsValid)
    {
        throw(LogicFail("Use of invalid traits"));
    }
    COREASSERT(inIndex < m_baseTraits.size());
    return *m_baseTraits[inIndex];
}

inline ostream& operator<<(ostream &inOut, const GameTraits& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}


#endif
