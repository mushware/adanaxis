#ifndef GAMEDATAUTILS_H
#define GAMEDATAUTILS_H
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
 * $Id: GameDataUtils.h,v 1.1 2002/08/10 12:34:48 southa Exp $
 * $Log: GameDataUtils.h,v $
 * Revision 1.1  2002/08/10 12:34:48  southa
 * Added current dialogues
 *
 */

#include "mushCore.h"

class GameDataUtils
{
public:
    static void NamedDialoguesAdd(const string& inStr); // Takes regular expression
};
#endif
