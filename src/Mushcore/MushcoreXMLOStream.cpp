//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLOStream.cpp
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
//%Header } M8NLGaYU/nALZBDAkQ1h4A
/*
 * $Id: MushcoreXMLOStream.cpp,v 1.7 2004/01/02 21:13:14 southa Exp $
 * $Log: MushcoreXMLOStream.cpp,v $
 * Revision 1.7  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.6  2003/10/01 23:18:27  southa
 * XML object handling
 *
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
