#ifndef GAMENETOBJECT_H
#define GAMENETOBJECT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameNetObject.h,v 1.5 2002/12/12 14:00:39 southa Exp $
 * $Log: GameNetObject.h,v $
 * Revision 1.5  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.4  2002/11/28 11:10:29  southa
 * Client and server delete messages
 *
 * Revision 1.3  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
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
    virtual void Pickle(std::ostream& inOut, const string& inPrefix="") const;
    virtual void Unpickle(CoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    void AddressSet(const MustlAddress& inAddress) { m_address = inAddress; }
    const MustlAddress& AddressGet(void) const { return m_address; }
    
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
    typedef std::map<string, void (GameNetObject::*)(CoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    Mushware::U32 m_pickleState;
    
    MustlAddress m_address;
};

inline std::ostream& operator<<(std::ostream &inOut, const GameNetObject& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
