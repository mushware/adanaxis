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
 * $Id: CoreUtil.cpp,v 1.10 2002/10/22 20:41:59 southa Exp $
 * $Log: CoreUtil.cpp,v $
 * Revision 1.10  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/04 20:27:36  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.4  2002/05/27 12:58:43  southa
 * GameContract and global configs added
 *
 * Revision 1.3  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "CoreUtil.h"
#include "CoreGlobalConfig.h"

using namespace Mushware;

U32
CoreUtil::BigEndianU32Get(istream& inIn)
{
    U8 buf[4]={0,0,0,0};
    inIn.read(reinterpret_cast<char *>(buf), 4);
    return ((buf[0] << 24) |
            (buf[1] << 16) |
            (buf[2] << 8)  |
            (buf[3] << 0) );
}

U32
CoreUtil::LittleEndianU32Get(istream& inIn)
{
    U8 buf[4]={0,0,0,0};
    inIn.read(reinterpret_cast<char *>(buf), 4);
    return ((buf[0] << 0)  |
            (buf[1] << 8)  |
            (buf[2] << 16) |
            (buf[3] << 24));
}

U8
CoreUtil::U8Get(istream& inIn)
{
    char ch;
    inIn.get(ch);
    return * reinterpret_cast<U8 *>(&ch);
}

string
CoreUtil::AppDirFilename(const string& inStr)
{
    return CoreGlobalConfig::Instance().Get("APPLPATH").StringGet() + "/" + inStr;
}
