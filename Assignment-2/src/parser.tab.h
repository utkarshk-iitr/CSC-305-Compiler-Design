/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INCLUDE = 258,
     PLUS = 259,
     MINUS = 260,
     STAR = 261,
     DIVIDE = 262,
     MODULUS = 263,
     ASSIGN = 264,
     INCREMENT = 265,
     DECREMENT = 266,
     EQUAL = 267,
     NOT_EQUAL = 268,
     LESS_THAN = 269,
     GREATER_THAN = 270,
     LESS_EQUAL = 271,
     GREATER_EQUAL = 272,
     BITWISE_AND = 273,
     BITWISE_OR = 274,
     BITWISE_XOR = 275,
     LEFT_SHIFT = 276,
     RIGHT_SHIFT = 277,
     ARROW = 278,
     LOGICAL_NOT = 279,
     LOGICAL_AND = 280,
     LOGICAL_OR = 281,
     PLUS_EQUAL = 282,
     MINUS_EQUAL = 283,
     STAR_EQUAL = 284,
     DIV_EQUAL = 285,
     MOD_EQUAL = 286,
     AND_EQUAL = 287,
     OR_EQUAL = 288,
     XOR_EQUAL = 289,
     LEFT_SHIFT_EQ = 290,
     RIGHT_SHIFT_EQ = 291,
     LROUND = 292,
     RROUND = 293,
     LCURLY = 294,
     RCURLY = 295,
     LSQUARE = 296,
     RSQUARE = 297,
     SEMICOLON = 298,
     COLON = 299,
     COMMA = 300,
     DOT = 301,
     QUESTION_MARK = 302,
     TILDE = 303,
     IF = 304,
     ELSE = 305,
     SWITCH = 306,
     CASE = 307,
     DEFAULT = 308,
     WHILE = 309,
     DO = 310,
     FOR = 311,
     GOTO = 312,
     CONTINUE = 313,
     BREAK = 314,
     RETURN = 315,
     UNTIL = 316,
     SIZEOF = 317,
     VOID = 318,
     INT = 319,
     DOUBLE = 320,
     CHAR = 321,
     BOOL = 322,
     STRING = 323,
     LONG = 324,
     TRUE = 325,
     FALSE = 326,
     NULLPTR = 327,
     AUTO = 328,
     STATIC = 329,
     CONST = 330,
     CLASS = 331,
     STRUCT = 332,
     PUBLIC = 333,
     PRIVATE = 334,
     PROTECTED = 335,
     DELETE = 336,
     NEW = 337,
     CIN = 338,
     COUT = 339,
     ENDL = 340,
     TYPE_NAME = 341,
     IDENTIFIER = 342,
     DECIMAL_LITERAL = 343,
     DOUBLE_LITERAL = 344,
     EXPONENT_LITERAL = 345,
     CHARACTER_LITERAL = 346,
     STRING_LITERAL = 347,
     FUNCTION = 348,
     INVALID_IDENTIFIER = 349
   };
#endif
/* Tokens.  */
#define INCLUDE 258
#define PLUS 259
#define MINUS 260
#define STAR 261
#define DIVIDE 262
#define MODULUS 263
#define ASSIGN 264
#define INCREMENT 265
#define DECREMENT 266
#define EQUAL 267
#define NOT_EQUAL 268
#define LESS_THAN 269
#define GREATER_THAN 270
#define LESS_EQUAL 271
#define GREATER_EQUAL 272
#define BITWISE_AND 273
#define BITWISE_OR 274
#define BITWISE_XOR 275
#define LEFT_SHIFT 276
#define RIGHT_SHIFT 277
#define ARROW 278
#define LOGICAL_NOT 279
#define LOGICAL_AND 280
#define LOGICAL_OR 281
#define PLUS_EQUAL 282
#define MINUS_EQUAL 283
#define STAR_EQUAL 284
#define DIV_EQUAL 285
#define MOD_EQUAL 286
#define AND_EQUAL 287
#define OR_EQUAL 288
#define XOR_EQUAL 289
#define LEFT_SHIFT_EQ 290
#define RIGHT_SHIFT_EQ 291
#define LROUND 292
#define RROUND 293
#define LCURLY 294
#define RCURLY 295
#define LSQUARE 296
#define RSQUARE 297
#define SEMICOLON 298
#define COLON 299
#define COMMA 300
#define DOT 301
#define QUESTION_MARK 302
#define TILDE 303
#define IF 304
#define ELSE 305
#define SWITCH 306
#define CASE 307
#define DEFAULT 308
#define WHILE 309
#define DO 310
#define FOR 311
#define GOTO 312
#define CONTINUE 313
#define BREAK 314
#define RETURN 315
#define UNTIL 316
#define SIZEOF 317
#define VOID 318
#define INT 319
#define DOUBLE 320
#define CHAR 321
#define BOOL 322
#define STRING 323
#define LONG 324
#define TRUE 325
#define FALSE 326
#define NULLPTR 327
#define AUTO 328
#define STATIC 329
#define CONST 330
#define CLASS 331
#define STRUCT 332
#define PUBLIC 333
#define PRIVATE 334
#define PROTECTED 335
#define DELETE 336
#define NEW 337
#define CIN 338
#define COUT 339
#define ENDL 340
#define TYPE_NAME 341
#define IDENTIFIER 342
#define DECIMAL_LITERAL 343
#define DOUBLE_LITERAL 344
#define EXPONENT_LITERAL 345
#define CHARACTER_LITERAL 346
#define STRING_LITERAL 347
#define FUNCTION 348
#define INVALID_IDENTIFIER 349




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 170 "src/parser.y"
{ 
    char *str; 
}
/* Line 1529 of yacc.c.  */
#line 241 "src/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

