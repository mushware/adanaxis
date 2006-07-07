//%includeGuardStart {
#ifndef ADANAXISAPPHANDLER_H
#define ADANAXISAPPHANDLER_H
//%includeGuardStart } v8t9CZvWGMEKr8skTuEKcQ
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisAppHandler.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } C/16EW0GDk97fUG+f75bUQ
/*
 * $Id: AdanaxisAppHandler.h,v 1.5 2006/06/30 15:05:30 southa Exp $
 * $Log: AdanaxisAppHandler.h,v $
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

class AdanaxisAppHandler : public MushGameAppHandler
{
public:
    AdanaxisAppHandler(const std::string& inName = "");
    void NewGameCreate(const std::string& inName);
    
private:
    MushcoreDataRef<MushGameBase> m_gameRef;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
