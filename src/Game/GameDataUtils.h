//%includeGuardStart {
#ifndef GAMEDATAUTILS_H
#define GAMEDATAUTILS_H
//%includeGuardStart } rJ11GWpIyovpV8ANQnm8Sw
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDataUtils.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } DoSOWNXzAjXUpkwQiOeCdQ
/*
 * $Id: GameDataUtils.h,v 1.7 2003/08/21 23:08:42 southa Exp $
 * $Log: GameDataUtils.h,v $
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

#include "Mushcore.h"

class GameDataUtils
{
public:
    static void NamedDialoguesAdd(const std::string& inStr); // Takes regular expression
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
