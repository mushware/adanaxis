/*
 * $Id: AutoMonkey.cpp,v 1.1 2002/02/23 11:43:34 southa Exp $
 * $Log: AutoMonkey.cpp,v $
 * Revision 1.1  2002/02/23 11:43:34  southa
 * Added AutoMonkey
 *
 */

#include "AutoMonkey.hp"
#include "CoreStandard.hp"

AutoMonkey::~AutoMonkey()
{
    --*m_refCtrPtr;
    CORETESTING(cerr << "Automonkey destroyed, refcount to " << ReferenceCountGet() << endl);
    if (*m_refCtrPtr == 0)
    {
        delete m_refCtrPtr;
        m_refCtrPtr=NULL;
        CORETESTING(cerr << "AutoMonkey workspace freed" << endl); 
    }
}

AutoMonkey::AutoMonkey(const AutoMonkey& inMonkey)
{
    m_refCtrPtr=inMonkey.m_refCtrPtr;
    ++*m_refCtrPtr;
    CORETESTING(cerr << "Automonkey copied, refcount to " << ReferenceCountGet() << endl);
}

void
AutoMonkey::Swap(AutoMonkey& inMonkey)
{
    swap(m_refCtrPtr, inMonkey.m_refCtrPtr);
}

AutoMonkey&
AutoMonkey::operator=(const AutoMonkey& inMonkey)
{
    AutoMonkey temp(inMonkey);
    Swap(temp);
    return *this;
}

bool
AutoMonkey::FreeInDestructor(void) const
{
    if (*m_refCtrPtr < 1) throw("AutoMonkey fault");
    CORETESTING(cerr << "Automonkey InDestructorFree, refcount is " << ReferenceCountGet() << endl);
    return (*m_refCtrPtr == 1);
}

