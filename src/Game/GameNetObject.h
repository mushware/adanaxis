//%includeGuardStart {
#ifndef GAMENETOBJECT_H
#define GAMENETOBJECT_H
//%includeGuardStart } WXTSJHy/mA9uvcjKSFTFcA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameNetObject.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ODs7JK0jpTTeTOOP3r/q1w
/*
 * $Id: GameNetObject.h,v 1.11 2003/08/21 23:08:50 southa Exp $
 * $Log: GameNetObject.h,v $
 * Revision 1.11  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.9  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.8  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.6  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "Mushcore.h"

#include "mushMedia.h"

class GameNetObject : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    virtual ~GameNetObject();
    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);
    virtual char *TypeNameGet(void) const;

    void AddressSet(const MustlAddress& inAddress) { m_address = inAddress; }
    const MustlAddress& AddressGet(void) const { return m_address; }
    
protected:
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

    void HandleGameDefClientStart(MushcoreXML& inXML);
    void HandleGameDefServerStart(MushcoreXML& inXML);
    void HandleNetObjectStart(MushcoreXML& inXML);
    void HandleNetObjectEnd(MushcoreXML& inXML);
    void NullHandler(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

private:
    typedef std::map<std::string, void (GameNetObject::*)(MushcoreXML& inXML)> ElementFunctionMap;
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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
