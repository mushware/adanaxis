#ifndef CORECOMMAND_H
#define CORECOMMAND_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: CoreCommand.h,v 1.5 2002/06/27 12:36:03 southa Exp $
 * $Log: CoreCommand.h,v $
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

#include "CoreStandard.h"
#include "CoreBison.h"
#include "CoreParamList.h"

class CoreEnv;

class CoreCommand
{
public:
    CoreCommand(const string& inStr): m_bison(inStr), m_string(inStr) {}
    void Execute(CoreEnv& inEnv);
    void Execute(void);
    const string& Name(void) {return m_name;}
    tSize NumParams(void) {return m_paramList.NumParams();}
    string AllParams(void);
    string PopString(void);
    tVal PopVal(void);
    void PopParam(string& outStr) {m_paramList.PopParam(outStr);}
    void PopParam(tVal& outVal) {m_paramList.PopParam(outVal);}
    void PopParam(U32& outU32) {m_paramList.PopParam(outU32);}
    
    // Callback interface from bison - not public
    CoreScalar Despatch(void);
    void PushParam(CoreScalar& inParam) {m_paramList.PushParam(inParam);}
    void ClearParams(void) {m_paramList.Clear();}
    void NameSet(const string& inStr) {m_name=inStr;}
    
private:
    CoreBison m_bison;
    string m_name;
    string m_string;
    CoreParamList m_paramList;
};
#endif
