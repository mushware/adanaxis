#ifndef GAMETILETRAITS_H
#define GAMETILETRAITS_H
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
 * $Id: GameTileTraits.h,v 1.14 2002/10/14 15:13:40 southa Exp $
 * $Log: GameTileTraits.h,v $
 * Revision 1.14  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.13  2002/10/14 13:03:00  southa
 * Display list test
 *
 * Revision 1.12  2002/10/10 22:47:58  southa
 * Full light definitions
 *
 * Revision 1.11  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 * Revision 1.10  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/18 15:13:16  southa
 * Adhesion handling
 *
 * Revision 1.8  2002/08/07 13:36:51  southa
 * Conditioned source
 *
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

#include "mushGL.h"
#include "GameTraits.h"
#include "GameGraphic.h"


class GameTileTraits : public GameTraits
{
public:
    virtual ~GameTileTraits();
    void Render(void);
    bool PermeabilityGet(tVal& outPermeability) const;
    bool AdhesionGet(tVal& outAdhesion) const;
    bool LightGet(GLLightDef& outLight) const;
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
    void HandleAdhesionEnd(CoreXML& inXML);
    void HandleLightStart(CoreXML& inXML);
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
    tVal m_adhesion;
    bool m_hasAdhesion;
    GLLightDef m_light;
    bool m_hasLight;
};

inline ostream& operator<<(ostream &inOut, const GameTileTraits& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
