/*
 * $Id$
 * $Log$
 */

#include "Test.hp"
#include "Dataset.hp"
#include "RegExp.hp"

void
Test::Test1(void)
{
    RegExp re;
    vector<string> matches;

    if (re.Search("dog", "cat")) throw TestFail("False positive");
    if (!re.Search("dog", "dog")) throw TestFail("False negative");
    
    re.SearchPatternSet(".*(cat).*");
    if (!re.Search("where is my cat?", matches))
    {
        throw TestFail("Expression wouldn't match string");
    }
    if (matches.size() != 1 || matches[0] != "cat")
    {
        throw TestFail("Expression failed to extract string");
    }
    matches.clear();
    if (!re.Search("{1.3,4.5}", "{([0-9.+e-]*),([0-9.+e-]*)}",  matches))
    {
        throw TestFail("Expression wouldn't match numbers");
    }
    if (matches.size() != 2 || matches[0] != "1.3" || matches[1] != "4.5")
    {
        throw TestFail("Expression failed to extract numbers");
    }
    if (!re.Search("{1.3,4.5}", "{([0-9.+e-]*),([0-9.+e-]*)}",  matches))
    {
        throw TestFail("Expression wouldn't match numbers");
    }
    if (matches.size() != 4 || matches[2] != "1.3" || matches[3] != "4.5")
    {
        throw TestFail("Expression failed to extract cumulative numbers");
    }
    try
    {
        re.Search("test", "{(");
        throw TestFail("Failed to raise exception");
    }
    catch (RegExpFail r)
    {
    }
}

void
Test::Test2(void)
{
    Dataset data1, data2;
    {
        ifstream inFile("test1_input.txt");
        if (inFile.fail()) throw TestFail("No input file");
        data1.Load(inFile);
    }
    {
        ofstream outFile("test1_output.txt");
        if (outFile.fail()) throw TestFail("Couldn't open output file");
        data1.Save(outFile);
    }
    {
        ifstream inFile("test1_output.txt");
        if (inFile.fail()) throw TestFail("No rewritten file");
        data2.Load(inFile);
    }
    if (data1 != data2)
    {
        throw TestFail("Reread data doesn't match");
    }
}

