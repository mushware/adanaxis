/*
 * $Id: CoreUtil.cpp,v 1.1 2002/02/26 17:01:40 southa Exp $
 * $Log: CoreUtil.cpp,v $
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "CoreUtil.hp"

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
