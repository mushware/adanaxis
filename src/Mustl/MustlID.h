//%includeGuardStart {
#ifndef MUSTLID_H
#define MUSTLID_H
//%includeGuardStart } G1vJoUq0DG+kQKGx0TIkuA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlID.h
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } FJ9Pe6IbLAR5tpCLhvLiFg
/*
 * $Id: MustlID.h,v 1.5 2003/08/21 23:09:25 southa Exp $
 * $Log: MustlID.h,v $
 * Revision 1.5  2003/08/21 23:09:25  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/07 17:13:44  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlStandard.h"

class MustlData;

class MustlID
{
public:
    virtual ~MustlID() {}
    virtual MustlID *Clone(void) const = 0;
    virtual void Pack(MustlData& ioData) const = 0;
    virtual void Unpack(MustlData& ioData) = 0;
    virtual void Print(std::ostream& ioOut) const = 0;
    
private:
};

std::ostream& operator<<(std::ostream &ioOut, const MustlID& inObj);

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
