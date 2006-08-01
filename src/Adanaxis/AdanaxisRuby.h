//%includeGuardStart {
#ifndef ADANAXISRUBY_H
#define ADANAXISRUBY_H
//%includeGuardStart } C5QmIHf+lvoXdK5/EOui9Q
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRuby.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } gEqqVEDekPhwNL6FyxZYWg
/*
 * $Id: AdanaxisRuby.h,v 1.2 2006/06/21 16:52:29 southa Exp $
 * $Log: AdanaxisRuby.h,v $
 * Revision 1.2  2006/06/21 16:52:29  southa
 * Deco objects
 *
 * Revision 1.1  2006/06/21 12:17:56  southa
 * Ruby object generation
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisLogic.h"

#include "API/mushMushRuby.h"

class AdanaxisRuby : public MushRubyEmptyObj<2000>
{
public:
	static void AdanaxisInstall(void);
	
	static AdanaxisSaveData& SaveData(void);
	static AdanaxisVolatileData& VolatileData(void);
	static void LogicNameSet(const std::string& inName) { s_logicRef.NameSet(inName); }
	
private:
    static MushcoreDataRef<MushGameLogic> s_logicRef;
};

MUSHRUBYEMPTYOBJ_INSTALL(2000)(void)
{
	EmptyInstall("AdanaxisRuby");
	AdanaxisRuby::AdanaxisInstall();
}

inline AdanaxisSaveData&
AdanaxisRuby::SaveData(void)
{
	AdanaxisLogic *pLogic = dynamic_cast<AdanaxisLogic *>(&s_logicRef.WRef());
    if (pLogic == NULL)
    {
        throw MushcoreLogicFail(std::string("AdanaxisLogic of wrong type '")+s_logicRef.Ref().AutoName()+"'");
    }
	return pLogic->SaveData();
}

inline AdanaxisVolatileData&
AdanaxisRuby::VolatileData(void)
{
	AdanaxisLogic *pLogic = dynamic_cast<AdanaxisLogic *>(&s_logicRef.WRef());
    if (pLogic == NULL)
    {
        throw MushcoreLogicFail(std::string("AdanaxisLogic of wrong type '")+s_logicRef.Ref().AutoName()+"'");
    }
	return pLogic->VolatileData();
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
