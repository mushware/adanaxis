#ifndef MUSHCOREREGEXP_H
#define MUSHCOREREGEXP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreRegExp.h,v 1.3 2003/01/11 17:07:53 southa Exp $
 * $Log: MushcoreRegExp.h,v $
 * Revision 1.3  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.8  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.6  2002/09/01 16:29:18  southa
 * Support Redhat paths for include files
 *
 * Revision 1.5  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/05/09 17:10:38  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#include "MushcoreStandard.h"

class MushcoreRegExp
{
public:
    enum
    {
        kMaxMatches = 256
    };

    typedef std::string tPattern;
    typedef std::vector<std::string> tMatches;

    MUSHCORE_DECLARE_INLINE MushcoreRegExp();
    explicit MUSHCORE_DECLARE_INLINE MushcoreRegExp(const tPattern& inPattern);
    ~MushcoreRegExp();
    
    void SearchPatternSet(const tPattern& inPattern);
    bool Search(const std::string& inString);
    bool Search(tMatches& outMatches, const std::string& inString);

private:
    bool HandleReturnCode(int inRC);
        
    void *m_regExp;
};

inline
MushcoreRegExp::MushcoreRegExp() :
    m_regExp(NULL)
{
}

inline
MushcoreRegExp::MushcoreRegExp(const tPattern& inPattern) :
    m_regExp(NULL)
{
    SearchPatternSet(inPattern);
}

#endif
