//%includeGuardStart {
#ifndef GLCOMMANDHANDLER_H
#define GLCOMMANDHANDLER_H
//%includeGuardStart } gJO88MJSAt/MwJK6xZTl0g
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLCommandHandler.h
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
//%Header } 8ukfWAjNfsX2j53VVrBDXg
/*
 * $Id: GLCommandHandler.h,v 1.18 2006/06/01 15:38:50 southa Exp $
 * $Log: GLCommandHandler.h,v $
 * Revision 1.18  2006/06/01 15:38:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/05/19 13:01:58  southa
 * Mac release work
 *
 * Revision 1.16  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.15  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.14  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:19  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.10  2003/01/09 14:56:58  southa
 * Created Mushcore
 *
 * Revision 1.9  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 * Revision 1.4  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/28 13:07:00  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.1  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.2  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "mushMushcore.h"

class GLCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar LoadPixmap(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar Decompose(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar DumpTextures(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
