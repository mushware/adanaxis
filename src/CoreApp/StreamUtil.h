/*
 * $Id: StreamUtil.h,v 1.2 2002/05/09 17:10:38 southa Exp $
 * $Log: StreamUtil.h,v $
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "CoreStandard.h"

class StreamUtil
{
public:
    StreamUtil():m_ctr(0) {}
    U32 BigEndianU32Get(u8istream& inIn);
    U32 LittleEndianU32Get(u8istream& inIn);
    U8 U8Get(u8istream& inIn);
    void Get(u8istream& inIn, U8 *outBuffer, Size inSize);
    void Ignore(u8istream &inIn, Size inSize);
    void ZeroIndex(Size inWhich);
    Size GetIndex(Size inWhich);
    void ConsumeToIndex(u8istream& inIn, Size inWhich, Size inValue);
    
private:
    vector<int> m_zero;
    int m_ctr;
};