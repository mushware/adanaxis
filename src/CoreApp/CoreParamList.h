#ifndef COREPARAMLIST_H
#define COREPARAMLIST_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreParamList.h,v 1.9 2002/08/27 08:56:17 southa Exp $
 * $Log: CoreParamList.h,v $
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

#include "CoreStandard.h"
#include "CoreScalar.h"

class CoreParamList
{
public:
    void PushParam(const CoreScalar& inScalar)
        {m_params.push_back(inScalar);}
    void PopParam(tVal& outVal);
    void PopParam(string& outStr);
    void PopParam(U32& outU32);
    tSize NumParams(void) {return m_params.size();}
    void Clear(void) {m_params.clear();};
    bool Empty(void) {return m_params.empty();}
    void ostreamPrint(ostream& inOut);
private:
    list<CoreScalar> m_params;
};

inline ostream& operator<<(ostream &inOut, CoreParamList inCoreParamList)
{
    inCoreParamList.ostreamPrint(inOut);
    return inOut;
}

#endif

