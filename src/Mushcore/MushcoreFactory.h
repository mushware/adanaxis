//%includeGuardStart {
#ifndef MUSHCOREFACTORY_H
#define MUSHCOREFACTORY_H
//%includeGuardStart } Z+MZF0GNXp9ZSAZTknuPjg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreFactory.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } PCqvrnn/p0THwedPuNPI9g
/*
 * $Id: MushcoreFactory.h,v 1.7 2004/10/31 23:34:07 southa Exp $
 * $Log: MushcoreFactory.h,v $
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
    void TemplatesPrint(std::ostream& ioOut) const;
    void TypesPrint(std::ostream& ioOut) const;
    
    static MushcoreScalar XMLTemplatePrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static MushcoreScalar XMLTypesPrint(MushcoreCommand& ioCommand, MushcoreEnv &ioEnv);
    static void Install(void);
private:
    tFactoryMap m_factories;
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
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
