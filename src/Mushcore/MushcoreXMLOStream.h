//%includeGuardStart {
#ifndef MUSHCOREXMLOSTREAM_H
#define MUSHCOREXMLOSTREAM_H
//%includeGuardStart } bPT5GEbKVMd5EIUcx4WzZA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLOStream.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } f2F46K8LXdioFTimaPJHmQ
/*
 * $Id: MushcoreXMLOstream.h,v 1.1 2003/09/21 09:51:09 southa Exp $
 * $Log: MushcoreXMLOstream.h,v $
 * Revision 1.1  2003/09/21 09:51:09  southa
 * Stream autogenerators
 *
 */

#include "MushcoreStandard.h"
#include "MushcoreXMLStream.h"

//:generate
class MushcoreXMLOStream
{
public:
    MushcoreXMLOStream();
    virtual ~MushcoreXMLOStream();
    
    std::ostream& OStreamGet() { return *m_pStream; }
    void Print(std::ostream& ioOut) const;
    
private:
    std::ostream *m_pStream;

//%classPrototypes {
public:
//%classPrototypes } 0ImSRh0/JBpOMwe5g8vGcA
};

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const T& inObj)
{
    ioOut.OStreamGet() << inObj;
    return ioOut;
}

inline std::ostream&
operator<<(std::ostream& ioOut, const MushcoreXMLOStream& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
