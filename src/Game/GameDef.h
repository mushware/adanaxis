#ifndef GAMEDEF_H
#define GAMEDEF_H
/*
 * $Id: GameDef.h,v 1.3 2002/11/24 22:32:42 southa Exp $
 * $Log: GameDef.h,v $
 * Revision 1.3  2002/11/24 22:32:42  southa
 * Host and join displays
 *
 * Revision 1.2  2002/11/23 17:23:44  southa
 * Sleep in setup
 *
 * Revision 1.1  2002/11/21 18:06:17  southa
 * Non-blocking network connection
 *
 */

#include "mushCore.h"

class GameStationDef;

class GameDef : public CorePickle, protected CoreXMLHandler
{
public:
    GameDef();
    virtual ~GameDef() {}
    virtual void Ticker(void) = 0;
    virtual void WebPrint(ostream& ioOut) const = 0;

    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    
protected:
    void CreateNewLink(const GameStationDef& inStation);
    
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleDefEnd(CoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef map<string, void (GameDef::*)(CoreXML& inXML)> ElementFunctionMap;
    vector<ElementFunctionMap> m_startTable;
    vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;
};
#endif
