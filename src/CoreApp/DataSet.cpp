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
 * $Id: DataSet.cpp,v 1.10 2002/12/20 13:17:34 southa Exp $
 * $Log: DataSet.cpp,v $
 * Revision 1.10  2002/12/20 13:17:34  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/12/04 00:37:10  southa
 * ControlFrameDef work
 *
 * Revision 1.8  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:04  southa
 * Build process fixes
 *
 * Revision 1.3  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.2  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */
 
#include "Dataset.h"

using namespace Mushware;
using namespace std;

Dataset::Dataset()
{
}

void
Dataset::startElement(void *userData, const char *name, const char **atts)
{
}

void
Dataset::endElement(void *userData, const char *name)
{
}

void
Dataset::characterDataHandler(void *userData, const XML_Char *s, int len)
{
    Dataset *dataset = (Dataset *) userData;

    string str(s);
    vector<string> matches;
    if (dataset->m_regexp.Search(str, matches))
    {
        vector<tVal> data;
        vector<bool> valid;
        vector<string>::iterator p=matches.begin();
        while (p != matches.end())
        {
            if (p->size() > 0)
            {
                data.push_back(atof(p->c_str()));
                valid.push_back(true);
            }
            else
            {
                data.push_back(666);
                valid.push_back(false);
            }
            ++p;
        }
    dataset->AppendElement(data, valid);
    }
}

void
Dataset::Load(istream& in)
{
    Clear();

    XML_Parser parser = XML_ParserCreate(NULL);

    XML_SetUserData(parser, this);
    XML_SetElementHandler(parser, startElement, endElement);
    XML_SetCharacterDataHandler(parser, characterDataHandler);

    m_regexp.SearchPatternSet("{([0-9.+e-]*),([0-9.+e-]*)}");
    

    do
    {
        string str;
        getline(in, str);
        if (!XML_Parse(parser, str.data(), str.length(), in.eof()))
        {
            cerr << XML_ErrorString(XML_GetErrorCode(parser)) << " at line " <<
            XML_GetCurrentLineNumber(parser);
            break;
        }
    } while (!in.eof());

    if (parser != NULL)
    {
        XML_ParserFree(parser);
    }
}

void
Dataset::Save(ostream& out)
{
    tSize i, j;
    out << "<data>" << endl;
    for (i=0; i<m_data.size(); i++)
    {
        out << "{";
        for (j=0; j<m_data[i].size(); j++)
        {
            if (m_valid[i][j])
            {
                out << m_data[i][j];
            }
            if (j+1 != m_data[i].size())
            {
                out << ",";
            }
        }
        out << "}";
        if (i+1 != m_data.size())
        {
            out << ",";
        }
        out << endl;
    }
    out << "</data>" << endl;
}

void
Dataset::AppendElement(const vector<tVal>& data, const vector<bool>& valid)
{
    m_data.push_back(data);
    m_valid.push_back(valid);
}

void
Dataset::Clear(void)
{
    m_data.clear();
    m_valid.clear();
}

void
Dataset::Testset(void)
{
    vector<tVal> data(2);
    vector<bool> valid(data.size(), true);
    data[0]=2.3;data[1]=1.3;AppendElement(data, valid);
    AppendElement(vector<tVal>(2,1.1), valid);
}



