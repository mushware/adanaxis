#ifndef COREDATA_H
#define COREDATA_H

/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreData.h,v 1.2 2002/08/16 19:46:06 southa Exp $
 * $Log: CoreData.h,v $
 * Revision 1.2  2002/08/16 19:46:06  southa
 * MediaSound work
 *
 * Revision 1.1  2002/08/15 13:39:30  southa
 * CoreData and CoreDatRef
 *
 */

#include "CoreStandard.h"
#include "CoreException.h"

template<class RefType> class CoreData
{
public:
    ~CoreData();
    static CoreData& Instance(void);

    inline RefType *DataGive(const string& inName, RefType *inData);
    inline RefType *DataGet(const string& inName) const;
    inline void Clear(void);
protected:
    CoreData() {}

private:
    map<string, RefType *> m_data;
    static auto_ptr< CoreData<RefType> > m_instance;
};

template<class RefType>
CoreData<RefType>::~CoreData(void)
{
    for (map<string, RefType *>::iterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        delete p->second;
    }
}

template<class RefType>
inline class CoreData<RefType>&
CoreData<RefType>::Instance(void)
{
    if (m_instance.get() != NULL) return *m_instance;
    m_instance.reset(new CoreData);
    return *m_instance;
}

template<class RefType>
inline RefType *
CoreData<RefType>::DataGive(const string& inName, RefType *inData)
{
    map<string, RefType *>::iterator p = m_data.find(inName);
    if (p != m_data.end())
    {
        delete p->second;
        p->second=inData;
    }
    else
    {
        m_data[inName]=inData;
    }
    return inData;
}

template<class RefType>
inline RefType *
CoreData<RefType>::DataGet(const string& inName) const
{
    map<string, RefType *>::const_iterator p = m_data.find(inName);
    if (p == m_data.end())
    {
        throw(ReferenceFail("Access to non-existent data '"+inName+"'"));
    }
    return p->second;
}

template<class RefType>
inline void
CoreData<RefType>::Clear(void)
{
    for (map<string, RefType *>::iterator p = m_data.begin();
         p != m_data.end(); ++p)
    {
        delete p->second;
    }
    m_data.clear();
}



#endif
