#ifndef GAMETILEMAP_H
#define GAMETILEMAP_H
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
 * $Id: GameTileMap.h,v 1.18 2003/01/11 13:03:15 southa Exp $
 * $Log: GameTileMap.h,v $
 * Revision 1.18  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.17  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.16  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.15  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/11/24 23:18:25  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.13  2002/11/18 11:31:14  southa
 * Return to game mode
 *
 * Revision 1.12  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.11  2002/10/13 12:26:47  southa
 * Facetised std::map rendering
 *
 * Revision 1.10  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.7  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.6  2002/06/05 12:28:05  southa
 * Map rendered using traits
 *
 * Revision 1.5  2002/06/04 20:27:37  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.4  2002/06/04 14:12:25  southa
 * Traits loader first stage
 *
 * Revision 1.3  2002/05/30 14:41:12  southa
 * GameData and loadtilemap command
 *
 * Revision 1.2  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.1  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 */

#include "GameTileSpec.h"
#include "Mushcore.h"

class GameTraits;

class GameTileMap : public MushcorePickle, private MushcoreXMLHandler
{
public:
    GameTileMap(): m_state(kInit), m_warned(false) {}
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;
    
    const std::string& NameGet(Mushware::U32 inNum) const;
    bool TraitsExist(Mushware::U32 inNum) const;
    const GameTileSpec& TileSpecGet(Mushware::U32 inNum);
    void Load(void);
    
    static MushcoreScalar LoadTileMap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
    
protected:
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

    void HandleMapEnd(MushcoreXML& inXML);
    void HandleTileMapStart(MushcoreXML& inXML);
    void HandleTileMapEnd(MushcoreXML& inXML);
    void HandleScriptStart(MushcoreXML& inXML);
    void HandleScriptEnd(MushcoreXML& inXML);
    void HandleTraitsStart(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);

    enum
    {
        kInvalid,
        kInit,
        kData,
        kNumStates
    };

private:

    enum
    {
        kMaxVectorSize=4000
    };

    const GameTileSpec& LookupSpec(Mushware::U32 inNum);

    typedef std::map<string, void (GameTileMap::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    Mushware::U32 m_state;
    // End of XML stuff
    class TraitDef
    {
    public:
        TraitDef() {}
        TraitDef(const std::string& inName, const GameTileSpec& inSpec) :
            name(inName),
            spec(inSpec)
            {}
        std::string name;
        GameTileSpec spec;
    };

    typedef std::map<Mushware::U32, TraitDef> tTraitMap;

    tTraitMap m_map;
    MushcoreScript m_loaderScript;

    mutable bool m_warned;
    mutable std::vector<GameTileSpec *> m_traits;
};

inline std::ostream& operator<<(std::ostream &inOut, const GameTileMap& inMap)
{
    inMap.Pickle(inOut);
    return inOut;
}

#endif
