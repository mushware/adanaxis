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
 * $Id: GameView.cpp,v 1.3 2002/08/27 08:56:28 southa Exp $
 * $Log: GameView.cpp,v $
 * Revision 1.3  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:49:28  southa
 * Created
 *
 */

#include "GameView.h"

GameView::GameView():
    m_dimensions(GLRectangle(0,0,0,0)),
    m_lightingFactor(1.0),
    m_ambientLighting(0.3)
{
}