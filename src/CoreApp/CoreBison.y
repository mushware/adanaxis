%{
/*
 * $Id: CoreBison.y,v 1.9 2002/06/04 22:50:02 southa Exp $
 * $Log: CoreBison.y,v $
 * Revision 1.9  2002/06/04 22:50:02  southa
 * Fixes to mac project
 *
 * Revision 1.8  2002/05/30 14:41:13  southa
 * GameData and loadtilemap command
 *
 */
#include "CoreBison.h"
#include "CoreCommand.h"
#include "CoreEnv.h"
    
#define YYSTYPE CoreScalar
#define YYPARSE_PARAM inBison
#define YYLEX_PARAM inBison
#define INBISON (static_cast<CoreBison *>(inBison))
#define CoreBison_lex INBISON->Lex
#define YYDEBUG 1
#define YYERROR_VERBOSE 1

using namespace std;
    
int yyerror( char *s);
%}

%pure_parser
%token NUMBER
%token VARIABLE
%token IDENTIFIER
%token STRING
%token EOS
%token END_OF_FILE

%% /* Grammar rules and actions follow */

input:    /* empty */
| input statement;
end: EOS
| END_OF_FILE
;
command: IDENTIFIER {
    INBISON->ClearParams();
}
;
scalar: VARIABLE {$$=CoreEnv::Instance().VariableGet($1.StringGet().substr(1)).StringGet();}
| STRING {$$ = $1.StringGet();}
| NUMBER {$$ = $1.ValGet();}
| scalar '+' scalar {$$ = $1.StringGet()+$3.StringGet(); /* Enhance me */ }
;
parameter: scalar {
    INBISON->PushParam($1);
}
;
parameter_list: /* empty */
| parameter
| parameter_list ',' parameter
;
command_tail: /* empty */
| '(' parameter_list ')'
;
statement: end
| command command_tail end {
    $$=INBISON->Despatch($1);
}
;
%%

int yyerror(char *s)
{
    cerr << "Bison error: " << s << endl;
    return 0;
}

int
CoreBison::Parse(CoreCommand& inCommand)
{
    m_command=&inCommand;
    return yyparse(this);
}

void
CoreBison::PushParam(CoreScalar& inParam)
{
    m_command->PushParam(inParam);
}

void
CoreBison::ClearParams(void)
{
    m_command->ClearParams();
}

CoreScalar 
CoreBison::Despatch(CoreScalar& inName)
{
    string name;
    inName.Get(name);
    m_command->NameSet(name);
    return m_command->Despatch();
}

