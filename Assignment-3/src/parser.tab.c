/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 8 "src/parser.y"

    #include <bits/stdc++.h>
    #include <fstream>
    #include <string>
    #include <cstring>
    #include <vector>
    #include <unordered_map>
    #include <map>
    #include <cstdlib>
    using namespace std;

    struct Node {
        vector<string> code;
        vector<string> syn;
        string place;
        string type;
        string kind;
        int argCount = 0;
        Node() : place(""), type("") , kind("") {}
        Node(string p, string t, string k) : place(p), type(t), kind(k) {}
    };

    struct Symbol {
        string name;
        string type;
        string kind;
        bool isFunction = false;
        int paramCount = 0;
        bool isDeclared = true;
        Symbol() : name(""), type(""), kind(""), isFunction(false), paramCount(0), isDeclared(true) {}
        Symbol(string n, string t, string k, bool f, int p) : name(n), type(t), kind(k), isFunction(f), paramCount(p) {}
    };

    struct funcInfo {
        string returnType;
        bool hasReturn = false;
        vector<string> paramTypes;
        int paramCount = 0;
        funcInfo() : returnType("void"), hasReturn(false) {}
    };

    unordered_map<string, funcInfo> funcTable;

    vector< unordered_map<string, Symbol> > symStack;

    unordered_map<string,int> typeSize = {
        {"int", 4}, {"char", 1}, {"bool", 1}, {"double", 8}, {"string", 8}, {"nullptr", 8}
    };
    
    vector<string> errors;
    static string currentFunction = "global";
    static int globalTemp = 0, globalLabel = 0;
    static int localTemp = 0, localLabel = 0;
    
    static string lastDeclType = "int";
    static string lastUsage = "rvalue";

    Node* finalRoot = nullptr;

    string newTemp() {
        if (currentFunction == "global") {
            return "global.t" + to_string(++globalTemp);
        } else {
            return currentFunction + ".t" + to_string(++localTemp);
        }
    }
    string newLabel() {
        if (currentFunction == "global") {
            return "global.L" + to_string(++globalLabel);
        } else {
            return currentFunction + ".L" + to_string(++localLabel);
        }
    }

    extern bool is_type_name(char const* s) {
        return typeSize.find(s) != typeSize.end();
    }

    void pushScope() {
        symStack.emplace_back();
    }
    void popScope() {
        if (!symStack.empty()) 
            symStack.pop_back();
    }

    Symbol* lookupSymbol(const string &name) {
        for (int i = (int)symStack.size()-1; i >= 0; --i) {
            auto &m = symStack[i];
            auto it = m.find(name);
            if (it != m.end()) return &it->second;
        }
        return nullptr;
    }

    bool declareSymbol(const string &name, const string &type, const string k="",bool isFunc=false, int params=0) {
        if (symStack.empty()) pushScope();
        auto &cur = symStack.back();
        if (cur.find(name) != cur.end()) {
            return false;
        }
        Symbol s; 
        s.name = name; s.type = type; s.kind = k; 
        s.isFunction = isFunc;
        s.paramCount = params;
        s.isDeclared = true;
        cur[name] = s;
        return true;
    }

    extern int yylineno;
    void yyerror(string s) {
        errors.push_back(string("Error at line ") + to_string(yylineno) + " : " + s);
    }

    void check_access(Symbol* sym) {
        if(sym->kind.find("private") != string::npos){
            yyerror("Can't access private member '" + sym->name + "'.");
        }
        else if(sym->kind.find("protected") != string::npos){
            yyerror("Can't access protected member '" + sym->name + "'.");
        }
    }

    extern int yylex();
    extern int yyparse();

    ofstream dbgfile("debug.txt");
    void dbg(const string &msg) {
        dbgfile << "Debug: " << msg << endl;
    }


#line 205 "src/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INCLUDE = 3,                    /* INCLUDE  */
  YYSYMBOL_TYPEDEF = 4,                    /* TYPEDEF  */
  YYSYMBOL_TYPE_NAME = 5,                  /* TYPE_NAME  */
  YYSYMBOL_PLUS = 6,                       /* PLUS  */
  YYSYMBOL_MINUS = 7,                      /* MINUS  */
  YYSYMBOL_STAR = 8,                       /* STAR  */
  YYSYMBOL_DIVIDE = 9,                     /* DIVIDE  */
  YYSYMBOL_MODULUS = 10,                   /* MODULUS  */
  YYSYMBOL_ASSIGN = 11,                    /* ASSIGN  */
  YYSYMBOL_INCREMENT = 12,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 13,                 /* DECREMENT  */
  YYSYMBOL_EQUAL = 14,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 15,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 16,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 17,              /* GREATER_THAN  */
  YYSYMBOL_LESS_EQUAL = 18,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 19,             /* GREATER_EQUAL  */
  YYSYMBOL_BITWISE_AND = 20,               /* BITWISE_AND  */
  YYSYMBOL_BITWISE_OR = 21,                /* BITWISE_OR  */
  YYSYMBOL_BITWISE_XOR = 22,               /* BITWISE_XOR  */
  YYSYMBOL_LEFT_SHIFT = 23,                /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 24,               /* RIGHT_SHIFT  */
  YYSYMBOL_ARROW = 25,                     /* ARROW  */
  YYSYMBOL_LOGICAL_NOT = 26,               /* LOGICAL_NOT  */
  YYSYMBOL_LOGICAL_AND = 27,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 28,                /* LOGICAL_OR  */
  YYSYMBOL_PLUS_EQUAL = 29,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 30,               /* MINUS_EQUAL  */
  YYSYMBOL_STAR_EQUAL = 31,                /* STAR_EQUAL  */
  YYSYMBOL_DIV_EQUAL = 32,                 /* DIV_EQUAL  */
  YYSYMBOL_MOD_EQUAL = 33,                 /* MOD_EQUAL  */
  YYSYMBOL_AND_EQUAL = 34,                 /* AND_EQUAL  */
  YYSYMBOL_OR_EQUAL = 35,                  /* OR_EQUAL  */
  YYSYMBOL_XOR_EQUAL = 36,                 /* XOR_EQUAL  */
  YYSYMBOL_LEFT_SHIFT_EQ = 37,             /* LEFT_SHIFT_EQ  */
  YYSYMBOL_RIGHT_SHIFT_EQ = 38,            /* RIGHT_SHIFT_EQ  */
  YYSYMBOL_LROUND = 39,                    /* LROUND  */
  YYSYMBOL_RROUND = 40,                    /* RROUND  */
  YYSYMBOL_LCURLY = 41,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 42,                    /* RCURLY  */
  YYSYMBOL_LSQUARE = 43,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 44,                   /* RSQUARE  */
  YYSYMBOL_SEMICOLON = 45,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 46,                     /* COLON  */
  YYSYMBOL_COMMA = 47,                     /* COMMA  */
  YYSYMBOL_DOT = 48,                       /* DOT  */
  YYSYMBOL_QUESTION_MARK = 49,             /* QUESTION_MARK  */
  YYSYMBOL_TILDE = 50,                     /* TILDE  */
  YYSYMBOL_FUNCTION = 51,                  /* FUNCTION  */
  YYSYMBOL_IF = 52,                        /* IF  */
  YYSYMBOL_ELSE = 53,                      /* ELSE  */
  YYSYMBOL_SWITCH = 54,                    /* SWITCH  */
  YYSYMBOL_CASE = 55,                      /* CASE  */
  YYSYMBOL_DEFAULT = 56,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 57,                     /* WHILE  */
  YYSYMBOL_DO = 58,                        /* DO  */
  YYSYMBOL_FOR = 59,                       /* FOR  */
  YYSYMBOL_GOTO = 60,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 61,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 62,                     /* BREAK  */
  YYSYMBOL_RETURN = 63,                    /* RETURN  */
  YYSYMBOL_UNTIL = 64,                     /* UNTIL  */
  YYSYMBOL_SIZEOF = 65,                    /* SIZEOF  */
  YYSYMBOL_VOID = 66,                      /* VOID  */
  YYSYMBOL_INT = 67,                       /* INT  */
  YYSYMBOL_DOUBLE = 68,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 69,                      /* CHAR  */
  YYSYMBOL_BOOL = 70,                      /* BOOL  */
  YYSYMBOL_STRING = 71,                    /* STRING  */
  YYSYMBOL_LONG = 72,                      /* LONG  */
  YYSYMBOL_TRUE = 73,                      /* TRUE  */
  YYSYMBOL_FALSE = 74,                     /* FALSE  */
  YYSYMBOL_NULLPTR = 75,                   /* NULLPTR  */
  YYSYMBOL_AUTO = 76,                      /* AUTO  */
  YYSYMBOL_STATIC = 77,                    /* STATIC  */
  YYSYMBOL_CONST = 78,                     /* CONST  */
  YYSYMBOL_CLASS = 79,                     /* CLASS  */
  YYSYMBOL_STRUCT = 80,                    /* STRUCT  */
  YYSYMBOL_PUBLIC = 81,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 82,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 83,                 /* PROTECTED  */
  YYSYMBOL_DELETE = 84,                    /* DELETE  */
  YYSYMBOL_NEW = 85,                       /* NEW  */
  YYSYMBOL_CIN = 86,                       /* CIN  */
  YYSYMBOL_COUT = 87,                      /* COUT  */
  YYSYMBOL_ENDL = 88,                      /* ENDL  */
  YYSYMBOL_IDENTIFIER = 89,                /* IDENTIFIER  */
  YYSYMBOL_INVALID_IDENTIFIER = 90,        /* INVALID_IDENTIFIER  */
  YYSYMBOL_DECIMAL_LITERAL = 91,           /* DECIMAL_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 92,            /* DOUBLE_LITERAL  */
  YYSYMBOL_EXPONENT_LITERAL = 93,          /* EXPONENT_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 94,         /* CHARACTER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 95,            /* STRING_LITERAL  */
  YYSYMBOL_LOWER_THAN_ELSE = 96,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 97,                  /* $accept  */
  YYSYMBOL_primary_expression = 98,        /* primary_expression  */
  YYSYMBOL_constant = 99,                  /* constant  */
  YYSYMBOL_postfix_expression = 100,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 101, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 102,         /* unary_expression  */
  YYSYMBOL_unary_operator = 103,           /* unary_operator  */
  YYSYMBOL_new_expression = 104,           /* new_expression  */
  YYSYMBOL_new_declarator = 105,           /* new_declarator  */
  YYSYMBOL_scalar_new_init_opt = 106,      /* scalar_new_init_opt  */
  YYSYMBOL_delete_expression = 107,        /* delete_expression  */
  YYSYMBOL_cast_expression = 108,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 109, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 110,      /* additive_expression  */
  YYSYMBOL_shift_expression = 111,         /* shift_expression  */
  YYSYMBOL_relational_expression = 112,    /* relational_expression  */
  YYSYMBOL_equality_expression = 113,      /* equality_expression  */
  YYSYMBOL_and_expression = 114,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 115,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 116,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 117,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 118,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 119,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 120,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 121,      /* assignment_operator  */
  YYSYMBOL_expression = 122,               /* expression  */
  YYSYMBOL_constant_expression = 123,      /* constant_expression  */
  YYSYMBOL_declaration = 124,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 125,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 126,     /* init_declarator_list  */
  YYSYMBOL_pointer_opt = 127,              /* pointer_opt  */
  YYSYMBOL_pointer_list = 128,             /* pointer_list  */
  YYSYMBOL_init_declarator = 129,          /* init_declarator  */
  YYSYMBOL_initializer = 130,              /* initializer  */
  YYSYMBOL_initializer_list = 131,         /* initializer_list  */
  YYSYMBOL_square_list = 132,              /* square_list  */
  YYSYMBOL_static_opt = 133,               /* static_opt  */
  YYSYMBOL_type_specifier = 134,           /* type_specifier  */
  YYSYMBOL_struct_or_class_specifier = 135, /* struct_or_class_specifier  */
  YYSYMBOL_struct_or_class = 136,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 137, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 138,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 139,   /* access_specifier_label  */
  YYSYMBOL_declarator = 140,               /* declarator  */
  YYSYMBOL_member_declaration = 141,       /* member_declaration  */
  YYSYMBOL_constructor_definition = 142,   /* constructor_definition  */
  YYSYMBOL_destructor_definition = 143,    /* destructor_definition  */
  YYSYMBOL_struct_declarator_list = 144,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 145,        /* struct_declarator  */
  YYSYMBOL_specifier_qualifier_list = 146, /* specifier_qualifier_list  */
  YYSYMBOL_const_opt = 147,                /* const_opt  */
  YYSYMBOL_pointer = 148,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 149,      /* type_qualifier_list  */
  YYSYMBOL_parameter_list = 150,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 151,    /* parameter_declaration  */
  YYSYMBOL_type_name = 152,                /* type_name  */
  YYSYMBOL_abstract_declarator = 153,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 154, /* direct_abstract_declarator  */
  YYSYMBOL_statement = 155,                /* statement  */
  YYSYMBOL_io_statement = 156,             /* io_statement  */
  YYSYMBOL_cout_expression = 157,          /* cout_expression  */
  YYSYMBOL_insertion_list = 158,           /* insertion_list  */
  YYSYMBOL_cin_expression = 159,           /* cin_expression  */
  YYSYMBOL_extraction_list = 160,          /* extraction_list  */
  YYSYMBOL_labeled_statement = 161,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 162,       /* compound_statement  */
  YYSYMBOL_statement_list = 163,           /* statement_list  */
  YYSYMBOL_block_item = 164,               /* block_item  */
  YYSYMBOL_expression_statement = 165,     /* expression_statement  */
  YYSYMBOL_selection_statement = 166,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 167,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 168,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 169,           /* jump_statement  */
  YYSYMBOL_translation_unit = 170,         /* translation_unit  */
  YYSYMBOL_external_declaration = 171,     /* external_declaration  */
  YYSYMBOL_function_header = 172,          /* function_header  */
  YYSYMBOL_function_definition = 173,      /* function_definition  */
  YYSYMBOL_return_type = 174,              /* return_type  */
  YYSYMBOL_lambda_expression = 175,        /* lambda_expression  */
  YYSYMBOL_lambda_declarator = 176,        /* lambda_declarator  */
  YYSYMBOL_lambda_parameter_clause = 177,  /* lambda_parameter_clause  */
  YYSYMBOL_trailing_return_opt = 178,      /* trailing_return_opt  */
  YYSYMBOL_lambda_capture_clause = 179,    /* lambda_capture_clause  */
  YYSYMBOL_capture_list = 180              /* capture_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  39
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1509

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  248
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  423

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   351


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   219,   219,   234,   237,   240,   246,   251,   256,   261,
     266,   271,   276,   281,   289,   292,   318,   342,   366,   390,
     410,   430,   453,   465,   480,   483,   492,   501,   533,   537,
     541,   544,   550,   553,   556,   559,   562,   565,   571,   579,
     587,   595,   606,   609,   615,   618,   624,   631,   641,   644,
     651,   654,   664,   674,   687,   690,   700,   713,   716,   725,
     737,   740,   747,   754,   761,   771,   774,   781,   791,   794,
     804,   807,   817,   820,   830,   833,   843,   846,   856,   859,
     880,   883,   915,   918,   921,   924,   927,   930,   933,   936,
     939,   942,   945,   951,   956,   968,   975,   982,   991,  1003,
    1008,  1019,  1025,  1033,  1038,  1047,  1064,  1085,  1103,  1128,
    1157,  1201,  1215,  1225,  1259,  1274,  1292,  1295,  1301,  1304,
    1307,  1310,  1313,  1316,  1319,  1322,  1328,  1331,  1337,  1340,
    1346,  1349,  1357,  1360,  1366,  1369,  1372,  1377,  1379,  1382,
    1385,  1388,  1391,  1394,  1397,  1403,  1407,  1414,  1421,  1424,
    1432,  1438,  1441,  1444,  1447,  1454,  1457,  1464,  1467,  1470,
    1473,  1479,  1482,  1488,  1492,  1502,  1522,  1525,  1531,  1534,
    1537,  1543,  1546,  1549,  1552,  1555,  1558,  1561,  1564,  1567,
    1573,  1576,  1579,  1582,  1585,  1588,  1591,  1597,  1600,  1606,
    1612,  1618,  1623,  1627,  1636,  1642,  1647,  1656,  1662,  1668,
    1677,  1684,  1694,  1697,  1706,  1709,  1712,  1716,  1719,  1725,
    1736,  1750,  1757,  1770,  1781,  1792,  1808,  1828,  1831,  1837,
    1843,  1847,  1851,  1855,  1867,  1870,  1878,  1883,  1886,  1889,
    1892,  1901,  1925,  1964,  1973,  1978,  1986,  1989,  1995,  2001,
    2004,  2010,  2013,  2019,  2022,  2025,  2028,  2034,  2037
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INCLUDE", "TYPEDEF",
  "TYPE_NAME", "PLUS", "MINUS", "STAR", "DIVIDE", "MODULUS", "ASSIGN",
  "INCREMENT", "DECREMENT", "EQUAL", "NOT_EQUAL", "LESS_THAN",
  "GREATER_THAN", "LESS_EQUAL", "GREATER_EQUAL", "BITWISE_AND",
  "BITWISE_OR", "BITWISE_XOR", "LEFT_SHIFT", "RIGHT_SHIFT", "ARROW",
  "LOGICAL_NOT", "LOGICAL_AND", "LOGICAL_OR", "PLUS_EQUAL", "MINUS_EQUAL",
  "STAR_EQUAL", "DIV_EQUAL", "MOD_EQUAL", "AND_EQUAL", "OR_EQUAL",
  "XOR_EQUAL", "LEFT_SHIFT_EQ", "RIGHT_SHIFT_EQ", "LROUND", "RROUND",
  "LCURLY", "RCURLY", "LSQUARE", "RSQUARE", "SEMICOLON", "COLON", "COMMA",
  "DOT", "QUESTION_MARK", "TILDE", "FUNCTION", "IF", "ELSE", "SWITCH",
  "CASE", "DEFAULT", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK",
  "RETURN", "UNTIL", "SIZEOF", "VOID", "INT", "DOUBLE", "CHAR", "BOOL",
  "STRING", "LONG", "TRUE", "FALSE", "NULLPTR", "AUTO", "STATIC", "CONST",
  "CLASS", "STRUCT", "PUBLIC", "PRIVATE", "PROTECTED", "DELETE", "NEW",
  "CIN", "COUT", "ENDL", "IDENTIFIER", "INVALID_IDENTIFIER",
  "DECIMAL_LITERAL", "DOUBLE_LITERAL", "EXPONENT_LITERAL",
  "CHARACTER_LITERAL", "STRING_LITERAL", "LOWER_THAN_ELSE", "$accept",
  "primary_expression", "constant", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "new_expression", "new_declarator", "scalar_new_init_opt",
  "delete_expression", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "pointer_opt", "pointer_list", "init_declarator",
  "initializer", "initializer_list", "square_list", "static_opt",
  "type_specifier", "struct_or_class_specifier", "struct_or_class",
  "struct_or_class_member_list", "struct_or_class_member",
  "access_specifier_label", "declarator", "member_declaration",
  "constructor_definition", "destructor_definition",
  "struct_declarator_list", "struct_declarator",
  "specifier_qualifier_list", "const_opt", "pointer",
  "type_qualifier_list", "parameter_list", "parameter_declaration",
  "type_name", "abstract_declarator", "direct_abstract_declarator",
  "statement", "io_statement", "cout_expression", "insertion_list",
  "cin_expression", "extraction_list", "labeled_statement",
  "compound_statement", "statement_list", "block_item",
  "expression_statement", "selection_statement", "iteration_statement",
  "for_init_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_header", "function_definition",
  "return_type", "lambda_expression", "lambda_declarator",
  "lambda_parameter_clause", "trailing_return_opt",
  "lambda_capture_clause", "capture_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-242)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-118)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1004,    97,   220,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,     3,   -53,    55,    -9,   -39,
     824,  -242,    56,  -242,    19,  -242,  -242,    29,  -242,    15,
       0,     6,  -242,  -242,   220,  -242,   171,  -242,   116,  -242,
      97,  -242,   353,  -242,   160,   213,  1234,  1234,    27,  -242,
       3,  -242,   229,  -242,   600,   152,  -242,  -242,  -242,  1304,
    1304,  -242,  -242,   634,  -242,    12,  -242,  -242,   203,   233,
    1234,   238,   258,   724,   266,   217,   264,   267,    60,   268,
    1344,  -242,  -242,  -242,  1414,   220,   287,   290,   269,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,    21,   446,  1234,  -242,
    -242,  -242,   245,   120,   227,   150,   262,   294,   295,   298,
     289,    28,  -242,  -242,   181,  -242,  -242,  -242,   275,   278,
    -242,  -242,   448,  -242,  -242,  -242,  -242,  -242,  -242,   118,
    -242,  -242,  -242,  -242,  -242,   282,   286,  1234,  -242,  1234,
    -242,   239,   284,   285,   291,   293,    93,   288,  1402,  -242,
    -242,  -242,  -242,  -242,     7,    93,  -242,  1234,  -242,  -242,
     -19,    14,   296,   292,  -242,   297,   299,  1234,  1234,   301,
     724,  1234,   283,   543,   303,  -242,  -242,  -242,   212,  1234,
     634,  -242,     5,  -242,    55,  1234,   319,   794,   321,   724,
    -242,  -242,   260,   834,  1234,   263,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,  -242,  1234,  -242,  1234,
    1234,  1234,  1234,  1234,  1234,  1234,  1234,  1234,  1234,  1234,
    1234,  1234,  1234,  1234,  1234,  1234,  1234,  1234,  -242,  1234,
    -242,  -242,  -242,  -242,  -242,    -3,  -242,   273,  -242,  1234,
    -242,   312,  -242,   325,  -242,  -242,  -242,   317,  -242,  -242,
    -242,  -242,  -242,  -242,    56,   228,  -242,  -242,  -242,    -2,
     195,   904,    -4,  -242,    45,  1234,   279,   242,    20,    34,
      38,   724,  -242,    42,   328,   324,  -242,  -242,   974,  -242,
    -242,    43,   330,  1234,   138,  -242,  1234,  -242,  -242,  1014,
    -242,  -242,  -242,    90,  -242,   136,  -242,  -242,  -242,  -242,
    -242,   245,   245,   120,   120,   227,   227,   227,   227,   150,
     150,   262,   294,   295,   298,   289,   247,  -242,  -242,   220,
    -242,  -242,    94,  -242,   331,    56,   100,  -242,  -242,     3,
    -242,  -242,    -2,  -242,   151,   332,  -242,   333,    45,   531,
    1084,  -242,   327,   624,  -242,    56,   350,  -242,  -242,   724,
     724,  -242,   724,  1234,  1124,   724,  -242,  -242,  1194,  1234,
     139,  -242,  -242,  -242,  -242,  -242,  1234,  -242,  1234,  -242,
    -242,  1234,    56,  -242,    56,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,   183,  -242,   334,   302,  -242,   192,  -242,    93,
    -242,   323,  -242,  -242,   196,   724,   197,  -242,  -242,   201,
     149,  1234,  -242,  -242,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,  -242,   724,   335,  -242,   724,  -242,  -242,   180,  -242,
    -242,  -242,  -242
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   226,     0,   125,   118,   120,   122,   119,   123,   124,
     121,   116,   129,   128,   229,     0,   156,   102,     0,     0,
       0,   224,     0,   227,     0,   234,    97,     0,   104,   105,
       0,     0,    99,   155,     0,   235,   101,   228,   127,     1,
       0,   225,     0,   233,     0,     0,     0,     0,   106,    96,
       0,   103,   107,    98,   156,     0,    34,    35,    33,     0,
       0,    32,    37,   156,   200,     0,   207,    36,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    13,    11,     0,     0,     0,     0,     2,     6,
      10,     9,     7,     8,    14,     3,    24,    48,     0,    31,
      30,    50,    54,    57,    60,    65,    68,    70,    72,    74,
      76,    78,    80,    93,     0,   205,   204,   186,     0,     0,
     180,   181,     0,   202,   182,   183,   184,   185,     5,     0,
     230,     2,   108,    48,    95,     0,     0,     0,   100,     0,
     142,     0,     0,     0,     0,     0,   152,     0,   156,   130,
     132,   133,   143,   144,   137,   154,   206,     0,    25,    26,
       0,   166,     0,   243,   247,     0,   244,     0,     0,     0,
       0,     0,     0,     0,     0,   220,   221,   222,     0,     0,
     156,    28,     0,    47,   102,     0,   194,     0,   189,     0,
      20,    21,     0,     0,     0,     0,    82,    86,    87,    83,
      84,    85,    90,    92,    91,    88,    89,     0,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   208,     0,
     187,   188,   201,   203,   231,     0,   163,     0,   115,     0,
     110,     0,   109,     0,   134,   135,   136,     0,   151,   141,
     126,   131,   139,   150,     0,     0,   148,   153,     4,   156,
       0,     0,   168,   167,   169,     0,     0,     0,     0,     0,
       0,     0,   199,     0,     0,     0,   218,   217,     0,   219,
     223,     0,     0,     0,    41,   195,     0,   191,   190,     0,
     197,    19,    16,     0,    22,     0,    18,    81,    51,    52,
      53,    55,    56,    58,    59,    62,    61,    63,    64,    66,
      67,    69,    71,    73,    75,    77,     0,    94,   232,     0,
     165,   112,     0,   114,     0,     0,     0,   140,   138,     0,
     161,   159,   156,   176,     0,     0,   172,     0,   170,     0,
       0,    49,   246,     0,   237,     0,   241,   245,   248,     0,
       0,   198,     0,     0,     0,     0,    29,    46,     0,     0,
      40,    39,   196,   192,   193,    17,     0,    15,     0,   164,
     111,     0,     0,   146,     0,   149,   162,   160,   177,   171,
     173,   178,     0,   174,     0,     0,   239,     0,   236,   156,
     238,   209,   211,   212,     0,     0,     0,   213,    44,     0,
       0,     0,    38,    23,    79,   113,   147,   145,   179,   175,
     240,   242,     0,     0,   215,     0,    45,    42,     0,   210,
     214,   216,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -242,  -242,  -242,  -242,    23,    -5,  -242,  -242,  -242,    22,
    -242,   -36,    83,    84,    52,    80,   168,   170,   173,   174,
     175,  -242,   -30,   -37,  -242,   -51,   -66,   -35,  -242,  -242,
     216,   -12,     9,  -242,  -242,  -242,  -242,   -34,   -44,  -242,
    -242,   254,  -242,  -242,  -242,  -242,  -242,  -242,    75,   -24,
     -14,  -241,  -242,  -228,    87,  -167,   169,   172,   -70,  -242,
    -242,  -242,  -242,  -242,  -242,   -21,  -242,   310,  -165,  -242,
    -242,  -242,  -242,  -242,   413,  -242,  -242,    41,  -242,  -242,
    -242,  -242,  -242,   177
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    94,    95,    96,   293,    97,    98,    99,   360,   361,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   207,   114,   135,    14,    15,    30,
      35,    31,   253,   240,   322,    48,    16,    17,    18,    19,
     148,   149,   150,   254,   151,   152,   153,   255,   256,   161,
     155,   262,   332,   235,   236,   162,   263,   264,   116,   117,
     118,   188,   119,   186,   120,   121,   122,   123,   124,   125,
     126,   278,   127,    20,    21,    22,    23,   237,   128,   345,
     346,   390,   165,   166
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    43,    34,   172,   169,    36,   259,   115,   277,   132,
     147,    28,   160,   282,    51,    28,   163,   134,   331,   326,
     146,   258,   259,   163,    32,    33,    46,   178,   229,   146,
     154,   347,   334,   190,   191,   260,    37,   318,   136,   261,
     134,    24,   133,    27,   319,    49,   192,    50,   183,   283,
      38,   184,   252,   260,   158,   159,   226,   261,    47,   138,
     193,    24,   208,    28,   194,   133,    56,    57,    58,   195,
     137,   241,    59,    60,   349,   181,    33,   227,   350,   133,
      61,   229,   352,   355,   339,   229,    62,   115,   340,   229,
     229,   377,    29,   133,   164,    52,    29,    42,     3,    63,
     272,   164,   242,    65,   147,   177,   160,   134,    44,   348,
      67,   382,   146,   354,   146,   387,   269,   270,    45,   290,
     273,   146,   248,     3,   154,    80,   212,   213,   281,   160,
     365,   257,   133,    81,    82,    83,   370,   366,   276,    25,
     374,   371,    26,   295,    84,    85,   146,   319,   285,   131,
     288,    89,    90,    91,    92,    93,   294,    54,   234,     4,
       5,     6,     7,     8,     9,    10,   216,   217,   218,   219,
     297,    33,    36,   298,   299,   300,   316,   358,   358,    51,
     367,   359,   401,   229,     4,     5,     6,     7,     8,     9,
      10,   378,   317,   417,   156,   337,   229,    26,   319,   129,
       3,   351,   321,   259,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   411,   408,   422,     3,   228,   229,   229,   341,
     319,   134,   410,   327,   260,   333,   413,   415,   261,   319,
     139,   416,   167,   229,   229,   330,   344,   357,   366,   362,
     214,   215,   364,   209,   210,   211,   133,   280,   130,   229,
     133,     4,     5,     6,     7,     8,     9,    10,   305,   306,
     307,   308,   168,   328,   384,   329,   220,   221,   133,   391,
     392,   343,   393,    42,   170,   397,     4,     5,     6,     7,
       8,     9,    10,   368,   229,   301,   302,   171,   303,   304,
     309,   310,   394,   396,   373,   173,   174,   179,   400,   175,
     134,   185,   176,   187,   222,   189,   225,   223,   376,   224,
     230,   294,     3,   231,   388,   414,   238,   239,   243,   403,
     244,   245,   247,   249,   405,   133,   265,   246,   404,   266,
     274,   267,   419,   286,   289,   421,   268,   271,   279,   291,
     418,   406,   296,   407,    55,   146,   323,   325,  -117,    56,
      57,    58,   320,   133,   324,    59,    60,   353,   164,    26,
     356,   372,   379,    61,   385,   389,   412,   380,   409,    62,
     420,   399,   402,     4,     5,     6,     7,     8,     9,    10,
     311,   348,    63,   312,    42,    64,    65,   313,    66,   314,
     284,   315,   251,    67,   375,    68,   369,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,    81,    82,    83,   335,
      11,  -117,   233,    41,   338,     0,     0,    84,    85,    86,
      87,     0,    88,   342,    89,    90,    91,    92,    93,    55,
       0,     0,     0,  -117,    56,    57,    58,   196,     0,     0,
      59,    60,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,     0,     0,    62,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,     0,     0,    63,     0,    42,
     232,    65,     0,    66,     0,     0,     0,     0,    67,     0,
      68,     0,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,    81,    82,    83,     0,    11,  -117,     0,     0,     0,
       0,     0,    84,    85,    86,    87,     3,    88,     0,    89,
      90,    91,    92,    93,   275,     0,     0,     0,  -117,    56,
      57,    58,     0,     0,     0,    59,    60,     0,     0,     0,
       0,     0,     0,    61,     0,     0,     0,     0,     0,    62,
       0,   381,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,     0,     0,     0,    65,     0,    66,     0,
       0,     0,     0,    67,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,     0,     3,     0,     0,    80,  -117,
    -117,  -117,  -117,  -117,  -117,  -117,    81,    82,    83,     0,
      11,  -117,     0,     0,     0,     0,     0,    84,    85,     3,
       0,     0,   131,     0,    89,    90,    91,    92,    93,     3,
      56,    57,    58,     0,     0,   140,    59,    60,     0,     0,
     141,     0,     0,     0,    61,     0,     0,     0,     0,     0,
      62,     0,     0,     0,   386,     0,     4,     5,     6,     7,
       8,     9,    10,    63,     0,     0,     0,    65,    33,    12,
      13,   142,   143,   144,    67,     0,     0,     0,     0,   145,
       4,     5,     6,     7,     8,     9,    10,     0,     0,    80,
       4,     5,     6,     7,     8,     9,    10,    81,    82,    83,
       0,     0,    33,     0,     0,     0,     0,     0,    84,    85,
       0,     0,     0,   131,     0,    89,    90,    91,    92,    93,
      56,    57,    58,     0,     0,     0,    59,    60,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,     0,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,    42,     0,    65,     0,    66,
       0,     0,     0,     0,    67,     0,    68,     0,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
       0,     0,     0,     0,     0,     0,     0,    81,    82,    83,
      56,    57,    58,     0,     0,     0,    59,    60,    84,    85,
      86,    87,     0,    88,    61,    89,    90,    91,    92,    93,
      62,     0,     0,     0,    39,    40,     0,     0,     2,     3,
       0,     0,     0,    63,     0,     0,     0,    65,     0,     0,
      56,    57,    58,     0,    67,     0,    59,    60,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,    80,
      62,     0,     0,     0,     0,     0,     0,    81,    82,    83,
       0,     0,     0,    63,   292,     0,     0,    65,    84,    85,
       0,     0,   287,   131,    67,    89,    90,    91,    92,    93,
       4,     5,     6,     7,     8,     9,    10,     0,     0,    80,
       0,    11,  -117,    12,    13,     0,     0,    81,    82,    83,
      56,    57,    58,     0,     0,     0,    59,    60,    84,    85,
       0,     0,     0,   131,    61,    89,    90,    91,    92,    93,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,    65,   336,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,    82,    83,
      56,    57,    58,     0,     0,     0,    59,    60,    84,    85,
       0,     0,     0,   131,    61,    89,    90,    91,    92,    93,
      62,     0,     0,     0,     0,     1,     0,     0,     2,     3,
       0,     0,     0,    63,     0,     0,     0,    65,     0,    66,
      56,    57,    58,     0,    67,     0,    59,    60,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,    80,
      62,     0,     0,     0,     0,     0,     0,    81,    82,    83,
       0,     0,     0,    63,     0,     0,     0,    65,    84,    85,
       0,     0,     0,   131,    67,    89,    90,    91,    92,    93,
       4,     5,     6,     7,     8,     9,    10,     0,     0,    80,
       0,    11,  -117,    12,    13,     0,     0,    81,    82,    83,
      56,    57,    58,     0,     0,     0,    59,    60,    84,    85,
       0,     0,   363,   131,    61,    89,    90,    91,    92,    93,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,    65,   383,     0,
      56,    57,    58,     0,    67,     0,    59,    60,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,    80,
      62,     0,     0,     0,     0,     0,     0,    81,    82,    83,
       0,     0,     0,    63,   395,     0,     0,    65,    84,    85,
       0,     0,     0,   131,    67,    89,    90,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,    82,    83,
      56,    57,    58,     0,     0,     0,    59,    60,    84,    85,
       0,     0,     0,   131,    61,    89,    90,    91,    92,    93,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,   398,     0,     0,    65,     0,     0,
      56,    57,    58,     0,    67,     0,    59,    60,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,    80,
      62,     0,     0,     0,     0,     0,     0,    81,    82,    83,
       0,     0,     0,    63,     0,     0,     0,    65,    84,    85,
       0,     0,     0,   131,    67,    89,    90,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,    82,    83,
      56,    57,    58,     0,     0,     0,    59,    60,    84,    85,
       0,     0,     0,   131,    61,    89,    90,    91,    92,    93,
      62,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   157,     0,     0,     0,    65,     0,     0,
      56,    57,    58,     0,    67,     0,    59,    60,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,     0,    80,
      62,     0,     0,     0,     0,     0,     0,    81,    82,    83,
       0,     0,     0,   180,     0,     0,     0,    65,    84,    85,
       0,     0,     0,   131,    67,    89,    90,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     3,     0,    80,
       0,     0,     0,     0,     0,     0,     0,    81,    82,    83,
      56,    57,    58,     0,     0,     0,    59,    60,    84,    85,
       0,     0,     0,   131,    61,    89,    90,    91,    92,    93,
      62,     0,     0,     0,   250,     0,     0,   140,     0,     0,
       0,     0,   141,    63,     0,     0,     0,   182,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,     0,    80,
      33,    12,    13,   142,   143,   144,     0,    81,    82,    83,
       0,   145,     0,     0,     0,     0,     0,     0,    84,    85,
       0,     0,     0,   131,     0,    89,    90,    91,    92,    93
};

static const yytype_int16 yycheck[] =
{
      34,    22,    16,    73,    70,    17,     8,    42,   173,    46,
      54,     8,    63,   180,     8,     8,    11,    47,   259,   247,
      54,    40,     8,    11,    15,    78,    11,    78,    47,    63,
      54,    11,   260,    12,    13,    39,    45,    40,    11,    43,
      70,     0,    47,     2,    47,    45,    25,    47,    84,    44,
      89,    85,    45,    39,    59,    60,    28,    43,    43,    50,
      39,    20,    98,     8,    43,    70,     6,     7,     8,    48,
      43,   137,    12,    13,    40,    80,    78,    49,    40,    84,
      20,    47,    40,    40,    39,    47,    26,   122,    43,    47,
      47,   332,    89,    98,    89,    89,    89,    41,     5,    39,
     170,    89,   139,    43,   148,    45,   157,   137,    89,    89,
      50,   339,   146,   278,   148,   343,   167,   168,    89,   189,
     171,   155,   146,     5,   148,    65,     6,     7,   179,   180,
      40,   155,   137,    73,    74,    75,    42,    47,   173,    42,
      40,    47,    45,   194,    84,    85,   180,    47,   185,    89,
     187,    91,    92,    93,    94,    95,   193,    41,    40,    66,
      67,    68,    69,    70,    71,    72,    16,    17,    18,    19,
     207,    78,   184,   209,   210,   211,   227,    39,    39,     8,
      44,    43,    43,    47,    66,    67,    68,    69,    70,    71,
      72,    40,   229,    44,    42,   261,    47,    45,    47,    39,
       5,   271,   239,     8,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   389,    40,    44,     5,    45,    47,    47,   265,
      47,   261,    40,   254,    39,    40,    40,    40,    43,    47,
      11,    40,    39,    47,    47,   259,   267,   283,    47,   286,
      23,    24,   289,     8,     9,    10,   261,    45,    45,    47,
     265,    66,    67,    68,    69,    70,    71,    72,   216,   217,
     218,   219,    39,    45,   340,    47,    14,    15,   283,   349,
     350,    39,   352,    41,    46,   355,    66,    67,    68,    69,
      70,    71,    72,    46,    47,   212,   213,    39,   214,   215,
     220,   221,   353,   354,   325,    39,    89,    39,   359,    45,
     340,    24,    45,    23,    20,    46,    27,    22,   332,    21,
      45,   358,     5,    45,   345,   395,    44,    41,    89,   366,
      46,    46,    39,    45,   371,   340,    40,    46,   368,    47,
      57,    44,   412,    24,    23,   415,    47,    46,    45,    89,
     401,   372,    89,   374,     1,   389,    44,    40,     5,     6,
       7,     8,    89,   368,    39,    12,    13,    39,    89,    45,
      40,    40,    40,    20,    47,    25,    53,    44,    44,    26,
      45,   358,   360,    66,    67,    68,    69,    70,    71,    72,
     222,    89,    39,   223,    41,    42,    43,   224,    45,   225,
     184,   226,   148,    50,   329,    52,   319,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,   260,
      77,    78,   122,    20,   262,    -1,    -1,    84,    85,    86,
      87,    -1,    89,   266,    91,    92,    93,    94,    95,     1,
      -1,    -1,    -1,     5,     6,     7,     8,    11,    -1,    -1,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    26,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    39,    -1,    41,
      42,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    77,    78,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,     5,    89,    -1,    91,
      92,    93,    94,    95,     1,    -1,    -1,    -1,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    45,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    -1,     5,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      77,    78,    -1,    -1,    -1,    -1,    -1,    84,    85,     5,
      -1,    -1,    89,    -1,    91,    92,    93,    94,    95,     5,
       6,     7,     8,    -1,    -1,    45,    12,    13,    -1,    -1,
      50,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    40,    -1,    66,    67,    68,    69,
      70,    71,    72,    39,    -1,    -1,    -1,    43,    78,    79,
      80,    81,    82,    83,    50,    -1,    -1,    -1,    -1,    89,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    89,    -1,    91,    92,    93,    94,    95,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    41,    -1,    43,    -1,    45,
      -1,    -1,    -1,    -1,    50,    -1,    52,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      86,    87,    -1,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,     0,     1,    -1,    -1,     4,     5,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    -1,
       6,     7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      -1,    -1,    -1,    39,    40,    -1,    -1,    43,    84,    85,
      -1,    -1,    88,    89,    50,    91,    92,    93,    94,    95,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    65,
      -1,    77,    78,    79,    80,    -1,    -1,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      -1,    -1,    -1,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    44,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      -1,    -1,    -1,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,    -1,     1,    -1,    -1,     4,     5,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    45,
       6,     7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    84,    85,
      -1,    -1,    -1,    89,    50,    91,    92,    93,    94,    95,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    65,
      -1,    77,    78,    79,    80,    -1,    -1,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      -1,    -1,    88,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    44,    -1,
       6,     7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      -1,    -1,    -1,    39,    40,    -1,    -1,    43,    84,    85,
      -1,    -1,    -1,    89,    50,    91,    92,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      -1,    -1,    -1,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,
       6,     7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    84,    85,
      -1,    -1,    -1,    89,    50,    91,    92,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      -1,    -1,    -1,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    -1,
       6,     7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    43,    84,    85,
      -1,    -1,    -1,    89,    50,    91,    92,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    65,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,
       6,     7,     8,    -1,    -1,    -1,    12,    13,    84,    85,
      -1,    -1,    -1,    89,    20,    91,    92,    93,    94,    95,
      26,    -1,    -1,    -1,    42,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    50,    39,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    -1,    -1,    65,
      78,    79,    80,    81,    82,    83,    -1,    73,    74,    75,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      -1,    -1,    -1,    89,    -1,    91,    92,    93,    94,    95
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     5,    66,    67,    68,    69,    70,    71,
      72,    77,    79,    80,   124,   125,   133,   134,   135,   136,
     170,   171,   172,   173,   174,    42,    45,   174,     8,    89,
     126,   128,   129,    78,   147,   127,   128,    45,    89,     0,
       1,   171,    41,   162,    89,    89,    11,    43,   132,    45,
      47,     8,    89,   134,    41,     1,     6,     7,     8,    12,
      13,    20,    26,    39,    42,    43,    45,    50,    52,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    73,    74,    75,    84,    85,    86,    87,    89,    91,
      92,    93,    94,    95,    98,    99,   100,   102,   103,   104,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   122,   124,   155,   156,   157,   159,
     161,   162,   163,   164,   165,   166,   167,   169,   175,    39,
      45,    89,   120,   102,   119,   123,    11,    43,   129,    11,
      45,    50,    81,    82,    83,    89,   134,   135,   137,   138,
     139,   141,   142,   143,   146,   147,    42,    39,   102,   102,
     122,   146,   152,    11,    89,   179,   180,    39,    39,   123,
      46,    39,   155,    39,    89,    45,    45,    45,   122,    39,
      39,   102,    43,   108,   134,    24,   160,    23,   158,    46,
      12,    13,    25,    39,    43,    48,    11,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,   121,   108,     8,
       9,    10,     6,     7,    23,    24,    16,    17,    18,    19,
      14,    15,    20,    22,    21,    27,    28,    49,    45,    47,
      45,    45,    42,   164,    40,   150,   151,   174,    44,    41,
     130,   123,   120,    89,    46,    46,    46,    39,   146,    45,
      42,   138,    45,   129,   140,   144,   145,   146,    40,     8,
      39,    43,   148,   153,   154,    40,    47,    44,    47,   122,
     122,    46,   155,   122,    57,     1,   124,   165,   168,    45,
      45,   122,   152,    44,   127,   120,    24,    88,   120,    23,
     155,    89,    40,   101,   120,   122,    89,   120,   108,   108,
     108,   109,   109,   110,   110,   111,   111,   111,   111,   112,
     112,   113,   114,   115,   116,   117,   122,   120,    40,    47,
      89,   120,   131,    44,    39,    40,   150,   162,    45,    47,
     147,   148,   149,    40,   150,   153,    44,   123,   154,    39,
      43,   108,   180,    39,   162,   176,   177,    11,    89,    40,
      40,   155,    40,    39,   165,    40,    40,   108,    39,    43,
     105,   106,   120,    88,   120,    40,    47,    44,    46,   151,
      42,    47,    40,   162,    40,   145,   147,   148,    40,    40,
      44,    40,   150,    44,   123,    47,    40,   150,   162,    25,
     178,   155,   155,   155,   122,    40,   122,   155,    40,   101,
     122,    43,   106,   120,   119,   120,   162,   162,    40,    44,
      40,   152,    53,    40,   155,    40,    40,    44,   122,   155,
      45,   155,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    98,    98,    98,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   104,   104,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   109,   109,   110,   110,   110,   111,   111,   111,
     112,   112,   112,   112,   112,   113,   113,   113,   114,   114,
     115,   115,   116,   116,   117,   117,   118,   118,   119,   119,
     120,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   122,   123,   124,   124,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   129,   129,   129,
     129,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     134,   134,   134,   134,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   138,   139,   139,   139,   140,   141,   141,
     141,   141,   141,   141,   141,   142,   142,   143,   144,   144,
     145,   146,   146,   146,   146,   147,   147,   148,   148,   148,
     148,   149,   149,   150,   150,   151,   152,   152,   153,   153,
     153,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     155,   155,   155,   155,   155,   155,   155,   156,   156,   157,
     158,   158,   158,   158,   159,   160,   160,   161,   161,   161,
     162,   162,   163,   163,   164,   164,   164,   165,   165,   166,
     166,   166,   167,   167,   167,   167,   167,   168,   168,   169,
     169,   169,   169,   169,   170,   170,   170,   171,   171,   171,
     171,   172,   172,   173,   173,   174,   175,   175,   176,   177,
     177,   178,   178,   179,   179,   179,   179,   180,   180
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       4,     3,     3,     4,     2,     3,     4,     2,     1,     4,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     5,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     2,     3,     1,
       3,     1,     0,     2,     1,     1,     2,     2,     3,     4,
       4,     3,     1,     3,     4,     3,     1,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     2,     1,     1,
       1,     2,     1,     1,     2,     2,     2,     0,     3,     2,
       3,     2,     1,     1,     1,     5,     4,     5,     1,     3,
       1,     2,     1,     2,     1,     1,     0,     1,     2,     2,
       3,     1,     2,     1,     3,     2,     1,     2,     1,     1,
       2,     3,     2,     3,     3,     4,     2,     3,     3,     4,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     3,     3,     2,     2,     3,     3,     4,     3,
       2,     3,     1,     2,     1,     1,     2,     1,     2,     5,
       7,     5,     5,     5,     7,     6,     7,     1,     1,     3,
       2,     2,     2,     3,     1,     2,     1,     1,     2,     1,
       4,     4,     5,     2,     2,     2,     5,     4,     2,     2,
       3,     0,     2,     1,     1,     3,     3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* primary_expression: IDENTIFIER  */
#line 219 "src/parser.y"
                     {
            dbg("primary_expression -> IDENTIFIER");
          Node* n = new Node();
          string name = string((yyvsp[0].str));
          n->place = name;
          Symbol* sym = lookupSymbol(name);
          if (!sym) {
              yyerror("Use of undeclared identifier '" + name + "'.");
          } else {
              check_access(sym);
              n->kind = sym->kind;
              n->type = sym->type;
          }
          (yyval.node) = n;
      }
#line 1940 "src/parser.tab.c"
    break;

  case 3: /* primary_expression: constant  */
#line 234 "src/parser.y"
                   { 
        dbg("primary_expression -> constant");
        (yyval.node) = (yyvsp[0].node); }
#line 1948 "src/parser.tab.c"
    break;

  case 4: /* primary_expression: LROUND expression RROUND  */
#line 237 "src/parser.y"
                                   { 
        dbg("primary_expression -> ( expression )");
        (yyval.node) = (yyvsp[-1].node); }
#line 1956 "src/parser.tab.c"
    break;

  case 5: /* primary_expression: lambda_expression  */
#line 240 "src/parser.y"
                        { 
        dbg("primary_expression -> lambda_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 1964 "src/parser.tab.c"
    break;

  case 6: /* constant: DECIMAL_LITERAL  */
#line 246 "src/parser.y"
                            {
          dbg("constant -> DECIMAL_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "int", "constant");
          (yyval.node) = n;
      }
#line 1974 "src/parser.tab.c"
    break;

  case 7: /* constant: CHARACTER_LITERAL  */
#line 251 "src/parser.y"
                            {
            dbg("constant -> CHARACTER_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "char", "constant");
          (yyval.node) = n;
      }
#line 1984 "src/parser.tab.c"
    break;

  case 8: /* constant: STRING_LITERAL  */
#line 256 "src/parser.y"
                            {
            dbg("constant -> STRING_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "string", "constant");
          (yyval.node) = n;
      }
#line 1994 "src/parser.tab.c"
    break;

  case 9: /* constant: EXPONENT_LITERAL  */
#line 261 "src/parser.y"
                            {
            dbg("constant -> EXPONENT_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "double", "constant");
          (yyval.node) = n;
      }
#line 2004 "src/parser.tab.c"
    break;

  case 10: /* constant: DOUBLE_LITERAL  */
#line 266 "src/parser.y"
                            {
            dbg("constant -> DOUBLE_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "double", "constant");
          (yyval.node) = n;
      }
#line 2014 "src/parser.tab.c"
    break;

  case 11: /* constant: NULLPTR  */
#line 271 "src/parser.y"
                            {
            dbg("constant -> NULLPTR");
          Node* n = new Node("0", "nullptr", "constant");
          (yyval.node) = n;
      }
#line 2024 "src/parser.tab.c"
    break;

  case 12: /* constant: TRUE  */
#line 276 "src/parser.y"
                            {
            dbg("constant -> TRUE");
          Node* n = new Node("1", "bool", "constant");
          (yyval.node) = n;
      }
#line 2034 "src/parser.tab.c"
    break;

  case 13: /* constant: FALSE  */
#line 281 "src/parser.y"
                            {
            dbg("constant -> FALSE");
          Node* n = new Node("0", "bool", "constant");
          (yyval.node) = n;
      }
#line 2044 "src/parser.tab.c"
    break;

  case 14: /* postfix_expression: primary_expression  */
#line 289 "src/parser.y"
                             { 
        dbg("postfix_expression -> primary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2052 "src/parser.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression LSQUARE expression RSQUARE  */
#line 292 "src/parser.y"
                                                        {
        dbg("postfix_expression -> postfix_expression [ expression ]");
          Node* base = (yyvsp[-3].node); Node* idx = (yyvsp[-1].node);
          if(base->kind!="array" && base->kind!="pointer"){
              yyerror("Subscripted value is not an array or pointer.");
          }
          if(idx->type!="int"){
              yyerror("Index is not an integer.");
          }

          Node* n = new Node();
          n->code = base->code;
          n->code.insert(n->code.end(), idx->code.begin(), idx->code.end());

          if(lastUsage=="lvalue"){
            n->place = base->place + "[" + idx->place + "]";
          }
          else{
            n->place = newTemp();
            n->code.push_back(n->place + " = " + base->place + "[" + idx->place + "];");
          }
          n->type = base->type;
          n->kind = lastUsage;          
          
          (yyval.node) = n;
      }
#line 2083 "src/parser.tab.c"
    break;

  case 16: /* postfix_expression: postfix_expression LROUND RROUND  */
#line 318 "src/parser.y"
                                           {
        dbg("postfix_expression -> postfix_expression ( )");
            Node* fun = (yyvsp[-2].node);
            Symbol* s = lookupSymbol(fun->place);
            check_access(s);
            if(!s || !s->isFunction){
                yyerror("Call to non-function '" + fun->place + "'.");
            }
            if(s->isFunction && s->paramCount != 0){
                yyerror("Call to function '" + fun->place + "' with incorrect number of arguments.");
            }
            Node* n = new Node();
            n->code = fun->code;
            n->type = fun->type;

            if(fun->type=="void"){
                n->code.push_back("call " + fun->place + ", 0;");
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = call " + fun->place + ", 0;");
            }
            (yyval.node) = n;
        }
#line 2112 "src/parser.tab.c"
    break;

  case 17: /* postfix_expression: postfix_expression LROUND argument_expression_list RROUND  */
#line 342 "src/parser.y"
                                                                    {
        dbg("postfix_expression -> postfix_expression ( argument_expression_list )");
            Node* fun = (yyvsp[-3].node); Node* args = (yyvsp[-1].node);
            Symbol* s = lookupSymbol(fun->place);
            check_access(s);
            if(!s || !s->isFunction){
                yyerror("Call to non-function '" + fun->place + "'.");
            }
            if (s->isFunction && s->paramCount != args->argCount) {
                yyerror("Call to function '" + fun->place + "' with incorrect number of arguments.");
            }
            Node* n = new Node();
            n->code = fun->code;
            n->type = fun->type;
            n->code.insert(n->code.end(), args->code.begin(), args->code.end());
            if(fun->type=="void"){
                n->code.push_back("call " + fun->place + ", " + to_string(args->argCount) + ";");
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = call " + fun->place + ", " + to_string(args->argCount) + ";");
            }
            (yyval.node) = n;
      }
#line 2141 "src/parser.tab.c"
    break;

  case 18: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 366 "src/parser.y"
                                            {
        dbg("postfix_expression -> postfix_expression . IDENTIFIER");
            Node* obj = (yyvsp[-2].node);
            if(obj->kind=="pointer"){
                yyerror("Member access through pointer must use '->' operator.");
            }
            Symbol* s = lookupSymbol(obj->type + "." + string((yyvsp[0].str)));
            if(!s){
                yyerror("No member named '" + string((yyvsp[0].str)) + "' in '" + obj->type + "'.");
            }
            check_access(s);
            Node* n = new Node();
            n->code = obj->code;

            if(lastUsage=="lvalue"){
                n->place = obj->place + "." + string((yyvsp[0].str));
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = " + obj->place + "." + string((yyvsp[0].str)) + ";");
            }
            n->type = s->type;
            (yyval.node) = n;
      }
#line 2170 "src/parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 390 "src/parser.y"
                                              {
        dbg("postfix_expression -> postfix_expression ARROW IDENTIFIER");
          Node* obj = (yyvsp[-2].node);
          Symbol* s = lookupSymbol(obj->type + "." + string((yyvsp[0].str)));
            if(!s){
                yyerror("No member named '" + string((yyvsp[0].str)) + "' in '" + obj->type + "'.");
            }
            check_access(s);
          Node* n = new Node();
          n->code = obj->code;
          if(lastUsage=="lvalue"){
              n->place = obj->place + "->" + string((yyvsp[0].str));
          }
          else{
              n->place = newTemp();
              n->code.push_back(n->place + " = " + obj->place + "->" + string((yyvsp[0].str)) + ";");
          }
          n->type = s->type;
          (yyval.node) = n;
      }
#line 2195 "src/parser.tab.c"
    break;

  case 20: /* postfix_expression: postfix_expression INCREMENT  */
#line 410 "src/parser.y"
                                       {
          dbg("postfix_expression -> postfix_expression ++");
          Node* v = (yyvsp[-1].node);
          if(v->kind!="lvalue"){
              yyerror("Lvalue required as increment operand.");
          }
          if(v->type=="bool" || v->type=="nullptr" || v->type=="string" || v->type=="char"){
              yyerror("Invalid type '" + v->type + "' for increment.");
          }
          Node* n = new Node();
          n->code = v->code;
          string old = newTemp();
            n->code.push_back(old + " = " + v->place + ";");          // load old value from address
            n->code.push_back(v->place + " = " + old + " + 1;");      // store back incremented value

            n->place = old;
          n->type = v->type;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 2220 "src/parser.tab.c"
    break;

  case 21: /* postfix_expression: postfix_expression DECREMENT  */
#line 430 "src/parser.y"
                                       { 
            dbg("postfix_expression -> postfix_expression --");
          Node* v = (yyvsp[-1].node);
            if(v->kind!="lvalue"){
                yyerror("Lvalue required as decrement operand.");
            }
            if(v->type=="bool" || v->type=="nullptr" || v->type=="string" || v->type=="char"){
                yyerror("Invalid type '" + v->type + "' for decrement.");
            }
          Node* n = new Node();
          n->code = v->code;
          string old = newTemp();
            n->code.push_back(old + " = " + v->place + ";");          // load old value from address
            n->code.push_back(v->place + " = " + old + " - 1;");      // store back incremented value

            n->place = old;
          n->type = v->type;
          n->kind = "rvalue";
          (yyval.node) = n;
      }
#line 2245 "src/parser.tab.c"
    break;

  case 22: /* argument_expression_list: assignment_expression  */
#line 453 "src/parser.y"
                                {
          dbg("argument_expression_list -> assignment_expression");
          Node* e = (yyvsp[0].node);
          if(e->place.empty()){
              yyerror("Void expression cannot be used as function argument.");
          }
          Node* n = new Node();
          n->code = e->code;
          n->argCount = 1;
          n->code.push_back("param " + e->place + ";");
          (yyval.node) = n;
      }
#line 2262 "src/parser.tab.c"
    break;

  case 23: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 465 "src/parser.y"
                                                               {
            dbg("argument_expression_list -> argument_expression_list , assignment_expression");
            Node* e = (yyvsp[0].node);
            if(e->place.empty()){
                yyerror("Void expression cannot be used as function argument.");
            }
          Node* n = (yyvsp[-2].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->argCount = n->argCount + 1;
          n->code.push_back("param " + e->place + ";");
          (yyval.node) = n;
      }
#line 2279 "src/parser.tab.c"
    break;

  case 24: /* unary_expression: postfix_expression  */
#line 480 "src/parser.y"
                             { 
        dbg("unary_expression -> postfix_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2287 "src/parser.tab.c"
    break;

  case 25: /* unary_expression: INCREMENT unary_expression  */
#line 483 "src/parser.y"
                                     {
          dbg("unary_expression -> ++ unary_expression");
          Node* v = (yyvsp[0].node);
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " + 1;");
          (yyval.node) = n;
      }
#line 2301 "src/parser.tab.c"
    break;

  case 26: /* unary_expression: DECREMENT unary_expression  */
#line 492 "src/parser.y"
                                     {
            dbg("unary_expression -> -- unary_expression");
          Node* v = (yyvsp[0].node);
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " - 1;");
          (yyval.node) = n;
      }
#line 2315 "src/parser.tab.c"
    break;

  case 27: /* unary_expression: unary_operator cast_expression  */
#line 501 "src/parser.y"
                                         {
            dbg("unary_expression -> unary_operator cast_expression");
          Node* rhs = (yyvsp[0].node);
          Node* n = new Node();
          n->code = rhs->code;
          string op = string((yyvsp[-1].str));
          if (op == "&") {
              n->place = newTemp();
              n->code.push_back(n->place + " = &" + rhs->place + ";");
              n->type = rhs->type + "*";
          } else if (op == "*") {
              n->place = newTemp();
              n->code.push_back(n->place + " = *" + rhs->place + ";");
              n->type = rhs->type;
          } else if (op == "+") {
              n->place = rhs->place;
              n->type = rhs->type;
          } else if (op == "-") {
              n->place = newTemp();
              n->code.push_back(n->place + " = 0 - " + rhs->place + ";");
              n->type = rhs->type;
          } else if (op == "~") {
              n->place = newTemp();
              n->code.push_back(n->place + " = ~" + rhs->place + ";");
              n->type = rhs->type;
          } else if (op == "!") {
              n->place = newTemp();
              n->code.push_back(n->place + " = !" + rhs->place + ";");
              n->type = "bool";
          }
          (yyval.node) = n;
      }
#line 2352 "src/parser.tab.c"
    break;

  case 28: /* unary_expression: SIZEOF unary_expression  */
#line 533 "src/parser.y"
                                  {
          dbg("unary_expression -> sizeof unary_expression");
          Node* n = new Node(); n->place = "sizeof"; (yyval.node) = n;
      }
#line 2361 "src/parser.tab.c"
    break;

  case 29: /* unary_expression: SIZEOF LROUND type_name RROUND  */
#line 537 "src/parser.y"
                                         {
            dbg("unary_expression -> sizeof ( type_name )");
          Node* n = new Node(); n->place = "sizeof"; (yyval.node) = n;
      }
#line 2370 "src/parser.tab.c"
    break;

  case 30: /* unary_expression: delete_expression  */
#line 541 "src/parser.y"
                            { 
        dbg("unary_expression -> delete_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2378 "src/parser.tab.c"
    break;

  case 31: /* unary_expression: new_expression  */
#line 544 "src/parser.y"
                         { 
        dbg("unary_expression -> new_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2386 "src/parser.tab.c"
    break;

  case 32: /* unary_operator: BITWISE_AND  */
#line 550 "src/parser.y"
                      { 
        dbg("unary_operator -> &");
        (yyval.str) = (yyvsp[0].str); }
#line 2394 "src/parser.tab.c"
    break;

  case 33: /* unary_operator: STAR  */
#line 553 "src/parser.y"
               { 
        dbg("unary_operator -> *");
        (yyval.str) = (yyvsp[0].str); }
#line 2402 "src/parser.tab.c"
    break;

  case 34: /* unary_operator: PLUS  */
#line 556 "src/parser.y"
               { 
        dbg("unary_operator -> +");
        (yyval.str) = (yyvsp[0].str); }
#line 2410 "src/parser.tab.c"
    break;

  case 35: /* unary_operator: MINUS  */
#line 559 "src/parser.y"
                { 
        dbg("unary_operator -> -");
        (yyval.str) = (yyvsp[0].str); }
#line 2418 "src/parser.tab.c"
    break;

  case 36: /* unary_operator: TILDE  */
#line 562 "src/parser.y"
                { 
        dbg("unary_operator -> ~");
        (yyval.str) = (yyvsp[0].str); }
#line 2426 "src/parser.tab.c"
    break;

  case 37: /* unary_operator: LOGICAL_NOT  */
#line 565 "src/parser.y"
                      { 
        dbg("unary_operator -> !");
        (yyval.str) = (yyvsp[0].str); }
#line 2434 "src/parser.tab.c"
    break;

  case 38: /* new_expression: NEW type_specifier pointer_opt new_declarator scalar_new_init_opt  */
#line 571 "src/parser.y"
                                                                            {
          dbg("new_expression -> NEW type_specifier pointer_opt new_declarator scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2447 "src/parser.tab.c"
    break;

  case 39: /* new_expression: NEW type_specifier pointer_opt scalar_new_init_opt  */
#line 579 "src/parser.y"
                                                             {
            dbg("new_expression -> NEW type_specifier pointer_opt scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2460 "src/parser.tab.c"
    break;

  case 40: /* new_expression: NEW type_specifier pointer_opt new_declarator  */
#line 587 "src/parser.y"
                                                        {
            dbg("new_expression -> NEW type_specifier pointer_opt new_declarator");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2473 "src/parser.tab.c"
    break;

  case 41: /* new_expression: NEW type_specifier pointer_opt  */
#line 595 "src/parser.y"
                                         {
            dbg("new_expression -> NEW type_specifier pointer_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2486 "src/parser.tab.c"
    break;

  case 42: /* new_declarator: LSQUARE expression RSQUARE  */
#line 606 "src/parser.y"
                                     { 
        dbg("new_declarator -> [ expression ]");
        (yyval.node) = (yyvsp[-1].node); }
#line 2494 "src/parser.tab.c"
    break;

  case 43: /* new_declarator: new_declarator LSQUARE expression RSQUARE  */
#line 609 "src/parser.y"
                                                    { 
        dbg("new_declarator -> new_declarator [ expression ]");
        (yyval.node) = (yyvsp[-1].node); }
#line 2502 "src/parser.tab.c"
    break;

  case 44: /* scalar_new_init_opt: LROUND RROUND  */
#line 615 "src/parser.y"
                        { 
        dbg("scalar_new_init_opt -> ( )");
        (yyval.node) = nullptr; }
#line 2510 "src/parser.tab.c"
    break;

  case 45: /* scalar_new_init_opt: LROUND argument_expression_list RROUND  */
#line 618 "src/parser.y"
                                                 { 
        dbg("scalar_new_init_opt -> ( argument_expression_list )");
        (yyval.node) = (yyvsp[-1].node); }
#line 2518 "src/parser.tab.c"
    break;

  case 46: /* delete_expression: DELETE LSQUARE RSQUARE cast_expression  */
#line 624 "src/parser.y"
                                                 {
          dbg("delete_expression -> DELETE [ ] cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("free " + (yyvsp[0].node)->place + ";");
          (yyval.node) = n;
      }
#line 2530 "src/parser.tab.c"
    break;

  case 47: /* delete_expression: DELETE cast_expression  */
#line 631 "src/parser.y"
                                 {
            dbg("delete_expression -> DELETE cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("free " + (yyvsp[0].node)->place + ";");
          (yyval.node) = n;
      }
#line 2542 "src/parser.tab.c"
    break;

  case 48: /* cast_expression: unary_expression  */
#line 641 "src/parser.y"
                           { 
        dbg("cast_expression -> unary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2550 "src/parser.tab.c"
    break;

  case 49: /* cast_expression: LROUND type_name RROUND cast_expression  */
#line 644 "src/parser.y"
                                                  {
            dbg("cast_expression -> ( type_name ) cast_expression");
          (yyval.node) = (yyvsp[0].node);
      }
#line 2559 "src/parser.tab.c"
    break;

  case 50: /* multiplicative_expression: cast_expression  */
#line 651 "src/parser.y"
                          { 
        dbg("multiplicative_expression -> cast_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2567 "src/parser.tab.c"
    break;

  case 51: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 654 "src/parser.y"
                                                         {
        dbg("multiplicative_expression -> multiplicative_expression * cast_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " * " + b->place + ";");
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2582 "src/parser.tab.c"
    break;

  case 52: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 664 "src/parser.y"
                                                           {
        dbg("multiplicative_expression -> multiplicative_expression / cast_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " / " + b->place + ";");
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2597 "src/parser.tab.c"
    break;

  case 53: /* multiplicative_expression: multiplicative_expression MODULUS cast_expression  */
#line 674 "src/parser.y"
                                                            {
        dbg("multiplicative_expression -> multiplicative_expression % cast_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " % " + b->place + ";");
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2612 "src/parser.tab.c"
    break;

  case 54: /* additive_expression: multiplicative_expression  */
#line 687 "src/parser.y"
                                    { 
        dbg("additive_expression -> multiplicative_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2620 "src/parser.tab.c"
    break;

  case 55: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 690 "src/parser.y"
                                                             {
            dbg("additive_expression -> additive_expression + multiplicative_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " + " + b->place + ";");
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2635 "src/parser.tab.c"
    break;

  case 56: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 700 "src/parser.y"
                                                              {
            dbg("additive_expression -> additive_expression - multiplicative_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " - " + b->place + ";");
          n->type = a->type;
          (yyval.node) = n;
      }
#line 2650 "src/parser.tab.c"
    break;

  case 57: /* shift_expression: additive_expression  */
#line 713 "src/parser.y"
                              { 
        dbg("shift_expression -> additive_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2658 "src/parser.tab.c"
    break;

  case 58: /* shift_expression: shift_expression LEFT_SHIFT additive_expression  */
#line 716 "src/parser.y"
                                                          {
            dbg("shift_expression -> shift_expression << additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " << " + b->place + ";");
          n->type = a->type; (yyval.node) = n;
      }
#line 2672 "src/parser.tab.c"
    break;

  case 59: /* shift_expression: shift_expression RIGHT_SHIFT additive_expression  */
#line 725 "src/parser.y"
                                                           {
            dbg("shift_expression -> shift_expression >> additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " >> " + b->place + ";");
          n->type = a->type; (yyval.node) = n;
      }
#line 2686 "src/parser.tab.c"
    break;

  case 60: /* relational_expression: shift_expression  */
#line 737 "src/parser.y"
                           { 
        dbg("relational_expression -> shift_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2694 "src/parser.tab.c"
    break;

  case 61: /* relational_expression: relational_expression GREATER_THAN shift_expression  */
#line 740 "src/parser.y"
                                                              {
          dbg("relational_expression -> relational_expression > shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " > " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2706 "src/parser.tab.c"
    break;

  case 62: /* relational_expression: relational_expression LESS_THAN shift_expression  */
#line 747 "src/parser.y"
                                                           {
          dbg("relational_expression -> relational_expression < shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " < " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2718 "src/parser.tab.c"
    break;

  case 63: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 754 "src/parser.y"
                                                            {
            dbg("relational_expression -> relational_expression <= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " <= " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2730 "src/parser.tab.c"
    break;

  case 64: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 761 "src/parser.y"
                                                               {
            dbg("relational_expression -> relational_expression >= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " >= " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2742 "src/parser.tab.c"
    break;

  case 65: /* equality_expression: relational_expression  */
#line 771 "src/parser.y"
                                { 
        dbg("equality_expression -> relational_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2750 "src/parser.tab.c"
    break;

  case 66: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 774 "src/parser.y"
                                                          {
            dbg("equality_expression -> equality_expression == relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " == " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2762 "src/parser.tab.c"
    break;

  case 67: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 781 "src/parser.y"
                                                              {
            dbg("equality_expression -> equality_expression != relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " != " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2774 "src/parser.tab.c"
    break;

  case 68: /* and_expression: equality_expression  */
#line 791 "src/parser.y"
                              { 
        dbg("and_expression -> equality_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2782 "src/parser.tab.c"
    break;

  case 69: /* and_expression: and_expression BITWISE_AND equality_expression  */
#line 794 "src/parser.y"
                                                         {
            dbg("and_expression -> and_expression & equality_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " & " + b->place + ";");
          (yyval.node) = n;
      }
#line 2794 "src/parser.tab.c"
    break;

  case 70: /* exclusive_or_expression: and_expression  */
#line 804 "src/parser.y"
                         { 
        dbg("exclusive_or_expression -> and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2802 "src/parser.tab.c"
    break;

  case 71: /* exclusive_or_expression: exclusive_or_expression BITWISE_XOR and_expression  */
#line 807 "src/parser.y"
                                                             {
            dbg("exclusive_or_expression -> exclusive_or_expression ^ and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " ^ " + b->place + ";");
          (yyval.node) = n;
      }
#line 2814 "src/parser.tab.c"
    break;

  case 72: /* inclusive_or_expression: exclusive_or_expression  */
#line 817 "src/parser.y"
                                  { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2822 "src/parser.tab.c"
    break;

  case 73: /* inclusive_or_expression: inclusive_or_expression BITWISE_OR exclusive_or_expression  */
#line 820 "src/parser.y"
                                                                     {
            dbg("inclusive_or_expression -> inclusive_or_expression | exclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " | " + b->place + ";");
          (yyval.node) = n;
      }
#line 2834 "src/parser.tab.c"
    break;

  case 74: /* logical_and_expression: inclusive_or_expression  */
#line 830 "src/parser.y"
                                  { 
        dbg("logical_and_expression -> inclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2842 "src/parser.tab.c"
    break;

  case 75: /* logical_and_expression: logical_and_expression LOGICAL_AND inclusive_or_expression  */
#line 833 "src/parser.y"
                                                                     {
            dbg("logical_and_expression -> logical_and_expression && inclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " && " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2854 "src/parser.tab.c"
    break;

  case 76: /* logical_or_expression: logical_and_expression  */
#line 843 "src/parser.y"
                                 { 
        dbg("logical_or_expression -> logical_and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2862 "src/parser.tab.c"
    break;

  case 77: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 846 "src/parser.y"
                                                                  {
            dbg("logical_or_expression -> logical_or_expression || logical_and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " || " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2874 "src/parser.tab.c"
    break;

  case 78: /* conditional_expression: logical_or_expression  */
#line 856 "src/parser.y"
                                { 
        dbg("conditional_expression -> logical_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2882 "src/parser.tab.c"
    break;

  case 79: /* conditional_expression: logical_or_expression QUESTION_MARK expression COLON conditional_expression  */
#line 859 "src/parser.y"
                                                                                      {
            dbg("conditional_expression -> logical_or_expression ? expression : conditional_expression");
          Node* cond = (yyvsp[-4].node); Node* e1 = (yyvsp[-2].node); Node* e2 = (yyvsp[0].node);
          Node* n = new Node();
          string Lfalse = newLabel();
          string Lend = newLabel();
          n->code = cond->code;
          n->place = newTemp();
          n->code.push_back("ifFalse " + cond->place + " goto " + Lfalse + ";");
          n->code.insert(n->code.end(), e1->code.begin(), e1->code.end());
          n->code.push_back(n->place + " = " + e1->place + ";");
          n->code.push_back("goto " + Lend + ";");
          n->code.push_back(Lfalse + ":");
          n->code.insert(n->code.end(), e2->code.begin(), e2->code.end());
          n->code.push_back(n->place + " = " + e2->place + ";");
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 2905 "src/parser.tab.c"
    break;

  case 80: /* assignment_expression: conditional_expression  */
#line 880 "src/parser.y"
                                 { 
        dbg("assignment_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2913 "src/parser.tab.c"
    break;

  case 81: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 883 "src/parser.y"
                                                                     {
            dbg("assignment_expression -> unary_expression assignment_operator assignment_expression");
          Node* left = (yyvsp[-2].node); Node* right = (yyvsp[0].node);
          Node* n = new Node();
          n->code = left->code; n->code.insert(n->code.end(), right->code.begin(), right->code.end());
          string op = string((yyvsp[-1].str));
          if (!left->type.empty() && !right->type.empty() && left->type != right->type) {
              yyerror("Type mismatch in assignment to '" + left->place + "' (" + left->type + " = " + right->type + ").");
          }
          if (op == "=") {
              n->code.push_back(left->place + " = " + right->place + ";");
          } else {
              string baseop;
              if (op == "+=") baseop = "+";
              else if (op == "-=") baseop = "-";
              else if (op == "*=") baseop = "*";
              else if (op == "/=") baseop = "/";
              else if (op == "%=") baseop = "%";
              else if (op == "&=") baseop = "&";
              else if (op == "|=") baseop = "|";
              else if (op == "^=") baseop = "^";
              else if (op == "<<=") baseop = "<<";
              else if (op == ">>=") baseop = ">>";
              else baseop = "";
              if (baseop.empty()) n->code.push_back("// unknown compound assignment " + op);
              else n->code.push_back(left->place + " = " + left->place + " " + baseop + " " + right->place + ";");
          }
          (yyval.node) = n;
      }
#line 2947 "src/parser.tab.c"
    break;

  case 82: /* assignment_operator: ASSIGN  */
#line 915 "src/parser.y"
                 { 
        dbg("assignment_operator -> =");
        (yyval.str) = (yyvsp[0].str); }
#line 2955 "src/parser.tab.c"
    break;

  case 83: /* assignment_operator: STAR_EQUAL  */
#line 918 "src/parser.y"
                     { 
        dbg("assignment_operator -> *=");
        (yyval.str) = (yyvsp[0].str); }
#line 2963 "src/parser.tab.c"
    break;

  case 84: /* assignment_operator: DIV_EQUAL  */
#line 921 "src/parser.y"
                    { 
        dbg("assignment_operator -> /=");
        (yyval.str) = (yyvsp[0].str); }
#line 2971 "src/parser.tab.c"
    break;

  case 85: /* assignment_operator: MOD_EQUAL  */
#line 924 "src/parser.y"
                    { 
        dbg("assignment_operator -> %=");
        (yyval.str) = (yyvsp[0].str); }
#line 2979 "src/parser.tab.c"
    break;

  case 86: /* assignment_operator: PLUS_EQUAL  */
#line 927 "src/parser.y"
                     { 
        dbg("assignment_operator -> +=");
        (yyval.str) = (yyvsp[0].str); }
#line 2987 "src/parser.tab.c"
    break;

  case 87: /* assignment_operator: MINUS_EQUAL  */
#line 930 "src/parser.y"
                      { 
        dbg("assignment_operator -> -=");
        (yyval.str) = (yyvsp[0].str); }
#line 2995 "src/parser.tab.c"
    break;

  case 88: /* assignment_operator: LEFT_SHIFT_EQ  */
#line 933 "src/parser.y"
                        { 
        dbg("assignment_operator -> <<=");
        (yyval.str) = (yyvsp[0].str); }
#line 3003 "src/parser.tab.c"
    break;

  case 89: /* assignment_operator: RIGHT_SHIFT_EQ  */
#line 936 "src/parser.y"
                         { 
        dbg("assignment_operator -> >>=");
        (yyval.str) = (yyvsp[0].str); }
#line 3011 "src/parser.tab.c"
    break;

  case 90: /* assignment_operator: AND_EQUAL  */
#line 939 "src/parser.y"
                    { 
        dbg("assignment_operator -> &=");
        (yyval.str) = (yyvsp[0].str); }
#line 3019 "src/parser.tab.c"
    break;

  case 91: /* assignment_operator: XOR_EQUAL  */
#line 942 "src/parser.y"
                    { 
        dbg("assignment_operator -> ^=");
        (yyval.str) = (yyvsp[0].str); }
#line 3027 "src/parser.tab.c"
    break;

  case 92: /* assignment_operator: OR_EQUAL  */
#line 945 "src/parser.y"
                   { 
        dbg("assignment_operator -> |=");
        (yyval.str) = (yyvsp[0].str); }
#line 3035 "src/parser.tab.c"
    break;

  case 93: /* expression: assignment_expression  */
#line 952 "src/parser.y"
    { 
        dbg("expression -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3044 "src/parser.tab.c"
    break;

  case 94: /* expression: expression COMMA assignment_expression  */
#line 957 "src/parser.y"
    {
        dbg("expression -> expression , assignment_expression");
        Node* n = (yyvsp[-2].node);
        Node* e = (yyvsp[0].node);
        n->code.insert(n->code.end(), e->code.begin(), e->code.end());
        n->place = e->place;
        (yyval.node) = n;
    }
#line 3057 "src/parser.tab.c"
    break;

  case 95: /* constant_expression: conditional_expression  */
#line 968 "src/parser.y"
                                 { 
        dbg("constant_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3065 "src/parser.tab.c"
    break;

  case 96: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 976 "src/parser.y"
    {
        dbg("we are in declaration");

        dbg("declaration -> declaration_specifiers init_declarator_list ;");
        (yyval.node) = (yyvsp[-1].node);
    }
#line 3076 "src/parser.tab.c"
    break;

  case 97: /* declaration: error SEMICOLON  */
#line 983 "src/parser.y"
    {
        dbg("declaration -> error ;");
        yyerror("Invalid declaration.");
    }
#line 3085 "src/parser.tab.c"
    break;

  case 98: /* declaration_specifiers: static_opt const_opt type_specifier  */
#line 991 "src/parser.y"
                                          {
        dbg("we are in declaration_specifiers");
        dbg("declaration_specifiers -> static_opt const_opt type_specifier");
        dbg("Type specifier is 000: " + lastDeclType);
        dbg("");
        dbg("");
        (yyval.str) = strdup( (string((yyvsp[-2].str)) + string((yyvsp[-1].str)) + string((yyvsp[0].str))).c_str() );
	}
#line 3098 "src/parser.tab.c"
    break;

  case 99: /* init_declarator_list: init_declarator  */
#line 1004 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator");
        (yyval.node) = (yyvsp[0].node); 
    }
#line 3107 "src/parser.tab.c"
    break;

  case 100: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1009 "src/parser.y"
    {
        dbg("init_declarator_list -> init_declarator_list , init_declarator");
        Node* n = (yyvsp[-2].node);
        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
        (yyval.node) = n;
    }
#line 3118 "src/parser.tab.c"
    break;

  case 101: /* pointer_opt: pointer_list  */
#line 1020 "src/parser.y"
    {
        dbg("pointer_opt -> pointer_list");
        (yyval.str) = (yyvsp[0].str);
    }
#line 3127 "src/parser.tab.c"
    break;

  case 102: /* pointer_opt: %empty  */
#line 1025 "src/parser.y"
    {
        dbg("pointer_opt -> <empty>");
        (yyval.str) = strdup("");
    }
#line 3136 "src/parser.tab.c"
    break;

  case 103: /* pointer_list: pointer_list STAR  */
#line 1034 "src/parser.y"
    {
        dbg("pointer_list -> * pointer_list");
        (yyval.str) = strdup( (string("*") + string((yyvsp[-1].str))).c_str() );
    }
#line 3145 "src/parser.tab.c"
    break;

  case 104: /* pointer_list: STAR  */
#line 1039 "src/parser.y"
    {
        dbg("pointer_list -> *");
        (yyval.str) = strdup("*");
    }
#line 3154 "src/parser.tab.c"
    break;

  case 105: /* init_declarator: IDENTIFIER  */
#line 1048 "src/parser.y"
    {
        dbg("init_declarator -> IDENTIFIER ");
        Node* n = new Node();
        n->place = string((yyvsp[0].str) ? (yyvsp[0].str) : "");
        n->code = {n->place + " = " + '0' + ";"};
        n->argCount = 0;
        n->type = lastDeclType;
        n->kind = "";
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }

        dbg("LEAVE init_declarator: created Node for '" + n->place + "' with type " + n->type);
        (yyval.node) = n;
    }
#line 3175 "src/parser.tab.c"
    break;

  case 106: /* init_declarator: IDENTIFIER square_list  */
#line 1065 "src/parser.y"
    {    
        dbg("init_declarator -> IDENTIFIER square_list ");
        Node* n = new Node();
        n->place = string((yyvsp[-1].str) ? (yyvsp[-1].str) : "");   /* restore actual place */
        n->code = (yyvsp[0].node)->code;
        n->argCount = (yyvsp[0].node)->argCount;
        n->type = lastDeclType;
        n->kind = "";
        for(int i = 0; i < (yyvsp[0].node)->argCount; i++)
        {
            n->kind += "[" + (yyvsp[0].node)->syn[i] + "]";
            n->type += "*";
        }
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }
        dbg("LEAVE init_declarator: created Node for '" + n->place + "' with type " + n->type);
        (yyval.node) = n;
    }
#line 3200 "src/parser.tab.c"
    break;

  case 107: /* init_declarator: pointer_list IDENTIFIER  */
#line 1086 "src/parser.y"
    {    
        dbg("init_declarator -> pointer_list IDENTIFIER ");
        Node* n = new Node();
        n->place = string((yyvsp[0].str) ? (yyvsp[0].str) : "");   /* restore actual place */
        n->code = {};
        n->argCount = 0;
        string stars = string((yyvsp[-1].str));
        n->type = lastDeclType + stars;
        n->kind = "pointer";
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }
        dbg("LEAVE init_declarator: created Node for '" + n->place + "'" + " with type " + n->type);
        (yyval.node) = n;
    }
#line 3221 "src/parser.tab.c"
    break;

  case 108: /* init_declarator: IDENTIFIER ASSIGN assignment_expression  */
#line 1104 "src/parser.y"
    {
        dbg("init_declarator -> IDENTIFIER = initializer ");
        Node* n = new Node();
        string name = string((yyvsp[-2].str));
        n->place = name;
        n->type = lastDeclType;
        n->code = (yyvsp[0].node)->code;
        n->code.push_back(n->place + " = " + (yyvsp[0].node)->place + ";");

        if(n->type != (yyvsp[0].node)->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }
        
        n->kind = "";

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
        dbg("LEAVE init_declarator: created Node for '" + n->place + "'" + " with type " + n->type);

        (yyval.node) = n;
    }
#line 3249 "src/parser.tab.c"
    break;

  case 109: /* init_declarator: pointer_list IDENTIFIER ASSIGN assignment_expression  */
#line 1129 "src/parser.y"
    {
        dbg("init_declarator -> pointer_list IDENTIFIER = initializer ");
        Node* n = new Node();
        string name = string((yyvsp[-2].str));
        n->place = name;

        string stars = string((yyvsp[-3].str));
        
        n->type = lastDeclType + stars;
        n->code = (yyvsp[0].node)->code;
        n->code.push_back(n->place + " = " + (yyvsp[0].node)->place + ";");

        // stars represent pointer
        if ((yyvsp[0].node)->kind !=stars || (yyvsp[0].node)->type!=lastDeclType){
            yyerror("Type mismatch in initialization of '" + name + "'."); 
        }

        n->kind = "pointer";

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }

        dbg("LEAVE init_declarator: created Node for '" + n->place + "'" + " with type " + n->type);
        (yyval.node) = n;
    }
#line 3281 "src/parser.tab.c"
    break;

  case 110: /* init_declarator: IDENTIFIER square_list ASSIGN initializer  */
#line 1158 "src/parser.y"
    {
        dbg("init_declarator -> IDENTIFIER square_list = initializer ");
        Node* n = new Node();
        string name = string((yyvsp[-3].str));
        n->place = name;
        n->type = lastDeclType;
        
        n->code = (yyvsp[0].node)->code;

        int p = 1;
        for(int i = 0; i < (yyvsp[-2].node)->argCount; i++)
        {
            n->kind += "[" + (yyvsp[-2].node)->syn[i] + "]";
            n->type += "*";
            p = p * stoi((yyvsp[-2].node)->syn[i]);
            dbg("");
            dbg("Array dimension " + to_string(i) + " is " + (yyvsp[-2].node)->syn[i]);
        }

        if(lastDeclType != (yyvsp[0].node)->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        dbg("");
        dbg("Array size is " + to_string(p) + ", initializer size is " + to_string((yyvsp[0].node)->argCount));
        dbg("");

        if(p < (yyvsp[0].node)->argCount){
            yyerror("Number of elements in initializer is greater than array size for '" + name + "'.");
        }

        n->argCount = (yyvsp[0].node)->argCount;
        n->code.push_back("// array initialization of '" + name + "' with " + to_string(n->argCount) + " elements");

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
        (yyval.node) = n;
    }
#line 3326 "src/parser.tab.c"
    break;

  case 111: /* initializer: LCURLY initializer_list RCURLY  */
#line 1202 "src/parser.y"
    { 
        dbg("initializer -> { initializer_list }");
        Node* n = new Node();
        n->code = (yyvsp[-1].node)->code;
        n->type = (yyvsp[-1].node)->type;
        n->syn = (yyvsp[-1].node)->syn;
        n->argCount = (yyvsp[-1].node)->argCount;
        (yyval.node) = n;
    }
#line 3340 "src/parser.tab.c"
    break;

  case 112: /* initializer_list: assignment_expression  */
#line 1216 "src/parser.y"
    { 
        dbg("initializer_list -> assignment_expression");
        Node * n = new Node();
        n->code = (yyvsp[0].node)->code;
        n->type = (yyvsp[0].node)->type;
        n->syn = (yyvsp[0].node)->syn;
        n->argCount = 1;
        (yyval.node) = n;
    }
#line 3354 "src/parser.tab.c"
    break;

  case 113: /* initializer_list: initializer_list COMMA assignment_expression  */
#line 1226 "src/parser.y"
    {
        dbg("initializer_list -> initializer_list , assignment_expression");
        Node* n = (yyvsp[-2].node); 

        if(n->type != (yyvsp[0].node)->type)
        {
            yyerror("Type mismatch in initializer list.");
        }

        n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());

        n->argCount = n->argCount + 1;

        (yyval.node) = n;
    }
#line 3374 "src/parser.tab.c"
    break;

  case 114: /* square_list: square_list LSQUARE constant_expression RSQUARE  */
#line 1260 "src/parser.y"
    {
        dbg("square_list -> square_list [ constant_expression ]");
        Node* n = new Node();
        n->argCount = (yyvsp[-3].node)->argCount+1;
        n->code = (yyvsp[-3].node)->code;
        n->syn = (yyvsp[-3].node)->syn;
        n->code.insert(n->code.end(),(yyvsp[-1].node)->code.begin(),(yyvsp[-1].node)->code.end());

        if((yyvsp[-1].node)->type!="int"){
            yyerror("Array size must be of type int.");
        }
        n->syn.push_back(to_string((yyvsp[-1].node)->argCount));
        (yyval.node) = n;
    }
#line 3393 "src/parser.tab.c"
    break;

  case 115: /* square_list: LSQUARE constant_expression RSQUARE  */
#line 1275 "src/parser.y"
    {
        dbg("square_opt -> [ constant_expression ]");
        Node* n = new Node();
        n->argCount = 1;
        n->code = (yyvsp[-1].node)->code;
        n->syn.push_back(to_string((yyvsp[-1].node)->argCount));

        if((yyvsp[-1].node)->type!="int"){
            yyerror("Array size must be of type int.");
        }
        (yyval.node) = n;
    }
#line 3410 "src/parser.tab.c"
    break;

  case 116: /* static_opt: STATIC  */
#line 1292 "src/parser.y"
                 { 
        dbg("static_opt -> STATIC");
        (yyval.str) = strdup("static"); }
#line 3418 "src/parser.tab.c"
    break;

  case 117: /* static_opt: %empty  */
#line 1295 "src/parser.y"
       { 
        dbg("static_opt -> <empty>");
        (yyval.str) = strdup(""); }
#line 3426 "src/parser.tab.c"
    break;

  case 118: /* type_specifier: VOID  */
#line 1301 "src/parser.y"
                 { 
        dbg("type_specifier -> VOID");
        (yyval.str) = strdup("void"); lastDeclType = "void"; }
#line 3434 "src/parser.tab.c"
    break;

  case 119: /* type_specifier: CHAR  */
#line 1304 "src/parser.y"
                 { 
        dbg("type_specifier -> CHAR");
        (yyval.str) = strdup("char"); lastDeclType = "char"; }
#line 3442 "src/parser.tab.c"
    break;

  case 120: /* type_specifier: INT  */
#line 1307 "src/parser.y"
                 { 
        dbg("type_specifier -> INT");
        (yyval.str) = strdup("int"); lastDeclType = "int"; }
#line 3450 "src/parser.tab.c"
    break;

  case 121: /* type_specifier: LONG  */
#line 1310 "src/parser.y"
                 { 
        dbg("type_specifier -> LONG");
        (yyval.str) = strdup("long"); lastDeclType = "long"; }
#line 3458 "src/parser.tab.c"
    break;

  case 122: /* type_specifier: DOUBLE  */
#line 1313 "src/parser.y"
                 { 
        dbg("type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); lastDeclType = "double"; }
#line 3466 "src/parser.tab.c"
    break;

  case 123: /* type_specifier: BOOL  */
#line 1316 "src/parser.y"
                 { 
        dbg("type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); lastDeclType = "bool"; }
#line 3474 "src/parser.tab.c"
    break;

  case 124: /* type_specifier: STRING  */
#line 1319 "src/parser.y"
                 { 
        dbg("type_specifier -> STRING");
        (yyval.str) = strdup("string"); lastDeclType = "string"; }
#line 3482 "src/parser.tab.c"
    break;

  case 125: /* type_specifier: TYPE_NAME  */
#line 1322 "src/parser.y"
                    { 
        dbg("type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str); lastDeclType = string((yyvsp[0].str)); }
#line 3490 "src/parser.tab.c"
    break;

  case 126: /* struct_or_class_specifier: struct_or_class IDENTIFIER LCURLY struct_or_class_member_list RCURLY  */
#line 1328 "src/parser.y"
                                                                               { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        Node* n = new Node(); (yyval.node) = n; }
#line 3498 "src/parser.tab.c"
    break;

  case 127: /* struct_or_class_specifier: struct_or_class IDENTIFIER  */
#line 1331 "src/parser.y"
                                     { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER");
        Node* n = new Node(); (yyval.node) = n; }
#line 3506 "src/parser.tab.c"
    break;

  case 128: /* struct_or_class: STRUCT  */
#line 1337 "src/parser.y"
                 { 
        dbg("struct_or_class -> STRUCT");
        (yyval.node) = new Node(); }
#line 3514 "src/parser.tab.c"
    break;

  case 129: /* struct_or_class: CLASS  */
#line 1340 "src/parser.y"
                { 
        dbg("struct_or_class -> CLASS");
        (yyval.node) = new Node(); }
#line 3522 "src/parser.tab.c"
    break;

  case 130: /* struct_or_class_member_list: struct_or_class_member  */
#line 1346 "src/parser.y"
                                 { 
        dbg("struct_or_class_member_list -> struct_or_class_member");
        (yyval.node) = (yyvsp[0].node); }
#line 3530 "src/parser.tab.c"
    break;

  case 131: /* struct_or_class_member_list: struct_or_class_member_list struct_or_class_member  */
#line 1349 "src/parser.y"
                                                             { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        Node* n = (yyvsp[-1].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; }
#line 3540 "src/parser.tab.c"
    break;

  case 132: /* struct_or_class_member: access_specifier_label  */
#line 1357 "src/parser.y"
                                 { 
        dbg("struct_or_class_member -> access_specifier_label");
        (yyval.node) = (yyvsp[0].node); }
#line 3548 "src/parser.tab.c"
    break;

  case 133: /* struct_or_class_member: member_declaration  */
#line 1360 "src/parser.y"
                             { 
        dbg("struct_or_class_member -> member_declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 3556 "src/parser.tab.c"
    break;

  case 134: /* access_specifier_label: PUBLIC COLON  */
#line 1366 "src/parser.y"
                       { 
        dbg("access_specifier_label -> PUBLIC :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3564 "src/parser.tab.c"
    break;

  case 135: /* access_specifier_label: PRIVATE COLON  */
#line 1369 "src/parser.y"
                        { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3572 "src/parser.tab.c"
    break;

  case 136: /* access_specifier_label: PROTECTED COLON  */
#line 1372 "src/parser.y"
                          { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3580 "src/parser.tab.c"
    break;

  case 138: /* member_declaration: specifier_qualifier_list struct_declarator_list SEMICOLON  */
#line 1379 "src/parser.y"
                                                                    { 
        dbg("member_declaration -> specifier_qualifier_list struct_declarator_list ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3588 "src/parser.tab.c"
    break;

  case 139: /* member_declaration: specifier_qualifier_list SEMICOLON  */
#line 1382 "src/parser.y"
                                             { 
        dbg("member_declaration -> specifier_qualifier_list ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3596 "src/parser.tab.c"
    break;

  case 140: /* member_declaration: specifier_qualifier_list declarator compound_statement  */
#line 1385 "src/parser.y"
                                                                 { 
        dbg("member_declaration -> specifier_qualifier_list declarator compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 3604 "src/parser.tab.c"
    break;

  case 141: /* member_declaration: struct_or_class_specifier SEMICOLON  */
#line 1388 "src/parser.y"
                                              { 
        dbg("member_declaration -> struct_or_class_specifier ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3612 "src/parser.tab.c"
    break;

  case 142: /* member_declaration: SEMICOLON  */
#line 1391 "src/parser.y"
                    { 
        dbg("member_declaration -> ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3620 "src/parser.tab.c"
    break;

  case 143: /* member_declaration: constructor_definition  */
#line 1394 "src/parser.y"
                                 { 
        dbg("member_declaration -> constructor_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 3628 "src/parser.tab.c"
    break;

  case 144: /* member_declaration: destructor_definition  */
#line 1397 "src/parser.y"
                                { 
        dbg("member_declaration -> destructor_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 3636 "src/parser.tab.c"
    break;

  case 145: /* constructor_definition: IDENTIFIER LROUND parameter_list RROUND compound_statement  */
#line 1403 "src/parser.y"
                                                                     {
        dbg("constructor_definition -> IDENTIFIER ( parameter_list ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3645 "src/parser.tab.c"
    break;

  case 146: /* constructor_definition: IDENTIFIER LROUND RROUND compound_statement  */
#line 1407 "src/parser.y"
                                                      {
        dbg("constructor_definition -> IDENTIFIER ( ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3654 "src/parser.tab.c"
    break;

  case 147: /* destructor_definition: TILDE IDENTIFIER LROUND RROUND compound_statement  */
#line 1414 "src/parser.y"
                                                            {
        dbg("destructor_definition -> ~ IDENTIFIER ( ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3663 "src/parser.tab.c"
    break;

  case 148: /* struct_declarator_list: struct_declarator  */
#line 1421 "src/parser.y"
                            { 
        dbg("struct_declarator_list -> struct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3671 "src/parser.tab.c"
    break;

  case 149: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1424 "src/parser.y"
                                                         { 
        dbg("struct_declarator_list -> struct_declarator_list , struct_declarator");
        Node* n = (yyvsp[-2].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; }
#line 3681 "src/parser.tab.c"
    break;

  case 150: /* struct_declarator: init_declarator  */
#line 1432 "src/parser.y"
                          { 
        dbg("struct_declarator -> init_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3689 "src/parser.tab.c"
    break;

  case 151: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1438 "src/parser.y"
                                                  { 
        dbg("specifier_qualifier_list -> type_specifier specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3697 "src/parser.tab.c"
    break;

  case 152: /* specifier_qualifier_list: type_specifier  */
#line 1441 "src/parser.y"
                         { 
        dbg("specifier_qualifier_list -> type_specifier");
        (yyval.node) = new Node(); }
#line 3705 "src/parser.tab.c"
    break;

  case 153: /* specifier_qualifier_list: const_opt specifier_qualifier_list  */
#line 1444 "src/parser.y"
                                             { 
        dbg("specifier_qualifier_list -> const_opt specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3713 "src/parser.tab.c"
    break;

  case 154: /* specifier_qualifier_list: const_opt  */
#line 1447 "src/parser.y"
                    { 
        dbg("specifier_qualifier_list -> const_opt");
        (yyval.node) = new Node(); }
#line 3721 "src/parser.tab.c"
    break;

  case 155: /* const_opt: CONST  */
#line 1454 "src/parser.y"
                { 
        dbg("const_opt -> CONST");
        (yyval.str) = strdup("const"); }
#line 3729 "src/parser.tab.c"
    break;

  case 156: /* const_opt: %empty  */
#line 1457 "src/parser.y"
       {
        dbg("const_opt -> <empty>");
        (yyval.str) = strdup(""); }
#line 3737 "src/parser.tab.c"
    break;

  case 157: /* pointer: STAR  */
#line 1464 "src/parser.y"
               { 
        dbg("pointer -> *");
        (yyval.node) = new Node(); }
#line 3745 "src/parser.tab.c"
    break;

  case 158: /* pointer: STAR type_qualifier_list  */
#line 1467 "src/parser.y"
                                   { 
        dbg("pointer -> * type_qualifier_list");
        (yyval.node) = new Node(); }
#line 3753 "src/parser.tab.c"
    break;

  case 159: /* pointer: STAR pointer  */
#line 1470 "src/parser.y"
                       { 
        dbg("pointer -> * pointer");
        (yyval.node) = new Node(); }
#line 3761 "src/parser.tab.c"
    break;

  case 160: /* pointer: STAR type_qualifier_list pointer  */
#line 1473 "src/parser.y"
                                           { 
        dbg("pointer -> * type_qualifier_list pointer");
        (yyval.node) = new Node(); }
#line 3769 "src/parser.tab.c"
    break;

  case 161: /* type_qualifier_list: const_opt  */
#line 1479 "src/parser.y"
                    { 
        dbg("type_qualifier_list -> const_opt");
        (yyval.node) = new Node(); }
#line 3777 "src/parser.tab.c"
    break;

  case 162: /* type_qualifier_list: type_qualifier_list const_opt  */
#line 1482 "src/parser.y"
                                        { 
        dbg("type_qualifier_list -> type_qualifier_list const_opt");
        (yyval.node) = new Node(); }
#line 3785 "src/parser.tab.c"
    break;

  case 163: /* parameter_list: parameter_declaration  */
#line 1488 "src/parser.y"
                                { 
            dbg("parameter_list -> parameter_declaration");
            (yyval.node) = (yyvsp[0].node); 
        }
#line 3794 "src/parser.tab.c"
    break;

  case 164: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1493 "src/parser.y"
        {
            dbg("parameter_list -> parameter_list , parameter_declaration");
            Node* n = (yyvsp[-2].node);
            n->syn.insert(n->syn.end(), (yyvsp[0].node)->syn.begin(), (yyvsp[0].node)->syn.end()); 
            (yyval.node) = n;
        }
#line 3805 "src/parser.tab.c"
    break;

  case 165: /* parameter_declaration: return_type IDENTIFIER  */
#line 1503 "src/parser.y"
        {
            dbg("parameter_declaration -> return_type IDENTIFIER");
            Node* n = new Node();
            n->syn.push_back(string((yyvsp[-1].str))); 
            n->syn.push_back(string((yyvsp[0].str)));
            (yyval.node) = n;
        }
#line 3817 "src/parser.tab.c"
    break;

  case 166: /* type_name: specifier_qualifier_list  */
#line 1522 "src/parser.y"
                                   { 
        dbg("type_name -> specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3825 "src/parser.tab.c"
    break;

  case 167: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1525 "src/parser.y"
                                                       { 
        dbg("type_name -> specifier_qualifier_list abstract_declarator");
        (yyval.node) = new Node(); }
#line 3833 "src/parser.tab.c"
    break;

  case 168: /* abstract_declarator: pointer  */
#line 1531 "src/parser.y"
                  { 
        dbg("abstract_declarator -> pointer");
        (yyval.node) = new Node(); }
#line 3841 "src/parser.tab.c"
    break;

  case 169: /* abstract_declarator: direct_abstract_declarator  */
#line 1534 "src/parser.y"
                                     { 
        dbg("abstract_declarator -> direct_abstract_declarator");
        (yyval.node) = new Node(); }
#line 3849 "src/parser.tab.c"
    break;

  case 170: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1537 "src/parser.y"
                                             { 
        dbg("abstract_declarator -> pointer direct_abstract_declarator");
        (yyval.node) = new Node(); }
#line 3857 "src/parser.tab.c"
    break;

  case 171: /* direct_abstract_declarator: LROUND abstract_declarator RROUND  */
#line 1543 "src/parser.y"
                                            { 
        dbg("direct_abstract_declarator -> ( abstract_declarator )");
        (yyval.node) = new Node(); }
#line 3865 "src/parser.tab.c"
    break;

  case 172: /* direct_abstract_declarator: LSQUARE RSQUARE  */
#line 1546 "src/parser.y"
                          { 
        dbg("direct_abstract_declarator -> [ ]");
        (yyval.node) = new Node(); }
#line 3873 "src/parser.tab.c"
    break;

  case 173: /* direct_abstract_declarator: LSQUARE constant_expression RSQUARE  */
#line 1549 "src/parser.y"
                                              { 
        dbg("direct_abstract_declarator -> [ constant_expression ]");
        (yyval.node) = new Node(); }
#line 3881 "src/parser.tab.c"
    break;

  case 174: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE RSQUARE  */
#line 1552 "src/parser.y"
                                                     { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator [ ]");
        (yyval.node) = new Node(); }
#line 3889 "src/parser.tab.c"
    break;

  case 175: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression RSQUARE  */
#line 1555 "src/parser.y"
                                                                         { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator [ constant_expression ]");
        (yyval.node) = new Node(); }
#line 3897 "src/parser.tab.c"
    break;

  case 176: /* direct_abstract_declarator: LROUND RROUND  */
#line 1558 "src/parser.y"
                        { 
        dbg("direct_abstract_declarator -> ( )");
        (yyval.node) = new Node(); }
#line 3905 "src/parser.tab.c"
    break;

  case 177: /* direct_abstract_declarator: LROUND parameter_list RROUND  */
#line 1561 "src/parser.y"
                                       { 
        dbg("direct_abstract_declarator -> ( parameter_list )");
        (yyval.node) = new Node(); }
#line 3913 "src/parser.tab.c"
    break;

  case 178: /* direct_abstract_declarator: direct_abstract_declarator LROUND RROUND  */
#line 1564 "src/parser.y"
                                                   { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator ( )");
        (yyval.node) = new Node(); }
#line 3921 "src/parser.tab.c"
    break;

  case 179: /* direct_abstract_declarator: direct_abstract_declarator LROUND parameter_list RROUND  */
#line 1567 "src/parser.y"
                                                                  { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator ( parameter_list )");
        (yyval.node) = new Node(); }
#line 3929 "src/parser.tab.c"
    break;

  case 180: /* statement: labeled_statement  */
#line 1573 "src/parser.y"
                            { 
        dbg("statement -> labeled_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3937 "src/parser.tab.c"
    break;

  case 181: /* statement: compound_statement  */
#line 1576 "src/parser.y"
                             { 
        dbg("statement -> compound_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3945 "src/parser.tab.c"
    break;

  case 182: /* statement: expression_statement  */
#line 1579 "src/parser.y"
                               { 
        dbg("statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3953 "src/parser.tab.c"
    break;

  case 183: /* statement: selection_statement  */
#line 1582 "src/parser.y"
                              { 
        dbg("statement -> selection_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3961 "src/parser.tab.c"
    break;

  case 184: /* statement: iteration_statement  */
#line 1585 "src/parser.y"
                              { 
        dbg("statement -> iteration_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3969 "src/parser.tab.c"
    break;

  case 185: /* statement: jump_statement  */
#line 1588 "src/parser.y"
                         { 
        dbg("statement -> jump_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3977 "src/parser.tab.c"
    break;

  case 186: /* statement: io_statement  */
#line 1591 "src/parser.y"
                       { 
        dbg("statement -> io_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3985 "src/parser.tab.c"
    break;

  case 187: /* io_statement: cout_expression SEMICOLON  */
#line 1597 "src/parser.y"
                                { 
        dbg("io_statement -> cout_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 3993 "src/parser.tab.c"
    break;

  case 188: /* io_statement: cin_expression SEMICOLON  */
#line 1600 "src/parser.y"
                                { 
        dbg("io_statement -> cin_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4001 "src/parser.tab.c"
    break;

  case 189: /* cout_expression: COUT insertion_list  */
#line 1606 "src/parser.y"
                          { 
        dbg("cout_expression -> COUT insertion_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4009 "src/parser.tab.c"
    break;

  case 190: /* insertion_list: LEFT_SHIFT assignment_expression  */
#line 1612 "src/parser.y"
                                       {
          dbg("insertion_list -> LEFT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node);
          Node* n = new Node();
          n->code = e->code; n->code.push_back("print " + e->place + ";"); (yyval.node) = n;
      }
#line 4020 "src/parser.tab.c"
    break;

  case 191: /* insertion_list: LEFT_SHIFT ENDL  */
#line 1618 "src/parser.y"
                          {
            dbg("insertion_list -> LEFT_SHIFT ENDL");
          Node* n = new Node();
          n->code.push_back("print endl;"); (yyval.node) = n;
      }
#line 4030 "src/parser.tab.c"
    break;

  case 192: /* insertion_list: insertion_list LEFT_SHIFT ENDL  */
#line 1623 "src/parser.y"
                                         {
            dbg("insertion_list -> insertion_list LEFT_SHIFT ENDL");
          Node* n = (yyvsp[-2].node); n->code.push_back("print endl;"); (yyval.node) = n;
      }
#line 4039 "src/parser.tab.c"
    break;

  case 193: /* insertion_list: insertion_list LEFT_SHIFT assignment_expression  */
#line 1627 "src/parser.y"
                                                          {
            dbg("insertion_list -> insertion_list LEFT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("print " + e->place + ";"); (yyval.node) = n;
      }
#line 4050 "src/parser.tab.c"
    break;

  case 194: /* cin_expression: CIN extraction_list  */
#line 1636 "src/parser.y"
                          { 
        dbg("cin_expression -> CIN extraction_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4058 "src/parser.tab.c"
    break;

  case 195: /* extraction_list: RIGHT_SHIFT assignment_expression  */
#line 1642 "src/parser.y"
                                        {
            dbg("extraction_list -> RIGHT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node); Node* n = new Node();
          n->code = e->code; n->code.push_back("read " + e->place + ";"); (yyval.node) = n;
      }
#line 4068 "src/parser.tab.c"
    break;

  case 196: /* extraction_list: extraction_list RIGHT_SHIFT assignment_expression  */
#line 1647 "src/parser.y"
                                                        {
            dbg("extraction_list -> extraction_list RIGHT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("read " + e->place + ";"); (yyval.node) = n;
      }
#line 4079 "src/parser.tab.c"
    break;

  case 197: /* labeled_statement: IDENTIFIER COLON statement  */
#line 1656 "src/parser.y"
                                     {
          dbg("labeled_statement -> IDENTIFIER : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string((yyvsp[-2].str)) + ":");
          (yyval.node) = s;
      }
#line 4090 "src/parser.tab.c"
    break;

  case 198: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1662 "src/parser.y"
                                                   {
            dbg("labeled_statement -> CASE constant_expression : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string("case ") + (yyvsp[-2].node)->place + ":");
          (yyval.node) = s;
      }
#line 4101 "src/parser.tab.c"
    break;

  case 199: /* labeled_statement: DEFAULT COLON statement  */
#line 1668 "src/parser.y"
                                  {
            dbg("labeled_statement -> DEFAULT : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string("default:"));
          (yyval.node) = s;
      }
#line 4112 "src/parser.tab.c"
    break;

  case 200: /* compound_statement: LCURLY RCURLY  */
#line 1677 "src/parser.y"
                        {
            dbg("compound_statement -> { }");
          pushScope();
          Node* n = new Node();
          popScope();
          (yyval.node) = n;
      }
#line 4124 "src/parser.tab.c"
    break;

  case 201: /* compound_statement: LCURLY statement_list RCURLY  */
#line 1684 "src/parser.y"
                                       {
            dbg("compound_statement -> { statement_list }");
          pushScope();
          Node* n = (yyvsp[-1].node);
          popScope();
          (yyval.node) = n;
      }
#line 4136 "src/parser.tab.c"
    break;

  case 202: /* statement_list: block_item  */
#line 1694 "src/parser.y"
                     { 
        dbg("statement_list -> block_item");
        (yyval.node) = (yyvsp[0].node); }
#line 4144 "src/parser.tab.c"
    break;

  case 203: /* statement_list: statement_list block_item  */
#line 1697 "src/parser.y"
                                    {
            dbg("statement_list -> statement_list block_item");
          Node* n = (yyvsp[-1].node);
          if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 4155 "src/parser.tab.c"
    break;

  case 204: /* block_item: statement  */
#line 1706 "src/parser.y"
                { 
        dbg("block_item -> statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4163 "src/parser.tab.c"
    break;

  case 205: /* block_item: declaration  */
#line 1709 "src/parser.y"
                  { 
        dbg("block_item -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4171 "src/parser.tab.c"
    break;

  case 206: /* block_item: error RCURLY  */
#line 1712 "src/parser.y"
                   { yyerrok;}
#line 4177 "src/parser.tab.c"
    break;

  case 207: /* expression_statement: SEMICOLON  */
#line 1716 "src/parser.y"
                    { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4185 "src/parser.tab.c"
    break;

  case 208: /* expression_statement: expression SEMICOLON  */
#line 1719 "src/parser.y"
                               { 
        dbg("expression_statement -> expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4193 "src/parser.tab.c"
    break;

  case 209: /* selection_statement: IF LROUND expression RROUND statement  */
#line 1725 "src/parser.y"
                                                                      {
          dbg("selection_statement -> IF ( expression ) statement");
          Node* cond = (yyvsp[-2].node); Node* thenS = (yyvsp[0].node);
          Node* n = new Node();
          string Lend = newLabel();
          n->code = cond->code;
          n->code.push_back("ifFalse " + cond->place + " goto " + Lend + ";");
          n->code.insert(n->code.end(), thenS->code.begin(), thenS->code.end());
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4209 "src/parser.tab.c"
    break;

  case 210: /* selection_statement: IF LROUND expression RROUND statement ELSE statement  */
#line 1736 "src/parser.y"
                                                               {
            dbg("selection_statement -> IF ( expression ) statement ELSE statement");
          Node* cond = (yyvsp[-4].node); Node* thenS = (yyvsp[-2].node); Node* elseS = (yyvsp[0].node);
          Node* n = new Node();
          string Lelse = newLabel(); string Lend = newLabel();
          n->code = cond->code;
          n->code.push_back("ifFalse " + cond->place + " goto " + Lelse + ";");
          n->code.insert(n->code.end(), thenS->code.begin(), thenS->code.end());
          n->code.push_back("goto " + Lend + ";");
          n->code.push_back(Lelse + ":");
          n->code.insert(n->code.end(), elseS->code.begin(), elseS->code.end());
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4228 "src/parser.tab.c"
    break;

  case 211: /* selection_statement: SWITCH LROUND expression RROUND statement  */
#line 1750 "src/parser.y"
                                                    {
            dbg("selection_statement -> SWITCH ( expression ) statement");
          Node* n = (yyvsp[0].node); (yyval.node) = n;
      }
#line 4237 "src/parser.tab.c"
    break;

  case 212: /* iteration_statement: WHILE LROUND expression RROUND statement  */
#line 1757 "src/parser.y"
                                                   {
          dbg("iteration_statement -> WHILE ( expression ) statement");
          Node* cond = (yyvsp[-2].node); Node* body = (yyvsp[0].node);
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back(Lbegin + ":");
          n->code.push_back("ifFalse " + cond->place + " goto " + Lend + ";");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.push_back("goto " + Lbegin + ";");
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4255 "src/parser.tab.c"
    break;

  case 213: /* iteration_statement: UNTIL LROUND expression RROUND statement  */
#line 1770 "src/parser.y"
                                                   {
            dbg("iteration_statement -> UNTIL ( expression ) statement");
          Node* cond = (yyvsp[-2].node); Node* body = (yyvsp[0].node);
          Node* n = new Node();
          string Lbegin = newLabel();
          n->code.push_back(Lbegin + ":");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back("ifTrue " + cond->place + " goto " + Lbegin + ";");
          (yyval.node) = n;
      }
#line 4271 "src/parser.tab.c"
    break;

  case 214: /* iteration_statement: DO statement WHILE LROUND expression RROUND SEMICOLON  */
#line 1781 "src/parser.y"
                                                                {
            dbg("iteration_statement -> DO statement WHILE ( expression ) ;");
          Node* body = (yyvsp[-5].node); Node* cond = (yyvsp[-2].node);
          Node* n = new Node();
          string Lbegin = newLabel();
          n->code.push_back(Lbegin + ":");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back("ifTrue " + cond->place + " goto " + Lbegin + ";");
          (yyval.node) = n;
      }
#line 4287 "src/parser.tab.c"
    break;

  case 215: /* iteration_statement: FOR LROUND for_init_statement expression_statement RROUND statement  */
#line 1792 "src/parser.y"
                                                                              {
            dbg("iteration_statement -> FOR ( for_init_statement expression_statement ) statement");
          Node* init = (yyvsp[-3].node); Node* cond = (yyvsp[-2].node); Node* body = (yyvsp[0].node);
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
          n->code.push_back(Lbegin + ":");
          if (cond) {
              n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
              n->code.push_back("ifFalse " + cond->place + " goto " + Lend + ";");
          }
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.push_back("goto " + Lbegin + ";");
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4308 "src/parser.tab.c"
    break;

  case 216: /* iteration_statement: FOR LROUND for_init_statement expression_statement expression RROUND statement  */
#line 1808 "src/parser.y"
                                                                                         {
            dbg("iteration_statement -> FOR ( for_init_statement expression_statement expression ) statement");
          Node* init = (yyvsp[-4].node); Node* cond = (yyvsp[-3].node); Node* iter = (yyvsp[-2].node); Node* body = (yyvsp[0].node);
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
          n->code.push_back(Lbegin + ":");
          if (cond) {
              n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
              n->code.push_back("ifFalse " + cond->place + " goto " + Lend + ";");
          }
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          if (iter) n->code.insert(n->code.end(), iter->code.begin(), iter->code.end());
          n->code.push_back("goto " + Lbegin + ";");
          n->code.push_back(Lend + ":");
          (yyval.node) = n;
      }
#line 4330 "src/parser.tab.c"
    break;

  case 217: /* for_init_statement: expression_statement  */
#line 1828 "src/parser.y"
                               { 
        dbg("for_init_statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4338 "src/parser.tab.c"
    break;

  case 218: /* for_init_statement: declaration  */
#line 1831 "src/parser.y"
                      { 
        dbg("for_init_statement -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4346 "src/parser.tab.c"
    break;

  case 219: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 1837 "src/parser.y"
                                    {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string((yyvsp[-1].str)) + ";");
          (yyval.node) = n;
      }
#line 4357 "src/parser.tab.c"
    break;

  case 220: /* jump_statement: CONTINUE SEMICOLON  */
#line 1843 "src/parser.y"
                             {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); n->code.push_back("continue;"); (yyval.node) = n;
      }
#line 4366 "src/parser.tab.c"
    break;

  case 221: /* jump_statement: BREAK SEMICOLON  */
#line 1847 "src/parser.y"
                          {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); n->code.push_back("break;"); (yyval.node) = n;
      }
#line 4375 "src/parser.tab.c"
    break;

  case 222: /* jump_statement: RETURN SEMICOLON  */
#line 1851 "src/parser.y"
                           {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); n->code.push_back("return;"); (yyval.node) = n;
      }
#line 4384 "src/parser.tab.c"
    break;

  case 223: /* jump_statement: RETURN expression SEMICOLON  */
#line 1855 "src/parser.y"
                                      {
            dbg("jump_statement -> RETURN expression ;");
          Node* expr = (yyvsp[-1].node);
          Node* n = new Node();
          n->code = expr->code;
          n->code.push_back("return " + expr->place + ";");
          (yyval.node) = n;
      }
#line 4397 "src/parser.tab.c"
    break;

  case 224: /* translation_unit: external_declaration  */
#line 1867 "src/parser.y"
                               { 
        dbg("translation_unit -> external_declaration");
        finalRoot = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 4405 "src/parser.tab.c"
    break;

  case 225: /* translation_unit: translation_unit external_declaration  */
#line 1870 "src/parser.y"
                                                {
            dbg("translation_unit -> translation_unit external_declaration");
          Node* a = (yyvsp[-1].node); Node* b = (yyvsp[0].node);
          if (a) { 
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; (yyval.node) = a; }
          else { finalRoot = b; (yyval.node) = b; }
      }
#line 4418 "src/parser.tab.c"
    break;

  case 226: /* translation_unit: error  */
#line 1878 "src/parser.y"
            { yyerrok;}
#line 4424 "src/parser.tab.c"
    break;

  case 227: /* external_declaration: function_definition  */
#line 1883 "src/parser.y"
                              { 
        dbg("external_declaration -> function_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 4432 "src/parser.tab.c"
    break;

  case 228: /* external_declaration: struct_or_class_specifier SEMICOLON  */
#line 1886 "src/parser.y"
                                              { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4440 "src/parser.tab.c"
    break;

  case 229: /* external_declaration: declaration  */
#line 1889 "src/parser.y"
                      {
        dbg("external_declaration -> declaration");
         (yyval.node) = (yyvsp[0].node); }
#line 4448 "src/parser.tab.c"
    break;

  case 230: /* external_declaration: TYPEDEF return_type IDENTIFIER SEMICOLON  */
#line 1892 "src/parser.y"
                                               {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string((yyvsp[-1].str))] = typeSize[string((yyvsp[-2].str))];
        (yyval.node) = new Node();
        }
#line 4458 "src/parser.tab.c"
    break;

  case 231: /* function_header: return_type IDENTIFIER LROUND RROUND  */
#line 1902 "src/parser.y"
        {
            dbg("function_header -> return_type IDENTIFIER ( ) compound_statement");
            string fname = string((yyvsp[-2].str));

            if(funcTable.find(fname)!=funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string((yyvsp[-3].str)) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;

            funcTable[fname].returnType = string((yyvsp[-3].str));
            funcTable[fname].paramCount = 0;
            // dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");
            // dbg("Function '" + fname + "' with " + to_string(funcTable[fname].paramCount) + " parameters declared.");

            currentFunction = fname;
            localTemp = 0; localLabel = 0;
            Node* n = new Node();
            n->code.push_back(fname + ":");
            pushScope(); 
            (yyval.node) = n;
        }
#line 4485 "src/parser.tab.c"
    break;

  case 232: /* function_header: return_type IDENTIFIER LROUND parameter_list RROUND  */
#line 1926 "src/parser.y"
        {
            dbg("function_definition -> return_type IDENTIFIER ( parameter_list ) compound_statement");
            string fname = string((yyvsp[-3].str));

            if(funcTable.find(fname) != funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string((yyvsp[-4].str)) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;
                       
            funcTable[fname].returnType = string((yyvsp[-4].str)); 
            funcTable[fname].paramCount = (yyvsp[-1].node)->syn.size()/2;
            // dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");
            // dbg("Function '" + fname + "' with " + to_string(funcTable[fname].paramCount) + " parameters declared.");

            for (int i=0;i<(yyvsp[-1].node)->syn.size();i+=2){
                funcTable[fname].paramTypes.push_back((yyvsp[-1].node)->syn[i]);
                // dbg("Parameter: " + $4->syn[i+1] + " of type " + $4->syn[i]);
            }
            
            currentFunction = fname;
            localTemp = 0; localLabel = 0;
            Node* n = new Node();            
            n->code.push_back(fname + ":");
            pushScope(); 

            for(int i=1;i<(yyvsp[-1].node)->syn.size();i+=2){
                string pname = (yyvsp[-1].node)->syn[i];
                string ptype = (yyvsp[-1].node)->syn[i-1];
                bool ok = declareSymbol(pname,ptype);
                if(!ok) yyerror("Duplicate parameter name '" + pname + "' in function '" + fname + "'.");
            }
            (yyval.node) = n;
        }
#line 4524 "src/parser.tab.c"
    break;

  case 233: /* function_definition: function_header compound_statement  */
#line 1964 "src/parser.y"
                                        {
            dbg("function_definition -> function_header compound_statement");
            Node* n = (yyvsp[-1].node);
            if((yyvsp[0].node)) n->code.insert(n->code.end(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end()); 
            popScope(); 
            finalRoot = n;
            currentFunction = "global";
            (yyval.node) = n;
        }
#line 4538 "src/parser.tab.c"
    break;

  case 234: /* function_definition: error RCURLY  */
#line 1973 "src/parser.y"
                   { yyerrok;}
#line 4544 "src/parser.tab.c"
    break;

  case 235: /* return_type: type_specifier pointer_opt  */
#line 1979 "src/parser.y"
    { 
        dbg("return_type -> type_specifier pointer_opt");
        (yyval.str) = strdup( (string((yyvsp[-1].str)) + string((yyvsp[0].str))).c_str() );
    }
#line 4553 "src/parser.tab.c"
    break;

  case 236: /* lambda_expression: LSQUARE lambda_capture_clause RSQUARE lambda_declarator compound_statement  */
#line 1986 "src/parser.y"
                                                                                 { 
        dbg("lambda_expression -> [ lambda_capture_clause ] lambda_declarator compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 4561 "src/parser.tab.c"
    break;

  case 237: /* lambda_expression: LSQUARE lambda_capture_clause RSQUARE compound_statement  */
#line 1989 "src/parser.y"
                                                               { 
        dbg("lambda_expression -> [ lambda_capture_clause ] compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 4569 "src/parser.tab.c"
    break;

  case 238: /* lambda_declarator: lambda_parameter_clause trailing_return_opt  */
#line 1995 "src/parser.y"
                                                  { 
        dbg("lambda_declarator -> lambda_parameter_clause trailing_return_opt");
        (yyval.node) = (yyvsp[-1].node); }
#line 4577 "src/parser.tab.c"
    break;

  case 239: /* lambda_parameter_clause: LROUND RROUND  */
#line 2001 "src/parser.y"
                    { 
        dbg("lambda_parameter_clause -> ( )");
        (yyval.node) = new Node(); }
#line 4585 "src/parser.tab.c"
    break;

  case 240: /* lambda_parameter_clause: LROUND parameter_list RROUND  */
#line 2004 "src/parser.y"
                                   {
        dbg("lambda_parameter_clause -> ( parameter_list )");
         (yyval.node) = (yyvsp[-1].node); }
#line 4593 "src/parser.tab.c"
    break;

  case 241: /* trailing_return_opt: %empty  */
#line 2010 "src/parser.y"
       { 
        dbg("trailing_return_opt -> <empty>");
        (yyval.node) = nullptr; }
#line 4601 "src/parser.tab.c"
    break;

  case 242: /* trailing_return_opt: ARROW type_name  */
#line 2013 "src/parser.y"
                      { 
        dbg("trailing_return_opt -> ARROW type_name");
        (yyval.node) = (yyvsp[0].node); }
#line 4609 "src/parser.tab.c"
    break;

  case 243: /* lambda_capture_clause: ASSIGN  */
#line 2019 "src/parser.y"
             { 
        dbg("lambda_capture_clause -> =");
        (yyval.node) = new Node(); }
#line 4617 "src/parser.tab.c"
    break;

  case 244: /* lambda_capture_clause: capture_list  */
#line 2022 "src/parser.y"
                   { 
        dbg("lambda_capture_clause -> capture_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4625 "src/parser.tab.c"
    break;

  case 245: /* lambda_capture_clause: capture_list COMMA ASSIGN  */
#line 2025 "src/parser.y"
                                { 
        dbg("lambda_capture_clause -> capture_list , =");
        (yyval.node) = (yyvsp[-2].node); }
#line 4633 "src/parser.tab.c"
    break;

  case 246: /* lambda_capture_clause: ASSIGN COMMA capture_list  */
#line 2028 "src/parser.y"
                                { 
        dbg("lambda_capture_clause -> = , capture_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4641 "src/parser.tab.c"
    break;

  case 247: /* capture_list: IDENTIFIER  */
#line 2034 "src/parser.y"
                 { 
        dbg("capture_list -> IDENTIFIER");
        Node* n=new Node(); (yyval.node) = n; }
#line 4649 "src/parser.tab.c"
    break;

  case 248: /* capture_list: capture_list COMMA IDENTIFIER  */
#line 2037 "src/parser.y"
                                    {
        dbg("capture_list -> capture_list , IDENTIFIER"); 
        Node* n=(yyvsp[-2].node); (yyval.node) = n; }
#line 4657 "src/parser.tab.c"
    break;


#line 4661 "src/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 2042 "src/parser.y"



#include <cstdio>
#include "parser.tab.h"
extern int yydebug;
void yyerror(const char *s);

int main(int argc, char** argv){
    yydebug = 0;
    pushScope();
    if(yyparse()) cerr << "Parsing failed.\n";
    else cerr << "Parsing completed successfully.\n"; 

    if(!errors.empty()){
        cout<<"---- Errors found ----\n";
        for(auto &e:errors) cout<<e<<"\n";
        return 1;
    }

    if(finalRoot){
        for(int i=0;i<finalRoot->code.size();i++) {
            cout<<"["<<(i+1)<<"] "<<finalRoot->code[i]<<"\n";
        }
    }

    return 0;
}

