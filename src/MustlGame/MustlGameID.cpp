//%Header {
/*****************************************************************************
 *
 * File: src/MustlGame/MustlGameID.cpp
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
//%Header } iZe+PaQaOwh1+jk7g40gOQ
/*
 * $Id: MustlGameID.cpp,v 1.5 2006/06/01 15:39:56 southa Exp $
 * $Log: MustlGameID.cpp,v $
 * Revision 1.5  2006/06/01 15:39:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:20  southa
 * Mac release work
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
 * Revision 1.7  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:08:49  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.4  2002/12/29 20:59:56  southa
 * More build fixes
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

#include "MustlGameID.h"

#include "MustlGameSTL.h"

using namespace Mushware;
using namespace std;

MustlGameID::MustlGameID(const string& inStr) :
    m_clientRef(inStr)
{
}

MustlGameID::MustlGameID(MustlData& ioData)
{
    Unpack(ioData);
}

MustlGameID::~MustlGameID()
{
}

MustlID *
MustlGameID::Clone(void) const
{
    return new MustlGameID(*this);
}

void
MustlGameID::Pack(MustlData& ioData) const
{
    const string& clientName = m_clientRef.NameGet();
    
    U32 size=clientName.size();
    if (size > 255) size=255;
    ioData.BytePush(size);
    for (U32 i=0; i<size; ++i)
    {
        ioData.BytePush(clientName[i]);
    }
}

void
MustlGameID::Unpack(MustlData& ioData)
{
    string clientName = "";
    U32 size=ioData.MessageBytePop();
    for (U32 i=0; i<size; ++i)
    {
        clientName += ioData.MessageBytePop();
    }
    m_clientRef.NameSet(clientName);
}

void
MustlGameID::Print(ostream& ioOut) const
{
    ioOut << m_clientRef.NameGet();
}

void
MustlGameID::NameSuffixAdd(const string& inStr)
{
    m_clientRef.NameSet(m_clientRef.NameGet() + inStr);
}

