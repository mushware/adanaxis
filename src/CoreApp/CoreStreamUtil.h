#ifndef CORESTREAMUTIL_H
#define CORESTREAMUTIL_H
#ifndef STREAMUTIL_H
#define STREAMUTIL_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: CoreStreamUtil.h,v 1.1 2002/07/02 09:24:10 southa Exp $
 * $Log: CoreStreamUtil.h,v $
 * Revision 1.1  2002/07/02 09:24:10  southa
 * Name changed to CoreStreamUtil
 *
 * Revision 1.3  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "CoreStandard.h"

class CoreStreamUtil
{
public:
    CoreStreamUtil():m_ctr(0) {}
    U32 BigEndianU32Get(u8istream& inIn);
    U32 LittleEndianU32Get(u8istream& inIn);
    U8 U8Get(u8istream& inIn);
    void Get(u8istream& inIn, U8 *outBuffer, tSize inSize);
    void Ignore(u8istream &inIn, tSize inSize);
    void ZeroIndex(tSize inWhich);
    tSize GetIndex(tSize inWhich);
    void ConsumeToIndex(u8istream& inIn, tSize inWhich, tSize inValue);
    
private:
    vector<int> m_zero;
    int m_ctr;
};
#endif
#endif
