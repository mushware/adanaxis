//%includeGuardStart {
#ifndef MUSTLGAMEBASE_H
#define MUSTLGAMEBASE_H
//%includeGuardStart } nVRUvush7GwFvi5/nkJm/g
//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameBase.h
 *
 * Copyright Andy Southgate 2002-2004
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } VhFSXrH5gZpkOdQUTz9uOg
/*
 * $Id: MustlGameBase.h,v 1.3 2004/01/02 21:13:16 southa Exp $
 * $Log: MustlGameBase.h,v $
 * Revision 1.3  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.21  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.20  2003/08/21 23:08:42  southa
 * Fixed file headers
 *
 * Revision 1.19  2003/02/05 17:06:36  southa
 * Build fixes
 *
 * Revision 1.18  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.17  2003/01/09 14:57:01  southa
 * Created Mushcore
 *
 * Revision 1.16  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.15  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.14  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.13  2002/12/07 18:32:14  southa
 * Network ID stuff
 *
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
 * Pass MustlGameBase status over link
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

#include "mushMushcore.h"

class MustlAddress;

class MustlGameBase : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    enum tStatus
    {
        kStatusInvalid,
        kStatusOK,
        kStatusTesting,
        kStatusNoServer
    };
    
    explicit MustlGameBase(const std::string& inName);
    virtual ~MustlGameBase() {}
    virtual void Ticker(const std::string& inName) = 0;
    virtual void WebPrint(std::ostream& ioOut) const = 0;

    virtual void Pickle(std::ostream& inOut, const std::string& inPrefix="") const;
    virtual void Unpickle(MushcoreXML& inXML);

    const std::string& NameGet(void) const { return m_name; }
    bool ImageIs(void) const { return m_isImage; }
    void ImageIsSet(bool inValue) { m_isImage = inValue; }
    const std::string StatusWebStringGet(void) const;
    Mushware::U32 CreationMsecGet(void) const { return m_creationMsec; }
    
protected:
    tStatus StatusGet(void) { return m_status; }
    void StatusSet(tStatus inStatus) { m_status = inStatus; }
    void UnpicklePrologue(void);
    void UnpickleEpilogue(void);
    void XMLStartHandler(MushcoreXML& inXML);
    void XMLEndHandler(MushcoreXML& inXML);
    void XMLDataHandler(MushcoreXML& inXML);

private:
    void NullHandler(MushcoreXML& inXML);
    void HandleNameEnd(MushcoreXML& inXML);
    void HandleStatusEnd(MushcoreXML& inXML);

    enum PickleState
    {
        kPickleInit,
        kPickleData,
        kPickleNumStates
    };

    typedef std::map<std::string, void (MustlGameBase::*)(MushcoreXML& inXML)> ElementFunctionMap;
    std::vector<ElementFunctionMap> m_startTable;
    std::vector<ElementFunctionMap> m_endTable;
    PickleState m_pickleState;

    std::string m_name;
    tStatus m_status;
    Mushware::U32 m_creationMsec;
    bool m_isImage;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
