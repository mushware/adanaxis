#ifndef GAMETILEMAP_H
#define GAMETILEMAP_H
/*
 * $Id: GameTileMap.h,v 1.5 2002/06/04 20:27:37 southa Exp $
 * $Log: GameTileMap.h,v $
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

class GameTraits;

class GameTileMap : public CorePickle, private CoreXMLHandler
{
public:
    GameTileMap(): m_state(kInit), m_warned(false) {}
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    const string& NameGet(U32 inNum) const;
    bool TraitsExist(U32 inNum) const;
    GameTraits *TraitsPtrGet(U32 inNum) const;
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
        kInit,
        kData,
        kNumStates
    };

private:

    enum
    {
        kMaxVectorSize=4000
    };

    GameTraits *LookupTrait(U32 inNum) const;

    typedef map<string, void (GameTileMap::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    U32 m_state;

    map<U32, string> m_map;
    CoreScript m_loaderScript;

    mutable bool m_warned;
    mutable vector<GameTraits *> m_traits;
};

inline ostream& operator<<(ostream &inOut, const GameTileMap& inMap)
{
    inMap.Pickle(inOut);
    return inOut;
}

#endif
