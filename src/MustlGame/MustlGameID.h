//%includeGuardStart {
#ifndef MUSTLGAMEID_H
#define MUSTLGAMEID_H
//%includeGuardStart } MiK13pln1khdc8vXGogH7w
//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameID.h
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
//%Header } /kg31EeeuSlYB8mSblVb4g
/*
 * $Id: MustlGameID.h,v 1.1 2003/10/06 22:22:38 southa Exp $
 * $Log: MustlGameID.h,v $
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.8  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.5  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/09 23:59:58  southa
 * Network control
 *
 */

#include "Mushcore.h"
#include "mushMedia.h"

#include "MustlGameClient.h"

class MustlGameID : public MustlID
{
public:
    explicit MustlGameID(const std::string& inStr);
    explicit MustlGameID(MustlData& ioData);
    virtual ~MustlGameID();
    virtual MustlID *Clone(void) const;
    virtual void Pack(MustlData& ioData) const;
    virtual void Unpack(MustlData& ioData);
    virtual void Print(std::ostream& ioOut) const;

    void NameSuffixAdd(const std::string& inStr);
    const MushcoreDataRef<MustlGameClient>& DataRefGet(void) const { return m_clientRef; }
    
private:
    MushcoreDataRef<MustlGameClient> m_clientRef;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
