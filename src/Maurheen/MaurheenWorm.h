//%includeGuardStart {
#ifndef MAURHEENWORM_H
#define MAURHEENWORM_H
//%includeGuardStart } ZJ7lSOYlXYLI8eqqNh3g8w
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenWorm.h
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 4jBiX/VEk4nB3NvQFvwHRw
/*
* $Id: MaurheenWorm.h,v 1.2 2004/03/07 20:33:54 southa Exp $
* $Log: MaurheenWorm.h,v $
* Revision 1.2  2004/03/07 20:33:54  southa
* Graphics tuning
*
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
