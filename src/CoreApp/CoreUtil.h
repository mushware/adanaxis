/*
 * $Id: CoreUtil.h,v 1.1 2002/05/10 16:39:38 southa Exp $
 * $Log: CoreUtil.h,v $
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
