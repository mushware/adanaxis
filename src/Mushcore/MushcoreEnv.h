//%includeGuardStart {
#ifndef MUSHCOREENV_H
#define MUSHCOREENV_H
//%includeGuardStart } Eq5NN656mTaTht1Xpecjog
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreEnv.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } tUAkmqyBXJdoSLWUndjNCA
/*
 * $Id: MushcoreEnv.h,v 1.12 2003/10/04 12:23:08 southa Exp $
 * $Log: MushcoreEnv.h,v $
 * Revision 1.12  2003/10/04 12:23:08  southa
 * File renaming
 *
 * Revision 1.11  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:09:10  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.8  2003/02/03 23:15:50  southa
 * Build work for Visual C++
 *
 * Revision 1.7  2003/01/20 17:03:21  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.6  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.5  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.4  2003/01/17 13:30:40  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.14  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.13  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.12  2002/11/07 11:59:02  southa
 * Web commands
 *
 * Revision 1.11  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/31 16:27:15  southa
 * Collision checking work
 *
 * Revision 1.7  2002/07/07 13:44:18  southa
 * Screen size config variables
 *
 * Revision 1.6  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.5  2002/07/02 14:27:12  southa
 * First floor std::map designer build
 *
 * Revision 1.4  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/30 14:41:13  southa
 * InfernalData and loadtilemap command
 *
 * Revision 1.2  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreConfig.h"

class MushcoreScalar;

class MushcoreEnv
{
public:
    static MushcoreEnv& Sgl(void) {return *((m_instance==NULL)?m_instance=new MushcoreEnv:m_instance);}

    void PushConfig(MushcoreConfig& inConfig);
    void PopConfig(MushcoreConfig& inConfig);
    const MushcoreScalar& VariableGet(const std::string& inName) const;
    bool VariableGetIfExists(const MushcoreScalar *& outScalar, const std::string& inName) const;
    bool VariableExists(const std::string& inName) const;
    std::ostream& Out(void) const;
    void OutSet(std::ostream& inOut);
    void OutReset(void);

	template<class ParamType> inline bool VariableGetIfExists(ParamType& outParam, const std::string& inName) const
	{
		const MushcoreScalar *pScalar;
		if (VariableGetIfExists(pScalar, inName))
		{
			pScalar->Get(outParam);
			return true;
		}
		return false;
	}
    template<class ParamType> inline void VariableSet(const std::string& inName, const ParamType& inValue)
    {
	    MUSHCOREASSERT(m_config.size() > 0);
	    m_config.back()->Set(inName, inValue);
    }

    static void NullFunction(void);

private:
    MushcoreEnv();

    std::ostream *m_outStream;
    bool m_outSet;
    std::vector<MushcoreConfig *> m_config;
    static MushcoreEnv *m_instance;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
