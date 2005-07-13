//%includeGuardStart {
#ifndef MUSHCOREUTIL_H
#define MUSHCOREUTIL_H
//%includeGuardStart } HMEpYR5TuOxF4EVwqj2pWA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreUtil.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } p0lCEz9EKwWFMt2/eD0agg
/*
 * $Id: MushcoreUtil.h,v 1.22 2005/07/06 19:08:27 southa Exp $
 * $Log: MushcoreUtil.h,v $
 * Revision 1.22  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.21  2005/07/04 15:59:01  southa
 * Adanaxis work
 *
 * Revision 1.20  2005/06/30 16:29:25  southa
 * Adanaxis work
 *
 * Revision 1.19  2005/06/14 13:25:34  southa
 * Adanaxis work
 *
 * Revision 1.18  2005/05/19 13:02:17  southa
 * Mac release work
 *
 * Revision 1.17  2005/05/18 15:53:27  southa
 * Made buildable using gcc 4.0/Mac OS X 10.4
 *
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
    static const Mushware::tVal RandomVal(const Mushware::tVal inMin, const Mushware::tVal inMax);
    
    template<class T> static void Constrain(T& ioValue, const T& inLowLim, const T& inHighLim);
    template<class T> static Mushware::U32 CountMatchesInSortedUnique(const std::vector<T>& inA, const std::vector<T>& inB, Mushware::tSize inLimit);
    
    static std::string LogTimeString(void);
    static void BreakpointFunction(void);
    static void BoundaryThrow(Mushware::U32 inValue, Mushware::U32 inLimit);
    static void BoundaryThrow(Mushware::U32 inValue1, Mushware::U32 inLimit1, Mushware::U32 inValue2, Mushware::U32 inLimit2);
    static void BoundsCheck(Mushware::U32 inValue, Mushware::U32 inLimit);
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

inline void
MushcoreUtil::BoundsCheck(Mushware::U32 inValue, Mushware::U32 inLimit)
{
    if (inValue > inLimit)
    {
        BoundaryThrow(inValue, inLimit);
    }
}

template<class T>
inline void
MushcoreUtil::Constrain(T& ioValue, const T& inLowLim, const T& inHighLim)
{
    if (ioValue < inLowLim)
    {
        ioValue = inLowLim;
    }
    else if (ioValue > inHighLim)
    {
        ioValue = inHighLim;
    }
}

template<class T>
inline Mushware::U32
MushcoreUtil::CountMatchesInSortedUnique(const std::vector<T>& inA, const std::vector<T>& inB, Mushware::tSize inLimit)
{
    Mushware::U32 retVal = 0;
    Mushware::tSize aSize = inA.size();
    Mushware::tSize bSize = inB.size();
    
    Mushware::tSize i=0;
    Mushware::tSize j=0;

    for (; i < aSize && j < bSize; )
    {
        if (inA[i] == inB[j])
        {
            ++retVal;
            if (retVal >= inLimit) break;
            ++i;
            ++j;
        }
        else if (inA[i] > inB[j])
        {
            ++j;
        }
        else
        {
            ++i;
        }
    }
    MUSHCOREASSERT(retVal <= inLimit);
    return retVal;
}


//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
