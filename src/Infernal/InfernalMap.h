//%includeGuardStart {
#ifndef INFERNALMAP_H
#define INFERNALMAP_H
//%includeGuardStart } droX77VdyETABT3BzCPPFg
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMap.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } SusjtfwuN3cnad/o/BV0rQ
/*
 * $Id: InfernalMap.h,v 1.1 2003/10/04 12:23:05 southa Exp $
 * $Log: InfernalMap.h,v $
 * Revision 1.1  2003/10/04 12:23:05  southa
 * File renaming
 *
 * Revision 1.16  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.15  2003/08/21 23:08:47  southa
 * Fixed file headers
 *
 * Revision 1.14  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.13  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.12  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.11  2003/01/07 17:13:43  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.10  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.8  2002/10/11 14:01:13  southa
 * Lighting work
 *
 * Revision 1.7  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 */

#include "Mushcore.h"
#include "mushGL.h"

template<class T> class InfernalMap
{
public:
    InfernalMap();
    void SizeSet(Mushware::U32 inX, Mushware::U32 inY);
    const T& ElementGet(const GLPoint& inPoint) const { return ElementGet(inPoint.U32XGet(), inPoint.U32YGet()); }
    const T& ElementGet(Mushware::U32 inX, Mushware::U32 inY) const;
    void ElementSet(const T& inValue, Mushware::U32 inX, Mushware::U32 inY);

private:
    Mushware::U32 m_xSize;
    Mushware::U32 m_ySize;
    MushwareValarray<T> m_map;
};

template<class T>
InfernalMap<T>::InfernalMap() :
m_xSize(0),
m_ySize(0)
{

}

template<class T>
inline void
InfernalMap<T>::SizeSet(Mushware::U32 inX, Mushware::U32 inY)
{
    m_xSize=inX;
    m_ySize=inY;
    m_map.resize(m_xSize * m_ySize);
}

template<class T>
inline void
InfernalMap<T>::ElementSet(const T& inValue, Mushware::U32 inX, Mushware::U32 inY)
{
    MUSHCOREASSERT(inX < m_xSize);
    MUSHCOREASSERT(inY < m_ySize);
    m_map[inY * m_xSize + inX] = inValue;
}

template<class T>
inline const T&
InfernalMap<T>::ElementGet(Mushware::U32 inX, Mushware::U32 inY) const
{
    if (inX >= m_xSize)
    {
        cerr << "inX=" << inX << ", m_xSize=" << m_xSize << endl;
    }
    MUSHCOREASSERT(inX < m_xSize);
    MUSHCOREASSERT(inY < m_ySize);
    return m_map[inY * m_xSize + inX];
}

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
