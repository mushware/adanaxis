/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"

#include "MediaNetID.h"

class MediaNetData;

class MediaNetIDString : public MediaNetID
{
public:
    explicit MediaNetIDString(const string& inName) : m_name(inName) {}
    explicit MediaNetIDString(MediaNetData& ioData);
    virtual ~MediaNetIDString();
    virtual MediaNetID *Clone(void) const;
    virtual void Pack(MediaNetData& ioData) const;
    virtual void Unpack(MediaNetData& ioData);
    virtual void Print(ostream& ioOut) const;

private:
    string m_name;
};
