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
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

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
    PLUS = 259,                    /* PLUS  */
    MINUS = 260,                   /* MINUS  */
    STAR = 261,                    /* STAR  */
    DIVIDE = 262,                  /* DIVIDE  */
    MODULUS = 263,                 /* MODULUS  */
    ASSIGN = 264,                  /* ASSIGN  */
    INCREMENT = 265,               /* INCREMENT  */
    DECREMENT = 266,               /* DECREMENT  */
    EQUAL = 267,                   /* EQUAL  */
    NOT_EQUAL = 268,               /* NOT_EQUAL  */
    LESS_THAN = 269,               /* LESS_THAN  */
    GREATER_THAN = 270,            /* GREATER_THAN  */
    LESS_EQUAL = 271,              /* LESS_EQUAL  */
    GREATER_EQUAL = 272,           /* GREATER_EQUAL  */
    BITWISE_AND = 273,             /* BITWISE_AND  */
    BITWISE_OR = 274,              /* BITWISE_OR  */
    BITWISE_XOR = 275,             /* BITWISE_XOR  */
    LEFT_SHIFT = 276,              /* LEFT_SHIFT  */
    RIGHT_SHIFT = 277,             /* RIGHT_SHIFT  */
    ARROW = 278,                   /* ARROW  */
    LOGICAL_NOT = 279,             /* LOGICAL_NOT  */
    LOGICAL_AND = 280,             /* LOGICAL_AND  */
    LOGICAL_OR = 281,              /* LOGICAL_OR  */
    PLUS_EQUAL = 282,              /* PLUS_EQUAL  */
    MINUS_EQUAL = 283,             /* MINUS_EQUAL  */
    STAR_EQUAL = 284,              /* STAR_EQUAL  */
    DIV_EQUAL = 285,               /* DIV_EQUAL  */
    MOD_EQUAL = 286,               /* MOD_EQUAL  */
    AND_EQUAL = 287,               /* AND_EQUAL  */
    OR_EQUAL = 288,                /* OR_EQUAL  */
    XOR_EQUAL = 289,               /* XOR_EQUAL  */
    LEFT_SHIFT_EQ = 290,           /* LEFT_SHIFT_EQ  */
    RIGHT_SHIFT_EQ = 291,          /* RIGHT_SHIFT_EQ  */
    LROUND = 292,                  /* LROUND  */
    RROUND = 293,                  /* RROUND  */
    LCURLY = 294,                  /* LCURLY  */
    RCURLY = 295,                  /* RCURLY  */
    LSQUARE = 296,                 /* LSQUARE  */
    RSQUARE = 297,                 /* RSQUARE  */
    SEMICOLON = 298,               /* SEMICOLON  */
    COLON = 299,                   /* COLON  */
    COMMA = 300,                   /* COMMA  */
    DOT = 301,                     /* DOT  */
    QUESTION_MARK = 302,           /* QUESTION_MARK  */
    TILDE = 303,                   /* TILDE  */
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
    SIZEOF = 317,                  /* SIZEOF  */
    VOID = 318,                    /* VOID  */
    INT = 319,                     /* INT  */
    DOUBLE = 320,                  /* DOUBLE  */
    CHAR = 321,                    /* CHAR  */
    BOOL = 322,                    /* BOOL  */
    STRING = 323,                  /* STRING  */
    LONG = 324,                    /* LONG  */
    TRUE = 325,                    /* TRUE  */
    FALSE = 326,                   /* FALSE  */
    NULLPTR = 327,                 /* NULLPTR  */
    AUTO = 328,                    /* AUTO  */
    STATIC = 329,                  /* STATIC  */
    CONST = 330,                   /* CONST  */
    CLASS = 331,                   /* CLASS  */
    STRUCT = 332,                  /* STRUCT  */
    PUBLIC = 333,                  /* PUBLIC  */
    PRIVATE = 334,                 /* PRIVATE  */
    PROTECTED = 335,               /* PROTECTED  */
    DELETE = 336,                  /* DELETE  */
    NEW = 337,                     /* NEW  */
    CIN = 338,                     /* CIN  */
    COUT = 339,                    /* COUT  */
    ENDL = 340,                    /* ENDL  */
    TYPE_NAME = 341,               /* TYPE_NAME  */
    IDENTIFIER = 342,              /* IDENTIFIER  */
    DECIMAL_LITERAL = 343,         /* DECIMAL_LITERAL  */
    DOUBLE_LITERAL = 344,          /* DOUBLE_LITERAL  */
    EXPONENT_LITERAL = 345,        /* EXPONENT_LITERAL  */
    CHARACTER_LITERAL = 346,       /* CHARACTER_LITERAL  */
    STRING_LITERAL = 347,          /* STRING_LITERAL  */
    FUNCTION = 348,                /* FUNCTION  */
    INVALID_IDENTIFIER = 349       /* INVALID_IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 170 "src/parser.y"
 
    char *str; 

#line 162 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
