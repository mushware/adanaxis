#ifndef CORECONFIG_H
#define CORECONFIG_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: CoreConfig.h,v 1.15 2002/12/17 12:53:33 southa Exp $
 * $Log: CoreConfig.h,v $
 * Revision 1.15  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.14  2002/11/24 23:18:03  southa
 * Added type name accessor to CorePickle
 *
 * Revision 1.13  2002/10/22 20:41:58  southa
 * Source conditioning
 *
 * Revision 1.12  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.11  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.10  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.9  2002/07/02 14:27:12  southa
 * First floor std::map designer build
 *
 * Revision 1.8  2002/06/27 12:36:03  southa
 * Build process fixes
 *
 * Revision 1.7  2002/06/04 14:11:21  southa
 * Traits loader first stage
 *
 * Revision 1.6  2002/05/30 14:41:13  southa
 * GameData and loadtilemap command
 *
 * Revision 1.5  2002/05/28 13:07:03  southa
 * Command parser extensions and TIFF loader
 *
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

#include "CoreScalar.h"
#include "CoreStandard.h"

class CoreConfig
{
public:
    virtual ~CoreConfig() {}
    void Set(const string& inName, const CoreScalar& inValue);
    void Set(const string& inName, const string& inStr) { Set(inName, CoreScalar(inStr)); }
    void Set(const string& inName, const Mushware::tVal inVal) { Set(inName, CoreScalar(inVal)); }
    const CoreScalar& Get(const string& inName) const;
    bool GetIfExists(const CoreScalar** outScalar, const string& inName) const;
    bool Exists(const string& inName) const;

private:
    std::map<string, CoreScalar> m_config;
};
#endif
