//%includeGuardStart {
#ifndef MAURHEENWORM_H
#define MAURHEENWORM_H
//%includeGuardStart } ZJ7lSOYlXYLI8eqqNh3g8w
//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenWorm.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 2AZN5UbBUQQJzrVQfOz7fQ
/*
* $Id: MaurheenWorm.h,v 1.4 2006/06/01 15:39:12 southa Exp $
* $Log: MaurheenWorm.h,v $
* Revision 1.4  2006/06/01 15:39:12  southa
* DrawArray verification and fixes
*
* Revision 1.3  2005/05/19 13:02:08  southa
* Mac release work
*
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
