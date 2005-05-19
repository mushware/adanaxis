//%includeGuardStart {
#ifndef MUSHCORECONFIG_H
#define MUSHCORECONFIG_H
//%includeGuardStart } tk9OsM5FERwFoYSoHhFOZQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreConfig.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } melRB0+0hNyY/EGCcggsHg
/*
 * $Id: MushcoreConfig.h,v 1.11 2004/01/02 21:13:12 southa Exp $
 * $Log: MushcoreConfig.h,v $
 * Revision 1.11  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.10  2003/10/04 12:23:08  southa
 * File renaming
 *
 * Revision 1.9  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:09:09  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.6  2003/02/03 23:15:49  southa
 * Build work for Visual C++
 *
 * Revision 1.5  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.4  2003/01/17 13:30:40  southa
 * Source conditioning and build fixes
 *
 * Revision 1.3  2003/01/13 23:05:22  southa
 * Mustl test application
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.17  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.16  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.15  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.14  2002/11/24 23:18:03  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.13  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.11  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.10  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.9  2002/07/02 14:27:12  southa
 * First floor std::map designer build
 *
 * Revision 1.8  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.7  2002/06/04 14:11:21  southa
 * Traits loader first stage
 *
 * Revision 1.6  2002/05/30 14:41:13  southa
 * InfernalData and loadtilemap command
 *
 * Revision 1.5  2002/05/28 13:07:03  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.4  2002/05/27 12:58:42  southa
 * InfernalContract and global configs added
 *
 * Revision 1.3  2002/05/26 16:35:07  southa
 * MushcoreXML work
 *
 * Revision 1.2  2002/05/25 17:17:18  southa
 * MushcoreXML implementation
 *
 * Revision 1.1  2002/05/24 16:23:09  southa
 * Config and typenames
 *
 */

#include "MushcoreScalar.h"
#include "MushcoreStandard.h"

class MushcoreConfig
{
public:
    virtual ~MushcoreConfig() {}

    const MushcoreScalar& Get(const std::string& inName) const;
    bool GetIfExists(const MushcoreScalar *& outScalar, const std::string& inName) const;
    bool Exists(const std::string& inName) const;

    template<class ParamType> inline void Set(const std::string& inName, const ParamType& inParam)
	{
		m_config[inName] = MushcoreScalar(inParam);
	}

private:
    std::map<std::string, MushcoreScalar> m_config;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
