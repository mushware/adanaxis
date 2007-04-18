//%includeGuardStart {
#ifndef MUSHCOREFACTORY_H
#define MUSHCOREFACTORY_H
//%includeGuardStart } Z+MZF0GNXp9ZSAZTknuPjg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFactory.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jaB5d7XGVKzF/KEVlI2Jdw
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
