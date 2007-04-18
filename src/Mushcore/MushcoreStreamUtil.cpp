//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreStreamUtil.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } sVuykpFHXo5hnT2P5EreRg
/*
 * $Id: MushcoreStreamUtil.cpp,v 1.9 2006/06/01 15:39:47 southa Exp $
 * $Log: MushcoreStreamUtil.cpp,v $
 * Revision 1.9  2006/06/01 15:39:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:16  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:17  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
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

#include "MushcoreFail.h"

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
        throw(MushcoreLogicFail("Request for uninitialised MushcoreStreamUtil index"));
    }
    if (m_ctr < m_zero[inWhich])
    {
        throw(MushcoreLogicFail("MushcoreStreamUtil index is beyond current position"));
    }        
    return m_ctr - m_zero[inWhich];
}

void
MushcoreStreamUtil::ConsumeToIndex(istream& inIn, U32 inWhich, U32 inValue)
{
    S32 target=inValue - GetIndex(inWhich);
    if (target > 0)
    {
        Ignore(inIn, target);
    }
}
