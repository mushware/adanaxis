//%includeGuardStart {
#ifndef MUSHCOREXMLCONSUMER_H
#define MUSHCOREXMLCONSUMER_H
//%includeGuardStart } Om7O0WB7UcmsV/6FWuIz6g
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreXMLConsumer.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } npITgZT+9cJbbZswb9CV2A
/*
 * $Id: MushcoreXMLConsumer.h,v 1.3 2003/09/21 23:15:08 southa Exp $
 * $Log: MushcoreXMLConsumer.h,v $
 * Revision 1.3  2003/09/21 23:15:08  southa
 * XML input stream improvements
 *
 * Revision 1.2  2003/09/21 18:49:41  southa
 * XML input stream work
 *
 * Revision 1.1  2003/09/21 15:57:31  southa
 * XML autogenerator work
 *
 */

#include "MushcoreStandard.h"

class MushcoreXMLIStream;
class MushcoreXMLOStream;

class MushcoreXMLConsumer
{
public:
    virtual void AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr) = 0;
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const = 0;
    virtual const char *AutoNameGet(void) const = 0;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
