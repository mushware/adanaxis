//%includeGuardStart {
#ifndef INFERNALFLOORMAP_H
#define INFERNALFLOORMAP_H
//%includeGuardStart } 2tBobbUViMTONTr99BFE8A
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalFloorMap.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Bkr/gtLL1h73xcqACjA34A
/*
 * $Id: InfernalFloorMap.h,v 1.31 2003/09/17 19:40:32 southa Exp $
 * $Log: InfernalFloorMap.h,v $
 * Revision 1.31  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.30  2003/08/21 23:08:45  southa
 * Fixed file headers
 *
 * Revision 1.29  2003/02/05 17:06:36  southa
 * Build fixes
 *
 * Revision 1.28  2003/01/12 17:32:54  southa
 * Mushcore work
 *
 * Revision 1.27  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.26  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.25  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.24  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.23  2002/11/24 23:18:16  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.22  2002/11/18 11:31:14  southa
 * Return to game mode
 *
 * Revision 1.21  2002/10/22 20:42:04  southa
 * Source conditioning
 *
 * Revision 1.20  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.19  2002/10/11 14:01:12  southa
 * Lighting work
 *
 * Revision 1.18  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 * Revision 1.17  2002/10/08 17:13:18  southa
 * Tiered maps
 *
 * Revision 1.16  2002/10/07 17:49:46  southa
 * Multiple values per std::map element
 *
 * Revision 1.15  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.14  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 * Revision 1.13  2002/08/18 15:13:15  southa
 * Adhesion handling
 *
 * Revision 1.12  2002/08/17 10:41:51  southa
 * Designer fixes
 *
 * Revision 1.11  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.10  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 * Revision 1.9  2002/07/16 19:30:09  southa
 * Simplistic collision checking
 *
 * Revision 1.8  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 * Revision 1.7  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.6  2002/07/02 18:36:56  southa
 * Selection in designer, mouse buttons
 *
 * Revision 1.5  2002/07/02 14:27:10  southa
 * First floor std::map designer build
 *
 * Revision 1.4  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.2  2002/06/04 14:12:26  southa
 * Traits loader first stage
 *
 * Revision 1.1  2002/05/30 16:21:53  southa
 * Pickleable InfernalContract
 *
 * Revision 1.5  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.4  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.3  2002/05/26 16:08:49  southa
 * MushcoreXML loader
 *
 * Revision 1.2  2002/05/25 17:16:15  southa
 * MushcoreXML implementation
 *
 * Revision 1.1  2002/05/24 18:08:35  southa
 * MushcoreXML and game map
 *
 */

#include "InfernalLightLinks.h"
#include "InfernalMap.h"
#include "InfernalSolidMap.h"
#include "Mushcore.h"
#include "mushGL.h"

class InfernalTileMap;
class InfernalMapArea;
class InfernalMapPoint;

class InfernalFloorMap : public MushcorePickle, private MushcoreXMLHandler
{
public:

    typedef Mushware::U32 tMapValue;
    typedef std::vector<tMapValue> tMapVector;
    
    InfernalFloorMap(): m_state(kInit), m_solidMapValid(false), m_tileMap(NULL), m_lightMapValid(false) {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    const tMapVector& At(Mushware::U32 inX, Mushware::U32 inY) {MUSHCOREASSERT(inX<m_xsize);MUSHCOREASSERT(inY<m_ysize);return m_map[inY][inX];}
    Mushware::U32 XSize(void) {return m_xsize;}
    Mushware::U32 YSize(void) {return m_ysize;}
    Mushware::tVal XStep(void) {return m_xstep;}
    Mushware::tVal YStep(void) {return m_ystep;}
    GLPoint SizeGet(void) { return GLPoint(m_xsize, m_ysize); }
    GLPoint StepGet(void) { return GLPoint(m_xstep, m_ystep); }

    const InfernalMapPoint SpaceToMap(const InfernalSpacePoint inPoint) const;
    const InfernalMapPoint SpaceToMapFractional(const InfernalSpacePoint inPoint) const;
    const InfernalSpacePoint MapToSpace(const InfernalMapPoint inPoint) const;
    bool IsInMap(const InfernalMapPoint inPoint) const;

    void Render(const InfernalMapArea& inArea, const InfernalMapArea& inHighlight, const std::vector<bool>& inTierHighlight);
    void RenderSolidMap(const InfernalMapArea& inArea) const;
    void RenderAdhesionMap(const InfernalMapArea& inArea) const;
    void RenderLightMap(const InfernalMapArea& inArea) const;
        
    const tMapVector& ElementGet(const GLPoint &inPoint) const;
    const tMapVector& ElementGet(const InfernalSpacePoint &inPoint) const;
    const tMapVector& ElementGet(const InfernalMapPoint &inPoint) const;
    void ElementSet(const GLPoint &inPoint, const tMapVector& inValue);
    Mushware::tVal PermeabilityGet(const InfernalMapPoint &inPoint) const;
    Mushware::tVal AdhesionGet(const InfernalSpacePoint &inPoint) const;
    Mushware::tVal AdhesionGet(const InfernalMapPoint &inPoint) const;
    void SetLightingFor(const InfernalSpacePoint &inPoint) const;
    void SetLightingFor(const InfernalMapPoint &inPoint) const;
    void AttachTileMap(InfernalTileMap *inTileMap) { m_tileMap=inTileMap; }
    const InfernalSolidMap& SolidMapGet(void) const;
    void SolidMapInvalidate(void) { m_solidMapValid=false; }
    void LightMapInvalidate(void) { m_lightMapValid=false; }
   
    static MushcoreScalar LoadFloorMap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

protected:
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

    void HandleDataEnd(MushcoreXML& inXML);
    void HandleGameFloorMapStart(MushcoreXML& inXML);
    void HandleGameFloorMapEnd(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);

    enum
    {
        kInvalid,
        kInit,
        kData,
        kNumStates
    };

private:
    void RebuildSolidMap(void) const;
    void RebuildLightMap(void) const;

    typedef std::map<std::string, void (InfernalFloorMap::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    Mushware::U32 m_state;
    
    std::vector< std::vector< tMapVector > > m_map;
    Mushware::U32 m_xsize;
    Mushware::U32 m_ysize;
    Mushware::tVal m_xstep;
    Mushware::tVal m_ystep;
    mutable InfernalSolidMap m_solidMap;
    mutable bool m_solidMapValid;
    InfernalTileMap *m_tileMap;
    
    mutable InfernalMap<InfernalLightLinks> m_lightMap;
    mutable bool m_lightMapValid;
    
    static tMapVector m_emptyMapVector;
};

inline std::ostream& operator<<(std::ostream &inOut, const InfernalFloorMap& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
