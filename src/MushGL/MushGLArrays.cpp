//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLArrays.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } BnwhF/W+69tpBqr5BOOloA
/*
 *$Id: MushGLArrays.cpp,v 1.3 2006/06/01 15:39:16 southa Exp $
 * $Log: MushGLArrays.cpp,v $
 * Revision 1.3  2006/06/01 15:39:16  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.1  2004/03/07 12:05:56  southa
 * Rendering work
 *
 */

#include "MushGLArrays.h"

bool MushGLArrays::m_normalArrayState = true;
bool MushGLArrays::m_texCoordArrayState = true;
