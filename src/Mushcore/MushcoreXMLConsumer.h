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
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"

class MushcoreXMLIStream;

class MushcoreXMLConsumer
{
public:
    virtual void XMLDataProcess(MushcoreXMLIStream& ioIn) = 0;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
