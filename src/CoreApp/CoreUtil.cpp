/*
 * $Id$
 * $Log$
 */

#include "CoreUtil.hp"

U32
CoreUtil::BigEndianU32Get(istream& inIn)
{
    U8 buf[4]={0,0,0,0};
    inIn.read(buf, 4);
    return ((buf[0] << 24) |
            (buf[1] << 16) |
            (buf[2] << 8)  |
            (buf[3] << 0) );
}

U32
CoreUtil::LittleEndianU32Get(istream& inIn)
{
    U8 buf[4]={0,0,0,0};
    inIn.read(buf, 4);
    return ((buf[0] << 0)  |
            (buf[1] << 8)  |
            (buf[2] << 16) |
            (buf[3] << 24));
}

U8
CoreUtil::U8Get(istream& inIn)
{
    U8 ch;
    inIn.get(ch);
    return ch;
}
