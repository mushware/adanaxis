/*
 * $Id: Dataset.h,v 1.2 2002/03/18 22:21:12 southa Exp $
 * $Log: Dataset.h,v $
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
    void Resize(Size entries);
    void AppendElement(const Vec<Val>& data, const Vec<bool>& valid);
    void Clear(void);
    void Testset(void);
    
private:
    static void startElement(void *userData, const char *name, const char **atts);
    static void endElement(void *userData, const char *name);
    static void characterDataHandler(void *userData, const XML_Char *s, int len);

    Vec< Vec<Val> > m_data;
    Vec< Vec<bool> > m_valid;

    CoreRegExp m_regexp;
    
    friend bool operator==(const Dataset& data1, const Dataset& data2);
};

inline bool operator==(const Dataset& data1, const Dataset& data2)
{
    return ((data1.m_data == data2.m_data) && (data1.m_valid == data2.m_valid));
}
