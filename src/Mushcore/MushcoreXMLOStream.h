//%includeGuardStart {
#ifndef MUSHCOREXMLOSTREAM_H
#define MUSHCOREXMLOSTREAM_H
//%includeGuardStart } bPT5GEbKVMd5EIUcx4WzZA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLOstream.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } loPhY3Ka3xrO9I8KESgPPA
/*
 * $Id: MushcoreXMLOStream.h,v 1.3 2003/09/21 09:56:38 southa Exp $
 * $Log: MushcoreXMLOStream.h,v $
 * Revision 1.3  2003/09/21 09:56:38  southa
 * Re-added
 *
 * Revision 1.1  2003/09/21 09:51:09  southa
 * Stream autogenerators
 *
 */

#include "MushcoreStandard.h"
#include "MushcoreXMLStream.h"
#include "MushcoreUtil.h"

class MushcoreXMLOStream : public MushcoreXMLStream
{
public:
    explicit MushcoreXMLOStream(std::ostream& inPStream);
    std::ostream& OStreamGet() { return m_pStream; }
    
private:
    std::ostream& m_pStream;
};

template<class T>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const T& inObj)
{
    ioOut.OStreamGet() << inObj;
    return ioOut;
}

template<>
inline MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const std::string& inStr)
{
    ioOut.OStreamGet() << MushcoreUtil::XMLMetaInsert(inStr);
    return ioOut;
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
