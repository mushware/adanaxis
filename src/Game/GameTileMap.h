#ifndef GAMETILEMAP_H
#define GAMETILEMAP_H
/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameTileMap : public CorePickle, private CoreXMLHandler
{
public:
    GameTileMap(): m_state(kInit) {}
    virtual void Pickle(ostream& inOut) const;
    virtual void Unpickle(CoreXML& inXML);
    void Load(void);
    
protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void HandleMapEnd(CoreXML& inXML);
    void HandleTileMapStart(CoreXML& inXML);
    void HandleTileMapEnd(CoreXML& inXML);
    void HandleScriptStart(CoreXML& inXML);
    void HandleScriptEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum
    {
        kInit,
        kData,
        kNumStates
    };

private:
    typedef map<string, void (GameTileMap::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    U32 m_state;

    map<U32, string> m_map;
    CoreScript m_loaderScript;
};
#endif
