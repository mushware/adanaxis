#ifndef GAMEDEF_H
#define GAMEDEF_H
/*
 * $Id: GameDef.h,v 1.12 2002/12/05 23:52:51 southa Exp $
 * $Log: GameDef.h,v $
 * Revision 1.12  2002/12/05 23:52:51  southa
 * Network management and status
 *
 * Revision 1.11  2002/12/05 13:20:12  southa
 * Client link handling
 *
 * Revision 1.10  2002/12/04 12:54:41  southa
 * Network control work
 *
 * Revision 1.9  2002/11/28 15:33:31  southa
 * Pass GameDef status over link
 *
 * Revision 1.8  2002/11/28 15:14:14  southa
 * Multiplayer setup timing
 *
 * Revision 1.7  2002/11/28 12:05:45  southa
 * Server name work
 *
 * Revision 1.6  2002/11/27 16:35:09  southa
 * Client and server image handling
 *
 * Revision 1.5  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
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

class MediaNetAddress;

class GameDef : public CorePickle, protected CoreXMLHandler
{
public:
    enum tStatus
    {
        kStatusInvalid,
        kStatusOK,
        kStatusTesting,
        kStatusNoServer
    };
    
    explicit GameDef(const string& inName);
    virtual ~GameDef() {}
    virtual void Ticker(const string& inName) = 0;
    virtual void WebPrint(ostream& ioOut) const = 0;

    virtual void Pickle(ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);

    const string& NameGet(void) const { return m_name; }
    bool ImageIs(void) const { return m_isImage; }
    void ImageIsSet(bool inValue) { m_isImage = inValue; }
    const string StatusWebStringGet(void) const;
    U32 CreationMsecGet(void) const { return m_creationMsec; }
    
protected:
    tStatus StatusGet(void) { return m_status; }
    void StatusSet(tStatus inStatus) { m_status = inStatus; }
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(CoreXML& inXML);
    void XMLEndHandler(CoreXML& inXML);
    void XMLDataHandler(CoreXML& inXML);

private:
    void NullHandler(CoreXML& inXML);
    void HandleNameEnd(CoreXML& inXML);
    void HandleStatusEnd(CoreXML& inXML);

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
    tStatus m_status;
    U32 m_creationMsec;
    bool m_isImage;
};
#endif
