//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLOStream.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } SW5J6spEp5jvZeyT03E1UA
/*
 * $Id: MushcoreXMLOStream.cpp,v 1.5 2003/09/22 19:40:36 southa Exp $
 * $Log: MushcoreXMLOStream.cpp,v $
 * Revision 1.5  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.4  2003/09/21 11:46:11  southa
 * XML input stream
 *
 * Revision 1.3  2003/09/21 09:56:39  southa
 * Re-added
 *
 * Revision 1.1  2003/09/21 09:51:09  southa
 * Stream autogenerators
 *
 */

#include "MushcoreXMLOStream.h"

MushcoreXMLOStream::MushcoreXMLOStream(std::ostream& inStream) :
    m_pStream(inStream),
    m_tagStr("obj")
{
}
