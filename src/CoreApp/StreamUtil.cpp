/*
 * $Id: StreamUtil.cpp,v 1.2 2002/05/09 17:10:38 southa Exp $
 * $Log: StreamUtil.cpp,v $
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "StreamUtil.h"

U32
StreamUtil::BigEndianU32Get(u8istream& inIn)
{
    U8 buf[4]={0,0,0,0};
    inIn.read(buf, 4);
    m_ctr+=4;
    return ((buf[0] << 24) |
            (buf[1] << 16) |
            (buf[2] << 8)  |
            (buf[3] << 0) );
}

U32
StreamUtil::LittleEndianU32Get(u8istream& inIn)
{
    U8 buf[4]={0,0,0,0};
    inIn.read(buf, 4);
    m_ctr+=4;
    return ((buf[0] << 0)  |
            (buf[1] << 8)  |
            (buf[2] << 16) |
            (buf[3] << 24));
}

U8
StreamUtil::U8Get(u8istream& inIn)
{
    char ch; // Should be U8
    inIn.get(ch);
    ++m_ctr;
    return ch;
}

void
StreamUtil::Ignore(u8istream& inIn, Size inSize)
{
    inIn.ignore(inSize);
    m_ctr+=inSize;
}

void
StreamUtil::Get(u8istream& inIn, U8 *outBuffer, Size inSize)
{
    inIn.read(outBuffer, inSize);
    m_ctr+=inSize;
}

void
StreamUtil::ZeroIndex(Size inWhich)
{
    if (inWhich >= m_zero.size())
    {
        m_zero.resize(inWhich+1);
    }
    m_zero[inWhich]=m_ctr;
}

Size
StreamUtil::GetIndex(Size inWhich)
{
    if (inWhich >= m_zero.size())
    {
        throw "StreamUtil::Request for uninitialised index";
    }
    return m_ctr-m_zero[inWhich];
}

void
StreamUtil::ConsumeToIndex(u8istream& inIn, Size inWhich, Size inValue)
{
    int target=inValue-GetIndex(inWhich);
    if (target>0)
    {
        Ignore(inIn, target);
    }
}
