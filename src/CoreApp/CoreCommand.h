#ifndef CORECOMMAND_H
#define CORECOMMAND_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: CoreCommand.h,v 1.11 2002/12/20 13:17:31 southa Exp $
 * $Log: CoreCommand.h,v $
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

#include "CoreBison.h"
#include "CoreParamList.h"
#include "CoreStandard.h"

class CoreEnv;

class CoreCommand
{
public:
    CoreCommand(const std::string& inStr): m_bison(inStr), m_string(inStr) {}
    void Execute(CoreEnv& inEnv);
    void Execute(void);
    const std::string& Name(void) const { return m_name; }
    const CoreParamList& ParamListGet(void) const { return m_paramList; }
    Mushware::U32 NumParams(void) {return m_paramList.NumParams();}
    std::string AllParams(void);
    std::string PopString(void);
    Mushware::tVal PopVal(void);
    void PopParam(std::string& outStr) {m_paramList.PopParam(outStr);}
    void PopParam(Mushware::tVal& outVal) {m_paramList.PopParam(outVal);}
    void PopParam(Mushware::U32& outU32) {m_paramList.PopParam(outU32);}

    // Callback interface from bison - not public
    CoreScalar Despatch(void);
    void PushParam(CoreScalar& inParam) {m_paramList.PushParam(inParam);}
    void ClearParams(void) {m_paramList.Clear();}
    void NameSet(const std::string& inStr) {m_name=inStr;}
    
private:
    CoreBison m_bison;
    std::string m_name;
    std::string m_string;
    CoreParamList m_paramList;
};
#endif
