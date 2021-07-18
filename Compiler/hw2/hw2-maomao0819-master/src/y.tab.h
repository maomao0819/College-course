/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INT = 259,
    REAL = 260,
    STRING = 261,
    FLOAT = 262,
    SN = 263,
    COMMA = 264,
    SEMI = 265,
    COLON = 266,
    left_PARENTHESE = 267,
    right_PARENTHESE = 268,
    left_BRACKET = 269,
    right_BRACKET = 270,
    OP_PLUS = 271,
    OP_MINUS = 272,
    OP_MUL = 273,
    OP_DIV = 274,
    OP_MOD = 275,
    ASSIGN = 276,
    LESS = 277,
    LESS_EQUAL = 278,
    LESS_MORE = 279,
    MORE_EQUAL = 280,
    MORE = 281,
    EQUAL = 282,
    AND = 283,
    OR = 284,
    NOT = 285,
    KW_ARRAY = 286,
    KW_BEGIN = 287,
    KW_BOOL = 288,
    KW_DO = 289,
    KW_ELSE = 290,
    KW_END = 291,
    KW_FALSE = 292,
    KW_FOR = 293,
    KW_INT = 294,
    KW_IF = 295,
    KW_OF = 296,
    KW_PRINT = 297,
    KW_READ = 298,
    KW_REAL = 299,
    KW_STRING = 300,
    KW_THEN = 301,
    KW_TO = 302,
    KW_TRUE = 303,
    KW_RETURN = 304,
    KW_VAR = 305,
    KW_WHILE = 306
  };
#endif
/* Tokens.  */
#define ID 258
#define INT 259
#define REAL 260
#define STRING 261
#define FLOAT 262
#define SN 263
#define COMMA 264
#define SEMI 265
#define COLON 266
#define left_PARENTHESE 267
#define right_PARENTHESE 268
#define left_BRACKET 269
#define right_BRACKET 270
#define OP_PLUS 271
#define OP_MINUS 272
#define OP_MUL 273
#define OP_DIV 274
#define OP_MOD 275
#define ASSIGN 276
#define LESS 277
#define LESS_EQUAL 278
#define LESS_MORE 279
#define MORE_EQUAL 280
#define MORE 281
#define EQUAL 282
#define AND 283
#define OR 284
#define NOT 285
#define KW_ARRAY 286
#define KW_BEGIN 287
#define KW_BOOL 288
#define KW_DO 289
#define KW_ELSE 290
#define KW_END 291
#define KW_FALSE 292
#define KW_FOR 293
#define KW_INT 294
#define KW_IF 295
#define KW_OF 296
#define KW_PRINT 297
#define KW_READ 298
#define KW_REAL 299
#define KW_STRING 300
#define KW_THEN 301
#define KW_TO 302
#define KW_TRUE 303
#define KW_RETURN 304
#define KW_VAR 305
#define KW_WHILE 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
