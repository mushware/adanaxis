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
 * $Id: GameGlobalConfig.cpp,v 1.6 2002/10/22 20:42:04 southa Exp $
 * $Log: GameGlobalConfig.cpp,v $
 * Revision 1.6  2002/10/22 20:42:04  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "GameGlobalConfig.h"

using namespace Mushware;

GameGlobalConfig *GameGlobalConfig::m_instance=NULL;
