//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreParamList.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } oGkA8yWmmPJV0bdTTs9y2g
/*
 * $Id: MushcoreParamList.cpp,v 1.5 2003/08/21 23:09:14 southa Exp $
 * $Log: MushcoreParamList.cpp,v $
 * Revision 1.5  2003/08/21 23:09:14  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/02/03 23:15:51  southa
 * Build work for Visual C++
 *
 * Revision 1.3  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:41:59  southa
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
 * Revision 1.4  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.3  2002/05/24 16:23:09  southa
 * Config and typenames
 *
 * Revision 1.2  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 */

#include "MushcoreParamList.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

void
MushcoreParamList::Print(ostream& ioOut) const
{
    bool first=true;
    
    tParamsConstIterator endValue = m_params.end();
    
    for (tParamsConstIterator p = m_params.begin(); p != endValue; ++p)
    {
        if (first)
        {
            first=false;
        }
        else
        {
            ioOut << ", ";
        }
        ioOut << *p;
    }
}
