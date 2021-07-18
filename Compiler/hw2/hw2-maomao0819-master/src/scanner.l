%{
#include <stdint.h>
#include "y.tab.h"
#include "error.h"

#define LIST                strCat(yytext)
#define TOKEN(t)            {LIST; if (OptTok) printf("<%s>\n", #t);}
#define TOKEN_CHAR(t)       {LIST; if (OptTok) printf("<%c>\n", (t));}
#define TOKEN_STRING(t, s)  {LIST; if (OptTok) printf("<%s: %s>\n", #t, (s));}
#define MAX_LINE_LENG       512

int32_t LineNum = 1;
char Buffer[MAX_LINE_LENG];

static int32_t OptSrc = 1;
static int32_t OptTok = 1;
static char StringLiteral[MAX_LINE_LENG];
static char *BufferPtr = Buffer;

static void strCat(const char *Text);

%}

integer 0|[1-9][0-9]*
float {integer}\.(0|[0-9]*[1-9])
id [a-zA-Z][a-zA-Z0-9]*
Scientific_Notation ({integer}|{float})[Ee][+-]?({integer})
%x CCOMMENT

%%
    /* Delimiter */
"," { TOKEN_CHAR(','); return COMMA; }
";" { TOKEN_CHAR(';'); return SEMI; }
":" { TOKEN_CHAR(':'); return COLON; }
"(" { TOKEN_CHAR('('); return left_PARENTHESE; }
")" { TOKEN_CHAR(')'); return right_PARENTHESE; }
"[" { TOKEN_CHAR('['); return left_BRACKET; }
"]" { TOKEN_CHAR(']'); return right_BRACKET; }

    /* Operator */
"+"   { TOKEN_CHAR('+'); return OP_PLUS; }
"-"   { TOKEN_CHAR('-'); return OP_MINUS; }
"*"   { TOKEN_CHAR('*'); return OP_MUL; }
"/"   { TOKEN_CHAR('/'); return OP_DIV; }
"mod" { TOKEN(mod); return OP_MOD; }
":="  { TOKEN(:=); return ASSIGN; }
"<"   { TOKEN_CHAR('<'); return LESS; }
"<="  { TOKEN(<=); return LESS_EQUAL; }
"<>"  { TOKEN(<>); return LESS_MORE; }
">="  { TOKEN(>=); return MORE_EQUAL;}
">"   { TOKEN_CHAR('>'); return MORE; }
"="   { TOKEN_CHAR('='); return EQUAL; }
"and" { TOKEN(and); return AND; }
"or"  { TOKEN(or); return OR; }
"not" { TOKEN(not); return NOT; }

    /* Keyword */
"array"   { TOKEN(KWarray); return KW_ARRAY; }
"begin"   { TOKEN(KWbegin); return KW_BEGIN; }
"boolean" { TOKEN(KWboolean); return KW_BOOL; }
"def"     { TOKEN(KWdef); }
"do"      { TOKEN(KWdo); return KW_DO; }
"else"    { TOKEN(KWelse); return KW_ELSE; }
"end"     { TOKEN(KWend); return KW_END; }
"false"   { TOKEN(KWfalse); return KW_FALSE; }
"for"     { TOKEN(KWfor); return KW_FOR; }
"integer" { TOKEN(KWinteger); return KW_INT; }
"if"      { TOKEN(KWif); return KW_IF; }
"of"      { TOKEN(KWof); return KW_OF; }
"print"   { TOKEN(KWprint); return KW_PRINT; }
"read"    { TOKEN(KWread); return KW_READ; }
"real"    { TOKEN(KWreal); return KW_REAL; }
"string"  { TOKEN(KWstring); return KW_STRING; }
"then"    { TOKEN(KWthen); return KW_THEN; }
"to"      { TOKEN(KWto); return KW_TO; }
"true"    { TOKEN(KWtrue); return KW_TRUE; }
"return"  { TOKEN(KWreturn); return KW_RETURN; }
"var"     { TOKEN(KWvar); return KW_VAR; }
"while"   { TOKEN(KWwhile); return KW_WHILE; }

    /* Identifier */
{id} { TOKEN_STRING(id, yytext); return ID; }

    /* Integer (decimal/octal) */
{integer} { TOKEN_STRING(integer, yytext); return INT; }
0[0-7]+   { TOKEN_STRING(oct_integer, yytext); }

    /* Floating-Point */
{float} { TOKEN_STRING(float, yytext); return FLOAT; }

    /* Scientific Notation [Ee][+-]?[0-9]+ */
{Scientific_Notation} { TOKEN_STRING(scientific, yytext); return SN; }

    /* [-]?({integer}|{float}|{Scientific_Notation}) {return REAL; } */
    /* String */
\"([^"\n]|\"\")*\" {
    char *YytextPtr = yytext;
    char *StrPtr = StringLiteral;

    /* Condition guard of the end of string literal
       Check only when *YytextPtr == '"' */
    while (*(YytextPtr + 1) != '\0') {
        ++YytextPtr;

        /* Handle the situation of double quotes */
        if (*YytextPtr == '"' && *(YytextPtr + 1) != '\0')
            *StrPtr++ = *YytextPtr++;

        while (*YytextPtr != '"')
            *StrPtr++ = *YytextPtr++;
    }
    *StrPtr = '\0';
    TOKEN_STRING(string, StringLiteral);
    return STRING; 
}
    /* Whitespace */
[ \t]+ { LIST; }

    /* Pseudocomment */
"//&"[ST][+-].* {
    LIST;
    char option = yytext[3];
    switch (option) {
    case 'S':
        OptSrc = (yytext[4] == '+') ? 1 : 0;
        break;
    case 'T':
        OptTok = (yytext[4] == '+') ? 1 : 0;
        break;
    }
}

    /* C++ Style Comment */
"//".* { LIST; }

    /* C Style Comment */
"/*"           { LIST; BEGIN(CCOMMENT); }
<CCOMMENT>"*/" { LIST; BEGIN(INITIAL); }
<CCOMMENT>.    { LIST; }

    /* Newline */
<INITIAL,CCOMMENT>\n {
    if (OptSrc)
        printf("%d: %s\n", LineNum, Buffer);
    ++LineNum;
    Buffer[0] = '\0';
    BufferPtr = Buffer;
}

    /* Catch the character which is not accepted by rules above */
. {
    printf("Error at line %d: bad character \"%s\"\n", LineNum, yytext);
    exit(-1);
}

%%

static void strCat(const char *Text) {
    while (*Text) {
        *BufferPtr++ = *Text++;
    }
    *BufferPtr = '\0';
}
