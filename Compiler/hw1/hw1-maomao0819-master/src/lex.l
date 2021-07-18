%{

//第1段：聲明段 Definitions

#define LIST               strcat(buf, yytext)
#define token(t)           {LIST; if (Opt_T) printf("<%s>\n", #t);}
#define tokenChar(t)       {LIST; if (Opt_T) printf("<%c>\n", (t));}
#define tokenInteger(t, i) {LIST; if (Opt_T) printf("<%s: %d>\n", #t, (i));}
#define tokenString(t, s)  {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (s));}
// Define your token macros here
//  for example :
#define tokenScientific(t, s) {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (s));}
#define tokenFloat(t, f)   {LIST; if (Opt_T) printf("<%s: %s>\n", #t, (f));}
//    #define <any other macros you needed>

#define MAX_LINE_LENG      256

int Opt_S = 1;
int Opt_T = 1;
int linenum = 1;
char buf[MAX_LINE_LENG]; 
%}

%x COMMENT

digit 		[0-9]
digits		{digit}+
posint		[1-9]{digit}*
posint_with_symbol	[+]{posint}
negint 		[-]{posint}
int             [0]|{posint}
dec_int		{posint}|{posint_with_symbol}|{negint}
oct_int		[0][0-7]+
dot 		\.
float_num	{int}{dot}([0]|{digits}*[1-9])
scientific_num	({float_num}|{int})[eE]{dec_int}
letter 		[a-zA-Z]
id 		{letter}({letter}|{digit})*
printable_char  [\40-\176]
string 		[\"]{printable_char}*[\"]
one_line_comment [\/][\/]{printable_char}*
/*one or more space*/
blank_chars	[ \f\r\t\v]+

/*第2段：規則段 Rules*/
%%
","     { tokenChar(','); }
";"     { tokenChar(';'); }
":"     { tokenChar(':'); }
"("     { tokenChar('('); }
")"     { tokenChar(')'); }
"["     { tokenChar('['); }
"]"     { tokenChar(']'); }

"+"     { tokenChar('+'); }
"-"     { tokenChar('-'); }
"*"     { tokenChar('*'); }
"/"     { tokenChar('/'); }
"mod"   { token(mod); }
":="    { token(:=); }

"<"     { tokenChar('<'); }
"<="    { token(<=); }
"<>"    { token(<>); }
">="    { token(>=); }
">"     { tokenChar('>'); }
"="     { tokenChar(']'); }

"and"   { token(and); }
"or"    { token(or); }
"not"   { token(not); }

"array"		{ token(KWarray); }
"begin" 	{ token(KWbegin); }
"boolean" 	{ token(KWboolean); }
"def" 		{ token(KWdef); }
"do" 		{ token(KWdo); }
"else" 		{ token(KWelse); }
"end" 		{ token(KWend); }
"false" 	{ token(KWfalse); }
"for" 		{ token(KWfor); }
"integer" 	{ token(KWinteger); }
"if" 		{ token(KWif); }
"of" 		{ token(KWof); }
"print" 	{ token(KWprint); }
"read" 		{ token(KWread); }
"real" 		{ token(KWreal); }
"string" 	{ token(KWstring); }
"then" 		{ token(KWthen); }
"to" 		{ token(KWto); }
"true" 		{ token(KWtrue); }
"return" 	{ token(KWreturn); }
"var" 		{ token(KWvar); }
"while" 	{ token(KWwhile); }

"//&S+"         { LIST; Opt_S = 1; }
"//&S-"         { LIST; Opt_S = 0; }
"//&T+"         { LIST; Opt_T = 1; }
"//&T-"         { LIST; Opt_T = 0; }

{int}		{ tokenInteger(integer, atoi(yytext)); }
{oct_int}	{ tokenString(oct_integer, yytext); }
{float_num}     { tokenFloat(float, yytext); }
{scientific_num}	{ tokenScientific(scientific, yytext); }
{id}		{ tokenString(id, yytext); }

{string}	{ 				
			/*int len = yyleng - 2;
			char s[MAX_LINE_LENG];		
			strncpy(s, yytext + 1, len);
			tokenString(string, s);*/
			LIST;
			if (Opt_T) 
			{			
				printf("<string: ");
				int count = 0;
				for (int i = 1; i < yyleng - 1; i++)
				{
					if (*(yytext + i) == '"' && *(yytext + i + 1) == '"')
					{
						printf("\"");
						i++;
					}
					else 
						printf("%c", *(yytext + i));
				} 
				printf(">\n");
			}
		}
{blank_chars}	{ LIST; }

{one_line_comment}	{ LIST; }

"/*"    	{ LIST; BEGIN COMMENT; }

<COMMENT>"*/"	{ LIST; BEGIN INITIAL; }
<COMMENT>\n	{  
		  	if (Opt_S)
                        	printf("%d: %s\n", linenum, buf);
                	linenum++;
                	buf[0] = '\0';
		}
<COMMENT>.     	{ LIST; }


\n      {
          	if (Opt_S)
            		printf("%d: %s\n", linenum, buf);
          	linenum++;
          	buf[0] = '\0';
        }
.       {
          /* error */
          printf("Error at line %d: bad character \"%s\"\n", linenum, yytext );
          exit(-1);
        }
%%
//第3段：C函數定義段 Routines
int main( int argc, char **argv )
{
  if( argc != 2 ) {
    fprintf( stderr, "Usage: ./scanner [filename]\n" );
    exit(0);
  }
	
  FILE *fp = fopen( argv[1], "r" );
  if( fp == NULL ) {
    fprintf( stderr, "Open file error\n" );
    exit(-1);
  }
	
  yyin = fp;

  yylex();
 
  exit(0);
}
