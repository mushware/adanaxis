/*
 * $Id: GLArray.h,v 1.2 2002/10/12 15:24:58 southa Exp $
 * $Log: GLArray.h,v $
 * Revision 1.2  2002/10/12 15:24:58  southa
 * Facet renderer
 *
 * Revision 1.1  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 */

#include "mushCore.h"
#include "GLVector.h"

template<class tSrc, class tDest>
class GLArray
{
public:
    GLArray(): m_pArray(NULL) {}
    GLArray(const GLArray& inArray); // Copy constructor
    ~GLArray() { if (m_pArray != NULL) delete[] m_pArray; }

    void Push(const tSrc& inValue) { m_vector.push_back(inValue); }
    void Build(void);
    const tDest *ArrayGet(void) const { COREASSERT(m_pArray != NULL); return m_pArray; }
    U32 SizeGet(void) const { return m_vector.size(); }
    
private:
    vector<tSrc> m_vector;
    tDest *m_pArray;
};

template<class tSrc, class tDest>
GLArray<tSrc, tDest>::GLArray(const GLArray& inArray) :
    m_vector(inArray.m_vector),
    m_pArray(NULL)
{
    if (inArray.m_pArray != NULL)
    {
        throw(LogicFail("Cannot copy GLArray once built"));
    }
}

template<class tSrc, class tDest>
inline void
GLArray<tSrc, tDest>::Build(void)
{
    U32 size=m_vector.size();
    if (m_pArray != NULL) delete[] m_pArray;
    m_pArray = new tDest[size];
    for (U32 i=0; i<size; ++i)
    {
         m_vector[i].ConvertTo(m_pArray[i]);
    }
}
