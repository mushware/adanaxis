//%includeGuardStart {
#ifndef MUSTLGAMEID_H
#define MUSTLGAMEID_H
//%includeGuardStart } MiK13pln1khdc8vXGogH7w
//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameID.h
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
//%Header } gn1kOYIxOQfdfeZV4bfPDw
/*
 * $Id: MustlGameID.h,v 1.7 2006/06/01 20:13:01 southa Exp $
 * $Log: MustlGameID.h,v $
 * Revision 1.7  2006/06/01 20:13:01  southa
 * Initial texture caching
 *
 * Revision 1.6  2006/06/01 15:39:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/06 22:42:04  southa
 * Include fixes
 *
 * Revision 1.1  2003/10/06 22:22:38  southa
 * Moved from Game to MustlGame
 *
 * Revision 1.8  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.7  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
 * Revision 1.6  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.5  2003/01/09 14:57:02  southa
 * Created Mushcore
 *
 * Revision 1.4  2002/12/29 20:30:54  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.3  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/12 14:00:39  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/09 23:59:58  southa
 * Network control
 *
 */

#include "mushMushcore.h"
#include "mushMedia.h"

#include "MustlGameClient.h"
#include "MustlID.h"

class MustlGameID : public MustlID
{
public:
    explicit MustlGameID(const std::string& inStr);
    explicit MustlGameID(MustlData& ioData);
    virtual ~MustlGameID();
    virtual MustlID *Clone(void) const;
    virtual void Pack(MustlData& ioData) const;
    virtual void Unpack(MustlData& ioData);
    virtual void Print(std::ostream& ioOut) const;

    void NameSuffixAdd(const std::string& inStr);
    const MushcoreDataRef<MustlGameClient>& DataRefGet(void) const { return m_clientRef; }
    
private:
    MushcoreDataRef<MustlGameClient> m_clientRef;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
