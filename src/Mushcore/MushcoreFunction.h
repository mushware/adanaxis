#ifndef MUSHCOREFUNCTION_H
#define MUSHCOREFUNCTION_H
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
 * $Id: MushcoreFunction.h,v 1.4 2003/01/20 12:23:23 southa Exp $
 * $Log: MushcoreFunction.h,v $
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.10  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/29 08:56:16  southa
 * Tile display
 *
 * Revision 1.3  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.2  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/03/08 22:48:14  southa
 * Added first avarisse code
 *
 * Revision 1.2  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/03/01 12:21:25  southa
 * Added first MushcoreScript code
 *
 */

#include "MushcoreStandard.h"

class MushcoreFunction
{
public:
    MushcoreFunction() {}
    MushcoreFunction(const std::string& inStr): m_name(inStr) {}
    MUSHCORE_DECLARE_INLINE void CommandAdd(const std::string& inStr);
    const std::string& NameGet(void) const { return m_name; }
    const std::string& CommandGet(Mushware::U32 inIndex) const { return m_commands[inIndex]; }
    Mushware::U32 SizeGet(void) const { return m_commands.size(); }
    
    void ThrowErrorExecute(void) const;
    void CoalesceErrorsExecute(void) const;
    
    void Print(std::ostream &ioOut) const;
    
private:
    typedef std::vector<std::string> tCommands;
    std::string m_name;
    tCommands m_commands;
};

inline void
MushcoreFunction::CommandAdd(const std::string& inStr)
{
    if (inStr != "")
    {
        m_commands.push_back(inStr);
    }
}

inline std::ostream&
operator<<(std::ostream &ioOut, const MushcoreFunction& inFunction)
{
    inFunction.Print(ioOut);
    return ioOut;
}

#endif
