//%includeGuardStart {
#ifndef MUSHCORESTANDARD_H
#define MUSHCORESTANDARD_H
//%includeGuardStart } n2v+Z7ZU0WF8ezNx14AESA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreStandard.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } VEQuSkwV/fh55K/iqbIbTA
/*
 * $Id: MushcoreStandard.h,v 1.18 2004/12/06 20:44:18 southa Exp $
 * $Log: MushcoreStandard.h,v $
 * Revision 1.18  2004/12/06 20:44:18  southa
 * Quaternion and matrix operations
 *
 * Revision 1.17  2004/09/26 19:42:05  southa
 * Added MushMesh, fixed typenames and release target
 *
 * Revision 1.16  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.15  2004/01/02 21:13:13  southa
 * Source conditioning
 *
 * Revision 1.14  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.13  2003/10/04 15:32:12  southa
 * Module split
 *
 * Revision 1.12  2003/09/23 22:57:57  southa
 * XML vector handling
 *
 * Revision 1.11  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:09:17  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/02/05 18:49:52  southa
 * Build fixes
 *
 * Revision 1.8  2003/02/05 17:06:38  southa
 * Build fixes
 *
 * Revision 1.7  2003/02/03 23:15:51  southa
 * Build work for Visual C++
 *
 * Revision 1.6  2003/01/20 10:45:29  southa
 * Singleton tidying
 *
 * Revision 1.5  2003/01/18 13:33:59  southa
 * Created MushcoreSingleton
 *
 * Revision 1.4  2003/01/13 14:32:03  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.3  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.25  2002/12/29 20:30:52  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.24  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.23  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.22  2002/12/12 18:38:57  southa
 * Mustl separation
 *
 * Revision 1.21  2002/12/04 00:37:10  southa
 * ControlFrameDef work
 *
 * Revision 1.20  2002/11/01 16:15:26  southa
 * Network send and receive
 *
 * Revision 1.19  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.18  2002/10/10 13:51:16  southa
 * Speed fixes and various others
 *
 * Revision 1.17  2002/08/27 09:03:24  southa
 * Added stdio.h
 *
 * Revision 1.16  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.15  2002/08/19 11:09:55  southa
 * InfernalTypeRace rendering
 *
 * Revision 1.14  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.13  2002/07/18 11:43:34  southa
 * Added M_PI
 *
 * Revision 1.12  2002/07/16 17:48:07  southa
 * Collision and optimisation work
 *
 * Revision 1.11  2002/07/07 11:16:07  southa
 * More designer work
 *
 * Revision 1.10  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.9  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.8  2002/06/24 12:12:30  southa
 * Added <math.h>
 *
 * Revision 1.7  2002/06/11 16:23:56  southa
 * New paths to data files
 *
 * Revision 1.6  2002/05/28 22:36:44  southa
 * Script loader and tile map
 *
 * Revision 1.5  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.4  2002/05/25 17:17:18  southa
 * MushcoreXML implementation
 *
 * Revision 1.3  2002/05/24 16:23:08  southa
 * Config and typenames
 *
 * Revision 1.2  2002/05/10 22:38:23  southa
 * Checkpoint
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.9  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.8  2002/03/21 22:07:52  southa
 * Initial wrangle application handler
 *
 * Revision 1.7  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.6  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.5  2002/03/04 22:30:49  southa
 * Interpreter work
 *
 * Revision 1.4  2002/02/26 17:01:40  southa
 * Completed Sprite loader
 *
 * Revision 1.3  2002/02/23 11:43:34  southa
 * Added AutoMonkey
 *
 * Revision 1.2  2002/02/18 22:04:37  southa
 * Initial texture loading
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef _MSC_VER
/* Disable type truncation warnings */
#pragma warning(disable: 4244 4305 4267)

/* MSVC doesn't support template friend functions */
#define MUSHWARE_NO_TEMPLATE_FRIENDS 1

/* MSVC std::valarray doesn't have const T& operator[] const,
 * so use the mimic instead
 */
#define MUSHCORE_MIMIC_VALARRAY 1
#endif

#include <iosfwd>
#include <list>
#include <map>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <assert.h>

namespace Mushware
{
    typedef float tVal;
    typedef double tLongVal;
    typedef signed int S32;
    typedef unsigned int U32;
    typedef signed short S16;
    typedef unsigned short U16;
    typedef signed char S8;
    typedef unsigned char U8;
    typedef double tXMLVal;
    typedef std::size_t tSize;
};

#ifdef MUSHCORE_MIMIC_VALARRAY
// Mimic valarray using vector
#define MushwareValarray std::vector
#else
#include <valarray>
#define MushwareValarray std::valarray
#endif


#define MUSHCOREASSERT(exp) assert(exp)

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
