/*
 * $Id: Test.cpp,v 1.6 2002/05/10 16:39:35 southa Exp $
 * $Log: Test.cpp,v $
 * Revision 1.6  2002/05/10 16:39:35  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/05/09 18:01:39  southa
 * Rebuild under cygwin
 *
 * Revision 1.4  2002/02/26 17:01:39  southa
 * Completed Sprite loader
 *
 * Revision 1.3  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.2  2002/02/23 11:43:36  southa
 * Added AutoMonkey
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "Test.h"
#include "mushCore.h"

void
Test::Test1(void)
{
    CoreRegExp re;
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
    catch (CoreRegExpFail r)
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
    char workspace[]="hello";
    
    AutoMonkey& monkey1=*new AutoMonkey;
    if (monkey1.ReferenceCountGet() != 1)
    {
        throw TestFail("AutoMonkey fault 1");
    }

    if (!monkey1.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 2");
    }
    AutoMonkey& monkey2=*new AutoMonkey(monkey1);
    if (monkey1.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 3");
    }
    if (monkey2.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 4");
    }
    if (monkey1.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 5");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 6");
    }
    monkey1=monkey1;
    if (monkey1.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 7");
    }
    if (monkey2.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 8");
    }
    if (monkey1.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 9");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 10");
    }
    monkey1=monkey2;
    if (monkey1.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 11");
    }
    if (monkey2.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 12");
    }
    if (monkey1.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 13");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 14");
    }
    AutoMonkey& monkey3=*new AutoMonkey;
    AutoMonkey& monkey4=*new AutoMonkey(monkey3);
    if (monkey3.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 40");
    }
    if (monkey4.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 41");
    }
    if (monkey3.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 42");
    }
    if (monkey4.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 43");
    }
    monkey3=monkey2;
    if (monkey4.ReferenceCountGet() != 1)
    {
        throw TestFail("AutoMonkey fault 44");
    }
    if (!monkey4.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 45");
    }
    if (monkey3.ReferenceCountGet() != 3)
    {
        throw TestFail("AutoMonkey fault 46");
    }
    if (monkey2.ReferenceCountGet() != 3)
    {
        throw TestFail("AutoMonkey fault 47");
    }
    if (monkey1.ReferenceCountGet() != 3)
    {
        throw TestFail("AutoMonkey fault 48");
    }
    if (monkey1.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 49");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 50");
    }
    if (monkey3.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 51");
    }
    delete &monkey1;
    if (monkey2.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 80");
    }
    if (monkey3.ReferenceCountGet() != 2)
    {
        throw TestFail("AutoMonkey fault 81");
    }
    if (monkey2.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 82");
    }
    if (monkey3.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 83");
    }
    delete &monkey2;
    if (monkey3.ReferenceCountGet() != 1)
    {
        throw TestFail("AutoMonkey fault 84");
    }
    if (!monkey3.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 85");
    }
    delete &monkey3;
    if (monkey4.ReferenceCountGet() != 1)
    {
        throw TestFail("AutoMonkey fault 86");
    }
    if (!monkey4.FreeInDestructor(workspace))
    {
        throw TestFail("AutoMonkey fault 87");
    }
    delete &monkey4;
    // All monkeys gone
    AutoMonkey& monkey5=*new AutoMonkey;
    
    if (monkey5.FreeInDestructor(NULL))
    {
        throw TestFail("AutoMonkey fault 100");
    }
    delete &monkey5;
}

void
Test::Test4(void)
{
    CoreConfig config;

    config.Set("elem1", CoreScalar("elem1value"));
    config.Set("elem2", CoreScalar(1.456));
    config.Set("elem3", CoreScalar(1));

    if (config.Get("elem1").String() != string("elem1value"))
    {
        throw TestFail("Config fault 1");
    }
    if (config.Get("elem1") != CoreScalar("elem1value"))
    {
        throw TestFail("Config fault 2");
    }
    if (config.Get("elem2").Val() != 1.456)
    {
        throw TestFail("Config fault 3");
    }
    if (config.Get("elem2") != CoreScalar(1.456))
    {
        throw TestFail("Config fault 4");
    }
    if (config.Get("elem3") != CoreScalar(1))
    {
        throw TestFail("Config fault 5");
    }

    config.Set("elem3", CoreScalar(2));
    
    if (config.Get("elem3") != 2)
    {
        throw TestFail("Config fault 6");
    }
}

void
Test::Test5(void)
{
    string inFilename("../test/XMLtest.xml");
    ifstream in(CoreUtil::TranslateFilename(inFilename).c_str());
    if (!in) throw(LoaderFail(inFilename, "Could not open file"));

    CoreXML parser;
    parser.ParseStream(in);
    
}

