#ifndef COREPARAMLIST_HP
#define COREPARAMLIST_HP
/*
 * $Id: CoreParamList.h,v 1.4 2002/05/28 16:37:36 southa Exp $
 * $Log: CoreParamList.h,v $
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

