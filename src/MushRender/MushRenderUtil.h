//%includeGuardStart {
#ifndef MUSHRENDERUTIL_H
#define MUSHRENDERUTIL_H
//%includeGuardStart } g/RC6XSRPyl9Augpd+6sCw
//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderUtil.h
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
//%Header } etMsJdwyQsBJcIrhF/whvg
/*
 * $Id: MushRenderUtil.h,v 1.2 2006/06/01 15:39:39 southa Exp $
 * $Log: MushRenderUtil.h,v $
 * Revision 1.2  2006/06/01 15:39:39  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/04 15:59:01  southa
 * Adanaxis work
 *
 */

#include "MushRenderStandard.h"

class MushRenderUtil
{
public:
    template <class T, Mushware::U32 D> static void Transform(std::vector< MushMeshVector<T, D> >& ioDest, const std::vector< MushMeshVector<T, D> >& inSrc, const MushMeshMattress<T, D>& inTransform);
private:
};

template <class T, Mushware::U32 D>
inline void
MushRenderUtil::Transform(std::vector< MushMeshVector<T, D> >& ioDest, const std::vector< MushMeshVector<T, D> >& inSrc, const MushMeshMattress<T, D>& inTransform)
{
    Mushware::tSize srcSize = inSrc.size();
    if (ioDest.size() < srcSize)
    {
        ioDest.resize(srcSize);
    }
    
    for (Mushware::U32 i=0; i<srcSize; ++i)
    {
        ioDest[i] = inTransform * inSrc[i];
    }
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
