#ifndef COREPARAMLIST_HP
#define COREPARAMLIST_HP
/*
 * $Id: CoreParamList.h,v 1.1 2002/03/05 22:44:46 southa Exp $
 * $Log: CoreParamList.h,v $
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
    void PopParam(Val& outVal);
    void PopParam(string& outStr);
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