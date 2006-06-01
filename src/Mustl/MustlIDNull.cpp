//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlIDNull.cpp
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
//%Header } SXBZkKnvuLtatO5Lug6g2A
/*
 * $Id: MustlIDNull.cpp,v 1.8 2005/05/19 13:02:18 southa Exp $
 * $Log: MustlIDNull.cpp,v $
 * Revision 1.8  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:26  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/07 17:13:45  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.3  2002/12/29 20:59:59  southa
 * More build fixes
 *
 * Revision 1.2  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlIDNull.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

MustlIDNull::~MustlIDNull()
{
}

MustlID *
MustlIDNull::Clone(void) const
{
    return new MustlIDNull(*this);
}

void
MustlIDNull::Pack(MustlData& ioData) const
{
}

void
MustlIDNull::Unpack(MustlData& ioData)
{
}

void
MustlIDNull::Print(ostream& ioOut) const
{
    ioOut << "Unknown";
}
