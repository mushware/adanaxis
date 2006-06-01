//%includeGuardStart {
#ifndef MUSTLGAMEID_H
#define MUSTLGAMEID_H
//%includeGuardStart } MiK13pln1khdc8vXGogH7w
//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameID.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } YA9b7okKTgZGOl30g8KHlg
/*
 * $Id: MustlGameID.h,v 1.6 2006/06/01 15:39:56 southa Exp $
 * $Log: MustlGameID.h,v $
 * Revision 1.6  2006/06/01 15:39:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
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

#include "mushMushcore.h"
#include "mushMedia.h"

#include "MustlGameClient.h"
#include "MustlID.h"

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
