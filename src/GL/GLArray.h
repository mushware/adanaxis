#ifndef GLARRAY_H
#define GLARRAY_H
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
 * $Id: GLArray.h,v 1.6 2003/01/11 13:03:11 southa Exp $
 * $Log: GLArray.h,v $
 * Revision 1.6  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.5  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.3  2002/10/12 17:34:20  southa
 * Wall edges
 *
 * Revision 1.2  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 * Revision 1.1  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 */

#include "GLVector.h"
#include "Mushcore.h"

template<class tSrc, class tDest>
class GLArray
{
public:
    GLArray(): m_pArray(NULL) {}
    GLArray(const GLArray& inArray); // Copy constructor
    ~GLArray() { if (m_pArray != NULL) delete[] m_pArray; }

    void Push(const tSrc& inValue) { m_vector.push_back(inValue); }
    void Build(void);
    const tDest *ArrayGet(void) const { MUSHCOREASSERT(m_pArray != NULL); return m_pArray; }
    Mushware::U32 SizeGet(void) const { return m_vector.size(); }
    
private:
    std::vector<tSrc> m_vector;
    tDest *m_pArray;
};

template<class tSrc, class tDest>
GLArray<tSrc, tDest>::GLArray(const GLArray& inArray) :
    m_vector(inArray.m_vector),
    m_pArray(NULL)
{
    if (inArray.m_pArray != NULL)
    {
        throw(MushcoreLogicFail("Cannot copy GLArray once built"));
    }
}

template<class tSrc, class tDest>
inline void
GLArray<tSrc, tDest>::Build(void)
{
    Mushware::U32 size=m_vector.size();
    if (m_pArray != NULL) delete[] m_pArray;
    m_pArray = new tDest[size];
    for (Mushware::U32 i=0; i<size; ++i)
    {
         m_vector[i].ConvertTo(m_pArray[i]);
    }
}
#endif
