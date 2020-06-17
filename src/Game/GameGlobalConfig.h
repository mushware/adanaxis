//%includeGuardStart {
#ifndef GAMEGLOBALCONFIG_H
#define GAMEGLOBALCONFIG_H
//%includeGuardStart } n9Hbux6ERNRBEFquBjwALA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameGlobalConfig.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } z6A3vs+USNDdWRIhITQK/w
/*
 * $Id: GameGlobalConfig.h,v 1.16 2006/06/01 15:38:57 southa Exp $
 * $Log: GameGlobalConfig.h,v $
 * Revision 1.16  2006/06/01 15:38:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.13  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.12  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.11  2003/08/21 23:08:45  southa
 * Fixed file headers
 *
 * Revision 1.10  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.9  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.8  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.7  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
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

#include "mushMushcore.h"

class GameGlobalConfig : public MushcoreConfig
{
public:
    static GameGlobalConfig& Sgl(void) {return *((m_instance==NULL)?m_instance=new GameGlobalConfig:m_instance);}

private:
    static GameGlobalConfig *m_instance;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
