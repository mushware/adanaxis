#ifndef COREUTIL_H
#define COREUTIL_H
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
 * $Id: CoreUtil.h,v 1.3 2002/06/27 12:36:04 southa Exp $
 * $Log: CoreUtil.h,v $
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
    static U32 BigEndianU32Get(istream& inIn);
    static U32 LittleEndianU32Get(istream& inIn);
    static U8 U8Get(istream& inIn);

    static string TranslateFilename(const string& inStr) {return inStr;}
    static string AppDirFilename(const string& inStr);
};
#endif
