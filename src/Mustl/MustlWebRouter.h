//%includeGuardStart {
#ifndef MUSTLWEBROUTER_H
#define MUSTLWEBROUTER_H
//%includeGuardStart } FxZ53+ahTtTM9VAZ8dj+vA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlWebRouter.h
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
//%Header } nplUP55cF+jZ/oYUra9AcA
/*
 * $Id: MustlWebRouter.h,v 1.12 2006/06/01 15:39:55 southa Exp $
 * $Log: MustlWebRouter.h,v $
 * Revision 1.12  2006/06/01 15:39:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.10  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.9  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:09:33  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.5  2002/12/29 20:30:57  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.4  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.2  2002/12/12 18:38:26  southa
 * Mustl separation
 *
 * Revision 1.1  2002/12/12 14:00:27  southa
 * Created Mustl
 *
 * Revision 1.3  2002/11/25 10:43:28  southa
 * GameProtocol work
 *
 * Revision 1.2  2002/11/23 17:23:45  southa
 * Sleep in setup
 *
 * Revision 1.1  2002/11/06 14:16:57  southa
 * Basic web server
 *
 */

#include "MustlStandard.h"

#include "MustlMushcore.h"

class MustlLink;

class MustlWebRouter : public MushcoreSingleton<MustlWebRouter>
{
public:
    MustlWebRouter();

    void ReceiveAll(void);

protected:

private:
    enum
    {
        kTickPeriod=100,
        kMaxReceivesPerCall=20
    };

    Mustl::tMsec m_lastTickMsec;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
