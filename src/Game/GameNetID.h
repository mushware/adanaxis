#ifndef GAMENETID_H
#define GAMENETID_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameNetID.h,v 1.6 2003/01/11 13:03:14 southa Exp $
 * $Log: GameNetID.h,v $
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

#include "GameDefClient.h"

class GameNetID : public MustlID
{
public:
    explicit GameNetID(const std::string& inStr);
    explicit GameNetID(MustlData& ioData);
    virtual ~GameNetID();
    virtual MustlID *Clone(void) const;
    virtual void Pack(MustlData& ioData) const;
    virtual void Unpack(MustlData& ioData);
    virtual void Print(std::ostream& ioOut) const;

    void NameSuffixAdd(const std::string& inStr);
    const MushcoreDataRef<GameDefClient>& DataRefGet(void) const { return m_clientRef; }
    
private:
    MushcoreDataRef<GameDefClient> m_clientRef;
};

#endif
