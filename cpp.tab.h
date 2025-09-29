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

#ifndef YY_YY_CPP_TAB_H_INCLUDED
# define YY_YY_CPP_TAB_H_INCLUDED
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
    TYPEDEF = 259,                 /* TYPEDEF  */
    PLUS = 260,                    /* PLUS  */
    MINUS = 261,                   /* MINUS  */
    STAR = 262,                    /* STAR  */
    DIVIDE = 263,                  /* DIVIDE  */
    MODULUS = 264,                 /* MODULUS  */
    ASSIGN = 265,                  /* ASSIGN  */
    INCREMENT = 266,               /* INCREMENT  */
    DECREMENT = 267,               /* DECREMENT  */
    EQUAL = 268,                   /* EQUAL  */
    NOT_EQUAL = 269,               /* NOT_EQUAL  */
    LESS_THAN = 270,               /* LESS_THAN  */
    GREATER_THAN = 271,            /* GREATER_THAN  */
    LESS_EQUAL = 272,              /* LESS_EQUAL  */
    GREATER_EQUAL = 273,           /* GREATER_EQUAL  */
    BITWISE_AND = 274,             /* BITWISE_AND  */
    BITWISE_OR = 275,              /* BITWISE_OR  */
    BITWISE_XOR = 276,             /* BITWISE_XOR  */
    LEFT_SHIFT = 277,              /* LEFT_SHIFT  */
    RIGHT_SHIFT = 278,             /* RIGHT_SHIFT  */
    ARROW = 279,                   /* ARROW  */
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
    TILDE = 304,                   /* TILDE  */
    IF = 305,                      /* IF  */
    ELSE = 306,                    /* ELSE  */
    SWITCH = 307,                  /* SWITCH  */
    CASE = 308,                    /* CASE  */
    DEFAULT = 309,                 /* DEFAULT  */
    WHILE = 310,                   /* WHILE  */
    DO = 311,                      /* DO  */
    FOR = 312,                     /* FOR  */
    GOTO = 313,                    /* GOTO  */
    CONTINUE = 314,                /* CONTINUE  */
    BREAK = 315,                   /* BREAK  */
    RETURN = 316,                  /* RETURN  */
    UNTIL = 317,                   /* UNTIL  */
    SIZEOF = 318,                  /* SIZEOF  */
    VOID = 319,                    /* VOID  */
    INT = 320,                     /* INT  */
    DOUBLE = 321,                  /* DOUBLE  */
    CHAR = 322,                    /* CHAR  */
    BOOL = 323,                    /* BOOL  */
    STRING = 324,                  /* STRING  */
    LONG = 325,                    /* LONG  */
    TRUE = 326,                    /* TRUE  */
    FALSE = 327,                   /* FALSE  */
    NULLPTR = 328,                 /* NULLPTR  */
    AUTO = 329,                    /* AUTO  */
    STATIC = 330,                  /* STATIC  */
    CONST = 331,                   /* CONST  */
    CLASS = 332,                   /* CLASS  */
    STRUCT = 333,                  /* STRUCT  */
    PUBLIC = 334,                  /* PUBLIC  */
    PRIVATE = 335,                 /* PRIVATE  */
    PROTECTED = 336,               /* PROTECTED  */
    DELETE = 337,                  /* DELETE  */
    NEW = 338,                     /* NEW  */
    CIN = 339,                     /* CIN  */
    COUT = 340,                    /* COUT  */
    ENDL = 341,                    /* ENDL  */
    IDENTIFIER = 342,              /* IDENTIFIER  */
    DECIMAL_LITERAL = 343,         /* DECIMAL_LITERAL  */
    DOUBLE_LITERAL = 344,          /* DOUBLE_LITERAL  */
    EXPONENT_LITERAL = 345,        /* EXPONENT_LITERAL  */
    CHARACTER_LITERAL = 346,       /* CHARACTER_LITERAL  */
    STRING_LITERAL = 347,          /* STRING_LITERAL  */
    FUNCTION = 348,                /* FUNCTION  */
    CONSTANT = 349                 /* CONSTANT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "cpp.y"
 
    char* str; 

#line 162 "cpp.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CPP_TAB_H_INCLUDED  */
