#ifndef MUSTLID_H
#define MUSTLID_H
/*
 * $Id: MustlID.h,v 1.1 2002/12/07 18:32:15 southa Exp $
 * $Log: MustlID.h,v $
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "mushCore.h"

class MustlData;

class MustlID
{
public:
    virtual ~MustlID() {}
    virtual MustlID *Clone(void) const = 0;
    virtual void Pack(MustlData& ioData) const = 0;
    virtual void Unpack(MustlData& ioData) = 0;
    virtual void Print(ostream& ioOut) const = 0;
    
private:
};

inline ostream&
operator<<(ostream &ioOut, const MustlID& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}
#endif
