//%includeGuardStart {
#ifndef MUSHCOREAPPHANDLER_H
#define MUSHCOREAPPHANDLER_H
//%includeGuardStart } lynq8Xlgkl/Jh0MiJI5jyw
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAppHandler.h
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
//%Header } pK/Fv8szf7U/JZnGo+RF+w
/*
 * $Id: MushcoreAppHandler.h,v 1.11 2006/07/31 11:01:39 southa Exp $
 * $Log: MushcoreAppHandler.h,v $
 * Revision 1.11  2006/07/31 11:01:39  southa
 * Music and dialogues
 *
 * Revision 1.10  2006/06/01 15:39:41  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:14  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.7  2003/10/04 12:23:08  southa
 * File renaming
 *
 * Revision 1.6  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:04  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.3  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.2  2003/01/11 13:03:16  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:05  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 * Revision 1.2  2002/05/30 14:41:13  southa
 * InfernalData and loadtilemap command
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/21 22:07:52  southa
 * Initial wrangle application handler
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreVirtualObject.h"

class MushcoreAppSignal;

//:generate virtual standard ostream xml1
class MushcoreAppHandler : public MushcoreVirtualObject
{
public:
    virtual ~MushcoreAppHandler() {};
    static MushcoreAppHandler& Sgl(void) {return *((m_instance==NULL)?m_instance=new MushcoreAppHandler:m_instance);}
    virtual void Mutate(MushcoreAppHandler *inAppHandler);
    virtual void Initialise(void);
    virtual void MainLoop(void);
    virtual void Idle(void);
    virtual void Signal(const MushcoreAppSignal& inSignal);
    
protected:
    MushcoreAppHandler() {};
    
private:
    static MushcoreAppHandler *m_instance;
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
operator<<(std::ostream& ioOut, const MushcoreAppHandler& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } QyjywdqKk4N5Onhdm+xaiA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
