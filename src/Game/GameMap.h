#ifndef GAMEMAP_H
#define GAMEMAP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameMap.h,v 1.8 2002/10/11 14:01:13 southa Exp $
 * $Log: GameMap.h,v $
 * Revision 1.8  2002/10/11 14:01:13  southa
 * Lighting work
 *
 * Revision 1.7  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 */

#include "mushCore.h"
#include "mushGL.h"

template<class T> class GameMap
{
public:
    GameMap();
    void SizeSet(U32 inX, U32 inY);
    const T& ElementGet(const GLPoint& inPoint) const { return ElementGet(inPoint.x, inPoint.y); }
    const T& ElementGet(U32 inX, U32 inY) const;
    void ElementSet(const T& inValue, U32 inX, U32 inY);

private:
    U32 m_xSize;
    U32 m_ySize;
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
GameMap<T>::SizeSet(U32 inX, U32 inY)
{
    m_xSize=inX;
    m_ySize=inY;
    m_map.resize(m_xSize * m_ySize);
}

template<class T>
inline void
GameMap<T>::ElementSet(const T& inValue, U32 inX, U32 inY)
{
    COREASSERT(inX < m_xSize);
    COREASSERT(inY < m_ySize);
    m_map[inY * m_xSize + inX] = inValue;
}

template<class T>
inline const T&
GameMap<T>::ElementGet(U32 inX, U32 inY) const
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
