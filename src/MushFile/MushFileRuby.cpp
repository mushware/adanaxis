//%Header {
/*****************************************************************************
 *
 * File: src/MushFile/MushFileRuby.cpp
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
//%Header } EjVQMJGZRf6g77tfjh6wJg
/*
 * $Id: MushFileRuby.cpp,v 1.2 2006/11/07 11:08:54 southa Exp $
 * $Log: MushFileRuby.cpp,v $
 * Revision 1.2  2006/11/07 11:08:54  southa
 * Texture loading from mushfiles
 *
 * Revision 1.1  2006/11/06 12:56:32  southa
 * MushFile work
 *
 */

#include "MushFileRuby.h"

#include "MushFileFilename.h"
#include "MushFileLibrary.h"

MUSHRUBYEMPTYOBJ_INSTANCE(6000);

MUSHRUBY_INSTALL(MushFileRuby);

using namespace Mushware;
using namespace std;

Mushware::tRubyValue
MushFileRuby::LibraryAdd(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue param0(inArg0);
    
    MushFileLibrary::Sgl().LibraryAdd(param0.String());
    
    return kRubyQnil;
}    

Mushware::tRubyValue
MushFileRuby::LibraryDump(Mushware::tRubyValue inSelf)
{
    MushcoreXMLOStream xmlOut(std::cout);
    xmlOut << MushFileLibrary::Sgl();
    
    return kRubyQnil;
}

Mushware::tRubyValue
MushFileRuby::File(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue param0(inArg0);
    

    MushFileFilename mushFilename(param0.String());
    mushFilename.ResolveForRead();
    bool present = mushFilename.SourceExists();
    return MushRubyValue(present).Value();
}    

void
MushFileRuby::MushFileInstall(void)
{
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cLibraryAdd", LibraryAdd);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cLibraryDump", LibraryDump);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cFile?", File);
}
