#ifndef GAMETILEMAP_H
#define GAMETILEMAP_H
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
 * $Id: GameTileMap.h,v 1.12 2002/10/22 20:42:06 southa Exp $
 * $Log: GameTileMap.h,v $
 * Revision 1.12  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.11  2002/10/13 12:26:47  southa
 * Facetised map rendering
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

#include "mushCore.h"
#include "GameTileSpec.h"

class GameTraits;

class GameTileMap : public CorePickle, private CoreXMLHandler
{
public:
    GameTileMap(): m_state(kInit), m_warned(false) {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    const string& NameGet(U32 inNum) const;
    bool TraitsExist(U32 inNum) const;
    const GameTileSpec& TileSpecGet(U32 inNum);
    void Load(void);
    
    static CoreScalar LoadTileMap(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);
    
protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void HandleMapEnd(CoreXML& inXML);
    void HandleTileMapStart(CoreXML& inXML);
    void HandleTileMapEnd(CoreXML& inXML);
    void HandleScriptStart(CoreXML& inXML);
    void HandleScriptEnd(CoreXML& inXML);
    void HandleTraitsStart(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

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

    const GameTileSpec& LookupSpec(U32 inNum);

    typedef map<string, void (GameTileMap::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    U32 m_state;
    // End of XML stuff
    class TraitDef
    {
    public:
        TraitDef() {}
        TraitDef(const string& inName, const GameTileSpec& inSpec) :
            name(inName),
            spec(inSpec)
            {}
        string name;
        GameTileSpec spec;
    };
    
    typedef map<U32, TraitDef> tTraitMap;

    tTraitMap m_map;
    CoreScript m_loaderScript;

    mutable bool m_warned;
    mutable vector<GameTileSpec *> m_traits;
};

inline ostream& operator<<(ostream &inOut, const GameTileMap& inMap)
{
    inMap.Pickle(inOut);
    return inOut;
}

#endif
