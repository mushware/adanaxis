#ifndef CORECONFIG_H
#define CORECONFIG_H
/*
 * $Id: CoreConfig.h,v 1.4 2002/05/27 12:58:42 southa Exp $
 * $Log: CoreConfig.h,v $
 * Revision 1.4  2002/05/27 12:58:42  southa
 * GameContract and global configs added
 *
 * Revision 1.3  2002/05/26 16:35:07  southa
 * CoreXML work
 *
 * Revision 1.2  2002/05/25 17:17:18  southa
 * CoreXML implementation
 *
 * Revision 1.1  2002/05/24 16:23:09  southa
 * Config and typenames
 *
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
    virtual void Pickle(ostream& inOut) const;
    virtual void Unpickle(CoreXML& inXML);
    
private:
    map<string, CoreScalar> m_config;
};
#endif
