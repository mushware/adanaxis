#ifndef GAMEMAP_H
#define GAMEMAP_H
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
 * $Id: GameMap.h,v 1.11 2003/01/07 17:13:43 southa Exp $
 * $Log: GameMap.h,v $
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

template<class T> class GameMap
{
public:
    GameMap();
    void SizeSet(Mushware::U32 inX, Mushware::U32 inY);
    const T& ElementGet(const GLPoint& inPoint) const { return ElementGet(inPoint.U32XGet(), inPoint.U32YGet()); }
    const T& ElementGet(Mushware::U32 inX, Mushware::U32 inY) const;
    void ElementSet(const T& inValue, Mushware::U32 inX, Mushware::U32 inY);

private:
    Mushware::U32 m_xSize;
    Mushware::U32 m_ySize;
    tValarray<T> m_map;
};

template<class T>
GameMap<T>::GameMap() :
m_xSize(0),
m_ySize(0)
{

}

template<class T>
inline void
GameMap<T>::SizeSet(Mushware::U32 inX, Mushware::U32 inY)
{
    m_xSize=inX;
    m_ySize=inY;
    m_map.resize(m_xSize * m_ySize);
}

template<class T>
inline void
GameMap<T>::ElementSet(const T& inValue, Mushware::U32 inX, Mushware::U32 inY)
{
    COREASSERT(inX < m_xSize);
    COREASSERT(inY < m_ySize);
    m_map[inY * m_xSize + inX] = inValue;
}

template<class T>
inline const T&
GameMap<T>::ElementGet(Mushware::U32 inX, Mushware::U32 inY) const
{
    if (inX >= m_xSize)
    {
        cerr << "inX=" << inX << ", m_xSize=" << m_xSize << endl;
    }
    COREASSERT(inX < m_xSize);
    COREASSERT(inY < m_ySize);
    return m_map[inY * m_xSize + inX];
}

#endif
