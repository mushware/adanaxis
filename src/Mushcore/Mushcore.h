//%includeGuardStart {
#ifndef MUSHCORE_H
#define MUSHCORE_H
//%includeGuardStart } SuMFSOC9JQAWIDpeVa9NFg
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/Mushcore.h
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
//%Header } khB037d4/c4ix61mTYfQtg
/*
 * $Id: Mushcore.h,v 1.26 2006/06/01 15:39:40 southa Exp $
 * $Log: Mushcore.h,v $
 * Revision 1.26  2006/06/01 15:39:40  southa
 * DrawArray verification and fixes
 *
 * Revision 1.25  2005/08/02 17:11:28  southa
 * win32 build fixes
 *
 * Revision 1.24  2005/07/29 14:59:50  southa
 * Maptor access
 *
 * Revision 1.23  2005/07/29 11:53:40  southa
 * MushcoreMaptor created
 *
 * Revision 1.22  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 * Revision 1.21  2005/06/13 14:25:45  southa
 * Pipe and ordered data work
 *
 * Revision 1.20  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.19  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 * Revision 1.18  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.17  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.16  2003/10/02 23:33:38  southa
 * XML polymorphic objects
 *
 * Revision 1.15  2003/09/21 15:57:11  southa
 * XML autogenerator work
 *
 * Revision 1.14  2003/09/21 11:46:10  southa
 * XML input stream
 *
 * Revision 1.13  2003/09/21 09:51:08  southa
 * Stream autogenerators
 *
 * Revision 1.12  2003/09/17 20:04:59  southa
 * Build changes
 *
 * Revision 1.11  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:09:03  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.8  2003/01/18 17:05:47  southa
 * Singleton work
 *
 * Revision 1.7  2003/01/18 13:33:57  southa
 * Created MushcoreSingleton
 *
 * Revision 1.6  2003/01/17 13:30:40  southa
 * Source conditioning and build fixes
 *
 * Revision 1.5  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
 * Revision 1.4  2003/01/13 14:32:02  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.3  2003/01/12 17:32:58  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 17:58:14  southa
 * Mustl fixes
 *
 * Revision 1.1  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 */

#include "MushcoreAbstractSingleton.h"
#include "MushcoreAppHandler.h"
#include "MushcoreAppSignal.h"
#include "MushcoreAutoBool.h"
#include "MushcoreAutoClonePtr.h"
#include "MushcoreAutoMonkey.h"
#include "MushcoreCommand.h"
#include "MushcoreCommandHandler.h"
#include "MushcoreConfig.h"
#include "MushcoreData.h"
#include "MushcoreDataRef.h"
#include "MushcoreEnv.h"
#include "MushcoreEnvOutput.h"
#include "MushcoreFactory.h"
#include "MushcoreFail.h"
#include "MushcoreGlobalConfig.h"
#include "MushcoreHistory.h"
#include "MushcoreInfo.h"
#include "MushcoreInstaller.h"
#include "MushcoreInterpreter.h"
#include "MushcoreLog.h"
#include "MushcoreMaptor.h"
#include "MushcoreMaptorConstIterator.h"
#include "MushcoreMaptorIterator.h"
#include "MushcoreMaptorRef.h"
// #include "MushcoreIO.h"
#include "MushcoreObject.h"
#include "MushcoreOrderedData.h"
#include "MushcorePickle.h"
#include "MushcorePipe.h"
#include "MushcoreRegExp.h"
#include "MushcoreScalar.h"
#include "MushcoreScript.h"
#include "MushcoreSingleton.h"
#include "MushcoreStandard.h"
#include "MushcoreStreamUtil.h"
#include "MushcoreStreamUtil.h"
#include "MushcoreUninstaller.h"
#include "MushcoreUtil.h"
#include "MushcoreVirtualObject.h"
#include "MushcoreXML.h"
#include "MushcoreXMLIStream.h"
#include "MushcoreXMLOStream.h"
#include "MushcoreXMLStream.h"

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
