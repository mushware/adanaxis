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
 * $Id: CorePickle.cpp,v 1.7 2002/10/22 20:41:59 southa Exp $
 * $Log: CorePickle.cpp,v $
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/26 16:35:07  southa
 * CoreXML work
 *
 * Revision 1.1  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 */

#include "CorePickle.h"
#include "CoreException.h"
#include "CoreUtil.h"
#include "CoreXML.h"

using namespace Mushware;

void
CorePickle::Unpickle(const string& inFilename)
{
    ifstream in(CoreUtil::TranslateFilename(inFilename).c_str());
    if (!in) throw(LoaderFail(inFilename, "Could not open file"));
    CoreXML xml(in, inFilename);
    Unpickle(xml);
}
