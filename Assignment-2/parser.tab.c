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
#line 1 "parser.y"

    #include <iostream>
    #include <string.h>
    #include <iomanip>
    #include <vector>
    #include <string>
    #include <cstdlib>
    using namespace std;

    #define MAX_ARGS 100

    extern int yylex();
    extern int yylineno;
    extern char *yytext;

    int count_symbol = 0;
    int count_const  = 0;

    struct symbol_table {
        string id_name;
        string data_type;
        string type;
        int    line_no;
    } symbol_table[1000];

    struct const_table {
        string value;
        string type;
        int    line_no;
    } const_table[1000];

    void print_symbol_table() {
        cout << "SYMBOL TABLE\n";
        cout << "---------------------------------------------------------------\n";
        cout << left
            << setw(20) << "NAME"
            << setw(20) << "DATATYPE"
            << setw(20) << "TYPE"
            << setw(10) << "LINE"
            << "\n";
        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < count_symbol; i++) {
            cout << left
                << setw(20) << symbol_table[i].id_name
                << setw(20) << symbol_table[i].data_type
                << setw(20) << symbol_table[i].type
                << setw(10) << symbol_table[i].line_no
                << "\n";
        }

        cout << "---------------------------------------------------------------\n";
    }

    void print_constant_table() {
        cout << "CONSTANT TABLE\n";
        cout << "---------------------------------------------------------------\n";
        cout << left
            << setw(25) << "VALUE"
            << setw(20) << "TYPE"
            << setw(10) << "LINE"
            << "\n";
        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < count_const; i++) {
            cout << left
                << setw(25) << const_table[i].value
                << setw(20) << const_table[i].type
                << setw(10) << const_table[i].line_no
                << "\n";
        }

        cout << "---------------------------------------------------------------\n";
    }

    static char* curr_decl_spec  = NULL; 
    static char* curr_param_spec = NULL; 
    static char* curr_func_spec  = NULL; 

    extern int last_ident_lineno;        
    int curr_decl_lineno = 0;            
    char* last_declarator_pointer = NULL;

    static vector<string> pending_ids;
    static const char* pending_role = "IDENTIFIER"; 

    static char* sdup(const char* s) {
        return s ? strdup(s) : strdup("");
    }
    static char* cat2(const char* a, const char* b) {
        size_t la = a ? strlen(a) : 0, lb = b ? strlen(b) : 0;
        char* r = (char*)malloc(la + lb + 2);
        r[0] = 0;
        if (la) { memcpy(r, a, la); r[la] = 0; }
        if (la && lb) strcat(r, " ");
        if (lb) strcat(r, b);
        return r;
    }
    static void push_id(char* s) {
        pending_ids.emplace_back(s ? s : "");
    }

    void insert_symbol_table (char* yytext, const char* data_type, const char* type) {
        symbol_table[count_symbol].id_name   = yytext;
        if (last_declarator_pointer && last_declarator_pointer[0]) {
            symbol_table[count_symbol].data_type = data_type && data_type[0] ? cat2(data_type, last_declarator_pointer) : sdup(last_declarator_pointer);
        } else {
            symbol_table[count_symbol].data_type = data_type ? data_type : "";
        }
        symbol_table[count_symbol].type      = type;
        symbol_table[count_symbol].line_no   = curr_decl_lineno ? curr_decl_lineno : yylineno;
        curr_decl_lineno = 0;
        last_declarator_pointer = NULL;
        count_symbol++;
    }

    void insert_const_symbol_table(char ch, char* yytext) {
        string t;
        switch(ch) {
            case 'I': t = "DECIMAL_LITERAL";    break;
            case 'D': t = "DOUBLE_LITERAL";     break;
            case 'E': t = "EXPONENT_LITERAL";   break;
            case 'C': t = "CHAR_LITERAL";       break;
            case 'S': t = "STRING_LITERAL";     break;
            case 'B': t = "BOOL_LITERAL";       break;
            case 'N': t = "NULLPTR";            break;
            default:  t = "UNKNOWN";            break;
        }
        const_table[count_const].value  = yytext;
        const_table[count_const].type   = t;
        const_table[count_const].line_no= yylineno;
        count_const++;
    }

    void yyerror(const char *s) {
        cerr << "Error: " << s << " at line " << yylineno << " near '" << yytext << "'" << endl;
    }


    int is_type_name(const char* s) {
        if (!s || s[0] == '\0') return 0;         
        for (int i = 0; i < count_symbol; ++i) {
            if (symbol_table[i].id_name == s && symbol_table[i].type == "TYPE") {
                return 1;
            }
        }
        return 0;
    }
    
    static void flush_pending(const char* spec, const char* role) {
        for (auto &id : pending_ids) {
            insert_symbol_table((char*)id.c_str(), spec ? spec : "", role ? role : "IDENTIFIER");
        }
        pending_ids.clear();
    }

#line 228 "parser.tab.c"

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
  YYSYMBOL_PLUS = 4,                       /* PLUS  */
  YYSYMBOL_MINUS = 5,                      /* MINUS  */
  YYSYMBOL_STAR = 6,                       /* STAR  */
  YYSYMBOL_DIVIDE = 7,                     /* DIVIDE  */
  YYSYMBOL_MODULUS = 8,                    /* MODULUS  */
  YYSYMBOL_ASSIGN = 9,                     /* ASSIGN  */
  YYSYMBOL_INCREMENT = 10,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 11,                 /* DECREMENT  */
  YYSYMBOL_EQUAL = 12,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 13,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 14,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 15,              /* GREATER_THAN  */
  YYSYMBOL_LESS_EQUAL = 16,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 17,             /* GREATER_EQUAL  */
  YYSYMBOL_BITWISE_AND = 18,               /* BITWISE_AND  */
  YYSYMBOL_BITWISE_OR = 19,                /* BITWISE_OR  */
  YYSYMBOL_BITWISE_XOR = 20,               /* BITWISE_XOR  */
  YYSYMBOL_LEFT_SHIFT = 21,                /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 22,               /* RIGHT_SHIFT  */
  YYSYMBOL_ARROW = 23,                     /* ARROW  */
  YYSYMBOL_LOGICAL_NOT = 24,               /* LOGICAL_NOT  */
  YYSYMBOL_LOGICAL_AND = 25,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 26,                /* LOGICAL_OR  */
  YYSYMBOL_PLUS_EQUAL = 27,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 28,               /* MINUS_EQUAL  */
  YYSYMBOL_STAR_EQUAL = 29,                /* STAR_EQUAL  */
  YYSYMBOL_DIV_EQUAL = 30,                 /* DIV_EQUAL  */
  YYSYMBOL_MOD_EQUAL = 31,                 /* MOD_EQUAL  */
  YYSYMBOL_AND_EQUAL = 32,                 /* AND_EQUAL  */
  YYSYMBOL_OR_EQUAL = 33,                  /* OR_EQUAL  */
  YYSYMBOL_XOR_EQUAL = 34,                 /* XOR_EQUAL  */
  YYSYMBOL_LEFT_SHIFT_EQ = 35,             /* LEFT_SHIFT_EQ  */
  YYSYMBOL_RIGHT_SHIFT_EQ = 36,            /* RIGHT_SHIFT_EQ  */
  YYSYMBOL_LROUND = 37,                    /* LROUND  */
  YYSYMBOL_RROUND = 38,                    /* RROUND  */
  YYSYMBOL_LCURLY = 39,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 40,                    /* RCURLY  */
  YYSYMBOL_LSQUARE = 41,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 42,                   /* RSQUARE  */
  YYSYMBOL_SEMICOLON = 43,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_COMMA = 45,                     /* COMMA  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_QUESTION_MARK = 47,             /* QUESTION_MARK  */
  YYSYMBOL_TILDE = 48,                     /* TILDE  */
  YYSYMBOL_IF = 49,                        /* IF  */
  YYSYMBOL_ELSE = 50,                      /* ELSE  */
  YYSYMBOL_SWITCH = 51,                    /* SWITCH  */
  YYSYMBOL_CASE = 52,                      /* CASE  */
  YYSYMBOL_DEFAULT = 53,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 54,                     /* WHILE  */
  YYSYMBOL_DO = 55,                        /* DO  */
  YYSYMBOL_FOR = 56,                       /* FOR  */
  YYSYMBOL_GOTO = 57,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 58,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 59,                     /* BREAK  */
  YYSYMBOL_RETURN = 60,                    /* RETURN  */
  YYSYMBOL_UNTIL = 61,                     /* UNTIL  */
  YYSYMBOL_SIZEOF = 62,                    /* SIZEOF  */
  YYSYMBOL_VOID = 63,                      /* VOID  */
  YYSYMBOL_INT = 64,                       /* INT  */
  YYSYMBOL_DOUBLE = 65,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 66,                      /* CHAR  */
  YYSYMBOL_BOOL = 67,                      /* BOOL  */
  YYSYMBOL_STRING = 68,                    /* STRING  */
  YYSYMBOL_LONG = 69,                      /* LONG  */
  YYSYMBOL_TRUE = 70,                      /* TRUE  */
  YYSYMBOL_FALSE = 71,                     /* FALSE  */
  YYSYMBOL_NULLPTR = 72,                   /* NULLPTR  */
  YYSYMBOL_AUTO = 73,                      /* AUTO  */
  YYSYMBOL_STATIC = 74,                    /* STATIC  */
  YYSYMBOL_CONST = 75,                     /* CONST  */
  YYSYMBOL_CLASS = 76,                     /* CLASS  */
  YYSYMBOL_STRUCT = 77,                    /* STRUCT  */
  YYSYMBOL_PUBLIC = 78,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 79,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 80,                 /* PROTECTED  */
  YYSYMBOL_DELETE = 81,                    /* DELETE  */
  YYSYMBOL_NEW = 82,                       /* NEW  */
  YYSYMBOL_CIN = 83,                       /* CIN  */
  YYSYMBOL_COUT = 84,                      /* COUT  */
  YYSYMBOL_ENDL = 85,                      /* ENDL  */
  YYSYMBOL_TYPE_NAME = 86,                 /* TYPE_NAME  */
  YYSYMBOL_IDENTIFIER = 87,                /* IDENTIFIER  */
  YYSYMBOL_DECIMAL_LITERAL = 88,           /* DECIMAL_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 89,            /* DOUBLE_LITERAL  */
  YYSYMBOL_EXPONENT_LITERAL = 90,          /* EXPONENT_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 91,         /* CHARACTER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 92,            /* STRING_LITERAL  */
  YYSYMBOL_FUNCTION = 93,                  /* FUNCTION  */
  YYSYMBOL_INVALID_IDENTIFIER = 94,        /* INVALID_IDENTIFIER  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_translation_unit = 96,          /* translation_unit  */
  YYSYMBOL_external_declaration = 97,      /* external_declaration  */
  YYSYMBOL_declaration = 98,               /* declaration  */
  YYSYMBOL_99_1 = 99,                      /* $@1  */
  YYSYMBOL_100_2 = 100,                    /* $@2  */
  YYSYMBOL_declaration_specifiers = 101,   /* declaration_specifiers  */
  YYSYMBOL_storage_class_specifier = 102,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 103,           /* type_specifier  */
  YYSYMBOL_init_declarator_list_no_func = 104, /* init_declarator_list_no_func  */
  YYSYMBOL_init_declarator_no_func = 105,  /* init_declarator_no_func  */
  YYSYMBOL_declarator_no_func = 106,       /* declarator_no_func  */
  YYSYMBOL_direct_declarator_no_func = 107, /* direct_declarator_no_func  */
  YYSYMBOL_declarator = 108,               /* declarator  */
  YYSYMBOL_pointer = 109,                  /* pointer  */
  YYSYMBOL_direct_declarator = 110,        /* direct_declarator  */
  YYSYMBOL_parameter_type_list = 111,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 112,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 113,    /* parameter_declaration  */
  YYSYMBOL_114_3 = 114,                    /* $@3  */
  YYSYMBOL_class_specifier = 115,          /* class_specifier  */
  YYSYMBOL_member_specification = 116,     /* member_specification  */
  YYSYMBOL_member_declaration = 117,       /* member_declaration  */
  YYSYMBOL_118_4 = 118,                    /* $@4  */
  YYSYMBOL_member_declarator_list = 119,   /* member_declarator_list  */
  YYSYMBOL_member_declarator = 120,        /* member_declarator  */
  YYSYMBOL_function_definition = 121,      /* function_definition  */
  YYSYMBOL_122_5 = 122,                    /* $@5  */
  YYSYMBOL_123_6 = 123,                    /* $@6  */
  YYSYMBOL_function_declarator = 124,      /* function_declarator  */
  YYSYMBOL_direct_function_declarator = 125, /* direct_function_declarator  */
  YYSYMBOL_statement = 126,                /* statement  */
  YYSYMBOL_compound_statement = 127,       /* compound_statement  */
  YYSYMBOL_block_item_list = 128,          /* block_item_list  */
  YYSYMBOL_block_item = 129,               /* block_item  */
  YYSYMBOL_selection_statement = 130,      /* selection_statement  */
  YYSYMBOL_switch_body = 131,              /* switch_body  */
  YYSYMBOL_case_list = 132,                /* case_list  */
  YYSYMBOL_case_label = 133,               /* case_label  */
  YYSYMBOL_iteration_statement = 134,      /* iteration_statement  */
  YYSYMBOL_expression_opt = 135,           /* expression_opt  */
  YYSYMBOL_label = 136,                    /* label  */
  YYSYMBOL_jump_statement = 137,           /* jump_statement  */
  YYSYMBOL_expression = 138,               /* expression  */
  YYSYMBOL_assignment_expression = 139,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 140,      /* assignment_operator  */
  YYSYMBOL_conditional_expression = 141,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 142,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 143,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 144,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 145,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 146,           /* and_expression  */
  YYSYMBOL_equality_expression = 147,      /* equality_expression  */
  YYSYMBOL_relational_expression = 148,    /* relational_expression  */
  YYSYMBOL_shift_expression = 149,         /* shift_expression  */
  YYSYMBOL_additive_expression = 150,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 151, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 152,          /* cast_expression  */
  YYSYMBOL_unary_expression = 153,         /* unary_expression  */
  YYSYMBOL_postfix_expression = 154,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 155,       /* primary_expression  */
  YYSYMBOL_argument_expression_list = 156, /* argument_expression_list  */
  YYSYMBOL_constant_expression_opt = 157,  /* constant_expression_opt  */
  YYSYMBOL_initializer = 158,              /* initializer  */
  YYSYMBOL_initializer_list = 159,         /* initializer_list  */
  YYSYMBOL_constant = 160                  /* constant  */
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  202
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  344

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   349


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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   217,   217,   218,   222,   223,   224,   225,   226,   231,
     231,   233,   233,   240,   241,   242,   243,   247,   248,   249,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     267,   268,   272,   273,   277,   278,   283,   284,   285,   299,
     300,   304,   305,   310,   311,   312,   313,   314,   318,   322,
     323,   327,   327,   329,   333,   334,   338,   339,   343,   344,
     345,   346,   346,   349,   353,   354,   358,   364,   363,   373,
     372,   382,   383,   387,   388,   389,   390,   395,   396,   397,
     398,   399,   400,   401,   405,   406,   410,   411,   415,   416,
     421,   422,   423,   427,   431,   432,   436,   437,   442,   443,
     444,   445,   449,   450,   455,   459,   460,   461,   462,   463,
     468,   469,   473,   474,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,   492,   493,   497,   498,   502,
     503,   507,   508,   512,   513,   517,   518,   522,   523,   524,
     528,   529,   530,   531,   532,   536,   537,   538,   542,   543,
     544,   548,   549,   550,   551,   555,   556,   560,   561,   562,
     563,   564,   565,   566,   567,   568,   569,   570,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,   587,   588,
     589,   590,   591,   592,   593,   594,   603,   604,   608,   609,
     618,   619,   620,   624,   625,   630,   631,   632,   633,   634,
     635,   636,   637
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
  "\"end of file\"", "error", "\"invalid token\"", "INCLUDE", "PLUS",
  "MINUS", "STAR", "DIVIDE", "MODULUS", "ASSIGN", "INCREMENT", "DECREMENT",
  "EQUAL", "NOT_EQUAL", "LESS_THAN", "GREATER_THAN", "LESS_EQUAL",
  "GREATER_EQUAL", "BITWISE_AND", "BITWISE_OR", "BITWISE_XOR",
  "LEFT_SHIFT", "RIGHT_SHIFT", "ARROW", "LOGICAL_NOT", "LOGICAL_AND",
  "LOGICAL_OR", "PLUS_EQUAL", "MINUS_EQUAL", "STAR_EQUAL", "DIV_EQUAL",
  "MOD_EQUAL", "AND_EQUAL", "OR_EQUAL", "XOR_EQUAL", "LEFT_SHIFT_EQ",
  "RIGHT_SHIFT_EQ", "LROUND", "RROUND", "LCURLY", "RCURLY", "LSQUARE",
  "RSQUARE", "SEMICOLON", "COLON", "COMMA", "DOT", "QUESTION_MARK",
  "TILDE", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT", "WHILE", "DO", "FOR",
  "GOTO", "CONTINUE", "BREAK", "RETURN", "UNTIL", "SIZEOF", "VOID", "INT",
  "DOUBLE", "CHAR", "BOOL", "STRING", "LONG", "TRUE", "FALSE", "NULLPTR",
  "AUTO", "STATIC", "CONST", "CLASS", "STRUCT", "PUBLIC", "PRIVATE",
  "PROTECTED", "DELETE", "NEW", "CIN", "COUT", "ENDL", "TYPE_NAME",
  "IDENTIFIER", "DECIMAL_LITERAL", "DOUBLE_LITERAL", "EXPONENT_LITERAL",
  "CHARACTER_LITERAL", "STRING_LITERAL", "FUNCTION", "INVALID_IDENTIFIER",
  "$accept", "translation_unit", "external_declaration", "declaration",
  "$@1", "$@2", "declaration_specifiers", "storage_class_specifier",
  "type_specifier", "init_declarator_list_no_func",
  "init_declarator_no_func", "declarator_no_func",
  "direct_declarator_no_func", "declarator", "pointer",
  "direct_declarator", "parameter_type_list", "parameter_list",
  "parameter_declaration", "$@3", "class_specifier",
  "member_specification", "member_declaration", "$@4",
  "member_declarator_list", "member_declarator", "function_definition",
  "$@5", "$@6", "function_declarator", "direct_function_declarator",
  "statement", "compound_statement", "block_item_list", "block_item",
  "selection_statement", "switch_body", "case_list", "case_label",
  "iteration_statement", "expression_opt", "label", "jump_statement",
  "expression", "assignment_expression", "assignment_operator",
  "conditional_expression", "logical_or_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "cast_expression", "unary_expression",
  "postfix_expression", "primary_expression", "argument_expression_list",
  "constant_expression_opt", "initializer", "initializer_list", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-292)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -292,   201,  -292,  -292,     4,     2,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,  -292,  -292,  -292,   -31,    -5,  -292,    51,
    -292,  -292,  -292,     2,   102,   102,     2,  -292,  -292,  -292,
      53,  -292,   120,    72,   125,   617,   129,     5,  -292,  -292,
    -292,  -292,  -292,  -292,   148,   961,  -292,  -292,  -292,  -292,
     -20,   151,   155,  -292,  -292,     5,  -292,    69,  -292,   193,
     165,   -30,   148,   275,  -292,  1010,  1010,  1010,  1010,  1010,
    1010,  1010,   548,  1010,  1059,  -292,  -292,  -292,  1010,   176,
     194,   202,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,    -4,   190,   203,   204,   207,   105,   179,   122,
      19,    63,  -292,    74,    40,  -292,   184,  -292,   515,  1092,
       8,  -292,   102,   189,  -292,     5,   730,   961,   165,  -292,
    -292,  -292,   191,   192,   195,   457,   197,   143,   188,   205,
     821,   200,   206,  -292,   208,  -292,  -292,   366,  -292,  -292,
    -292,  -292,  -292,   110,  -292,   961,  -292,  -292,  -292,  -292,
    -292,  -292,  -292,   209,    15,  -292,   548,  -292,  -292,  -292,
     159,   961,   961,   961,   961,   961,   961,   961,   961,   961,
     961,   961,   961,   961,   961,   961,   961,   961,   961,   961,
     961,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,  -292,
    -292,  -292,   961,  -292,  -292,   168,   912,   961,   169,  -292,
    -292,   213,   214,   219,   228,  -292,  -292,     8,  -292,  -292,
     -28,   119,  -292,  -292,  -292,   730,  -292,  -292,   230,   961,
     961,   961,   229,   961,   239,  -292,  -292,  -292,   118,   961,
    -292,  -292,  -292,  -292,   961,   961,  -292,   235,  -292,  -292,
     244,   190,  -292,   140,   203,   204,   207,   105,   179,   179,
     122,   122,   122,   122,    19,    19,    63,    63,  -292,  -292,
    -292,  -292,  -292,  -292,    34,    10,  -292,  -292,  -292,  -292,
    -292,     5,   246,   119,   707,   961,  -292,     9,  -292,    42,
      75,    77,   253,   248,   247,  -292,  -292,    78,  -292,  -292,
    -292,   961,   961,  -292,  -292,  -292,   137,  -292,  -292,  -292,
     257,   254,  -292,   639,   457,   258,   457,   961,   961,   457,
    -292,  -292,  -292,     5,  -292,  -292,  -292,  -292,   250,   138,
    -292,  -292,   114,   255,  -292,  -292,   457,   -24,   457,    45,
    -292,   259,   961,  -292,  -292,   457,  -292,  -292,  -292,  -292,
     263,  -292,   457,  -292
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     7,    41,     0,    20,    21,    23,    24,
      25,    26,    22,    17,    18,    19,    29,    28,    27,     0,
       8,     3,     5,     9,    14,    13,     0,     6,     4,    69,
      71,    42,     0,     0,     0,     0,     0,     0,    67,    29,
      28,    15,    16,    72,     0,   188,    75,    56,    56,    74,
      51,     0,    48,    49,    10,     0,    36,     0,    30,    32,
      35,     0,     0,     0,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   201,   202,   200,     0,     0,
       0,     0,   184,   178,   195,   199,   198,   196,   180,   185,
     189,   112,   125,   127,   129,   131,   133,   135,   137,   140,
     145,   148,   151,   155,   157,   168,     0,   179,     0,     0,
       0,    73,     0,     0,    12,     0,     0,   188,    34,    68,
      84,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   178,    88,    11,    89,    77,     0,    86,    78,
      79,    81,    80,     0,   110,     0,   160,   161,   162,   158,
     159,   163,   164,     0,     0,   165,     0,   166,   177,   176,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,     0,   174,   175,     0,     0,     0,     0,    76,
      54,     0,     0,     0,    61,    57,    55,     0,    43,    52,
       0,    40,    50,    37,    31,     0,   190,    33,     0,     0,
       0,     0,     0,   102,     0,   106,   107,   108,     0,     0,
     104,    85,    87,    82,     0,     0,   181,     0,   183,   186,
     182,   128,   155,     0,   130,   132,   134,   136,   138,   139,
     141,   142,   143,   144,   146,   147,   149,   150,   152,   153,
     154,   113,   173,   170,     0,     0,   172,    58,    59,    60,
      63,     0,     0,    39,     0,   188,   193,     0,    38,     0,
       0,     0,     0,     0,   103,   105,   109,     0,   111,   156,
     167,     0,     0,   171,   169,    66,     0,    64,    44,    46,
       0,     0,   191,     0,     0,     0,     0,     0,   102,     0,
     187,   126,    62,     0,    45,    47,   192,   194,    90,     0,
      92,    98,     0,     0,    99,    65,     0,     0,     0,     0,
      95,     0,   102,    91,   197,     0,    97,    93,    94,   100,
       0,    96,     0,   101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -292,  -292,  -292,   302,  -292,  -292,    37,  -292,   -66,  -292,
     196,   -54,   243,    98,    11,    96,    33,  -292,   198,  -292,
    -292,   260,  -292,  -292,  -292,     0,  -292,  -292,  -292,    73,
    -292,  -123,   -18,  -292,   172,  -292,  -292,  -292,   -13,  -292,
    -291,  -292,  -292,   -72,   -42,  -292,    25,  -292,   157,   156,
     160,   161,   154,    30,    38,    39,    44,  -159,   -38,  -292,
    -292,   126,  -113,  -210,  -292,     1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    21,   133,    36,    37,    50,    24,    25,    57,
      58,    59,    60,   209,    61,   211,    51,    52,    53,   110,
      27,   108,   205,   271,   296,   297,    28,    62,    44,    29,
      30,   135,   136,   137,   138,   139,   320,   329,   330,   140,
     283,   141,   142,   143,   144,   192,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   240,   106,   217,   277,   107
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     154,   113,   222,    90,   218,   276,   153,    55,     4,   207,
       4,     4,    26,   159,     4,    31,    26,   323,   -53,   258,
     259,   260,   162,   176,   177,   -53,    64,   146,   147,   148,
     149,   150,   151,   152,    26,   155,   157,    26,    23,     5,
     158,   340,    55,   163,   119,   207,    75,    76,    77,   302,
     193,   194,   294,   236,   303,   234,    33,    56,   228,   208,
     234,    41,    42,   195,    84,    85,    86,    87,   334,   178,
     179,   180,   293,   154,   216,    90,   289,   196,    32,   291,
     304,   197,    34,   181,   154,   337,   198,   234,    35,    19,
     237,   243,    56,   317,    45,   208,    38,   327,   328,    43,
     134,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,    47,   114,   305,   115,   306,   309,   168,   169,   239,
     234,   210,   234,   234,   242,   265,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   174,   175,   204,   204,   279,   280,   281,
     261,   284,   331,   233,   239,   234,   274,   287,    46,   234,
     275,   286,   301,   234,    48,     6,     7,     8,     9,    10,
      11,    12,    54,   216,   134,    13,    14,    15,    39,    40,
     312,   318,   313,   321,   292,   234,   324,    63,    18,   111,
     327,   328,   288,   170,   171,   172,   173,   242,   248,   249,
     112,     2,   116,   333,     3,   336,   117,     4,   250,   251,
     252,   253,   341,   254,   255,   164,   160,   295,   210,   343,
     256,   257,   165,   161,   166,   167,   199,   213,   219,   220,
     224,   225,   221,    90,   223,   322,   284,   229,     5,     6,
       7,     8,     9,    10,    11,    12,   238,   235,   226,   310,
     230,    -9,    39,    40,   242,   262,   266,   267,   268,   295,
     284,   216,    18,   269,     6,     7,     8,     9,    10,    11,
      12,   270,   278,   290,    13,    14,    15,    16,    17,    65,
      66,    67,   285,   282,   298,    68,    69,    18,    19,   291,
     307,   308,   234,    70,    20,   314,   315,   319,   332,    71,
     326,   342,   339,    22,   118,   272,   273,   300,   109,   232,
     212,   214,    72,   325,    63,   120,   338,   311,   121,   241,
     244,   247,   264,    73,   122,   245,   123,   246,   335,   124,
     125,   126,   127,   128,   129,   130,   131,    74,     6,     7,
       8,     9,    10,    11,    12,    75,    76,    77,    13,    14,
      15,    39,    40,     0,     0,     0,    78,    79,    80,    81,
      82,    18,   132,    84,    85,    86,    87,    88,     0,    89,
      65,    66,    67,     0,     0,     0,    68,    69,     0,     0,
       0,     0,     0,     0,    70,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    72,     0,    63,   231,     0,     0,   121,
       0,     0,     0,     0,    73,   122,     0,   123,     0,     0,
     124,   125,   126,   127,   128,   129,   130,   131,    74,     6,
       7,     8,     9,    10,    11,    12,    75,    76,    77,    13,
      14,    15,    39,    40,     0,     0,     0,    78,    79,    80,
      81,    82,    18,   132,    84,    85,    86,    87,    88,     0,
      89,    65,    66,    67,     0,     0,     0,    68,    69,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    72,     0,    63,     0,     0,     0,
     121,     0,     0,     0,     0,    73,   122,     0,   123,     0,
       0,   124,   125,   126,   127,   128,   129,   130,   131,    74,
       0,     0,     0,     0,     0,     0,     0,    75,    76,    77,
       0,     0,     0,     0,     0,     0,     0,     0,    78,    79,
      80,    81,    82,     0,   132,    84,    85,    86,    87,    88,
       0,    89,    65,    66,    67,   200,     0,     0,    68,    69,
       0,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,     6,     7,
       8,     9,    10,    11,    12,    72,     0,     0,    13,    14,
      15,    39,    40,   201,   202,   203,    73,     0,     0,     0,
       0,    18,     0,     0,     0,     0,     0,     0,     0,     0,
      74,     6,     7,     8,     9,    10,    11,    12,    75,    76,
      77,     0,     0,     0,    39,    40,     0,     0,     0,    78,
      79,    80,    81,    82,    18,    83,    84,    85,    86,    87,
      88,     0,    89,    65,    66,    67,     0,     0,     0,    68,
      69,     0,     0,     0,     0,    49,     0,    70,     0,     0,
       0,     0,     0,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    72,     0,   215,   316,
       6,     7,     8,     9,    10,    11,    12,    73,     0,     0,
      13,    14,    15,    39,    40,     0,     0,     0,     0,     0,
       0,    74,     0,    18,     0,     0,     0,     0,     0,    75,
      76,    77,     0,     0,     0,     0,     0,     0,     0,     0,
      78,    79,    80,    81,    82,     0,    83,    84,    85,    86,
      87,    88,     0,    89,    65,    66,    67,     0,     0,     0,
      68,    69,     0,     0,     0,   299,     0,     0,    70,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    72,     0,   215,
       6,     7,     8,     9,    10,    11,    12,     0,    73,     0,
      13,    14,    15,    39,    40,     0,     0,     0,     0,     0,
       0,     0,    74,    18,     0,     0,     0,     0,     0,     0,
      75,    76,    77,     0,     0,     0,     0,     0,     0,     0,
       0,    78,    79,    80,    81,    82,     0,    83,    84,    85,
      86,    87,    88,     0,    89,    65,    66,    67,     0,     0,
       0,    68,    69,     0,     0,     0,     0,     0,     0,    70,
       0,     0,     0,     0,     0,    71,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    72,     0,
       0,     0,     0,     0,   227,     0,     0,     0,     0,    73,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    74,     0,     0,     0,     0,     0,     0,
       0,    75,    76,    77,     0,     0,     0,     0,     0,     0,
       0,     0,    78,    79,    80,    81,    82,     0,    83,    84,
      85,    86,    87,    88,     0,    89,    65,    66,    67,     0,
       0,     0,    68,    69,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    72,
     263,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     0,     0,    65,    66,    67,     0,     0,
       0,    68,    69,     0,    74,     0,     0,     0,     0,    70,
       0,     0,    75,    76,    77,    71,     0,     0,     0,     0,
       0,     0,     0,    78,    79,    80,    81,    82,    72,    83,
      84,    85,    86,    87,    88,     0,    89,     0,     0,    73,
       0,     0,     0,     0,    65,    66,    67,     0,     0,     0,
      68,    69,     0,    74,     0,     0,     0,     0,    70,     0,
       0,    75,    76,    77,    71,     0,     0,     0,     0,     0,
       0,     0,    78,    79,    80,    81,    82,   145,    83,    84,
      85,    86,    87,    88,     0,    89,     0,     0,    73,     0,
       0,     0,     0,    65,    66,    67,     0,     0,     0,    68,
      69,     0,    74,     0,     0,     0,     0,    70,     0,     0,
      75,    76,    77,    71,     0,     0,     0,     0,     0,     0,
       0,    78,    79,    80,    81,    82,   156,    83,    84,    85,
      86,    87,    88,     0,    89,     0,     0,    73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    74,     0,     0,     0,     0,     0,     0,     0,    75,
      76,    77,   206,     0,     0,     0,     0,     0,     0,     0,
      78,    79,    80,    81,    82,     0,    83,    84,    85,    86,
      87,    88,     0,    89,     0,     6,     7,     8,     9,    10,
      11,    12,     0,     0,     0,    13,    14,    15,    39,    40,
     201,   202,   203,     0,     0,     0,     0,     0,    18
};

static const yytype_int16 yycheck[] =
{
      72,    55,   125,    45,   117,   215,    72,    37,     6,    37,
       6,     6,     1,    79,     6,     4,     5,   308,    38,   178,
     179,   180,    26,     4,     5,    45,    44,    65,    66,    67,
      68,    69,    70,    71,    23,    73,    74,    26,     1,    37,
      78,   332,    37,    47,    62,    37,    70,    71,    72,    40,
      10,    11,    42,    38,    45,    45,    87,    87,   130,    87,
      45,    24,    25,    23,    88,    89,    90,    91,    92,     6,
       7,     8,    38,   145,   116,   117,   235,    37,     5,    45,
      38,    41,    87,     9,   156,    40,    46,    45,    37,    87,
     156,   163,    87,   303,    41,    87,    23,    52,    53,    26,
      63,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    39,    43,    38,    45,    38,    38,    12,    13,   161,
      45,   110,    45,    45,   162,   197,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,    21,    22,   108,   109,   219,   220,   221,
     192,   223,    38,    43,   196,    45,    37,   229,    38,    45,
      41,    43,   275,    45,    39,    63,    64,    65,    66,    67,
      68,    69,    43,   215,   137,    73,    74,    75,    76,    77,
      43,   304,    45,   306,    44,    45,   309,    39,    86,    38,
      52,    53,   234,    14,    15,    16,    17,   235,   168,   169,
      45,     0,     9,   326,     3,   328,    41,     6,   170,   171,
     172,   173,   335,   174,   175,    25,    22,   271,   207,   342,
     176,   177,    19,    21,    20,    18,    42,    38,    37,    37,
      87,    43,    37,   275,    37,   307,   308,    37,    37,    63,
      64,    65,    66,    67,    68,    69,    87,    38,    43,   291,
      44,    43,    76,    77,   292,    87,    87,    44,    44,   313,
     332,   303,    86,    44,    63,    64,    65,    66,    67,    68,
      69,    43,    42,    38,    73,    74,    75,    76,    77,     4,
       5,     6,    43,    54,    38,    10,    11,    86,    87,    45,
      37,    43,    45,    18,    93,    38,    42,    39,    43,    24,
      50,    38,    43,     1,    61,   207,   210,   274,    48,   137,
     112,   115,    37,   313,    39,    40,   329,   292,    43,   162,
     164,   167,   196,    48,    49,   165,    51,   166,   327,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
       4,     5,     6,    -1,    -1,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    39,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    48,    49,    -1,    51,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      94,     4,     5,     6,    -1,    -1,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    88,    89,    90,    91,    92,
      -1,    94,     4,     5,     6,    40,    -1,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    37,    -1,    -1,    73,    74,
      75,    76,    77,    78,    79,    80,    48,    -1,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    -1,    -1,    -1,    76,    77,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    -1,    94,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    -1,    -1,    -1,    -1,    38,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    39,    40,
      63,    64,    65,    66,    67,    68,    69,    48,    -1,    -1,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    86,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    -1,    87,    88,    89,    90,
      91,    92,    -1,    94,     4,     5,     6,    -1,    -1,    -1,
      10,    11,    -1,    -1,    -1,    38,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    39,
      63,    64,    65,    66,    67,    68,    69,    -1,    48,    -1,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    86,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    -1,    87,    88,    89,
      90,    91,    92,    -1,    94,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    -1,    87,    88,
      89,    90,    91,    92,    -1,    94,     4,     5,     6,    -1,
      -1,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    -1,    62,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    70,    71,    72,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    37,    87,
      88,    89,    90,    91,    92,    -1,    94,    -1,    -1,    48,
      -1,    -1,    -1,    -1,     4,     5,     6,    -1,    -1,    -1,
      10,    11,    -1,    62,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    70,    71,    72,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    37,    87,    88,
      89,    90,    91,    92,    -1,    94,    -1,    -1,    48,    -1,
      -1,    -1,    -1,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    -1,    62,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      70,    71,    72,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    37,    87,    88,    89,
      90,    91,    92,    -1,    94,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    -1,    87,    88,    89,    90,
      91,    92,    -1,    94,    -1,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    73,    74,    75,    76,    77,
      78,    79,    80,    -1,    -1,    -1,    -1,    -1,    86
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    96,     0,     3,     6,    37,    63,    64,    65,    66,
      67,    68,    69,    73,    74,    75,    76,    77,    86,    87,
      93,    97,    98,   101,   102,   103,   109,   115,   121,   124,
     125,   109,   124,    87,    87,    37,    99,   100,   124,    76,
      77,   101,   101,   124,   123,    41,    38,    39,    39,    38,
     101,   111,   112,   113,    43,    37,    87,   104,   105,   106,
     107,   109,   122,    39,   127,     4,     5,     6,    10,    11,
      18,    24,    37,    48,    62,    70,    71,    72,    81,    82,
      83,    84,    85,    87,    88,    89,    90,    91,    92,    94,
     139,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   157,   160,   116,   116,
     114,    38,    45,   106,    43,    45,     9,    41,   107,   127,
      40,    43,    49,    51,    54,    55,    56,    57,    58,    59,
      60,    61,    87,    98,   101,   126,   127,   128,   129,   130,
     134,   136,   137,   138,   139,    37,   153,   153,   153,   153,
     153,   153,   153,   103,   138,   153,    37,   153,   153,   103,
      22,    21,    26,    47,    25,    19,    20,    18,    12,    13,
      14,    15,    16,    17,    21,    22,     4,     5,     6,     7,
       8,     9,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,   140,    10,    11,    23,    37,    41,    46,    42,
      40,    78,    79,    80,   101,   117,    40,    37,    87,   108,
     109,   110,   113,    38,   105,    39,   139,   158,   157,    37,
      37,    37,   126,    37,    87,    43,    43,    43,   138,    37,
      44,    40,   129,    43,    45,    38,    38,   103,    87,   139,
     156,   143,   153,   138,   144,   145,   146,   147,   148,   148,
     149,   149,   149,   149,   150,   150,   151,   151,   152,   152,
     152,   139,    87,    38,   156,   138,    87,    44,    44,    44,
      43,   118,   108,   110,    37,    41,   158,   159,    42,   138,
     138,   138,    54,   135,   138,    43,    43,   138,   139,   152,
      38,    45,    44,    38,    42,   106,   119,   120,    38,    38,
     111,   157,    40,    45,    38,    38,    38,    37,    43,    38,
     139,   141,    43,    45,    38,    42,    40,   158,   126,    39,
     131,   126,   138,   135,   126,   120,    50,    52,    53,   132,
     133,    38,    43,   126,    92,   160,   126,    40,   133,    43,
     135,   126,    38,   126
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    97,    97,    97,    97,    97,    99,
      98,   100,    98,   101,   101,   101,   101,   102,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   107,   108,
     108,   109,   109,   110,   110,   110,   110,   110,   111,   112,
     112,   114,   113,   113,   115,   115,   116,   116,   117,   117,
     117,   118,   117,   117,   119,   119,   120,   122,   121,   123,
     121,   124,   124,   125,   125,   125,   125,   126,   126,   126,
     126,   126,   126,   126,   127,   127,   128,   128,   129,   129,
     130,   130,   130,   131,   132,   132,   133,   133,   134,   134,
     134,   134,   135,   135,   136,   137,   137,   137,   137,   137,
     138,   138,   139,   139,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   141,   141,   142,   142,   143,
     143,   144,   144,   145,   145,   146,   146,   147,   147,   147,
     148,   148,   148,   148,   148,   149,   149,   149,   150,   150,
     150,   151,   151,   151,   151,   152,   152,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   155,   155,
     155,   155,   155,   155,   155,   155,   156,   156,   157,   157,
     158,   158,   158,   159,   159,   160,   160,   160,   160,   160,
     160,   160,   160
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     0,
       3,     0,     4,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     2,     1,     1,     3,     4,     2,
       1,     1,     2,     1,     3,     4,     3,     4,     1,     1,
       3,     0,     3,     1,     5,     5,     0,     2,     2,     2,
       2,     0,     4,     2,     1,     3,     1,     0,     4,     0,
       3,     1,     2,     4,     3,     3,     4,     1,     1,     1,
       1,     1,     2,     1,     2,     3,     1,     2,     1,     1,
       5,     7,     5,     3,     2,     1,     3,     2,     5,     5,
       7,     9,     0,     1,     2,     3,     2,     2,     2,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     4,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     4,     1,     4,
       3,     4,     3,     3,     2,     2,     2,     2,     1,     1,
       1,     3,     3,     3,     1,     1,     1,     3,     0,     1,
       1,     3,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1
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
  case 9: /* $@1: %empty  */
#line 231 "parser.y"
                             { curr_decl_spec = (yyvsp[0].str); pending_role = "IDENTIFIER"; pending_ids.clear(); }
#line 1813 "parser.tab.c"
    break;

  case 11: /* $@2: %empty  */
#line 233 "parser.y"
                             { curr_decl_spec = (yyvsp[0].str); pending_role = "IDENTIFIER"; pending_ids.clear(); }
#line 1819 "parser.tab.c"
    break;

  case 12: /* declaration: declaration_specifiers $@2 init_declarator_list_no_func SEMICOLON  */
#line 235 "parser.y"
      { flush_pending(curr_decl_spec, pending_role); }
#line 1825 "parser.tab.c"
    break;

  case 13: /* declaration_specifiers: type_specifier  */
#line 240 "parser.y"
                                                    { (yyval.str) = (yyvsp[0].str); }
#line 1831 "parser.tab.c"
    break;

  case 14: /* declaration_specifiers: storage_class_specifier  */
#line 241 "parser.y"
                                                    { (yyval.str) = (yyvsp[0].str); }
#line 1837 "parser.tab.c"
    break;

  case 15: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 242 "parser.y"
                                                     { (yyval.str) = cat2((yyvsp[-1].str), (yyvsp[0].str)); }
#line 1843 "parser.tab.c"
    break;

  case 16: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 243 "parser.y"
                                                     { (yyval.str) = cat2((yyvsp[-1].str), (yyvsp[0].str)); }
#line 1849 "parser.tab.c"
    break;

  case 17: /* storage_class_specifier: AUTO  */
#line 247 "parser.y"
               { (yyval.str) = sdup("AUTO"); }
#line 1855 "parser.tab.c"
    break;

  case 18: /* storage_class_specifier: STATIC  */
#line 248 "parser.y"
               { (yyval.str) = sdup("STATIC"); }
#line 1861 "parser.tab.c"
    break;

  case 19: /* storage_class_specifier: CONST  */
#line 249 "parser.y"
               { (yyval.str) = sdup("CONST"); }
#line 1867 "parser.tab.c"
    break;

  case 20: /* type_specifier: VOID  */
#line 253 "parser.y"
               { (yyval.str) = sdup("VOID"); }
#line 1873 "parser.tab.c"
    break;

  case 21: /* type_specifier: INT  */
#line 254 "parser.y"
               { (yyval.str) = sdup("INT"); }
#line 1879 "parser.tab.c"
    break;

  case 22: /* type_specifier: LONG  */
#line 255 "parser.y"
               { (yyval.str) = sdup("LONG"); }
#line 1885 "parser.tab.c"
    break;

  case 23: /* type_specifier: DOUBLE  */
#line 256 "parser.y"
               { (yyval.str) = sdup("DOUBLE"); }
#line 1891 "parser.tab.c"
    break;

  case 24: /* type_specifier: CHAR  */
#line 257 "parser.y"
               { (yyval.str) = sdup("CHAR"); }
#line 1897 "parser.tab.c"
    break;

  case 25: /* type_specifier: BOOL  */
#line 258 "parser.y"
               { (yyval.str) = sdup("BOOL"); }
#line 1903 "parser.tab.c"
    break;

  case 26: /* type_specifier: STRING  */
#line 259 "parser.y"
               { (yyval.str) = sdup("STRING"); }
#line 1909 "parser.tab.c"
    break;

  case 27: /* type_specifier: TYPE_NAME  */
#line 260 "parser.y"
               { (yyval.str) = sdup((yyvsp[0].str)); }
#line 1915 "parser.tab.c"
    break;

  case 28: /* type_specifier: STRUCT  */
#line 261 "parser.y"
               { (yyval.str) = sdup("STRUCT"); }
#line 1921 "parser.tab.c"
    break;

  case 29: /* type_specifier: CLASS  */
#line 262 "parser.y"
               { (yyval.str) = sdup("CLASS"); }
#line 1927 "parser.tab.c"
    break;

  case 32: /* init_declarator_no_func: declarator_no_func  */
#line 272 "parser.y"
                                               { push_id((yyvsp[0].str)); }
#line 1933 "parser.tab.c"
    break;

  case 33: /* init_declarator_no_func: declarator_no_func ASSIGN initializer  */
#line 273 "parser.y"
                                               { push_id((yyvsp[-2].str)); }
#line 1939 "parser.tab.c"
    break;

  case 34: /* declarator_no_func: pointer direct_declarator_no_func  */
#line 277 "parser.y"
                                           { last_declarator_pointer = (yyvsp[-1].str); curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[0].str); }
#line 1945 "parser.tab.c"
    break;

  case 35: /* declarator_no_func: direct_declarator_no_func  */
#line 278 "parser.y"
                                           { last_declarator_pointer = NULL; curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[0].str); }
#line 1951 "parser.tab.c"
    break;

  case 39: /* declarator: pointer direct_declarator  */
#line 299 "parser.y"
                                           { last_declarator_pointer = (yyvsp[-1].str); curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[0].str); }
#line 1957 "parser.tab.c"
    break;

  case 40: /* declarator: direct_declarator  */
#line 300 "parser.y"
                                           { last_declarator_pointer = NULL; curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[0].str); }
#line 1963 "parser.tab.c"
    break;

  case 41: /* pointer: STAR  */
#line 304 "parser.y"
                                     { (yyval.str) = sdup("pointer"); }
#line 1969 "parser.tab.c"
    break;

  case 42: /* pointer: STAR pointer  */
#line 305 "parser.y"
                                     { (yyval.str) = cat2((yyvsp[0].str), "pointer"); }
#line 1975 "parser.tab.c"
    break;

  case 43: /* direct_declarator: IDENTIFIER  */
#line 310 "parser.y"
                                                           { (yyval.str) = (yyvsp[0].str); }
#line 1981 "parser.tab.c"
    break;

  case 44: /* direct_declarator: LROUND declarator RROUND  */
#line 311 "parser.y"
                                                           { (yyval.str) = (yyvsp[-1].str); }
#line 1987 "parser.tab.c"
    break;

  case 45: /* direct_declarator: direct_declarator LROUND parameter_type_list RROUND  */
#line 312 "parser.y"
                                                           { (yyval.str) = (yyvsp[-3].str); }
#line 1993 "parser.tab.c"
    break;

  case 46: /* direct_declarator: direct_declarator LROUND RROUND  */
#line 313 "parser.y"
                                                           { (yyval.str) = (yyvsp[-2].str); }
#line 1999 "parser.tab.c"
    break;

  case 47: /* direct_declarator: direct_declarator LSQUARE constant_expression_opt RSQUARE  */
#line 314 "parser.y"
                                                                { (yyval.str) = (yyvsp[-3].str); }
#line 2005 "parser.tab.c"
    break;

  case 51: /* $@3: %empty  */
#line 327 "parser.y"
                             { curr_param_spec = (yyvsp[0].str); }
#line 2011 "parser.tab.c"
    break;

  case 52: /* parameter_declaration: declaration_specifiers $@3 declarator  */
#line 328 "parser.y"
        { insert_symbol_table((yyvsp[0].str), curr_param_spec ? curr_param_spec : "", "PARAM"); }
#line 2017 "parser.tab.c"
    break;

  case 54: /* class_specifier: CLASS IDENTIFIER LCURLY member_specification RCURLY  */
#line 333 "parser.y"
                                                           { insert_symbol_table((yyvsp[-3].str), sdup("CLASS"), "TYPE"); }
#line 2023 "parser.tab.c"
    break;

  case 55: /* class_specifier: STRUCT IDENTIFIER LCURLY member_specification RCURLY  */
#line 334 "parser.y"
                                                           { insert_symbol_table((yyvsp[-3].str), sdup("STRUCT"), "TYPE"); }
#line 2029 "parser.tab.c"
    break;

  case 61: /* $@4: %empty  */
#line 346 "parser.y"
                             { curr_decl_spec = (yyvsp[0].str); pending_role = "MEMBER"; pending_ids.clear(); }
#line 2035 "parser.tab.c"
    break;

  case 62: /* member_declaration: declaration_specifiers $@4 member_declarator_list SEMICOLON  */
#line 348 "parser.y"
      { flush_pending(curr_decl_spec, pending_role); }
#line 2041 "parser.tab.c"
    break;

  case 66: /* member_declarator: declarator_no_func  */
#line 358 "parser.y"
                                            { push_id((yyvsp[0].str)); }
#line 2047 "parser.tab.c"
    break;

  case 67: /* $@5: %empty  */
#line 364 "parser.y"
        { /* remember return-spec and record function-name lineno here */
          curr_func_spec = (yyvsp[-1].str);
          curr_decl_lineno = last_ident_lineno;
        }
#line 2056 "parser.tab.c"
    break;

  case 68: /* function_definition: declaration_specifiers function_declarator $@5 compound_statement  */
#line 369 "parser.y"
        { insert_symbol_table((yyvsp[-2].str), curr_func_spec ? curr_func_spec : "", "FUNCTION");
          curr_func_spec = NULL;
        }
#line 2064 "parser.tab.c"
    break;

  case 69: /* $@6: %empty  */
#line 373 "parser.y"
        { /* no explicit return-specifiers; record function-name lineno */
          curr_decl_lineno = last_ident_lineno;
        }
#line 2072 "parser.tab.c"
    break;

  case 70: /* function_definition: function_declarator $@6 compound_statement  */
#line 377 "parser.y"
        { insert_symbol_table((yyvsp[-2].str), "INT", "FUNCTION"); }
#line 2078 "parser.tab.c"
    break;

  case 71: /* function_declarator: direct_function_declarator  */
#line 382 "parser.y"
                                                       { (yyval.str) = (yyvsp[0].str); }
#line 2084 "parser.tab.c"
    break;

  case 72: /* function_declarator: pointer function_declarator  */
#line 383 "parser.y"
                                                       { (yyval.str) = (yyvsp[0].str); }
#line 2090 "parser.tab.c"
    break;

  case 73: /* direct_function_declarator: IDENTIFIER LROUND parameter_type_list RROUND  */
#line 387 "parser.y"
                                                       { curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[-3].str); }
#line 2096 "parser.tab.c"
    break;

  case 74: /* direct_function_declarator: IDENTIFIER LROUND RROUND  */
#line 388 "parser.y"
                                                       { curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[-2].str); }
#line 2102 "parser.tab.c"
    break;

  case 75: /* direct_function_declarator: LROUND function_declarator RROUND  */
#line 389 "parser.y"
                                                       { (yyval.str) = (yyvsp[-1].str); }
#line 2108 "parser.tab.c"
    break;

  case 76: /* direct_function_declarator: direct_function_declarator LSQUARE constant_expression_opt RSQUARE  */
#line 390 "parser.y"
                                                                         { (yyval.str) = (yyvsp[-3].str); }
#line 2114 "parser.tab.c"
    break;

  case 104: /* label: IDENTIFIER COLON  */
#line 455 "parser.y"
                       { insert_symbol_table((yyvsp[-1].str), sdup("LABEL"), "IDENTIFIER");   }
#line 2120 "parser.tab.c"
    break;

  case 180: /* primary_expression: STRING_LITERAL  */
#line 589 "parser.y"
                                          { insert_const_symbol_table('S',(yyvsp[0].str)); }
#line 2126 "parser.tab.c"
    break;

  case 195: /* constant: DECIMAL_LITERAL  */
#line 630 "parser.y"
                            { insert_const_symbol_table('I',(yyvsp[0].str)); }
#line 2132 "parser.tab.c"
    break;

  case 196: /* constant: CHARACTER_LITERAL  */
#line 631 "parser.y"
                            { insert_const_symbol_table('C',(yyvsp[0].str)); }
#line 2138 "parser.tab.c"
    break;

  case 197: /* constant: STRING_LITERAL  */
#line 632 "parser.y"
                            { insert_const_symbol_table('S',(yyvsp[0].str)); }
#line 2144 "parser.tab.c"
    break;

  case 198: /* constant: EXPONENT_LITERAL  */
#line 633 "parser.y"
                            { insert_const_symbol_table('E',(yyvsp[0].str)); }
#line 2150 "parser.tab.c"
    break;

  case 199: /* constant: DOUBLE_LITERAL  */
#line 634 "parser.y"
                            { insert_const_symbol_table('D',(yyvsp[0].str)); }
#line 2156 "parser.tab.c"
    break;

  case 200: /* constant: NULLPTR  */
#line 635 "parser.y"
                            { insert_const_symbol_table('N',(yyvsp[0].str)); }
#line 2162 "parser.tab.c"
    break;

  case 201: /* constant: TRUE  */
#line 636 "parser.y"
                            { insert_const_symbol_table('B',(yyvsp[0].str)); }
#line 2168 "parser.tab.c"
    break;

  case 202: /* constant: FALSE  */
#line 637 "parser.y"
                            { insert_const_symbol_table('B',(yyvsp[0].str)); }
#line 2174 "parser.tab.c"
    break;


#line 2178 "parser.tab.c"

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

#line 640 "parser.y"


int main() {
    yyparse();
    print_symbol_table();
    cout << endl;
    print_constant_table();
    return 0;
}
