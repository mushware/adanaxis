#ifndef MUSHCORESTREAMUTIL_H
#define MUSHCORESTREAMUTIL_H
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
 * $Id: MushcoreStreamUtil.h,v 1.2 2003/01/11 13:03:17 southa Exp $
 * $Log: MushcoreStreamUtil.h,v $
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
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

#include "MushcoreStandard.h"

class MushcoreStreamUtil
{
public:
    MushcoreStreamUtil():m_ctr(0) {}
    Mushware::U32 BigEndianU32Get(std::istream& inIn);
    Mushware::U32 LittleEndianU32Get(std::istream& inIn);
    Mushware::U8 U8Get(std::istream& inIn);
    void Get(std::istream& inIn, Mushware::U8 *outBuffer, Mushware::U32 inSize);
    void Ignore(std::istream &inIn, Mushware::U32 inSize);
    void ZeroIndex(Mushware::U32 inWhich);
    Mushware::U32 GetIndex(Mushware::U32 inWhich);
    void ConsumeToIndex(std::istream& inIn, Mushware::U32 inWhich, Mushware::U32 inValue);
    
private:
    std::vector<int> m_zero;
    int m_ctr;
};
#endif
