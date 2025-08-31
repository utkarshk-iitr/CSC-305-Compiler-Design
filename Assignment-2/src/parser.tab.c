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
#line 1 "src/parser.y"

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

    vector<string> err;

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

    void print_error(){
        cout << "\nERRORS\n";
        for(auto& x:err){
            cout<<x<<endl;
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
        string a = "Error: ";
        string b = s;
        err.push_back(a+b+" at line "+to_string(yylineno)+" near '" + yytext + "'");
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

#line 240 "src/parser.tab.c"

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
  YYSYMBOL_116_4 = 116,                    /* $@4  */
  YYSYMBOL_117_5 = 117,                    /* $@5  */
  YYSYMBOL_member_specification = 118,     /* member_specification  */
  YYSYMBOL_member_declaration = 119,       /* member_declaration  */
  YYSYMBOL_120_6 = 120,                    /* $@6  */
  YYSYMBOL_member_declarator_list = 121,   /* member_declarator_list  */
  YYSYMBOL_member_declarator = 122,        /* member_declarator  */
  YYSYMBOL_function_definition = 123,      /* function_definition  */
  YYSYMBOL_124_7 = 124,                    /* $@7  */
  YYSYMBOL_125_8 = 125,                    /* $@8  */
  YYSYMBOL_function_declarator = 126,      /* function_declarator  */
  YYSYMBOL_direct_function_declarator = 127, /* direct_function_declarator  */
  YYSYMBOL_statement = 128,                /* statement  */
  YYSYMBOL_compound_statement = 129,       /* compound_statement  */
  YYSYMBOL_block_item_list = 130,          /* block_item_list  */
  YYSYMBOL_block_item = 131,               /* block_item  */
  YYSYMBOL_selection_statement = 132,      /* selection_statement  */
  YYSYMBOL_switch_body = 133,              /* switch_body  */
  YYSYMBOL_case_list = 134,                /* case_list  */
  YYSYMBOL_case_label = 135,               /* case_label  */
  YYSYMBOL_iteration_statement = 136,      /* iteration_statement  */
  YYSYMBOL_for_init = 137,                 /* for_init  */
  YYSYMBOL_for_declaration = 138,          /* for_declaration  */
  YYSYMBOL_139_9 = 139,                    /* $@9  */
  YYSYMBOL_expression_opt = 140,           /* expression_opt  */
  YYSYMBOL_label = 141,                    /* label  */
  YYSYMBOL_jump_statement = 142,           /* jump_statement  */
  YYSYMBOL_expression = 143,               /* expression  */
  YYSYMBOL_assignment_expression = 144,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 145,      /* assignment_operator  */
  YYSYMBOL_conditional_expression = 146,   /* conditional_expression  */
  YYSYMBOL_logical_or_expression = 147,    /* logical_or_expression  */
  YYSYMBOL_logical_and_expression = 148,   /* logical_and_expression  */
  YYSYMBOL_inclusive_or_expression = 149,  /* inclusive_or_expression  */
  YYSYMBOL_exclusive_or_expression = 150,  /* exclusive_or_expression  */
  YYSYMBOL_and_expression = 151,           /* and_expression  */
  YYSYMBOL_equality_expression = 152,      /* equality_expression  */
  YYSYMBOL_relational_expression = 153,    /* relational_expression  */
  YYSYMBOL_shift_expression = 154,         /* shift_expression  */
  YYSYMBOL_additive_expression = 155,      /* additive_expression  */
  YYSYMBOL_multiplicative_expression = 156, /* multiplicative_expression  */
  YYSYMBOL_cast_expression = 157,          /* cast_expression  */
  YYSYMBOL_unary_expression = 158,         /* unary_expression  */
  YYSYMBOL_postfix_expression = 159,       /* postfix_expression  */
  YYSYMBOL_primary_expression = 160,       /* primary_expression  */
  YYSYMBOL_lambda_expression = 161,        /* lambda_expression  */
  YYSYMBOL_lambda_introducer = 162,        /* lambda_introducer  */
  YYSYMBOL_lambda_capture_list = 163,      /* lambda_capture_list  */
  YYSYMBOL_lambda_capture = 164,           /* lambda_capture  */
  YYSYMBOL_lambda_specifier = 165,         /* lambda_specifier  */
  YYSYMBOL_lambda_declarator = 166,        /* lambda_declarator  */
  YYSYMBOL_lambda_body = 167,              /* lambda_body  */
  YYSYMBOL_argument_expression_list = 168, /* argument_expression_list  */
  YYSYMBOL_constant_expression_opt = 169,  /* constant_expression_opt  */
  YYSYMBOL_initializer = 170,              /* initializer  */
  YYSYMBOL_initializer_list = 171,         /* initializer_list  */
  YYSYMBOL_constant = 172                  /* constant  */
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
#define YYLAST   1918

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  78
/* YYNRULES -- Number of rules.  */
#define YYNRULES  234
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  394

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
       0,   228,   228,   229,   233,   234,   235,   236,   237,   238,
     243,   243,   244,   244,   247,   252,   253,   254,   258,   259,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     276,   277,   281,   282,   286,   287,   291,   292,   293,   294,
     308,   309,   313,   314,   319,   320,   321,   322,   323,   327,
     331,   332,   336,   336,   338,   342,   342,   343,   343,   347,
     348,   352,   353,   354,   355,   355,   358,   359,   364,   365,
     369,   373,   373,   381,   381,   386,   392,   393,   397,   398,
     399,   400,   404,   405,   406,   407,   408,   409,   410,   411,
     416,   417,   421,   422,   423,   428,   429,   433,   434,   435,
     439,   443,   444,   448,   449,   453,   454,   455,   456,   460,
     461,   465,   465,   468,   474,   475,   479,   483,   484,   485,
     486,   487,   491,   492,   493,   497,   498,   499,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   517,
     518,   522,   523,   527,   528,   532,   533,   537,   538,   542,
     543,   547,   548,   549,   553,   554,   555,   556,   557,   561,
     562,   563,   567,   568,   569,   573,   574,   575,   576,   580,
     581,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   599,   600,   601,   602,   603,   604,   605,   606,
     607,   608,   612,   613,   614,   615,   616,   617,   618,   619,
     620,   624,   625,   630,   631,   635,   636,   640,   641,   642,
     647,   648,   649,   654,   655,   656,   657,   662,   671,   672,
     676,   677,   686,   687,   688,   692,   693,   697,   698,   699,
     700,   701,   702,   703,   704
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
  "parameter_declaration", "$@3", "class_specifier", "$@4", "$@5",
  "member_specification", "member_declaration", "$@6",
  "member_declarator_list", "member_declarator", "function_definition",
  "$@7", "$@8", "function_declarator", "direct_function_declarator",
  "statement", "compound_statement", "block_item_list", "block_item",
  "selection_statement", "switch_body", "case_list", "case_label",
  "iteration_statement", "for_init", "for_declaration", "$@9",
  "expression_opt", "label", "jump_statement", "expression",
  "assignment_expression", "assignment_operator", "conditional_expression",
  "logical_or_expression", "logical_and_expression",
  "inclusive_or_expression", "exclusive_or_expression", "and_expression",
  "equality_expression", "relational_expression", "shift_expression",
  "additive_expression", "multiplicative_expression", "cast_expression",
  "unary_expression", "postfix_expression", "primary_expression",
  "lambda_expression", "lambda_introducer", "lambda_capture_list",
  "lambda_capture", "lambda_specifier", "lambda_declarator", "lambda_body",
  "argument_expression_list", "constant_expression_opt", "initializer",
  "initializer_list", "constant", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-330)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-221)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -330,  1543,  -330,    15,  -330,    21,     3,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  -330,   -66,   -34,  -330,
      24,  -330,  -330,  -330,     3,   164,  -330,     3,  -330,  -330,
    -330,    42,  -330,  -330,  -330,    47,    62,    75,   765,   118,
       6,  -330,  -330,  -330,  -330,  -330,   125,   867,  -330,  -330,
    -330,  -330,    53,    82,   129,  -330,  -330,     6,  -330,    88,
    -330,   171,   146,   -22,   125,   315,  -330,   154,  1617,  1617,
    1617,  1617,  1617,  1617,  1617,   683,    -1,  1617,  1708,  -330,
    -330,  -330,  1617,   201,   186,   194,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,    30,   209,   200,   222,
     228,   205,   156,   134,   217,   176,  -330,    40,    13,  -330,
    -330,   206,   207,  -330,  -330,  -330,     8,  -330,   164,   215,
    -330,     6,   959,   867,   146,  -330,   218,  -330,  -330,   223,
     225,   234,   591,   236,   188,   233,   237,  1051,   244,   239,
    -330,   242,  -330,  -330,   407,  -330,  -330,  -330,  -330,  -330,
     143,  -330,  -330,  1419,  -330,  -330,  -330,  -330,  -330,  -330,
    -330,   243,   250,    77,   202,  -330,  -330,    57,  -330,  -330,
     683,  -330,  -330,  -330,   203,  1511,  1799,  1419,  1799,  1799,
    1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
    1799,  1799,  1799,  1799,  1799,  -330,  -330,  -330,  -330,  -330,
    -330,  -330,  -330,  -330,  -330,  -330,  1511,  -330,  -330,   204,
    1143,  1419,   208,  -330,    25,  -330,   126,  1832,     8,  -330,
    -330,   -21,   -15,  -330,   255,  -330,   959,  -330,  -330,   251,
     249,  1419,  1419,  1419,   253,   245,   499,   254,  -330,  -330,
    -330,   153,  1419,  -330,   257,  -330,  -330,  -330,  1511,  -330,
    1799,  -330,  -330,  -330,    -7,   264,  -330,  -330,   258,   209,
    -330,   179,   200,   222,   228,   205,   156,   156,   134,   134,
     134,   134,   217,   217,   176,   176,  -330,  -330,  -330,  -330,
    -330,  -330,    79,    87,  -330,   857,  -330,   125,  -330,   261,
    -330,   263,   265,   266,   262,  -330,  -330,   270,   -15,   949,
     867,   164,  -330,   -27,  -330,    80,    81,    85,   249,   274,
     269,   271,  -330,  -330,   268,  -330,  -330,    90,   249,  -330,
    -330,  -330,  -330,  1511,  1799,  -330,  -330,   292,   279,  -330,
    -330,  -330,  -330,  -330,  -330,     8,  -330,  -330,   280,   281,
     284,  -330,   775,   591,   285,   591,  1419,     6,  1235,   591,
    -330,  -330,   201,   304,  -330,   166,  -330,  -330,  -330,  -330,
    -330,  -330,   278,   173,  -330,  -330,   122,   286,   289,  -330,
    -330,   201,  -330,     8,   591,    17,   591,    60,  -330,   291,
    1327,  -330,  -330,  -330,  -330,   591,  -330,  -330,  -330,  -330,
     297,  -330,   591,  -330
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     7,    42,     0,    20,    21,    23,
      24,    25,    26,    22,    16,    18,    19,    29,    28,    27,
       0,     8,     3,     5,    10,     0,    15,     0,     6,     4,
      73,    76,    75,     9,    43,     0,     0,     0,     0,     0,
       0,    71,    29,    28,    17,    77,     0,     0,    80,    55,
      57,    79,    52,     0,    49,    50,    11,     0,    36,     0,
      30,    32,    35,     0,     0,     0,    74,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   233,
     234,   232,     0,     0,     0,     0,   198,   192,   227,   231,
     230,   228,   194,   200,   221,   125,   139,   141,   143,   145,
     147,   149,   151,   154,   159,   162,   165,   169,   171,   182,
     199,   210,     0,   193,    59,    59,     0,    78,     0,     0,
      13,     0,     0,     0,    34,    72,     0,    90,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   192,
      95,    12,    96,    82,     0,    92,    83,    84,    86,    85,
       0,   122,   127,     0,   174,   175,   176,   172,   173,   177,
     178,     0,     0,     0,   209,   203,   207,     0,   205,   179,
       0,   180,   191,   190,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,     0,   188,   189,     0,
       0,     0,     0,   211,     0,    81,     0,     0,     0,    44,
      53,     0,    41,    51,    37,    31,     0,   222,    33,     0,
      14,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     120,     0,     0,   116,     0,    91,    93,    87,     0,   124,
       0,   195,   208,   204,     0,     0,   197,   218,   196,   142,
     169,     0,   144,   146,   148,   150,   152,   153,   155,   156,
     157,   158,   160,   161,   163,   164,   166,   167,   168,   126,
     187,   184,     0,     0,   186,     0,   217,     0,   202,     0,
      56,     0,     0,     0,    64,    60,    58,     0,    40,     0,
       0,     0,   225,     0,    39,     0,     0,     0,    89,     0,
     111,     0,   110,   109,   115,   117,   121,     0,    14,   123,
     170,   206,   181,     0,     0,   185,   183,   214,     0,   201,
      67,    61,    62,    63,    66,     0,    45,    47,     0,     0,
       0,   223,     0,     0,     0,     0,     0,     0,     0,     0,
     219,   140,     0,   213,    70,     0,    68,    46,    48,    38,
     224,   226,    97,     0,    99,   105,     0,   112,     0,   106,
     216,     0,    65,     0,     0,     0,     0,     0,   102,     0,
       0,   215,    69,    98,   229,     0,   104,   100,   101,   107,
       0,   103,     0,   108
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -330,  -330,  -330,   328,  -330,  -330,    19,  -330,   -73,   -11,
     216,   283,   275,  -108,    -5,   120,  -207,  -330,   226,  -330,
    -330,  -330,  -330,   230,  -330,  -330,  -330,   -30,  -330,  -330,
    -330,    33,  -330,  -129,   -39,  -330,   213,  -330,  -330,  -330,
     -31,  -330,  -330,  -330,  -330,  -329,  -330,  -330,   -74,   -41,
    -330,    23,  -330,   172,   175,   170,   180,   169,    61,    -8,
      63,    67,  -146,   -40,  -330,  -330,  -330,  -330,  -330,    97,
    -330,  -330,    72,   151,  -119,  -221,  -330,   -13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    22,   140,    39,    40,    52,    25,    26,    59,
      60,    61,    62,   354,    27,   222,    53,    54,    55,   116,
      28,   114,   115,   216,   295,   335,   355,   356,    29,    64,
      46,    30,    31,   142,   143,   144,   145,   146,   364,   377,
     378,   147,   311,   312,   347,   313,   148,   149,   150,   151,
     206,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   167,   168,
     214,   287,   288,   258,   112,   228,   303,   113
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,   163,   162,   235,   229,   302,    94,    66,   220,     5,
     173,   164,     5,   341,     5,    57,   218,   164,   342,   368,
      24,    36,   299,   207,   208,   125,   300,     5,   154,   155,
     156,   157,   158,   159,   160,    63,   209,   169,   171,    35,
       6,   165,   172,    57,    44,   218,   276,   277,   278,   195,
     210,   390,    63,    37,   211,    32,   176,    41,    33,   212,
      45,    38,   285,   241,    65,    58,   219,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   177,   328,   163,
     166,   227,    94,    47,   141,    48,   166,    79,    80,    81,
      20,   -54,   338,    58,   340,   219,   163,   255,   -54,   253,
     387,    49,   254,   261,   320,    88,    89,    90,    91,   384,
     297,   221,   375,   376,    50,   251,    63,   325,   343,   344,
     117,   361,   248,   345,   323,   248,   248,   289,   349,   326,
     248,   120,   248,   121,   257,   248,   260,   283,   260,   260,
     260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   260,   188,   189,   305,   306,   307,
     379,    56,   314,   141,    65,   279,   290,   248,   317,   257,
     184,   185,   186,   187,   118,   286,   268,   269,   270,   271,
     122,   339,   192,   193,   194,   227,   247,   123,   248,     7,
       8,     9,    10,    11,    12,    13,   316,   152,   248,    14,
      15,    16,    42,    43,   291,   292,   293,   319,   174,   372,
     260,   373,    19,   221,   362,   175,   365,   182,   183,   179,
     369,   190,   191,   324,   248,   375,   376,     7,     8,     9,
      10,    11,    12,    13,   178,   294,   294,    14,    15,    16,
      42,    43,   180,   266,   267,   383,   181,   386,   286,   215,
      19,   272,   273,   224,   213,   310,   391,   274,   275,    94,
     231,   230,   232,   393,     7,     8,     9,    10,    11,    12,
      13,   233,   366,   236,   314,   237,   238,    42,    43,   370,
     239,   242,   350,   243,   260,   -10,   249,    19,   250,   252,
     256,   280,   301,   304,  -124,   284,   308,   315,   381,   309,
     318,   227,   322,   323,   330,   334,   314,   331,   336,   332,
     333,   346,  -113,   248,   348,   352,   126,   353,   357,    68,
      69,    70,   359,   358,   363,    71,    72,   371,   374,    23,
     221,   121,   380,    73,   389,   392,   367,   225,   124,    74,
     119,   298,    63,   382,   223,   217,   388,   351,   259,   263,
     265,   321,    75,   262,    65,   127,    76,   246,   128,   329,
     264,   282,   385,    77,   129,     0,   130,     0,   221,   131,
     132,   133,   134,   135,   136,   137,   138,    78,     7,     8,
       9,    10,    11,    12,    13,    79,    80,    81,    14,    15,
      16,    42,    43,     0,     0,     0,    82,    83,    84,    85,
      86,    19,   139,    88,    89,    90,    91,    92,   244,    93,
       0,    68,    69,    70,     0,     0,     0,    71,    72,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,     0,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,     0,    65,   245,    76,     0,
     128,     0,     0,     0,     0,    77,   129,     0,   130,     0,
       0,   131,   132,   133,   134,   135,   136,   137,   138,    78,
       7,     8,     9,    10,    11,    12,    13,    79,    80,    81,
      14,    15,    16,    42,    43,     0,     0,     0,    82,    83,
      84,    85,    86,    19,   139,    88,    89,    90,    91,    92,
     161,    93,     0,    68,    69,    70,     0,     0,     0,    71,
      72,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,     0,     0,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,     0,     0,     0,
      76,     0,  -114,     0,     0,     0,     0,    77,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,     7,     8,     9,    10,    11,    12,    13,    79,
      80,    81,    14,    15,    16,    42,    43,     0,     0,     0,
      82,    83,    84,    85,    86,    19,    87,    88,    89,    90,
      91,    92,   234,    93,     0,    68,    69,    70,     0,     0,
       0,    71,    72,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,     0,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
      65,     0,    76,     0,   128,     0,     0,     0,     0,    77,
     129,     0,   130,     0,     0,   131,   132,   133,   134,   135,
     136,   137,   138,    78,     0,     0,     0,     0,     0,     0,
       0,    79,    80,    81,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,    86,     0,   139,    88,
      89,    90,    91,    92,   161,    93,     0,    68,    69,    70,
       0,     0,     0,    71,    72,     0,     0,     0,     0,     0,
       0,    73,     0,     0,     0,     0,     0,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,     0,     0,     0,    76,     0,     0,     0,     0,     0,
       0,    77,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,     7,     8,     9,    10,
      11,    12,    13,    79,    80,    81,     0,     0,     0,    42,
      43,     0,     0,     0,    82,    83,    84,    85,    86,    19,
      87,    88,    89,    90,    91,    92,    67,    93,     0,    68,
      69,    70,     0,     0,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,     0,    74,
       0,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,   226,   360,    76,     0,     0,     0,
       0,     0,     0,    77,     0,     0,     0,     0,     7,     8,
       9,    10,    11,    12,    13,     0,     0,    78,    14,    15,
      16,    42,    43,     0,     0,    79,    80,    81,     0,     0,
       0,    19,     0,     0,     0,     0,    82,    83,    84,    85,
      86,     0,    87,    88,    89,    90,    91,    92,    67,    93,
       0,    68,    69,    70,     0,     0,     0,    71,    72,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,     0,
       0,    74,     0,     0,     0,   327,     0,     0,     0,     0,
       0,     0,     0,     0,    75,     0,     0,     0,    76,  -220,
       0,     0,     0,     0,     0,    77,     0,     0,     0,     0,
       7,     8,     9,    10,    11,    12,    13,     0,     0,    78,
      14,    15,    16,    42,    43,     0,     0,    79,    80,    81,
       0,     0,     0,    19,     0,     0,     0,     0,    82,    83,
      84,    85,    86,     0,    87,    88,    89,    90,    91,    92,
      67,    93,     0,    68,    69,    70,     0,     0,     0,    71,
      72,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,     0,     0,    74,     0,     0,     0,   337,     0,     0,
       0,     0,     0,     0,     0,     0,    75,     0,   226,     0,
      76,     0,     0,     0,     0,     0,     0,    77,     0,     0,
       0,     0,     7,     8,     9,    10,    11,    12,    13,     0,
       0,    78,    14,    15,    16,    42,    43,     0,     0,    79,
      80,    81,     0,     0,     0,    19,     0,     0,     0,     0,
      82,    83,    84,    85,    86,     0,    87,    88,    89,    90,
      91,    92,   161,    93,     0,    68,    69,    70,     0,     0,
       0,    71,    72,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,     0,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    75,     0,
       0,     0,    76,     0,   240,     0,     0,     0,     0,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,     0,     0,
       0,    79,    80,    81,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,    86,     0,    87,    88,
      89,    90,    91,    92,    67,    93,     0,    68,    69,    70,
       0,     0,     0,    71,    72,     0,     0,     0,     0,     0,
       0,    73,     0,     0,     0,     0,     0,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      75,   281,     0,     0,    76,     0,     0,     0,     0,     0,
       0,    77,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    78,     0,     0,     0,     0,
       0,     0,     0,    79,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,    82,    83,    84,    85,    86,     0,
      87,    88,    89,    90,    91,    92,   161,    93,     0,    68,
      69,    70,     0,     0,     0,    71,    72,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,     0,     0,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,     0,     0,     0,    76,     0,  -114,     0,
       0,     0,     0,    77,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    81,     0,     0,
       0,     0,     0,     0,     0,     0,    82,    83,    84,    85,
      86,     0,    87,    88,    89,    90,    91,    92,   161,    93,
       0,    68,    69,    70,     0,     0,     0,    71,    72,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,     0,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,  -114,     0,     0,    76,     0,
       0,     0,     0,     0,     0,    77,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,     0,     0,     0,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,    82,    83,
      84,    85,    86,     0,    87,    88,    89,    90,    91,    92,
     161,    93,     0,    68,    69,    70,     0,     0,     0,    71,
      72,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,     0,     0,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,     0,     0,     0,
      76,     0,     0,     0,     0,     0,     0,    77,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,     0,     0,     0,     0,     0,     0,     0,    79,
      80,    81,     0,     0,     0,     0,     0,     0,     0,     0,
      82,    83,    84,    85,    86,     0,    87,    88,    89,    90,
      91,    92,    67,    93,     0,    68,    69,    70,     0,     0,
       0,    71,    72,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,     0,     0,    74,     0,     0,     0,     0,
       0,     0,     0,     2,     3,     0,     4,     0,    75,     5,
       0,     0,    76,     0,     0,     0,     0,     0,     0,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,     0,     0,     0,     0,     0,     0,
       6,    79,    80,    81,     0,     0,     0,     0,     0,     0,
       0,     0,    82,    83,    84,    85,    86,     0,    87,    88,
      89,    90,    91,    92,     0,    93,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,    14,    15,    16,    17,
      18,    68,    69,    70,     0,     0,     0,    71,    72,    19,
      20,     0,     0,     0,     0,    73,    21,     0,     0,     0,
       0,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,     0,     0,     0,    76,     0,
       0,     0,     0,     0,     0,    77,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,     0,     0,     0,    79,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,    82,    83,
      84,    85,    86,     0,    87,    88,    89,    90,    91,    92,
       0,    93,    68,    69,    70,     0,     0,     0,    71,    72,
       0,     0,     0,     0,     0,     0,    73,     0,     0,     0,
       0,     0,    74,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   170,     0,     0,     0,    76,
       0,     0,     0,     0,     0,     0,    77,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,     0,     0,     0,     0,     0,     0,     0,    79,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,    82,
      83,    84,    85,    86,     0,    87,    88,    89,    90,    91,
      92,     0,    93,    68,    69,    70,     0,     0,     0,    71,
      72,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,     0,     0,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   289,     0,     0,    75,     0,     0,     0,
      76,     0,     0,     0,     0,     0,     0,    77,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,     0,     0,     0,     0,     0,     0,     0,    79,
      80,    81,   296,     0,     0,     0,     0,     0,     0,     0,
      82,    83,    84,    85,    86,     0,    87,    88,    89,    90,
      91,    92,     0,    93,     0,     7,     8,     9,    10,    11,
      12,    13,     0,     0,     0,    14,    15,    16,    42,    43,
     291,   292,   293,     0,     0,     0,     0,     0,    19
};

static const yytype_int16 yycheck[] =
{
       5,    75,    75,   132,   123,   226,    47,    46,   116,     6,
      83,    18,     6,    40,     6,    37,    37,    18,    45,   348,
       1,    87,    37,    10,    11,    64,    41,     6,    68,    69,
      70,    71,    72,    73,    74,    40,    23,    77,    78,     6,
      37,    42,    82,    37,    25,    37,   192,   193,   194,     9,
      37,   380,    57,    87,    41,    40,    26,    24,    43,    46,
      27,    37,    37,   137,    39,    87,    87,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    47,   285,   153,
      87,   122,   123,    41,    65,    38,    87,    70,    71,    72,
      87,    38,   299,    87,   301,    87,   170,   170,    45,    42,
      40,    39,    45,   177,   250,    88,    89,    90,    91,    92,
     218,   116,    52,    53,    39,    38,   121,    38,    38,    38,
      38,   342,    45,    38,    45,    45,    45,     1,    38,    42,
      45,    43,    45,    45,   175,    45,   176,   211,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,    21,    22,   231,   232,   233,
      38,    43,   236,   144,    39,   206,    40,    45,   242,   210,
      14,    15,    16,    17,    45,   214,   184,   185,   186,   187,
       9,   300,     6,     7,     8,   226,    43,    41,    45,    63,
      64,    65,    66,    67,    68,    69,    43,    43,    45,    73,
      74,    75,    76,    77,    78,    79,    80,   248,    22,    43,
     250,    45,    86,   218,   343,    21,   345,    12,    13,    19,
     349,     4,     5,    44,    45,    52,    53,    63,    64,    65,
      66,    67,    68,    69,    25,   216,   217,    73,    74,    75,
      76,    77,    20,   182,   183,   374,    18,   376,   287,    42,
      86,   188,   189,    38,    48,   236,   385,   190,   191,   300,
      37,    43,    37,   392,    63,    64,    65,    66,    67,    68,
      69,    37,   346,    37,   348,    87,    43,    76,    77,   352,
      43,    37,   323,    44,   324,    43,    43,    86,    38,    87,
      87,    87,    37,    42,    45,    87,    43,    43,   371,    54,
      43,   342,    38,    45,    43,    43,   380,    44,    38,    44,
      44,    37,    43,    45,    43,    23,     1,    38,    38,     4,
       5,     6,    38,    42,    39,    10,    11,    23,    50,     1,
     335,    45,    43,    18,    43,    38,   347,   121,    63,    24,
      57,   221,   347,   373,   118,   115,   377,   324,   176,   179,
     181,   254,    37,   178,    39,    40,    41,   144,    43,   287,
     180,   210,   375,    48,    49,    -1,    51,    -1,   373,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,     1,    94,
      -1,     4,     5,     6,    -1,    -1,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    39,    40,    41,    -1,
      43,    -1,    -1,    -1,    -1,    48,    49,    -1,    51,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       1,    94,    -1,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      41,    -1,    43,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     1,    94,    -1,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      39,    -1,    41,    -1,    43,    -1,    -1,    -1,    -1,    48,
      49,    -1,    51,    -1,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    -1,    87,    88,
      89,    90,    91,    92,     1,    94,    -1,     4,     5,     6,
      -1,    -1,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    -1,    -1,    -1,    76,
      77,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,     1,    94,    -1,     4,
       5,     6,    -1,    -1,    -1,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    68,    69,    -1,    -1,    62,    73,    74,
      75,    76,    77,    -1,    -1,    70,    71,    72,    -1,    -1,
      -1,    86,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    -1,    87,    88,    89,    90,    91,    92,     1,    94,
      -1,     4,     5,     6,    -1,    -1,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    69,    -1,    -1,    62,
      73,    74,    75,    76,    77,    -1,    -1,    70,    71,    72,
      -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    88,    89,    90,    91,    92,
       1,    94,    -1,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    39,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    63,    64,    65,    66,    67,    68,    69,    -1,
      -1,    62,    73,    74,    75,    76,    77,    -1,    -1,    70,
      71,    72,    -1,    -1,    -1,    86,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    -1,    87,    88,    89,    90,
      91,    92,     1,    94,    -1,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,
      -1,    -1,    41,    -1,    43,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    -1,    87,    88,
      89,    90,    91,    92,     1,    94,    -1,     4,     5,     6,
      -1,    -1,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    -1,
      87,    88,    89,    90,    91,    92,     1,    94,    -1,     4,
       5,     6,    -1,    -1,    -1,    10,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    -1,    -1,    41,    -1,    43,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    -1,    87,    88,    89,    90,    91,    92,     1,    94,
      -1,     4,     5,     6,    -1,    -1,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    88,    89,    90,    91,    92,
       1,    94,    -1,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    -1,    87,    88,    89,    90,
      91,    92,     1,    94,    -1,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     0,     1,    -1,     3,    -1,    37,     6,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    -1,    87,    88,
      89,    90,    91,    92,    -1,    94,    63,    64,    65,    66,
      67,    68,    69,    -1,    -1,    -1,    73,    74,    75,    76,
      77,     4,     5,     6,    -1,    -1,    -1,    10,    11,    86,
      87,    -1,    -1,    -1,    -1,    18,    93,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    -1,    87,    88,    89,    90,    91,    92,
      -1,    94,     4,     5,     6,    -1,    -1,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    -1,    87,    88,    89,    90,    91,
      92,    -1,    94,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    37,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
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
       0,    96,     0,     1,     3,     6,    37,    63,    64,    65,
      66,    67,    68,    69,    73,    74,    75,    76,    77,    86,
      87,    93,    97,    98,   101,   102,   103,   109,   115,   123,
     126,   127,    40,    43,   109,   126,    87,    87,    37,    99,
     100,   126,    76,    77,   101,   126,   125,    41,    38,    39,
      39,    38,   101,   111,   112,   113,    43,    37,    87,   104,
     105,   106,   107,   109,   124,    39,   129,     1,     4,     5,
       6,    10,    11,    18,    24,    37,    41,    48,    62,    70,
      71,    72,    81,    82,    83,    84,    85,    87,    88,    89,
      90,    91,    92,    94,   144,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   169,   172,   116,   117,   114,    38,    45,   106,
      43,    45,     9,    41,   107,   129,     1,    40,    43,    49,
      51,    54,    55,    56,    57,    58,    59,    60,    61,    87,
      98,   101,   128,   129,   130,   131,   132,   136,   141,   142,
     143,   144,    43,    37,   158,   158,   158,   158,   158,   158,
     158,     1,   103,   143,    18,    42,    87,   163,   164,   158,
      37,   158,   158,   103,    22,    21,    26,    47,    25,    19,
      20,    18,    12,    13,    14,    15,    16,    17,    21,    22,
       4,     5,     6,     7,     8,     9,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,   145,    10,    11,    23,
      37,    41,    46,    48,   165,    42,   118,   118,    37,    87,
     108,   109,   110,   113,    38,   105,    39,   144,   170,   169,
      43,    37,    37,    37,     1,   128,    37,    87,    43,    43,
      43,   143,    37,    44,     1,    40,   131,    43,    45,    43,
      38,    38,    87,    42,    45,   103,    87,   144,   168,   148,
     158,   143,   149,   150,   151,   152,   153,   153,   154,   154,
     154,   154,   155,   155,   156,   156,   157,   157,   157,   144,
      87,    38,   168,   143,    87,    37,   129,   166,   167,     1,
      40,    78,    79,    80,   101,   119,    40,   108,   110,    37,
      41,    37,   170,   171,    42,   143,   143,   143,    43,    54,
     101,   137,   138,   140,   143,    43,    43,   143,    43,   144,
     157,   164,    38,    45,    44,    38,    42,    38,   111,   167,
      43,    44,    44,    44,    43,   120,    38,    38,   111,   169,
     111,    40,    45,    38,    38,    38,    37,   139,    43,    38,
     144,   146,    23,    38,   108,   121,   122,    38,    42,    38,
      40,   170,   128,    39,   133,   128,   143,   104,   140,   128,
     103,    23,    43,    45,    50,    52,    53,   134,   135,    38,
      43,   103,   122,   128,    92,   172,   128,    40,   135,    43,
     140,   128,    38,   128
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    97,    97,    97,    97,    97,    97,
      99,    98,   100,    98,    98,   101,   101,   101,   102,   102,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   105,   106,   106,   107,   107,   107,   107,
     108,   108,   109,   109,   110,   110,   110,   110,   110,   111,
     112,   112,   114,   113,   113,   116,   115,   117,   115,   118,
     118,   119,   119,   119,   120,   119,   119,   119,   121,   121,
     122,   124,   123,   125,   123,   123,   126,   126,   127,   127,
     127,   127,   128,   128,   128,   128,   128,   128,   128,   128,
     129,   129,   130,   130,   130,   131,   131,   132,   132,   132,
     133,   134,   134,   135,   135,   136,   136,   136,   136,   137,
     137,   139,   138,   138,   140,   140,   141,   142,   142,   142,
     142,   142,   143,   143,   143,   144,   144,   144,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   146,
     146,   147,   147,   148,   148,   149,   149,   150,   150,   151,
     151,   152,   152,   152,   153,   153,   153,   153,   153,   154,
     154,   154,   155,   155,   155,   156,   156,   156,   156,   157,
     157,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   161,   161,   162,   162,   163,   163,   164,   164,   164,
     165,   165,   165,   166,   166,   166,   166,   167,   168,   168,
     169,   169,   170,   170,   170,   171,   171,   172,   172,   172,
     172,   172,   172,   172,   172
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     2,
       0,     3,     0,     4,     2,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     2,     1,     1,     3,     6,     4,
       2,     1,     1,     2,     1,     3,     4,     3,     4,     1,
       1,     3,     0,     3,     1,     0,     6,     0,     6,     0,
       2,     2,     2,     2,     0,     4,     2,     2,     1,     3,
       1,     0,     4,     0,     3,     2,     1,     2,     4,     3,
       3,     4,     1,     1,     1,     1,     1,     2,     1,     2,
       2,     3,     1,     2,     2,     1,     1,     5,     7,     5,
       3,     2,     1,     3,     2,     5,     5,     7,     9,     1,
       1,     0,     3,     1,     0,     1,     2,     3,     2,     2,
       2,     3,     1,     3,     2,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       4,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     4,     1,     4,     3,     4,     3,     3,     2,     2,
       2,     2,     1,     1,     1,     3,     3,     3,     1,     1,
       1,     4,     3,     2,     3,     1,     3,     1,     2,     1,
       0,     1,     0,     3,     2,     5,     4,     1,     1,     3,
       0,     1,     1,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1
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
  case 9: /* external_declaration: error SEMICOLON  */
#line 239 "src/parser.y"
      { yyerrok; }
#line 2014 "src/parser.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 243 "src/parser.y"
                             { curr_decl_spec = (yyvsp[0].str); pending_role = "IDENTIFIER"; pending_ids.clear(); }
#line 2020 "src/parser.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 244 "src/parser.y"
                             { curr_decl_spec = (yyvsp[0].str); pending_role = "IDENTIFIER"; pending_ids.clear(); }
#line 2026 "src/parser.tab.c"
    break;

  case 13: /* declaration: declaration_specifiers $@2 init_declarator_list_no_func SEMICOLON  */
#line 246 "src/parser.y"
      { flush_pending(curr_decl_spec, pending_role); }
#line 2032 "src/parser.tab.c"
    break;

  case 14: /* declaration: error SEMICOLON  */
#line 248 "src/parser.y"
      { yyerrok; }
#line 2038 "src/parser.tab.c"
    break;

  case 15: /* declaration_specifiers: type_specifier  */
#line 252 "src/parser.y"
                     { (yyval.str) = (yyvsp[0].str); }
#line 2044 "src/parser.tab.c"
    break;

  case 16: /* declaration_specifiers: AUTO  */
#line 253 "src/parser.y"
           { (yyval.str) = (yyvsp[0].str); }
#line 2050 "src/parser.tab.c"
    break;

  case 17: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 254 "src/parser.y"
                                                     { (yyval.str) = cat2((yyvsp[-1].str), (yyvsp[0].str)); }
#line 2056 "src/parser.tab.c"
    break;

  case 18: /* storage_class_specifier: STATIC  */
#line 258 "src/parser.y"
               { (yyval.str) = sdup("STATIC"); }
#line 2062 "src/parser.tab.c"
    break;

  case 19: /* storage_class_specifier: CONST  */
#line 259 "src/parser.y"
               { (yyval.str) = sdup("CONST"); }
#line 2068 "src/parser.tab.c"
    break;

  case 20: /* type_specifier: VOID  */
#line 263 "src/parser.y"
               { (yyval.str) = sdup("VOID"); }
#line 2074 "src/parser.tab.c"
    break;

  case 21: /* type_specifier: INT  */
#line 264 "src/parser.y"
               { (yyval.str) = sdup("INT"); }
#line 2080 "src/parser.tab.c"
    break;

  case 22: /* type_specifier: LONG  */
#line 265 "src/parser.y"
               { (yyval.str) = sdup("LONG"); }
#line 2086 "src/parser.tab.c"
    break;

  case 23: /* type_specifier: DOUBLE  */
#line 266 "src/parser.y"
               { (yyval.str) = sdup("DOUBLE"); }
#line 2092 "src/parser.tab.c"
    break;

  case 24: /* type_specifier: CHAR  */
#line 267 "src/parser.y"
               { (yyval.str) = sdup("CHAR"); }
#line 2098 "src/parser.tab.c"
    break;

  case 25: /* type_specifier: BOOL  */
#line 268 "src/parser.y"
               { (yyval.str) = sdup("BOOL"); }
#line 2104 "src/parser.tab.c"
    break;

  case 26: /* type_specifier: STRING  */
#line 269 "src/parser.y"
               { (yyval.str) = sdup("STRING"); }
#line 2110 "src/parser.tab.c"
    break;

  case 27: /* type_specifier: TYPE_NAME  */
#line 270 "src/parser.y"
               { (yyval.str) = sdup((yyvsp[0].str)); }
#line 2116 "src/parser.tab.c"
    break;

  case 28: /* type_specifier: STRUCT  */
#line 271 "src/parser.y"
               { (yyval.str) = sdup("STRUCT"); }
#line 2122 "src/parser.tab.c"
    break;

  case 29: /* type_specifier: CLASS  */
#line 272 "src/parser.y"
               { (yyval.str) = sdup("CLASS"); }
#line 2128 "src/parser.tab.c"
    break;

  case 32: /* init_declarator_no_func: declarator_no_func  */
#line 281 "src/parser.y"
                                               { push_id((yyvsp[0].str)); }
#line 2134 "src/parser.tab.c"
    break;

  case 33: /* init_declarator_no_func: declarator_no_func ASSIGN initializer  */
#line 282 "src/parser.y"
                                               { push_id((yyvsp[-2].str)); }
#line 2140 "src/parser.tab.c"
    break;

  case 34: /* declarator_no_func: pointer direct_declarator_no_func  */
#line 286 "src/parser.y"
                                           { last_declarator_pointer = (yyvsp[-1].str); curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[0].str); }
#line 2146 "src/parser.tab.c"
    break;

  case 35: /* declarator_no_func: direct_declarator_no_func  */
#line 287 "src/parser.y"
                                           { last_declarator_pointer = NULL; curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[0].str); }
#line 2152 "src/parser.tab.c"
    break;

  case 40: /* declarator: pointer direct_declarator  */
#line 308 "src/parser.y"
                                           { last_declarator_pointer = (yyvsp[-1].str); curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[0].str); }
#line 2158 "src/parser.tab.c"
    break;

  case 41: /* declarator: direct_declarator  */
#line 309 "src/parser.y"
                                           { last_declarator_pointer = NULL; curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[0].str); }
#line 2164 "src/parser.tab.c"
    break;

  case 42: /* pointer: STAR  */
#line 313 "src/parser.y"
                                     { (yyval.str) = sdup("pointer"); }
#line 2170 "src/parser.tab.c"
    break;

  case 43: /* pointer: STAR pointer  */
#line 314 "src/parser.y"
                                     { (yyval.str) = cat2((yyvsp[0].str), "pointer"); }
#line 2176 "src/parser.tab.c"
    break;

  case 44: /* direct_declarator: IDENTIFIER  */
#line 319 "src/parser.y"
                                                           { (yyval.str) = (yyvsp[0].str); }
#line 2182 "src/parser.tab.c"
    break;

  case 45: /* direct_declarator: LROUND declarator RROUND  */
#line 320 "src/parser.y"
                                                           { (yyval.str) = (yyvsp[-1].str); }
#line 2188 "src/parser.tab.c"
    break;

  case 46: /* direct_declarator: direct_declarator LROUND parameter_type_list RROUND  */
#line 321 "src/parser.y"
                                                           { (yyval.str) = (yyvsp[-3].str); }
#line 2194 "src/parser.tab.c"
    break;

  case 47: /* direct_declarator: direct_declarator LROUND RROUND  */
#line 322 "src/parser.y"
                                                           { (yyval.str) = (yyvsp[-2].str); }
#line 2200 "src/parser.tab.c"
    break;

  case 48: /* direct_declarator: direct_declarator LSQUARE constant_expression_opt RSQUARE  */
#line 323 "src/parser.y"
                                                                { (yyval.str) = (yyvsp[-3].str); }
#line 2206 "src/parser.tab.c"
    break;

  case 52: /* $@3: %empty  */
#line 336 "src/parser.y"
                             { curr_param_spec = (yyvsp[0].str); }
#line 2212 "src/parser.tab.c"
    break;

  case 53: /* parameter_declaration: declaration_specifiers $@3 declarator  */
#line 337 "src/parser.y"
        { insert_symbol_table((yyvsp[0].str), curr_param_spec ? curr_param_spec : "", "PARAM"); }
#line 2218 "src/parser.tab.c"
    break;

  case 55: /* $@4: %empty  */
#line 342 "src/parser.y"
                               { insert_symbol_table((yyvsp[-1].str), sdup("CLASS"), "TYPE"); }
#line 2224 "src/parser.tab.c"
    break;

  case 57: /* $@5: %empty  */
#line 343 "src/parser.y"
                               { insert_symbol_table((yyvsp[-1].str), sdup("STRUCT"), "TYPE"); }
#line 2230 "src/parser.tab.c"
    break;

  case 64: /* $@6: %empty  */
#line 355 "src/parser.y"
                             { curr_decl_spec = (yyvsp[0].str); pending_role = "MEMBER"; pending_ids.clear(); }
#line 2236 "src/parser.tab.c"
    break;

  case 65: /* member_declaration: declaration_specifiers $@6 member_declarator_list SEMICOLON  */
#line 357 "src/parser.y"
      { flush_pending(curr_decl_spec, pending_role); }
#line 2242 "src/parser.tab.c"
    break;

  case 67: /* member_declaration: error SEMICOLON  */
#line 360 "src/parser.y"
      { yyerrok; }
#line 2248 "src/parser.tab.c"
    break;

  case 70: /* member_declarator: declarator  */
#line 369 "src/parser.y"
                                  { push_id((yyvsp[0].str)); }
#line 2254 "src/parser.tab.c"
    break;

  case 71: /* $@7: %empty  */
#line 373 "src/parser.y"
                                                {
          curr_func_spec = (yyvsp[-1].str);
          curr_decl_lineno = last_ident_lineno;
          insert_symbol_table((yyvsp[0].str), curr_func_spec ? curr_func_spec : "", "FUNCTION");
        }
#line 2264 "src/parser.tab.c"
    break;

  case 72: /* function_definition: declaration_specifiers function_declarator $@7 compound_statement  */
#line 378 "src/parser.y"
                          {
          curr_func_spec = NULL;
        }
#line 2272 "src/parser.tab.c"
    break;

  case 73: /* $@8: %empty  */
#line 381 "src/parser.y"
                         {
          curr_decl_lineno = last_ident_lineno;
        }
#line 2280 "src/parser.tab.c"
    break;

  case 74: /* function_definition: function_declarator $@8 compound_statement  */
#line 385 "src/parser.y"
        { insert_symbol_table((yyvsp[-2].str), "INT", "FUNCTION"); }
#line 2286 "src/parser.tab.c"
    break;

  case 75: /* function_definition: error RCURLY  */
#line 387 "src/parser.y"
      { yyerrok; }
#line 2292 "src/parser.tab.c"
    break;

  case 76: /* function_declarator: direct_function_declarator  */
#line 392 "src/parser.y"
                                                       { (yyval.str) = (yyvsp[0].str); }
#line 2298 "src/parser.tab.c"
    break;

  case 77: /* function_declarator: pointer function_declarator  */
#line 393 "src/parser.y"
                                                       { (yyval.str) = (yyvsp[0].str); }
#line 2304 "src/parser.tab.c"
    break;

  case 78: /* direct_function_declarator: IDENTIFIER LROUND parameter_type_list RROUND  */
#line 397 "src/parser.y"
                                                       { curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[-3].str); }
#line 2310 "src/parser.tab.c"
    break;

  case 79: /* direct_function_declarator: IDENTIFIER LROUND RROUND  */
#line 398 "src/parser.y"
                                                       { curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[-2].str); }
#line 2316 "src/parser.tab.c"
    break;

  case 80: /* direct_function_declarator: LROUND function_declarator RROUND  */
#line 399 "src/parser.y"
                                                       { (yyval.str) = (yyvsp[-1].str); }
#line 2322 "src/parser.tab.c"
    break;

  case 81: /* direct_function_declarator: direct_function_declarator LSQUARE constant_expression_opt RSQUARE  */
#line 400 "src/parser.y"
                                                                         { (yyval.str) = (yyvsp[-3].str); }
#line 2328 "src/parser.tab.c"
    break;

  case 89: /* statement: error SEMICOLON  */
#line 412 "src/parser.y"
      { yyerrok; }
#line 2334 "src/parser.tab.c"
    break;

  case 94: /* block_item_list: error SEMICOLON  */
#line 424 "src/parser.y"
      { yyerrok; }
#line 2340 "src/parser.tab.c"
    break;

  case 111: /* $@9: %empty  */
#line 465 "src/parser.y"
                             { curr_decl_spec = (yyvsp[0].str); pending_role = "IDENTIFIER"; pending_ids.clear(); }
#line 2346 "src/parser.tab.c"
    break;

  case 112: /* for_declaration: declaration_specifiers $@9 init_declarator_list_no_func  */
#line 467 "src/parser.y"
      { flush_pending(curr_decl_spec, pending_role); }
#line 2352 "src/parser.tab.c"
    break;

  case 113: /* for_declaration: declaration_specifiers  */
#line 468 "src/parser.y"
                             {
        flush_pending(curr_decl_spec, pending_role);
      }
#line 2360 "src/parser.tab.c"
    break;

  case 116: /* label: IDENTIFIER COLON  */
#line 479 "src/parser.y"
                       { insert_symbol_table((yyvsp[-1].str), sdup("LABEL"), "IDENTIFIER");   }
#line 2366 "src/parser.tab.c"
    break;

  case 124: /* expression: error SEMICOLON  */
#line 493 "src/parser.y"
                      { yyerrok; }
#line 2372 "src/parser.tab.c"
    break;

  case 127: /* assignment_expression: error SEMICOLON  */
#line 499 "src/parser.y"
                      { yyerrok; }
#line 2378 "src/parser.tab.c"
    break;

  case 194: /* primary_expression: STRING_LITERAL  */
#line 614 "src/parser.y"
                                          { insert_const_symbol_table('S',(yyvsp[0].str)); }
#line 2384 "src/parser.tab.c"
    break;

  case 227: /* constant: DECIMAL_LITERAL  */
#line 697 "src/parser.y"
                            { insert_const_symbol_table('I',(yyvsp[0].str)); }
#line 2390 "src/parser.tab.c"
    break;

  case 228: /* constant: CHARACTER_LITERAL  */
#line 698 "src/parser.y"
                            { insert_const_symbol_table('C',(yyvsp[0].str)); }
#line 2396 "src/parser.tab.c"
    break;

  case 229: /* constant: STRING_LITERAL  */
#line 699 "src/parser.y"
                            { insert_const_symbol_table('S',(yyvsp[0].str)); }
#line 2402 "src/parser.tab.c"
    break;

  case 230: /* constant: EXPONENT_LITERAL  */
#line 700 "src/parser.y"
                            { insert_const_symbol_table('E',(yyvsp[0].str)); }
#line 2408 "src/parser.tab.c"
    break;

  case 231: /* constant: DOUBLE_LITERAL  */
#line 701 "src/parser.y"
                            { insert_const_symbol_table('D',(yyvsp[0].str)); }
#line 2414 "src/parser.tab.c"
    break;

  case 232: /* constant: NULLPTR  */
#line 702 "src/parser.y"
                            { insert_const_symbol_table('N',(yyvsp[0].str)); }
#line 2420 "src/parser.tab.c"
    break;

  case 233: /* constant: TRUE  */
#line 703 "src/parser.y"
                            { insert_const_symbol_table('B',(yyvsp[0].str)); }
#line 2426 "src/parser.tab.c"
    break;

  case 234: /* constant: FALSE  */
#line 704 "src/parser.y"
                            { insert_const_symbol_table('B',(yyvsp[0].str)); }
#line 2432 "src/parser.tab.c"
    break;


#line 2436 "src/parser.tab.c"

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

#line 707 "src/parser.y"


int main() {
    yyparse();
    print_symbol_table();
    cout << endl;
    print_constant_table();
    print_error();
    return 0;
}
