/*
 * $Id$
 * $Log$
 */

#include "CoreStandard.h"
#include "CoreScalar.h"
#include "CorePickle.h"

class CoreConfig : public CorePickle
{
public:
    virtual ~CoreConfig() {}
    void Set(const string& inName, const CoreScalar& inValue);
    void Set(const string& inName, const string& inStr) { Set(inName, CoreScalar(inStr)); }
    void Set(const string& inName, const tVal inVal) { Set(inName, CoreScalar(inVal)); }
    const CoreScalar& Get(const string& inName) const;
    bool ConfigExists(const string& inName) const;
    virtual void Pickle(istream& inOut) const;
    virtual void Unpickle(ostream& inIn);
    
private:
    map<string, CoreScalar> m_config;
};
