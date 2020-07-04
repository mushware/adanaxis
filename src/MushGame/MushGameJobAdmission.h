//%includeGuardStart {
#ifndef MUSHGAMEJOBADMISSION_H
#define MUSHGAMEJOBADMISSION_H
//%includeGuardStart } yu6AJJDmPLuXA0KQ3WLErg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobAdmission.h
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
//%Header } B8KC8/+sL/tMfXVwcTYhqQ
/*
 * $Id: MushGameJobAdmission.h,v 1.4 2006/06/01 15:39:22 southa Exp $
 * $Log: MushGameJobAdmission.h,v $
 * Revision 1.4  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 */

#include "MushGameStandard.h"

#include "MushGameJob.h"

#include "MushGameMessageJoinRequest.h"

//:xml1base MushGameJob
//:generate standard ostream xml1
class MushGameJobAdmission : public MushGameJob
{
public:
    explicit MushGameJobAdmission(const std::string& inID = "");
    virtual ~MushGameJobAdmission() {}
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void JoinRequestConsume(MushGameLogic& ioLogic, const MushGameMessageJoinRequest& inMessage);
    
private:
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameJobAdmission& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 5rhtAOjHv4oNL6qR77ANeQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw

