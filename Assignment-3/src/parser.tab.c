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
#line 6 "src/parser.y"

    #include <iostream>
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

    bool declareSymbol(const string &name, const string &type, bool isFunc=false, int params=0) {
        if (symStack.empty()) pushScope();
        auto &cur = symStack.back();
        if (cur.find(name) != cur.end()) {
            return false;
        }
        Symbol s; s.name = name; s.type = type; s.isFunction = isFunc; s.paramCount = params; s.isDeclared = true;
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


#line 201 "src/parser.tab.c"

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
  YYSYMBOL_pointer_opt = 105,              /* pointer_opt  */
  YYSYMBOL_new_declarator = 106,           /* new_declarator  */
  YYSYMBOL_scalar_new_init_opt = 107,      /* scalar_new_init_opt  */
  YYSYMBOL_delete_expression = 108,        /* delete_expression  */
  YYSYMBOL_cast_expression = 109,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 110, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 111,      /* additive_expression  */
  YYSYMBOL_shift_expression = 112,         /* shift_expression  */
  YYSYMBOL_relational_expression = 113,    /* relational_expression  */
  YYSYMBOL_equality_expression = 114,      /* equality_expression  */
  YYSYMBOL_and_expression = 115,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 116,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 117,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 118,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 119,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 120,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 121,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 122,      /* assignment_operator  */
  YYSYMBOL_expression = 123,               /* expression  */
  YYSYMBOL_constant_expression = 124,      /* constant_expression  */
  YYSYMBOL_declaration = 125,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 126,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 127,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 128,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 129,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 130,           /* type_specifier  */
  YYSYMBOL_struct_or_class_specifier = 131, /* struct_or_class_specifier  */
  YYSYMBOL_struct_or_class = 132,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 133, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 134,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 135,   /* access_specifier_label  */
  YYSYMBOL_member_declaration = 136,       /* member_declaration  */
  YYSYMBOL_constructor_definition = 137,   /* constructor_definition  */
  YYSYMBOL_destructor_definition = 138,    /* destructor_definition  */
  YYSYMBOL_struct_declarator_list = 139,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 140,        /* struct_declarator  */
  YYSYMBOL_specifier_qualifier_list = 141, /* specifier_qualifier_list  */
  YYSYMBOL_type_qualifier = 142,           /* type_qualifier  */
  YYSYMBOL_declarator = 143,               /* declarator  */
  YYSYMBOL_direct_declarator = 144,        /* direct_declarator  */
  YYSYMBOL_pointer = 145,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 146,      /* type_qualifier_list  */
  YYSYMBOL_parameter_list = 147,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 148,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 149,          /* identifier_list  */
  YYSYMBOL_type_name = 150,                /* type_name  */
  YYSYMBOL_abstract_declarator = 151,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 152, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 153,              /* initializer  */
  YYSYMBOL_initializer_list = 154,         /* initializer_list  */
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
#define YYFINAL  48
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1758

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  256
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  436

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
       0,   211,   211,   226,   229,   232,   238,   243,   248,   253,
     258,   263,   268,   273,   281,   284,   310,   334,   358,   382,
     402,   422,   445,   457,   472,   475,   484,   493,   525,   529,
     533,   536,   542,   545,   548,   551,   554,   557,   563,   571,
     579,   587,   598,   601,   607,   610,   616,   619,   625,   632,
     642,   645,   652,   655,   665,   675,   688,   691,   701,   714,
     717,   726,   738,   741,   748,   755,   762,   772,   775,   782,
     792,   795,   805,   808,   818,   821,   831,   834,   844,   847,
     857,   860,   881,   884,   916,   919,   922,   925,   928,   931,
     934,   937,   940,   943,   946,   952,   955,   966,   972,   977,
     981,   985,   988,   991,   994,   997,  1000,  1006,  1009,  1018,
    1031,  1050,  1056,  1059,  1062,  1065,  1068,  1071,  1074,  1077,
    1083,  1086,  1092,  1095,  1101,  1104,  1112,  1115,  1121,  1124,
    1127,  1133,  1136,  1139,  1142,  1145,  1148,  1151,  1157,  1161,
    1168,  1175,  1178,  1186,  1192,  1195,  1198,  1201,  1207,  1213,
    1216,  1222,  1228,  1231,  1234,  1237,  1240,  1243,  1249,  1252,
    1255,  1258,  1264,  1267,  1273,  1277,  1287,  1298,  1301,  1307,
    1310,  1316,  1319,  1322,  1328,  1331,  1334,  1337,  1340,  1343,
    1346,  1349,  1352,  1358,  1361,  1364,  1370,  1373,  1380,  1383,
    1386,  1389,  1392,  1395,  1398,  1404,  1407,  1413,  1419,  1425,
    1430,  1434,  1443,  1449,  1454,  1463,  1469,  1475,  1484,  1491,
    1501,  1504,  1513,  1516,  1519,  1523,  1526,  1532,  1543,  1557,
    1564,  1577,  1588,  1599,  1615,  1635,  1638,  1644,  1650,  1654,
    1658,  1662,  1674,  1677,  1685,  1690,  1693,  1696,  1699,  1708,
    1732,  1771,  1780,  1785,  1792,  1795,  1801,  1807,  1810,  1816,
    1819,  1825,  1828,  1831,  1834,  1840,  1843
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
  "new_expression", "pointer_opt", "new_declarator", "scalar_new_init_opt",
  "delete_expression", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_class_specifier", "struct_or_class",
  "struct_or_class_member_list", "struct_or_class_member",
  "access_specifier_label", "member_declaration", "constructor_definition",
  "destructor_definition", "struct_declarator_list", "struct_declarator",
  "specifier_qualifier_list", "type_qualifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "io_statement", "cout_expression",
  "insertion_list", "cin_expression", "extraction_list",
  "labeled_statement", "compound_statement", "statement_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "for_init_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_header",
  "function_definition", "return_type", "lambda_expression",
  "lambda_declarator", "lambda_parameter_clause", "trailing_return_opt",
  "lambda_capture_clause", "capture_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-195)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-44)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1003,   227,   623,  -195,  -195,  -195,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,  -195,  -195,    23,   244,   119,    -7,
     -34,   244,   823,  -195,    69,  -195,   -26,  -195,  -195,   108,
      33,    21,    15,  -195,  -195,    53,  -195,   130,     1,    -9,
    -195,   244,   108,  -195,  -195,  -195,    91,  -195,  -195,   227,
    -195,   352,  -195,   126,   158,  -195,  -195,    21,   115,  -195,
      15,   833,    19,   903,     1,  -195,   599,   259,  -195,  -195,
    -195,  1483,  1483,  -195,  -195,   633,  -195,    14,  -195,  -195,
     136,   159,  1553,   161,   198,   723,   209,   181,   208,   237,
     973,   249,  1593,  -195,  -195,  -195,  1663,   623,   283,   302,
     299,  -195,  -195,  -195,  -195,  -195,  -195,  -195,    22,   445,
    1553,  -195,  -195,  -195,    74,   177,   294,   275,   288,   318,
     329,   331,   334,    65,  -195,  -195,   236,  -195,  -195,  -195,
     317,   322,  -195,  -195,   447,  -195,  -195,  -195,  -195,  -195,
    -195,   174,  -195,  -195,  -195,  -195,  -195,   833,  -195,  -195,
    -195,  -195,  -195,    24,  -195,    79,   274,  -195,  -195,  -195,
     325,  -195,   282,   330,   333,   341,   338,   263,   343,  1651,
    -195,  -195,  -195,  -195,  -195,    34,   263,  -195,  1553,  -195,
    -195,    93,    35,   349,   345,  -195,   346,   351,  1553,  1553,
     350,   723,  1553,   342,   542,   355,  -195,  -195,  -195,   279,
    1553,   633,  -195,     5,  -195,   108,  1553,   377,  1013,   382,
     723,  -195,  -195,   339,  1083,  1553,   344,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,  -195,  -195,  -195,  -195,  1553,  -195,
    1553,  1553,  1553,  1553,  1553,  1553,  1553,  1553,  1553,  1553,
    1553,  1553,  1553,  1553,  1553,  1553,  1553,  1553,  1553,  -195,
    1553,  -195,  -195,  -195,  -195,  -195,    95,  -195,    11,  -195,
     623,  -195,   353,  -195,  -195,   392,  -195,  -195,  -195,   207,
    -195,  -195,  -195,  -195,  -195,  -195,   292,  -195,    28,  -195,
    -195,   891,  1153,   135,  -195,   195,  1553,   360,   125,    17,
      96,    98,   723,  -195,   107,   393,   389,  -195,  -195,  1223,
    -195,  -195,   110,   395,  1553,   220,  -195,  1553,  -195,  -195,
    1263,  -195,  -195,  -195,   121,  -195,   105,  -195,  -195,  -195,
    -195,  -195,    74,    74,   177,   177,   294,   294,   294,   294,
     275,   275,   288,   318,   329,   331,   334,   301,  -195,  -195,
    -195,   793,  -195,  -195,   400,    69,   123,  -195,    15,  -195,
    -195,   152,   410,  -195,   407,   195,   314,  1333,  -195,   411,
     530,  -195,    69,   432,  -195,  -195,   723,   723,  -195,   723,
    1553,  1373,   723,  -195,  -195,  1443,  1553,   221,  -195,  -195,
    -195,  -195,  -195,  1553,  -195,  1553,  -195,  -195,    69,  -195,
      69,  -195,  -195,  -195,  -195,  -195,   153,  -195,   417,   373,
    -195,   164,  -195,   263,  -195,   412,  -195,  -195,   166,   723,
     210,  -195,  -195,   211,   218,  1553,  -195,  -195,  -195,  -195,
    -195,  -195,  -195,  -195,  -195,   723,   418,  -195,   723,  -195,
    -195,   262,  -195,  -195,  -195,  -195
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   234,     0,   119,   112,   114,   116,   113,   117,   118,
     115,   111,   148,   123,   122,   237,     0,   101,   103,     0,
       0,   105,     0,   232,     0,   235,     0,   242,   100,    43,
       0,   158,     0,    98,   151,     0,   107,   109,   150,     0,
     102,   103,    43,   243,   104,   236,   121,   106,     1,     0,
     233,     0,   241,     0,     0,   162,   160,   159,     0,    99,
       0,     0,     0,     0,   149,    42,     0,     0,    34,    35,
      33,     0,     0,    32,    37,     0,   208,     0,   215,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    13,    11,     0,     0,     0,     0,
       2,     6,    10,     9,     7,     8,    14,     3,    24,    50,
       0,    31,    30,    52,    56,    59,    62,    67,    70,    72,
      74,    76,    78,    80,    82,    95,     0,   213,   212,   194,
       0,     0,   188,   189,     0,   210,   190,   191,   192,   193,
       5,     0,   238,   163,   161,   152,   108,     0,     2,   183,
     110,   157,   167,     0,   164,     0,     0,   154,    50,    97,
       0,   135,     0,     0,     0,     0,     0,   145,     0,     0,
     124,   126,   127,   136,   137,     0,   147,   214,     0,    25,
      26,     0,   169,     0,   251,   255,     0,   252,     0,     0,
       0,     0,     0,     0,     0,     0,   228,   229,   230,     0,
       0,     0,    28,     0,    49,    43,     0,   202,     0,   197,
       0,    20,    21,     0,     0,     0,     0,    84,    88,    89,
      85,    86,    87,    92,    94,    93,    90,    91,     0,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   216,
       0,   195,   196,   209,   211,   239,     0,   186,     0,   155,
       0,   156,     0,   166,   153,     0,   128,   129,   130,     0,
     144,   134,   120,   125,   132,   143,     0,   141,   109,   146,
       4,     0,     0,   171,   170,   172,     0,     0,     0,     0,
       0,     0,     0,   207,     0,     0,     0,   226,   225,     0,
     227,   231,     0,     0,     0,    41,   203,     0,   199,   198,
       0,   205,    19,    16,     0,    22,     0,    18,    83,    53,
      54,    55,    57,    58,    60,    61,    64,    63,    65,    66,
      68,    69,    71,    73,    75,    77,    79,     0,    96,   240,
     184,     0,   165,   168,     0,     0,     0,   131,     0,   133,
     179,     0,     0,   175,     0,   173,     0,     0,    51,   254,
       0,   245,     0,   249,   253,   256,     0,     0,   206,     0,
       0,     0,     0,    29,    48,     0,     0,    40,    39,   204,
     200,   201,    17,     0,    15,     0,   185,   187,     0,   139,
       0,   142,   180,   174,   176,   181,     0,   177,     0,     0,
     247,     0,   244,     0,   246,   217,   219,   220,     0,     0,
       0,   221,    46,     0,     0,     0,    38,    23,    81,   140,
     138,   182,   178,   248,   250,     0,     0,   223,     0,    47,
      44,     0,   218,   222,   224,    45
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -195,  -195,  -195,  -195,    89,   -15,  -195,  -195,   -33,  -195,
      92,  -195,   -50,   116,   120,    58,   133,   223,   224,   225,
     226,   238,  -195,   -49,   -55,  -195,   -71,   -77,   -38,    84,
    -195,    16,  -195,     0,   -54,  -195,  -195,   315,  -195,  -195,
    -195,  -195,  -195,   139,   -56,   -30,   -17,   452,   -20,  -195,
    -121,   233,  -195,  -194,   190,   212,  -139,  -195,   -82,  -195,
    -195,  -195,  -195,  -195,  -195,   -22,  -195,   362,  -168,  -195,
    -195,  -195,  -195,  -195,   472,  -195,  -195,    50,  -195,  -195,
    -195,  -195,  -195,   213
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   106,   107,   108,   314,   109,   110,   111,    43,   377,
     378,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   228,   126,   160,    15,    16,
      35,   275,    17,    29,    19,    20,   169,   170,   171,   172,
     173,   174,   276,   277,   182,    21,    37,    38,    39,    57,
     153,   154,   155,   183,   284,   285,   150,   258,   128,   129,
     130,   209,   131,   207,   132,   133,   134,   135,   136,   137,
     138,   299,   139,    22,    23,    24,    25,   156,   140,   362,
     363,   404,   186,   187
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      18,    55,    52,   193,   181,   190,   149,   303,   257,    65,
     175,    56,   168,   127,   159,    58,   184,    41,    41,   199,
     256,    41,    18,    31,     3,   184,   298,   143,   364,    31,
      32,    31,    36,   159,   211,   212,   176,   144,    45,    61,
      62,    41,    31,    31,    63,   176,   204,   213,   158,   304,
      26,    41,    30,   340,    32,    46,   179,   180,   341,   151,
     229,   214,    32,    53,   259,   215,   167,   158,    33,    51,
     216,   260,    26,    32,   281,   167,   146,   202,   282,   274,
      34,   158,   230,   231,   232,     4,     5,     6,     7,     8,
       9,    10,   149,   247,   185,   158,   127,   205,    59,    12,
      60,    40,    44,   185,    34,    47,   365,   181,   152,   293,
      51,   270,    34,   175,   248,   168,    42,   290,   291,   261,
     279,   294,    54,    34,     3,    44,   262,    42,   311,   302,
     181,   371,    66,   280,    41,   339,   366,   176,   367,   176,
     250,    61,   260,   250,   316,   250,   176,   369,   346,   384,
     372,   306,   250,   309,   250,   145,   297,   250,   278,   315,
     351,   382,   283,   390,   360,   141,    51,   167,   383,   167,
     260,   176,   305,   318,   281,   188,   167,   337,   282,     3,
     319,   320,   321,   233,   234,     4,     5,     6,     7,     8,
       9,    10,   392,   421,    41,   338,    11,    12,   189,   260,
     260,   167,   387,   142,   423,   354,   426,   191,   -43,   424,
     368,   260,     3,   250,   255,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   159,   356,   396,   358,   192,   357,   401,
       4,     5,     6,     7,     8,     9,    10,   345,   194,     3,
     428,   429,   379,   196,   374,   381,   349,   250,   383,   375,
     375,   283,   430,   376,   415,   250,   361,   158,     3,    27,
     195,   158,    28,     4,     5,     6,     7,     8,     9,    10,
     398,   249,   197,   250,   405,   406,   149,   407,   200,   158,
     411,   237,   238,   239,   240,   326,   327,   328,   329,   408,
     410,   177,   241,   242,    28,   414,   435,   206,   159,   250,
       4,     5,     6,     7,     8,     9,    10,   235,   236,     3,
     315,    11,    12,   389,   301,   208,   250,   427,   417,     4,
       5,     6,     7,     8,     9,    10,   418,   347,   243,   348,
     402,    12,   158,   432,   431,   210,   434,   385,   250,   322,
     323,   244,   245,    67,   395,   324,   325,     3,    68,    69,
      70,   246,   251,   263,    71,    72,   419,   252,   420,   264,
     158,   265,    73,   176,   330,   331,   266,   269,    74,   267,
       4,     5,     6,     7,     8,     9,    10,   268,   271,   286,
     288,    75,   287,    51,    76,    77,   292,    78,   289,   295,
     300,   307,    79,   167,    80,   310,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,     4,     5,
       6,     7,     8,     9,    10,    93,    94,    95,   312,    11,
      12,   344,   370,   317,    28,   373,    96,    97,    98,    99,
     388,   100,   343,   101,   102,   103,   104,   105,    67,   185,
     393,   394,     3,    68,    69,    70,   217,   403,   399,    71,
      72,   422,   365,   433,   413,   425,   332,    73,   333,   416,
     334,   352,   335,    74,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   273,   336,    75,   391,    51,   253,
      77,    64,    78,   342,    50,   355,   254,    79,     0,    80,
     359,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,     4,     5,     6,     7,     8,     9,    10,
      93,    94,    95,     0,    11,    12,     0,     0,     0,     0,
       0,    96,    97,    98,    99,     3,   100,     0,   101,   102,
     103,   104,   105,   296,     0,     0,     0,     3,    68,    69,
      70,     0,     0,     0,    71,    72,     0,     0,     0,     0,
       0,     0,    73,     0,     0,     0,     0,     0,    74,     0,
     400,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    75,     0,     0,     0,    77,     0,    78,     0,     0,
       0,     0,    79,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,     0,     3,     0,     0,    92,     4,     5,
       6,     7,     8,     9,    10,    93,    94,    95,     0,    11,
      12,     0,     0,     0,     0,     0,    96,    97,     3,     0,
       0,   148,     0,   101,   102,   103,   104,   105,     3,    68,
      69,    70,     0,     0,   161,    71,    72,     0,     0,   162,
       0,     0,     0,    73,     0,     0,     0,     0,     0,    74,
       0,     0,     0,     0,     0,     4,     5,     6,     7,     8,
       9,    10,    75,     0,     0,     0,    77,    12,    13,    14,
     163,   164,   165,    79,     0,     0,     0,     0,   166,     4,
       5,     6,     7,     8,     9,    10,     0,     0,    92,     4,
       5,     6,     7,     8,     9,    10,    93,    94,    95,     0,
       0,    12,     0,     0,     0,     0,     0,    96,    97,     0,
       0,     0,   148,     0,   101,   102,   103,   104,   105,    68,
      69,    70,     0,     0,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,     0,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,    51,     0,    77,     0,    78,     0,
       0,     0,     0,    79,     0,    80,     0,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,    98,
      99,     0,   100,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,    48,    49,     0,     0,     2,     3,     0,
       0,     0,    75,     0,   147,   386,    77,     0,     0,    68,
      69,    70,     0,    79,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,    92,    74,
       0,     0,     0,     0,     0,     0,    93,    94,    95,     0,
       0,     0,    75,     0,   147,     0,    77,    96,    97,     0,
       0,     0,   148,    79,   101,   102,   103,   104,   105,     4,
       5,     6,     7,     8,     9,    10,     3,     0,    92,    31,
      11,    12,    13,    14,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,     0,   148,    73,   101,   102,   103,   104,   105,    74,
     281,   350,     0,     0,   282,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,    77,   157,     0,     0,
       0,     0,     0,    79,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,     0,   148,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,     0,     1,     0,     0,     2,     3,     0,
       0,     0,    75,     0,     0,     0,    77,     0,   198,    68,
      69,    70,     0,    79,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,    92,    74,
       0,     0,     0,     0,     0,     0,    93,    94,    95,     0,
       0,     0,    75,     0,     0,     0,    77,    96,    97,     0,
       0,     0,   148,    79,   101,   102,   103,   104,   105,     4,
       5,     6,     7,     8,     9,    10,     0,     0,    92,     0,
      11,    12,    13,    14,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,   308,   148,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,   313,     0,     0,    77,     0,     0,     0,
       0,     0,     0,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,     0,   148,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,    77,   353,     0,     0,
       0,     0,     0,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,     0,   148,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,    77,     0,    78,    68,
      69,    70,     0,    79,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,    92,    74,
       0,     0,     0,     0,     0,     0,    93,    94,    95,     0,
       0,     0,    75,     0,     0,     0,    77,    96,    97,     0,
       0,     0,   148,    79,   101,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,   380,   148,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,    77,   397,     0,    68,
      69,    70,     0,    79,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,    92,    74,
       0,     0,     0,     0,     0,     0,    93,    94,    95,     0,
       0,     0,    75,   409,     0,     0,    77,    96,    97,     0,
       0,     0,   148,    79,   101,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,     0,   148,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,   412,     0,     0,    77,     0,     0,    68,
      69,    70,     0,    79,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,    92,    74,
       0,     0,     0,     0,     0,     0,    93,    94,    95,     0,
       0,     0,   178,     0,     0,     0,    77,    96,    97,     0,
       0,     0,   148,    79,   101,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,     0,   148,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,    77,     0,     0,    68,
      69,    70,     0,    79,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,    92,    74,
       0,     0,     0,     0,     0,     0,    93,    94,    95,     0,
       0,     0,   201,     0,     0,     0,    77,    96,    97,     0,
       0,     0,   148,    79,   101,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     3,     0,    92,     0,
       0,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      69,    70,     0,     0,     0,    71,    72,    96,    97,     0,
       0,     0,   148,    73,   101,   102,   103,   104,   105,    74,
       0,     0,     0,   272,     0,     0,   161,     0,     0,     0,
       0,   162,    75,     0,     0,     0,   203,     0,     0,     0,
       0,     0,     0,    79,     0,     0,     0,     4,     5,     6,
       7,     8,     9,    10,     0,     0,     0,     0,    92,    12,
      13,    14,   163,   164,   165,     0,    93,    94,    95,     0,
     166,     0,     0,     0,     0,     0,     0,    96,    97,     0,
       0,     0,   148,     0,   101,   102,   103,   104,   105
};

static const yytype_int16 yycheck[] =
{
       0,    31,    24,    85,    75,    82,    61,   201,   147,    42,
      66,    31,    66,    51,    63,    32,    11,    17,    18,    90,
     141,    21,    22,     8,     5,    11,   194,    57,    11,     8,
      39,     8,    16,    82,    12,    13,    66,    57,    45,    11,
      39,    41,     8,     8,    43,    75,    96,    25,    63,    44,
       0,    51,     2,    42,    39,    89,    71,    72,    47,    40,
     110,    39,    39,    89,    40,    43,    66,    82,    45,    41,
      48,    47,    22,    39,    39,    75,    60,    92,    43,    45,
      89,    96,     8,     9,    10,    66,    67,    68,    69,    70,
      71,    72,   147,    28,    89,   110,   134,    97,    45,    78,
      47,    17,    18,    89,    89,    21,    89,   178,    89,   191,
      41,   167,    89,   169,    49,   169,     8,   188,   189,    40,
     176,   192,    89,    89,     5,    41,    47,     8,   210,   200,
     201,   299,    41,    40,   134,    40,    40,   167,    40,   169,
      47,    11,    47,    47,   215,    47,   176,    40,   269,    44,
      40,   206,    47,   208,    47,    40,   194,    47,   175,   214,
     281,    40,   182,    40,    39,    39,    41,   167,    47,   169,
      47,   201,   205,   228,    39,    39,   176,   248,    43,     5,
     230,   231,   232,     6,     7,    66,    67,    68,    69,    70,
      71,    72,    40,    40,   194,   250,    77,    78,    39,    47,
      47,   201,   341,    45,    40,   282,    40,    46,    89,   403,
     292,    47,     5,    47,    40,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   282,    39,   356,   286,    39,    43,   360,
      66,    67,    68,    69,    70,    71,    72,    40,    39,     5,
      40,    40,   307,    45,   304,   310,   278,    47,    47,    39,
      39,   281,    44,    43,    43,    47,   288,   282,     5,    42,
      89,   286,    45,    66,    67,    68,    69,    70,    71,    72,
     357,    45,    45,    47,   366,   367,   341,   369,    39,   304,
     372,    16,    17,    18,    19,   237,   238,   239,   240,   370,
     371,    42,    14,    15,    45,   376,    44,    24,   357,    47,
      66,    67,    68,    69,    70,    71,    72,    23,    24,     5,
     375,    77,    78,   345,    45,    23,    47,   409,   383,    66,
      67,    68,    69,    70,    71,    72,   385,    45,    20,    47,
     362,    78,   357,   425,   415,    46,   428,    46,    47,   233,
     234,    22,    21,     1,    40,   235,   236,     5,     6,     7,
       8,    27,    45,    89,    12,    13,   388,    45,   390,    44,
     385,    89,    20,   403,   241,   242,    46,    39,    26,    46,
      66,    67,    68,    69,    70,    71,    72,    46,    45,    40,
      44,    39,    47,    41,    42,    43,    46,    45,    47,    57,
      45,    24,    50,   403,    52,    23,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    89,    77,
      78,    39,    39,    89,    45,    40,    84,    85,    86,    87,
      40,    89,    89,    91,    92,    93,    94,    95,     1,    89,
      40,    44,     5,     6,     7,     8,    11,    25,    47,    12,
      13,    44,    89,    45,   375,    53,   243,    20,   244,   377,
     245,   281,   246,    26,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   169,   247,    39,   348,    41,    42,
      43,    39,    45,   260,    22,   283,   134,    50,    -1,    52,
     287,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    -1,    77,    78,    -1,    -1,    -1,    -1,
      -1,    84,    85,    86,    87,     5,    89,    -1,    91,    92,
      93,    94,    95,     1,    -1,    -1,    -1,     5,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    -1,     5,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    77,
      78,    -1,    -1,    -1,    -1,    -1,    84,    85,     5,    -1,
      -1,    89,    -1,    91,    92,    93,    94,    95,     5,     6,
       7,     8,    -1,    -1,    45,    12,    13,    -1,    -1,    50,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    39,    -1,    -1,    -1,    43,    78,    79,    80,
      81,    82,    83,    50,    -1,    -1,    -1,    -1,    89,    66,
      67,    68,    69,    70,    71,    72,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    -1,
      -1,    78,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    89,    -1,    91,    92,    93,    94,    95,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    41,    -1,    43,    -1,    45,    -1,
      -1,    -1,    -1,    50,    -1,    52,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    86,
      87,    -1,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,     0,     1,    -1,    -1,     4,     5,    -1,
      -1,    -1,    39,    -1,    41,    42,    43,    -1,    -1,     6,
       7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,
      -1,    -1,    39,    -1,    41,    -1,    43,    84,    85,    -1,
      -1,    -1,    89,    50,    91,    92,    93,    94,    95,    66,
      67,    68,    69,    70,    71,    72,     5,    -1,    65,     8,
      77,    78,    79,    80,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    -1,    89,    20,    91,    92,    93,    94,    95,    26,
      39,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    -1,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,    -1,     1,    -1,    -1,     4,     5,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    45,     6,
       7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    84,    85,    -1,
      -1,    -1,    89,    50,    91,    92,    93,    94,    95,    66,
      67,    68,    69,    70,    71,    72,    -1,    -1,    65,    -1,
      77,    78,    79,    80,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    88,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    -1,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    44,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    -1,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    45,     6,
       7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    84,    85,    -1,
      -1,    -1,    89,    50,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    88,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    44,    -1,     6,
       7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,
      -1,    -1,    39,    40,    -1,    -1,    43,    84,    85,    -1,
      -1,    -1,    89,    50,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    -1,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,     6,
       7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    84,    85,    -1,
      -1,    -1,    89,    50,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    -1,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    -1,     6,
       7,     8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    84,    85,    -1,
      -1,    -1,    89,    50,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,
      -1,    -1,    89,    20,    91,    92,    93,    94,    95,    26,
      -1,    -1,    -1,    42,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    50,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    65,    78,
      79,    80,    81,    82,    83,    -1,    73,    74,    75,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,
      -1,    -1,    89,    -1,    91,    92,    93,    94,    95
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     5,    66,    67,    68,    69,    70,    71,
      72,    77,    78,    79,    80,   125,   126,   129,   130,   131,
     132,   142,   170,   171,   172,   173,   174,    42,    45,   130,
     174,     8,    39,    45,    89,   127,   128,   143,   144,   145,
     126,   130,     8,   105,   126,    45,    89,   126,     0,     1,
     171,    41,   162,    89,    89,   142,   145,   146,   143,    45,
      47,    11,    39,    43,   144,   105,    41,     1,     6,     7,
       8,    12,    13,    20,    26,    39,    42,    43,    45,    50,
      52,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    73,    74,    75,    84,    85,    86,    87,
      89,    91,    92,    93,    94,    95,    98,    99,   100,   102,
     103,   104,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   123,   125,   155,   156,
     157,   159,   161,   162,   163,   164,   165,   166,   167,   169,
     175,    39,    45,   142,   145,    40,   128,    41,    89,   121,
     153,    40,    89,   147,   148,   149,   174,    44,   102,   120,
     124,    45,    50,    81,    82,    83,    89,   130,   131,   133,
     134,   135,   136,   137,   138,   141,   142,    42,    39,   102,
     102,   123,   141,   150,    11,    89,   179,   180,    39,    39,
     124,    46,    39,   155,    39,    89,    45,    45,    45,   123,
      39,    39,   102,    43,   109,   130,    24,   160,    23,   158,
      46,    12,    13,    25,    39,    43,    48,    11,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   122,   109,
       8,     9,    10,     6,     7,    23,    24,    16,    17,    18,
      19,    14,    15,    20,    22,    21,    27,    28,    49,    45,
      47,    45,    45,    42,   164,    40,   147,   153,   154,    40,
      47,    40,    47,    89,    44,    89,    46,    46,    46,    39,
     141,    45,    42,   134,    45,   128,   139,   140,   143,   141,
      40,    39,    43,   145,   151,   152,    40,    47,    44,    47,
     123,   123,    46,   155,   123,    57,     1,   125,   165,   168,
      45,    45,   123,   150,    44,   105,   121,    24,    88,   121,
      23,   155,    89,    40,   101,   121,   123,    89,   121,   109,
     109,   109,   110,   110,   111,   111,   112,   112,   112,   112,
     113,   113,   114,   115,   116,   117,   118,   123,   121,    40,
      42,    47,   148,    89,    39,    40,   147,    45,    47,   162,
      40,   147,   151,    44,   124,   152,    39,    43,   109,   180,
      39,   162,   176,   177,    11,    89,    40,    40,   155,    40,
      39,   165,    40,    40,   109,    39,    43,   106,   107,   121,
      88,   121,    40,    47,    44,    46,    42,   153,    40,   162,
      40,   140,    40,    40,    44,    40,   147,    44,   124,    47,
      40,   147,   162,    25,   178,   155,   155,   155,   123,    40,
     123,   155,    40,   101,   123,    43,   107,   121,   120,   162,
     162,    40,    44,    40,   150,    53,    40,   155,    40,    40,
      44,   123,   155,    45,   155,    44
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    98,    98,    98,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   104,   104,
     104,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   110,   110,   111,   111,   111,   112,
     112,   112,   113,   113,   113,   113,   113,   114,   114,   114,
     115,   115,   116,   116,   117,   117,   118,   118,   119,   119,
     120,   120,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   124,   125,   125,
     125,   126,   126,   126,   126,   126,   126,   127,   127,   128,
     128,   129,   130,   130,   130,   130,   130,   130,   130,   130,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     135,   136,   136,   136,   136,   136,   136,   136,   137,   137,
     138,   139,   139,   140,   141,   141,   141,   141,   142,   143,
     143,   144,   144,   144,   144,   144,   144,   144,   145,   145,
     145,   145,   146,   146,   147,   147,   148,   149,   149,   150,
     150,   151,   151,   151,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   153,   153,   153,   154,   154,   155,   155,
     155,   155,   155,   155,   155,   156,   156,   157,   158,   158,
     158,   158,   159,   160,   160,   161,   161,   161,   162,   162,
     163,   163,   164,   164,   164,   165,   165,   166,   166,   166,
     167,   167,   167,   167,   167,   168,   168,   169,   169,   169,
     169,   169,   170,   170,   170,   171,   171,   171,   171,   172,
     172,   173,   173,   174,   175,   175,   176,   177,   177,   178,
     178,   179,   179,   179,   179,   180,   180
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       4,     3,     2,     0,     3,     4,     2,     3,     4,     2,
       1,     4,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     5,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     2,     3,
       2,     1,     2,     1,     2,     1,     2,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     2,     1,     1,     1,     2,     1,     1,     2,     2,
       2,     3,     2,     3,     2,     1,     1,     1,     5,     4,
       5,     1,     3,     1,     2,     1,     2,     1,     1,     2,
       1,     1,     3,     4,     3,     4,     4,     3,     1,     2,
       2,     3,     1,     2,     1,     3,     2,     1,     3,     1,
       2,     1,     1,     2,     3,     2,     3,     3,     4,     2,
       3,     3,     4,     1,     3,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       3,     3,     2,     2,     3,     3,     4,     3,     2,     3,
       1,     2,     1,     1,     2,     1,     2,     5,     7,     5,
       5,     5,     7,     6,     7,     1,     1,     3,     2,     2,
       2,     3,     1,     2,     1,     1,     2,     1,     4,     4,
       5,     2,     2,     2,     5,     4,     2,     2,     3,     0,
       2,     1,     1,     3,     3,     1,     3
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
#line 211 "src/parser.y"
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
#line 1991 "src/parser.tab.c"
    break;

  case 3: /* primary_expression: constant  */
#line 226 "src/parser.y"
                   { 
        dbg("primary_expression -> constant");
        (yyval.node) = (yyvsp[0].node); }
#line 1999 "src/parser.tab.c"
    break;

  case 4: /* primary_expression: LROUND expression RROUND  */
#line 229 "src/parser.y"
                                   { 
        dbg("primary_expression -> ( expression )");
        (yyval.node) = (yyvsp[-1].node); }
#line 2007 "src/parser.tab.c"
    break;

  case 5: /* primary_expression: lambda_expression  */
#line 232 "src/parser.y"
                        { 
        dbg("primary_expression -> lambda_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2015 "src/parser.tab.c"
    break;

  case 6: /* constant: DECIMAL_LITERAL  */
#line 238 "src/parser.y"
                            {
          dbg("constant -> DECIMAL_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "int", "constant");
          (yyval.node) = n;
      }
#line 2025 "src/parser.tab.c"
    break;

  case 7: /* constant: CHARACTER_LITERAL  */
#line 243 "src/parser.y"
                            {
            dbg("constant -> CHARACTER_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "char", "constant");
          (yyval.node) = n;
      }
#line 2035 "src/parser.tab.c"
    break;

  case 8: /* constant: STRING_LITERAL  */
#line 248 "src/parser.y"
                            {
            dbg("constant -> STRING_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "string", "constant");
          (yyval.node) = n;
      }
#line 2045 "src/parser.tab.c"
    break;

  case 9: /* constant: EXPONENT_LITERAL  */
#line 253 "src/parser.y"
                            {
            dbg("constant -> EXPONENT_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "double", "constant");
          (yyval.node) = n;
      }
#line 2055 "src/parser.tab.c"
    break;

  case 10: /* constant: DOUBLE_LITERAL  */
#line 258 "src/parser.y"
                            {
            dbg("constant -> DOUBLE_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "double", "constant");
          (yyval.node) = n;
      }
#line 2065 "src/parser.tab.c"
    break;

  case 11: /* constant: NULLPTR  */
#line 263 "src/parser.y"
                            {
            dbg("constant -> NULLPTR");
          Node* n = new Node("0", "nullptr", "constant");
          (yyval.node) = n;
      }
#line 2075 "src/parser.tab.c"
    break;

  case 12: /* constant: TRUE  */
#line 268 "src/parser.y"
                            {
            dbg("constant -> TRUE");
          Node* n = new Node("1", "bool", "constant");
          (yyval.node) = n;
      }
#line 2085 "src/parser.tab.c"
    break;

  case 13: /* constant: FALSE  */
#line 273 "src/parser.y"
                            {
            dbg("constant -> FALSE");
          Node* n = new Node("0", "bool", "constant");
          (yyval.node) = n;
      }
#line 2095 "src/parser.tab.c"
    break;

  case 14: /* postfix_expression: primary_expression  */
#line 281 "src/parser.y"
                             { 
        dbg("postfix_expression -> primary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2103 "src/parser.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression LSQUARE expression RSQUARE  */
#line 284 "src/parser.y"
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
#line 2134 "src/parser.tab.c"
    break;

  case 16: /* postfix_expression: postfix_expression LROUND RROUND  */
#line 310 "src/parser.y"
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
#line 2163 "src/parser.tab.c"
    break;

  case 17: /* postfix_expression: postfix_expression LROUND argument_expression_list RROUND  */
#line 334 "src/parser.y"
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
#line 2192 "src/parser.tab.c"
    break;

  case 18: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 358 "src/parser.y"
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
#line 2221 "src/parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 382 "src/parser.y"
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
#line 2246 "src/parser.tab.c"
    break;

  case 20: /* postfix_expression: postfix_expression INCREMENT  */
#line 402 "src/parser.y"
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
#line 2271 "src/parser.tab.c"
    break;

  case 21: /* postfix_expression: postfix_expression DECREMENT  */
#line 422 "src/parser.y"
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
#line 2296 "src/parser.tab.c"
    break;

  case 22: /* argument_expression_list: assignment_expression  */
#line 445 "src/parser.y"
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
#line 2313 "src/parser.tab.c"
    break;

  case 23: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 457 "src/parser.y"
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
#line 2330 "src/parser.tab.c"
    break;

  case 24: /* unary_expression: postfix_expression  */
#line 472 "src/parser.y"
                             { 
        dbg("unary_expression -> postfix_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2338 "src/parser.tab.c"
    break;

  case 25: /* unary_expression: INCREMENT unary_expression  */
#line 475 "src/parser.y"
                                     {
          dbg("unary_expression -> ++ unary_expression");
          Node* v = (yyvsp[0].node);
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " + 1;");
          (yyval.node) = n;
      }
#line 2352 "src/parser.tab.c"
    break;

  case 26: /* unary_expression: DECREMENT unary_expression  */
#line 484 "src/parser.y"
                                     {
            dbg("unary_expression -> -- unary_expression");
          Node* v = (yyvsp[0].node);
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " - 1;");
          (yyval.node) = n;
      }
#line 2366 "src/parser.tab.c"
    break;

  case 27: /* unary_expression: unary_operator cast_expression  */
#line 493 "src/parser.y"
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
#line 2403 "src/parser.tab.c"
    break;

  case 28: /* unary_expression: SIZEOF unary_expression  */
#line 525 "src/parser.y"
                                  {
          dbg("unary_expression -> sizeof unary_expression");
          Node* n = new Node(); n->place = "sizeof"; (yyval.node) = n;
      }
#line 2412 "src/parser.tab.c"
    break;

  case 29: /* unary_expression: SIZEOF LROUND type_name RROUND  */
#line 529 "src/parser.y"
                                         {
            dbg("unary_expression -> sizeof ( type_name )");
          Node* n = new Node(); n->place = "sizeof"; (yyval.node) = n;
      }
#line 2421 "src/parser.tab.c"
    break;

  case 30: /* unary_expression: delete_expression  */
#line 533 "src/parser.y"
                            { 
        dbg("unary_expression -> delete_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2429 "src/parser.tab.c"
    break;

  case 31: /* unary_expression: new_expression  */
#line 536 "src/parser.y"
                         { 
        dbg("unary_expression -> new_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2437 "src/parser.tab.c"
    break;

  case 32: /* unary_operator: BITWISE_AND  */
#line 542 "src/parser.y"
                      { 
        dbg("unary_operator -> &");
        (yyval.str) = (yyvsp[0].str); }
#line 2445 "src/parser.tab.c"
    break;

  case 33: /* unary_operator: STAR  */
#line 545 "src/parser.y"
               { 
        dbg("unary_operator -> *");
        (yyval.str) = (yyvsp[0].str); }
#line 2453 "src/parser.tab.c"
    break;

  case 34: /* unary_operator: PLUS  */
#line 548 "src/parser.y"
               { 
        dbg("unary_operator -> +");
        (yyval.str) = (yyvsp[0].str); }
#line 2461 "src/parser.tab.c"
    break;

  case 35: /* unary_operator: MINUS  */
#line 551 "src/parser.y"
                { 
        dbg("unary_operator -> -");
        (yyval.str) = (yyvsp[0].str); }
#line 2469 "src/parser.tab.c"
    break;

  case 36: /* unary_operator: TILDE  */
#line 554 "src/parser.y"
                { 
        dbg("unary_operator -> ~");
        (yyval.str) = (yyvsp[0].str); }
#line 2477 "src/parser.tab.c"
    break;

  case 37: /* unary_operator: LOGICAL_NOT  */
#line 557 "src/parser.y"
                      { 
        dbg("unary_operator -> !");
        (yyval.str) = (yyvsp[0].str); }
#line 2485 "src/parser.tab.c"
    break;

  case 38: /* new_expression: NEW type_specifier pointer_opt new_declarator scalar_new_init_opt  */
#line 563 "src/parser.y"
                                                                            {
          dbg("new_expression -> NEW type_specifier pointer_opt new_declarator scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2498 "src/parser.tab.c"
    break;

  case 39: /* new_expression: NEW type_specifier pointer_opt scalar_new_init_opt  */
#line 571 "src/parser.y"
                                                             {
            dbg("new_expression -> NEW type_specifier pointer_opt scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2511 "src/parser.tab.c"
    break;

  case 40: /* new_expression: NEW type_specifier pointer_opt new_declarator  */
#line 579 "src/parser.y"
                                                        {
            dbg("new_expression -> NEW type_specifier pointer_opt new_declarator");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2524 "src/parser.tab.c"
    break;

  case 41: /* new_expression: NEW type_specifier pointer_opt  */
#line 587 "src/parser.y"
                                         {
            dbg("new_expression -> NEW type_specifier pointer_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2537 "src/parser.tab.c"
    break;

  case 42: /* pointer_opt: STAR pointer_opt  */
#line 598 "src/parser.y"
                           { 
        dbg("pointer_opt -> * pointer_opt");
        (yyval.str) = strcat(strdup("*"), (yyvsp[0].str)); }
#line 2545 "src/parser.tab.c"
    break;

  case 43: /* pointer_opt: %empty  */
#line 601 "src/parser.y"
           { 
        dbg("pointer_opt -> <empty>");
        (yyval.str) = strdup(""); }
#line 2553 "src/parser.tab.c"
    break;

  case 44: /* new_declarator: LSQUARE expression RSQUARE  */
#line 607 "src/parser.y"
                                     { 
        dbg("new_declarator -> [ expression ]");
        (yyval.node) = (yyvsp[-1].node); }
#line 2561 "src/parser.tab.c"
    break;

  case 45: /* new_declarator: new_declarator LSQUARE expression RSQUARE  */
#line 610 "src/parser.y"
                                                    { 
        dbg("new_declarator -> new_declarator [ expression ]");
        (yyval.node) = (yyvsp[-1].node); }
#line 2569 "src/parser.tab.c"
    break;

  case 46: /* scalar_new_init_opt: LROUND RROUND  */
#line 616 "src/parser.y"
                        { 
        dbg("scalar_new_init_opt -> ( )");
        (yyval.node) = nullptr; }
#line 2577 "src/parser.tab.c"
    break;

  case 47: /* scalar_new_init_opt: LROUND argument_expression_list RROUND  */
#line 619 "src/parser.y"
                                                 { 
        dbg("scalar_new_init_opt -> ( argument_expression_list )");
        (yyval.node) = (yyvsp[-1].node); }
#line 2585 "src/parser.tab.c"
    break;

  case 48: /* delete_expression: DELETE LSQUARE RSQUARE cast_expression  */
#line 625 "src/parser.y"
                                                 {
          dbg("delete_expression -> DELETE [ ] cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("free " + (yyvsp[0].node)->place + ";");
          (yyval.node) = n;
      }
#line 2597 "src/parser.tab.c"
    break;

  case 49: /* delete_expression: DELETE cast_expression  */
#line 632 "src/parser.y"
                                 {
            dbg("delete_expression -> DELETE cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("free " + (yyvsp[0].node)->place + ";");
          (yyval.node) = n;
      }
#line 2609 "src/parser.tab.c"
    break;

  case 50: /* cast_expression: unary_expression  */
#line 642 "src/parser.y"
                           { 
        dbg("cast_expression -> unary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2617 "src/parser.tab.c"
    break;

  case 51: /* cast_expression: LROUND type_name RROUND cast_expression  */
#line 645 "src/parser.y"
                                                  {
            dbg("cast_expression -> ( type_name ) cast_expression");
          (yyval.node) = (yyvsp[0].node);
      }
#line 2626 "src/parser.tab.c"
    break;

  case 52: /* multiplicative_expression: cast_expression  */
#line 652 "src/parser.y"
                          { 
        dbg("multiplicative_expression -> cast_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2634 "src/parser.tab.c"
    break;

  case 53: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 655 "src/parser.y"
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
#line 2649 "src/parser.tab.c"
    break;

  case 54: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 665 "src/parser.y"
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
#line 2664 "src/parser.tab.c"
    break;

  case 55: /* multiplicative_expression: multiplicative_expression MODULUS cast_expression  */
#line 675 "src/parser.y"
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
#line 2679 "src/parser.tab.c"
    break;

  case 56: /* additive_expression: multiplicative_expression  */
#line 688 "src/parser.y"
                                    { 
        dbg("additive_expression -> multiplicative_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2687 "src/parser.tab.c"
    break;

  case 57: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 691 "src/parser.y"
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
#line 2702 "src/parser.tab.c"
    break;

  case 58: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 701 "src/parser.y"
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
#line 2717 "src/parser.tab.c"
    break;

  case 59: /* shift_expression: additive_expression  */
#line 714 "src/parser.y"
                              { 
        dbg("shift_expression -> additive_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2725 "src/parser.tab.c"
    break;

  case 60: /* shift_expression: shift_expression LEFT_SHIFT additive_expression  */
#line 717 "src/parser.y"
                                                          {
            dbg("shift_expression -> shift_expression << additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " << " + b->place + ";");
          n->type = a->type; (yyval.node) = n;
      }
#line 2739 "src/parser.tab.c"
    break;

  case 61: /* shift_expression: shift_expression RIGHT_SHIFT additive_expression  */
#line 726 "src/parser.y"
                                                           {
            dbg("shift_expression -> shift_expression >> additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " >> " + b->place + ";");
          n->type = a->type; (yyval.node) = n;
      }
#line 2753 "src/parser.tab.c"
    break;

  case 62: /* relational_expression: shift_expression  */
#line 738 "src/parser.y"
                           { 
        dbg("relational_expression -> shift_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2761 "src/parser.tab.c"
    break;

  case 63: /* relational_expression: relational_expression GREATER_THAN shift_expression  */
#line 741 "src/parser.y"
                                                              {
          dbg("relational_expression -> relational_expression > shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " > " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2773 "src/parser.tab.c"
    break;

  case 64: /* relational_expression: relational_expression LESS_THAN shift_expression  */
#line 748 "src/parser.y"
                                                           {
          dbg("relational_expression -> relational_expression < shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " < " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2785 "src/parser.tab.c"
    break;

  case 65: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 755 "src/parser.y"
                                                            {
            dbg("relational_expression -> relational_expression <= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " <= " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2797 "src/parser.tab.c"
    break;

  case 66: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 762 "src/parser.y"
                                                               {
            dbg("relational_expression -> relational_expression >= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " >= " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2809 "src/parser.tab.c"
    break;

  case 67: /* equality_expression: relational_expression  */
#line 772 "src/parser.y"
                                { 
        dbg("equality_expression -> relational_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2817 "src/parser.tab.c"
    break;

  case 68: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 775 "src/parser.y"
                                                          {
            dbg("equality_expression -> equality_expression == relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " == " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2829 "src/parser.tab.c"
    break;

  case 69: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 782 "src/parser.y"
                                                              {
            dbg("equality_expression -> equality_expression != relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " != " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2841 "src/parser.tab.c"
    break;

  case 70: /* and_expression: equality_expression  */
#line 792 "src/parser.y"
                              { 
        dbg("and_expression -> equality_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2849 "src/parser.tab.c"
    break;

  case 71: /* and_expression: and_expression BITWISE_AND equality_expression  */
#line 795 "src/parser.y"
                                                         {
            dbg("and_expression -> and_expression & equality_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " & " + b->place + ";");
          (yyval.node) = n;
      }
#line 2861 "src/parser.tab.c"
    break;

  case 72: /* exclusive_or_expression: and_expression  */
#line 805 "src/parser.y"
                         { 
        dbg("exclusive_or_expression -> and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2869 "src/parser.tab.c"
    break;

  case 73: /* exclusive_or_expression: exclusive_or_expression BITWISE_XOR and_expression  */
#line 808 "src/parser.y"
                                                             {
            dbg("exclusive_or_expression -> exclusive_or_expression ^ and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " ^ " + b->place + ";");
          (yyval.node) = n;
      }
#line 2881 "src/parser.tab.c"
    break;

  case 74: /* inclusive_or_expression: exclusive_or_expression  */
#line 818 "src/parser.y"
                                  { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2889 "src/parser.tab.c"
    break;

  case 75: /* inclusive_or_expression: inclusive_or_expression BITWISE_OR exclusive_or_expression  */
#line 821 "src/parser.y"
                                                                     {
            dbg("inclusive_or_expression -> inclusive_or_expression | exclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " | " + b->place + ";");
          (yyval.node) = n;
      }
#line 2901 "src/parser.tab.c"
    break;

  case 76: /* logical_and_expression: inclusive_or_expression  */
#line 831 "src/parser.y"
                                  { 
        dbg("logical_and_expression -> inclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2909 "src/parser.tab.c"
    break;

  case 77: /* logical_and_expression: logical_and_expression LOGICAL_AND inclusive_or_expression  */
#line 834 "src/parser.y"
                                                                     {
            dbg("logical_and_expression -> logical_and_expression && inclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " && " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2921 "src/parser.tab.c"
    break;

  case 78: /* logical_or_expression: logical_and_expression  */
#line 844 "src/parser.y"
                                 { 
        dbg("logical_or_expression -> logical_and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2929 "src/parser.tab.c"
    break;

  case 79: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 847 "src/parser.y"
                                                                  {
            dbg("logical_or_expression -> logical_or_expression || logical_and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " || " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2941 "src/parser.tab.c"
    break;

  case 80: /* conditional_expression: logical_or_expression  */
#line 857 "src/parser.y"
                                { 
        dbg("conditional_expression -> logical_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2949 "src/parser.tab.c"
    break;

  case 81: /* conditional_expression: logical_or_expression QUESTION_MARK expression COLON conditional_expression  */
#line 860 "src/parser.y"
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
#line 2972 "src/parser.tab.c"
    break;

  case 82: /* assignment_expression: conditional_expression  */
#line 881 "src/parser.y"
                                 { 
        dbg("assignment_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2980 "src/parser.tab.c"
    break;

  case 83: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 884 "src/parser.y"
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
#line 3014 "src/parser.tab.c"
    break;

  case 84: /* assignment_operator: ASSIGN  */
#line 916 "src/parser.y"
                 { 
        dbg("assignment_operator -> =");
        (yyval.str) = (yyvsp[0].str); }
#line 3022 "src/parser.tab.c"
    break;

  case 85: /* assignment_operator: STAR_EQUAL  */
#line 919 "src/parser.y"
                     { 
        dbg("assignment_operator -> *=");
        (yyval.str) = (yyvsp[0].str); }
#line 3030 "src/parser.tab.c"
    break;

  case 86: /* assignment_operator: DIV_EQUAL  */
#line 922 "src/parser.y"
                    { 
        dbg("assignment_operator -> /=");
        (yyval.str) = (yyvsp[0].str); }
#line 3038 "src/parser.tab.c"
    break;

  case 87: /* assignment_operator: MOD_EQUAL  */
#line 925 "src/parser.y"
                    { 
        dbg("assignment_operator -> %=");
        (yyval.str) = (yyvsp[0].str); }
#line 3046 "src/parser.tab.c"
    break;

  case 88: /* assignment_operator: PLUS_EQUAL  */
#line 928 "src/parser.y"
                     { 
        dbg("assignment_operator -> +=");
        (yyval.str) = (yyvsp[0].str); }
#line 3054 "src/parser.tab.c"
    break;

  case 89: /* assignment_operator: MINUS_EQUAL  */
#line 931 "src/parser.y"
                      { 
        dbg("assignment_operator -> -=");
        (yyval.str) = (yyvsp[0].str); }
#line 3062 "src/parser.tab.c"
    break;

  case 90: /* assignment_operator: LEFT_SHIFT_EQ  */
#line 934 "src/parser.y"
                        { 
        dbg("assignment_operator -> <<=");
        (yyval.str) = (yyvsp[0].str); }
#line 3070 "src/parser.tab.c"
    break;

  case 91: /* assignment_operator: RIGHT_SHIFT_EQ  */
#line 937 "src/parser.y"
                         { 
        dbg("assignment_operator -> >>=");
        (yyval.str) = (yyvsp[0].str); }
#line 3078 "src/parser.tab.c"
    break;

  case 92: /* assignment_operator: AND_EQUAL  */
#line 940 "src/parser.y"
                    { 
        dbg("assignment_operator -> &=");
        (yyval.str) = (yyvsp[0].str); }
#line 3086 "src/parser.tab.c"
    break;

  case 93: /* assignment_operator: XOR_EQUAL  */
#line 943 "src/parser.y"
                    { 
        dbg("assignment_operator -> ^=");
        (yyval.str) = (yyvsp[0].str); }
#line 3094 "src/parser.tab.c"
    break;

  case 94: /* assignment_operator: OR_EQUAL  */
#line 946 "src/parser.y"
                   { 
        dbg("assignment_operator -> |=");
        (yyval.str) = (yyvsp[0].str); }
#line 3102 "src/parser.tab.c"
    break;

  case 95: /* expression: assignment_expression  */
#line 952 "src/parser.y"
                                { 
        dbg("expression -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3110 "src/parser.tab.c"
    break;

  case 96: /* expression: expression COMMA assignment_expression  */
#line 955 "src/parser.y"
                                                 {
            dbg("expression -> expression , assignment_expression");
          Node* n = (yyvsp[-2].node);
          Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->place = e->place;
          (yyval.node) = n;
      }
#line 3123 "src/parser.tab.c"
    break;

  case 97: /* constant_expression: conditional_expression  */
#line 966 "src/parser.y"
                                 { 
        dbg("constant_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3131 "src/parser.tab.c"
    break;

  case 98: /* declaration: declaration_specifiers SEMICOLON  */
#line 972 "src/parser.y"
                                           {
          dbg("declaration -> declaration_specifiers ;");
          Node* n = new Node();
          (yyval.node) = n;
      }
#line 3141 "src/parser.tab.c"
    break;

  case 99: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 977 "src/parser.y"
                                                                {
            dbg("declaration -> declaration_specifiers init_declarator_list ;");
          (yyval.node) = (yyvsp[-1].node);
      }
#line 3150 "src/parser.tab.c"
    break;

  case 100: /* declaration: error SEMICOLON  */
#line 981 "src/parser.y"
                      {yyerrok;}
#line 3156 "src/parser.tab.c"
    break;

  case 101: /* declaration_specifiers: storage_class_specifier  */
#line 985 "src/parser.y"
                                  { 
        dbg("declaration_specifiers -> storage_class_specifier");
        (yyval.node) = new Node(); }
#line 3164 "src/parser.tab.c"
    break;

  case 102: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 988 "src/parser.y"
                                                         { 
        dbg("declaration_specifiers -> storage_class_specifier declaration_specifiers");
        (yyval.node) = (yyvsp[0].node); }
#line 3172 "src/parser.tab.c"
    break;

  case 103: /* declaration_specifiers: type_specifier  */
#line 991 "src/parser.y"
                         { 
        dbg("declaration_specifiers -> type_specifier");
        lastDeclType = string((yyvsp[0].str)); (yyval.node) = new Node(); }
#line 3180 "src/parser.tab.c"
    break;

  case 104: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 994 "src/parser.y"
                                                { 
        dbg("declaration_specifiers -> type_specifier declaration_specifiers");
        lastDeclType = string((yyvsp[-1].str)); (yyval.node) = (yyvsp[0].node); }
#line 3188 "src/parser.tab.c"
    break;

  case 105: /* declaration_specifiers: type_qualifier  */
#line 997 "src/parser.y"
                         { 
        dbg("declaration_specifiers -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3196 "src/parser.tab.c"
    break;

  case 106: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 1000 "src/parser.y"
                                                { 
        dbg("declaration_specifiers -> type_qualifier declaration_specifiers");
        (yyval.node) = (yyvsp[0].node); }
#line 3204 "src/parser.tab.c"
    break;

  case 107: /* init_declarator_list: init_declarator  */
#line 1006 "src/parser.y"
                          { 
        dbg("init_declarator_list -> init_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3212 "src/parser.tab.c"
    break;

  case 108: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1009 "src/parser.y"
                                                     {
            dbg("init_declarator_list -> init_declarator_list , init_declarator");
          Node* n = (yyvsp[-2].node);
          n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 3223 "src/parser.tab.c"
    break;

  case 109: /* init_declarator: declarator  */
#line 1018 "src/parser.y"
                     {
            dbg("init_declarator -> declarator");
          Node* n = new Node();
          if ((yyvsp[0].node)) {
              string name = (yyvsp[0].node)->place;
              bool ok = declareSymbol(name, lastDeclType);
              if (!ok) {
                  yyerror("Duplicate declaration of '" + name + "' in same scope.");
              }
              n->place = name; n->type = lastDeclType;
          }
          (yyval.node) = n;
      }
#line 3241 "src/parser.tab.c"
    break;

  case 110: /* init_declarator: declarator ASSIGN initializer  */
#line 1031 "src/parser.y"
                                        {
            dbg("init_declarator -> declarator = initializer");
          Node* lhs = (yyvsp[-2].node);
          Node* rhs = (yyvsp[0].node);
          Node* n = new Node();
          n->code = rhs->code;
          string name = lhs->place;
          bool ok = declareSymbol(name, lastDeclType);
          if (!ok) yyerror("Duplicate declaration of '" + name + "' in same scope.");
          n->code.push_back(name + " = " + rhs->place + ";");
          n->place = name; n->type = lastDeclType;
          if (!rhs->type.empty() && rhs->type != lastDeclType) {
              yyerror("Initializing '" + name + "' of type " + lastDeclType + " with incompatible type " + rhs->type + ".");
          }
          (yyval.node) = n;
      }
#line 3262 "src/parser.tab.c"
    break;

  case 111: /* storage_class_specifier: STATIC  */
#line 1050 "src/parser.y"
                 { 
        dbg("storage_class_specifier -> STATIC");
        (yyval.node) = new Node(); }
#line 3270 "src/parser.tab.c"
    break;

  case 112: /* type_specifier: VOID  */
#line 1056 "src/parser.y"
                 { 
        dbg("type_specifier -> VOID");
        (yyval.str) = strdup("void"); lastDeclType = "void"; }
#line 3278 "src/parser.tab.c"
    break;

  case 113: /* type_specifier: CHAR  */
#line 1059 "src/parser.y"
                 { 
        dbg("type_specifier -> CHAR");
        (yyval.str) = strdup("char"); lastDeclType = "char"; }
#line 3286 "src/parser.tab.c"
    break;

  case 114: /* type_specifier: INT  */
#line 1062 "src/parser.y"
                 { 
        dbg("type_specifier -> INT");
        (yyval.str) = strdup("int"); lastDeclType = "int"; }
#line 3294 "src/parser.tab.c"
    break;

  case 115: /* type_specifier: LONG  */
#line 1065 "src/parser.y"
                 { 
        dbg("type_specifier -> LONG");
        (yyval.str) = strdup("long"); lastDeclType = "long"; }
#line 3302 "src/parser.tab.c"
    break;

  case 116: /* type_specifier: DOUBLE  */
#line 1068 "src/parser.y"
                 { 
        dbg("type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); lastDeclType = "double"; }
#line 3310 "src/parser.tab.c"
    break;

  case 117: /* type_specifier: BOOL  */
#line 1071 "src/parser.y"
                 { 
        dbg("type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); lastDeclType = "bool"; }
#line 3318 "src/parser.tab.c"
    break;

  case 118: /* type_specifier: STRING  */
#line 1074 "src/parser.y"
                 { 
        dbg("type_specifier -> STRING");
        (yyval.str) = strdup("string"); lastDeclType = "string"; }
#line 3326 "src/parser.tab.c"
    break;

  case 119: /* type_specifier: TYPE_NAME  */
#line 1077 "src/parser.y"
                    { 
        dbg("type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str); lastDeclType = string((yyvsp[0].str)); }
#line 3334 "src/parser.tab.c"
    break;

  case 120: /* struct_or_class_specifier: struct_or_class IDENTIFIER LCURLY struct_or_class_member_list RCURLY  */
#line 1083 "src/parser.y"
                                                                               { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        Node* n = new Node(); (yyval.node) = n; }
#line 3342 "src/parser.tab.c"
    break;

  case 121: /* struct_or_class_specifier: struct_or_class IDENTIFIER  */
#line 1086 "src/parser.y"
                                     { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER");
        Node* n = new Node(); (yyval.node) = n; }
#line 3350 "src/parser.tab.c"
    break;

  case 122: /* struct_or_class: STRUCT  */
#line 1092 "src/parser.y"
                 { 
        dbg("struct_or_class -> STRUCT");
        (yyval.node) = new Node(); }
#line 3358 "src/parser.tab.c"
    break;

  case 123: /* struct_or_class: CLASS  */
#line 1095 "src/parser.y"
                { 
        dbg("struct_or_class -> CLASS");
        (yyval.node) = new Node(); }
#line 3366 "src/parser.tab.c"
    break;

  case 124: /* struct_or_class_member_list: struct_or_class_member  */
#line 1101 "src/parser.y"
                                 { 
        dbg("struct_or_class_member_list -> struct_or_class_member");
        (yyval.node) = (yyvsp[0].node); }
#line 3374 "src/parser.tab.c"
    break;

  case 125: /* struct_or_class_member_list: struct_or_class_member_list struct_or_class_member  */
#line 1104 "src/parser.y"
                                                             { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        Node* n = (yyvsp[-1].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; }
#line 3384 "src/parser.tab.c"
    break;

  case 126: /* struct_or_class_member: access_specifier_label  */
#line 1112 "src/parser.y"
                                 { 
        dbg("struct_or_class_member -> access_specifier_label");
        (yyval.node) = (yyvsp[0].node); }
#line 3392 "src/parser.tab.c"
    break;

  case 127: /* struct_or_class_member: member_declaration  */
#line 1115 "src/parser.y"
                             { 
        dbg("struct_or_class_member -> member_declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 3400 "src/parser.tab.c"
    break;

  case 128: /* access_specifier_label: PUBLIC COLON  */
#line 1121 "src/parser.y"
                       { 
        dbg("access_specifier_label -> PUBLIC :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3408 "src/parser.tab.c"
    break;

  case 129: /* access_specifier_label: PRIVATE COLON  */
#line 1124 "src/parser.y"
                        { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3416 "src/parser.tab.c"
    break;

  case 130: /* access_specifier_label: PROTECTED COLON  */
#line 1127 "src/parser.y"
                          { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3424 "src/parser.tab.c"
    break;

  case 131: /* member_declaration: specifier_qualifier_list struct_declarator_list SEMICOLON  */
#line 1133 "src/parser.y"
                                                                    { 
        dbg("member_declaration -> specifier_qualifier_list struct_declarator_list ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3432 "src/parser.tab.c"
    break;

  case 132: /* member_declaration: specifier_qualifier_list SEMICOLON  */
#line 1136 "src/parser.y"
                                             { 
        dbg("member_declaration -> specifier_qualifier_list ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3440 "src/parser.tab.c"
    break;

  case 133: /* member_declaration: specifier_qualifier_list declarator compound_statement  */
#line 1139 "src/parser.y"
                                                                 { 
        dbg("member_declaration -> specifier_qualifier_list declarator compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 3448 "src/parser.tab.c"
    break;

  case 134: /* member_declaration: struct_or_class_specifier SEMICOLON  */
#line 1142 "src/parser.y"
                                              { 
        dbg("member_declaration -> struct_or_class_specifier ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3456 "src/parser.tab.c"
    break;

  case 135: /* member_declaration: SEMICOLON  */
#line 1145 "src/parser.y"
                    { 
        dbg("member_declaration -> ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3464 "src/parser.tab.c"
    break;

  case 136: /* member_declaration: constructor_definition  */
#line 1148 "src/parser.y"
                                 { 
        dbg("member_declaration -> constructor_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 3472 "src/parser.tab.c"
    break;

  case 137: /* member_declaration: destructor_definition  */
#line 1151 "src/parser.y"
                                { 
        dbg("member_declaration -> destructor_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 3480 "src/parser.tab.c"
    break;

  case 138: /* constructor_definition: IDENTIFIER LROUND parameter_list RROUND compound_statement  */
#line 1157 "src/parser.y"
                                                                     {
        dbg("constructor_definition -> IDENTIFIER ( parameter_list ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3489 "src/parser.tab.c"
    break;

  case 139: /* constructor_definition: IDENTIFIER LROUND RROUND compound_statement  */
#line 1161 "src/parser.y"
                                                      {
        dbg("constructor_definition -> IDENTIFIER ( ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3498 "src/parser.tab.c"
    break;

  case 140: /* destructor_definition: TILDE IDENTIFIER LROUND RROUND compound_statement  */
#line 1168 "src/parser.y"
                                                            {
        dbg("destructor_definition -> ~ IDENTIFIER ( ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3507 "src/parser.tab.c"
    break;

  case 141: /* struct_declarator_list: struct_declarator  */
#line 1175 "src/parser.y"
                            { 
        dbg("struct_declarator_list -> struct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3515 "src/parser.tab.c"
    break;

  case 142: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1178 "src/parser.y"
                                                         { 
        dbg("struct_declarator_list -> struct_declarator_list , struct_declarator");
        Node* n = (yyvsp[-2].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; }
#line 3525 "src/parser.tab.c"
    break;

  case 143: /* struct_declarator: init_declarator  */
#line 1186 "src/parser.y"
                          { 
        dbg("struct_declarator -> init_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3533 "src/parser.tab.c"
    break;

  case 144: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1192 "src/parser.y"
                                                  { 
        dbg("specifier_qualifier_list -> type_specifier specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3541 "src/parser.tab.c"
    break;

  case 145: /* specifier_qualifier_list: type_specifier  */
#line 1195 "src/parser.y"
                         { 
        dbg("specifier_qualifier_list -> type_specifier");
        (yyval.node) = new Node(); }
#line 3549 "src/parser.tab.c"
    break;

  case 146: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1198 "src/parser.y"
                                                  { 
        dbg("specifier_qualifier_list -> type_qualifier specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3557 "src/parser.tab.c"
    break;

  case 147: /* specifier_qualifier_list: type_qualifier  */
#line 1201 "src/parser.y"
                         { 
        dbg("specifier_qualifier_list -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3565 "src/parser.tab.c"
    break;

  case 148: /* type_qualifier: CONST  */
#line 1207 "src/parser.y"
                { 
        dbg("type_qualifier -> CONST");
        (yyval.node) = new Node(); }
#line 3573 "src/parser.tab.c"
    break;

  case 149: /* declarator: pointer direct_declarator  */
#line 1213 "src/parser.y"
                                    { 
        dbg("declarator -> pointer direct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3581 "src/parser.tab.c"
    break;

  case 150: /* declarator: direct_declarator  */
#line 1216 "src/parser.y"
                            { 
        dbg("declarator -> direct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3589 "src/parser.tab.c"
    break;

  case 151: /* direct_declarator: IDENTIFIER  */
#line 1222 "src/parser.y"
                     {
            dbg("direct_declarator -> IDENTIFIER");
          Node* n = new Node();
          n->place = string((yyvsp[0].str));
          (yyval.node) = n;
      }
#line 3600 "src/parser.tab.c"
    break;

  case 152: /* direct_declarator: LROUND declarator RROUND  */
#line 1228 "src/parser.y"
                                   { 
        dbg("direct_declarator -> ( declarator )");
        (yyval.node) = (yyvsp[-1].node); }
#line 3608 "src/parser.tab.c"
    break;

  case 153: /* direct_declarator: direct_declarator LSQUARE constant_expression RSQUARE  */
#line 1231 "src/parser.y"
                                                                { 
        dbg("direct_declarator -> direct_declarator [ constant_expression ]");
        (yyval.node) = (yyvsp[-3].node); }
#line 3616 "src/parser.tab.c"
    break;

  case 154: /* direct_declarator: direct_declarator LSQUARE RSQUARE  */
#line 1234 "src/parser.y"
                                            { 
        dbg("direct_declarator -> direct_declarator [ ]");
        (yyval.node) = (yyvsp[-2].node); }
#line 3624 "src/parser.tab.c"
    break;

  case 155: /* direct_declarator: direct_declarator LROUND parameter_list RROUND  */
#line 1237 "src/parser.y"
                                                         { 
        dbg("direct_declarator -> direct_declarator ( parameter_list )");
        (yyval.node) = (yyvsp[-3].node); }
#line 3632 "src/parser.tab.c"
    break;

  case 156: /* direct_declarator: direct_declarator LROUND identifier_list RROUND  */
#line 1240 "src/parser.y"
                                                          { 
        dbg("direct_declarator -> direct_declarator ( identifier_list )");
        (yyval.node) = (yyvsp[-3].node); }
#line 3640 "src/parser.tab.c"
    break;

  case 157: /* direct_declarator: direct_declarator LROUND RROUND  */
#line 1243 "src/parser.y"
                                          { 
        dbg("direct_declarator -> direct_declarator ( )");
        (yyval.node) = (yyvsp[-2].node); }
#line 3648 "src/parser.tab.c"
    break;

  case 158: /* pointer: STAR  */
#line 1249 "src/parser.y"
               { 
        dbg("pointer -> *");
        (yyval.node) = new Node(); }
#line 3656 "src/parser.tab.c"
    break;

  case 159: /* pointer: STAR type_qualifier_list  */
#line 1252 "src/parser.y"
                                   { 
        dbg("pointer -> * type_qualifier_list");
        (yyval.node) = new Node(); }
#line 3664 "src/parser.tab.c"
    break;

  case 160: /* pointer: STAR pointer  */
#line 1255 "src/parser.y"
                       { 
        dbg("pointer -> * pointer");
        (yyval.node) = new Node(); }
#line 3672 "src/parser.tab.c"
    break;

  case 161: /* pointer: STAR type_qualifier_list pointer  */
#line 1258 "src/parser.y"
                                           { 
        dbg("pointer -> * type_qualifier_list pointer");
        (yyval.node) = new Node(); }
#line 3680 "src/parser.tab.c"
    break;

  case 162: /* type_qualifier_list: type_qualifier  */
#line 1264 "src/parser.y"
                         { 
        dbg("type_qualifier_list -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3688 "src/parser.tab.c"
    break;

  case 163: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1267 "src/parser.y"
                                             { 
        dbg("type_qualifier_list -> type_qualifier_list type_qualifier");
        (yyval.node) = new Node(); }
#line 3696 "src/parser.tab.c"
    break;

  case 164: /* parameter_list: parameter_declaration  */
#line 1273 "src/parser.y"
                                { 
            dbg("parameter_list -> parameter_declaration");
            (yyval.node) = (yyvsp[0].node); 
        }
#line 3705 "src/parser.tab.c"
    break;

  case 165: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1278 "src/parser.y"
        {
            dbg("parameter_list -> parameter_list , parameter_declaration");
            Node* n = (yyvsp[-2].node);
            n->syn.insert(n->syn.end(), (yyvsp[0].node)->syn.begin(), (yyvsp[0].node)->syn.end()); 
            (yyval.node) = n;
        }
#line 3716 "src/parser.tab.c"
    break;

  case 166: /* parameter_declaration: return_type IDENTIFIER  */
#line 1288 "src/parser.y"
        {
            dbg("parameter_declaration -> return_type IDENTIFIER");
            Node* n = new Node();
            n->syn.push_back(string((yyvsp[-1].str))); 
            n->syn.push_back(string((yyvsp[0].str)));
            (yyval.node) = n;
        }
#line 3728 "src/parser.tab.c"
    break;

  case 167: /* identifier_list: IDENTIFIER  */
#line 1298 "src/parser.y"
                     { 
        dbg("identifier_list -> IDENTIFIER");
        (yyval.node) = nullptr; }
#line 3736 "src/parser.tab.c"
    break;

  case 168: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 1301 "src/parser.y"
                                           { 
        dbg("identifier_list -> identifier_list , IDENTIFIER");
        (yyval.node) = nullptr; }
#line 3744 "src/parser.tab.c"
    break;

  case 169: /* type_name: specifier_qualifier_list  */
#line 1307 "src/parser.y"
                                   { 
        dbg("type_name -> specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3752 "src/parser.tab.c"
    break;

  case 170: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1310 "src/parser.y"
                                                       { 
        dbg("type_name -> specifier_qualifier_list abstract_declarator");
        (yyval.node) = new Node(); }
#line 3760 "src/parser.tab.c"
    break;

  case 171: /* abstract_declarator: pointer  */
#line 1316 "src/parser.y"
                  { 
        dbg("abstract_declarator -> pointer");
        (yyval.node) = new Node(); }
#line 3768 "src/parser.tab.c"
    break;

  case 172: /* abstract_declarator: direct_abstract_declarator  */
#line 1319 "src/parser.y"
                                     { 
        dbg("abstract_declarator -> direct_abstract_declarator");
        (yyval.node) = new Node(); }
#line 3776 "src/parser.tab.c"
    break;

  case 173: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1322 "src/parser.y"
                                             { 
        dbg("abstract_declarator -> pointer direct_abstract_declarator");
        (yyval.node) = new Node(); }
#line 3784 "src/parser.tab.c"
    break;

  case 174: /* direct_abstract_declarator: LROUND abstract_declarator RROUND  */
#line 1328 "src/parser.y"
                                            { 
        dbg("direct_abstract_declarator -> ( abstract_declarator )");
        (yyval.node) = new Node(); }
#line 3792 "src/parser.tab.c"
    break;

  case 175: /* direct_abstract_declarator: LSQUARE RSQUARE  */
#line 1331 "src/parser.y"
                          { 
        dbg("direct_abstract_declarator -> [ ]");
        (yyval.node) = new Node(); }
#line 3800 "src/parser.tab.c"
    break;

  case 176: /* direct_abstract_declarator: LSQUARE constant_expression RSQUARE  */
#line 1334 "src/parser.y"
                                              { 
        dbg("direct_abstract_declarator -> [ constant_expression ]");
        (yyval.node) = new Node(); }
#line 3808 "src/parser.tab.c"
    break;

  case 177: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE RSQUARE  */
#line 1337 "src/parser.y"
                                                     { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator [ ]");
        (yyval.node) = new Node(); }
#line 3816 "src/parser.tab.c"
    break;

  case 178: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression RSQUARE  */
#line 1340 "src/parser.y"
                                                                         { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator [ constant_expression ]");
        (yyval.node) = new Node(); }
#line 3824 "src/parser.tab.c"
    break;

  case 179: /* direct_abstract_declarator: LROUND RROUND  */
#line 1343 "src/parser.y"
                        { 
        dbg("direct_abstract_declarator -> ( )");
        (yyval.node) = new Node(); }
#line 3832 "src/parser.tab.c"
    break;

  case 180: /* direct_abstract_declarator: LROUND parameter_list RROUND  */
#line 1346 "src/parser.y"
                                       { 
        dbg("direct_abstract_declarator -> ( parameter_list )");
        (yyval.node) = new Node(); }
#line 3840 "src/parser.tab.c"
    break;

  case 181: /* direct_abstract_declarator: direct_abstract_declarator LROUND RROUND  */
#line 1349 "src/parser.y"
                                                   { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator ( )");
        (yyval.node) = new Node(); }
#line 3848 "src/parser.tab.c"
    break;

  case 182: /* direct_abstract_declarator: direct_abstract_declarator LROUND parameter_list RROUND  */
#line 1352 "src/parser.y"
                                                                  { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator ( parameter_list )");
        (yyval.node) = new Node(); }
#line 3856 "src/parser.tab.c"
    break;

  case 183: /* initializer: assignment_expression  */
#line 1358 "src/parser.y"
                                { 
        dbg("initializer -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3864 "src/parser.tab.c"
    break;

  case 184: /* initializer: LCURLY initializer_list RCURLY  */
#line 1361 "src/parser.y"
                                         { 
        dbg("initializer -> { initializer_list }");
        (yyval.node) = (yyvsp[-1].node); }
#line 3872 "src/parser.tab.c"
    break;

  case 185: /* initializer: LCURLY initializer_list COMMA RCURLY  */
#line 1364 "src/parser.y"
                                               { 
        dbg("initializer -> { initializer_list , }");
        (yyval.node) = (yyvsp[-2].node); }
#line 3880 "src/parser.tab.c"
    break;

  case 186: /* initializer_list: initializer  */
#line 1370 "src/parser.y"
                      { 
        dbg("initializer_list -> initializer");
        (yyval.node) = (yyvsp[0].node); }
#line 3888 "src/parser.tab.c"
    break;

  case 187: /* initializer_list: initializer_list COMMA initializer  */
#line 1373 "src/parser.y"
                                             {
            dbg("initializer_list -> initializer_list , initializer");
          Node* n = (yyvsp[-2].node); n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); (yyval.node) = n;
      }
#line 3897 "src/parser.tab.c"
    break;

  case 188: /* statement: labeled_statement  */
#line 1380 "src/parser.y"
                            { 
        dbg("statement -> labeled_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3905 "src/parser.tab.c"
    break;

  case 189: /* statement: compound_statement  */
#line 1383 "src/parser.y"
                             { 
        dbg("statement -> compound_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3913 "src/parser.tab.c"
    break;

  case 190: /* statement: expression_statement  */
#line 1386 "src/parser.y"
                               { 
        dbg("statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3921 "src/parser.tab.c"
    break;

  case 191: /* statement: selection_statement  */
#line 1389 "src/parser.y"
                              { 
        dbg("statement -> selection_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3929 "src/parser.tab.c"
    break;

  case 192: /* statement: iteration_statement  */
#line 1392 "src/parser.y"
                              { 
        dbg("statement -> iteration_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3937 "src/parser.tab.c"
    break;

  case 193: /* statement: jump_statement  */
#line 1395 "src/parser.y"
                         { 
        dbg("statement -> jump_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3945 "src/parser.tab.c"
    break;

  case 194: /* statement: io_statement  */
#line 1398 "src/parser.y"
                       { 
        dbg("statement -> io_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3953 "src/parser.tab.c"
    break;

  case 195: /* io_statement: cout_expression SEMICOLON  */
#line 1404 "src/parser.y"
                                { 
        dbg("io_statement -> cout_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 3961 "src/parser.tab.c"
    break;

  case 196: /* io_statement: cin_expression SEMICOLON  */
#line 1407 "src/parser.y"
                                { 
        dbg("io_statement -> cin_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 3969 "src/parser.tab.c"
    break;

  case 197: /* cout_expression: COUT insertion_list  */
#line 1413 "src/parser.y"
                          { 
        dbg("cout_expression -> COUT insertion_list");
        (yyval.node) = (yyvsp[0].node); }
#line 3977 "src/parser.tab.c"
    break;

  case 198: /* insertion_list: LEFT_SHIFT assignment_expression  */
#line 1419 "src/parser.y"
                                       {
          dbg("insertion_list -> LEFT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node);
          Node* n = new Node();
          n->code = e->code; n->code.push_back("print " + e->place + ";"); (yyval.node) = n;
      }
#line 3988 "src/parser.tab.c"
    break;

  case 199: /* insertion_list: LEFT_SHIFT ENDL  */
#line 1425 "src/parser.y"
                          {
            dbg("insertion_list -> LEFT_SHIFT ENDL");
          Node* n = new Node();
          n->code.push_back("print endl;"); (yyval.node) = n;
      }
#line 3998 "src/parser.tab.c"
    break;

  case 200: /* insertion_list: insertion_list LEFT_SHIFT ENDL  */
#line 1430 "src/parser.y"
                                         {
            dbg("insertion_list -> insertion_list LEFT_SHIFT ENDL");
          Node* n = (yyvsp[-2].node); n->code.push_back("print endl;"); (yyval.node) = n;
      }
#line 4007 "src/parser.tab.c"
    break;

  case 201: /* insertion_list: insertion_list LEFT_SHIFT assignment_expression  */
#line 1434 "src/parser.y"
                                                          {
            dbg("insertion_list -> insertion_list LEFT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("print " + e->place + ";"); (yyval.node) = n;
      }
#line 4018 "src/parser.tab.c"
    break;

  case 202: /* cin_expression: CIN extraction_list  */
#line 1443 "src/parser.y"
                          { 
        dbg("cin_expression -> CIN extraction_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4026 "src/parser.tab.c"
    break;

  case 203: /* extraction_list: RIGHT_SHIFT assignment_expression  */
#line 1449 "src/parser.y"
                                        {
            dbg("extraction_list -> RIGHT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node); Node* n = new Node();
          n->code = e->code; n->code.push_back("read " + e->place + ";"); (yyval.node) = n;
      }
#line 4036 "src/parser.tab.c"
    break;

  case 204: /* extraction_list: extraction_list RIGHT_SHIFT assignment_expression  */
#line 1454 "src/parser.y"
                                                        {
            dbg("extraction_list -> extraction_list RIGHT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("read " + e->place + ";"); (yyval.node) = n;
      }
#line 4047 "src/parser.tab.c"
    break;

  case 205: /* labeled_statement: IDENTIFIER COLON statement  */
#line 1463 "src/parser.y"
                                     {
          dbg("labeled_statement -> IDENTIFIER : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string((yyvsp[-2].str)) + ":");
          (yyval.node) = s;
      }
#line 4058 "src/parser.tab.c"
    break;

  case 206: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1469 "src/parser.y"
                                                   {
            dbg("labeled_statement -> CASE constant_expression : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string("case ") + (yyvsp[-2].node)->place + ":");
          (yyval.node) = s;
      }
#line 4069 "src/parser.tab.c"
    break;

  case 207: /* labeled_statement: DEFAULT COLON statement  */
#line 1475 "src/parser.y"
                                  {
            dbg("labeled_statement -> DEFAULT : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string("default:"));
          (yyval.node) = s;
      }
#line 4080 "src/parser.tab.c"
    break;

  case 208: /* compound_statement: LCURLY RCURLY  */
#line 1484 "src/parser.y"
                        {
            dbg("compound_statement -> { }");
          pushScope();
          Node* n = new Node();
          popScope();
          (yyval.node) = n;
      }
#line 4092 "src/parser.tab.c"
    break;

  case 209: /* compound_statement: LCURLY statement_list RCURLY  */
#line 1491 "src/parser.y"
                                       {
            dbg("compound_statement -> { statement_list }");
          pushScope();
          Node* n = (yyvsp[-1].node);
          popScope();
          (yyval.node) = n;
      }
#line 4104 "src/parser.tab.c"
    break;

  case 210: /* statement_list: block_item  */
#line 1501 "src/parser.y"
                     { 
        dbg("statement_list -> block_item");
        (yyval.node) = (yyvsp[0].node); }
#line 4112 "src/parser.tab.c"
    break;

  case 211: /* statement_list: statement_list block_item  */
#line 1504 "src/parser.y"
                                    {
            dbg("statement_list -> statement_list block_item");
          Node* n = (yyvsp[-1].node);
          if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 4123 "src/parser.tab.c"
    break;

  case 212: /* block_item: statement  */
#line 1513 "src/parser.y"
                { 
        dbg("block_item -> statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4131 "src/parser.tab.c"
    break;

  case 213: /* block_item: declaration  */
#line 1516 "src/parser.y"
                  { 
        dbg("block_item -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4139 "src/parser.tab.c"
    break;

  case 214: /* block_item: error RCURLY  */
#line 1519 "src/parser.y"
                   { yyerrok;}
#line 4145 "src/parser.tab.c"
    break;

  case 215: /* expression_statement: SEMICOLON  */
#line 1523 "src/parser.y"
                    { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4153 "src/parser.tab.c"
    break;

  case 216: /* expression_statement: expression SEMICOLON  */
#line 1526 "src/parser.y"
                               { 
        dbg("expression_statement -> expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4161 "src/parser.tab.c"
    break;

  case 217: /* selection_statement: IF LROUND expression RROUND statement  */
#line 1532 "src/parser.y"
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
#line 4177 "src/parser.tab.c"
    break;

  case 218: /* selection_statement: IF LROUND expression RROUND statement ELSE statement  */
#line 1543 "src/parser.y"
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
#line 4196 "src/parser.tab.c"
    break;

  case 219: /* selection_statement: SWITCH LROUND expression RROUND statement  */
#line 1557 "src/parser.y"
                                                    {
            dbg("selection_statement -> SWITCH ( expression ) statement");
          Node* n = (yyvsp[0].node); (yyval.node) = n;
      }
#line 4205 "src/parser.tab.c"
    break;

  case 220: /* iteration_statement: WHILE LROUND expression RROUND statement  */
#line 1564 "src/parser.y"
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
#line 4223 "src/parser.tab.c"
    break;

  case 221: /* iteration_statement: UNTIL LROUND expression RROUND statement  */
#line 1577 "src/parser.y"
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
#line 4239 "src/parser.tab.c"
    break;

  case 222: /* iteration_statement: DO statement WHILE LROUND expression RROUND SEMICOLON  */
#line 1588 "src/parser.y"
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
#line 4255 "src/parser.tab.c"
    break;

  case 223: /* iteration_statement: FOR LROUND for_init_statement expression_statement RROUND statement  */
#line 1599 "src/parser.y"
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
#line 4276 "src/parser.tab.c"
    break;

  case 224: /* iteration_statement: FOR LROUND for_init_statement expression_statement expression RROUND statement  */
#line 1615 "src/parser.y"
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
#line 4298 "src/parser.tab.c"
    break;

  case 225: /* for_init_statement: expression_statement  */
#line 1635 "src/parser.y"
                               { 
        dbg("for_init_statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4306 "src/parser.tab.c"
    break;

  case 226: /* for_init_statement: declaration  */
#line 1638 "src/parser.y"
                      { 
        dbg("for_init_statement -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4314 "src/parser.tab.c"
    break;

  case 227: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 1644 "src/parser.y"
                                    {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string((yyvsp[-1].str)) + ";");
          (yyval.node) = n;
      }
#line 4325 "src/parser.tab.c"
    break;

  case 228: /* jump_statement: CONTINUE SEMICOLON  */
#line 1650 "src/parser.y"
                             {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); n->code.push_back("continue;"); (yyval.node) = n;
      }
#line 4334 "src/parser.tab.c"
    break;

  case 229: /* jump_statement: BREAK SEMICOLON  */
#line 1654 "src/parser.y"
                          {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); n->code.push_back("break;"); (yyval.node) = n;
      }
#line 4343 "src/parser.tab.c"
    break;

  case 230: /* jump_statement: RETURN SEMICOLON  */
#line 1658 "src/parser.y"
                           {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); n->code.push_back("return;"); (yyval.node) = n;
      }
#line 4352 "src/parser.tab.c"
    break;

  case 231: /* jump_statement: RETURN expression SEMICOLON  */
#line 1662 "src/parser.y"
                                      {
            dbg("jump_statement -> RETURN expression ;");
          Node* expr = (yyvsp[-1].node);
          Node* n = new Node();
          n->code = expr->code;
          n->code.push_back("return " + expr->place + ";");
          (yyval.node) = n;
      }
#line 4365 "src/parser.tab.c"
    break;

  case 232: /* translation_unit: external_declaration  */
#line 1674 "src/parser.y"
                               { 
        dbg("translation_unit -> external_declaration");
        finalRoot = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 4373 "src/parser.tab.c"
    break;

  case 233: /* translation_unit: translation_unit external_declaration  */
#line 1677 "src/parser.y"
                                                {
            dbg("translation_unit -> translation_unit external_declaration");
          Node* a = (yyvsp[-1].node); Node* b = (yyvsp[0].node);
          if (a) { 
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; (yyval.node) = a; }
          else { finalRoot = b; (yyval.node) = b; }
      }
#line 4386 "src/parser.tab.c"
    break;

  case 234: /* translation_unit: error  */
#line 1685 "src/parser.y"
            { yyerrok;}
#line 4392 "src/parser.tab.c"
    break;

  case 235: /* external_declaration: function_definition  */
#line 1690 "src/parser.y"
                              { 
        dbg("external_declaration -> function_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 4400 "src/parser.tab.c"
    break;

  case 236: /* external_declaration: struct_or_class_specifier SEMICOLON  */
#line 1693 "src/parser.y"
                                              { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4408 "src/parser.tab.c"
    break;

  case 237: /* external_declaration: declaration  */
#line 1696 "src/parser.y"
                      {
        dbg("external_declaration -> declaration");
         (yyval.node) = (yyvsp[0].node); }
#line 4416 "src/parser.tab.c"
    break;

  case 238: /* external_declaration: TYPEDEF return_type IDENTIFIER SEMICOLON  */
#line 1699 "src/parser.y"
                                               {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string((yyvsp[-1].str))] = typeSize[string((yyvsp[-2].str))];
        (yyval.node) = new Node();
        }
#line 4426 "src/parser.tab.c"
    break;

  case 239: /* function_header: return_type IDENTIFIER LROUND RROUND  */
#line 1709 "src/parser.y"
        {
            dbg("function_definition -> return_type direct_declarator compound_statement");
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
#line 4453 "src/parser.tab.c"
    break;

  case 240: /* function_header: return_type IDENTIFIER LROUND parameter_list RROUND  */
#line 1733 "src/parser.y"
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
#line 4492 "src/parser.tab.c"
    break;

  case 241: /* function_definition: function_header compound_statement  */
#line 1771 "src/parser.y"
                                        {
            dbg("function_definition -> function_header compound_statement");
            Node* n = (yyvsp[-1].node);
            if((yyvsp[0].node)) n->code.insert(n->code.end(),(yyvsp[0].node)->code.begin(),(yyvsp[0].node)->code.end()); 
            popScope(); 
            finalRoot = n;
            currentFunction = "global";
            (yyval.node) = n;
        }
#line 4506 "src/parser.tab.c"
    break;

  case 242: /* function_definition: error RCURLY  */
#line 1780 "src/parser.y"
                   { yyerrok;}
#line 4512 "src/parser.tab.c"
    break;

  case 243: /* return_type: type_specifier pointer_opt  */
#line 1785 "src/parser.y"
                                 { 
            dbg("return_type -> type_specifier pointer_opt");
            (yyval.str) = strcat((yyvsp[-1].str),(yyvsp[0].str)); 
        }
#line 4521 "src/parser.tab.c"
    break;

  case 244: /* lambda_expression: LSQUARE lambda_capture_clause RSQUARE lambda_declarator compound_statement  */
#line 1792 "src/parser.y"
                                                                                 { 
        dbg("lambda_expression -> [ lambda_capture_clause ] lambda_declarator compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 4529 "src/parser.tab.c"
    break;

  case 245: /* lambda_expression: LSQUARE lambda_capture_clause RSQUARE compound_statement  */
#line 1795 "src/parser.y"
                                                               { 
        dbg("lambda_expression -> [ lambda_capture_clause ] compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 4537 "src/parser.tab.c"
    break;

  case 246: /* lambda_declarator: lambda_parameter_clause trailing_return_opt  */
#line 1801 "src/parser.y"
                                                  { 
        dbg("lambda_declarator -> lambda_parameter_clause trailing_return_opt");
        (yyval.node) = (yyvsp[-1].node); }
#line 4545 "src/parser.tab.c"
    break;

  case 247: /* lambda_parameter_clause: LROUND RROUND  */
#line 1807 "src/parser.y"
                    { 
        dbg("lambda_parameter_clause -> ( )");
        (yyval.node) = new Node(); }
#line 4553 "src/parser.tab.c"
    break;

  case 248: /* lambda_parameter_clause: LROUND parameter_list RROUND  */
#line 1810 "src/parser.y"
                                   {
        dbg("lambda_parameter_clause -> ( parameter_list )");
         (yyval.node) = (yyvsp[-1].node); }
#line 4561 "src/parser.tab.c"
    break;

  case 249: /* trailing_return_opt: %empty  */
#line 1816 "src/parser.y"
       { 
        dbg("trailing_return_opt -> <empty>");
        (yyval.node) = nullptr; }
#line 4569 "src/parser.tab.c"
    break;

  case 250: /* trailing_return_opt: ARROW type_name  */
#line 1819 "src/parser.y"
                      { 
        dbg("trailing_return_opt -> ARROW type_name");
        (yyval.node) = (yyvsp[0].node); }
#line 4577 "src/parser.tab.c"
    break;

  case 251: /* lambda_capture_clause: ASSIGN  */
#line 1825 "src/parser.y"
             { 
        dbg("lambda_capture_clause -> =");
        (yyval.node) = new Node(); }
#line 4585 "src/parser.tab.c"
    break;

  case 252: /* lambda_capture_clause: capture_list  */
#line 1828 "src/parser.y"
                   { 
        dbg("lambda_capture_clause -> capture_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4593 "src/parser.tab.c"
    break;

  case 253: /* lambda_capture_clause: capture_list COMMA ASSIGN  */
#line 1831 "src/parser.y"
                                { 
        dbg("lambda_capture_clause -> capture_list , =");
        (yyval.node) = (yyvsp[-2].node); }
#line 4601 "src/parser.tab.c"
    break;

  case 254: /* lambda_capture_clause: ASSIGN COMMA capture_list  */
#line 1834 "src/parser.y"
                                { 
        dbg("lambda_capture_clause -> = , capture_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4609 "src/parser.tab.c"
    break;

  case 255: /* capture_list: IDENTIFIER  */
#line 1840 "src/parser.y"
                 { 
        dbg("capture_list -> IDENTIFIER");
        Node* n=new Node(); (yyval.node) = n; }
#line 4617 "src/parser.tab.c"
    break;

  case 256: /* capture_list: capture_list COMMA IDENTIFIER  */
#line 1843 "src/parser.y"
                                    {
        dbg("capture_list -> capture_list , IDENTIFIER"); 
        Node* n=(yyvsp[-2].node); (yyval.node) = n; }
#line 4625 "src/parser.tab.c"
    break;


#line 4629 "src/parser.tab.c"

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

#line 1848 "src/parser.y"



#include <cstdio>

void yyerror(const char *s);

int main(int argc, char** argv){
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

