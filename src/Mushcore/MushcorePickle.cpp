/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MushcorePickle.cpp,v 1.3 2003/01/20 12:23:23 southa Exp $
 * $Log: MushcorePickle.cpp,v $
 * Revision 1.3  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
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
 * MushcoreXML work
 *
 * Revision 1.1  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 */

#include "MushcorePickle.h"

#include "MushcoreFail.h"
#include "MushcoreUtil.h"
#include "MushcoreXML.h"

#include "MushcoreSTL.h"

using namespace Mushware;
using namespace std;

void
MushcorePickle::Unpickle(const string& inFilename)
{
    ifstream in(MushcoreUtil::TranslateFilename(inFilename).c_str());
    if (!in) throw(MushcoreFileFail(inFilename, "Could not open file"));
    MushcoreXML xml(in, inFilename);
    Unpickle(xml);
}
