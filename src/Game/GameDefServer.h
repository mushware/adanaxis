/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "GameDef.h"

class GameDefServer : public GameDef
{
public:
    GameDefServer();
    virtual void Ticker(void);
    virtual void WebPrint(ostream& ioOut) const;

    void HostGame(const string& inContract, U32 inPlayerLimit);

    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;

protected:
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleDefServerEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleWithinBase,
        kPickleNumStates
    };

    typedef map<string, void (GameDefServer::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
    U32 m_baseThreaded;

    string m_contractName;
    U32 m_playerLimit;
    vector<string> m_clientStation;
};
