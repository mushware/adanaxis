#ifndef MUSHCOREPARAMLIST_H
#define MUSHCOREPARAMLIST_H
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
 * $Id: MushcoreParamList.h,v 1.3 2003/01/20 12:23:23 southa Exp $
 * $Log: MushcoreParamList.h,v $
 * Revision 1.3  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.2  2003/01/11 13:03:17  southa
 * Use Mushcore header
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.13  2002/12/29 20:30:51  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.12  2002/12/20 13:17:33  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.10  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/27 08:56:17  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/07 13:36:45  southa
 * Conditioned source
 *
 * Revision 1.7  2002/07/06 18:04:16  southa
 * More designer work
 *
 * Revision 1.6  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.5  2002/06/24 12:12:52  southa
 * Added newline
 *
 * Revision 1.4  2002/05/28 16:37:36  southa
 * Texture references and decomposer
 *
 * Revision 1.3  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.2  2002/05/24 16:23:08  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 */

#include "MushcoreScalar.h"
#include "MushcoreStandard.h"

class MushcoreParamList
{
public:
    typedef std::list<MushcoreScalar> tParams;
    typedef tParams::iterator tParamsIterator;
    typedef tParams::const_iterator tParamsConstIterator;
    
    void PushParam(const MushcoreScalar& inScalar) { m_params.push_back(inScalar); }
 
    Mushware::U32 NumParams(void) { return m_params.size(); }
    void Clear(void) { m_params.clear(); };
    bool Empty(void) { return m_params.empty(); }
    void Print(std::ostream& ioOut) const;

    template<class ParamType> MUSHCORE_DECLARE_INLINE void PopParam(ParamType& outParam)
	{
		if (m_params.empty())
		{
			throw(MushcoreSyntaxFail("Parameter missing"));
		}
		else
		{
			m_params.front().Get(outParam);
			m_params.pop_front();
		}
	}
	

private:
    tParams m_params;
};

inline std::ostream&
operator<<(std::ostream &ioOut, const MushcoreParamList inParamList)
{
    inParamList.Print(ioOut);
    return ioOut;
}

#endif
