/*
 * $Id: CoreUtil.h,v 1.1 2002/02/26 17:01:40 southa Exp $
 * $Log: CoreUtil.h,v $
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
};