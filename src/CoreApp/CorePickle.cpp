/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CorePickle.cpp,v 1.2 2002/05/26 16:35:07 southa Exp $
 * $Log: CorePickle.cpp,v $
 * Revision 1.2  2002/05/26 16:35:07  southa
 * CoreXML work
 *
 * Revision 1.1  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 */

#include "CorePickle.h"
#include "CoreUtil.h"
#include "CoreException.h"
#include "CoreXML.h"

void
CorePickle::Unpickle(const string& inFilename)
{
    ifstream in(CoreUtil::TranslateFilename(inFilename).c_str());
    if (!in) throw(LoaderFail(inFilename, "Could not open file"));
    CoreXML xml(in, inFilename);
    Unpickle(xml);
}
