#ifndef MUSTLCONFIGDEF_H
#define MUSTLCONFIGDEF_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: MustlConfigDef.h,v 1.2 2003/01/15 13:27:32 southa Exp $
 * $Log: MustlConfigDef.h,v $
 * Revision 1.2  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.1  2003/01/14 12:40:10  southa
 * Moved ConfigDefs into Mustl
 *
 */

#include "MustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

// Abstract base
class MustlConfigDef
{
public:
    virtual ~MustlConfigDef();
    virtual const MushcoreScalar ValueGet(void) const = 0;
    virtual void ValueSet(const MushcoreScalar& inValue) = 0;
    virtual bool FromPostRetrieve(const std::string& inName, const std::string& inData) = 0;
    virtual void WebInputPrint(std::ostream& ioOut, const std::string& inName) = 0;

    static void NullFunction(void);
    
protected:
    // Utility functions for subclasses
    static void SelectPrologue(std::ostream& ioOut, const std::string& inName);
    static void SelectOption(std::ostream& ioOut, const std::string& inName, const std::string& inValue, bool inSelected);
    static void SelectOption(std::ostream& ioOut, const std::string& inName, Mustl::U32 inValue, bool inSelected);
    static void SelectEpilogue(std::ostream& ioOut);
};

#endif
