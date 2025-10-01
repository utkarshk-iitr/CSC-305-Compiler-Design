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
    ARROW = 280,                   /* ARROW  */
    LOGICAL_NOT = 281,             /* LOGICAL_NOT  */
    LOGICAL_AND = 282,             /* LOGICAL_AND  */
    LOGICAL_OR = 283,              /* LOGICAL_OR  */
    PLUS_EQUAL = 284,              /* PLUS_EQUAL  */
    MINUS_EQUAL = 285,             /* MINUS_EQUAL  */
    STAR_EQUAL = 286,              /* STAR_EQUAL  */
    DIV_EQUAL = 287,               /* DIV_EQUAL  */
    MOD_EQUAL = 288,               /* MOD_EQUAL  */
    AND_EQUAL = 289,               /* AND_EQUAL  */
    OR_EQUAL = 290,                /* OR_EQUAL  */
    XOR_EQUAL = 291,               /* XOR_EQUAL  */
    LEFT_SHIFT_EQ = 292,           /* LEFT_SHIFT_EQ  */
    RIGHT_SHIFT_EQ = 293,          /* RIGHT_SHIFT_EQ  */
    LROUND = 294,                  /* LROUND  */
    RROUND = 295,                  /* RROUND  */
    LCURLY = 296,                  /* LCURLY  */
    RCURLY = 297,                  /* RCURLY  */
    LSQUARE = 298,                 /* LSQUARE  */
    RSQUARE = 299,                 /* RSQUARE  */
    SEMICOLON = 300,               /* SEMICOLON  */
    COLON = 301,                   /* COLON  */
    COMMA = 302,                   /* COMMA  */
    DOT = 303,                     /* DOT  */
    QUESTION_MARK = 304,           /* QUESTION_MARK  */
    TILDE = 305,                   /* TILDE  */
    IF = 306,                      /* IF  */
    ELSE = 307,                    /* ELSE  */
    SWITCH = 308,                  /* SWITCH  */
    CASE = 309,                    /* CASE  */
    DEFAULT = 310,                 /* DEFAULT  */
    WHILE = 311,                   /* WHILE  */
    DO = 312,                      /* DO  */
    FOR = 313,                     /* FOR  */
    GOTO = 314,                    /* GOTO  */
    CONTINUE = 315,                /* CONTINUE  */
    BREAK = 316,                   /* BREAK  */
    RETURN = 317,                  /* RETURN  */
    UNTIL = 318,                   /* UNTIL  */
    SIZEOF = 319,                  /* SIZEOF  */
    VOID = 320,                    /* VOID  */
    INT = 321,                     /* INT  */
    DOUBLE = 322,                  /* DOUBLE  */
    CHAR = 323,                    /* CHAR  */
    BOOL = 324,                    /* BOOL  */
    STRING = 325,                  /* STRING  */
    LONG = 326,                    /* LONG  */
    TRUE = 327,                    /* TRUE  */
    FALSE = 328,                   /* FALSE  */
    NULLPTR = 329,                 /* NULLPTR  */
    AUTO = 330,                    /* AUTO  */
    STATIC = 331,                  /* STATIC  */
    CONST = 332,                   /* CONST  */
    CLASS = 333,                   /* CLASS  */
    STRUCT = 334,                  /* STRUCT  */
    PUBLIC = 335,                  /* PUBLIC  */
    PRIVATE = 336,                 /* PRIVATE  */
    PROTECTED = 337,               /* PROTECTED  */
    DELETE = 338,                  /* DELETE  */
    NEW = 339,                     /* NEW  */
    CIN = 340,                     /* CIN  */
    COUT = 341,                    /* COUT  */
    ENDL = 342,                    /* ENDL  */
    IDENTIFIER = 343,              /* IDENTIFIER  */
    DECIMAL_LITERAL = 344,         /* DECIMAL_LITERAL  */
    DOUBLE_LITERAL = 345,          /* DOUBLE_LITERAL  */
    EXPONENT_LITERAL = 346,        /* EXPONENT_LITERAL  */
    CHARACTER_LITERAL = 347,       /* CHARACTER_LITERAL  */
    STRING_LITERAL = 348           /* STRING_LITERAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "cpp.y"
 
    char* str; 

#line 161 "cpp.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CPP_TAB_H_INCLUDED  */
