#ifndef GAMETILETRAITS_H
#define GAMETILETRAITS_H
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
 * $Id: GameTileTraits.h,v 1.7 2002/07/16 17:48:09 southa Exp $
 * $Log: GameTileTraits.h,v $
 * Revision 1.7  2002/07/16 17:48:09  southa
 * Collision and optimisation work
 *
 * Revision 1.6  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 * Revision 1.3  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.2  2002/06/04 17:02:11  southa
 * More work
 *
 * Revision 1.1  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 */

#include "GameTraits.h"
#include "GameGraphic.h"

class GameTileTraits : public GameTraits
{
public:
    virtual ~GameTileTraits();
    void Render(void);
    bool PermeabilityGet(tVal& outPermeability) const;
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) {return "tile";}

protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleGraphicStart(CoreXML& inXML);
    void HandlePermeabilityEnd(CoreXML& inXML);
    void HandleTraitsEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef map<string, void (GameTileTraits::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    U32 m_baseThreaded;
    
    vector <GameGraphic *> m_graphics;
    tVal m_permeability;
    bool m_hasPermeability;
};

inline ostream& operator<<(ostream &inOut, const GameTileTraits& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
