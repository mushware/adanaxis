/*
 * $Id: AutoMonkey.cpp,v 1.4 2002/03/07 22:24:32 southa Exp $
 * $Log: AutoMonkey.cpp,v $
 * Revision 1.4  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 * Revision 1.3  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 * Revision 1.2  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.1  2002/02/23 11:43:34  southa
 * Added AutoMonkey
 *
 */

#include "AutoMonkey.hp"
#include "CoreStandard.hp"
#include "CoreSwitches.hp"

AutoMonkey::~AutoMonkey()
{
    --*m_refCtrPtr;
    IFMONKEYTESTING(cerr << "Automonkey destroyed, refcount to " << ReferenceCountGet() << endl);
    if (*m_refCtrPtr == 0)
    {
        delete m_refCtrPtr;
        m_refCtrPtr=NULL;
        IFMONKEYTESTING(cerr << "AutoMonkey workspace freed" << endl); 
    }
}

AutoMonkey::AutoMonkey(const AutoMonkey& inMonkey)
{
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    ++*m_refCtrPtr;
    IFMONKEYTESTING(cerr << "Automonkey copied, refcount to " << ReferenceCountGet() << endl);
}

void
AutoMonkey::Swap(AutoMonkey& inMonkey)
{
    int *temp=m_refCtrPtr;
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    inMonkey.m_refCtrPtr=temp;
}

AutoMonkey&
AutoMonkey::operator=(const AutoMonkey& inMonkey)
{
    AutoMonkey temp(inMonkey);
    Swap(temp);
    return *this;
}

bool
AutoMonkey::FreeInDestructor(void *inDataPtr) const
{
    if (*m_refCtrPtr < 1) throw("AutoMonkey fault");
    IFMONKEYTESTING(cerr << "Automonkey InDestructorFree, refcount is " << ReferenceCountGet() << endl);
    return (*m_refCtrPtr == 1  && inDataPtr != NULL);
}

