//%includeGuardStart {
#ifndef ADANAXISRUBY_H
#define ADANAXISRUBY_H
//%includeGuardStart } C5QmIHf+lvoXdK5/EOui9Q
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRuby.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } M/DhwggGGCe5wb6cbey+rg
/*
 * $Id: AdanaxisRuby.h,v 1.11 2007/04/18 09:22:03 southa Exp $
 * $Log: AdanaxisRuby.h,v $
 * Revision 1.11  2007/04/18 09:22:03  southa
 * Header and level fixes
 *
 * Revision 1.10  2007/04/16 18:50:59  southa
 * Voice work
 *
 * Revision 1.9  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.8  2007/03/20 17:31:24  southa
 * Difficulty and GL options
 *
 * Revision 1.7  2007/03/19 16:01:35  southa
 * Damage indicators
 *
 * Revision 1.6  2007/03/07 11:29:24  southa
 * Level permission
 *
 * Revision 1.5  2006/11/12 20:09:55  southa
 * Missile guidance
 *
 * Revision 1.4  2006/08/20 14:19:21  southa
 * Seek operation
 *
 * Revision 1.3  2006/08/01 17:21:27  southa
 * River demo
 *
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
	static Mushware::tRubyValue PlayerPosition(Mushware::tRubyValue inSelf);
	static Mushware::tRubyValue PlayerOrientationForce(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue PlayerTargetID(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue RecordTime(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue DamageIconSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0, Mushware::tRubyValue inArg1);
    static Mushware::tRubyValue ConfigDifficulty(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue ConfigDifficultySet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue GameDifficulty(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue UseGLCompression(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue UseGLCompressionSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue UseGLShader(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue UseGLShaderSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue Apply2020Makeover(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue Apply2020MakeoverSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
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
