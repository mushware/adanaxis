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
 * $Id: MushcoreStreamUtil.cpp,v 1.2 2003/01/12 17:33:00 southa Exp $
 * $Log: MushcoreStreamUtil.cpp,v $
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.8  2003/01/07 17:13:40  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.7  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.6  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:24:10  southa
 * Name changed to MushcoreStreamUtil
 *
 * Revision 1.5  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/24 16:23:10  southa
 * Config and typenames
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

#include "MushcoreStreamUtil.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

U32
MushcoreStreamUtil::BigEndianU32Get(istream& inIn)
{
    U8 buf[4]={0,0,0,0};
    inIn.read(reinterpret_cast<char *>(buf), 4);
    m_ctr+=4;
    return ((buf[0] << 24) |
            (buf[1] << 16) |
            (buf[2] << 8)  |
            (buf[3] << 0) );
}

U32
MushcoreStreamUtil::LittleEndianU32Get(istream& inIn)
{
    U8 buf[4]={0,0,0,0};
    inIn.read(reinterpret_cast<char *>(buf), 4);
    m_ctr+=4;
    return ((buf[0] << 0)  |
            (buf[1] << 8)  |
            (buf[2] << 16) |
            (buf[3] << 24));
}

U8
MushcoreStreamUtil::U8Get(istream& inIn)
{
    char ch; // Should be U8
    inIn.get(ch);
    ++m_ctr;
    return ch;
}

void
MushcoreStreamUtil::Ignore(istream& inIn, U32 inSize)
{
    inIn.ignore(inSize);
    m_ctr+=inSize;
}

void
MushcoreStreamUtil::Get(istream& inIn, U8 *outBuffer, U32 inSize)
{
    inIn.read(reinterpret_cast<char *>(outBuffer), inSize);
    m_ctr+=inSize;
}

void
MushcoreStreamUtil::ZeroIndex(U32 inWhich)
{
    if (inWhich >= m_zero.size())
    {
        m_zero.resize(inWhich+1);
    }
    m_zero[inWhich]=m_ctr;
}

U32
MushcoreStreamUtil::GetIndex(U32 inWhich)
{
    if (inWhich >= m_zero.size())
    {
        throw "MushcoreStreamUtil::Request for uninitialised index";
    }
    return m_ctr-m_zero[inWhich];
}

void
MushcoreStreamUtil::ConsumeToIndex(istream& inIn, U32 inWhich, U32 inValue)
{
    int target=inValue-GetIndex(inWhich);
    if (target>0)
    {
        Ignore(inIn, target);
    }
}
