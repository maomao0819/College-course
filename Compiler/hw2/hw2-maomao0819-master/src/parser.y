%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "error.h"

extern int32_t LineNum;   /* declared in scanner.l */
extern char Buffer[512];  /* declared in scanner.l */
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */

extern int yylex(void); 
static void yyerror(const char *msg);
%}

%token ID INT REAL STRING FLOAT SN
%token COMMA SEMI COLON left_PARENTHESE right_PARENTHESE left_BRACKET right_BRACKET
%token OP_PLUS OP_MINUS OP_MUL OP_DIV OP_MOD ASSIGN LESS LESS_EQUAL LESS_MORE MORE_EQUAL MORE EQUAL AND OR NOT
%token KW_ARRAY KW_BEGIN KW_BOOL KW_DO KW_ELSE KW_END KW_FALSE KW_FOR KW_INT KW_IF KW_OF KW_PRINT KW_READ KW_REAL KW_STRING KW_THEN KW_TO KW_TRUE KW_RETURN KW_VAR KW_WHILE 
%%
program: ID SEMI declaration func_list compound KW_END ID;
func_list: func_list func | %empty;
func: non_procedure func_content | procedure func_content;
func_arg: formal_args | %empty;
formal_args: formal_args SEMI formal_arg | formal_arg;
formal_arg: ID_list COLON type; 
func_return: COLON type ;
func_content: compound KW_END ID | %empty;
procedure: ID left_PARENTHESE func_arg right_PARENTHESE SEMI;
non_procedure: ID left_PARENTHESE func_arg right_PARENTHESE func_return SEMI;
declaration: Var declaration | Const declaration | %empty;
Var: KW_VAR ID_list COLON type SEMI;
type: array_type | scalar_type;
array_type: KW_ARRAY INT KW_TO INT KW_OF type;
Const: KW_VAR ID_list COLON literal_const SEMI;
literal_const: integer_literal | STRING | bool ;
integer_literal: INT | FLOAT | SN | REAL;
scalar_type: KW_INT | KW_REAL | KW_STRING | KW_BOOL;
bool: KW_TRUE | KW_FALSE;
ID_list: ID_list COMMA ID | ID;
Statements: Statements Statement | %empty;
Statement: compound | simple | conditional | while | for 
	 | return | function_invocation;
compound: KW_BEGIN declaration Statements KW_END; 
simple: var_ref ASSIGN expr SEMI | KW_PRINT var_ref SEMI | KW_PRINT expr SEMI 
       | KW_PRINT func | KW_READ var_ref SEMI;
var_ref: ID | array_ref;
array_ref: ID expr_parameter ;
expr_parameter: left_BRACKET exprs right_BRACKET expr_parameter | %empty; 
exprs: exprs COMMA expr | expr;
expr: expr operator component | component ;
operator: Arithmetic_op | Relational_op | logical_op;
Arithmetic_op: OP_PLUS | OP_MINUS | OP_MUL | OP_DIV | OP_MOD;
Relational_op: LESS | LESS_EQUAL | LESS_MORE | MORE_EQUAL | MORE | EQUAL;
logical_op: AND | OR | NOT;
component: literal_const | array_ref | func_invocation | group ;
group: left_PARENTHESE expr right_PARENTHESE | left_PARENTHESE group right_PARENTHESE;
func_invocation: ID left_PARENTHESE exprs right_PARENTHESE | procedure ;
conditional: match_cond | unmatch_cond;
match_cond: KW_IF expr KW_THEN Statements KW_ELSE Statements KW_END KW_IF;
unmatch_cond:  KW_IF expr KW_THEN Statements KW_END KW_IF;
while: KW_WHILE expr KW_DO Statements KW_END KW_DO;
for: KW_FOR ID ASSIGN INT KW_TO INT KW_DO Statements KW_END KW_DO;
return: KW_RETURN expr SEMI;
function_invocation: func_invocation SEMI | procedure; 

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            LineNum, Buffer, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    CHECK(argc == 2, "Usage: ./parser <filename>\n");

    FILE *fp = fopen(argv[1], "r");

    CHECK(fp != NULL, "fopen() fails.\n");
    yyin = fp;
    yyparse();

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
