/*
 * $Id: GameGraphicSprite.h,v 1.1 2002/06/04 17:02:11 southa Exp $
 * $Log: GameGraphicSprite.h,v $
 * Revision 1.1  2002/06/04 17:02:11  southa
 * More work
 *
 */

#include "GameGraphic.h"
#include "mushGL.h"

class GameGraphicSprite: public GameGraphic
{
public:

    virtual void Render(void);
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual string TypeNameGet(void) const {return "sprite";}
    
protected:
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void HandleGraphicEnd(CoreXML& inXML);
    void HandleNameEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef map<string, void (GameGraphicSprite::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    bool m_baseThreaded;
    
    GLTextureRef m_texRef;
};

inline ostream& operator<<(ostream &inOut, const GameGraphicSprite& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
