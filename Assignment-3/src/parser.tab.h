/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 3 "src/parser.y"

    struct Node;
    struct Symbol;

#line 54 "src/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INCLUDE = 258,                 /* INCLUDE  */
    TYPEDEF = 259,                 /* TYPEDEF  */
    TYPE_NAME = 260,               /* TYPE_NAME  */
    PLUS = 261,                    /* PLUS  */
    MINUS = 262,                   /* MINUS  */
    STAR = 263,                    /* STAR  */
    DIVIDE = 264,                  /* DIVIDE  */
    MODULUS = 265,                 /* MODULUS  */
    ASSIGN = 266,                  /* ASSIGN  */
    INCREMENT = 267,               /* INCREMENT  */
    DECREMENT = 268,               /* DECREMENT  */
    EQUAL = 269,                   /* EQUAL  */
    NOT_EQUAL = 270,               /* NOT_EQUAL  */
    LESS_THAN = 271,               /* LESS_THAN  */
    GREATER_THAN = 272,            /* GREATER_THAN  */
    LESS_EQUAL = 273,              /* LESS_EQUAL  */
    GREATER_EQUAL = 274,           /* GREATER_EQUAL  */
    BITWISE_AND = 275,             /* BITWISE_AND  */
    BITWISE_OR = 276,              /* BITWISE_OR  */
    BITWISE_XOR = 277,             /* BITWISE_XOR  */
    LEFT_SHIFT = 278,              /* LEFT_SHIFT  */
    RIGHT_SHIFT = 279,             /* RIGHT_SHIFT  */
    LOGICAL_NOT = 280,             /* LOGICAL_NOT  */
    LOGICAL_AND = 281,             /* LOGICAL_AND  */
    LOGICAL_OR = 282,              /* LOGICAL_OR  */
    PLUS_EQUAL = 283,              /* PLUS_EQUAL  */
    MINUS_EQUAL = 284,             /* MINUS_EQUAL  */
    STAR_EQUAL = 285,              /* STAR_EQUAL  */
    DIV_EQUAL = 286,               /* DIV_EQUAL  */
    MOD_EQUAL = 287,               /* MOD_EQUAL  */
    AND_EQUAL = 288,               /* AND_EQUAL  */
    OR_EQUAL = 289,                /* OR_EQUAL  */
    XOR_EQUAL = 290,               /* XOR_EQUAL  */
    LEFT_SHIFT_EQ = 291,           /* LEFT_SHIFT_EQ  */
    RIGHT_SHIFT_EQ = 292,          /* RIGHT_SHIFT_EQ  */
    LROUND = 293,                  /* LROUND  */
    RROUND = 294,                  /* RROUND  */
    LCURLY = 295,                  /* LCURLY  */
    RCURLY = 296,                  /* RCURLY  */
    LSQUARE = 297,                 /* LSQUARE  */
    RSQUARE = 298,                 /* RSQUARE  */
    SEMICOLON = 299,               /* SEMICOLON  */
    COLON = 300,                   /* COLON  */
    COMMA = 301,                   /* COMMA  */
    DOT = 302,                     /* DOT  */
    QUESTION_MARK = 303,           /* QUESTION_MARK  */
    IF = 304,                      /* IF  */
    ELSE = 305,                    /* ELSE  */
    SWITCH = 306,                  /* SWITCH  */
    CASE = 307,                    /* CASE  */
    DEFAULT = 308,                 /* DEFAULT  */
    WHILE = 309,                   /* WHILE  */
    DO = 310,                      /* DO  */
    FOR = 311,                     /* FOR  */
    GOTO = 312,                    /* GOTO  */
    CONTINUE = 313,                /* CONTINUE  */
    BREAK = 314,                   /* BREAK  */
    RETURN = 315,                  /* RETURN  */
    UNTIL = 316,                   /* UNTIL  */
    VOID = 317,                    /* VOID  */
    INT = 318,                     /* INT  */
    DOUBLE = 319,                  /* DOUBLE  */
    CHAR = 320,                    /* CHAR  */
    BOOL = 321,                    /* BOOL  */
    LONG = 322,                    /* LONG  */
    TRUE = 323,                    /* TRUE  */
    FALSE = 324,                   /* FALSE  */
    NULLPTR = 325,                 /* NULLPTR  */
    TILDE = 326,                   /* TILDE  */
    STATIC = 327,                  /* STATIC  */
    CONST = 328,                   /* CONST  */
    SIZEOF = 329,                  /* SIZEOF  */
    STRING_LITERAL = 330,          /* STRING_LITERAL  */
    CLASS = 331,                   /* CLASS  */
    STRUCT = 332,                  /* STRUCT  */
    PUBLIC = 333,                  /* PUBLIC  */
    PRIVATE = 334,                 /* PRIVATE  */
    PROTECTED = 335,               /* PROTECTED  */
    IDENTIFIER = 336,              /* IDENTIFIER  */
    INVALID_IDENTIFIER = 337,      /* INVALID_IDENTIFIER  */
    DECIMAL_LITERAL = 338,         /* DECIMAL_LITERAL  */
    DOUBLE_LITERAL = 339,          /* DOUBLE_LITERAL  */
    EXPONENT_LITERAL = 340,        /* EXPONENT_LITERAL  */
    CHARACTER_LITERAL = 341,       /* CHARACTER_LITERAL  */
    LOWER_THAN_ELSE = 342          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 351 "src/parser.y"

    char* str;
    Node* node;

#line 163 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
