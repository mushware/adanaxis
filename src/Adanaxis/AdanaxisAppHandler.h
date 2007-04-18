//%includeGuardStart {
#ifndef ADANAXISAPPHANDLER_H
#define ADANAXISAPPHANDLER_H
//%includeGuardStart } v8t9CZvWGMEKr8skTuEKcQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisAppHandler.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6BQT67GhCMk937Kb8YQA2g
/*
 * $Id: AdanaxisAppHandler.h,v 1.8 2006/08/01 17:21:22 southa Exp $
 * $Log: AdanaxisAppHandler.h,v $
 * Revision 1.8  2006/08/01 17:21:22  southa
 * River demo
 *
 * Revision 1.7  2006/07/31 11:01:36  southa
 * Music and dialogues
 *
 * Revision 1.6  2006/07/07 18:13:57  southa
 * Menu start and stop
 *
 * Revision 1.5  2006/06/30 15:05:30  southa
 * Texture and buffer purge
 *
 * Revision 1.4  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.2  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"

//:xml1base MushGameAppHandler
//:generate virtual standard ostram xml1
class AdanaxisAppHandler : public MushGameAppHandler
{
public:
    AdanaxisAppHandler(const std::string& inName = "");
    void NewGameCreate(const std::string& inName);
    
private:
    MushcoreDataRef<MushGameBase> m_gameRef;
    bool m_firstGame; //:readwrite
//%classPrototypes {
public:
    const bool& FirstGame(void) const { return m_firstGame; }
    void FirstGameSet(const bool& inValue) { m_firstGame=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 41ea4WwBp3htQ6jE1GF4Mg
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
