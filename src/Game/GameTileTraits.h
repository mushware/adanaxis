/*
 * $Id$
 * $Log$
 */

#include "GameTraits.h"

class GameTileTraits : public GameTraits
{
public:
    virtual ~GameTileTraits() {}
    void Render(void) {}

    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);

protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void HandleGraphicStart(CoreXML& inXML);
    void HandleGraphicEnd(CoreXML& inXML);
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
    
    // vector <GameGraphics> m_graphics;
};
