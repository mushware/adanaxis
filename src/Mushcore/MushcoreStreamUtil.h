//%includeGuardStart {
#ifndef MUSHCORESTREAMUTIL_H
#define MUSHCORESTREAMUTIL_H
//%includeGuardStart } r7wM6Gh/tuQSO/Ut3wio6Q
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreStreamUtil.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Vax3khZeAGMQfnMcs+HF0A
/*
 * $Id: MushcoreStreamUtil.h,v 1.6 2003/09/17 19:40:36 southa Exp $
 * $Log: MushcoreStreamUtil.h,v $
 * Revision 1.6  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:18  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.3  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
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
    MushcoreStreamUtil() : m_ctr(0) {}
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
    Mushware::S32 m_ctr;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
