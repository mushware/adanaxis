//%includeGuardStart {
#ifndef MUSTLGAMEOBJECT_H
#define MUSTLGAMEOBJECT_H
//%includeGuardStart } WW/LEJoL5ZgTLzt0OtWMAg
//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameObject.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } eoZ1k3d9jW1nZN6k0yXfDA
/*
 * $Id: MustlGameObject.h,v 1.12 2003/09/17 19:40:32 southa Exp $
 * $Log: MustlGameObject.h,v $
 * Revision 1.12  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
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

class MustlGameObject : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    virtual ~MustlGameObject();
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
    typedef std::map<std::string, void (MustlGameObject::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    Mushware::U32 m_pickleState;
    
    MustlAddress m_address;
};

inline std::ostream& operator<<(std::ostream &inOut, const MustlGameObject& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
