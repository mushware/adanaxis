//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshStitchable.cpp
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
//%Header } +T0ZkIsswfrdsGOLZm30xw
/*
 * $Id: MushMeshStitchable.cpp,v 1.6 2006/06/01 15:39:32 southa Exp $
 * $Log: MushMeshStitchable.cpp,v $
 * Revision 1.6  2006/06/01 15:39:32  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/30 12:34:59  southa
 * Mesh and source conditioner work
 *
 * Revision 1.4  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/19 15:59:34  southa
 * Edge manipulation
 *
 * Revision 1.1  2003/10/19 12:41:42  southa
 * Connectors
 *
 */

#include "MushMeshStitchable.h"
//%outOfLineFunctions {
void
MushMeshStitchable::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    if (m_pGeometry == NULL)
    {
        ioOut << "pGeometry=NULL"  << ", ";
    }
    else
    {
        ioOut << "pGeometry=" << *m_pGeometry << ", ";
    }
    if (m_pActiveBox == NULL)
    {
        ioOut << "pActiveBox=NULL"  << ", ";
    }
    else
    {
        ioOut << "pActiveBox=" << *m_pActiveBox << ", ";
    }
    ioOut << "selection=" << m_selection;
    ioOut << "]";
}
//%outOfLineFunctions } mgYtbL6jEKzdUfbYIuOUqA
