#ifndef COREPARAMLIST_H
#define COREPARAMLIST_H
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
 * $Id: CoreParamList.h,v 1.12 2002/12/20 13:17:33 southa Exp $
 * $Log: CoreParamList.h,v $
 * Revision 1.12  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.10  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/24 12:12:52  southa
 * Added newline
 *
 * Revision 1.4  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.3  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.2  2002/05/24 16:23:08  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 */

#include "CoreScalar.h"
#include "CoreStandard.h"

class CoreParamList
{
public:
    void PushParam(const CoreScalar& inScalar)
        {m_params.push_back(inScalar);}
    void PopParam(Mushware::tVal& outVal);
    void PopParam(std::string& outStr);
    void PopParam(Mushware::U32& outU32);
    Mushware::U32 NumParams(void) {return m_params.size();}
    void Clear(void) {m_params.clear();};
    bool Empty(void) {return m_params.empty();}
    void ostreamPrint(std::ostream& inOut);
private:
    std::list<CoreScalar> m_params;
};

inline std::ostream& operator<<(std::ostream &inOut, CoreParamList inCoreParamList)
{
    inCoreParamList.ostreamPrint(inOut);
    return inOut;
}

#endif

