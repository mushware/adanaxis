//%includeGuardStart {
#ifndef MUSTLIDNULL_H
#define MUSTLIDNULL_H
//%includeGuardStart } Kb4yOVq0bljErBTtDHuRNA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlIDNull.h
 *
 * Copyright Andy Southgate 2002-2004
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } e8KmJkbRUoKCFhtQrweoRw
/*
 * $Id: MustlIDNull.h,v 1.5 2003/09/17 19:40:37 southa Exp $
 * $Log: MustlIDNull.h,v $
 * Revision 1.5  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:09:26  southa
 * Fixed file headers
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

#include "MustlID.h"

class MustlData;

class MustlIDNull : public MustlID
{
public:
    virtual ~MustlIDNull();
    virtual MustlID *Clone(void) const;
    virtual void Pack(MustlData& ioData) const;
    virtual void Unpack(MustlData& ioData);
    virtual void Print(std::ostream& ioOut) const;

private:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
