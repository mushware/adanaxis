//%includeGuardStart {
#ifndef MUSHCOREUTIL_H
#define MUSHCOREUTIL_H
//%includeGuardStart } HMEpYR5TuOxF4EVwqj2pWA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreUtil.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } XWTplRc9rgj8oYPVlTvtrA
/*
 * $Id: MushcoreUtil.h,v 1.16 2005/04/11 23:31:41 southa Exp $
 * $Log: MushcoreUtil.h,v $
 * Revision 1.16  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 * Revision 1.15  2005/03/13 00:34:48  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.14  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 * Revision 1.13  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.12  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.11  2003/10/04 12:23:09  southa
 * File renaming
 *
 * Revision 1.10  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 * Revision 1.9  2003/09/29 21:48:37  southa
 * XML work
 *
 * Revision 1.8  2003/09/23 22:57:57  southa
 * XML vector handling
 *
 * Revision 1.7  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.6  2003/09/21 15:57:11  southa
 * XML autogenerator work
 *
 * Revision 1.5  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:19  southa
 * Fixed file headers
 *
 * Revision 1.3  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:08  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.8  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/27 12:58:43  southa
 * InfernalContract and global configs added
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 */

#include "MushcoreStandard.h"

class MushcoreUtil
{
public:
    static std::string TranslateFilename(const std::string& inStr);
    static std::string XMLMetaInsert(const std::string& inStr);
    static std::string XMLMetaRemove(const std::string& inStr);
    static bool XMLAttributeExtract(std::string& outTypeStr, const std::string& inTagData, const std::string& inAttrName);
    static std::istream *IStringStreamNew(const std::string& inStr);
    template<class T> static std::vector<T> ArrayToVector(const T inArray[], Mushware::U32 inSize);
    template<class T> static void VectorToArrayPad(T outArray[], const std::vector<T>& inVec, Mushware::U32 inSize, const T& inPadValue = T());
    
    
    static std::string MakeXMLSafe(const std::string& inStr);
    static std::string MakeWebSafe(const std::string& inStr);
    static Mushware::U32 MakeWebSafe(Mushware::U32 inValue) { return inValue; }
    static Mushware::tVal MakeWebSafe(Mushware::tVal inValue) { return inValue; }
    static std::string RemoveMeta(const std::string& inStr);
    static std::string InsertMeta(const std::string& inStr);

    static const Mushware::U32 RandomU32(const Mushware::U32 inMin, const Mushware::U32 inMax);
    
    static void BreakpointFunction(void);
};

template<class T>
inline std::vector<T>
MushcoreUtil::ArrayToVector(const T inArray[], Mushware::U32 inSize)
{
    std::vector<T> valueVec(inSize);
    for (Mushware::U32 i=0; i<inSize; ++i)
    {
        valueVec[i] = inArray[i];
    }
    return valueVec;
}

#if 0
template<class T>
inline void
MushcoreUtil::VectorToArrayPad(T outArray[], const std::vector<T>& inVec, Mushware::U32 inSize, const T& inPadValue)
{
    for (Mushware::U32 i=0; i<inSize; ++i)
    {
        outArray[i] = (i < inVec.size())?inVec[i]:inPadValue;
    }
}
#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
