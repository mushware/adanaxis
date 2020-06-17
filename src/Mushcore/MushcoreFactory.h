//%includeGuardStart {
#ifndef MUSHCOREFACTORY_H
#define MUSHCOREFACTORY_H
//%includeGuardStart } Z+MZF0GNXp9ZSAZTknuPjg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFactory.h
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
//%Header } oSMRw36Y9hqzTpcGdadl7A
/*
 * $Id: MushcoreFactory.h,v 1.12 2006/06/01 15:39:43 southa Exp $
 * $Log: MushcoreFactory.h,v $
 * Revision 1.12  2006/06/01 15:39:43  southa
 * DrawArray verification and fixes
 *
 * Revision 1.11  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.10  2005/06/21 13:10:52  southa
 * MushGame work
 *
 * Revision 1.9  2005/05/19 13:02:15  southa
 * Mac release work
 *
 * Revision 1.8  2005/02/10 12:34:18  southa
 * Template fixes
 *
 * Revision 1.7  2004/10/31 23:34:07  southa
 * Hypercube rendering test
 *
 * Revision 1.6  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.5  2004/01/08 16:06:11  southa
 * XML fixes
 *
 * Revision 1.4  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 * Revision 1.3  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.2  2004/01/02 21:13:12  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 */

#include "MushcoreStandard.h"

#include "MushcoreSingleton.h"
#include "MushcoreScalar.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreVirtualObject;

//:generate ostream
class MushcoreFactory : public MushcoreSingleton<MushcoreFactory>
{
public:
    typedef MushcoreVirtualObject *(* tFactoryPtr)(void) ;
    typedef std::map<std::string, tFactoryPtr> tFactoryMap;

    virtual ~MushcoreFactory () {}
    
    void FactoryAdd(const std::string& inName, tFactoryPtr inPtr);
    MushcoreVirtualObject *ObjectCreate(const std::string& inName) const;
    bool Exists(const std::string& inName) const;
    
    void TemplatesPrint(std::ostream& ioOut) const;
    void TypesPrint(std::ostream& ioOut) const;
    
    static MushcoreScalar XMLTemplatePrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar XMLTypesPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static void Install(void);
private:
    tFactoryMap m_factories;
//%classPrototypes {
public:
    virtual void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } b86DSDsq8lQQbiM0rrNtkg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreFactory& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LqoVPNELHsXwHf/xHX8fpA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
