/*
 * $Id$
 * $Log$
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

bool
AutoMonkey::FreeInDestructor(void) const
{
    if (*m_refCtrPtr < 1) throw("AutoMonkey fault");
    CORETESTING(cerr << "Automonkey InDestructorFree, refcount is " << ReferenceCountGet() << endl);
    return (*m_refCtrPtr == 1);
}

