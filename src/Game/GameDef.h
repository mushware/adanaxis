#ifndef GAMEDEF_H
#define GAMEDEF_H
/*
 * $Id: GameDef.h,v 1.4 2002/11/24 23:54:36 southa Exp $
 * $Log: GameDef.h,v $
 * Revision 1.4  2002/11/24 23:54:36  southa
 * Initial send of objects over links
 *
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
class MediaNetAddress;

class GameDef : public CorePickle, protected CoreXMLHandler
{
public:
    explicit GameDef(const string& inName);
    virtual ~GameDef() {}
    virtual void Ticker(void) = 0;
    virtual void WebPrint(ostream& ioOut) const = 0;

    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);

    const string& NameGet(void) const { return m_name; }
    bool IsImage(void) const { return m_isImage; }
    void IsImageSet(bool inValue) { m_isImage = inValue; }
    
protected:
    void CreateNewLink(const GameStationDef& inStation) const;
    void CreateNewLink(const MediaNetAddress& inAddress) const;
    
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

    string m_name;
    bool m_isImage;
};
#endif
