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
        string place;
        string type;
        string kind;
        int argCount = 0;
        Node() : place(""), type("") , kind("") {}
        Node(const Node &n) : code(n.code), place(n.place), type(n.type), kind(n.kind), argCount(n.argCount) {}
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
        Symbol(const Symbol &s) : name(s.name), type(s.type), kind(s.kind), isFunction(s.isFunction), paramCount(s.paramCount), isDeclared(s.isDeclared) {}
        Symbol(string n, string t, string k, bool f, int p) : name(n), type(t), kind(k), isFunction(f), paramCount(p) {}
    };

    vector< unordered_map<string, Symbol> > symStack;
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

    void pushScope() {
        symStack.emplace_back();
    }
    void popScope() {
        if (!symStack.empty()) symStack.pop_back();
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

    bool is_type_name(char const* name) {
        for (int i = (int)symStack.size()-1; i >= 0; --i){
            auto &m = symStack[i];
            auto it = m.find(name);
            if (it != m.end() && it->second.isDeclared) 
                return true;
        }
        return false;
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


#line 191 "src/parser.tab.c"

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
  YYSYMBOL_parameter_type_list = 147,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 148,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 149,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 150,          /* identifier_list  */
  YYSYMBOL_type_name = 151,                /* type_name  */
  YYSYMBOL_abstract_declarator = 152,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 153, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 154,              /* initializer  */
  YYSYMBOL_initializer_list = 155,         /* initializer_list  */
  YYSYMBOL_statement = 156,                /* statement  */
  YYSYMBOL_io_statement = 157,             /* io_statement  */
  YYSYMBOL_cout_expression = 158,          /* cout_expression  */
  YYSYMBOL_insertion_list = 159,           /* insertion_list  */
  YYSYMBOL_cin_expression = 160,           /* cin_expression  */
  YYSYMBOL_extraction_list = 161,          /* extraction_list  */
  YYSYMBOL_labeled_statement = 162,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 163,       /* compound_statement  */
  YYSYMBOL_statement_list = 164,           /* statement_list  */
  YYSYMBOL_block_item = 165,               /* block_item  */
  YYSYMBOL_expression_statement = 166,     /* expression_statement  */
  YYSYMBOL_selection_statement = 167,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 168,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 169,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 170,           /* jump_statement  */
  YYSYMBOL_translation_unit = 171,         /* translation_unit  */
  YYSYMBOL_external_declaration = 172,     /* external_declaration  */
  YYSYMBOL_function_definition = 173,      /* function_definition  */
  YYSYMBOL_lambda_expression = 174,        /* lambda_expression  */
  YYSYMBOL_lambda_declarator = 175,        /* lambda_declarator  */
  YYSYMBOL_lambda_parameter_clause = 176,  /* lambda_parameter_clause  */
  YYSYMBOL_trailing_return_opt = 177,      /* trailing_return_opt  */
  YYSYMBOL_lambda_capture_clause = 178,    /* lambda_capture_clause  */
  YYSYMBOL_capture_list = 179              /* capture_list  */
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
#define YYFINAL  52
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1787

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  97
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  262
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  435

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
       0,   201,   201,   216,   219,   222,   228,   233,   238,   243,
     248,   253,   258,   263,   271,   274,   300,   324,   348,   372,
     392,   412,   435,   447,   462,   465,   474,   483,   515,   519,
     523,   526,   532,   535,   538,   541,   544,   547,   553,   561,
     569,   577,   585,   593,   601,   609,   620,   623,   629,   632,
     638,   641,   647,   654,   664,   667,   674,   677,   687,   697,
     710,   713,   723,   736,   739,   748,   760,   763,   770,   777,
     784,   794,   797,   804,   814,   817,   827,   830,   840,   843,
     853,   856,   866,   869,   879,   882,   903,   906,   938,   941,
     944,   947,   950,   953,   956,   959,   962,   965,   968,   974,
     977,   988,   994,   999,  1003,  1007,  1010,  1013,  1016,  1019,
    1022,  1028,  1031,  1040,  1053,  1072,  1075,  1078,  1084,  1087,
    1090,  1093,  1096,  1099,  1102,  1105,  1111,  1114,  1120,  1123,
    1129,  1132,  1140,  1143,  1149,  1152,  1155,  1161,  1164,  1167,
    1170,  1173,  1176,  1179,  1185,  1189,  1196,  1203,  1206,  1214,
    1220,  1223,  1226,  1229,  1235,  1241,  1244,  1250,  1256,  1259,
    1262,  1265,  1268,  1271,  1277,  1280,  1283,  1286,  1292,  1295,
    1301,  1307,  1310,  1317,  1324,  1327,  1333,  1336,  1342,  1345,
    1351,  1354,  1357,  1363,  1366,  1369,  1372,  1375,  1378,  1381,
    1384,  1387,  1393,  1396,  1399,  1405,  1408,  1415,  1418,  1421,
    1424,  1427,  1430,  1433,  1439,  1442,  1448,  1454,  1460,  1465,
    1469,  1478,  1484,  1489,  1498,  1504,  1510,  1519,  1526,  1536,
    1539,  1548,  1551,  1554,  1558,  1561,  1567,  1578,  1592,  1599,
    1612,  1623,  1634,  1650,  1670,  1673,  1679,  1685,  1689,  1693,
    1697,  1708,  1711,  1717,  1721,  1724,  1727,  1733,  1748,  1762,
    1766,  1769,  1775,  1781,  1784,  1790,  1793,  1799,  1802,  1805,
    1808,  1814,  1817
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
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "statement", "io_statement", "cout_expression", "insertion_list",
  "cin_expression", "extraction_list", "labeled_statement",
  "compound_statement", "statement_list", "block_item",
  "expression_statement", "selection_statement", "iteration_statement",
  "for_init_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "lambda_expression",
  "lambda_declarator", "lambda_parameter_clause", "trailing_return_opt",
  "lambda_capture_clause", "capture_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-278)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     241,    53,  -278,  -278,    48,    21,  -278,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
      34,  1652,  1652,   -17,   -27,  1652,     9,   153,     4,   892,
    -278,  -278,  -278,  -278,  -278,  -278,    48,    91,  -278,    16,
    -278,    24,  -278,  -278,  -278,   113,  -278,   351,  -278,  1002,
     862,   153,  -278,    53,  -278,  -278,  -278,  -278,  -278,    21,
     902,  -278,   598,    67,  -278,  -278,  -278,  1512,  1512,  -278,
    -278,   632,  -278,    19,  -278,  -278,   134,   143,  1552,   117,
     156,   722,   195,   159,   211,   238,   972,   252,  1622,  -278,
    -278,  -278,  1662,   132,   274,   279,   268,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,    32,   349,  1552,  -278,  -278,  -278,
     269,    31,   118,   254,   215,   296,   302,   304,   299,    42,
    -278,  -278,   221,  -278,    34,  -278,  -278,   283,   284,  -278,
    -278,   446,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
      38,   291,   287,  -278,   -16,  -278,  -278,  -278,  -278,   293,
    -278,   324,   902,  -278,  -278,  -278,   249,   294,   295,   298,
     303,    80,   300,  1698,  -278,  -278,  -278,  -278,  -278,    43,
      80,  -278,  1552,  -278,  -278,    49,    95,   306,   307,  -278,
     305,   314,  1552,  1552,   316,   722,  1552,   308,   541,   321,
    -278,  -278,  -278,   237,  1552,   632,  -278,    11,  -278,   131,
    1552,   326,  1012,   330,   722,  -278,  -278,   278,  1082,  1552,
     280,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,  -278,
    -278,  -278,  1552,  -278,  1552,  1552,  1552,  1552,  1552,  1552,
    1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,  1552,
    1552,  1552,  1552,  -278,  1552,  -278,  -278,  -278,  -278,   784,
    1152,  -278,    44,  -278,   201,  -278,  1652,  -278,   281,  -278,
    -278,    98,   329,  -278,  -278,  -278,  1252,  -278,  -278,  -278,
    -278,  -278,  -278,   243,  -278,    24,  -278,  -278,  1144,   204,
    -278,  1552,   309,   258,    30,    50,    88,   722,  -278,   122,
     333,   331,  -278,  -278,  1222,  -278,  -278,   124,   348,  1552,
    -278,  1262,  1552,   212,   214,  -278,  -278,  1552,  -278,  -278,
    1332,  -278,  -278,  -278,   125,  -278,   146,  -278,  -278,  -278,
    -278,  -278,   269,   269,    31,    31,   118,   118,   118,   118,
     254,   254,   215,   296,   302,   304,   299,   121,  -278,  -278,
     355,   357,  -278,   345,   201,  1432,  1402,  -278,  -278,  -278,
     792,   359,     9,   136,  -278,    21,  -278,  -278,   344,  1542,
    -278,     9,   375,  -278,  -278,   722,   722,  -278,   722,  1552,
    1442,   722,  -278,  -278,  -278,  -278,   141,   217,   214,  -278,
    1552,  -278,  -278,  -278,  -278,  -278,  1552,  -278,  1552,  -278,
    -278,  -278,  -278,   364,  -278,   386,  -278,  -278,     9,  -278,
       9,  -278,   342,  -278,   147,  -278,    80,  -278,   379,  -278,
    -278,   191,   722,   192,  -278,  -278,  -278,  -278,   218,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,  -278,   722,   388,  -278,
     722,  -278,  -278,  -278,  -278
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   243,   115,   125,   164,     0,   118,   120,   122,   119,
     123,   124,   121,   117,   116,   154,   129,   128,   157,   246,
       0,   105,   107,     0,     0,   109,     0,   156,     0,     0,
     241,   244,   249,   104,   168,   166,   165,     0,   102,     0,
     111,   113,   106,   108,   245,   127,   110,     0,   248,     0,
       0,   155,     1,     0,   242,   169,   167,   158,   103,     0,
       0,   247,     0,     0,    34,    35,    33,     0,     0,    32,
      37,     0,   217,     0,   224,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    12,
      13,    11,     0,     0,     0,     0,     2,     6,    10,     9,
       7,     8,    14,     3,    24,    54,     0,    31,    30,    56,
      60,    63,    66,    71,    74,    76,    78,    80,    82,    84,
      86,    99,     0,   222,     0,   221,   203,     0,     0,   197,
     198,     0,   219,   199,   200,   201,   202,     5,   163,   176,
     175,     0,   170,   171,     0,   160,     2,    54,   101,     0,
     112,   113,     0,   192,   114,   141,     0,     0,     0,     0,
       0,   151,     0,     0,   130,   132,   133,   142,   143,     0,
     153,   223,     0,    25,    26,     0,   178,     0,   257,   261,
       0,   258,     0,     0,     0,     0,     0,     0,     0,     0,
     237,   238,   239,     0,     0,     0,    28,     0,    53,    45,
       0,   211,     0,   206,     0,    20,    21,     0,     0,     0,
       0,    88,    92,    93,    89,    90,    91,    96,    98,    97,
      94,    95,     0,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   225,     0,   204,   205,   218,   220,     0,
       0,   173,   180,   174,   181,   161,     0,   162,     0,   159,
     195,     0,     0,   134,   135,   136,     0,   150,   140,   126,
     131,   138,   149,     0,   147,   113,   152,     4,     0,   180,
     179,     0,     0,     0,     0,     0,     0,     0,   216,     0,
       0,     0,   235,   234,     0,   236,   240,     0,     0,     0,
      47,     0,     0,    42,    43,    44,   212,     0,   208,   207,
       0,   214,    19,    16,     0,    22,     0,    18,    87,    57,
      58,    59,    61,    62,    64,    65,    68,    67,    69,    70,
      72,    73,    75,    77,    79,    81,    83,     0,   100,   188,
       0,     0,   184,     0,   182,     0,     0,   172,   177,   193,
       0,     0,     0,     0,   137,     0,   139,    55,   260,     0,
     251,     0,   255,   259,   262,     0,     0,   215,     0,     0,
       0,     0,    29,    52,    46,    50,     0,     0,    41,    40,
       0,    39,   213,   209,   210,    17,     0,    15,     0,   189,
     183,   185,   190,     0,   186,     0,   194,   196,     0,   145,
       0,   148,     0,   253,     0,   250,     0,   252,   226,   228,
     229,     0,     0,     0,   230,    51,    48,    38,     0,    23,
      85,   191,   187,   146,   144,   254,   256,     0,     0,   232,
       0,    49,   227,   231,   233
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -278,  -278,  -278,  -278,   133,   -14,  -278,  -278,   139,   138,
    -277,  -278,   -40,   -21,    45,    62,    87,   219,   210,   216,
     209,   220,  -278,   -45,   -47,  -278,   -65,   -70,   -32,    47,
    -278,   -55,  -278,   -59,   -43,  -278,  -278,   297,  -278,  -278,
    -278,  -278,  -278,   102,   -48,    -4,    20,   -19,     3,  -278,
     -39,  -243,   206,  -278,  -178,   -92,  -193,  -141,  -278,   -79,
    -278,  -278,  -278,  -278,  -278,  -278,   -25,  -278,   332,  -170,
    -278,  -278,  -278,  -278,  -278,   435,  -278,  -278,  -278,  -278,
    -278,  -278,   183
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,   102,   103,   104,   314,   105,   106,   107,   303,   304,
     305,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   222,   122,   149,    19,   140,
      39,    40,    21,    22,    23,    24,   163,   164,   165,   166,
     167,   168,   273,   274,   176,    25,   151,    27,    28,    36,
     340,   142,   143,   144,   177,   341,   254,   154,   261,   125,
     126,   127,   203,   128,   201,   129,   130,   131,   132,   133,
     134,   135,   294,   136,    29,    30,    31,   137,   361,   362,
     407,   180,   181
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,    48,   187,   161,   150,   148,   175,    35,   184,    51,
     141,   260,   161,   153,   169,   123,    61,   298,   293,   162,
      26,   193,   178,   353,   257,    37,   379,   381,    44,     4,
     178,   258,    55,   148,   199,    60,   147,   227,   228,    56,
      41,   363,     4,     5,   205,   206,     4,    20,   253,    26,
      47,     4,   198,   173,   174,   299,     4,   207,   170,   344,
       5,    58,    45,    59,   147,    47,   223,   170,    42,    43,
     241,   208,    46,     5,   196,   209,    20,   249,   147,    38,
     210,   250,     5,   249,   280,     3,   344,   250,   271,   277,
     365,   242,   147,    18,   124,    32,   244,   244,    33,   123,
     179,   417,   161,     4,   161,   153,   288,   175,   179,   171,
      18,   161,    33,   267,   272,   169,   404,   285,   286,   364,
     162,   289,   276,    18,   370,   311,    15,    18,   366,   297,
     175,    57,    18,    18,   278,   244,   161,     3,   250,   300,
     349,   229,   230,   252,   316,   350,     6,     7,     8,     9,
      10,    11,    12,   306,    62,   309,   292,   170,    15,   170,
     251,   315,   368,   185,   371,   385,   170,   388,   244,   244,
     301,   244,   386,   182,   302,   318,   400,   337,   124,   279,
     343,   415,   183,   256,   319,   320,   321,   425,   386,   275,
     387,   170,    49,   244,   256,   186,    50,   338,     6,     7,
       8,     9,    10,    11,    12,   148,   322,   323,   367,   397,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   426,   235,
     236,   428,   430,    51,   188,   124,   147,   377,   244,   244,
     345,   357,     1,   278,   346,     2,     3,   250,   189,     4,
     356,   301,   252,   301,   315,   302,   190,   380,   360,   373,
     382,   416,   431,   384,   244,   244,   243,   147,   244,    37,
     231,   232,   233,   234,   324,   325,   395,   224,   225,   226,
       5,   279,   296,   191,   244,   147,   408,   409,   354,   410,
     355,   194,   414,   326,   327,   328,   329,   359,   200,    47,
     272,   148,   202,   153,   411,   413,   393,     6,     7,     8,
       9,    10,    11,    12,   204,   418,   237,    13,    14,    15,
      16,    17,   330,   331,   238,   239,   240,   399,   245,   246,
      18,   255,   147,   429,   256,    60,   405,   259,   262,   419,
     263,   264,   266,   420,   265,   268,   281,   161,   432,   283,
     307,   434,    63,   310,   282,     2,     3,    64,    65,    66,
     211,   284,   287,    67,    68,   290,   295,   312,   351,   317,
     348,    69,   369,   423,   147,   424,    33,    70,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   372,   391,
      71,   402,    47,    72,    73,   389,    74,   390,   179,   398,
     406,    75,   170,    76,   421,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,     6,     7,     8,
       9,    10,    11,    12,    89,    90,    91,    13,    14,    15,
     422,   364,   427,   433,   376,    92,    93,    94,    95,   374,
      96,   378,    97,    98,    99,   100,   101,    63,   333,   335,
       2,     3,    64,    65,    66,   334,   332,   401,    67,    68,
     270,   336,   347,   248,    54,   358,    69,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,    47,   247,    73,
       0,    74,     0,     0,     0,     0,    75,     0,    76,     0,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,     6,     7,     8,     9,    10,    11,    12,    89,
      90,    91,    13,    14,    15,     0,     0,     0,     0,     0,
      92,    93,    94,    95,     0,    96,     0,    97,    98,    99,
     100,   101,   291,     0,     0,     2,     3,    64,    65,    66,
       0,     0,     0,    67,    68,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,     0,     0,     0,    73,     0,    74,     0,     0,     0,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     0,    88,     6,     7,     8,
       9,    10,    11,    12,    89,    90,    91,    13,    14,    15,
       0,     0,     0,     0,     0,    92,    93,     0,     0,     0,
     146,     0,    97,    98,    99,   100,   101,     3,    64,    65,
      66,     0,     0,   155,    67,    68,     0,     0,   156,     0,
       0,     0,    69,     0,     0,     0,     0,     0,    70,     0,
       0,     0,     0,     0,     6,     7,     8,     9,    10,    11,
      12,    71,     0,     0,     0,    73,    15,    16,    17,   157,
     158,   159,    75,     0,     0,     0,     0,   160,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     6,     7,
       8,     9,    10,    11,    12,    89,    90,    91,     0,     0,
      15,     0,     0,     0,     0,     0,    92,    93,     0,     0,
       0,   146,     0,    97,    98,    99,   100,   101,    64,    65,
      66,     0,     0,     0,    67,    68,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,     0,    70,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,     0,    47,     0,    73,     0,    74,     0,     0,
       0,     0,    75,     0,    76,     0,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,     2,     3,
       0,     0,     4,     0,     0,    89,    90,    91,    64,    65,
      66,     0,     0,     0,    67,    68,    92,    93,    94,    95,
       0,    96,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,   249,   339,     0,     0,   250,     0,     0,
       0,    71,     0,   152,   396,    73,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,     0,     0,     0,     0,
       6,     7,     8,     9,    10,    11,    12,    88,     0,     0,
      13,    14,    15,     0,     0,    89,    90,    91,    64,    65,
      66,     0,     0,    18,    67,    68,    92,    93,     0,     0,
       0,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,    52,    53,     0,     0,     2,     3,     0,     0,
       4,    71,     0,     0,     0,    73,   145,     0,    64,    65,
      66,     0,    75,     0,    67,    68,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,    88,    70,     0,
       0,     5,     0,     0,     0,    89,    90,    91,     0,     0,
       0,    71,     0,   152,     0,    73,    92,    93,     0,     0,
       0,   146,    75,    97,    98,    99,   100,   101,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    88,    13,    14,
      15,    16,    17,     0,     0,    89,    90,    91,    64,    65,
      66,    18,     0,     0,    67,    68,    92,    93,     0,     0,
       0,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,    71,     0,     0,     0,    73,     0,   192,    64,    65,
      66,     0,    75,     0,    67,    68,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,    88,    70,     0,
       0,     0,   138,     0,     0,    89,    90,    91,     0,     0,
       0,    71,     0,     0,     0,    73,    92,    93,     0,     0,
       0,   146,    75,    97,    98,    99,   100,   101,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    88,    13,    14,
      15,     0,     0,     0,     0,    89,    90,    91,    64,    65,
      66,   139,     0,     0,    67,    68,    92,    93,     0,     0,
     308,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,   313,     0,     0,    73,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     2,     3,
       0,     0,     4,     0,     0,    89,    90,    91,    64,    65,
      66,     0,     0,     0,    67,    68,    92,    93,     0,     0,
       0,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,   278,   339,     0,     0,   250,     0,     0,
       0,    71,     0,     0,     0,    73,   342,     0,     0,     0,
       0,     0,    75,     0,     0,     0,     0,     0,     0,     0,
       6,     7,     8,     9,    10,    11,    12,    88,     0,     0,
      13,    14,    15,     0,     0,    89,    90,    91,    64,    65,
      66,     0,     0,     0,    67,    68,    92,    93,     0,     0,
       0,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,    71,     0,     0,     0,    73,     0,    74,    64,    65,
      66,     0,    75,     0,    67,    68,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,    88,    70,     0,
       0,     0,   352,     0,     0,    89,    90,    91,     0,     0,
       0,    71,   375,     0,     0,    73,    92,    93,     0,     0,
       0,   146,    75,    97,    98,    99,   100,   101,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    88,    13,    14,
      15,     0,     0,     0,     0,    89,    90,    91,    64,    65,
      66,     0,     0,     0,    67,    68,    92,    93,     0,     0,
       0,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,     0,     0,     0,    73,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    88,     0,     0,
       0,     0,     0,     0,     0,    89,    90,    91,    64,    65,
      66,     0,     0,     0,    67,    68,    92,    93,     0,     0,
     383,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,    71,     0,     0,     0,    73,   394,     0,    64,    65,
      66,     0,    75,     0,    67,    68,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,    88,    70,     0,
       0,     0,   392,     0,     0,    89,    90,    91,     0,     0,
       0,    71,   412,     0,     0,    73,    92,    93,     0,     0,
       0,   146,    75,    97,    98,    99,   100,   101,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    88,    13,    14,
      15,     0,     0,     0,     0,    89,    90,    91,    64,    65,
      66,     0,     0,     0,    67,    68,    92,    93,     0,     0,
       0,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,   172,     0,     0,     0,    73,     0,     0,    64,    65,
      66,     0,    75,     0,    67,    68,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,    88,    70,     0,
       0,     0,   403,     0,     0,    89,    90,    91,     0,     0,
       0,    71,     0,     0,     0,    73,    92,    93,     0,     0,
       0,   146,    75,    97,    98,    99,   100,   101,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    88,    13,    14,
      15,     0,     0,     0,     0,    89,    90,    91,    64,    65,
      66,     0,     0,     0,    67,    68,    92,    93,     0,     0,
       0,   146,    69,    97,    98,    99,   100,   101,    70,     0,
       0,     0,     0,     0,     0,     0,     2,     3,     0,     0,
       0,   195,     0,     0,     0,    73,     0,     0,    64,    65,
      66,     0,    75,     0,    67,    68,     0,     0,     0,     0,
       0,     0,    69,     0,     0,     0,     0,    88,    70,     0,
       0,     0,     0,     0,     0,    89,    90,    91,     0,     0,
       0,    71,     0,     3,     0,   197,    92,    93,     0,     0,
       0,   146,    75,    97,    98,    99,   100,   101,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    88,    13,    14,
      15,     0,     0,     0,     0,    89,    90,    91,     0,     0,
     269,     0,     0,   155,     0,     0,    92,    93,   156,     0,
       0,   146,     0,    97,    98,    99,   100,   101,     0,     0,
       0,     0,     0,     0,     6,     7,     8,     9,    10,    11,
      12,     0,     0,     0,     0,     0,    15,    16,    17,   157,
     158,   159,     0,     0,     0,     0,     0,   160
};

static const yytype_int16 yycheck[] =
{
       4,    26,    81,    62,    59,    50,    71,     4,    78,    28,
      49,   152,    71,    60,    62,    47,    41,   195,   188,    62,
       0,    86,    11,   266,    40,     5,   303,   304,    45,     8,
      11,    47,    36,    78,    93,    11,    50,     6,     7,    36,
      20,    11,     8,    39,    12,    13,     8,     0,   140,    29,
      41,     8,    92,    67,    68,    44,     8,    25,    62,   252,
      39,    45,    89,    47,    78,    41,   106,    71,    21,    22,
      28,    39,    25,    39,    88,    43,    29,    39,    92,    45,
      48,    43,    39,    39,   176,     5,   279,    43,    45,    40,
      40,    49,   106,    89,    47,    42,    47,    47,    45,   131,
      89,   378,   161,     8,   163,   152,   185,   172,    89,    42,
      89,   170,    45,   161,   169,   163,   359,   182,   183,    89,
     163,   186,   170,    89,   294,   204,    78,    89,    40,   194,
     195,    40,    89,    89,    39,    47,   195,     5,    43,     8,
      42,    23,    24,   140,   209,    47,    66,    67,    68,    69,
      70,    71,    72,   200,    41,   202,   188,   161,    78,   163,
     140,   208,    40,    46,    40,    40,   170,    46,    47,    47,
      39,    47,    47,    39,    43,   222,    40,   242,   131,   176,
     250,    40,    39,    47,   224,   225,   226,    40,    47,   169,
      44,   195,    39,    47,    47,    39,    43,   244,    66,    67,
      68,    69,    70,    71,    72,   250,   227,   228,   287,   350,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   406,    14,
      15,    40,    40,   252,    39,   188,   250,   302,    47,    47,
      39,   281,     1,    39,    43,     4,     5,    43,    89,     8,
     275,    39,   249,    39,   301,    43,    45,    43,   283,   299,
     307,    44,    44,   310,    47,    47,    45,   281,    47,   249,
      16,    17,    18,    19,   229,   230,   346,     8,     9,    10,
      39,   278,    45,    45,    47,   299,   365,   366,    45,   368,
      47,    39,   371,   231,   232,   233,   234,    39,    24,    41,
     355,   346,    23,   350,   369,   370,   345,    66,    67,    68,
      69,    70,    71,    72,    46,   380,    20,    76,    77,    78,
      79,    80,   235,   236,    22,    21,    27,   352,    45,    45,
      89,    40,   346,   412,    47,    11,   361,    44,    89,   386,
      46,    46,    39,   388,    46,    45,    40,   406,   427,    44,
      24,   430,     1,    23,    47,     4,     5,     6,     7,     8,
      11,    47,    46,    12,    13,    57,    45,    89,    39,    89,
      89,    20,    39,   398,   388,   400,    45,    26,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    40,    44,
      39,    47,    41,    42,    43,    40,    45,    40,    89,    40,
      25,    50,   406,    52,    40,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      44,    89,    53,    45,   301,    84,    85,    86,    87,   300,
      89,   303,    91,    92,    93,    94,    95,     1,   238,   240,
       4,     5,     6,     7,     8,   239,   237,   355,    12,    13,
     163,   241,   256,   131,    29,   282,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    41,    42,    43,
      -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    52,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,
      84,    85,    86,    87,    -1,    89,    -1,    91,    92,    93,
      94,    95,     1,    -1,    -1,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    43,    -1,    45,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,    -1,
      89,    -1,    91,    92,    93,    94,    95,     5,     6,     7,
       8,    -1,    -1,    45,    12,    13,    -1,    -1,    50,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    39,    -1,    -1,    -1,    43,    78,    79,    80,    81,
      82,    83,    50,    -1,    -1,    -1,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    -1,    -1,
      78,    -1,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    89,    -1,    91,    92,    93,    94,    95,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    41,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    52,    -1,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,     4,     5,
      -1,    -1,     8,    -1,    -1,    73,    74,    75,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    84,    85,    86,    87,
      -1,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,
      -1,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    65,    -1,    -1,
      76,    77,    78,    -1,    -1,    73,    74,    75,     6,     7,
       8,    -1,    -1,    89,    12,    13,    84,    85,    -1,    -1,
      -1,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,     0,     1,    -1,    -1,     4,     5,    -1,    -1,
       8,    39,    -1,    -1,    -1,    43,    44,    -1,     6,     7,
       8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,    -1,
      -1,    39,    -1,    -1,    -1,    73,    74,    75,    -1,    -1,
      -1,    39,    -1,    41,    -1,    43,    84,    85,    -1,    -1,
      -1,    89,    50,    91,    92,    93,    94,    95,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    65,    76,    77,
      78,    79,    80,    -1,    -1,    73,    74,    75,     6,     7,
       8,    89,    -1,    -1,    12,    13,    84,    85,    -1,    -1,
      -1,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    -1,    45,     6,     7,
       8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,    -1,
      -1,    -1,    40,    -1,    -1,    73,    74,    75,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    84,    85,    -1,    -1,
      -1,    89,    50,    91,    92,    93,    94,    95,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    65,    76,    77,
      78,    -1,    -1,    -1,    -1,    73,    74,    75,     6,     7,
       8,    89,    -1,    -1,    12,    13,    84,    85,    -1,    -1,
      88,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,     4,     5,
      -1,    -1,     8,    -1,    -1,    73,    74,    75,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,    -1,
      -1,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    39,    40,    -1,    -1,    43,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    65,    -1,    -1,
      76,    77,    78,    -1,    -1,    73,    74,    75,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,    -1,
      -1,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    -1,    45,     6,     7,
       8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,    -1,
      -1,    -1,    40,    -1,    -1,    73,    74,    75,    -1,    -1,
      -1,    39,    40,    -1,    -1,    43,    84,    85,    -1,    -1,
      -1,    89,    50,    91,    92,    93,    94,    95,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    65,    76,    77,
      78,    -1,    -1,    -1,    -1,    73,    74,    75,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,    -1,
      -1,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,    -1,
      88,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    44,    -1,     6,     7,
       8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,    -1,
      -1,    -1,    40,    -1,    -1,    73,    74,    75,    -1,    -1,
      -1,    39,    40,    -1,    -1,    43,    84,    85,    -1,    -1,
      -1,    89,    50,    91,    92,    93,    94,    95,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    65,    76,    77,
      78,    -1,    -1,    -1,    -1,    73,    74,    75,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,    -1,
      -1,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    -1,    -1,     6,     7,
       8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,    -1,
      -1,    -1,    40,    -1,    -1,    73,    74,    75,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    84,    85,    -1,    -1,
      -1,    89,    50,    91,    92,    93,    94,    95,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    65,    76,    77,
      78,    -1,    -1,    -1,    -1,    73,    74,    75,     6,     7,
       8,    -1,    -1,    -1,    12,    13,    84,    85,    -1,    -1,
      -1,    89,    20,    91,    92,    93,    94,    95,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    43,    -1,    -1,     6,     7,
       8,    -1,    50,    -1,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    65,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,    -1,
      -1,    39,    -1,     5,    -1,    43,    84,    85,    -1,    -1,
      -1,    89,    50,    91,    92,    93,    94,    95,    66,    67,
      68,    69,    70,    71,    72,    -1,    -1,    65,    76,    77,
      78,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,    -1,
      42,    -1,    -1,    45,    -1,    -1,    84,    85,    50,    -1,
      -1,    89,    -1,    91,    92,    93,    94,    95,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,    81,
      82,    83,    -1,    -1,    -1,    -1,    -1,    89
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     4,     5,     8,    39,    66,    67,    68,    69,
      70,    71,    72,    76,    77,    78,    79,    80,    89,   125,
     126,   129,   130,   131,   132,   142,   143,   144,   145,   171,
     172,   173,    42,    45,   142,   145,   146,   143,    45,   127,
     128,   143,   126,   126,    45,    89,   126,    41,   163,    39,
      43,   144,     0,     1,   172,   142,   145,    40,    45,    47,
      11,   163,    41,     1,     6,     7,     8,    12,    13,    20,
      26,    39,    42,    43,    45,    50,    52,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    73,
      74,    75,    84,    85,    86,    87,    89,    91,    92,    93,
      94,    95,    98,    99,   100,   102,   103,   104,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   123,   125,   126,   156,   157,   158,   160,   162,
     163,   164,   165,   166,   167,   168,   170,   174,    40,    89,
     126,   147,   148,   149,   150,    44,    89,   102,   120,   124,
     128,   143,    41,   121,   154,    45,    50,    81,    82,    83,
      89,   130,   131,   133,   134,   135,   136,   137,   138,   141,
     142,    42,    39,   102,   102,   123,   141,   151,    11,    89,
     178,   179,    39,    39,   124,    46,    39,   156,    39,    89,
      45,    45,    45,   123,    39,    39,   102,    43,   109,   130,
      24,   161,    23,   159,    46,    12,    13,    25,    39,    43,
      48,    11,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   122,   109,     8,     9,    10,     6,     7,    23,
      24,    16,    17,    18,    19,    14,    15,    20,    22,    21,
      27,    28,    49,    45,    47,    45,    45,    42,   165,    39,
      43,   143,   145,   152,   153,    40,    47,    40,    47,    44,
     154,   155,    89,    46,    46,    46,    39,   141,    45,    42,
     134,    45,   128,   139,   140,   143,   141,    40,    39,   145,
     152,    40,    47,    44,    47,   123,   123,    46,   156,   123,
      57,     1,   125,   166,   169,    45,    45,   123,   151,    44,
       8,    39,    43,   105,   106,   107,   121,    24,    88,   121,
      23,   156,    89,    40,   101,   121,   123,    89,   121,   109,
     109,   109,   110,   110,   111,   111,   112,   112,   112,   112,
     113,   113,   114,   115,   116,   117,   118,   123,   121,    40,
     147,   152,    44,   124,   153,    39,    43,   149,    89,    42,
      47,    39,    40,   148,    45,    47,   163,   109,   179,    39,
     163,   175,   176,    11,    89,    40,    40,   156,    40,    39,
     166,    40,    40,   109,   105,    40,   101,   123,   106,   107,
      43,   107,   121,    88,   121,    40,    47,    44,    46,    40,
      40,    44,    40,   147,    44,   124,    42,   154,    40,   163,
      40,   140,    47,    40,   148,   163,    25,   177,   156,   156,
     156,   123,    40,   123,   156,    40,    44,   107,   123,   121,
     120,    40,    44,   163,   163,    40,   151,    53,    40,   156,
      40,    44,   156,    45,   156
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
     147,   148,   148,   149,   149,   149,   150,   150,   151,   151,
     152,   152,   152,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   154,   154,   154,   155,   155,   156,   156,   156,
     156,   156,   156,   156,   157,   157,   158,   159,   159,   159,
     159,   160,   161,   161,   162,   162,   162,   163,   163,   164,
     164,   165,   165,   165,   166,   166,   167,   167,   167,   168,
     168,   168,   168,   168,   169,   169,   170,   170,   170,   170,
     170,   171,   171,   171,   172,   172,   172,   173,   173,   173,
     174,   174,   175,   176,   176,   177,   177,   178,   178,   178,
     178,   179,   179
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       4,     4,     3,     3,     3,     2,     2,     1,     3,     4,
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
       1,     1,     3,     2,     2,     1,     1,     3,     1,     2,
       1,     1,     2,     3,     2,     3,     3,     4,     2,     3,
       3,     4,     1,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     2,     2,     3,
       3,     2,     2,     3,     3,     4,     3,     2,     3,     1,
       2,     1,     1,     2,     1,     2,     5,     7,     5,     5,
       5,     7,     6,     7,     1,     1,     3,     2,     2,     2,
       3,     1,     2,     1,     1,     2,     1,     3,     2,     2,
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
#line 201 "src/parser.y"
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
#line 1989 "src/parser.tab.c"
    break;

  case 3: /* primary_expression: constant  */
#line 216 "src/parser.y"
                   { 
        dbg("primary_expression -> constant");
        (yyval.node) = (yyvsp[0].node); }
#line 1997 "src/parser.tab.c"
    break;

  case 4: /* primary_expression: LROUND expression RROUND  */
#line 219 "src/parser.y"
                                   { 
        dbg("primary_expression -> ( expression )");
        (yyval.node) = (yyvsp[-1].node); }
#line 2005 "src/parser.tab.c"
    break;

  case 5: /* primary_expression: lambda_expression  */
#line 222 "src/parser.y"
                        { 
        dbg("primary_expression -> lambda_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2013 "src/parser.tab.c"
    break;

  case 6: /* constant: DECIMAL_LITERAL  */
#line 228 "src/parser.y"
                            {
          dbg("constant -> DECIMAL_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "int", "constant");
          (yyval.node) = n;
      }
#line 2023 "src/parser.tab.c"
    break;

  case 7: /* constant: CHARACTER_LITERAL  */
#line 233 "src/parser.y"
                            {
            dbg("constant -> CHARACTER_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "char", "constant");
          (yyval.node) = n;
      }
#line 2033 "src/parser.tab.c"
    break;

  case 8: /* constant: STRING_LITERAL  */
#line 238 "src/parser.y"
                            {
            dbg("constant -> STRING_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "string", "constant");
          (yyval.node) = n;
      }
#line 2043 "src/parser.tab.c"
    break;

  case 9: /* constant: EXPONENT_LITERAL  */
#line 243 "src/parser.y"
                            {
            dbg("constant -> EXPONENT_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "double", "constant");
          (yyval.node) = n;
      }
#line 2053 "src/parser.tab.c"
    break;

  case 10: /* constant: DOUBLE_LITERAL  */
#line 248 "src/parser.y"
                            {
            dbg("constant -> DOUBLE_LITERAL");
          Node* n = new Node(string((yyvsp[0].str)), "double", "constant");
          (yyval.node) = n;
      }
#line 2063 "src/parser.tab.c"
    break;

  case 11: /* constant: NULLPTR  */
#line 253 "src/parser.y"
                            {
            dbg("constant -> NULLPTR");
          Node* n = new Node("0", "nullptr", "constant");
          (yyval.node) = n;
      }
#line 2073 "src/parser.tab.c"
    break;

  case 12: /* constant: TRUE  */
#line 258 "src/parser.y"
                            {
            dbg("constant -> TRUE");
          Node* n = new Node("1", "bool", "constant");
          (yyval.node) = n;
      }
#line 2083 "src/parser.tab.c"
    break;

  case 13: /* constant: FALSE  */
#line 263 "src/parser.y"
                            {
            dbg("constant -> FALSE");
          Node* n = new Node("0", "bool", "constant");
          (yyval.node) = n;
      }
#line 2093 "src/parser.tab.c"
    break;

  case 14: /* postfix_expression: primary_expression  */
#line 271 "src/parser.y"
                             { 
        dbg("postfix_expression -> primary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2101 "src/parser.tab.c"
    break;

  case 15: /* postfix_expression: postfix_expression LSQUARE expression RSQUARE  */
#line 274 "src/parser.y"
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
#line 2132 "src/parser.tab.c"
    break;

  case 16: /* postfix_expression: postfix_expression LROUND RROUND  */
#line 300 "src/parser.y"
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
#line 2161 "src/parser.tab.c"
    break;

  case 17: /* postfix_expression: postfix_expression LROUND argument_expression_list RROUND  */
#line 324 "src/parser.y"
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
#line 2190 "src/parser.tab.c"
    break;

  case 18: /* postfix_expression: postfix_expression DOT IDENTIFIER  */
#line 348 "src/parser.y"
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
#line 2219 "src/parser.tab.c"
    break;

  case 19: /* postfix_expression: postfix_expression ARROW IDENTIFIER  */
#line 372 "src/parser.y"
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
#line 2244 "src/parser.tab.c"
    break;

  case 20: /* postfix_expression: postfix_expression INCREMENT  */
#line 392 "src/parser.y"
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
#line 2269 "src/parser.tab.c"
    break;

  case 21: /* postfix_expression: postfix_expression DECREMENT  */
#line 412 "src/parser.y"
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
#line 2294 "src/parser.tab.c"
    break;

  case 22: /* argument_expression_list: assignment_expression  */
#line 435 "src/parser.y"
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
#line 2311 "src/parser.tab.c"
    break;

  case 23: /* argument_expression_list: argument_expression_list COMMA assignment_expression  */
#line 447 "src/parser.y"
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
#line 2328 "src/parser.tab.c"
    break;

  case 24: /* unary_expression: postfix_expression  */
#line 462 "src/parser.y"
                             { 
        dbg("unary_expression -> postfix_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2336 "src/parser.tab.c"
    break;

  case 25: /* unary_expression: INCREMENT unary_expression  */
#line 465 "src/parser.y"
                                     {
          dbg("unary_expression -> ++ unary_expression");
          Node* v = (yyvsp[0].node);
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " + 1;");
          (yyval.node) = n;
      }
#line 2350 "src/parser.tab.c"
    break;

  case 26: /* unary_expression: DECREMENT unary_expression  */
#line 474 "src/parser.y"
                                     {
            dbg("unary_expression -> -- unary_expression");
          Node* v = (yyvsp[0].node);
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " - 1;");
          (yyval.node) = n;
      }
#line 2364 "src/parser.tab.c"
    break;

  case 27: /* unary_expression: unary_operator cast_expression  */
#line 483 "src/parser.y"
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
#line 2401 "src/parser.tab.c"
    break;

  case 28: /* unary_expression: SIZEOF unary_expression  */
#line 515 "src/parser.y"
                                  {
          dbg("unary_expression -> sizeof unary_expression");
          Node* n = new Node(); n->place = "sizeof"; (yyval.node) = n;
      }
#line 2410 "src/parser.tab.c"
    break;

  case 29: /* unary_expression: SIZEOF LROUND type_name RROUND  */
#line 519 "src/parser.y"
                                         {
            dbg("unary_expression -> sizeof ( type_name )");
          Node* n = new Node(); n->place = "sizeof"; (yyval.node) = n;
      }
#line 2419 "src/parser.tab.c"
    break;

  case 30: /* unary_expression: delete_expression  */
#line 523 "src/parser.y"
                            { 
        dbg("unary_expression -> delete_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2427 "src/parser.tab.c"
    break;

  case 31: /* unary_expression: new_expression  */
#line 526 "src/parser.y"
                         { 
        dbg("unary_expression -> new_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2435 "src/parser.tab.c"
    break;

  case 32: /* unary_operator: BITWISE_AND  */
#line 532 "src/parser.y"
                      { 
        dbg("unary_operator -> &");
        (yyval.str) = (yyvsp[0].str); }
#line 2443 "src/parser.tab.c"
    break;

  case 33: /* unary_operator: STAR  */
#line 535 "src/parser.y"
               { 
        dbg("unary_operator -> *");
        (yyval.str) = (yyvsp[0].str); }
#line 2451 "src/parser.tab.c"
    break;

  case 34: /* unary_operator: PLUS  */
#line 538 "src/parser.y"
               { 
        dbg("unary_operator -> +");
        (yyval.str) = (yyvsp[0].str); }
#line 2459 "src/parser.tab.c"
    break;

  case 35: /* unary_operator: MINUS  */
#line 541 "src/parser.y"
                { 
        dbg("unary_operator -> -");
        (yyval.str) = (yyvsp[0].str); }
#line 2467 "src/parser.tab.c"
    break;

  case 36: /* unary_operator: TILDE  */
#line 544 "src/parser.y"
                { 
        dbg("unary_operator -> ~");
        (yyval.str) = (yyvsp[0].str); }
#line 2475 "src/parser.tab.c"
    break;

  case 37: /* unary_operator: LOGICAL_NOT  */
#line 547 "src/parser.y"
                      { 
        dbg("unary_operator -> !");
        (yyval.str) = (yyvsp[0].str); }
#line 2483 "src/parser.tab.c"
    break;

  case 38: /* new_expression: NEW type_specifier pointer_opt new_declarator scalar_new_init_opt  */
#line 553 "src/parser.y"
                                                                            {
          dbg("new_expression -> NEW type_specifier pointer_opt new_declarator scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2496 "src/parser.tab.c"
    break;

  case 39: /* new_expression: NEW type_specifier new_declarator scalar_new_init_opt  */
#line 561 "src/parser.y"
                                                                {
          dbg("new_expression -> NEW type_specifier new_declarator scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2509 "src/parser.tab.c"
    break;

  case 40: /* new_expression: NEW type_specifier pointer_opt scalar_new_init_opt  */
#line 569 "src/parser.y"
                                                             {
            dbg("new_expression -> NEW type_specifier pointer_opt scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2522 "src/parser.tab.c"
    break;

  case 41: /* new_expression: NEW type_specifier pointer_opt new_declarator  */
#line 577 "src/parser.y"
                                                        {
            dbg("new_expression -> NEW type_specifier pointer_opt new_declarator");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2535 "src/parser.tab.c"
    break;

  case 42: /* new_expression: NEW type_specifier pointer_opt  */
#line 585 "src/parser.y"
                                         {
            dbg("new_expression -> NEW type_specifier pointer_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2548 "src/parser.tab.c"
    break;

  case 43: /* new_expression: NEW type_specifier new_declarator  */
#line 593 "src/parser.y"
                                            {
            dbg("new_expression -> NEW type_specifier new_declarator");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2561 "src/parser.tab.c"
    break;

  case 44: /* new_expression: NEW type_specifier scalar_new_init_opt  */
#line 601 "src/parser.y"
                                                 {
            dbg("new_expression -> NEW type_specifier scalar_new_init_opt");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2574 "src/parser.tab.c"
    break;

  case 45: /* new_expression: NEW type_specifier  */
#line 609 "src/parser.y"
                             {
            dbg("new_expression -> NEW type_specifier");
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          (yyval.node) = n;
      }
#line 2587 "src/parser.tab.c"
    break;

  case 46: /* pointer_opt: STAR pointer_opt  */
#line 620 "src/parser.y"
                           { 
        dbg("pointer_opt -> * pointer_opt");
        (yyval.node) = nullptr; }
#line 2595 "src/parser.tab.c"
    break;

  case 47: /* pointer_opt: STAR  */
#line 623 "src/parser.y"
               { 
        dbg("pointer_opt -> *");
        (yyval.node) = nullptr; }
#line 2603 "src/parser.tab.c"
    break;

  case 48: /* new_declarator: LSQUARE expression RSQUARE  */
#line 629 "src/parser.y"
                                     { 
        dbg("new_declarator -> [ expression ]");
        (yyval.node) = (yyvsp[-1].node); }
#line 2611 "src/parser.tab.c"
    break;

  case 49: /* new_declarator: new_declarator LSQUARE expression RSQUARE  */
#line 632 "src/parser.y"
                                                    { 
        dbg("new_declarator -> new_declarator [ expression ]");
        (yyval.node) = (yyvsp[-1].node); }
#line 2619 "src/parser.tab.c"
    break;

  case 50: /* scalar_new_init_opt: LROUND RROUND  */
#line 638 "src/parser.y"
                        { 
        dbg("scalar_new_init_opt -> ( )");
        (yyval.node) = nullptr; }
#line 2627 "src/parser.tab.c"
    break;

  case 51: /* scalar_new_init_opt: LROUND argument_expression_list RROUND  */
#line 641 "src/parser.y"
                                                 { 
        dbg("scalar_new_init_opt -> ( argument_expression_list )");
        (yyval.node) = (yyvsp[-1].node); }
#line 2635 "src/parser.tab.c"
    break;

  case 52: /* delete_expression: DELETE LSQUARE RSQUARE cast_expression  */
#line 647 "src/parser.y"
                                                 {
          dbg("delete_expression -> DELETE [ ] cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("free " + (yyvsp[0].node)->place + ";");
          (yyval.node) = n;
      }
#line 2647 "src/parser.tab.c"
    break;

  case 53: /* delete_expression: DELETE cast_expression  */
#line 654 "src/parser.y"
                                 {
            dbg("delete_expression -> DELETE cast_expression");
          Node* n = new Node();
          n->code = (yyvsp[0].node)->code;
          n->code.push_back("free " + (yyvsp[0].node)->place + ";");
          (yyval.node) = n;
      }
#line 2659 "src/parser.tab.c"
    break;

  case 54: /* cast_expression: unary_expression  */
#line 664 "src/parser.y"
                           { 
        dbg("cast_expression -> unary_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2667 "src/parser.tab.c"
    break;

  case 55: /* cast_expression: LROUND type_name RROUND cast_expression  */
#line 667 "src/parser.y"
                                                  {
            dbg("cast_expression -> ( type_name ) cast_expression");
          (yyval.node) = (yyvsp[0].node);
      }
#line 2676 "src/parser.tab.c"
    break;

  case 56: /* multiplicative_expression: cast_expression  */
#line 674 "src/parser.y"
                          { 
        dbg("multiplicative_expression -> cast_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2684 "src/parser.tab.c"
    break;

  case 57: /* multiplicative_expression: multiplicative_expression STAR cast_expression  */
#line 677 "src/parser.y"
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
#line 2699 "src/parser.tab.c"
    break;

  case 58: /* multiplicative_expression: multiplicative_expression DIVIDE cast_expression  */
#line 687 "src/parser.y"
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
#line 2714 "src/parser.tab.c"
    break;

  case 59: /* multiplicative_expression: multiplicative_expression MODULUS cast_expression  */
#line 697 "src/parser.y"
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
#line 2729 "src/parser.tab.c"
    break;

  case 60: /* additive_expression: multiplicative_expression  */
#line 710 "src/parser.y"
                                    { 
        dbg("additive_expression -> multiplicative_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2737 "src/parser.tab.c"
    break;

  case 61: /* additive_expression: additive_expression PLUS multiplicative_expression  */
#line 713 "src/parser.y"
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
#line 2752 "src/parser.tab.c"
    break;

  case 62: /* additive_expression: additive_expression MINUS multiplicative_expression  */
#line 723 "src/parser.y"
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
#line 2767 "src/parser.tab.c"
    break;

  case 63: /* shift_expression: additive_expression  */
#line 736 "src/parser.y"
                              { 
        dbg("shift_expression -> additive_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2775 "src/parser.tab.c"
    break;

  case 64: /* shift_expression: shift_expression LEFT_SHIFT additive_expression  */
#line 739 "src/parser.y"
                                                          {
            dbg("shift_expression -> shift_expression << additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " << " + b->place + ";");
          n->type = a->type; (yyval.node) = n;
      }
#line 2789 "src/parser.tab.c"
    break;

  case 65: /* shift_expression: shift_expression RIGHT_SHIFT additive_expression  */
#line 748 "src/parser.y"
                                                           {
            dbg("shift_expression -> shift_expression >> additive_expression");
          Node* a = (yyvsp[-2].node); Node* b = (yyvsp[0].node);
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " >> " + b->place + ";");
          n->type = a->type; (yyval.node) = n;
      }
#line 2803 "src/parser.tab.c"
    break;

  case 66: /* relational_expression: shift_expression  */
#line 760 "src/parser.y"
                           { 
        dbg("relational_expression -> shift_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2811 "src/parser.tab.c"
    break;

  case 67: /* relational_expression: relational_expression GREATER_THAN shift_expression  */
#line 763 "src/parser.y"
                                                              {
          dbg("relational_expression -> relational_expression > shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " > " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2823 "src/parser.tab.c"
    break;

  case 68: /* relational_expression: relational_expression LESS_THAN shift_expression  */
#line 770 "src/parser.y"
                                                           {
          dbg("relational_expression -> relational_expression < shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " < " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2835 "src/parser.tab.c"
    break;

  case 69: /* relational_expression: relational_expression LESS_EQUAL shift_expression  */
#line 777 "src/parser.y"
                                                            {
            dbg("relational_expression -> relational_expression <= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " <= " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2847 "src/parser.tab.c"
    break;

  case 70: /* relational_expression: relational_expression GREATER_EQUAL shift_expression  */
#line 784 "src/parser.y"
                                                               {
            dbg("relational_expression -> relational_expression >= shift_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " >= " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2859 "src/parser.tab.c"
    break;

  case 71: /* equality_expression: relational_expression  */
#line 794 "src/parser.y"
                                { 
        dbg("equality_expression -> relational_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2867 "src/parser.tab.c"
    break;

  case 72: /* equality_expression: equality_expression EQUAL relational_expression  */
#line 797 "src/parser.y"
                                                          {
            dbg("equality_expression -> equality_expression == relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " == " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2879 "src/parser.tab.c"
    break;

  case 73: /* equality_expression: equality_expression NOT_EQUAL relational_expression  */
#line 804 "src/parser.y"
                                                              {
            dbg("equality_expression -> equality_expression != relational_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " != " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2891 "src/parser.tab.c"
    break;

  case 74: /* and_expression: equality_expression  */
#line 814 "src/parser.y"
                              { 
        dbg("and_expression -> equality_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2899 "src/parser.tab.c"
    break;

  case 75: /* and_expression: and_expression BITWISE_AND equality_expression  */
#line 817 "src/parser.y"
                                                         {
            dbg("and_expression -> and_expression & equality_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " & " + b->place + ";");
          (yyval.node) = n;
      }
#line 2911 "src/parser.tab.c"
    break;

  case 76: /* exclusive_or_expression: and_expression  */
#line 827 "src/parser.y"
                         { 
        dbg("exclusive_or_expression -> and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2919 "src/parser.tab.c"
    break;

  case 77: /* exclusive_or_expression: exclusive_or_expression BITWISE_XOR and_expression  */
#line 830 "src/parser.y"
                                                             {
            dbg("exclusive_or_expression -> exclusive_or_expression ^ and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " ^ " + b->place + ";");
          (yyval.node) = n;
      }
#line 2931 "src/parser.tab.c"
    break;

  case 78: /* inclusive_or_expression: exclusive_or_expression  */
#line 840 "src/parser.y"
                                  { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2939 "src/parser.tab.c"
    break;

  case 79: /* inclusive_or_expression: inclusive_or_expression BITWISE_OR exclusive_or_expression  */
#line 843 "src/parser.y"
                                                                     {
            dbg("inclusive_or_expression -> inclusive_or_expression | exclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " | " + b->place + ";");
          (yyval.node) = n;
      }
#line 2951 "src/parser.tab.c"
    break;

  case 80: /* logical_and_expression: inclusive_or_expression  */
#line 853 "src/parser.y"
                                  { 
        dbg("logical_and_expression -> inclusive_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2959 "src/parser.tab.c"
    break;

  case 81: /* logical_and_expression: logical_and_expression LOGICAL_AND inclusive_or_expression  */
#line 856 "src/parser.y"
                                                                     {
            dbg("logical_and_expression -> logical_and_expression && inclusive_or_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " && " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2971 "src/parser.tab.c"
    break;

  case 82: /* logical_or_expression: logical_and_expression  */
#line 866 "src/parser.y"
                                 { 
        dbg("logical_or_expression -> logical_and_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2979 "src/parser.tab.c"
    break;

  case 83: /* logical_or_expression: logical_or_expression LOGICAL_OR logical_and_expression  */
#line 869 "src/parser.y"
                                                                  {
            dbg("logical_or_expression -> logical_or_expression || logical_and_expression");
          Node* a=(yyvsp[-2].node); Node* b=(yyvsp[0].node); Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " || " + b->place + ";");
          n->type = "bool"; (yyval.node) = n;
      }
#line 2991 "src/parser.tab.c"
    break;

  case 84: /* conditional_expression: logical_or_expression  */
#line 879 "src/parser.y"
                                { 
        dbg("conditional_expression -> logical_or_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 2999 "src/parser.tab.c"
    break;

  case 85: /* conditional_expression: logical_or_expression QUESTION_MARK expression COLON conditional_expression  */
#line 882 "src/parser.y"
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
#line 3022 "src/parser.tab.c"
    break;

  case 86: /* assignment_expression: conditional_expression  */
#line 903 "src/parser.y"
                                 { 
        dbg("assignment_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3030 "src/parser.tab.c"
    break;

  case 87: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 906 "src/parser.y"
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
#line 3064 "src/parser.tab.c"
    break;

  case 88: /* assignment_operator: ASSIGN  */
#line 938 "src/parser.y"
                 { 
        dbg("assignment_operator -> =");
        (yyval.str) = (yyvsp[0].str); }
#line 3072 "src/parser.tab.c"
    break;

  case 89: /* assignment_operator: STAR_EQUAL  */
#line 941 "src/parser.y"
                     { 
        dbg("assignment_operator -> *=");
        (yyval.str) = (yyvsp[0].str); }
#line 3080 "src/parser.tab.c"
    break;

  case 90: /* assignment_operator: DIV_EQUAL  */
#line 944 "src/parser.y"
                    { 
        dbg("assignment_operator -> /=");
        (yyval.str) = (yyvsp[0].str); }
#line 3088 "src/parser.tab.c"
    break;

  case 91: /* assignment_operator: MOD_EQUAL  */
#line 947 "src/parser.y"
                    { 
        dbg("assignment_operator -> %=");
        (yyval.str) = (yyvsp[0].str); }
#line 3096 "src/parser.tab.c"
    break;

  case 92: /* assignment_operator: PLUS_EQUAL  */
#line 950 "src/parser.y"
                     { 
        dbg("assignment_operator -> +=");
        (yyval.str) = (yyvsp[0].str); }
#line 3104 "src/parser.tab.c"
    break;

  case 93: /* assignment_operator: MINUS_EQUAL  */
#line 953 "src/parser.y"
                      { 
        dbg("assignment_operator -> -=");
        (yyval.str) = (yyvsp[0].str); }
#line 3112 "src/parser.tab.c"
    break;

  case 94: /* assignment_operator: LEFT_SHIFT_EQ  */
#line 956 "src/parser.y"
                        { 
        dbg("assignment_operator -> <<=");
        (yyval.str) = (yyvsp[0].str); }
#line 3120 "src/parser.tab.c"
    break;

  case 95: /* assignment_operator: RIGHT_SHIFT_EQ  */
#line 959 "src/parser.y"
                         { 
        dbg("assignment_operator -> >>=");
        (yyval.str) = (yyvsp[0].str); }
#line 3128 "src/parser.tab.c"
    break;

  case 96: /* assignment_operator: AND_EQUAL  */
#line 962 "src/parser.y"
                    { 
        dbg("assignment_operator -> &=");
        (yyval.str) = (yyvsp[0].str); }
#line 3136 "src/parser.tab.c"
    break;

  case 97: /* assignment_operator: XOR_EQUAL  */
#line 965 "src/parser.y"
                    { 
        dbg("assignment_operator -> ^=");
        (yyval.str) = (yyvsp[0].str); }
#line 3144 "src/parser.tab.c"
    break;

  case 98: /* assignment_operator: OR_EQUAL  */
#line 968 "src/parser.y"
                   { 
        dbg("assignment_operator -> |=");
        (yyval.str) = (yyvsp[0].str); }
#line 3152 "src/parser.tab.c"
    break;

  case 99: /* expression: assignment_expression  */
#line 974 "src/parser.y"
                                { 
        dbg("expression -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3160 "src/parser.tab.c"
    break;

  case 100: /* expression: expression COMMA assignment_expression  */
#line 977 "src/parser.y"
                                                 {
            dbg("expression -> expression , assignment_expression");
          Node* n = (yyvsp[-2].node);
          Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->place = e->place;
          (yyval.node) = n;
      }
#line 3173 "src/parser.tab.c"
    break;

  case 101: /* constant_expression: conditional_expression  */
#line 988 "src/parser.y"
                                 { 
        dbg("constant_expression -> conditional_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3181 "src/parser.tab.c"
    break;

  case 102: /* declaration: declaration_specifiers SEMICOLON  */
#line 994 "src/parser.y"
                                           {
          dbg("declaration -> declaration_specifiers ;");
          Node* n = new Node();
          (yyval.node) = n;
      }
#line 3191 "src/parser.tab.c"
    break;

  case 103: /* declaration: declaration_specifiers init_declarator_list SEMICOLON  */
#line 999 "src/parser.y"
                                                                {
            dbg("declaration -> declaration_specifiers init_declarator_list ;");
          (yyval.node) = (yyvsp[-1].node);
      }
#line 3200 "src/parser.tab.c"
    break;

  case 104: /* declaration: error SEMICOLON  */
#line 1003 "src/parser.y"
                      {yyerrok;}
#line 3206 "src/parser.tab.c"
    break;

  case 105: /* declaration_specifiers: storage_class_specifier  */
#line 1007 "src/parser.y"
                                  { 
        dbg("declaration_specifiers -> storage_class_specifier");
        (yyval.node) = new Node(); }
#line 3214 "src/parser.tab.c"
    break;

  case 106: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 1010 "src/parser.y"
                                                         { 
        dbg("declaration_specifiers -> storage_class_specifier declaration_specifiers");
        (yyval.node) = (yyvsp[0].node); }
#line 3222 "src/parser.tab.c"
    break;

  case 107: /* declaration_specifiers: type_specifier  */
#line 1013 "src/parser.y"
                         { 
        dbg("declaration_specifiers -> type_specifier");
        lastDeclType = string((yyvsp[0].str)); (yyval.node) = new Node(); }
#line 3230 "src/parser.tab.c"
    break;

  case 108: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 1016 "src/parser.y"
                                                { 
        dbg("declaration_specifiers -> type_specifier declaration_specifiers");
        lastDeclType = string((yyvsp[-1].str)); (yyval.node) = (yyvsp[0].node); }
#line 3238 "src/parser.tab.c"
    break;

  case 109: /* declaration_specifiers: type_qualifier  */
#line 1019 "src/parser.y"
                         { 
        dbg("declaration_specifiers -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3246 "src/parser.tab.c"
    break;

  case 110: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 1022 "src/parser.y"
                                                { 
        dbg("declaration_specifiers -> type_qualifier declaration_specifiers");
        (yyval.node) = (yyvsp[0].node); }
#line 3254 "src/parser.tab.c"
    break;

  case 111: /* init_declarator_list: init_declarator  */
#line 1028 "src/parser.y"
                          { 
        dbg("init_declarator_list -> init_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3262 "src/parser.tab.c"
    break;

  case 112: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 1031 "src/parser.y"
                                                     {
            dbg("init_declarator_list -> init_declarator_list , init_declarator");
          Node* n = (yyvsp[-2].node);
          n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 3273 "src/parser.tab.c"
    break;

  case 113: /* init_declarator: declarator  */
#line 1040 "src/parser.y"
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
#line 3291 "src/parser.tab.c"
    break;

  case 114: /* init_declarator: declarator ASSIGN initializer  */
#line 1053 "src/parser.y"
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
#line 3312 "src/parser.tab.c"
    break;

  case 115: /* storage_class_specifier: TYPEDEF  */
#line 1072 "src/parser.y"
                  { 
        dbg("storage_class_specifier -> TYPEDEF");
        (yyval.node) = new Node(); }
#line 3320 "src/parser.tab.c"
    break;

  case 116: /* storage_class_specifier: STATIC  */
#line 1075 "src/parser.y"
                 { 
        dbg("storage_class_specifier -> STATIC");
        (yyval.node) = new Node(); }
#line 3328 "src/parser.tab.c"
    break;

  case 117: /* storage_class_specifier: AUTO  */
#line 1078 "src/parser.y"
               { 
        dbg("storage_class_specifier -> AUTO");
        (yyval.node) = new Node(); }
#line 3336 "src/parser.tab.c"
    break;

  case 118: /* type_specifier: VOID  */
#line 1084 "src/parser.y"
                 { 
        dbg("type_specifier -> VOID");
        (yyval.str) = strdup("void"); lastDeclType = "void"; }
#line 3344 "src/parser.tab.c"
    break;

  case 119: /* type_specifier: CHAR  */
#line 1087 "src/parser.y"
                 { 
        dbg("type_specifier -> CHAR");
        (yyval.str) = strdup("char"); lastDeclType = "char"; }
#line 3352 "src/parser.tab.c"
    break;

  case 120: /* type_specifier: INT  */
#line 1090 "src/parser.y"
                 { 
        dbg("type_specifier -> INT");
        (yyval.str) = strdup("int"); lastDeclType = "int"; }
#line 3360 "src/parser.tab.c"
    break;

  case 121: /* type_specifier: LONG  */
#line 1093 "src/parser.y"
                 { 
        dbg("type_specifier -> LONG");
        (yyval.str) = strdup("long"); lastDeclType = "long"; }
#line 3368 "src/parser.tab.c"
    break;

  case 122: /* type_specifier: DOUBLE  */
#line 1096 "src/parser.y"
                 { 
        dbg("type_specifier -> DOUBLE");
        (yyval.str) = strdup("double"); lastDeclType = "double"; }
#line 3376 "src/parser.tab.c"
    break;

  case 123: /* type_specifier: BOOL  */
#line 1099 "src/parser.y"
                 { 
        dbg("type_specifier -> BOOL");
        (yyval.str) = strdup("bool"); lastDeclType = "bool"; }
#line 3384 "src/parser.tab.c"
    break;

  case 124: /* type_specifier: STRING  */
#line 1102 "src/parser.y"
                 { 
        dbg("type_specifier -> STRING");
        (yyval.str) = strdup("string"); lastDeclType = "string"; }
#line 3392 "src/parser.tab.c"
    break;

  case 125: /* type_specifier: TYPE_NAME  */
#line 1105 "src/parser.y"
                    { 
        dbg("type_specifier -> TYPE_NAME");
        (yyval.str) = (yyvsp[0].str); lastDeclType = string((yyvsp[0].str)); }
#line 3400 "src/parser.tab.c"
    break;

  case 126: /* struct_or_class_specifier: struct_or_class IDENTIFIER LCURLY struct_or_class_member_list RCURLY  */
#line 1111 "src/parser.y"
                                                                               { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        Node* n = new Node(); (yyval.node) = n; }
#line 3408 "src/parser.tab.c"
    break;

  case 127: /* struct_or_class_specifier: struct_or_class IDENTIFIER  */
#line 1114 "src/parser.y"
                                     { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER");
        Node* n = new Node(); (yyval.node) = n; }
#line 3416 "src/parser.tab.c"
    break;

  case 128: /* struct_or_class: STRUCT  */
#line 1120 "src/parser.y"
                 { 
        dbg("struct_or_class -> STRUCT");
        (yyval.node) = new Node(); }
#line 3424 "src/parser.tab.c"
    break;

  case 129: /* struct_or_class: CLASS  */
#line 1123 "src/parser.y"
                { 
        dbg("struct_or_class -> CLASS");
        (yyval.node) = new Node(); }
#line 3432 "src/parser.tab.c"
    break;

  case 130: /* struct_or_class_member_list: struct_or_class_member  */
#line 1129 "src/parser.y"
                                 { 
        dbg("struct_or_class_member_list -> struct_or_class_member");
        (yyval.node) = (yyvsp[0].node); }
#line 3440 "src/parser.tab.c"
    break;

  case 131: /* struct_or_class_member_list: struct_or_class_member_list struct_or_class_member  */
#line 1132 "src/parser.y"
                                                             { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        Node* n = (yyvsp[-1].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; }
#line 3450 "src/parser.tab.c"
    break;

  case 132: /* struct_or_class_member: access_specifier_label  */
#line 1140 "src/parser.y"
                                 { 
        dbg("struct_or_class_member -> access_specifier_label");
        (yyval.node) = (yyvsp[0].node); }
#line 3458 "src/parser.tab.c"
    break;

  case 133: /* struct_or_class_member: member_declaration  */
#line 1143 "src/parser.y"
                             { 
        dbg("struct_or_class_member -> member_declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 3466 "src/parser.tab.c"
    break;

  case 134: /* access_specifier_label: PUBLIC COLON  */
#line 1149 "src/parser.y"
                       { 
        dbg("access_specifier_label -> PUBLIC :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3474 "src/parser.tab.c"
    break;

  case 135: /* access_specifier_label: PRIVATE COLON  */
#line 1152 "src/parser.y"
                        { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3482 "src/parser.tab.c"
    break;

  case 136: /* access_specifier_label: PROTECTED COLON  */
#line 1155 "src/parser.y"
                          { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); (yyval.node) = n; }
#line 3490 "src/parser.tab.c"
    break;

  case 137: /* member_declaration: specifier_qualifier_list struct_declarator_list SEMICOLON  */
#line 1161 "src/parser.y"
                                                                    { 
        dbg("member_declaration -> specifier_qualifier_list struct_declarator_list ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3498 "src/parser.tab.c"
    break;

  case 138: /* member_declaration: specifier_qualifier_list SEMICOLON  */
#line 1164 "src/parser.y"
                                             { 
        dbg("member_declaration -> specifier_qualifier_list ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3506 "src/parser.tab.c"
    break;

  case 139: /* member_declaration: specifier_qualifier_list declarator compound_statement  */
#line 1167 "src/parser.y"
                                                                 { 
        dbg("member_declaration -> specifier_qualifier_list declarator compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 3514 "src/parser.tab.c"
    break;

  case 140: /* member_declaration: struct_or_class_specifier SEMICOLON  */
#line 1170 "src/parser.y"
                                              { 
        dbg("member_declaration -> struct_or_class_specifier ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3522 "src/parser.tab.c"
    break;

  case 141: /* member_declaration: SEMICOLON  */
#line 1173 "src/parser.y"
                    { 
        dbg("member_declaration -> ;");
        Node* n=new Node(); (yyval.node) = n; }
#line 3530 "src/parser.tab.c"
    break;

  case 142: /* member_declaration: constructor_definition  */
#line 1176 "src/parser.y"
                                 { 
        dbg("member_declaration -> constructor_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 3538 "src/parser.tab.c"
    break;

  case 143: /* member_declaration: destructor_definition  */
#line 1179 "src/parser.y"
                                { 
        dbg("member_declaration -> destructor_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 3546 "src/parser.tab.c"
    break;

  case 144: /* constructor_definition: IDENTIFIER LROUND parameter_list RROUND compound_statement  */
#line 1185 "src/parser.y"
                                                                     {
        dbg("constructor_definition -> IDENTIFIER ( parameter_list ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3555 "src/parser.tab.c"
    break;

  case 145: /* constructor_definition: IDENTIFIER LROUND RROUND compound_statement  */
#line 1189 "src/parser.y"
                                                      {
        dbg("constructor_definition -> IDENTIFIER ( ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3564 "src/parser.tab.c"
    break;

  case 146: /* destructor_definition: TILDE IDENTIFIER LROUND RROUND compound_statement  */
#line 1196 "src/parser.y"
                                                            {
        dbg("destructor_definition -> ~ IDENTIFIER ( ) compound_statement");
          Node* n = new Node(); (yyval.node) = n;
      }
#line 3573 "src/parser.tab.c"
    break;

  case 147: /* struct_declarator_list: struct_declarator  */
#line 1203 "src/parser.y"
                            { 
        dbg("struct_declarator_list -> struct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3581 "src/parser.tab.c"
    break;

  case 148: /* struct_declarator_list: struct_declarator_list COMMA struct_declarator  */
#line 1206 "src/parser.y"
                                                         { 
        dbg("struct_declarator_list -> struct_declarator_list , struct_declarator");
        Node* n = (yyvsp[-2].node); 
        if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); 
        (yyval.node) = n; }
#line 3591 "src/parser.tab.c"
    break;

  case 149: /* struct_declarator: init_declarator  */
#line 1214 "src/parser.y"
                          { 
        dbg("struct_declarator -> init_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3599 "src/parser.tab.c"
    break;

  case 150: /* specifier_qualifier_list: type_specifier specifier_qualifier_list  */
#line 1220 "src/parser.y"
                                                  { 
        dbg("specifier_qualifier_list -> type_specifier specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3607 "src/parser.tab.c"
    break;

  case 151: /* specifier_qualifier_list: type_specifier  */
#line 1223 "src/parser.y"
                         { 
        dbg("specifier_qualifier_list -> type_specifier");
        (yyval.node) = new Node(); }
#line 3615 "src/parser.tab.c"
    break;

  case 152: /* specifier_qualifier_list: type_qualifier specifier_qualifier_list  */
#line 1226 "src/parser.y"
                                                  { 
        dbg("specifier_qualifier_list -> type_qualifier specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3623 "src/parser.tab.c"
    break;

  case 153: /* specifier_qualifier_list: type_qualifier  */
#line 1229 "src/parser.y"
                         { 
        dbg("specifier_qualifier_list -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3631 "src/parser.tab.c"
    break;

  case 154: /* type_qualifier: CONST  */
#line 1235 "src/parser.y"
                { 
        dbg("type_qualifier -> CONST");
        (yyval.node) = new Node(); }
#line 3639 "src/parser.tab.c"
    break;

  case 155: /* declarator: pointer direct_declarator  */
#line 1241 "src/parser.y"
                                    { 
        dbg("declarator -> pointer direct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3647 "src/parser.tab.c"
    break;

  case 156: /* declarator: direct_declarator  */
#line 1244 "src/parser.y"
                            { 
        dbg("declarator -> direct_declarator");
        (yyval.node) = (yyvsp[0].node); }
#line 3655 "src/parser.tab.c"
    break;

  case 157: /* direct_declarator: IDENTIFIER  */
#line 1250 "src/parser.y"
                     {
            dbg("direct_declarator -> IDENTIFIER");
          Node* n = new Node();
          n->place = string((yyvsp[0].str));
          (yyval.node) = n;
      }
#line 3666 "src/parser.tab.c"
    break;

  case 158: /* direct_declarator: LROUND declarator RROUND  */
#line 1256 "src/parser.y"
                                   { 
        dbg("direct_declarator -> ( declarator )");
        (yyval.node) = (yyvsp[-1].node); }
#line 3674 "src/parser.tab.c"
    break;

  case 159: /* direct_declarator: direct_declarator LSQUARE constant_expression RSQUARE  */
#line 1259 "src/parser.y"
                                                                { 
        dbg("direct_declarator -> direct_declarator [ constant_expression ]");
        (yyval.node) = (yyvsp[-3].node); }
#line 3682 "src/parser.tab.c"
    break;

  case 160: /* direct_declarator: direct_declarator LSQUARE RSQUARE  */
#line 1262 "src/parser.y"
                                            { 
        dbg("direct_declarator -> direct_declarator [ ]");
        (yyval.node) = (yyvsp[-2].node); }
#line 3690 "src/parser.tab.c"
    break;

  case 161: /* direct_declarator: direct_declarator LROUND parameter_type_list RROUND  */
#line 1265 "src/parser.y"
                                                              { 
        dbg("direct_declarator -> direct_declarator ( parameter_type_list )");
        (yyval.node) = (yyvsp[-3].node); }
#line 3698 "src/parser.tab.c"
    break;

  case 162: /* direct_declarator: direct_declarator LROUND identifier_list RROUND  */
#line 1268 "src/parser.y"
                                                          { 
        dbg("direct_declarator -> direct_declarator ( identifier_list )");
        (yyval.node) = (yyvsp[-3].node); }
#line 3706 "src/parser.tab.c"
    break;

  case 163: /* direct_declarator: direct_declarator LROUND RROUND  */
#line 1271 "src/parser.y"
                                          { 
        dbg("direct_declarator -> direct_declarator ( )");
        (yyval.node) = (yyvsp[-2].node); }
#line 3714 "src/parser.tab.c"
    break;

  case 164: /* pointer: STAR  */
#line 1277 "src/parser.y"
               { 
        dbg("pointer -> *");
        (yyval.node) = new Node(); }
#line 3722 "src/parser.tab.c"
    break;

  case 165: /* pointer: STAR type_qualifier_list  */
#line 1280 "src/parser.y"
                                   { 
        dbg("pointer -> * type_qualifier_list");
        (yyval.node) = new Node(); }
#line 3730 "src/parser.tab.c"
    break;

  case 166: /* pointer: STAR pointer  */
#line 1283 "src/parser.y"
                       { 
        dbg("pointer -> * pointer");
        (yyval.node) = new Node(); }
#line 3738 "src/parser.tab.c"
    break;

  case 167: /* pointer: STAR type_qualifier_list pointer  */
#line 1286 "src/parser.y"
                                           { 
        dbg("pointer -> * type_qualifier_list pointer");
        (yyval.node) = new Node(); }
#line 3746 "src/parser.tab.c"
    break;

  case 168: /* type_qualifier_list: type_qualifier  */
#line 1292 "src/parser.y"
                         { 
        dbg("type_qualifier_list -> type_qualifier");
        (yyval.node) = new Node(); }
#line 3754 "src/parser.tab.c"
    break;

  case 169: /* type_qualifier_list: type_qualifier_list type_qualifier  */
#line 1295 "src/parser.y"
                                             { 
        dbg("type_qualifier_list -> type_qualifier_list type_qualifier");
        (yyval.node) = new Node(); }
#line 3762 "src/parser.tab.c"
    break;

  case 170: /* parameter_type_list: parameter_list  */
#line 1301 "src/parser.y"
                         {
        dbg("parameter_type_list -> parameter_list"); 
        (yyval.node) = (yyvsp[0].node); }
#line 3770 "src/parser.tab.c"
    break;

  case 171: /* parameter_list: parameter_declaration  */
#line 1307 "src/parser.y"
                                { 
        dbg("parameter_list -> parameter_declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 3778 "src/parser.tab.c"
    break;

  case 172: /* parameter_list: parameter_list COMMA parameter_declaration  */
#line 1310 "src/parser.y"
                                                     {
            dbg("parameter_list -> parameter_list , parameter_declaration");
          Node* n = (yyvsp[-2].node); (yyval.node) = n;
      }
#line 3787 "src/parser.tab.c"
    break;

  case 173: /* parameter_declaration: declaration_specifiers declarator  */
#line 1317 "src/parser.y"
                                            {
            dbg("parameter_declaration -> declaration_specifiers declarator");
          Node* n = new Node();
          n->place = (yyvsp[0].node)->place;
          n->type = lastDeclType;
          (yyval.node) = n;
      }
#line 3799 "src/parser.tab.c"
    break;

  case 174: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 1324 "src/parser.y"
                                                     { 
        dbg("parameter_declaration -> declaration_specifiers abstract_declarator");
        Node* n = new Node(); (yyval.node) = n; }
#line 3807 "src/parser.tab.c"
    break;

  case 175: /* parameter_declaration: declaration_specifiers  */
#line 1327 "src/parser.y"
                                 { 
        dbg("parameter_declaration -> declaration_specifiers");
        Node* n = new Node(); (yyval.node) = n; }
#line 3815 "src/parser.tab.c"
    break;

  case 176: /* identifier_list: IDENTIFIER  */
#line 1333 "src/parser.y"
                     { 
        dbg("identifier_list -> IDENTIFIER");
        (yyval.node) = nullptr; }
#line 3823 "src/parser.tab.c"
    break;

  case 177: /* identifier_list: identifier_list COMMA IDENTIFIER  */
#line 1336 "src/parser.y"
                                           { 
        dbg("identifier_list -> identifier_list , IDENTIFIER");
        (yyval.node) = nullptr; }
#line 3831 "src/parser.tab.c"
    break;

  case 178: /* type_name: specifier_qualifier_list  */
#line 1342 "src/parser.y"
                                   { 
        dbg("type_name -> specifier_qualifier_list");
        (yyval.node) = new Node(); }
#line 3839 "src/parser.tab.c"
    break;

  case 179: /* type_name: specifier_qualifier_list abstract_declarator  */
#line 1345 "src/parser.y"
                                                       { 
        dbg("type_name -> specifier_qualifier_list abstract_declarator");
        (yyval.node) = new Node(); }
#line 3847 "src/parser.tab.c"
    break;

  case 180: /* abstract_declarator: pointer  */
#line 1351 "src/parser.y"
                  { 
        dbg("abstract_declarator -> pointer");
        (yyval.node) = new Node(); }
#line 3855 "src/parser.tab.c"
    break;

  case 181: /* abstract_declarator: direct_abstract_declarator  */
#line 1354 "src/parser.y"
                                     { 
        dbg("abstract_declarator -> direct_abstract_declarator");
        (yyval.node) = new Node(); }
#line 3863 "src/parser.tab.c"
    break;

  case 182: /* abstract_declarator: pointer direct_abstract_declarator  */
#line 1357 "src/parser.y"
                                             { 
        dbg("abstract_declarator -> pointer direct_abstract_declarator");
        (yyval.node) = new Node(); }
#line 3871 "src/parser.tab.c"
    break;

  case 183: /* direct_abstract_declarator: LROUND abstract_declarator RROUND  */
#line 1363 "src/parser.y"
                                            { 
        dbg("direct_abstract_declarator -> ( abstract_declarator )");
        (yyval.node) = new Node(); }
#line 3879 "src/parser.tab.c"
    break;

  case 184: /* direct_abstract_declarator: LSQUARE RSQUARE  */
#line 1366 "src/parser.y"
                          { 
        dbg("direct_abstract_declarator -> [ ]");
        (yyval.node) = new Node(); }
#line 3887 "src/parser.tab.c"
    break;

  case 185: /* direct_abstract_declarator: LSQUARE constant_expression RSQUARE  */
#line 1369 "src/parser.y"
                                              { 
        dbg("direct_abstract_declarator -> [ constant_expression ]");
        (yyval.node) = new Node(); }
#line 3895 "src/parser.tab.c"
    break;

  case 186: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE RSQUARE  */
#line 1372 "src/parser.y"
                                                     { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator [ ]");
        (yyval.node) = new Node(); }
#line 3903 "src/parser.tab.c"
    break;

  case 187: /* direct_abstract_declarator: direct_abstract_declarator LSQUARE constant_expression RSQUARE  */
#line 1375 "src/parser.y"
                                                                         { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator [ constant_expression ]");
        (yyval.node) = new Node(); }
#line 3911 "src/parser.tab.c"
    break;

  case 188: /* direct_abstract_declarator: LROUND RROUND  */
#line 1378 "src/parser.y"
                        { 
        dbg("direct_abstract_declarator -> ( )");
        (yyval.node) = new Node(); }
#line 3919 "src/parser.tab.c"
    break;

  case 189: /* direct_abstract_declarator: LROUND parameter_type_list RROUND  */
#line 1381 "src/parser.y"
                                            { 
        dbg("direct_abstract_declarator -> ( parameter_type_list )");
        (yyval.node) = new Node(); }
#line 3927 "src/parser.tab.c"
    break;

  case 190: /* direct_abstract_declarator: direct_abstract_declarator LROUND RROUND  */
#line 1384 "src/parser.y"
                                                   { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator ( )");
        (yyval.node) = new Node(); }
#line 3935 "src/parser.tab.c"
    break;

  case 191: /* direct_abstract_declarator: direct_abstract_declarator LROUND parameter_type_list RROUND  */
#line 1387 "src/parser.y"
                                                                       { 
        dbg("direct_abstract_declarator -> direct_abstract_declarator ( parameter_type_list )");
        (yyval.node) = new Node(); }
#line 3943 "src/parser.tab.c"
    break;

  case 192: /* initializer: assignment_expression  */
#line 1393 "src/parser.y"
                                { 
        dbg("initializer -> assignment_expression");
        (yyval.node) = (yyvsp[0].node); }
#line 3951 "src/parser.tab.c"
    break;

  case 193: /* initializer: LCURLY initializer_list RCURLY  */
#line 1396 "src/parser.y"
                                         { 
        dbg("initializer -> { initializer_list }");
        (yyval.node) = (yyvsp[-1].node); }
#line 3959 "src/parser.tab.c"
    break;

  case 194: /* initializer: LCURLY initializer_list COMMA RCURLY  */
#line 1399 "src/parser.y"
                                               { 
        dbg("initializer -> { initializer_list , }");
        (yyval.node) = (yyvsp[-2].node); }
#line 3967 "src/parser.tab.c"
    break;

  case 195: /* initializer_list: initializer  */
#line 1405 "src/parser.y"
                      { 
        dbg("initializer_list -> initializer");
        (yyval.node) = (yyvsp[0].node); }
#line 3975 "src/parser.tab.c"
    break;

  case 196: /* initializer_list: initializer_list COMMA initializer  */
#line 1408 "src/parser.y"
                                             {
            dbg("initializer_list -> initializer_list , initializer");
          Node* n = (yyvsp[-2].node); n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); (yyval.node) = n;
      }
#line 3984 "src/parser.tab.c"
    break;

  case 197: /* statement: labeled_statement  */
#line 1415 "src/parser.y"
                            { 
        dbg("statement -> labeled_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 3992 "src/parser.tab.c"
    break;

  case 198: /* statement: compound_statement  */
#line 1418 "src/parser.y"
                             { 
        dbg("statement -> compound_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4000 "src/parser.tab.c"
    break;

  case 199: /* statement: expression_statement  */
#line 1421 "src/parser.y"
                               { 
        dbg("statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4008 "src/parser.tab.c"
    break;

  case 200: /* statement: selection_statement  */
#line 1424 "src/parser.y"
                              { 
        dbg("statement -> selection_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4016 "src/parser.tab.c"
    break;

  case 201: /* statement: iteration_statement  */
#line 1427 "src/parser.y"
                              { 
        dbg("statement -> iteration_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4024 "src/parser.tab.c"
    break;

  case 202: /* statement: jump_statement  */
#line 1430 "src/parser.y"
                         { 
        dbg("statement -> jump_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4032 "src/parser.tab.c"
    break;

  case 203: /* statement: io_statement  */
#line 1433 "src/parser.y"
                       { 
        dbg("statement -> io_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4040 "src/parser.tab.c"
    break;

  case 204: /* io_statement: cout_expression SEMICOLON  */
#line 1439 "src/parser.y"
                                { 
        dbg("io_statement -> cout_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4048 "src/parser.tab.c"
    break;

  case 205: /* io_statement: cin_expression SEMICOLON  */
#line 1442 "src/parser.y"
                                { 
        dbg("io_statement -> cin_expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4056 "src/parser.tab.c"
    break;

  case 206: /* cout_expression: COUT insertion_list  */
#line 1448 "src/parser.y"
                          { 
        dbg("cout_expression -> COUT insertion_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4064 "src/parser.tab.c"
    break;

  case 207: /* insertion_list: LEFT_SHIFT assignment_expression  */
#line 1454 "src/parser.y"
                                       {
          dbg("insertion_list -> LEFT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node);
          Node* n = new Node();
          n->code = e->code; n->code.push_back("print " + e->place + ";"); (yyval.node) = n;
      }
#line 4075 "src/parser.tab.c"
    break;

  case 208: /* insertion_list: LEFT_SHIFT ENDL  */
#line 1460 "src/parser.y"
                          {
            dbg("insertion_list -> LEFT_SHIFT ENDL");
          Node* n = new Node();
          n->code.push_back("print endl;"); (yyval.node) = n;
      }
#line 4085 "src/parser.tab.c"
    break;

  case 209: /* insertion_list: insertion_list LEFT_SHIFT ENDL  */
#line 1465 "src/parser.y"
                                         {
            dbg("insertion_list -> insertion_list LEFT_SHIFT ENDL");
          Node* n = (yyvsp[-2].node); n->code.push_back("print endl;"); (yyval.node) = n;
      }
#line 4094 "src/parser.tab.c"
    break;

  case 210: /* insertion_list: insertion_list LEFT_SHIFT assignment_expression  */
#line 1469 "src/parser.y"
                                                          {
            dbg("insertion_list -> insertion_list LEFT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("print " + e->place + ";"); (yyval.node) = n;
      }
#line 4105 "src/parser.tab.c"
    break;

  case 211: /* cin_expression: CIN extraction_list  */
#line 1478 "src/parser.y"
                          { 
        dbg("cin_expression -> CIN extraction_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4113 "src/parser.tab.c"
    break;

  case 212: /* extraction_list: RIGHT_SHIFT assignment_expression  */
#line 1484 "src/parser.y"
                                        {
            dbg("extraction_list -> RIGHT_SHIFT assignment_expression");
          Node* e = (yyvsp[0].node); Node* n = new Node();
          n->code = e->code; n->code.push_back("read " + e->place + ";"); (yyval.node) = n;
      }
#line 4123 "src/parser.tab.c"
    break;

  case 213: /* extraction_list: extraction_list RIGHT_SHIFT assignment_expression  */
#line 1489 "src/parser.y"
                                                        {
            dbg("extraction_list -> extraction_list RIGHT_SHIFT assignment_expression");
          Node* n = (yyvsp[-2].node); Node* e = (yyvsp[0].node);
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("read " + e->place + ";"); (yyval.node) = n;
      }
#line 4134 "src/parser.tab.c"
    break;

  case 214: /* labeled_statement: IDENTIFIER COLON statement  */
#line 1498 "src/parser.y"
                                     {
          dbg("labeled_statement -> IDENTIFIER : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string((yyvsp[-2].str)) + ":");
          (yyval.node) = s;
      }
#line 4145 "src/parser.tab.c"
    break;

  case 215: /* labeled_statement: CASE constant_expression COLON statement  */
#line 1504 "src/parser.y"
                                                   {
            dbg("labeled_statement -> CASE constant_expression : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string("case ") + (yyvsp[-2].node)->place + ":");
          (yyval.node) = s;
      }
#line 4156 "src/parser.tab.c"
    break;

  case 216: /* labeled_statement: DEFAULT COLON statement  */
#line 1510 "src/parser.y"
                                  {
            dbg("labeled_statement -> DEFAULT : statement");
          Node* s = (yyvsp[0].node);
          s->code.insert(s->code.begin(), string("default:"));
          (yyval.node) = s;
      }
#line 4167 "src/parser.tab.c"
    break;

  case 217: /* compound_statement: LCURLY RCURLY  */
#line 1519 "src/parser.y"
                        {
            dbg("compound_statement -> { }");
          pushScope();
          Node* n = new Node();
          popScope();
          (yyval.node) = n;
      }
#line 4179 "src/parser.tab.c"
    break;

  case 218: /* compound_statement: LCURLY statement_list RCURLY  */
#line 1526 "src/parser.y"
                                       {
            dbg("compound_statement -> { statement_list }");
          pushScope();
          Node* n = (yyvsp[-1].node);
          popScope();
          (yyval.node) = n;
      }
#line 4191 "src/parser.tab.c"
    break;

  case 219: /* statement_list: block_item  */
#line 1536 "src/parser.y"
                     { 
        dbg("statement_list -> block_item");
        (yyval.node) = (yyvsp[0].node); }
#line 4199 "src/parser.tab.c"
    break;

  case 220: /* statement_list: statement_list block_item  */
#line 1539 "src/parser.y"
                                    {
            dbg("statement_list -> statement_list block_item");
          Node* n = (yyvsp[-1].node);
          if ((yyvsp[0].node)) n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end());
          (yyval.node) = n;
      }
#line 4210 "src/parser.tab.c"
    break;

  case 221: /* block_item: statement  */
#line 1548 "src/parser.y"
                { 
        dbg("block_item -> statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4218 "src/parser.tab.c"
    break;

  case 222: /* block_item: declaration  */
#line 1551 "src/parser.y"
                  { 
        dbg("block_item -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4226 "src/parser.tab.c"
    break;

  case 223: /* block_item: error RCURLY  */
#line 1554 "src/parser.y"
                   { yyerrok;}
#line 4232 "src/parser.tab.c"
    break;

  case 224: /* expression_statement: SEMICOLON  */
#line 1558 "src/parser.y"
                    { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4240 "src/parser.tab.c"
    break;

  case 225: /* expression_statement: expression SEMICOLON  */
#line 1561 "src/parser.y"
                               { 
        dbg("expression_statement -> expression ;");
        (yyval.node) = (yyvsp[-1].node); }
#line 4248 "src/parser.tab.c"
    break;

  case 226: /* selection_statement: IF LROUND expression RROUND statement  */
#line 1567 "src/parser.y"
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
#line 4264 "src/parser.tab.c"
    break;

  case 227: /* selection_statement: IF LROUND expression RROUND statement ELSE statement  */
#line 1578 "src/parser.y"
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
#line 4283 "src/parser.tab.c"
    break;

  case 228: /* selection_statement: SWITCH LROUND expression RROUND statement  */
#line 1592 "src/parser.y"
                                                    {
            dbg("selection_statement -> SWITCH ( expression ) statement");
          Node* n = (yyvsp[0].node); (yyval.node) = n;
      }
#line 4292 "src/parser.tab.c"
    break;

  case 229: /* iteration_statement: WHILE LROUND expression RROUND statement  */
#line 1599 "src/parser.y"
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
#line 4310 "src/parser.tab.c"
    break;

  case 230: /* iteration_statement: UNTIL LROUND expression RROUND statement  */
#line 1612 "src/parser.y"
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
#line 4326 "src/parser.tab.c"
    break;

  case 231: /* iteration_statement: DO statement WHILE LROUND expression RROUND SEMICOLON  */
#line 1623 "src/parser.y"
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
#line 4342 "src/parser.tab.c"
    break;

  case 232: /* iteration_statement: FOR LROUND for_init_statement expression_statement RROUND statement  */
#line 1634 "src/parser.y"
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
#line 4363 "src/parser.tab.c"
    break;

  case 233: /* iteration_statement: FOR LROUND for_init_statement expression_statement expression RROUND statement  */
#line 1650 "src/parser.y"
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
#line 4385 "src/parser.tab.c"
    break;

  case 234: /* for_init_statement: expression_statement  */
#line 1670 "src/parser.y"
                               { 
        dbg("for_init_statement -> expression_statement");
        (yyval.node) = (yyvsp[0].node); }
#line 4393 "src/parser.tab.c"
    break;

  case 235: /* for_init_statement: declaration  */
#line 1673 "src/parser.y"
                      { 
        dbg("for_init_statement -> declaration");
        (yyval.node) = (yyvsp[0].node); }
#line 4401 "src/parser.tab.c"
    break;

  case 236: /* jump_statement: GOTO IDENTIFIER SEMICOLON  */
#line 1679 "src/parser.y"
                                    {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string((yyvsp[-1].str)) + ";");
          (yyval.node) = n;
      }
#line 4412 "src/parser.tab.c"
    break;

  case 237: /* jump_statement: CONTINUE SEMICOLON  */
#line 1685 "src/parser.y"
                             {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); n->code.push_back("continue;"); (yyval.node) = n;
      }
#line 4421 "src/parser.tab.c"
    break;

  case 238: /* jump_statement: BREAK SEMICOLON  */
#line 1689 "src/parser.y"
                          {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); n->code.push_back("break;"); (yyval.node) = n;
      }
#line 4430 "src/parser.tab.c"
    break;

  case 239: /* jump_statement: RETURN SEMICOLON  */
#line 1693 "src/parser.y"
                           {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); n->code.push_back("return;"); (yyval.node) = n;
      }
#line 4439 "src/parser.tab.c"
    break;

  case 240: /* jump_statement: RETURN expression SEMICOLON  */
#line 1697 "src/parser.y"
                                      {
            dbg("jump_statement -> RETURN expression ;");
          Node* expr = (yyvsp[-1].node);
          Node* n = new Node();
          n->code = expr->code;
          n->code.push_back("return " + expr->place + ";");
          (yyval.node) = n;
      }
#line 4452 "src/parser.tab.c"
    break;

  case 241: /* translation_unit: external_declaration  */
#line 1708 "src/parser.y"
                               { 
        dbg("translation_unit -> external_declaration");
        finalRoot = (yyvsp[0].node); (yyval.node) = (yyvsp[0].node); }
#line 4460 "src/parser.tab.c"
    break;

  case 242: /* translation_unit: translation_unit external_declaration  */
#line 1711 "src/parser.y"
                                                {
            dbg("translation_unit -> translation_unit external_declaration");
          Node* a = (yyvsp[-1].node); Node* b = (yyvsp[0].node);
          if (a) { a->code.insert(a->code.end(), b->code.begin(), b->code.end()); finalRoot = a; (yyval.node) = a; }
          else { finalRoot = b; (yyval.node) = b; }
      }
#line 4471 "src/parser.tab.c"
    break;

  case 243: /* translation_unit: error  */
#line 1717 "src/parser.y"
            { yyerrok;}
#line 4477 "src/parser.tab.c"
    break;

  case 244: /* external_declaration: function_definition  */
#line 1721 "src/parser.y"
                              { 
        dbg("external_declaration -> function_definition");
        (yyval.node) = (yyvsp[0].node); }
#line 4485 "src/parser.tab.c"
    break;

  case 245: /* external_declaration: struct_or_class_specifier SEMICOLON  */
#line 1724 "src/parser.y"
                                              { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        Node* n = new Node(); (yyval.node) = n; }
#line 4493 "src/parser.tab.c"
    break;

  case 246: /* external_declaration: declaration  */
#line 1727 "src/parser.y"
                      {
        dbg("external_declaration -> declaration");
         (yyval.node) = (yyvsp[0].node); }
#line 4501 "src/parser.tab.c"
    break;

  case 247: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 1733 "src/parser.y"
                                                               {
            dbg("function_definition -> declaration_specifiers declarator compound_statement");
          string fname = (yyvsp[-1].node)->place;
          if (fname.empty()) fname = "anon";
          Symbol* s = lookupSymbol(fname);
          if (s && s->isFunction) yyerror("Function redeclaration: " + fname);
          else declareSymbol(fname, "function", true, 0);
          currentFunction = fname;
          localTemp = 0; localLabel = 0;
          Node* n = new Node();
          n->code.push_back(fname + ":");
          if ((yyvsp[0].node)) { pushScope(); n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); popScope(); }
          finalRoot = n;
          (yyval.node) = n;
      }
#line 4521 "src/parser.tab.c"
    break;

  case 248: /* function_definition: declarator compound_statement  */
#line 1748 "src/parser.y"
                                        {
            dbg("function_definition -> declarator compound_statement");
          string fname = (yyvsp[-1].node)->place;
          if (fname.empty()) fname = "anon";
          Symbol* s = lookupSymbol(fname);
          if (s && s->isFunction) yyerror("Function redeclaration: " + fname);
          else declareSymbol(fname, "function", true, 0);
          currentFunction = fname; localTemp = 0; localLabel = 0;
          Node* n = new Node();
          n->code.push_back(fname + ":");
          if ((yyvsp[0].node)) { pushScope(); n->code.insert(n->code.end(), (yyvsp[0].node)->code.begin(), (yyvsp[0].node)->code.end()); popScope(); }
          finalRoot = n;
          (yyval.node) = n;
      }
#line 4540 "src/parser.tab.c"
    break;

  case 249: /* function_definition: error RCURLY  */
#line 1762 "src/parser.y"
                   { yyerrok;}
#line 4546 "src/parser.tab.c"
    break;

  case 250: /* lambda_expression: LSQUARE lambda_capture_clause RSQUARE lambda_declarator compound_statement  */
#line 1766 "src/parser.y"
                                                                                 { 
        dbg("lambda_expression -> [ lambda_capture_clause ] lambda_declarator compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 4554 "src/parser.tab.c"
    break;

  case 251: /* lambda_expression: LSQUARE lambda_capture_clause RSQUARE compound_statement  */
#line 1769 "src/parser.y"
                                                               { 
        dbg("lambda_expression -> [ lambda_capture_clause ] compound_statement");
        Node* n=new Node(); (yyval.node) = n; }
#line 4562 "src/parser.tab.c"
    break;

  case 252: /* lambda_declarator: lambda_parameter_clause trailing_return_opt  */
#line 1775 "src/parser.y"
                                                  { 
        dbg("lambda_declarator -> lambda_parameter_clause trailing_return_opt");
        (yyval.node) = (yyvsp[-1].node); }
#line 4570 "src/parser.tab.c"
    break;

  case 253: /* lambda_parameter_clause: LROUND RROUND  */
#line 1781 "src/parser.y"
                    { 
        dbg("lambda_parameter_clause -> ( )");
        (yyval.node) = new Node(); }
#line 4578 "src/parser.tab.c"
    break;

  case 254: /* lambda_parameter_clause: LROUND parameter_list RROUND  */
#line 1784 "src/parser.y"
                                   {
        dbg("lambda_parameter_clause -> ( parameter_list )");
         (yyval.node) = (yyvsp[-1].node); }
#line 4586 "src/parser.tab.c"
    break;

  case 255: /* trailing_return_opt: %empty  */
#line 1790 "src/parser.y"
       { 
        dbg("trailing_return_opt -> <empty>");
        (yyval.node) = nullptr; }
#line 4594 "src/parser.tab.c"
    break;

  case 256: /* trailing_return_opt: ARROW type_name  */
#line 1793 "src/parser.y"
                      { 
        dbg("trailing_return_opt -> ARROW type_name");
        (yyval.node) = (yyvsp[0].node); }
#line 4602 "src/parser.tab.c"
    break;

  case 257: /* lambda_capture_clause: ASSIGN  */
#line 1799 "src/parser.y"
             { 
        dbg("lambda_capture_clause -> =");
        (yyval.node) = new Node(); }
#line 4610 "src/parser.tab.c"
    break;

  case 258: /* lambda_capture_clause: capture_list  */
#line 1802 "src/parser.y"
                   { 
        dbg("lambda_capture_clause -> capture_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4618 "src/parser.tab.c"
    break;

  case 259: /* lambda_capture_clause: capture_list COMMA ASSIGN  */
#line 1805 "src/parser.y"
                                { 
        dbg("lambda_capture_clause -> capture_list , =");
        (yyval.node) = (yyvsp[-2].node); }
#line 4626 "src/parser.tab.c"
    break;

  case 260: /* lambda_capture_clause: ASSIGN COMMA capture_list  */
#line 1808 "src/parser.y"
                                { 
        dbg("lambda_capture_clause -> = , capture_list");
        (yyval.node) = (yyvsp[0].node); }
#line 4634 "src/parser.tab.c"
    break;

  case 261: /* capture_list: IDENTIFIER  */
#line 1814 "src/parser.y"
                 { 
        dbg("capture_list -> IDENTIFIER");
        Node* n=new Node(); (yyval.node) = n; }
#line 4642 "src/parser.tab.c"
    break;

  case 262: /* capture_list: capture_list COMMA IDENTIFIER  */
#line 1817 "src/parser.y"
                                    {
        dbg("capture_list -> capture_list , IDENTIFIER"); 
        Node* n=(yyvsp[-2].node); (yyval.node) = n; }
#line 4650 "src/parser.tab.c"
    break;


#line 4654 "src/parser.tab.c"

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

#line 1822 "src/parser.y"



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

    cerr<< "No errors found.\n";
    cerr<< "Generating three-address code:\n";

    if (finalRoot) {
        for (size_t i = 0; i < finalRoot->code.size(); ++i) {
            cout << "["<<(i+1) << "] " << finalRoot->code[i] << "\n";
        }
    }

    return 0;
}

