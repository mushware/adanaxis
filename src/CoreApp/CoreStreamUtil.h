#ifndef CORESTREAMUTIL_H
#define CORESTREAMUTIL_H
#ifndef STREAMUTIL_H
#define STREAMUTIL_H
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
 * $Id: CoreStreamUtil.h,v 1.5 2002/10/22 20:41:59 southa Exp $
 * $Log: CoreStreamUtil.h,v $
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
    Mushware::U32 BigEndianU32Get(Mushware::u8istream& inIn);
    Mushware::U32 LittleEndianU32Get(Mushware::u8istream& inIn);
    Mushware::U8 U8Get(Mushware::u8istream& inIn);
    void Get(Mushware::u8istream& inIn, Mushware::U8 *outBuffer, Mushware::U32 inSize);
    void Ignore(Mushware::u8istream &inIn, Mushware::U32 inSize);
    void ZeroIndex(Mushware::U32 inWhich);
    Mushware::U32 GetIndex(Mushware::U32 inWhich);
    void ConsumeToIndex(Mushware::u8istream& inIn, Mushware::U32 inWhich, Mushware::U32 inValue);
    
private:
    std::vector<int> m_zero;
    int m_ctr;
};
#endif
#endif
