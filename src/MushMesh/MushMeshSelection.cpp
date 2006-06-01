//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshSelection.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } 8ARcwQmmxUqGXageKHfmqw
/*
 * $Id: MushMeshSelection.cpp,v 1.3 2005/05/19 13:02:11 southa Exp $
 * $Log: MushMeshSelection.cpp,v $
 * Revision 1.3  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.2  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/20 13:05:57  southa
 * Created
 *
 */

#include "MushMeshSelection.h"
//%outOfLineFunctions {
void
MushMeshSelection::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "start=" << start << ", ";
    ioOut << "stride=" << stride << ", ";
    ioOut << "size=" << size;
    ioOut << "]";
}
//%outOfLineFunctions } paTFObkZeEk2ziQvG69Lyw
