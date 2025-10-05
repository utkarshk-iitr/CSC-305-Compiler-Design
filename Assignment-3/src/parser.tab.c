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
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1795

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  84
/* YYNRULES -- Number of rules.  */
#define YYNRULES  262
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  441

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
     579,   587,   595,   603,   611,   619,   630,   633,   639,   642,
     648,   651,   657,   664,   674,   677,   684,   687,   697,   707,
     720,   723,   733,   746,   749,   758,   770,   773,   780,   787,
     794,   804,   807,   814,   824,   827,   837,   840,   850,   853,
     863,   866,   876,   879,   889,   892,   913,   916,   948,   951,
     954,   957,   960,   963,   966,   969,   972,   975,   978,   984,
     987,   998,  1004,  1009,  1013,  1017,  1020,  1023,  1026,  1029,
    1032,  1038,  1041,  1050,  1063,  1082,  1085,  1088,  1094,  1097,
    1100,  1103,  1106,  1109,  1112,  1115,  1121,  1124,  1130,  1133,
    1139,  1142,  1150,  1153,  1159,  1162,  1165,  1171,  1174,  1177,
    1180,  1183,  1186,  1189,  1195,  1199,  1206,  1213,  1216,  1224,
    1230,  1233,  1236,  1239,  1245,  1251,  1254,  1260,  1266,  1269,
    1272,  1275,  1278,  1281,  1287,  1290,  1293,  1296,  1302,  1305,
    1311,  1315,  1325,  1336,  1339,  1345,  1348,  1354,  1357,  1360,
    1366,  1369,  1372,  1375,  1378,  1381,  1384,  1387,  1390,  1396,
    1399,  1402,  1408,  1411,  1418,  1421,  1424,  1427,  1430,  1433,
    1436,  1442,  1445,  1451,  1457,  1463,  1468,  1472,  1481,  1487,
    1492,  1501,  1507,  1513,  1522,  1529,  1539,  1542,  1551,  1554,
    1557,  1561,  1564,  1570,  1581,  1595,  1602,  1615,  1626,  1637,
    1653,  1673,  1676,  1682,  1688,  1692,  1696,  1700,  1712,  1715,
    1723,  1728,  1731,  1734,  1737,  1745,  1773,  1825,  1836,  1840,
    1847,  1850,  1856,  1862,  1865,  1871,  1874,  1880,  1883,  1886,
    1889,  1895,  1898
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

#define YYPACT_NINF (-275)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-48)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1010,    45,   630,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,     9,  1145,   604,
      -6,   -42,  1145,   830,  -275,    54,  -275,   -30,  -275,  -275,
     141,   124,    25,    17,  -275,  -275,    66,  -275,   204,    92,
      -7,  -275,  -275,  1145,   141,  -275,  -275,  -275,   176,  -275,
    -275,    45,  -275,   359,  -275,   202,   201,  -275,  -275,    25,
     208,  -275,    17,   840,   237,   910,    92,  -275,  1056,   164,
    -275,  -275,  -275,  1520,  1520,  -275,  -275,   640,  -275,    18,
    -275,  -275,   216,   219,  1560,   229,   227,   730,   241,   203,
     248,   250,   980,   258,  1630,  -275,  -275,  -275,  1670,   630,
     274,   276,   254,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
      37,   452,  1560,  -275,  -275,  -275,   255,   214,   220,   235,
     246,   281,   280,   291,   286,    55,  -275,  -275,   117,  -275,
    -275,  -275,   272,   273,  -275,  -275,   454,  -275,  -275,  -275,
    -275,  -275,  -275,   322,  -275,  -275,  -275,  -275,  -275,   840,
    -275,  -275,  -275,  -275,  -275,     5,  -275,    49,   231,  -275,
    -275,  -275,   277,  -275,   233,   278,   283,   284,   292,   113,
     287,  1706,  -275,  -275,  -275,  -275,  -275,    12,   113,  -275,
    1560,  -275,  -275,    53,    26,   293,   289,  -275,   279,   297,
    1560,  1560,   300,   730,  1560,   290,   549,   303,  -275,  -275,
    -275,   129,  1560,   640,  -275,    16,  -275,    36,  1560,   327,
    1020,   331,   730,  -275,  -275,   266,  1090,  1560,   267,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    1560,  -275,  1560,  1560,  1560,  1560,  1560,  1560,  1560,  1560,
    1560,  1560,  1560,  1560,  1560,  1560,  1560,  1560,  1560,  1560,
    1560,  -275,  1560,  -275,  -275,  -275,  -275,  -275,    75,  -275,
      79,  -275,   630,  -275,   268,  -275,  -275,   319,  -275,  -275,
    -275,   871,  -275,  -275,  -275,  -275,  -275,  -275,   154,  -275,
      31,  -275,  -275,   271,  1160,   149,  -275,   159,  1560,   270,
      98,    19,    77,    85,   730,  -275,    87,   329,   316,  -275,
    -275,  1230,  -275,  -275,   103,   330,  1560,  1270,  1560,   168,
     169,  -275,  -275,  1560,  -275,  -275,  1340,  -275,  -275,  -275,
     108,  -275,    14,  -275,  -275,  -275,  -275,  -275,   255,   255,
     214,   214,   220,   220,   220,   220,   235,   235,   246,   281,
     280,   291,   286,   226,  -275,  -275,  -275,   800,  -275,  -275,
     333,    54,   118,  -275,    17,  -275,  -275,   120,   335,  -275,
     325,   159,  1191,  1410,  -275,   336,  1260,  -275,    54,   352,
    -275,  -275,   730,   730,  -275,   730,  1560,  1450,   730,  -275,
    -275,  -275,   121,    34,   169,  -275,  1560,  -275,  -275,  -275,
    -275,  -275,  1560,  -275,  1560,  -275,  -275,    54,  -275,    54,
    -275,  -275,  -275,  -275,  -275,   130,  -275,   334,   298,  -275,
     146,  -275,   113,  -275,   342,  -275,  -275,   147,   730,   150,
    -275,  -275,  -275,  -275,   172,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   730,   337,  -275,   730,  -275,  -275,  -275,
    -275
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   240,   115,   125,   118,   120,   122,   119,   123,   124,
     121,   117,   116,   154,   129,   128,   243,     0,   105,   107,
       0,     0,   109,     0,   238,     0,   241,     0,   248,   104,
      47,     0,   164,     0,   102,   157,     0,   111,   113,   156,
       0,   115,   106,   107,    47,   249,   108,   242,   127,   110,
       1,     0,   239,     0,   247,     0,     0,   168,   166,   165,
       0,   103,     0,     0,     0,     0,   155,    46,     0,     0,
      34,    35,    33,     0,     0,    32,    37,     0,   214,     0,
     221,    36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    13,    11,     0,     0,
       0,     0,     2,     6,    10,     9,     7,     8,    14,     3,
      24,    54,     0,    31,    30,    56,    60,    63,    66,    71,
      74,    76,    78,    80,    82,    84,    86,    99,     0,   219,
     218,   200,     0,     0,   194,   195,     0,   216,   196,   197,
     198,   199,     5,     0,   244,   169,   167,   158,   112,     0,
       2,   189,   114,   163,   173,     0,   170,     0,     0,   160,
      54,   101,     0,   141,     0,     0,     0,     0,     0,   151,
       0,     0,   130,   132,   133,   142,   143,     0,   153,   220,
       0,    25,    26,     0,   175,     0,   257,   261,     0,   258,
       0,     0,     0,     0,     0,     0,     0,     0,   234,   235,
     236,     0,     0,     0,    28,     0,    53,    45,     0,   208,
       0,   203,     0,    20,    21,     0,     0,     0,     0,    88,
      92,    93,    89,    90,    91,    96,    98,    97,    94,    95,
       0,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   222,     0,   201,   202,   215,   217,   245,     0,   192,
       0,   161,     0,   162,     0,   172,   159,     0,   134,   135,
     136,     0,   150,   140,   126,   131,   138,   149,     0,   147,
     113,   152,     4,     0,     0,   177,   176,   178,     0,     0,
       0,     0,     0,     0,     0,   213,     0,     0,     0,   232,
     231,     0,   233,   237,     0,     0,     0,     0,     0,    42,
      43,    44,   209,     0,   205,   204,     0,   211,    19,    16,
       0,    22,     0,    18,    87,    57,    58,    59,    61,    62,
      64,    65,    68,    67,    69,    70,    72,    73,    75,    77,
      79,    81,    83,     0,   100,   246,   190,     0,   171,   174,
       0,     0,     0,   137,     0,   139,   185,     0,     0,   181,
       0,   179,     0,     0,    55,   260,     0,   251,     0,   255,
     259,   262,     0,     0,   212,     0,     0,     0,     0,    29,
      52,    50,     0,     0,    41,    40,     0,    39,   210,   206,
     207,    17,     0,    15,     0,   191,   193,     0,   145,     0,
     148,   186,   180,   182,   187,     0,   183,     0,     0,   253,
       0,   250,     0,   252,   223,   225,   226,     0,     0,     0,
     227,    51,    48,    38,     0,    23,    85,   146,   144,   188,
     184,   254,   256,     0,     0,   229,     0,    49,   224,   228,
     230
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -275,  -275,  -275,  -275,    73,   -10,  -275,  -275,   -32,    88,
    -274,  -275,   -88,    46,    47,    29,    43,   151,   140,   152,
     155,   156,  -275,   -44,   -57,  -275,   -61,   -80,   -39,    48,
    -275,    24,  -275,     0,   -59,  -275,  -275,   236,  -275,  -275,
    -275,  -275,  -275,    52,   -55,   -31,   -25,   368,   -21,  -275,
    -117,   148,  -275,  -198,   157,   153,  -142,  -275,   -84,  -275,
    -275,  -275,  -275,  -275,  -275,   -23,  -275,   305,  -181,  -275,
    -275,  -275,  -275,  -275,   416,  -275,  -275,    71,  -275,  -275,
    -275,  -275,  -275,   158
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   108,   109,   110,   320,   111,   112,   113,    45,   310,
     311,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   230,   128,   162,    16,    17,
      36,   277,    18,    30,    20,    21,   171,   172,   173,   174,
     175,   176,   278,   279,   184,    22,    38,    39,    40,    59,
     155,   156,   157,   185,   286,   287,   152,   260,   130,   131,
     132,   211,   133,   209,   134,   135,   136,   137,   138,   139,
     140,   301,   141,    23,    24,    25,    26,   158,   142,   368,
     369,   413,   188,   189
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      19,    57,    54,   195,   192,   305,   151,   259,    60,   170,
     206,    58,    67,   177,   129,   300,   183,    32,    43,    43,
      32,   161,    43,    19,   231,    32,   258,   186,   145,   186,
     370,   201,    33,    32,    32,   385,   387,   178,   146,    47,
     161,    37,    63,    43,    44,   261,   178,    48,    33,   213,
     214,    33,   262,    43,    34,   160,    33,   276,   393,    55,
     306,   252,   215,   181,   182,   283,    42,    46,   169,   284,
      49,    27,    53,    31,   160,   307,   216,   169,   422,   308,
     217,   252,    35,   249,   204,   218,   148,    28,   160,   263,
      29,    46,   151,   282,    27,    53,   264,   129,    35,   207,
     252,    35,   160,    13,   250,   187,    35,   187,   371,   295,
     423,    61,   170,    62,   272,   345,   177,   372,     3,   183,
     377,   346,   262,   281,   252,   373,   347,   375,   317,   292,
     293,    64,   252,   296,   252,    65,    43,   366,   178,    53,
     178,   304,   183,   378,   325,   326,   327,   178,   391,    44,
     252,   312,   280,   315,   352,   392,   322,   299,   399,   321,
     401,   421,   251,   285,   252,   262,   357,   262,   392,   169,
     429,   169,   178,   324,   303,   309,   252,   262,   169,     4,
       5,     6,     7,     8,     9,    10,   431,   434,   283,   343,
     436,    13,   284,   262,   252,   344,    43,   252,   362,   353,
     364,   354,   363,   169,   360,   396,   179,   307,   307,    29,
     374,   308,   386,    56,   432,    63,   437,    68,   380,   252,
     235,   236,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     161,   143,     3,   237,   238,   405,   144,   383,   147,   410,
     321,   239,   240,   241,   242,   190,   388,   355,   191,   390,
     243,   244,   285,   232,   233,   234,   194,   367,   332,   333,
     334,   335,   394,   252,   160,   193,     3,   153,   160,    32,
     196,   328,   329,   407,   330,   331,   336,   337,   414,   415,
     151,   416,   197,   198,   420,   199,   160,   202,   208,   210,
     212,   245,   246,     4,     5,     6,     7,     8,     9,    10,
     283,   356,   247,   248,   284,   417,   419,   253,   254,   161,
     265,   266,   267,   290,   268,   424,   154,     3,   398,   269,
     270,   271,   273,   288,   435,   425,   289,     4,     5,     6,
       7,     8,     9,    10,   291,   411,   294,   297,   302,   438,
     426,   313,   440,   160,   316,   318,   323,   349,   350,   187,
      69,    29,   257,    41,     3,    70,    71,    72,   376,   403,
     379,    73,    74,   397,   427,   402,   428,   412,   430,    75,
     382,   178,   439,   408,   160,    76,   339,   371,     4,     5,
       6,     7,     8,     9,    10,   433,   338,   384,    77,   340,
      53,    78,    79,   341,    80,   342,   400,   275,    66,    81,
     348,    82,   169,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     4,     5,     6,     7,     8,
       9,    10,    95,    96,    97,    11,    12,    13,   361,    52,
     358,   256,     0,    98,    99,   100,   101,   365,   102,     0,
     103,   104,   105,   106,   107,    69,     0,     0,    41,     3,
      70,    71,    72,   219,     0,     0,    73,    74,     0,     0,
       0,     0,     0,     0,    75,     0,     0,     0,     0,     0,
      76,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,     0,     0,    77,     0,    53,   255,    79,     0,    80,
       0,     0,     0,     0,    81,     0,    82,     0,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       4,     5,     6,     7,     8,     9,    10,    95,    96,    97,
      11,    12,    13,     0,     0,     0,     0,     0,    98,    99,
     100,   101,     0,   102,     0,   103,   104,   105,   106,   107,
     298,     0,     0,    41,     3,    70,    71,    72,     0,     0,
       0,    73,    74,     0,     0,     0,     0,     0,     0,    75,
       0,     0,     0,     0,     0,    76,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    77,     0,
       0,     0,    79,     0,    80,     0,     0,     0,     0,    81,
       0,     0,     0,     0,     0,     0,     0,     0,    41,     3,
       0,     0,    44,     0,    94,     4,     5,     6,     7,     8,
       9,    10,    95,    96,    97,    11,    12,    13,     0,     0,
       0,     0,     0,    98,    99,     3,     0,     0,   150,     0,
     103,   104,   105,   106,   107,     3,    70,    71,    72,     0,
       0,     0,    73,    74,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,     0,    76,     0,     0,     0,
       4,     5,     6,     7,     8,     9,    10,     0,     0,    77,
      11,    12,    13,    79,     0,     0,     0,     0,     0,     0,
      81,     0,     0,   -47,     0,     0,     4,     5,     6,     7,
       8,     9,    10,     0,     0,    94,     4,     5,     6,     7,
       8,     9,    10,    95,    96,    97,     0,     0,    13,     0,
       0,     0,     0,     0,    98,    99,     0,     0,     0,   150,
       0,   103,   104,   105,   106,   107,    70,    71,    72,     0,
       0,     0,    73,    74,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,     0,    76,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
       0,    53,     0,    79,     0,    80,     0,     0,     0,     0,
      81,     0,    82,     0,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,   100,   101,     0,   102,
      75,   103,   104,   105,   106,   107,    76,     0,     0,     0,
      50,    51,     0,     0,     2,     3,     0,     0,     0,    77,
       0,   149,   395,    79,     0,     0,    70,    71,    72,     0,
      81,     0,    73,    74,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,    94,    76,     0,     0,     0,
       0,     0,     0,    95,    96,    97,     3,     0,     0,    77,
       0,   149,     0,    79,    98,    99,     0,     0,     0,   150,
      81,   103,   104,   105,   106,   107,     4,     5,     6,     7,
       8,     9,    10,     0,     0,    94,    11,    12,    13,    14,
      15,   351,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,     0,     0,     0,   150,
      75,   103,   104,   105,   106,   107,    76,     4,     5,     6,
       7,     8,     9,    10,     0,     0,     0,     0,     0,    77,
       0,     0,     0,    79,   159,     0,     0,     0,     0,     0,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,     0,     0,     0,   150,
      75,   103,   104,   105,   106,   107,    76,     0,     0,     0,
       0,     1,     0,     0,     2,     3,     0,     0,     0,    77,
       0,     0,     0,    79,     0,   200,    70,    71,    72,     0,
      81,     0,    73,    74,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,    94,    76,     0,     0,     0,
       0,     0,     0,    95,    96,    97,     0,     0,     0,    77,
       0,     3,     0,    79,    98,    99,     0,     0,     0,   150,
      81,   103,   104,   105,   106,   107,     4,     5,     6,     7,
       8,     9,    10,     0,     0,    94,    11,    12,    13,    14,
      15,     0,     0,    95,    96,    97,    70,    71,    72,     0,
       0,   163,    73,    74,    98,    99,   164,     0,   314,   150,
      75,   103,   104,   105,   106,   107,    76,     0,     0,     0,
       0,     0,     4,     5,     6,     7,     8,     9,    10,    77,
     319,     0,     0,    79,    13,    14,    15,   165,   166,   167,
      81,     0,     0,     0,     0,   168,     0,     0,     0,    41,
       3,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,     0,     0,     0,   150,
      75,   103,   104,   105,   106,   107,    76,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,    77,
       0,     0,     0,    79,   359,     0,     0,     0,     0,     0,
      81,     4,     5,     6,     7,     8,     9,    10,     0,     0,
       0,    11,    12,    13,     0,    94,     0,     0,     0,     0,
       0,   404,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,     0,     0,     0,   150,
      75,   103,   104,   105,   106,   107,    76,     4,     5,     6,
       7,     8,     9,    10,     0,     3,     0,     0,     0,    77,
       0,     0,     0,    79,     0,    80,    70,    71,    72,     0,
      81,     0,    73,    74,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,    94,    76,     0,     0,     0,
     409,     0,     0,    95,    96,    97,     0,     0,     0,    77,
     381,     0,     0,    79,    98,    99,     0,     0,     0,   150,
      81,   103,   104,   105,   106,   107,     4,     5,     6,     7,
       8,     9,    10,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,     0,     0,     0,   150,
      75,   103,   104,   105,   106,   107,    76,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
       0,     0,     0,    79,     0,     0,     0,     0,     0,     0,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,     0,     0,   389,   150,
      75,   103,   104,   105,   106,   107,    76,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
       0,     0,     0,    79,   406,     0,    70,    71,    72,     0,
      81,     0,    73,    74,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,    94,    76,     0,     0,     0,
       0,     0,     0,    95,    96,    97,     0,     0,     0,    77,
     418,     0,     0,    79,    98,    99,     0,     0,     0,   150,
      81,   103,   104,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,     0,     0,     0,   150,
      75,   103,   104,   105,   106,   107,    76,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
       0,     0,     0,    79,     0,     0,    70,    71,    72,     0,
      81,     0,    73,    74,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,    94,    76,     0,     0,     0,
       0,     0,     0,    95,    96,    97,     0,     0,     0,    77,
       0,     0,     0,    79,    98,    99,     0,     0,     0,   150,
      81,   103,   104,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,    70,    71,    72,     0,
       0,     0,    73,    74,    98,    99,     0,     0,     0,   150,
      75,   103,   104,   105,   106,   107,    76,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   203,
       0,     0,     0,    79,     0,     0,    70,    71,    72,     0,
      81,     0,    73,    74,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,     0,    94,    76,     0,     0,     0,
       0,     0,     0,    95,    96,    97,     0,     0,     0,    77,
       0,     3,     0,   205,    98,    99,     0,     0,     0,   150,
      81,   103,   104,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,     0,     0,     0,     0,
       0,     0,     0,    95,    96,    97,     0,     0,   274,     0,
       0,   163,     0,     0,    98,    99,   164,     0,     0,   150,
       0,   103,   104,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     4,     5,     6,     7,     8,     9,    10,     0,
       0,     0,     0,     0,    13,    14,    15,   165,   166,   167,
       0,     0,     0,     0,     0,   168
};

static const yytype_int16 yycheck[] =
{
       0,    32,    25,    87,    84,   203,    63,   149,    33,    68,
      98,    32,    44,    68,    53,   196,    77,     8,    18,    19,
       8,    65,    22,    23,   112,     8,   143,    11,    59,    11,
      11,    92,    39,     8,     8,   309,   310,    68,    59,    45,
      84,    17,    11,    43,     8,    40,    77,    89,    39,    12,
      13,    39,    47,    53,    45,    65,    39,    45,    44,    89,
      44,    47,    25,    73,    74,    39,    18,    19,    68,    43,
      22,     0,    41,     2,    84,    39,    39,    77,    44,    43,
      43,    47,    89,    28,    94,    48,    62,    42,    98,    40,
      45,    43,   149,    40,    23,    41,    47,   136,    89,    99,
      47,    89,   112,    78,    49,    89,    89,    89,    89,   193,
     384,    45,   171,    47,   169,    40,   171,    40,     5,   180,
     301,    42,    47,   178,    47,    40,    47,    40,   212,   190,
     191,    39,    47,   194,    47,    43,   136,    39,   169,    41,
     171,   202,   203,    40,   232,   233,   234,   178,    40,     8,
      47,   208,   177,   210,   271,    47,   217,   196,    40,   216,
      40,    40,    45,   184,    47,    47,   283,    47,    47,   169,
      40,   171,   203,   230,    45,   207,    47,    47,   178,    66,
      67,    68,    69,    70,    71,    72,    40,    40,    39,   250,
      40,    78,    43,    47,    47,   252,   196,    47,    39,    45,
     288,    47,    43,   203,   284,   347,    42,    39,    39,    45,
     294,    43,    43,    89,   412,    11,    44,    41,   306,    47,
       6,     7,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     284,    39,     5,    23,    24,   362,    45,   308,    40,   366,
     307,    16,    17,    18,    19,    39,   313,   280,    39,   316,
      14,    15,   283,     8,     9,    10,    39,   290,   239,   240,
     241,   242,    46,    47,   284,    46,     5,    40,   288,     8,
      39,   235,   236,   363,   237,   238,   243,   244,   372,   373,
     347,   375,    89,    45,   378,    45,   306,    39,    24,    23,
      46,    20,    22,    66,    67,    68,    69,    70,    71,    72,
      39,    40,    21,    27,    43,   376,   377,    45,    45,   363,
      89,    44,    89,    44,    46,   386,    89,     5,   351,    46,
      46,    39,    45,    40,   418,   392,    47,    66,    67,    68,
      69,    70,    71,    72,    47,   368,    46,    57,    45,   433,
     394,    24,   436,   363,    23,    89,    89,    89,    39,    89,
       1,    45,    40,     4,     5,     6,     7,     8,    39,    44,
      40,    12,    13,    40,   397,    40,   399,    25,    44,    20,
     307,   412,    45,    47,   394,    26,   246,    89,    66,    67,
      68,    69,    70,    71,    72,    53,   245,   309,    39,   247,
      41,    42,    43,   248,    45,   249,   354,   171,    40,    50,
     262,    52,   412,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,   285,    23,
     283,   136,    -1,    84,    85,    86,    87,   289,    89,    -1,
      91,    92,    93,    94,    95,     1,    -1,    -1,     4,     5,
       6,     7,     8,    11,    -1,    -1,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    39,    -1,    41,    42,    43,    -1,    45,
      -1,    -1,    -1,    -1,    50,    -1,    52,    -1,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    -1,    89,    -1,    91,    92,    93,    94,    95,
       1,    -1,    -1,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,
      -1,    -1,     8,    -1,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    84,    85,     5,    -1,    -1,    89,    -1,
      91,    92,    93,    94,    95,     5,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    -1,    -1,    39,
      76,    77,    78,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    89,    -1,    -1,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    89,
      -1,    91,    92,    93,    94,    95,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,
      50,    -1,    52,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    86,    87,    -1,    89,
      20,    91,    92,    93,    94,    95,    26,    -1,    -1,    -1,
       0,     1,    -1,    -1,     4,     5,    -1,    -1,    -1,    39,
      -1,    41,    42,    43,    -1,    -1,     6,     7,     8,    -1,
      50,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    65,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     5,    -1,    -1,    39,
      -1,    41,    -1,    43,    84,    85,    -1,    -1,    -1,    89,
      50,    91,    92,    93,    94,    95,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    65,    76,    77,    78,    79,
      80,    40,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    -1,    -1,    -1,    89,
      20,    91,    92,    93,    94,    95,    26,    66,    67,    68,
      69,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    -1,    -1,    -1,    89,
      20,    91,    92,    93,    94,    95,    26,    -1,    -1,    -1,
      -1,     1,    -1,    -1,     4,     5,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    -1,    45,     6,     7,     8,    -1,
      50,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    65,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    -1,    -1,    -1,    39,
      -1,     5,    -1,    43,    84,    85,    -1,    -1,    -1,    89,
      50,    91,    92,    93,    94,    95,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    65,    76,    77,    78,    79,
      80,    -1,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    45,    12,    13,    84,    85,    50,    -1,    88,    89,
      20,    91,    92,    93,    94,    95,    26,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    39,
      40,    -1,    -1,    43,    78,    79,    80,    81,    82,    83,
      50,    -1,    -1,    -1,    -1,    89,    -1,    -1,    -1,     4,
       5,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    -1,    -1,    -1,    89,
      20,    91,    92,    93,    94,    95,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,    39,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    66,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    76,    77,    78,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    -1,    -1,    -1,    89,
      20,    91,    92,    93,    94,    95,    26,    66,    67,    68,
      69,    70,    71,    72,    -1,     5,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    -1,    45,     6,     7,     8,    -1,
      50,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    65,    26,    -1,    -1,    -1,
      40,    -1,    -1,    73,    74,    75,    -1,    -1,    -1,    39,
      40,    -1,    -1,    43,    84,    85,    -1,    -1,    -1,    89,
      50,    91,    92,    93,    94,    95,    66,    67,    68,    69,
      70,    71,    72,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    -1,    -1,    -1,    89,
      20,    91,    92,    93,    94,    95,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    -1,    -1,    88,    89,
      20,    91,    92,    93,    94,    95,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    44,    -1,     6,     7,     8,    -1,
      50,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    65,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    -1,    -1,    -1,    39,
      40,    -1,    -1,    43,    84,    85,    -1,    -1,    -1,    89,
      50,    91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    -1,    -1,    -1,    89,
      20,    91,    92,    93,    94,    95,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    -1,    -1,     6,     7,     8,    -1,
      50,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    65,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    84,    85,    -1,    -1,    -1,    89,
      50,    91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    84,    85,    -1,    -1,    -1,    89,
      20,    91,    92,    93,    94,    95,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    43,    -1,    -1,     6,     7,     8,    -1,
      50,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    65,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    -1,    -1,    -1,    39,
      -1,     5,    -1,    43,    84,    85,    -1,    -1,    -1,    89,
      50,    91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    -1,    -1,    42,    -1,
      -1,    45,    -1,    -1,    84,    85,    50,    -1,    -1,    89,
      -1,    91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,    83,
      -1,    -1,    -1,    -1,    -1,    89
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     5,    66,    67,    68,    69,    70,    71,
      72,    76,    77,    78,    79,    80,   125,   126,   129,   130,
     131,   132,   142,   170,   171,   172,   173,   174,    42,    45,
     130,   174,     8,    39,    45,    89,   127,   128,   143,   144,
     145,     4,   126,   130,     8,   105,   126,    45,    89,   126,
       0,     1,   171,    41,   162,    89,    89,   142,   145,   146,
     143,    45,    47,    11,    39,    43,   144,   105,    41,     1,
       6,     7,     8,    12,    13,    20,    26,    39,    42,    43,
      45,    50,    52,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    73,    74,    75,    84,    85,
      86,    87,    89,    91,    92,    93,    94,    95,    98,    99,
     100,   102,   103,   104,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   123,   125,
     155,   156,   157,   159,   161,   162,   163,   164,   165,   166,
     167,   169,   175,    39,    45,   142,   145,    40,   128,    41,
      89,   121,   153,    40,    89,   147,   148,   149,   174,    44,
     102,   120,   124,    45,    50,    81,    82,    83,    89,   130,
     131,   133,   134,   135,   136,   137,   138,   141,   142,    42,
      39,   102,   102,   123,   141,   150,    11,    89,   179,   180,
      39,    39,   124,    46,    39,   155,    39,    89,    45,    45,
      45,   123,    39,    39,   102,    43,   109,   130,    24,   160,
      23,   158,    46,    12,    13,    25,    39,    43,    48,    11,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
     122,   109,     8,     9,    10,     6,     7,    23,    24,    16,
      17,    18,    19,    14,    15,    20,    22,    21,    27,    28,
      49,    45,    47,    45,    45,    42,   164,    40,   147,   153,
     154,    40,    47,    40,    47,    89,    44,    89,    46,    46,
      46,    39,   141,    45,    42,   134,    45,   128,   139,   140,
     143,   141,    40,    39,    43,   145,   151,   152,    40,    47,
      44,    47,   123,   123,    46,   155,   123,    57,     1,   125,
     165,   168,    45,    45,   123,   150,    44,    39,    43,   105,
     106,   107,   121,    24,    88,   121,    23,   155,    89,    40,
     101,   121,   123,    89,   121,   109,   109,   109,   110,   110,
     111,   111,   112,   112,   112,   112,   113,   113,   114,   115,
     116,   117,   118,   123,   121,    40,    42,    47,   148,    89,
      39,    40,   147,    45,    47,   162,    40,   147,   151,    44,
     124,   152,    39,    43,   109,   180,    39,   162,   176,   177,
      11,    89,    40,    40,   155,    40,    39,   165,    40,    40,
     109,    40,   101,   123,   106,   107,    43,   107,   121,    88,
     121,    40,    47,    44,    46,    42,   153,    40,   162,    40,
     140,    40,    40,    44,    40,   147,    44,   124,    47,    40,
     147,   162,    25,   178,   155,   155,   155,   123,    40,   123,
     155,    40,    44,   107,   123,   121,   120,   162,   162,    40,
      44,    40,   150,    53,    40,   155,    40,    44,   155,    45,
     155
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    97,    98,    98,    98,    98,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   104,   104,
     104,   104,   104,   104,   104,   104,   105,   105,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   110,   110,   110,
     111,   111,   111,   112,   112,   112,   113,   113,   113,   113,
     113,   114,   114,   114,   115,   115,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   121,   121,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   123,
     123,   124,   125,   125,   125,   126,   126,   126,   126,   126,
     126,   127,   127,   128,   128,   129,   129,   129,   130,   130,
     130,   130,   130,   130,   130,   130,   131,   131,   132,   132,
     133,   133,   134,   134,   135,   135,   135,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   138,   139,   139,   140,
     141,   141,   141,   141,   142,   143,   143,   144,   144,   144,
     144,   144,   144,   144,   145,   145,   145,   145,   146,   146,
     147,   147,   148,   149,   149,   150,   150,   151,   151,   151,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   153,
     153,   153,   154,   154,   155,   155,   155,   155,   155,   155,
     155,   156,   156,   157,   158,   158,   158,   158,   159,   160,
     160,   161,   161,   161,   162,   162,   163,   163,   164,   164,
     164,   165,   165,   166,   166,   166,   167,   167,   167,   167,
     167,   168,   168,   169,   169,   169,   169,   169,   170,   170,
     170,   171,   171,   171,   171,   172,   172,   173,   173,   174,
     175,   175,   176,   177,   177,   178,   178,   179,   179,   179,
     179,   180,   180
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       4,     4,     3,     3,     3,     2,     2,     0,     3,     4,
       2,     3,     4,     2,     1,     4,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     3,     2,     1,     2,     1,     2,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     2,     1,     1,
       1,     2,     1,     1,     2,     2,     2,     3,     2,     3,
       2,     1,     1,     1,     5,     4,     5,     1,     3,     1,
       2,     1,     2,     1,     1,     2,     1,     1,     3,     4,
       3,     4,     4,     3,     1,     2,     2,     3,     1,     2,
       1,     3,     2,     1,     3,     1,     2,     1,     1,     2,
       3,     2,     3,     3,     4,     2,     3,     3,     4,     1,
       3,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     3,     3,     2,     2,
       3,     3,     4,     3,     2,     3,     1,     2,     1,     1,
       2,     1,     2,     5,     7,     5,     5,     5,     7,     6,
       7,     1,     1,     3,     2,     2,     2,     3,     1,     2,
       1,     1,     2,     1,     4,     4,     5,     2,     2,     2,
       5,     4,     2,     2,     3,     0,     2,     1,     1,     3,
       3,     1,     3
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
#line 2005 "src/parser.tab.c"
    break;

  case 3: /* primary_expression: constant  */
#line 226 "src/parser.y"
                   { 
        dbg("primary_expression -> constant");
        (yyval.node) = (yyvsp[0].node); }
#line 2013 "src/parser.tab.c"
    break;

  case 4: /* primary_expression: LROUND expression RROUND  */
#line 229 "src/parser.y"
                                   { 
        dbg("primary_expression -> ( expression )");
        (yyval.node) = (yyvsp[-1].node); }
#line 2021 "src/parser.tab.c"
    break;

  case 5: /* primary_expression: lambda_expression  */
#line 232 "src/parser.y"
                        { 
        dbg("primary_expression -> lambda_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2029 "src/parser.tab.c"
    break;

  case 6: /* constant: DECIMAL_LITERAL  */
#line 238 "src/parser.y"
                            {
          dbg("constant -> DECIMAL_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "int", "constant");
          (yyval.node) = n;
      }
#line 2039 "src/parser.tab.c"
    break;

  case 7: /* constant: CHARACTER_LITERAL  */
#line 243 "src/parser.y"
                            {
            dbg("constant -> CHARACTER_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "char", "constant");
          (yyval.node) = n;
      }
#line 2049 "src/parser.tab.c"
    break;

  case 8: /* constant: STRING_LITERAL  */
#line 248 "src/parser.y"
                            {
            dbg("constant -> STRING_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "string", "constant");
          (yyval.node) = n;
      }
#line 2059 "src/parser.tab.c"
    break;

  case 9: /* constant: EXPONENT_LITERAL  */
#line 253 "src/parser.y"
                            {
            dbg("constant -> EXPONENT_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "double", "constant");
          (yyval.node) = n;
      }
#line 2069 "src/parser.tab.c"
    break;

  case 10: /* constant: DOUBLE_LITERAL  */
#line 258 "src/parser.y"
                            {
            dbg("constant -> DOUBLE_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "double", "constant");
          (yyval.node) = n;
      }
#line 2079 "src/parser.tab.c"
    break;

  case 11: /* constant: NULLPTR  */
#line 263 "src/parser.y"
                            {
            dbg("constant -> NULLPTR");
          Node* n = new Node("0", "nullptr", "constant");
          (yyval.node) = n;
      }
#line 2089 "src/parser.tab.c"
    break;

  case 12: /* constant: TRUE  */
#line 268 "src/parser.y"
                            {
            dbg("constant -> TRUE");
          Node* n = new Node("1", "bool", "constant");
          (yyval.node) = n;
      }
#line 2099 "src/parser.tab.c"
    break;

  case 13: /* constant: FALSE  */
#line 273 "src/parser.y"
                            {
            dbg("constant -> FALSE");
          Node* n = new Node("0", "bool", "constant");
          (yyval.node) = n;
      }
#line 2109 "src/parser.tab.c"
    break;

  case 14: /* postfix_expression: primary_expression  */
#line 281 "src/parser.y"
                             { 
        dbg("postfix_expression -> primary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2117 "src/parser.tab.c"
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
#line 2148 "src/parser.tab.c"
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
#line 2177 "src/parser.tab.c"
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
#line 2206 "src/parser.tab.c"
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
#line 2235 "src/parser.tab.c"
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
#line 2260 "src/parser.tab.c"
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
#line 2285 "src/parser.tab.c"
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
#line 2310 "src/parser.tab.c"
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
#line 2327 "src/parser.tab.c"
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
#line 2344 "src/parser.tab.c"
    break;

  case 24: /* unary_expression: postfix_expression  */
#line 472 "src/parser.y"
                             { 
        dbg("unary_expression -> postfix_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2352 "src/parser.tab.c"
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
#line 2366 "src/parser.tab.c"
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
#line 2380 "src/parser.tab.c"
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
#line 2417 "src/parser.tab.c"
    break;

  case 28: /* unary_expression: SIZEOF unary_expression  */
#line 525 "src/parser.y"
                                  {
          dbg("unary_expression -> sizeof unary_expression");
          Node* n = new Node(); n->place = "sizeof"; (yyval.node) = n;
      }
#line 2426 "src/parser.tab.c"
    break;

  case 29: /* unary_expression: SIZEOF LROUND type_name RROUND  */
#line 529 "src/parser.y"
                                         {
            dbg("unary_expression -> sizeof ( type_name )");
          Node* n = new Node(); n->place = "sizeof"; (yyval.node) = n;
      }
#line 2435 "src/parser.tab.c"
    break;

  case 30: /* unary_expression: delete_expression  */
#line 533 "src/parser.y"
                            { 
        dbg("unary_expression -> delete_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2443 "src/parser.tab.c"
    break;

  case 31: /* unary_expression: new_expression  */
#line 536 "src/parser.y"
                         { 
        dbg("unary_expression -> new_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2451 "src/parser.tab.c"
    break;

  case 32: /* unary_operator: BITWISE_AND  */
#line 542 "src/parser.y"
                      { 
        dbg("unary_operator -> &");
        (yyval.str) = (yyvsp[0].str); }
#line 2459 "src/parser.tab.c"
    break;

  case 33: /* unary_operator: STAR  */
#line 545 "src/parser.y"
               { 
        dbg("unary_operator -> *");
        (yyval.str) = (yyvsp[0].str); }
#line 2467 "src/parser.tab.c"
    break;

  case 34: /* unary_operator: PLUS  */
#line 548 "src/parser.y"
               { 
        dbg("unary_operator -> +");
        (yyval.str) = (yyvsp[0].str); }
#line 2475 "src/parser.tab.c"
    break;

  case 35: /* unary_operator: MINUS  */
#line 551 "src/parser.y"
                { 
        dbg("unary_operator -> -");
        (yyval.str) = (yyvsp[0].str); }
#line 2483 "src/parser.tab.c"
    break;

  case 36: /* unary_operator: TILDE  */
#line 554 "src/parser.y"
                { 
        dbg("unary_operator -> ~");
        (yyval.str) = (yyvsp[0].str); }
#line 2491 "src/parser.tab.c"
    break;

  case 37: /* unary_operator: LOGICAL_NOT  */
#line 557 "src/parser.y"
                      { 
        dbg("unary_operator -> !");
        (yyval.str) = (yyvsp[0].str); }
#line 2499 "src/parser.tab.c"
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
#line 2512 "src/parser.tab.c"
    break;

  case 39: /* new_expression: NEW type_specifier new_declarator scalar_new_init_opt  */
#line 571 "src/parser.y"
                                                                {
          dbg("new_expression -> NEW type_specifier new_declarator scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2525 "src/parser.tab.c"
    break;

  case 40: /* new_expression: NEW type_specifier pointer_opt scalar_new_init_opt  */
#line 579 "src/parser.y"
                                                             {
            dbg("new_expression -> NEW type_specifier pointer_opt scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2538 "src/parser.tab.c"
    break;

  case 41: /* new_expression: NEW type_specifier pointer_opt new_declarator  */
#line 587 "src/parser.y"
                                                        {
            dbg("new_expression -> NEW type_specifier pointer_opt new_declarator");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2551 "src/parser.tab.c"
    break;

  case 42: /* new_expression: NEW type_specifier pointer_opt  */
#line 595 "src/parser.y"
                                         {
            dbg("new_expression -> NEW type_specifier pointer_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2564 "src/parser.tab.c"
    break;

  case 43: /* new_expression: NEW type_specifier new_declarator  */
#line 603 "src/parser.y"
                                            {
            dbg("new_expression -> NEW type_specifier new_declarator");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2577 "src/parser.tab.c"
    break;

  case 44: /* new_expression: NEW type_specifier scalar_new_init_opt  */
#line 611 "src/parser.y"
                                                 {
            dbg("new_expression -> NEW type_specifier scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2590 "src/parser.tab.c"
    break;

  case 45: /* new_expression: NEW type_specifier  */
#line 619 "src/parser.y"
                             {
            dbg("new_expression -> NEW type_specifier");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2603 "src/parser.tab.c"
    break;

  case 46: /* pointer_opt: STAR pointer_opt  */
#line 630 "src/parser.y"
                           { 
        dbg("pointer_opt -> * pointer_opt");
        (yyval.str) = strcat(strdup("*"), (yyvsp[0].str)); }
#line 2611 "src/parser.tab.c"
    break;

  case 47: /* pointer_opt: %empty  */
#line 633 "src/parser.y"
           { 
        dbg("pointer_opt -> <empty>");
        (yyval.str) = strdup(""); }
#line 2619 "src/parser.tab.c"
    break;

  case 48: /* new_declarator: LSQUARE expression RSQUARE  */
#line 639 "src/parser.y"
                                     { 
        dbg("new_declarator -> [ expression ]");
        (yyval.node) = (yyvsp[-1].node); }
#line 2627 "src/parser.tab.c"
    break;

  case 49: /* new_declarator: new_declarator LSQUARE expression RSQUARE  */
#line 642 "src/parser.y"
                                                    { 
        dbg("new_declarator -> new_declarator [ expression ]");
        (yyval.node) = (yyvsp[-1].node); }
#line 2635 "src/parser.tab.c"
    break;

  case 50: /* scalar_new_init_opt: LROUND RROUND  */
#line 648 "src/parser.y"
                        { 
        dbg("scalar_new_init_opt -> ( )");
        (yyval.node) = nullptr; }
#line 2643 "src/parser.tab.c"
    break;

  case 51: /* scalar_new_init_opt: LROUND argument_expression_list RROUND  */
#line 651 "src/parser.y"
                                                 { 
        dbg("scalar_new_init_opt -> ( argument_expression_list )");
        (yyval.node) = (yyvsp[-1].node); }
#line 2651 "src/parser.tab.c"
    break;

  case 52: /* delete_expression: DELETE LSQUARE RSQUARE cast_expression  */
#line 657 "src/parser.y"
                                                 {
          dbg("delete_expression -> DELETE [ ] cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("free " + (yyvsp[0].node)->place + ";");
          (yyval.node) = n;
      }
#line 2663 "src/parser.tab.c"
    break;

  case 53: /* delete_expression: DELETE cast_expression  */
#line 664 "src/parser.y"
                                 {
            dbg("delete_expression -> DELETE cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("free " + (yyvsp[0].node)->place + ";");
          (yyval.node) = n;
      }
#line 2675 "src/parser.tab.c"
    break;

  case 54: /* cast_expression: unary_expression  */
#line 674 "src/parser.y"
                           { 
        dbg("cast_expression -> unary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2683 "src/parser.tab.c"
    break;

  case 55: /* cast_expression: LROUND type_name RROUND cast_expression  */
#line 677 "src/parser.y"
                                                  {
            dbg("cast_expression -> ( type_name ) cast_expression");
          (yyval.node) = (yyvsp[0].node);
      }
#line 2692 "src/parser.tab.c"
    break;

  case 56: /* multiplicative_expression: cast_expression  */
#line 684 "src/parser.y"
                          { 
        dbg("multiplicative_expression -> cast_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2700 "src/parser.tab.c"
    break;

  case 57: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 687 "src/parser.y"
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
#line 2715 "src/parser.tab.c"
    break;

  case 58: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 697 "src/parser.y"
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
#line 2730 "src/parser.tab.c"
    break;

  case 59: /* multiplicative_expression: multiplicative_expression MODULUS cast_expression  */
#line 707 "src/parser.y"
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
#line 2745 "src/parser.tab.c"
    break;

  case 60: /* additive_expression: multiplicative_expression  */
#line 720 "src/parser.y"
                                    { 
        dbg("additive_expression -> multiplicative_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2753 "src/parser.tab.c"
    break;

  case 61: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 723 "src/parser.y"
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
#line 2768 "src/parser.tab.c"
    break;

  case 62: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 733 "src/parser.y"
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
#line 2783 "src/parser.tab.c"
    break;

  case 63: /* shift_expression: additive_expression  */
#line 746 "src/parser.y"
                              { 
        dbg("shift_expression -> additive_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2791 "src/parser.tab.c"
    break;

  case 64: /* shift_expression: shift_expression LEFT_SHIFT additive_expression  */
#line 749 "src/parser.y"
                                                          {
            dbg("shift_expression -> shift_expression << additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " << " + b->place + ";");
          n->type = a->type; (yyval.node) = n;
      }
#line 2805 "src/parser.tab.c"
    break;

  case 65: /* shift_expression: shift_expression RIGHT_SHIFT additive_expression  */
#line 758 "src/parser.y"
                                                           {
            dbg("shift_expression -> shift_expression >> additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " >> " + b->place + ";");
          n->type = a->type; (yyval.node) = n;
      }
#line 2819 "src/parser.tab.c"
    break;

  case 66: /* relational_expression: shift_expression  */
#line 770 "src/parser.y"
                           { 
        dbg("relational_expression -> shift_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2827 "src/parser.tab.c"
    break;

  case 67: /* relational_expression: relational_expression GREATER_THAN shift_expression  */
#line 773 "src/parser.y"
                                                              {
          dbg("relational_expression -> relational_expression > shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " > " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2839 "src/parser.tab.c"
    break;

  case 68: /* relational_expression: relational_expression LESS_THAN shift_expression  */
#line 780 "src/parser.y"
                                                           {
          dbg("relational_expression -> relational_expression < shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " < " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2851 "src/parser.tab.c"
    break;

  case 69: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 787 "src/parser.y"
                                                            {
            dbg("relational_expression -> relational_expression <= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " <= " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2863 "src/parser.tab.c"
    break;

  case 70: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 794 "src/parser.y"
                                                               {
            dbg("relational_expression -> relational_expression >= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " >= " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2875 "src/parser.tab.c"
    break;

  case 71: /* equality_expression: relational_expression  */
#line 804 "src/parser.y"
                                { 
        dbg("equality_expression -> relational_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2883 "src/parser.tab.c"
    break;

  case 72: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 807 "src/parser.y"
                                                          {
            dbg("equality_expression -> equality_expression == relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " == " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2895 "src/parser.tab.c"
    break;

  case 73: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 814 "src/parser.y"
                                                              {
            dbg("equality_expression -> equality_expression != relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " != " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2907 "src/parser.tab.c"
    break;

  case 74: /* and_expression: equality_expression  */
#line 824 "src/parser.y"
                              { 
        dbg("and_expression -> equality_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2915 "src/parser.tab.c"
    break;

  case 75: /* and_expression: and_expression BITWISE_AND equality_expression  */
#line 827 "src/parser.y"
                                                         {
            dbg("and_expression -> and_expression & equality_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " & " + b->place + ";");
          (yyval.node) = n;
      }
#line 2927 "src/parser.tab.c"
    break;

  case 76: /* exclusive_or_expression: and_expression  */
#line 837 "src/parser.y"
                         { 
        dbg("exclusive_or_expression -> and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2935 "src/parser.tab.c"
    break;

  case 77: /* exclusive_or_expression: exclusive_or_expression BITWISE_XOR and_expression  */
#line 840 "src/parser.y"
                                                             {
            dbg("exclusive_or_expression -> exclusive_or_expression ^ and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " ^ " + b->place + ";");
          (yyval.node) = n;
      }
#line 2947 "src/parser.tab.c"
    break;

  case 78: /* inclusive_or_expression: exclusive_or_expression  */
#line 850 "src/parser.y"
                                  { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2955 "src/parser.tab.c"
    break;

  case 79: /* inclusive_or_expression: inclusive_or_expression BITWISE_OR exclusive_or_expression  */
#line 853 "src/parser.y"
                                                                     {
            dbg("inclusive_or_expression -> inclusive_or_expression | exclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " | " + b->place + ";");
          (yyval.node) = n;
      }
#line 2967 "src/parser.tab.c"
    break;

  case 80: /* logical_and_expression: inclusive_or_expression  */
#line 863 "src/parser.y"
                                  { 
        dbg("logical_and_expression -> inclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2975 "src/parser.tab.c"
    break;

  case 81: /* logical_and_expression: logical_and_expression LOGICAL_AND inclusive_or_expression  */
#line 866 "src/parser.y"
                                                                     {
            dbg("logical_and_expression -> logical_and_expression && inclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " && " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2987 "src/parser.tab.c"
    break;

  case 82: /* logical_or_expression: logical_and_expression  */
#line 876 "src/parser.y"
                                 { 
        dbg("logical_or_expression -> logical_and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2995 "src/parser.tab.c"
    break;

  case 83: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 879 "src/parser.y"
                                                                  {
            dbg("logical_or_expression -> logical_or_expression || logical_and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " || " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 3007 "src/parser.tab.c"
    break;

  case 84: /* conditional_expression: logical_or_expression  */
#line 889 "src/parser.y"
                                { 
        dbg("conditional_expression -> logical_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3015 "src/parser.tab.c"
    break;

  case 85: /* conditional_expression: logical_or_expression QUESTION_MARK expression COLON conditional_expression  */
#line 892 "src/parser.y"
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
#line 3038 "src/parser.tab.c"
    break;

  case 86: /* assignment_expression: conditional_expression  */
#line 913 "src/parser.y"
                                 { 
        dbg("assignment_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3046 "src/parser.tab.c"
    break;

  case 87: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 916 "src/parser.y"
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
#line 3080 "src/parser.tab.c"
    break;

  case 88: /* assignment_operator: ASSIGN  */
#line 948 "src/parser.y"
                 { 
        dbg("assignment_operator -> =");
        (yyval.str) = (yyvsp[0].str); }
#line 3088 "src/parser.tab.c"
    break;

  case 89: /* assignment_operator: STAR_EQUAL  */
#line 951 "src/parser.y"
                     { 
        dbg("assignment_operator -> *=");
        (yyval.str) = (yyvsp[0].str); }
#line 3096 "src/parser.tab.c"
    break;

  case 90: /* assignment_operator: DIV_EQUAL  */
#line 954 "src/parser.y"
                    { 
        dbg("assignment_operator -> /=");
        (yyval.str) = (yyvsp[0].str); }
#line 3104 "src/parser.tab.c"
    break;

  case 91: /* assignment_operator: MOD_EQUAL  */
#line 957 "src/parser.y"
                    { 
        dbg("assignment_operator -> %=");
        (yyval.str) = (yyvsp[0].str); }
#line 3112 "src/parser.tab.c"
    break;

  case 92: /* assignment_operator: PLUS_EQUAL  */
#line 960 "src/parser.y"
                     { 
        dbg("assignment_operator -> +=");
        (yyval.str) = (yyvsp[0].str); }
#line 3120 "src/parser.tab.c"
    break;

  case 93: /* assignment_operator: MINUS_EQUAL  */
#line 963 "src/parser.y"
                      { 
        dbg("assignment_operator -> -=");
        (yyval.str) = (yyvsp[0].str); }
#line 3128 "src/parser.tab.c"
    break;

  case 94: /* assignment_operator: LEFT_SHIFT_EQ  */
#line 966 "src/parser.y"
                        { 
        dbg("assignment_operator -> <<=");
        (yyval.str) = (yyvsp[0].str); }
#line 3136 "src/parser.tab.c"
    break;

  case 95: /* assignment_operator: RIGHT_SHIFT_EQ  */
#line 969 "src/parser.y"
                         { 
        dbg("assignment_operator -> >>=");
        (yyval.str) = (yyvsp[0].str); }
#line 3144 "src/parser.tab.c"
    break;

  case 96: /* assignment_operator: AND_EQUAL  */
#line 972 "src/parser.y"
                    { 
        dbg("assignment_operator -> &=");
        (yyval.str) = (yyvsp[0].str); }
#line 3152 "src/parser.tab.c"
    break;

  case 97: /* assignment_operator: XOR_EQUAL  */
#line 975 "src/parser.y"
                    { 
        dbg("assignment_operator -> ^=");
        (yyval.str) = (yyvsp[0].str); }
#line 3160 "src/parser.tab.c"
    break;

  case 98: /* assignment_operator: OR_EQUAL  */
#line 978 "src/parser.y"
                   { 
        dbg("assignment_operator -> |=");
        (yyval.str) = (yyvsp[0].str); }
#line 3168 "src/parser.tab.c"
    break;

  case 99: /* expression: assignment_expression  */
#line 984 "src/parser.y"
                                { 
        dbg("expression -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3176 "src/parser.tab.c"
    break;

  case 100: /* expression: expression COMMA assignment_expression  */
#line 987 "src/parser.y"
                                                 {
            dbg("expression -> expression , assignment_expression");
          Node* n = (yyvsp[-2].node);
          Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->place = e->place;
          (yyval.node) = n;
      }
#line 3189 "src/parser.tab.c"
    break;

  case 101: /* constant_expression: conditional_expression  */
#line 998 "src/parser.y"
                                 { 
        dbg("constant_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3197 "src/parser.tab.c"
    break;

  case 102: /* declaration: declaration_specifiers SEMICOLON  */
#line 1004 "src/parser.y"
                                           {
          dbg("declaration -> declaration_specifiers ;");
          Node* n = new Node();
          (yyval.node) = n;
      }
#line 3207 "src/parser.tab.c"
    break;

  case 103: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 1009 "src/parser.y"
                                                                {
            dbg("declaration -> declaration_specifiers init_declarator_list ;");
          (yyval.node) = (yyvsp[-1].node);
      }
#line 3216 "src/parser.tab.c"
    break;

  case 104: /* declaration: error SEMICOLON  */
#line 1013 "src/parser.y"
                      {yyerrok;}
#line 3222 "src/parser.tab.c"
    break;

  case 105: /* declaration_specifiers: storage_class_specifier  */
#line 1017 "src/parser.y"
                                  { 
        dbg("declaration_specifiers -> storage_class_specifier");
        (yyval.node) = new Node(); }
#line 3230 "src/parser.tab.c"
    break;

  case 106: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 1020 "src/parser.y"
                                                         { 
        dbg("declaration_specifiers -> storage_class_specifier declaration_specifiers");
        (yyval.node) = (yyvsp[0].node); }
#line 3238 "src/parser.tab.c"
    break;

  case 107: /* declaration_specifiers: type_specifier  */
#line 1023 "src/parser.y"
                         { 
        dbg("declaration_specifiers -> type_specifier");
        lastDeclType = string((yyvsp[0].str)); (yyval.node) = new Node(); }
#line 3246 "src/parser.tab.c"
    break;

  case 108: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 1026 "src/parser.y"
                                                { 
        dbg("declaration_specifiers -> type_specifier declaration_specifiers");
        lastDeclType = string((yyvsp[-1].str)); (yyval.node) = (yyvsp[0].node); }
#line 3254 "src/parser.tab.c"
    break;

  case 109: /* declaration_specifiers: type_qualifier  */
#line 1029 "src/parser.y"
                         { 
        dbg("declaration_specifiers -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3262 "src/parser.tab.c"
    break;

  case 110: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 1032 "src/parser.y"
                                                { 
        dbg("declaration_specifiers -> type_qualifier declaration_specifiers");
        (yyval.node) = (yyvsp[0].node); }
#line 3270 "src/parser.tab.c"
    break;

  case 111: /* init_declarator_list: init_declarator  */
#line 1038 "src/parser.y"
                          { 
        dbg("init_declarator_list -> init_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3278 "src/parser.tab.c"
    break;

  case 112: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1041 "src/parser.y"
                                                     {
            dbg("init_declarator_list -> init_declarator_list , init_declarator");
          Node* n = (yyvsp[-2].node);
          n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 3289 "src/parser.tab.c"
    break;

  case 113: /* init_declarator: declarator  */
#line 1050 "src/parser.y"
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
#line 3307 "src/parser.tab.c"
    break;

  case 114: /* init_declarator: declarator ASSIGN initializer  */
#line 1063 "src/parser.y"
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
#line 3328 "src/parser.tab.c"
    break;

  case 115: /* storage_class_specifier: TYPEDEF  */
#line 1082 "src/parser.y"
                  { 
        dbg("storage_class_specifier -> TYPEDEF");
        (yyval.node) = new Node(); }
#line 3336 "src/parser.tab.c"
    break;

  case 116: /* storage_class_specifier: STATIC  */
#line 1085 "src/parser.y"
                 { 
        dbg("storage_class_specifier -> STATIC");
        (yyval.node) = new Node(); }
#line 3344 "src/parser.tab.c"
    break;

  case 117: /* storage_class_specifier: AUTO  */
#line 1088 "src/parser.y"
               { 
        dbg("storage_class_specifier -> AUTO");
        (yyval.node) = new Node(); }
#line 3352 "src/parser.tab.c"
    break;

  case 118: /* type_specifier: VOID  */
#line 1094 "src/parser.y"
                 { 
        dbg("type_specifier -> VOID");
        (yyval.str) = strdup("void"); lastDeclType = "void"; }
#line 3360 "src/parser.tab.c"
    break;

  case 119: /* type_specifier: CHAR  */
#line 1097 "src/parser.y"
                 { 
        dbg("type_specifier -> CHAR");
        (yyval.str) = strdup("char"); lastDeclType = "char"; }
#line 3368 "src/parser.tab.c"
    break;

  case 120: /* type_specifier: INT  */
#line 1100 "src/parser.y"
                 { 
        dbg("type_specifier -> INT");
        (yyval.str) = strdup("int"); lastDeclType = "int"; }
#line 3376 "src/parser.tab.c"
    break;

  case 121: /* type_specifier: LONG  */
#line 1103 "src/parser.y"
                 { 
        dbg("type_specifier -> LONG");
        (yyval.str) = strdup("long"); lastDeclType = "long"; }
#line 3384 "src/parser.tab.c"
    break;

  case 122: /* type_specifier: DOUBLE  */
#line 1106 "src/parser.y"
                 { 
        dbg("type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); lastDeclType = "double"; }
#line 3392 "src/parser.tab.c"
    break;

  case 123: /* type_specifier: BOOL  */
#line 1109 "src/parser.y"
                 { 
        dbg("type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); lastDeclType = "bool"; }
#line 3400 "src/parser.tab.c"
    break;

  case 124: /* type_specifier: STRING  */
#line 1112 "src/parser.y"
                 { 
        dbg("type_specifier -> STRING");
        (yyval.str) = strdup("string"); lastDeclType = "string"; }
#line 3408 "src/parser.tab.c"
    break;

  case 125: /* type_specifier: TYPE_NAME  */
#line 1115 "src/parser.y"
                    { 
        dbg("type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str); lastDeclType = string((yyvsp[0].str)); }
#line 3416 "src/parser.tab.c"
    break;

  case 126: /* struct_or_class_specifier: struct_or_class IDENTIFIER LCURLY struct_or_class_member_list RCURLY  */
#line 1121 "src/parser.y"
                                                                               { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        Node* n = new Node(); (yyval.node) = n; }
#line 3424 "src/parser.tab.c"
    break;

  case 127: /* struct_or_class_specifier: struct_or_class IDENTIFIER  */
#line 1124 "src/parser.y"
                                     { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER");
        Node* n = new Node(); (yyval.node) = n; }
#line 3432 "src/parser.tab.c"
    break;

  case 128: /* struct_or_class: STRUCT  */
#line 1130 "src/parser.y"
                 { 
        dbg("struct_or_class -> STRUCT");
        (yyval.node) = new Node(); }
#line 3440 "src/parser.tab.c"
    break;

  case 129: /* struct_or_class: CLASS  */
#line 1133 "src/parser.y"
                { 
        dbg("struct_or_class -> CLASS");
        (yyval.node) = new Node(); }
#line 3448 "src/parser.tab.c"
    break;

  case 130: /* struct_or_class_member_list: struct_or_class_member  */
#line 1139 "src/parser.y"
                                 { 
        dbg("struct_or_class_member_list -> struct_or_class_member");
        (yyval.node) = (yyvsp[0].node); }
#line 3456 "src/parser.tab.c"
    break;

  case 131: /* struct_or_class_member_list: struct_or_class_member_list struct_or_class_member  */
#line 1142 "src/parser.y"
                                                             { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        Node* n = (yyvsp[-1].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; }
#line 3466 "src/parser.tab.c"
    break;

  case 132: /* struct_or_class_member: access_specifier_label  */
#line 1150 "src/parser.y"
                                 { 
        dbg("struct_or_class_member -> access_specifier_label");
        (yyval.node) = (yyvsp[0].node); }
#line 3474 "src/parser.tab.c"
    break;

  case 133: /* struct_or_class_member: member_declaration  */
#line 1153 "src/parser.y"
                             { 
        dbg("struct_or_class_member -> member_declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 3482 "src/parser.tab.c"
    break;

  case 134: /* access_specifier_label: PUBLIC COLON  */
#line 1159 "src/parser.y"
                       { 
        dbg("access_specifier_label -> PUBLIC :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3490 "src/parser.tab.c"
    break;

  case 135: /* access_specifier_label: PRIVATE COLON  */
#line 1162 "src/parser.y"
                        { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3498 "src/parser.tab.c"
    break;

  case 136: /* access_specifier_label: PROTECTED COLON  */
#line 1165 "src/parser.y"
                          { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3506 "src/parser.tab.c"
    break;

  case 137: /* member_declaration: specifier_qualifier_list struct_declarator_list SEMICOLON  */
#line 1171 "src/parser.y"
                                                                    { 
        dbg("member_declaration -> specifier_qualifier_list struct_declarator_list ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3514 "src/parser.tab.c"
    break;

  case 138: /* member_declaration: specifier_qualifier_list SEMICOLON  */
#line 1174 "src/parser.y"
                                             { 
        dbg("member_declaration -> specifier_qualifier_list ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3522 "src/parser.tab.c"
    break;

  case 139: /* member_declaration: specifier_qualifier_list declarator compound_statement  */
#line 1177 "src/parser.y"
                                                                 { 
        dbg("member_declaration -> specifier_qualifier_list declarator compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 3530 "src/parser.tab.c"
    break;

  case 140: /* member_declaration: struct_or_class_specifier SEMICOLON  */
#line 1180 "src/parser.y"
                                              { 
        dbg("member_declaration -> struct_or_class_specifier ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3538 "src/parser.tab.c"
    break;

  case 141: /* member_declaration: SEMICOLON  */
#line 1183 "src/parser.y"
                    { 
        dbg("member_declaration -> ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3546 "src/parser.tab.c"
    break;

  case 142: /* member_declaration: constructor_definition  */
#line 1186 "src/parser.y"
                                 { 
        dbg("member_declaration -> constructor_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 3554 "src/parser.tab.c"
    break;

  case 143: /* member_declaration: destructor_definition  */
#line 1189 "src/parser.y"
                                { 
        dbg("member_declaration -> destructor_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 3562 "src/parser.tab.c"
    break;

  case 144: /* constructor_definition: IDENTIFIER LROUND parameter_list RROUND compound_statement  */
#line 1195 "src/parser.y"
                                                                     {
        dbg("constructor_definition -> IDENTIFIER ( parameter_list ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3571 "src/parser.tab.c"
    break;

  case 145: /* constructor_definition: IDENTIFIER LROUND RROUND compound_statement  */
#line 1199 "src/parser.y"
                                                      {
        dbg("constructor_definition -> IDENTIFIER ( ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3580 "src/parser.tab.c"
    break;

  case 146: /* destructor_definition: TILDE IDENTIFIER LROUND RROUND compound_statement  */
#line 1206 "src/parser.y"
                                                            {
        dbg("destructor_definition -> ~ IDENTIFIER ( ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3589 "src/parser.tab.c"
    break;

  case 147: /* struct_declarator_list: struct_declarator  */
#line 1213 "src/parser.y"
                            { 
        dbg("struct_declarator_list -> struct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3597 "src/parser.tab.c"
    break;

  case 148: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1216 "src/parser.y"
                                                         { 
        dbg("struct_declarator_list -> struct_declarator_list , struct_declarator");
        Node* n = (yyvsp[-2].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; }
#line 3607 "src/parser.tab.c"
    break;

  case 149: /* struct_declarator: init_declarator  */
#line 1224 "src/parser.y"
                          { 
        dbg("struct_declarator -> init_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3615 "src/parser.tab.c"
    break;

  case 150: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1230 "src/parser.y"
                                                  { 
        dbg("specifier_qualifier_list -> type_specifier specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3623 "src/parser.tab.c"
    break;

  case 151: /* specifier_qualifier_list: type_specifier  */
#line 1233 "src/parser.y"
                         { 
        dbg("specifier_qualifier_list -> type_specifier");
        (yyval.node) = new Node(); }
#line 3631 "src/parser.tab.c"
    break;

  case 152: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1236 "src/parser.y"
                                                  { 
        dbg("specifier_qualifier_list -> type_qualifier specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3639 "src/parser.tab.c"
    break;

  case 153: /* specifier_qualifier_list: type_qualifier  */
#line 1239 "src/parser.y"
                         { 
        dbg("specifier_qualifier_list -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3647 "src/parser.tab.c"
    break;

  case 154: /* type_qualifier: CONST  */
#line 1245 "src/parser.y"
                { 
        dbg("type_qualifier -> CONST");
        (yyval.node) = new Node(); }
#line 3655 "src/parser.tab.c"
    break;

  case 155: /* declarator: pointer direct_declarator  */
#line 1251 "src/parser.y"
                                    { 
        dbg("declarator -> pointer direct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3663 "src/parser.tab.c"
    break;

  case 156: /* declarator: direct_declarator  */
#line 1254 "src/parser.y"
                            { 
        dbg("declarator -> direct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3671 "src/parser.tab.c"
    break;

  case 157: /* direct_declarator: IDENTIFIER  */
#line 1260 "src/parser.y"
                     {
            dbg("direct_declarator -> IDENTIFIER");
          Node* n = new Node();
          n->place = string((yyvsp[0].str));
          (yyval.node) = n;
      }
#line 3682 "src/parser.tab.c"
    break;

  case 158: /* direct_declarator: LROUND declarator RROUND  */
#line 1266 "src/parser.y"
                                   { 
        dbg("direct_declarator -> ( declarator )");
        (yyval.node) = (yyvsp[-1].node); }
#line 3690 "src/parser.tab.c"
    break;

  case 159: /* direct_declarator: direct_declarator LSQUARE constant_expression RSQUARE  */
#line 1269 "src/parser.y"
                                                                { 
        dbg("direct_declarator -> direct_declarator [ constant_expression ]");
        (yyval.node) = (yyvsp[-3].node); }
#line 3698 "src/parser.tab.c"
    break;

  case 160: /* direct_declarator: direct_declarator LSQUARE RSQUARE  */
#line 1272 "src/parser.y"
                                            { 
        dbg("direct_declarator -> direct_declarator [ ]");
        (yyval.node) = (yyvsp[-2].node); }
#line 3706 "src/parser.tab.c"
    break;

  case 161: /* direct_declarator: direct_declarator LROUND parameter_list RROUND  */
#line 1275 "src/parser.y"
                                                         { 
        dbg("direct_declarator -> direct_declarator ( parameter_list )");
        (yyval.node) = (yyvsp[-3].node); }
#line 3714 "src/parser.tab.c"
    break;

  case 162: /* direct_declarator: direct_declarator LROUND identifier_list RROUND  */
#line 1278 "src/parser.y"
                                                          { 
        dbg("direct_declarator -> direct_declarator ( identifier_list )");
        (yyval.node) = (yyvsp[-3].node); }
#line 3722 "src/parser.tab.c"
    break;

  case 163: /* direct_declarator: direct_declarator LROUND RROUND  */
#line 1281 "src/parser.y"
                                          { 
        dbg("direct_declarator -> direct_declarator ( )");
        (yyval.node) = (yyvsp[-2].node); }
#line 3730 "src/parser.tab.c"
    break;

  case 164: /* pointer: STAR  */
#line 1287 "src/parser.y"
               { 
        dbg("pointer -> *");
        (yyval.node) = new Node(); }
#line 3738 "src/parser.tab.c"
    break;

  case 165: /* pointer: STAR type_qualifier_list  */
#line 1290 "src/parser.y"
                                   { 
        dbg("pointer -> * type_qualifier_list");
        (yyval.node) = new Node(); }
#line 3746 "src/parser.tab.c"
    break;

  case 166: /* pointer: STAR pointer  */
#line 1293 "src/parser.y"
                       { 
        dbg("pointer -> * pointer");
        (yyval.node) = new Node(); }
#line 3754 "src/parser.tab.c"
    break;

  case 167: /* pointer: STAR type_qualifier_list pointer  */
#line 1296 "src/parser.y"
                                           { 
        dbg("pointer -> * type_qualifier_list pointer");
        (yyval.node) = new Node(); }
#line 3762 "src/parser.tab.c"
    break;

  case 168: /* type_qualifier_list: type_qualifier  */
#line 1302 "src/parser.y"
                         { 
        dbg("type_qualifier_list -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3770 "src/parser.tab.c"
    break;

  case 169: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1305 "src/parser.y"
                                             { 
        dbg("type_qualifier_list -> type_qualifier_list type_qualifier");
        (yyval.node) = new Node(); }
#line 3778 "src/parser.tab.c"
    break;

  case 170: /* parameter_list: parameter_declaration  */
#line 1311 "src/parser.y"
                                { 
            dbg("parameter_list -> parameter_declaration");
            (yyval.node) = (yyvsp[0].node); 
        }
#line 3787 "src/parser.tab.c"
    break;

  case 171: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1316 "src/parser.y"
        {
            dbg("parameter_list -> parameter_list , parameter_declaration");
            Node* n = (yyvsp[-2].node);
            n->syn.insert(n->syn.end(), (yyvsp[0].node)->syn.begin(), (yyvsp[0].node)->syn.end()); 
            (yyval.node) = n;
        }
#line 3798 "src/parser.tab.c"
    break;

  case 172: /* parameter_declaration: return_type IDENTIFIER  */
#line 1326 "src/parser.y"
        {
            dbg("parameter_declaration -> return_type IDENTIFIER");
            Node* n = new Node();
            n->syn.push_back(string((yyvsp[-1].str))); 
            n->syn.push_back(string((yyvsp[0].str)));
            (yyval.node) = n;
        }
#line 3810 "src/parser.tab.c"
    break;

  case 173: /* identifier_list: IDENTIFIER  */
#line 1336 "src/parser.y"
                     { 
        dbg("identifier_list -> IDENTIFIER");
        (yyval.node) = nullptr; }
#line 3818 "src/parser.tab.c"
    break;

  case 174: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 1339 "src/parser.y"
                                           { 
        dbg("identifier_list -> identifier_list , IDENTIFIER");
        (yyval.node) = nullptr; }
#line 3826 "src/parser.tab.c"
    break;

  case 175: /* type_name: specifier_qualifier_list  */
#line 1345 "src/parser.y"
                                   { 
        dbg("type_name -> specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3834 "src/parser.tab.c"
    break;

  case 176: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1348 "src/parser.y"
                                                       { 
        dbg("type_name -> specifier_qualifier_list abstract_declarator");
        (yyval.node) = new Node(); }
#line 3842 "src/parser.tab.c"
    break;

  case 177: /* abstract_declarator: pointer  */
#line 1354 "src/parser.y"
                  { 
        dbg("abstract_declarator -> pointer");
        (yyval.node) = new Node(); }
#line 3850 "src/parser.tab.c"
    break;

  case 178: /* abstract_declarator: direct_abstract_declarator  */
#line 1357 "src/parser.y"
                                     { 
        dbg("abstract_declarator -> direct_abstract_declarator");
        (yyval.node) = new Node(); }
#line 3858 "src/parser.tab.c"
    break;

  case 179: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1360 "src/parser.y"
                                             { 
        dbg("abstract_declarator -> pointer direct_abstract_declarator");
        (yyval.node) = new Node(); }
#line 3866 "src/parser.tab.c"
    break;

  case 180: /* direct_abstract_declarator: LROUND abstract_declarator RROUND  */
#line 1366 "src/parser.y"
                                            { 
        dbg("direct_abstract_declarator -> ( abstract_declarator )");
        (yyval.node) = new Node(); }
#line 3874 "src/parser.tab.c"
    break;

  case 181: /* direct_abstract_declarator: LSQUARE RSQUARE  */
#line 1369 "src/parser.y"
                          { 
        dbg("direct_abstract_declarator -> [ ]");
        (yyval.node) = new Node(); }
#line 3882 "src/parser.tab.c"
    break;

  case 182: /* direct_abstract_declarator: LSQUARE constant_expression RSQUARE  */
#line 1372 "src/parser.y"
                                              { 
        dbg("direct_abstract_declarator -> [ constant_expression ]");
        (yyval.node) = new Node(); }
#line 3890 "src/parser.tab.c"
    break;

  case 183: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE RSQUARE  */
#line 1375 "src/parser.y"
                                                     { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator [ ]");
        (yyval.node) = new Node(); }
#line 3898 "src/parser.tab.c"
    break;

  case 184: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression RSQUARE  */
#line 1378 "src/parser.y"
                                                                         { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator [ constant_expression ]");
        (yyval.node) = new Node(); }
#line 3906 "src/parser.tab.c"
    break;

  case 185: /* direct_abstract_declarator: LROUND RROUND  */
#line 1381 "src/parser.y"
                        { 
        dbg("direct_abstract_declarator -> ( )");
        (yyval.node) = new Node(); }
#line 3914 "src/parser.tab.c"
    break;

  case 186: /* direct_abstract_declarator: LROUND parameter_list RROUND  */
#line 1384 "src/parser.y"
                                       { 
        dbg("direct_abstract_declarator -> ( parameter_list )");
        (yyval.node) = new Node(); }
#line 3922 "src/parser.tab.c"
    break;

  case 187: /* direct_abstract_declarator: direct_abstract_declarator LROUND RROUND  */
#line 1387 "src/parser.y"
                                                   { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator ( )");
        (yyval.node) = new Node(); }
#line 3930 "src/parser.tab.c"
    break;

  case 188: /* direct_abstract_declarator: direct_abstract_declarator LROUND parameter_list RROUND  */
#line 1390 "src/parser.y"
                                                                  { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator ( parameter_list )");
        (yyval.node) = new Node(); }
#line 3938 "src/parser.tab.c"
    break;

  case 189: /* initializer: assignment_expression  */
#line 1396 "src/parser.y"
                                { 
        dbg("initializer -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3946 "src/parser.tab.c"
    break;

  case 190: /* initializer: LCURLY initializer_list RCURLY  */
#line 1399 "src/parser.y"
                                         { 
        dbg("initializer -> { initializer_list }");
        (yyval.node) = (yyvsp[-1].node); }
#line 3954 "src/parser.tab.c"
    break;

  case 191: /* initializer: LCURLY initializer_list COMMA RCURLY  */
#line 1402 "src/parser.y"
                                               { 
        dbg("initializer -> { initializer_list , }");
        (yyval.node) = (yyvsp[-2].node); }
#line 3962 "src/parser.tab.c"
    break;

  case 192: /* initializer_list: initializer  */
#line 1408 "src/parser.y"
                      { 
        dbg("initializer_list -> initializer");
        (yyval.node) = (yyvsp[0].node); }
#line 3970 "src/parser.tab.c"
    break;

  case 193: /* initializer_list: initializer_list COMMA initializer  */
#line 1411 "src/parser.y"
                                             {
            dbg("initializer_list -> initializer_list , initializer");
          Node* n = (yyvsp[-2].node); n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); (yyval.node) = n;
      }
#line 3979 "src/parser.tab.c"
    break;

  case 194: /* statement: labeled_statement  */
#line 1418 "src/parser.y"
                            { 
        dbg("statement -> labeled_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3987 "src/parser.tab.c"
    break;

  case 195: /* statement: compound_statement  */
#line 1421 "src/parser.y"
                             { 
        dbg("statement -> compound_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3995 "src/parser.tab.c"
    break;

  case 196: /* statement: expression_statement  */
#line 1424 "src/parser.y"
                               { 
        dbg("statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4003 "src/parser.tab.c"
    break;

  case 197: /* statement: selection_statement  */
#line 1427 "src/parser.y"
                              { 
        dbg("statement -> selection_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4011 "src/parser.tab.c"
    break;

  case 198: /* statement: iteration_statement  */
#line 1430 "src/parser.y"
                              { 
        dbg("statement -> iteration_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4019 "src/parser.tab.c"
    break;

  case 199: /* statement: jump_statement  */
#line 1433 "src/parser.y"
                         { 
        dbg("statement -> jump_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4027 "src/parser.tab.c"
    break;

  case 200: /* statement: io_statement  */
#line 1436 "src/parser.y"
                       { 
        dbg("statement -> io_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4035 "src/parser.tab.c"
    break;

  case 201: /* io_statement: cout_expression SEMICOLON  */
#line 1442 "src/parser.y"
                                { 
        dbg("io_statement -> cout_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4043 "src/parser.tab.c"
    break;

  case 202: /* io_statement: cin_expression SEMICOLON  */
#line 1445 "src/parser.y"
                                { 
        dbg("io_statement -> cin_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4051 "src/parser.tab.c"
    break;

  case 203: /* cout_expression: COUT insertion_list  */
#line 1451 "src/parser.y"
                          { 
        dbg("cout_expression -> COUT insertion_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4059 "src/parser.tab.c"
    break;

  case 204: /* insertion_list: LEFT_SHIFT assignment_expression  */
#line 1457 "src/parser.y"
                                       {
          dbg("insertion_list -> LEFT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node);
          Node* n = new Node();
          n->code = e->code; n->code.push_back("print " + e->place + ";"); (yyval.node) = n;
      }
#line 4070 "src/parser.tab.c"
    break;

  case 205: /* insertion_list: LEFT_SHIFT ENDL  */
#line 1463 "src/parser.y"
                          {
            dbg("insertion_list -> LEFT_SHIFT ENDL");
          Node* n = new Node();
          n->code.push_back("print endl;"); (yyval.node) = n;
      }
#line 4080 "src/parser.tab.c"
    break;

  case 206: /* insertion_list: insertion_list LEFT_SHIFT ENDL  */
#line 1468 "src/parser.y"
                                         {
            dbg("insertion_list -> insertion_list LEFT_SHIFT ENDL");
          Node* n = (yyvsp[-2].node); n->code.push_back("print endl;"); (yyval.node) = n;
      }
#line 4089 "src/parser.tab.c"
    break;

  case 207: /* insertion_list: insertion_list LEFT_SHIFT assignment_expression  */
#line 1472 "src/parser.y"
                                                          {
            dbg("insertion_list -> insertion_list LEFT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("print " + e->place + ";"); (yyval.node) = n;
      }
#line 4100 "src/parser.tab.c"
    break;

  case 208: /* cin_expression: CIN extraction_list  */
#line 1481 "src/parser.y"
                          { 
        dbg("cin_expression -> CIN extraction_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4108 "src/parser.tab.c"
    break;

  case 209: /* extraction_list: RIGHT_SHIFT assignment_expression  */
#line 1487 "src/parser.y"
                                        {
            dbg("extraction_list -> RIGHT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node); Node* n = new Node();
          n->code = e->code; n->code.push_back("read " + e->place + ";"); (yyval.node) = n;
      }
#line 4118 "src/parser.tab.c"
    break;

  case 210: /* extraction_list: extraction_list RIGHT_SHIFT assignment_expression  */
#line 1492 "src/parser.y"
                                                        {
            dbg("extraction_list -> extraction_list RIGHT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("read " + e->place + ";"); (yyval.node) = n;
      }
#line 4129 "src/parser.tab.c"
    break;

  case 211: /* labeled_statement: IDENTIFIER COLON statement  */
#line 1501 "src/parser.y"
                                     {
          dbg("labeled_statement -> IDENTIFIER : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string((yyvsp[-2].str)) + ":");
          (yyval.node) = s;
      }
#line 4140 "src/parser.tab.c"
    break;

  case 212: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1507 "src/parser.y"
                                                   {
            dbg("labeled_statement -> CASE constant_expression : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string("case ") + (yyvsp[-2].node)->place + ":");
          (yyval.node) = s;
      }
#line 4151 "src/parser.tab.c"
    break;

  case 213: /* labeled_statement: DEFAULT COLON statement  */
#line 1513 "src/parser.y"
                                  {
            dbg("labeled_statement -> DEFAULT : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string("default:"));
          (yyval.node) = s;
      }
#line 4162 "src/parser.tab.c"
    break;

  case 214: /* compound_statement: LCURLY RCURLY  */
#line 1522 "src/parser.y"
                        {
            dbg("compound_statement -> { }");
          pushScope();
          Node* n = new Node();
          popScope();
          (yyval.node) = n;
      }
#line 4174 "src/parser.tab.c"
    break;

  case 215: /* compound_statement: LCURLY statement_list RCURLY  */
#line 1529 "src/parser.y"
                                       {
            dbg("compound_statement -> { statement_list }");
          pushScope();
          Node* n = (yyvsp[-1].node);
          popScope();
          (yyval.node) = n;
      }
#line 4186 "src/parser.tab.c"
    break;

  case 216: /* statement_list: block_item  */
#line 1539 "src/parser.y"
                     { 
        dbg("statement_list -> block_item");
        (yyval.node) = (yyvsp[0].node); }
#line 4194 "src/parser.tab.c"
    break;

  case 217: /* statement_list: statement_list block_item  */
#line 1542 "src/parser.y"
                                    {
            dbg("statement_list -> statement_list block_item");
          Node* n = (yyvsp[-1].node);
          if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 4205 "src/parser.tab.c"
    break;

  case 218: /* block_item: statement  */
#line 1551 "src/parser.y"
                { 
        dbg("block_item -> statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4213 "src/parser.tab.c"
    break;

  case 219: /* block_item: declaration  */
#line 1554 "src/parser.y"
                  { 
        dbg("block_item -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4221 "src/parser.tab.c"
    break;

  case 220: /* block_item: error RCURLY  */
#line 1557 "src/parser.y"
                   { yyerrok;}
#line 4227 "src/parser.tab.c"
    break;

  case 221: /* expression_statement: SEMICOLON  */
#line 1561 "src/parser.y"
                    { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4235 "src/parser.tab.c"
    break;

  case 222: /* expression_statement: expression SEMICOLON  */
#line 1564 "src/parser.y"
                               { 
        dbg("expression_statement -> expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4243 "src/parser.tab.c"
    break;

  case 223: /* selection_statement: IF LROUND expression RROUND statement  */
#line 1570 "src/parser.y"
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
#line 4259 "src/parser.tab.c"
    break;

  case 224: /* selection_statement: IF LROUND expression RROUND statement ELSE statement  */
#line 1581 "src/parser.y"
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
#line 4278 "src/parser.tab.c"
    break;

  case 225: /* selection_statement: SWITCH LROUND expression RROUND statement  */
#line 1595 "src/parser.y"
                                                    {
            dbg("selection_statement -> SWITCH ( expression ) statement");
          Node* n = (yyvsp[0].node); (yyval.node) = n;
      }
#line 4287 "src/parser.tab.c"
    break;

  case 226: /* iteration_statement: WHILE LROUND expression RROUND statement  */
#line 1602 "src/parser.y"
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
#line 4305 "src/parser.tab.c"
    break;

  case 227: /* iteration_statement: UNTIL LROUND expression RROUND statement  */
#line 1615 "src/parser.y"
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
#line 4321 "src/parser.tab.c"
    break;

  case 228: /* iteration_statement: DO statement WHILE LROUND expression RROUND SEMICOLON  */
#line 1626 "src/parser.y"
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
#line 4337 "src/parser.tab.c"
    break;

  case 229: /* iteration_statement: FOR LROUND for_init_statement expression_statement RROUND statement  */
#line 1637 "src/parser.y"
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
#line 4358 "src/parser.tab.c"
    break;

  case 230: /* iteration_statement: FOR LROUND for_init_statement expression_statement expression RROUND statement  */
#line 1653 "src/parser.y"
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
#line 4380 "src/parser.tab.c"
    break;

  case 231: /* for_init_statement: expression_statement  */
#line 1673 "src/parser.y"
                               { 
        dbg("for_init_statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4388 "src/parser.tab.c"
    break;

  case 232: /* for_init_statement: declaration  */
#line 1676 "src/parser.y"
                      { 
        dbg("for_init_statement -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4396 "src/parser.tab.c"
    break;

  case 233: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 1682 "src/parser.y"
                                    {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string((yyvsp[-1].str)) + ";");
          (yyval.node) = n;
      }
#line 4407 "src/parser.tab.c"
    break;

  case 234: /* jump_statement: CONTINUE SEMICOLON  */
#line 1688 "src/parser.y"
                             {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); n->code.push_back("continue;"); (yyval.node) = n;
      }
#line 4416 "src/parser.tab.c"
    break;

  case 235: /* jump_statement: BREAK SEMICOLON  */
#line 1692 "src/parser.y"
                          {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); n->code.push_back("break;"); (yyval.node) = n;
      }
#line 4425 "src/parser.tab.c"
    break;

  case 236: /* jump_statement: RETURN SEMICOLON  */
#line 1696 "src/parser.y"
                           {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); n->code.push_back("return;"); (yyval.node) = n;
      }
#line 4434 "src/parser.tab.c"
    break;

  case 237: /* jump_statement: RETURN expression SEMICOLON  */
#line 1700 "src/parser.y"
                                      {
            dbg("jump_statement -> RETURN expression ;");
          Node* expr = (yyvsp[-1].node);
          Node* n = new Node();
          n->code = expr->code;
          n->code.push_back("return " + expr->place + ";");
          (yyval.node) = n;
      }
#line 4447 "src/parser.tab.c"
    break;

  case 238: /* translation_unit: external_declaration  */
#line 1712 "src/parser.y"
                               { 
        dbg("translation_unit -> external_declaration");
        finalRoot = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 4455 "src/parser.tab.c"
    break;

  case 239: /* translation_unit: translation_unit external_declaration  */
#line 1715 "src/parser.y"
                                                {
            dbg("translation_unit -> translation_unit external_declaration");
          Node* a = (yyvsp[-1].node); Node* b = (yyvsp[0].node);
          if (a) { 
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; (yyval.node) = a; }
          else { finalRoot = b; (yyval.node) = b; }
      }
#line 4468 "src/parser.tab.c"
    break;

  case 240: /* translation_unit: error  */
#line 1723 "src/parser.y"
            { yyerrok;}
#line 4474 "src/parser.tab.c"
    break;

  case 241: /* external_declaration: function_definition  */
#line 1728 "src/parser.y"
                              { 
        dbg("external_declaration -> function_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 4482 "src/parser.tab.c"
    break;

  case 242: /* external_declaration: struct_or_class_specifier SEMICOLON  */
#line 1731 "src/parser.y"
                                              { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4490 "src/parser.tab.c"
    break;

  case 243: /* external_declaration: declaration  */
#line 1734 "src/parser.y"
                      {
        dbg("external_declaration -> declaration");
         (yyval.node) = (yyvsp[0].node); }
#line 4498 "src/parser.tab.c"
    break;

  case 244: /* external_declaration: TYPEDEF return_type IDENTIFIER SEMICOLON  */
#line 1737 "src/parser.y"
                                               {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string((yyvsp[-1].str))] = typeSize[string((yyvsp[-2].str))];
        (yyval.node) = new Node();
        }
#line 4508 "src/parser.tab.c"
    break;

  case 245: /* function_header: return_type IDENTIFIER LROUND RROUND  */
#line 1746 "src/parser.y"
        {
            dbg("function_definition -> return_type direct_declarator compound_statement");
            string fname = string((yyvsp[-2].str));
            if (funcTable.find(fname) != funcTable.end()){
                yyerror("Function redeclaration: " + fname);
            }
            
            if(string((yyvsp[-3].str)) == "void")
            {
                funcTable[fname].returnType = "void";
                funcTable[fname].hasReturn = false;
            }
            else
            {
                funcTable[fname].returnType = string((yyvsp[-3].str)); 
                funcTable[fname].hasReturn = true;
            }
                       
            funcTable[fname].paramCount = 0;
            currentFunction = fname;
            localTemp = 0; localLabel = 0;
            Node* n = new Node();
            n->code.push_back(fname + ":");
            pushScope(); 
            (yyval.node) = n;
        }
#line 4539 "src/parser.tab.c"
    break;

  case 246: /* function_header: return_type IDENTIFIER LROUND parameter_list RROUND  */
#line 1774 "src/parser.y"
        {
            dbg("function_definition -> return_type IDENTIFIER ( parameter_list ) compound_statement");
            string fname = string((yyvsp[-3].str));
            if (funcTable.find(fname) != funcTable.end()){
                yyerror("Function redeclaration: " + fname);
            }
            
            if(string((yyvsp[-4].str)) == "void")
            {
                funcTable[fname].returnType = "void";
                funcTable[fname].hasReturn = false;
            }
            else
            {
                funcTable[fname].returnType = string((yyvsp[-4].str)); 
                funcTable[fname].hasReturn = true;
            }
            // dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");
                       
            funcTable[fname].paramCount = (yyvsp[-1].node)->syn.size()/2;
            dbg("--------Function '" + fname + "' with " + to_string(funcTable[fname].paramCount) + " parameters declared.");

            for (int i = 0; i < (yyvsp[-1].node)->syn.size(); i += 2)
            {
                funcTable[fname].paramTypes.push_back((yyvsp[-1].node)->syn[i]);
                // dbg("Parameter: " + $4->syn[i+1] + " of type " + $4->syn[i]);
            }
            
            currentFunction = fname;
            localTemp = 0; localLabel = 0;
            Node* n = new Node();
            
            n->code.push_back(fname + ":");
            
            // Declare parameters in the new scope
            pushScope(); 
            for (int i = 1; i < (yyvsp[-1].node)->syn.size(); i += 2) 
            {
                string pname = (yyvsp[-1].node)->syn[i];
                string ptype = (yyvsp[-1].node)->syn[i-1]; // Parameter type information can be added if needed
                bool ok = declareSymbol(pname, ptype);
                
                if (!ok) {
                    yyerror("Duplicate parameter name '" + pname + "' in function '" + fname + "'.");
                }
            }
            (yyval.node) = n;
        }
#line 4592 "src/parser.tab.c"
    break;

  case 247: /* function_definition: function_header compound_statement  */
#line 1825 "src/parser.y"
                                        {
            dbg("function_definition -> function_header compound_statement");
            Node* n = (yyvsp[-1].node);
            if ((yyvsp[0].node)) { 
                n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
            }
            popScope(); 
            finalRoot = n;
            currentFunction = "global";
            (yyval.node) = n;
        }
#line 4608 "src/parser.tab.c"
    break;

  case 248: /* function_definition: error RCURLY  */
#line 1836 "src/parser.y"
                   { yyerrok;}
#line 4614 "src/parser.tab.c"
    break;

  case 249: /* return_type: type_specifier pointer_opt  */
#line 1840 "src/parser.y"
                                 { 
            dbg("return_type -> type_specifier pointer_opt");
            (yyval.str) = strcat((yyvsp[-1].str), (yyvsp[0].str)); 
        }
#line 4623 "src/parser.tab.c"
    break;

  case 250: /* lambda_expression: LSQUARE lambda_capture_clause RSQUARE lambda_declarator compound_statement  */
#line 1847 "src/parser.y"
                                                                                 { 
        dbg("lambda_expression -> [ lambda_capture_clause ] lambda_declarator compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 4631 "src/parser.tab.c"
    break;

  case 251: /* lambda_expression: LSQUARE lambda_capture_clause RSQUARE compound_statement  */
#line 1850 "src/parser.y"
                                                               { 
        dbg("lambda_expression -> [ lambda_capture_clause ] compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 4639 "src/parser.tab.c"
    break;

  case 252: /* lambda_declarator: lambda_parameter_clause trailing_return_opt  */
#line 1856 "src/parser.y"
                                                  { 
        dbg("lambda_declarator -> lambda_parameter_clause trailing_return_opt");
        (yyval.node) = (yyvsp[-1].node); }
#line 4647 "src/parser.tab.c"
    break;

  case 253: /* lambda_parameter_clause: LROUND RROUND  */
#line 1862 "src/parser.y"
                    { 
        dbg("lambda_parameter_clause -> ( )");
        (yyval.node) = new Node(); }
#line 4655 "src/parser.tab.c"
    break;

  case 254: /* lambda_parameter_clause: LROUND parameter_list RROUND  */
#line 1865 "src/parser.y"
                                   {
        dbg("lambda_parameter_clause -> ( parameter_list )");
         (yyval.node) = (yyvsp[-1].node); }
#line 4663 "src/parser.tab.c"
    break;

  case 255: /* trailing_return_opt: %empty  */
#line 1871 "src/parser.y"
       { 
        dbg("trailing_return_opt -> <empty>");
        (yyval.node) = nullptr; }
#line 4671 "src/parser.tab.c"
    break;

  case 256: /* trailing_return_opt: ARROW type_name  */
#line 1874 "src/parser.y"
                      { 
        dbg("trailing_return_opt -> ARROW type_name");
        (yyval.node) = (yyvsp[0].node); }
#line 4679 "src/parser.tab.c"
    break;

  case 257: /* lambda_capture_clause: ASSIGN  */
#line 1880 "src/parser.y"
             { 
        dbg("lambda_capture_clause -> =");
        (yyval.node) = new Node(); }
#line 4687 "src/parser.tab.c"
    break;

  case 258: /* lambda_capture_clause: capture_list  */
#line 1883 "src/parser.y"
                   { 
        dbg("lambda_capture_clause -> capture_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4695 "src/parser.tab.c"
    break;

  case 259: /* lambda_capture_clause: capture_list COMMA ASSIGN  */
#line 1886 "src/parser.y"
                                { 
        dbg("lambda_capture_clause -> capture_list , =");
        (yyval.node) = (yyvsp[-2].node); }
#line 4703 "src/parser.tab.c"
    break;

  case 260: /* lambda_capture_clause: ASSIGN COMMA capture_list  */
#line 1889 "src/parser.y"
                                { 
        dbg("lambda_capture_clause -> = , capture_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4711 "src/parser.tab.c"
    break;

  case 261: /* capture_list: IDENTIFIER  */
#line 1895 "src/parser.y"
                 { 
        dbg("capture_list -> IDENTIFIER");
        Node* n=new Node(); (yyval.node) = n; }
#line 4719 "src/parser.tab.c"
    break;

  case 262: /* capture_list: capture_list COMMA IDENTIFIER  */
#line 1898 "src/parser.y"
                                    {
        dbg("capture_list -> capture_list , IDENTIFIER"); 
        Node* n=(yyvsp[-2].node); (yyval.node) = n; }
#line 4727 "src/parser.tab.c"
    break;


#line 4731 "src/parser.tab.c"

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

#line 1903 "src/parser.y"



#include <cstdio>

void yyerror(const char *s);

int main(int argc, char** argv){
    pushScope();
    
    if (yyparse() == 0) {
        cerr << "Parsing completed successfully.\n";
    } else {
        cerr << "Parsing failed.\n";
    }

    if (!errors.empty()) {
        cout << "---- Errors found ----\n";
        for (auto &e : errors) 
            cout << e << "\n";

        return 1;
    }

    if (finalRoot) {
        for (size_t i = 0; i < finalRoot->code.size(); ++i) {
            cout << "["<<(i+1) << "] " << finalRoot->code[i] << "\n";
        }
    }

    return 0;
}

