/*
 * $Id: main.cpp,v 1.3 2002/03/04 22:30:47 southa Exp $
 * $Log: main.cpp,v $
 * Revision 1.3  2002/03/04 22:30:47  southa
 * Interpreter work
 *
 * Revision 1.2  2002/02/24 22:49:33  southa
 * Got working under cygwin
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "CoreStandard.hp"
#include "CoreApp.hp"
#include "CoreAppHandler.hp"

int main(int argc, char *argv[])
{
    string str;
    for (int i=1; i<argc; i++)
    {
        str.append(argv[i]);
        if (i+1 != argc) str.append(" ");
    }
    str.append(";");
    cout << "Command line was '" << str << "'" << endl;
    try
    {
        CoreApp::Instance().Process(str);
        CoreAppHandler::Instance().Initialise();
        CoreAppHandler::Instance().MainLoop();
    }
    catch (exception& e)
    {
        cerr << "Standard exception: " << e.what() << endl;
        return 1;
    }
    catch (string& str)
    {
        cerr << "Exception: " << str << endl;
        return 1;
    }
    catch (const char *c_str)
    {
        cerr << "Exception: " << c_str << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception" << endl;
        return 1;
    }
    return 0;
}
