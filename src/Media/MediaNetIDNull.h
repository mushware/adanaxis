/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "MediaNetID.h"

class MediaNetData;

class MediaNetIDNull : public MediaNetID
{
public:
    virtual ~MediaNetIDNull();
    virtual MediaNetID *Clone(void) const;
    virtual void Pack(MediaNetData& ioData) const;
    virtual void Unpack(MediaNetData& ioData);
    virtual void Print(ostream& ioOut) const;

private:
};
