//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlID.cpp
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Hnu2PaLs15Ug3dGSHnOwBQ
/*
 * $Id: MustlID.cpp,v 1.5 2003/08/21 23:09:25 southa Exp $
 * $Log: MustlID.cpp,v $
 * Revision 1.5  2003/08/21 23:09:25  southa
 * Fixed file headers
 *
 * Revision 1.4  2002/12/29 20:59:59  southa
 * More build fixes
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 */

#include "MustlID.h"

using namespace Mustl;
using namespace std;

ostream&
operator<<(ostream &ioOut, const MustlID& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}
