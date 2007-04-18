//%includeGuardStart {
#ifndef INFERNALTILETRAITS_H
#define INFERNALTILETRAITS_H
//%includeGuardStart } 4aqDd2dpFjOe6dGqsFGMBg
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTileTraits.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 1fj2rsLArXtswNudysk3SQ
/*
 * $Id: InfernalTileTraits.h,v 1.5 2006/06/01 15:39:06 southa Exp $
 * $Log: InfernalTileTraits.h,v $
 * Revision 1.5  2006/06/01 15:39:06  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 15:32:12  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
 * Revision 1.22  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.21  2003/08/21 23:08:57  southa
 * Fixed file headers
 *
 * Revision 1.20  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.19  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
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

#include "InfernalTraits.h"

#include "mushGame.h"
#include "mushGL.h"


class InfernalTileTraits : public InfernalTraits
{
public:
    virtual ~InfernalTileTraits();
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

    typedef std::map<std::string, void (InfernalTileTraits::*)(MushcoreXML& inXML)> ElementFunctionMap;
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

inline std::ostream& operator<<(std::ostream &inOut, const InfernalTileTraits& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
