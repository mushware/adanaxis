//%includeGuardStart {
#ifndef GAMEEVENT_H
#define GAMEEVENT_H
//%includeGuardStart } UEcZVIFbR3skg9cYgm/VwQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameEvent.h
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
//%Header } Yj1zCYqquAGdgvMxW/VKUg
/*
 * $Id: GameEvent.h,v 1.16 2006/06/01 15:38:57 southa Exp $
 * $Log: GameEvent.h,v $
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
 * Revision 1.12  2003/10/07 22:40:05  southa
 * Created MeshMover
 *
 * Revision 1.11  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.10  2003/10/04 12:22:59  southa
 * File renaming
 *
 * Revision 1.9  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:43  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.3  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/21 16:09:04  southa
 * InfernalTypeRace state tweaks
 *
 * Revision 1.1  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 */

#include "mushMushcore.h"

class GameEvent
{
public:
    virtual ~GameEvent() {}
protected:
    GameEvent() {}
};

class GameEventReward : public GameEvent
{
public:
    explicit GameEventReward(const std::string& inName) { m_name = inName; }
    const std::string& NameGet(void) const { return m_name; }
private:
    std::string m_name;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
