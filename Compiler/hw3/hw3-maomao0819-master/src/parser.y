%{

#include "include/AST/ast.hpp"
#include "include/AST/program.hpp"
#include "include/core/error.h"
#include "include/visitor/dumpvisitor.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

/* Declared by scanner.l */
extern int32_t LineNum;
extern char Buffer[512];

/* Declared by lex */
extern FILE *yyin;
extern char *yytext;

extern "C" int yylex(void);
extern "C" int yyparse();
static void yyerror(const char *msg);

static ProgramNode *root;


%}

%locations
/* include must be here, for 73's union */
%code requires{ #include "AST/program.hpp"}
%code requires{ #include "AST/FunctionDeclaration.hpp"}
%code requires{ #include "AST/Declaration.hpp"}
%code requires{ #include "AST/Statement.hpp"}
%code requires{ #include "AST/CompoundStatement.hpp"}
%code requires{ #include "AST/Simple.hpp"}
%code requires{ #include "AST/VariableReference.hpp"}
%code requires{ #include "AST/While.hpp"}
%code requires{ #include "AST/For.hpp"}
%code requires{ #include "AST/Return.hpp"}
%code requires{ #include "AST/FunctionCall.hpp"}
%code requires{ #include "AST/Expression.hpp"}
%code requires{ #include "AST/Variable.hpp"}
%code requires{ #include "AST/ConstantValue.hpp"}
%code requires{ #include "AST/Assignment.hpp"}
%code requires{ #include "AST/Print.hpp"}
%code requires{ #include "AST/Read.hpp"}
%code requires{ #include "AST/BinaryOperator.hpp"}
%code requires{ #include "AST/UnaryOperator.hpp"}
%code requires{ #include "AST/If.hpp"}
%code requires{ #include <iostream>}
%code requires{ #include "stdio.h"}
%code requires{ #include "string.h"}



    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token ASSIGN
%left<str> OR
%left<str> AND
%right<str> NOT
%left<str> LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left<str> PLUS MINUS
%left<str> MULTIPLY DIVIDE MOD
%right<str> UNARY_MINUS

    /* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token FALSE TRUE
%token PRINT READ

    /* Identifier */
%token ID

    /* Literal */
%token<str> INT_LITERAL
%token<str> REAL_LITERAL
%token STRING_LITERAL

    /* 對接lex, 告訴scanner.l要傳什麼過來 */ 
%union {
    char *str;
    char *op;
    int int_value;
    float float_value;
    ProgramNode* program;
    DeclarationNode* declaration;
    FunctionDeclarationNode* functionDeclaration;
    CompoundStatementNode* compoundStatement;
    StatementNode* statement;
    VariableNode* variable;
    SimpleNode* simple;
    ExpressionNode* expression;
    VariableReferenceNode* variableReference;
    AssignmentNode*  assignment;
    ReadNode*   read;
    ReturnNode* returnn;
    IfNode* ifn;
    ForNode* forn;
    WhileNode* wn;
    FunctionCallNode* functioncall;
}
    /* <>內的program是因為上面的program */
%type<program> Program
%type<variable> IdList
%type<str> ProgramName
%type<str> FunctionName
%type<declaration> DeclarationList
%type<declaration> Declarations
%type<declaration> Declaration
%type<FunctionDeclaration> FunctionList
%type<FunctionDeclaration> Functions
%type<functionDeclaration> FunctionDeclaration
%type<compoundStatement> CompoundStatement
%type<str> ArrDecl
%type<str> ScalarType
%type<str> Type
%type<str> TypeOrConstant
%type<str> LiteralConstant
%type<str> ID
%type<str> ReturnType
%type<str> ArrType
%type<declaration> FormalArg
%type<functionDeclaration> FormalArgList
%type<functionDeclaration> FormalArgs
%type<statement> Statement
%type<statement> Statements
%type<statement> StatementList
%type<simple> Simple
%type<expression> Expression
%type<expression> Expressions
%type<expression> ExpressionList
%type<variableReference> VariableReference
%type<variableReference> ArrForm
%type<assignment> ASSIGN
%type<returnn> Return
%type<ifn> Condition
%type<ifn> ElseOrNot
%type<functioncall> FunctionInvokation
%type<functioncall> FunctionCall
%type<forn> For
%type<wn> While
%%
    /*
       Program Units
                     */

Program:
    ProgramName
    {
        root = new ProgramNode(@1.first_line, @1.first_column);
        root -> level = 0;
    } 
    SEMICOLON ProgramBody END ProgramName 
    // when P program match correctly, run this action
    {
	    // root = newProgramNode();
	    // this method can get the information of line and column
        $$ = root;
        //= new ProgramNode(@1.first_line, @1.first_column);
        // c_string to string ,name declare in program.hpp
	    $$ -> name.assign($1);
    }
;

ProgramName:
    ID
;

ProgramBody:
    DeclarationList FunctionList CompoundStatement 
    {
        root -> c = $3;
        root -> d = $1;
    }
;

DeclarationList:
    Epsilon
    {
        $$ = new DeclarationNode(@1.first_line, @1.first_column);
        $$ -> mark = false;
    }
    |
    Declarations
    {
        
        DeclarationNode* now = $1;
        while(now -> prev !=  NULL)
        {
            now = now -> prev;
        }
        $$ = now;
    }
;

Declarations:
    Declaration
    {  
        $1 -> location.line = @1.first_line;
        $1 -> location.col = @1.first_column;
        $$ = $1;
    }
    |
    Declarations Declaration
    {
        $2 -> location.line = @2.first_line;
        $2 -> location.col = @2.first_column;
        $$ = $2;
        $1 -> next = $$;
        $$ -> prev = $1;
    }
;

FunctionList:
    Epsilon
    |
    Functions
;

Functions:
    FunctionDeclaration
    {
        $1 -> location.line = @1.first_line;
        $1 -> location.col = @1.first_column;
        root -> vf.push_back($1);
    }
    |
    Functions FunctionDeclaration
    {
        $2 -> location.line = @2.first_line;
        $2 -> location.col = @2.first_column;
        root -> vf.push_back($2);
    }
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON
    CompoundStatement
    END FunctionName
    {
        $$ = $3;
        $$ -> location.line = @1.first_line;
        $$ -> location.col = @1.first_column;
        $$ -> name.assign($1);
        if($5 != "\0")
            $$ -> returntype = $5;
        if($7 == NULL)
            $7 = new CompoundStatementNode(@7.first_line, @7.first_column);
        $$ -> c = $7;
    }
;

FunctionName:
    ID
;

FormalArgList:
    Epsilon
    {
        $$ = new FunctionDeclarationNode(@1.first_line, @1.first_column);;
    }
    |
    FormalArgs
    {
        $$ = $1;
    }
;

FormalArgs:
    FormalArg
    {
        $$ = new FunctionDeclarationNode(@1.first_line, @1.first_column);
        for(int i = 0; i < $1 -> vv.size(); i++)
            $$ -> parameter.push_back($1 -> vv[0] -> type);
        $$ -> vd.push_back($1);
    }
    |
    FormalArgs SEMICOLON FormalArg
    {
        for(int i = 0; i < $3 -> vv.size(); i++)
            $$ -> parameter.push_back($3 -> vv[i] -> type);
        $$ -> vd.push_back($3);
    }
;

FormalArg:
    IdList COLON Type
    {
        
        $$ = new DeclarationNode(@1.first_line, @1.first_column);
        while($1 -> prev != NULL)
            $1 = $1 -> prev;
        while($1 != NULL)
        {
            $1 -> type = $3;
            $$ -> vv.push_back($1);
            $1 = $1 -> next;
        }
    }

;

IdList:
    ID
    {
        VariableNode* vn = new VariableNode(@1.first_line, @1.first_column);
        $$ = vn;
        $$ -> name = $1;
    }
    |
    IdList COMMA ID
    {
        VariableNode* vn = new VariableNode(@3.first_line, @3.first_column);
        $$ = vn;
        $$ -> name = $3;
        $1 -> next = $$;
        $$ -> prev = $1;
    }
;

ReturnType:
    COLON ScalarType
    {
        $$ = $2;
    }
    |
    Epsilon
    {
        $$ = "\0";
    }
;

    /*
       Data Types and Declarations
                                   */

Declaration:
    VAR IdList COLON TypeOrConstant SEMICOLON
    {
        $$ = new DeclarationNode(@1.first_line, @1.first_column);
        while($2 -> prev != NULL)
            $2 = $2 -> prev;
        while($2 != NULL)
        {
            char* true_p = strstr ($4, "true");
            char* false_p = strstr ($4, "false");
            char* str_p = strstr ($4, "\"");
            char* float_p = strstr ($4, ".");
            char* e_p = strstr($4, "e");
            char* E_p = strstr($4, "E");
            char* plus_p = strstr($4, "+");
            char* minus_p = strstr($4, "-");
            if(float_p != NULL && *(float_p + 1) != '.')
            {
                $2 -> type =  "real";
                $2 -> c = new ConstantValueNode(@4.first_line, @4.first_column);
                $2 -> c -> float_mark = true;
                $2 -> c -> float_value = atof($4);
            }
            else if($4[0] == '0')
            {
                $2 -> type =  "integer";
                $2 -> c = new ConstantValueNode(@4.first_line, @4.first_column);
                $2 -> c -> int_mark = true;
                $2 -> c -> oct_mark = true;
                $2 -> c -> int_value = atoi($4);
            }
            else if($4[0] <= '9' && $4[0] >= '1')
            {
                $2 -> type =  "integer";
                $2 -> c = new ConstantValueNode(@4.first_line, @4.first_column);
                $2 -> c -> int_mark = true;
                $2 -> c -> int_value = atoi($4);
            }
            else if(true_p == $4 || false_p == $4)
            {
                $2 -> type =  "boolean";
                $2 -> c = new ConstantValueNode(@4.first_line, @4.first_column);
                $2 -> c -> bool_mark = true;
                $2 -> c -> bool_value = $4;
            }
            else if(str_p == $4)
            {
                $2 -> type =  "string";
                $2 -> c = new ConstantValueNode(@4.first_line, @4.first_column);
                $2 -> c -> str_mark = true;
                $2 -> c -> str_value = $4;
            }
            else
                $2 -> type = $4;
            $$ -> vv.push_back($2);
            $2 = $2 -> next;
        }
    }
;

TypeOrConstant:
    Type
    {
        $$ = $1;
    }
    |
    LiteralConstant
;

Type:
    ScalarType
    |
    ArrType
    {
        $$ = $1;
    }
;

ScalarType:
    INTEGER
    |
    REAL
    |
    STRING
    |
    BOOLEAN
;

ArrType:
    ArrDecl ScalarType
    {
        std::string s1;
        s1.assign($1);
        std::string s2;
        s2.assign($2);
        std::string str;
        str = s2 + s1;
        strcpy($$, str.c_str());
    }

;

ArrDecl:
    ARRAY INT_LITERAL TO INT_LITERAL OF
    {
        std::string s2;
        s2.assign($2);
        std::string s4;
        s4.assign($4);
        std::string str;
        str = "[" + s2 + "..." + s4 + "]";
        strcpy($$, str.c_str());
    }
    |
    ArrDecl ARRAY INT_LITERAL TO INT_LITERAL OF
    {
        std::string s1;
        s1.assign($1);
        std::string s3;
        s3.assign($3);
        std::string s5;
        s5.assign($5);
        std::string str;
        str = s1 + "[" + s3 + "..." + s5 + "]";
        strcpy($$, str.c_str());
    }
;

LiteralConstant:
    INT_LITERAL
    {
        $$ = $1;
    }
    |
    REAL_LITERAL
    {
        $$ = $1;
    }
    |
    STRING_LITERAL
    |
    TRUE
    |
    FALSE
;

    /*
       Statements
                  */

Statement:
    CompoundStatement
    {
        $$ = new StatementNode(@1.first_line, @1.first_column);
        $$ -> c = $1;
    }
    |
    Simple
    {
        $$ = new StatementNode(@1.first_line, @1.first_column);
        $$ -> s = $1;
    }
    |
    Condition
    {
        $$ = new StatementNode(@1.first_line, @1.first_column);
        $$ -> i = $1;
    }
    |
    While
    {
        $$ = new StatementNode(@1.first_line, @1.first_column);
        $$ -> w = $1;
    }
    |
    For
    {
        $$ = new StatementNode(@1.first_line, @1.first_column);
        $$ -> f = $1;
    }
    |
    Return
    {
        $$ = new StatementNode(@1.first_line, @1.first_column);
        $$ -> r = $1;
    }
    |
    FunctionInvokation
    {
        $$ = new StatementNode(@1.first_line, @1.first_column);
        $$ -> fc = $1;
    }
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END
    {
        $$ = new CompoundStatementNode(@1.first_line, @1.first_column);
        $$ -> d = $2;
        $$ -> s = $3;
    }
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON
    {
        $$ = new SimpleNode(@1.first_line, @1.first_column);
        AssignmentNode *an = new AssignmentNode(@2.first_line, @2.first_column);
        an -> vr = $1;
        an -> e = $3;
        $$ -> a = an;
    }    
    |
    PRINT Expression SEMICOLON
    {
        $$ = new SimpleNode(@1.first_line, @1.first_column);
        PrintNode* pn = new PrintNode(@1.first_line, @1.first_column);
        pn -> e = $2;        
        $$ -> p = pn;
    }
    |
    READ VariableReference SEMICOLON
    {
        $$ = new SimpleNode(@1.first_line, @1.first_column);
        ReadNode* rn = new ReadNode(@1.first_line, @1.first_column);
        rn -> vr = $2;
        $$ -> r =  rn;
    }
;

VariableReference:
    ID
    {
        $$ = new VariableReferenceNode(@1.first_line, @1.first_column);
        $$ -> name.assign($1);
    }
    |
    ID ArrForm
    {
        $$ = $2;
        $$ -> location.line = @1.first_line;
        $$ -> location.col = @1.first_column;
        $$ -> name.assign($1);
    }
;

ArrForm:
    L_BRACKET Expression R_BRACKET
    {
        $$ = new VariableReferenceNode(@1.first_line, @1.first_column);
        $$ -> arr_mark = true;
        $$ -> e = $2;
    }
    |
    ArrForm L_BRACKET Expression R_BRACKET
    {
        $$ = $1;
        $$ -> e -> next = $3;
        $$ -> e -> next -> prev = $$ -> e;
    }
;

Condition:
    IF Expression THEN
    StatementList
    ElseOrNot
    END IF
    {

        $$ = $5;
        $$ -> location.line = @1.first_line;
        $$ -> location.col = @1.first_column;
        $$ -> e = $2;
        $$ -> s = $4;
    }
;

ElseOrNot:
    ELSE
    StatementList
    {
        $$ = new IfNode(@1.first_line, @1.first_column);
        $$ -> es = $2;
    }
    |
    Epsilon
    {
        $$ = new IfNode(@1.first_line, @1.first_column);
        $$ -> else_mark = false;
    }
;

While:
    WHILE Expression DO
    StatementList
    END DO
    {

        $$ = new WhileNode(@1.first_line, @1.first_column);
        $$ -> e = $2;
        $$ -> s = $4;
    }
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    StatementList
    END DO
    {
        $$ = new ForNode(@1.first_line, @1.first_column);
        $$ -> d = new DeclarationNode(@2.first_line, @2.first_column);
        VariableNode* vn = new VariableNode(@2.first_line, @2.first_column);
        vn -> name = $2;
        vn -> type = "integer";
        $$ -> d -> vv.push_back(vn);
        $$ -> a = new AssignmentNode(@3.first_line, @3.first_column);
        VariableReferenceNode* vrn = new VariableReferenceNode(@2.first_line, @2.first_column);
        vrn -> name = $2;
        ConstantValueNode* cvn1 = new ConstantValueNode(@4.first_line, @4.first_column);
        cvn1 -> int_mark = true;
        cvn1 -> int_value = atoi($4);
        vrn -> cv = cvn1;
        $$ -> a -> vr = vrn;
        ConstantValueNode* cvn2 = new ConstantValueNode(@6.first_line, @6.first_column);
        cvn2 -> int_mark = true;
        cvn2 -> int_value = (atoi($6) - atoi($4));
        $$ -> cv = cvn2;
        $$ -> s = $8;
    }
;

Return:
    RETURN Expression SEMICOLON
    {
        $$ = new ReturnNode(@1.first_line, @1.first_column);
        $$ -> e = $2;
    }
;

FunctionInvokation:
    FunctionCall SEMICOLON
    {
        $$ = $1;
    }
;

FunctionCall:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS
    {
        $$ = new FunctionCallNode(@1.first_line, @1.first_column);
        $$ -> name.assign($1);
        $$ -> e = $3;
    }
;

ExpressionList:
    Epsilon
    {
        $$ = new ExpressionNode(@1.first_line, @1.first_column);
        $$ -> empty_mark = true;
    }
    |
    Expressions
    {
        ExpressionNode* now = $1;
        while(now -> prev !=  NULL)
        {
            now = now -> prev;
        }
        $$ = now;
    }
;

Expressions:
    Expression
    {
        $$ = $1;
    }
    |
    Expressions COMMA Expression
    {
        $$ = $3;
        $1 -> next = $$;
        $$ -> prev = $1;
    }
;

StatementList:
    Epsilon
    {
        $$ = new StatementNode(@1.first_line, @1.first_column);
    }
    |
    Statements
    {
        StatementNode* now = $1;
        while(now -> prev !=  NULL)
        {
            now = now -> prev;
        }
        $$ = now;
    }
;

Statements:
    Statement
    {
        $$ = $1;
    }
    |
    Statements Statement
    {
        $$ = $2;
        $1 -> next = $$;
        $$ -> prev = $1;
    }
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS
    {
        $$ = $2;
        $$ -> scope_mark = true;
    }
    |
    MINUS Expression %prec UNARY_MINUS
    {
        $$ = $2;
        UnaryOperatorNode* u = new UnaryOperatorNode(@1.first_line, @1.first_column);
        u -> op = "neg";
        u -> cv = $2 -> cv;
        if($$ -> bo != NULL)
        {
            if($$ -> bo -> uo1 == NULL)
                $$ -> bo -> uo1 = u;
            else
                $$ -> bo -> uo2 = u;
        }
        else
            $$ -> uom = u;
        $$ -> uo = u;
        $$ -> uo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
    }
    |
    Expression MULTIPLY Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;       
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression DIVIDE Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression MOD Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression PLUS Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression MINUS Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression LESS Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression LESS_OR_EQUAL Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression GREATER Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression GREATER_OR_EQUAL Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression EQUAL Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression NOT_EQUAL Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    NOT Expression
    {
        $$ = $2;
        UnaryOperatorNode* u = new UnaryOperatorNode(@1.first_line, @1.first_column);
        u -> op = $1;
        u -> cv = $2 -> cv;
        $$ -> uo = u;
        $$ -> uo_mark = true;
        $$ -> cv_mark = false;
    }
    |
    Expression AND Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    Expression OR Expression
    {
        $$ = $1;
        BinaryOperatorNode* b = new BinaryOperatorNode(@2.first_line, @2.first_column);
        b -> op = $2;
        BinaryOperatorNode* bon = new BinaryOperatorNode(@1.first_line, @1.first_column);
        bon = $1 -> bo;
        if($1 -> uom != NULL)
            b -> uo1 = $1 -> uom;
        if($3 -> uom != NULL)
            b -> uo1 = $3 -> uom;
        if(b -> uo1 == NULL)
        {
            if($1 -> vr != NULL)
                b -> vr1 = $1 -> vr;
            else
                b -> cv1 = $1 -> cv;
        }
        if(b -> uo2 == NULL)
        {
            if($3 -> vr != NULL)
                b -> vr2 = $3 -> vr;
            else
                b -> cv2 = $3 -> cv;
        }
        $$ -> cv_mark = false;
        $$ -> bo = b;
        $$ -> bo_mark = true;
        $$ -> cv_mark = false;
        $$ -> vr_mark = false;
        if($1 -> scope_mark)
        {
            $$ -> bo -> scope_mark = true;
            $$ -> bo -> bo_next = bon;
        }
    }
    |
    LiteralConstant
    {
        $$ = new ExpressionNode(@1.first_line, @1.first_column);
        ConstantValueNode* cv = new ConstantValueNode(@1.first_line, @1.first_column);
        char* e_p = strstr($1, "e");
        char* E_p = strstr($1, "E");
        char* float_p = strstr($1, ".");
        char* true_p = strstr ($1, "true");
        char* false_p = strstr ($1, "false");
        char* str_p = strstr ($1, "\"");
        char* int_0_p = strstr ($1, "0");
        if(true_p == $1 || false_p == $1)
        {
            cv -> str_mark = true;
            cv -> str_value = $1;
        }
        else if(str_p != NULL)
        {
            cv -> str_mark = true;
            cv -> str_value = $1;
        }
        else if(float_p != NULL || e_p != NULL || E_p != NULL)
        {
            cv -> float_mark = true;
            cv -> float_value = atof($1);
        }
        else if(int_0_p != NULL)
        {
            cv -> str_mark = true;
            cv -> str_value = $1;
            $$ -> cv_mark = true;
        }
        else
        {
            cv -> str_mark = true;
            cv -> str_value = $1;
        }
        $$ -> cv_mark = true;
        $$ -> cv = cv;
    }
    |
    VariableReference
    {
        $$ = new ExpressionNode(@1.first_line, @1.first_column);
        $$ -> vr = $1;
        $$ -> vr_mark = true;
    }
    |
    FunctionCall
    {
        $$ = new ExpressionNode(@1.first_line, @1.first_column);
        $$ -> fc_mark = true;
        $$ -> fc = $1;
        $$ -> cv_mark = false;
    }
;

    /*
       misc
            */
Epsilon:
;
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
    //CHECK(argc == 2, "Usage: ./parser <filename>\n");

    FILE *fp = fopen(argv[1], "r");

    CHECK(fp != NULL, "fopen() fails.\n");
    yyin = fp;
    yyparse();

    //freeProgramNode(root);
    // print node
    DumpVisitor dvisitor;
    root -> accept(dvisitor);

    //std::cout << "CPP works!" << std::endl;
    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");
    return 0;
}
