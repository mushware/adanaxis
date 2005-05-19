//%includeGuardStart {
#ifndef GLFONTREF_H
#define GLFONTREF_H
//%includeGuardStart } wUK6hMbgy/tpf0fSBXIhYw
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLFontRef.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } r1FHucV07VBBiradUIkD9g
/*
* $Id: GLFontRef.h,v 1.13 2005/03/25 19:13:48 southa Exp $
* $Log: GLFontRef.h,v $
* Revision 1.13  2005/03/25 19:13:48  southa
* GameDialogue work
*
* Revision 1.12  2004/01/06 20:46:49  southa
* Build fixes
*
* Revision 1.11  2004/01/02 21:13:05  southa
* Source conditioning
*
* Revision 1.10  2003/10/04 15:32:08  southa
* Module split
*
* Revision 1.9  2003/09/17 19:40:29  southa
* Source conditioning upgrades
*
* Revision 1.8  2003/08/21 23:08:21  southa
* Fixed file headers
*
* Revision 1.7  2003/01/11 13:03:11  southa
* Use Mushcore header
*
* Revision 1.6  2002/12/29 20:30:52  southa
* Work for gcc 3.1 build
*
* Revision 1.5  2002/12/20 13:17:35  southa
* Namespace changes, licence changes and source conditioning
*
* Revision 1.4  2002/10/22 20:42:00  southa
* Source conditioning
*
* Revision 1.3  2002/08/27 08:56:19  southa
* Source conditioning
*
* Revision 1.2  2002/08/09 17:09:02  southa
* InfernalDialogue added
*
* Revision 1.1  2002/08/08 13:39:09  southa
* Text rendering
*
*/

#include "mushMushcore.h"

class GLFont;

//:generate virtual basic standard ostream xml1
class GLFontRef : public MushcoreVirtualObject
{
public:
    GLFontRef(): m_fontPtr(NULL) {}
    virtual ~GLFontRef() {}
    
    explicit GLFontRef(const std::string& inName, Mushware::tVal inSize=1.0): m_name(inName), m_size(inSize), m_fontPtr(NULL) {}
    void NameSet(const std::string& inName) {m_name=inName; m_fontPtr=NULL;}
    const std::string& NameGet(void) const {return m_name;}
    Mushware::tVal SizeGet(void) const {return m_size;}
    GLFont *FontGet(void) const;
    bool Exists(void) const;

private:
    void GetReference(void) const;
    std::string m_name;
    Mushware::tVal m_size;
    mutable GLFont *m_fontPtr; //:ignore
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const GLFontRef& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } BnRK317IXs8murPqdpFesg
};
//%inlineHeader {

inline bool
operator==(const GLFontRef& inA, const GLFontRef& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const GLFontRef& inA, const GLFontRef& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const GLFontRef& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } skSh5zwrtoCfCe0Hff67ww
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
