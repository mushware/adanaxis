//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Util.cpp
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
//%Header } V62Lt+D2xzRsWTfsB/etng
/*
 * $Id$
 * $Log$
 */

#include "MushMesh4Util.h"

#include "MushMeshMushcoreIO.h"
#include "MushMeshSTL.h"

using namespace Mushware;
using namespace std;

void 
MushMesh4Util::NullFacetsRemove(MushMesh4Mesh& ioMesh, Mushware::U32 inFaceNum)
{
    bool modified = false;
    MushMesh4Face& faceRef = ioMesh.FaceWRef(inFaceNum);
    
    MushMesh4Face::tVertexList& srcVertexListRef = faceRef.VertexListWRef();
    U32 srcVertexListSize = srcVertexListRef.size();
    MushMesh4Face::tVertexGroupSize& srcGroupSizeRef = faceRef.VertexGroupSizeWRef();
    MushMesh4Face::tVertexList newVertexList;
    MushMesh4Face::tVertexGroupSize newGroupSizeList;
    
    U32 srcVertexNum = 0;
    for (U32 i=0; i<srcGroupSizeRef.size(); ++i)
    {
        U32 srcGroupSize = srcGroupSizeRef[i];
        U32 newGroupSize = 0;
        for (U32 j=0; j < srcGroupSize; ++j)
        {
            U32 vertNum = srcVertexNum + j;
            U32 otherVertNum = srcVertexNum + ((j + 1) % srcGroupSize);
            
            if (vertNum >= srcVertexListSize || otherVertNum >= srcVertexListSize)
            {
                throw MushcoreDataFail("Vertex overrun in NullFacetsRemove");
            }
            
            if (srcVertexListRef[vertNum] == srcVertexListRef[otherVertNum])
            {
                modified = true;
            }
            else
            {
                newVertexList.push_back(srcVertexListRef[vertNum]);
                ++newGroupSize;
            }
        }
        if (newGroupSize > 2)
        {
#if 0
            if (newGroupSize == srcGroupSize)
            {
                MushcoreLog::Sgl().InfoLog() << "Keeping facet size " << srcGroupSize << endl;
            }
            else
            {
                MushcoreLog::Sgl().InfoLog() << "Reducing facet size " << srcGroupSize << " to " << newGroupSize << endl;
            }
#endif       
            newGroupSizeList.push_back(newGroupSize);
        }
        else if (newGroupSize == 2)
        {
            MushcoreLog::Sgl().WarningLog() << "Discarding two point facet" << endl;
            newVertexList.resize(newVertexList.size() - 2);
        }
        else if (newGroupSize == 1)
        {
            MushcoreLog::Sgl().ErrorLog() << "Discarding rogue single point facet" << endl;
            newVertexList.resize(newVertexList.size() - 1);
        }
        else
        {
            // Discard entire facet
            // MushcoreLog::Sgl().InfoLog() << "Discarding facet of size " << srcGroupSize << endl;
        }
        srcVertexNum += srcGroupSize;
    }
    
#if 0
    cout << "srcVertexListRef=" << srcVertexListRef << endl;
    cout << "srcGroupSizeRef=" << srcGroupSizeRef << endl;
    cout << "newVertexList=" << newVertexList << endl;
    cout << "newGroupSizeList=" << newGroupSizeList << endl;
#endif
    
    if (modified)
    {
        
        srcVertexListRef = newVertexList;
        srcGroupSizeRef = newGroupSizeList;
        
        faceRef.AllTouch();
        // MushcoreLog::Sgl().InfoLog() << "Wrote modified face" << endl;

    }
}
