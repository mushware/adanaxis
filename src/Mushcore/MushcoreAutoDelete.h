/*
 * $Id$
 * $Log$
 */

#include "MushcoreStandard.h"

template<class RefType> class MushcoreAutoDelete
{
public:
    MushcoreAutoDelete();
    ~MushcoreAutoDelete();

    inline RefType *Get(void) const;
    inline void Reset(RefType *inObj);
    
private:
    RefType *m_pObject;
};

template<class RefType>
MushcoreAutoDelete<RefType>::MushcoreAutoDelete(void) :
    m_pObject(NULL)
{
}

template<class RefType>
MushcoreAutoDelete<RefType>::~MushcoreAutoDelete(void)
{
    if (m_pObject != NULL)
    {
        cerr << "Deleting object" << endl;
        delete m_pObject;
    }    
}

template<class RefType>
inline RefType *
MushcoreAutoDelete<RefType>::Get(void) const
{
    return m_pObject;
}

template<class RefType>
inline void
MushcoreAutoDelete<RefType>::Reset(RefType *inObj)
{
    if (m_pObject != NULL)
    {
        delete m_pObject;
    }
    m_pObject = inObj;
}
