#ifndef MUSHCOREUTIL_H
#define MUSHCOREUTIL_H
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
 * $Id: MushcoreUtil.h,v 1.9 2002/12/29 20:30:52 southa Exp $
 * $Log: MushcoreUtil.h,v $
 * Revision 1.9  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.8  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "MushcoreStandard.h"

class MushcoreUtil
{
public:
    static Mushware::U32 BigEndianU32Get(std::istream& inIn);
    static Mushware::U32 LittleEndianU32Get(std::istream& inIn);
    static Mushware::U8 U8Get(std::istream& inIn);

    static std::string TranslateFilename(const std::string& inStr) {return inStr;}
    static std::string AppDirFilename(const std::string& inStr);
};
#endif
#endif
