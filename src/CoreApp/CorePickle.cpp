/*
 * $Id: CorePickle.cpp,v 1.1 2002/05/24 16:23:10 southa Exp $
 * $Log: CorePickle.cpp,v $
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
