/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class GameNetObject : public CorePickle, protected CoreXMLHandler
{
public:
    virtual ~GameNetObject();
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;

protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void HandleNetObjectStart(CoreXML& inXML);
    void HandleNetObjectEnd(CoreXML& inXML);
    void NullHandler(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

private:
    typedef map<string, void (GameNetObject::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    U32 m_pickleState;
};

inline ostream& operator<<(ostream &inOut, const GameNetObject& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
