#ifndef DATASET_H
#define DATASET_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/




/*
 * $Id: Dataset.h,v 1.5 2002/08/07 13:36:46 southa Exp $
 * $Log: Dataset.h,v $
 * Revision 1.5  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.2  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreStandard.h"
#include "CoreXML.h"
#include "CoreRegExp.h"

class Dataset
{
public:
    Dataset();
    void Load(istream& in);
    void Save(ostream& out);
    void Resize(tSize entries);
    void AppendElement(const Vec<tVal>& data, const Vec<bool>& valid);
    void Clear(void);
    void Testset(void);
    
private:
    static void startElement(void *userData, const char *name, const char **atts);
    static void endElement(void *userData, const char *name);
    static void characterDataHandler(void *userData, const XML_Char *s, int len);

    Vec< Vec<tVal> > m_data;
    Vec< Vec<bool> > m_valid;

    CoreRegExp m_regexp;
    
    friend bool operator==(const Dataset& data1, const Dataset& data2);
};

inline bool operator==(const Dataset& data1, const Dataset& data2)
{
    return ((data1.m_data == data2.m_data) && (data1.m_valid == data2.m_valid));
}

#endif
