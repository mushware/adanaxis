#ifndef GAMEDATAUTILS_H
#define GAMEDATAUTILS_H
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
 * $Id: GameDataUtils.h,v 1.3 2002/10/22 20:42:03 southa Exp $
 * $Log: GameDataUtils.h,v $
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

#include "mushCore.h"

class GameDataUtils
{
public:
    static void NamedDialoguesAdd(const string& inStr); // Takes regular expression
};
#endif
