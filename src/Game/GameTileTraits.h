#ifndef GAMETILETRAITS_H
#define GAMETILETRAITS_H
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
 * $Id: GameTileTraits.h,v 1.18 2002/12/29 20:30:54 southa Exp $
 * $Log: GameTileTraits.h,v $
 * Revision 1.18  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.17  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.16  2002/11/24 23:18:25  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.15  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.14  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.13  2002/10/14 13:03:00  southa
 * Display std::list test
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

#include "GameGraphic.h"
#include "GameTraits.h"
#include "mushGL.h"


class GameTileTraits : public GameTraits
{
public:
    virtual ~GameTileTraits();
    void Render(void);
    bool PermeabilityGet(Mushware::tVal& outPermeability) const;
    bool AdhesionGet(Mushware::tVal& outAdhesion) const;
    bool LightGet(GLLightDef& outLight) const;
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
protected:
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleGraphicStart(MushcoreXML& inXML);
    void HandlePermeabilityEnd(MushcoreXML& inXML);
    void HandleAdhesionEnd(MushcoreXML& inXML);
    void HandleLightStart(MushcoreXML& inXML);
    void HandleTraitsEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef std::map<string, void (GameTileTraits::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    Mushware::U32 m_baseThreaded;
    
    std::vector <GameGraphic *> m_graphics;
    Mushware::tVal m_permeability;
    bool m_hasPermeability;
    Mushware::tVal m_adhesion;
    bool m_hasAdhesion;
    GLLightDef m_light;
    bool m_hasLight;
};

inline std::ostream& operator<<(std::ostream &inOut, const GameTileTraits& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
