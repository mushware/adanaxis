#ifndef COREUTIL_H
#define COREUTIL_H
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
 * $Id: CoreUtil.h,v 1.7 2002/10/22 20:41:59 southa Exp $
 * $Log: CoreUtil.h,v $
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "CoreStandard.h"

class CoreUtil
{
public:
    static Mushware::U32 BigEndianU32Get(istream& inIn);
    static Mushware::U32 LittleEndianU32Get(istream& inIn);
    static Mushware::U8 U8Get(istream& inIn);

    static string TranslateFilename(const string& inStr) {return inStr;}
    static string AppDirFilename(const string& inStr);
};
#endif
