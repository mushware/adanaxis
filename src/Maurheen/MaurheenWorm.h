//%includeGuardStart {
#ifndef MAURHEENWORM_H
#define MAURHEENWORM_H
//%includeGuardStart } ZJ7lSOYlXYLI8eqqNh3g8w
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenWorm.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ab2Pj3ndh37+YDdurQvQLQ
/*
* $Id: MaurheenWorm.h,v 1.1 2004/03/07 12:05:56 southa Exp $
* $Log: MaurheenWorm.h,v $
* Revision 1.1  2004/03/07 12:05:56  southa
* Rendering work
*
*/

#include "MaurheenStandard.h"

#include "mushMushGL.h"

class MaurheenWorm
{
public:
    MaurheenWorm() {}
    void Create(Mushware::tVal frame);
    void Render(void);
    
private:
    MushMeshArray<Mushware::t3GLVal> m_vertices;
    MushMeshArray<Mushware::t3GLVal> m_normals;
    MushMeshArray<Mushware::t2GLVal> m_texCoords;
    Mushware::U32 m_length;
    Mushware::U32 m_order;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
