#ifndef MEDIANETID_H
#define MEDIANETID_H
/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

class MediaNetData;

class MediaNetID
{
public:
    virtual ~MediaNetID() {}
    virtual MediaNetID *Clone(void) const = 0;
    virtual void Pack(MediaNetData& ioData) const = 0;
    virtual void Unpack(MediaNetData& ioData) = 0;
    virtual void Print(ostream& ioOut) const = 0;
    
private:
};

inline ostream&
operator<<(ostream &ioOut, const MediaNetID& inObj)
{
    inObj.Print(ioOut);
    return ioOut;
}
#endif
