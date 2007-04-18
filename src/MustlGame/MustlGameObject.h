//%includeGuardStart {
#ifndef MUSTLGAMEOBJECT_H
#define MUSTLGAMEOBJECT_H
//%includeGuardStart } WW/LEJoL5ZgTLzt0OtWMAg
//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameObject.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } +5sffB4PGAZN4ZLfq7GmfQ
/*
 * $Id: MustlGameObject.h,v 1.6 2006/06/01 20:13:01 southa Exp $
 * $Log: MustlGameObject.h,v $
 * Revision 1.6  2006/06/01 20:13:01  southa
 * Initial texture caching
 *
 * Revision 1.5  2006/06/01 15:39:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
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

#include "MustlAddress.h"

#include "mushMushcore.h"

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
