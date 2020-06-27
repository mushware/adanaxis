//%includeGuardStart {
#ifndef MUSHMEDIA_H
#define MUSHMEDIA_H
//%includeGuardStart } JsOmWNwG2BYqQm+ESWImqQ
//%Header {
/*****************************************************************************
 *
 * File: src/API/mushMedia.h
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
//%Header } 2PFZP/Qui/I+X1x2nzQEgg
/*
 * $Id: mushMedia.h,v 1.33 2006/07/11 19:49:03 southa Exp $
 * $Log: mushMedia.h,v $
 * Revision 1.33  2006/07/11 19:49:03  southa
 * Control menu
 *
 * Revision 1.32  2006/07/07 07:57:28  southa
 * Key translation
 *
 * Revision 1.31  2006/06/01 15:38:45  southa
 * DrawArray verification and fixes
 *
 * Revision 1.30  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.29  2005/03/13 00:34:45  southa
 * Build fixes, key support and stereo
 *
 * Revision 1.28  2004/01/06 20:46:48  southa
 * Build fixes
 *
 * Revision 1.27  2004/01/02 21:13:04  southa
 * Source conditioning
 *
 * Revision 1.26  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.25  2003/08/21 23:08:16  southa
 * Fixed file headers
 *
 * Revision 1.24  2003/01/09 14:56:57  southa
 * Created Mushcore
 *
 * Revision 1.23  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.22  2002/12/12 14:00:38  southa
 * Created Mustl
 *
 * Revision 1.21  2002/12/07 18:32:14  southa
 * Network ID stuff
 *
 * Revision 1.20  2002/11/27 13:23:26  southa
 * Server and client data exchange
 *
 * Revision 1.19  2002/11/25 12:06:17  southa
 * Received net message routing
 *
 * Revision 1.18  2002/11/15 18:58:33  southa
 * Configuration mode
 *
 * Revision 1.17  2002/11/15 11:47:55  southa
 * Web processing and error handling
 *
 * Revision 1.16  2002/11/05 18:15:00  southa
 * Web server
 *
 * Revision 1.15  2002/11/04 01:02:37  southa
 * Link checks
 *
 * Revision 1.14  2002/11/03 18:43:08  southa
 * Network fixes
 *
 * Revision 1.13  2002/11/01 16:15:26  southa
 * Network send and receive
 *
 * Revision 1.12  2002/10/31 19:55:53  southa
 * Network links
 *
 * Revision 1.11  2002/10/31 16:41:32  southa
 * Network client
 *
 * Revision 1.10  2002/10/31 15:52:14  southa
 * First network code
 *
 * Revision 1.9  2002/10/22 20:41:56  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/16 21:13:52  southa
 * Added MediaSoundStream
 *
 * Revision 1.6  2002/08/15 13:39:30  southa
 * MushcoreData and MushcoreDatRef
 *
 * Revision 1.5  2002/08/07 13:36:43  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:01  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/21 18:50:16  southa
 * SDLAppHandler added
 *
 * Revision 1.1  2002/06/10 15:16:59  southa
 * Integration of MP3 player
 *
 */

#include "Media/MediaAudio.h"
#include "Media/MediaJob.h"
#include "Media/MediaJoystick.h"
#include "Media/MediaKeyboard.h"
#include "Media/MediaSDL.h"
#include "Media/MediaSound.h"
#include "Media/MediaSoundStream.h"
#include "Media/MediaThreadPool.h"

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
