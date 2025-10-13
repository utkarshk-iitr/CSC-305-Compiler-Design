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
    FUNCTION = 306,                /* FUNCTION  */
    IF = 307,                      /* IF  */
    ELSE = 308,                    /* ELSE  */
    SWITCH = 309,                  /* SWITCH  */
    CASE = 310,                    /* CASE  */
    DEFAULT = 311,                 /* DEFAULT  */
    WHILE = 312,                   /* WHILE  */
    DO = 313,                      /* DO  */
    FOR = 314,                     /* FOR  */
    GOTO = 315,                    /* GOTO  */
    CONTINUE = 316,                /* CONTINUE  */
    BREAK = 317,                   /* BREAK  */
    RETURN = 318,                  /* RETURN  */
    UNTIL = 319,                   /* UNTIL  */
    SIZEOF = 320,                  /* SIZEOF  */
    VOID = 321,                    /* VOID  */
    INT = 322,                     /* INT  */
    DOUBLE = 323,                  /* DOUBLE  */
    CHAR = 324,                    /* CHAR  */
    BOOL = 325,                    /* BOOL  */
    STRING = 326,                  /* STRING  */
    LONG = 327,                    /* LONG  */
    TRUE = 328,                    /* TRUE  */
    FALSE = 329,                   /* FALSE  */
    NULLPTR = 330,                 /* NULLPTR  */
    AUTO = 331,                    /* AUTO  */
    STATIC = 332,                  /* STATIC  */
    CONST = 333,                   /* CONST  */
    CLASS = 334,                   /* CLASS  */
    STRUCT = 335,                  /* STRUCT  */
    PUBLIC = 336,                  /* PUBLIC  */
    PRIVATE = 337,                 /* PRIVATE  */
    PROTECTED = 338,               /* PROTECTED  */
    DELETE = 339,                  /* DELETE  */
    NEW = 340,                     /* NEW  */
    CIN = 341,                     /* CIN  */
    COUT = 342,                    /* COUT  */
    ENDL = 343,                    /* ENDL  */
    IDENTIFIER = 344,              /* IDENTIFIER  */
    INVALID_IDENTIFIER = 345,      /* INVALID_IDENTIFIER  */
    DECIMAL_LITERAL = 346,         /* DECIMAL_LITERAL  */
    DOUBLE_LITERAL = 347,          /* DOUBLE_LITERAL  */
    EXPONENT_LITERAL = 348,        /* EXPONENT_LITERAL  */
    CHARACTER_LITERAL = 349,       /* CHARACTER_LITERAL  */
    STRING_LITERAL = 350,          /* STRING_LITERAL  */
    LOWER_THAN_ELSE = 351          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 300 "src/parser.y"

    char* str;
    Node* node;

#line 172 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
