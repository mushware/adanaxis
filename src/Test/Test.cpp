/*
 * $Id: Test.cpp,v 1.1.1.1 2002/02/11 22:30:09 southa Exp $
 * $Log: Test.cpp,v $
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "Test.hp"
#include "Dataset.hp"
#include "RegExp.hp"
#include "AutoMonkey.hp"

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

void
Test::Test3(void)
{
    AutoMonkey& monkey1=*new AutoMonkey;
    if (monkey1.ReferenceCountGet() != 1)
    {
        TestFail("AutoMonkey fault 1");
    }

    if (!monkey1.FreeInDestructor())
    {
        TestFail("AutoMonkey fault 2");
    }
    AutoMonkey& monkey2=*new AutoMonkey(monkey1);
    if (monkey1.ReferenceCountGet() != 2)
    {
        TestFail("AutoMonkey fault 3");
    }
    if (monkey2.ReferenceCountGet() != 2)
    {
        TestFail("AutoMonkey fault 4");
    }
    if (monkey1.FreeInDestructor())
    {
        TestFail("AutoMonkey fault 5");
    }
    if (monkey2.FreeInDestructor())
    {
        TestFail("AutoMonkey fault 6");
    }
    // Next line should not compile
    // monkey1=monkey2;
    
    delete &monkey1;
    if (monkey2.ReferenceCountGet() != 1)
    {
        TestFail("AutoMonkey fault 7");
    }
    if (!monkey2.FreeInDestructor())
    {
        TestFail("AutoMonkey fault 8");
    }
    delete &monkey2;
}