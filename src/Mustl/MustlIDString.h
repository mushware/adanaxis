/*
 * $Id: MustlIDString.h,v 1.1 2002/12/07 18:32:15 southa Exp $
 * $Log: MustlIDString.h,v $
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "mushCore.h"

#include "MustlID.h"

class MustlData;

class MustlIDString : public MustlID
{
public:
    explicit MustlIDString(const string& inName) : m_name(inName) {}
    explicit MustlIDString(MustlData& ioData);
    virtual ~MustlIDString();
    virtual MustlID *Clone(void) const;
    virtual void Pack(MustlData& ioData) const;
    virtual void Unpack(MustlData& ioData);
    virtual void Print(ostream& ioOut) const;

private:
    string m_name;
};
