//%includeGuardStart {
#ifndef MUSHCORESCRIPT_H
#define MUSHCORESCRIPT_H
//%includeGuardStart } urKsJWO1SYzAJonRAuxV6w
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreScript.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } PHPXCSDW4xEHm+8dy0D1dg
/*
 * $Id: MushcoreScript.h,v 1.5 2003/09/17 19:40:36 southa Exp $
 * $Log: MushcoreScript.h,v $
 * Revision 1.5  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:17  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.9  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.2  2002/05/24 16:23:08  southa
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

#include "MushcoreFunction.h"
#include "MushcoreStandard.h"

class MushcoreScript
{
public:
    MushcoreScript();
    explicit MushcoreScript(const std::string& inContent);
    explicit MushcoreScript(std::istream& inIn);
    
    void Print(std::ostream& ioOut) const;
    const MushcoreFunction& FunctionGet(const std::string& inName) const;
    void Execute(void) const;
    
private:
    typedef std::map<std::string, MushcoreFunction> tFunctionMap;
    typedef tFunctionMap::iterator tFunctionMapIterator;
    typedef tFunctionMap::const_iterator tFunctionMapConstIterator;
    
    void ReadFromStream(std::istream& inIn);
    tFunctionMap m_functions;
};

inline std::ostream&
operator<<(std::ostream &ioOut, const MushcoreScript& inMushcoreScript)
{
    inMushcoreScript.Print(ioOut);
    return ioOut;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
