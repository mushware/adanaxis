//%includeGuardStart {
#ifndef INFERNALDATAUTILS_H
#define INFERNALDATAUTILS_H
//%includeGuardStart } SnrlkcsX5I7FHGwRpVsD8A
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalDataUtils.h
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
//%Header } lfaF9T0q/qyWdL7QlAztZw
/*
 * $Id: InfernalDataUtils.h,v 1.4 2004/01/06 20:46:50 southa Exp $
 * $Log: InfernalDataUtils.h,v $
 * Revision 1.4  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 12:44:34  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:05  southa
 * File renaming
 *
 * Revision 1.8  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:08:42  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.5  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.1  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 */

#include "mushMushcore.h"

class InfernalDataUtils
{
public:
    static void NamedDialoguesAdd(const std::string& inStr); // Takes regular expression
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
