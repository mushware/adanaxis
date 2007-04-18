//%includeGuardStart {
#ifndef MUSHCORECOMMAND_H
#define MUSHCORECOMMAND_H
//%includeGuardStart } bqyHdt+FIZcWuJ+taFUqJQ
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreCommand.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } stWdNVVsf8c6F+NRD10Vuw
/*
 * $Id: MushcoreCommand.h,v 1.13 2006/06/01 15:39:42 southa Exp $
 * $Log: MushcoreCommand.h,v $
 * Revision 1.13  2006/06/01 15:39:42  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.11  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.10  2004/09/26 19:42:05  southa
 * Added MushMesh, fixed typenames and release target
 *
 * Revision 1.9  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:35  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:08  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/02/05 17:06:37  southa
 * Build fixes
 *
 * Revision 1.5  2003/02/03 23:15:49  southa
 * Build work for Visual C++
 *
 * Revision 1.4  2003/01/20 17:03:21  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.3  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.12  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.11  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/11/22 11:42:06  southa
 * Added developer controls
 *
 * Revision 1.9  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.3  2002/05/28 13:07:03  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.2  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.4  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.3  2002/03/04 22:30:48  southa
 * Interpreter work
 *
 * Revision 1.2  2002/03/02 20:35:07  southa
 * Added flex and bison parser
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "MushcoreBison.h"
#include "MushcoreParamList.h"
#include "MushcoreStandard.h"

class MushcoreEnv;

class MushcoreCommand
{
public:
    MushcoreCommand(const std::string& inStr): m_bison(inStr), m_name(), m_string(inStr) {}
    void Execute(MushcoreEnv& inEnv);
    void Execute(void);
    const std::string& Name(void) const { return m_name; }
    const MushcoreParamList& ParamListGet(void) const { return m_paramList; }
	std::size_t NumParams(void) { return m_paramList.NumParams(); }
    std::string AllParams(void);
    std::string PopString(void);
    Mushware::tVal PopVal(void);

    template<class ParamType> inline void PopParam(ParamType& outParam)
	{
		m_paramList.PopParam(outParam);
	}

    // Callback interface from bison - not intended as public
    MushcoreScalar Despatch(void);
    void PushParam(MushcoreScalar& inParam) {m_paramList.PushParam(inParam);}
    void ClearParams(void) {m_paramList.Clear();}
    void NameSet(const std::string& inStr) {m_name=inStr;}
    
private:
    MushcoreBison m_bison;
    std::string m_name;
    std::string m_string;
    MushcoreParamList m_paramList;
};




//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
