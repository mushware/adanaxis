 // $Id: MushcoreFlex.flex,v 1.7 2003/02/04 00:11:05 southa Exp $
%{
/*
 * $Id: MushcoreFlex.flex,v 1.7 2003/02/04 00:11:05 southa Exp $
 * $Log: MushcoreFlex.flex,v $
 * Revision 1.7  2003/02/04 00:11:05  southa
 * Build fixes
 *
 * Revision 1.6  2003/01/20 17:03:22  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.5  2003/01/20 12:23:23  southa
 * Code and interface tidying
 *
 * Revision 1.4  2003/01/18 13:33:58  southa
 * Created MushcoreSingleton
 *
 * Revision 1.3  2003/01/14 20:46:10  southa
 * Post data handling
 *
 * Revision 1.2  2003/01/12 17:33:00  southa
 * Mushcore work
 *
 * Revision 1.1  2003/01/09 14:57:07  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.10  2002/11/14 20:24:43  southa
 * Configurable config elements
 *
 * Revision 1.9  2002/07/02 14:27:12  southa
 * First floor map designer build
 *
 * Revision 1.8  2002/05/30 14:41:15  southa
 * InfernalData and loadtilemap command
 *
 * Revision 1.7  2002/05/28 13:07:04  southa
 * Command parser extensions and TIFF loader
 *
 * Revision 1.6  2002/05/10 16:39:40  southa
 * Changed .hp files to .h
 *
 * Revision 1.5  2002/03/08 22:48:14  southa
 * Added first avarisse code
 *
 * Revision 1.4  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.3  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.2  2002/03/04 22:30:49  southa
 * Interpreter work
 *
 * Revision 1.1  2002/03/02 20:35:08  southa
 * Added flex and bison parser
 *
 * C++ file autogenerated by flex
 */

/*****************************************************************************
 *
 *  MushcoreFlex.cpp is autogenerated from the file MushcoreFlex.flex.
 *  Please edit that file in preference to MushcoreFlex.cpp.
 *
 ****************************************************************************/

#include "MushcoreFlex.h"

#include "MushcoreBisonDefs.h"
#include "MushcoreFail.h"
#include "MushcoreScalar.h"
#include "MushcoreStandard.h"
#include "MushcoreSwitches.h"

#include "MushcoreSTL.h"

using namespace std;

#define YY_DECL int MushcoreFlex::Lex(MushcoreScalar *outScalar, void *inPtr)
#define YY_NEVER_INTERACTIVE 1
%}

%option noyywrap

dstring     \"[^\n"]*\"
sstring     '[^\n']*'
string      {sstring}|{dstring}
ws          [ \t]+
alpha       [A-Za-z]
dig         [0-9]
identifier  ({alpha}|_)({alpha}|{dig}|_)*
variable    \${identifier}
operator    [-+*/]
num1        {dig}+\.?([eE][-+]?{dig}+)?
num2        {dig}*\.{dig}+([eE][-+]?{dig}+)?
number      {num1}|{num2}
eos	        [;\n]
comment     ^[ \t]*#.*
%%

{ws}      /* ignore whitespace */

{comment} /* ignore comment */
        
","     {
            MUSHCORE_IFFLEXTESTING(cerr << "," << endl);
            return ',';
        }
        
"("     {
            MUSHCORE_IFFLEXTESTING(cerr << "(" << endl);
            return '(';
        }

")"     {
            MUSHCORE_IFFLEXTESTING(cerr << ")" << endl);
            return ')';
        }
                    
"+"     {
            MUSHCORE_IFFLEXTESTING(cerr << yytext << endl);
            return '+';
        }
                    
"-"     {
            MUSHCORE_IFFLEXTESTING(cerr << yytext << endl);
            return '-';
        }
                    
"*"     {
            MUSHCORE_IFFLEXTESTING(cerr << yytext << endl);
            return '*';
        }
                    
"/"     {
            MUSHCORE_IFFLEXTESTING(cerr << yytext << endl);
            return '/';
        }
                    
"/*"    {
        int c;

        while((c = yyinput()) != 0)
            {
                if(c == '*')
                {
                    if((c = yyinput()) == '/')
                        break;
                    else
                        unput(c);
                }
            }
        }

{variable} {
    MUSHCORE_IFFLEXTESTING(cerr << "variable='" << yytext << "'" << endl);
    *outScalar=yytext;
    return VARIABLE;
}

{identifier} {
    MUSHCORE_IFFLEXTESTING(cerr << "identifier='" << yytext << "'" << endl);
    *outScalar=yytext;
    return IDENTIFIER;
}

{operator} {
    MUSHCORE_IFFLEXTESTING(cerr << "operator='" << yytext << "'" << endl);
    return yytext[0];
}

{number} {
    MUSHCORE_IFFLEXTESTING(cerr << "number='" << yytext << "'" << endl);
    *outScalar=yytext;
    return NUMBER;
}

{string} {
    MUSHCORE_IFFLEXTESTING(cerr << "string='" << yytext << "'" << endl);
    *outScalar=string(&yytext[1], strlen(yytext)-2);
    return STRING;
}

{eos} {
    MUSHCORE_IFFLEXTESTING(cerr << "EOS" << endl);
    return EOS;
}

<<EOF>> {
    MUSHCORE_IFFLEXTESTING(cerr << "EOF" << endl);
    if (!m_eofFound)
    {
        m_eofFound=true;
        return END_OF_FILE;
    }
    return 0;
}


%%

MushcoreFlex::MushcoreFlex(const string& inStr): m_scalar(0), m_eofFound(false)
{
    m_buffer_state=yy_scan_bytes(inStr.c_str(), inStr.size());
    if (m_buffer_state == NULL) throw(MushcoreLogicFail("Flex failed"));
}

