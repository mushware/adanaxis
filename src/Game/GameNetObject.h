/*
 * $Id: GameNetObject.h,v 1.2 2002/11/25 18:02:57 southa Exp $
 * $Log: GameNetObject.h,v $
 * Revision 1.2  2002/11/25 18:02:57  southa
 * Mushware ID work
 *
 * Revision 1.1  2002/11/25 15:44:03  southa
 * CreateObject message decoding
 *
 */

#include "mushCore.h"

#include "mushMedia.h"

class GameNetObject : public CorePickle, protected CoreXMLHandler
{
public:
    virtual ~GameNetObject();
    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    void AddressSet(const MediaNetAddress& inAddress) { m_address = inAddress; }
    const MediaNetAddress& AddressGet(void) const { return m_address; }
    
protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

    void HandleGameDefClientStart(CoreXML& inXML);
    void HandleGameDefServerStart(CoreXML& inXML);
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

    MediaNetAddress m_address;
};

inline ostream& operator<<(ostream &inOut, const GameNetObject& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
