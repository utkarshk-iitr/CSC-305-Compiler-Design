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
#line 1 "cpp.y"

    #include <iostream>
    #include <string.h>
    #include <iomanip>
    #include <vector>
    #include <string>
    #include <cstdlib>
    using namespace std;

#line 81 "cpp.tab.c"

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

#include "cpp.tab.h"
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
  YYSYMBOL_IF = 51,                        /* IF  */
  YYSYMBOL_ELSE = 52,                      /* ELSE  */
  YYSYMBOL_SWITCH = 53,                    /* SWITCH  */
  YYSYMBOL_CASE = 54,                      /* CASE  */
  YYSYMBOL_DEFAULT = 55,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 56,                     /* WHILE  */
  YYSYMBOL_DO = 57,                        /* DO  */
  YYSYMBOL_FOR = 58,                       /* FOR  */
  YYSYMBOL_GOTO = 59,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 60,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 61,                     /* BREAK  */
  YYSYMBOL_RETURN = 62,                    /* RETURN  */
  YYSYMBOL_UNTIL = 63,                     /* UNTIL  */
  YYSYMBOL_SIZEOF = 64,                    /* SIZEOF  */
  YYSYMBOL_VOID = 65,                      /* VOID  */
  YYSYMBOL_INT = 66,                       /* INT  */
  YYSYMBOL_DOUBLE = 67,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 68,                      /* CHAR  */
  YYSYMBOL_BOOL = 69,                      /* BOOL  */
  YYSYMBOL_STRING = 70,                    /* STRING  */
  YYSYMBOL_LONG = 71,                      /* LONG  */
  YYSYMBOL_TRUE = 72,                      /* TRUE  */
  YYSYMBOL_FALSE = 73,                     /* FALSE  */
  YYSYMBOL_NULLPTR = 74,                   /* NULLPTR  */
  YYSYMBOL_AUTO = 75,                      /* AUTO  */
  YYSYMBOL_STATIC = 76,                    /* STATIC  */
  YYSYMBOL_CONST = 77,                     /* CONST  */
  YYSYMBOL_CLASS = 78,                     /* CLASS  */
  YYSYMBOL_STRUCT = 79,                    /* STRUCT  */
  YYSYMBOL_PUBLIC = 80,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 81,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 82,                 /* PROTECTED  */
  YYSYMBOL_DELETE = 83,                    /* DELETE  */
  YYSYMBOL_NEW = 84,                       /* NEW  */
  YYSYMBOL_CIN = 85,                       /* CIN  */
  YYSYMBOL_COUT = 86,                      /* COUT  */
  YYSYMBOL_ENDL = 87,                      /* ENDL  */
  YYSYMBOL_IDENTIFIER = 88,                /* IDENTIFIER  */
  YYSYMBOL_DECIMAL_LITERAL = 89,           /* DECIMAL_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 90,            /* DOUBLE_LITERAL  */
  YYSYMBOL_EXPONENT_LITERAL = 91,          /* EXPONENT_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 92,         /* CHARACTER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 93,            /* STRING_LITERAL  */
  YYSYMBOL_LOWER_THAN_ELSE = 94,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_primary_expression = 96,        /* primary_expression  */
  YYSYMBOL_constant = 97,                  /* constant  */
  YYSYMBOL_postfix_expression = 98,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 99,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 100,         /* unary_expression  */
  YYSYMBOL_unary_operator = 101,           /* unary_operator  */
  YYSYMBOL_new_expression = 102,           /* new_expression  */
  YYSYMBOL_pointer_opt = 103,              /* pointer_opt  */
  YYSYMBOL_scalar_new_init_opt = 104,      /* scalar_new_init_opt  */
  YYSYMBOL_new_declarator = 105,           /* new_declarator  */
  YYSYMBOL_delete_expression = 106,        /* delete_expression  */
  YYSYMBOL_cast_expression = 107,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 108, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 109,      /* additive_expression  */
  YYSYMBOL_shift_expression = 110,         /* shift_expression  */
  YYSYMBOL_relational_expression = 111,    /* relational_expression  */
  YYSYMBOL_equality_expression = 112,      /* equality_expression  */
  YYSYMBOL_and_expression = 113,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 114,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 115,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 116,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 117,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 118,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 119,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 120,      /* assignment_operator  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_constant_expression = 122,      /* constant_expression  */
  YYSYMBOL_declaration = 123,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 124,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 125,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 126,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 127,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 128,           /* type_specifier  */
  YYSYMBOL_struct_or_class_specifier = 129, /* struct_or_class_specifier  */
  YYSYMBOL_struct_or_class = 130,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 131, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 132,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 133,   /* access_specifier_label  */
  YYSYMBOL_member_declaration = 134,       /* member_declaration  */
  YYSYMBOL_constructor_definition = 135,   /* constructor_definition  */
  YYSYMBOL_destructor_definition = 136,    /* destructor_definition  */
  YYSYMBOL_struct_declarator_list = 137,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 138,        /* struct_declarator  */
  YYSYMBOL_specifier_qualifier_list = 139, /* specifier_qualifier_list  */
  YYSYMBOL_type_qualifier = 140,           /* type_qualifier  */
  YYSYMBOL_declarator = 141,               /* declarator  */
  YYSYMBOL_direct_declarator = 142,        /* direct_declarator  */
  YYSYMBOL_pointer = 143,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 144,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 145,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 146,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 147,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 148,          /* identifier_list  */
  YYSYMBOL_type_name = 149,                /* type_name  */
  YYSYMBOL_abstract_declarator = 150,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 151, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 152,              /* initializer  */
  YYSYMBOL_initializer_list = 153,         /* initializer_list  */
  YYSYMBOL_statement = 154,                /* statement  */
  YYSYMBOL_io_statement = 155,             /* io_statement  */
  YYSYMBOL_cout_expression = 156,          /* cout_expression  */
  YYSYMBOL_insertion_list = 157,           /* insertion_list  */
  YYSYMBOL_cin_expression = 158,           /* cin_expression  */
  YYSYMBOL_extraction_list = 159,          /* extraction_list  */
  YYSYMBOL_labeled_statement = 160,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 161,       /* compound_statement  */
  YYSYMBOL_statement_list = 162,           /* statement_list  */
  YYSYMBOL_expression_statement = 163,     /* expression_statement  */
  YYSYMBOL_selection_statement = 164,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 165,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 166,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 167,           /* jump_statement  */
  YYSYMBOL_translation_unit = 168,         /* translation_unit  */
  YYSYMBOL_external_declaration = 169,     /* external_declaration  */
  YYSYMBOL_declaration_list = 170,         /* declaration_list  */
  YYSYMBOL_function_definition = 171,      /* function_definition  */
  YYSYMBOL_lambda_expression = 172,        /* lambda_expression  */
  YYSYMBOL_lambda_declarator = 173,        /* lambda_declarator  */
  YYSYMBOL_lambda_parameter_clause = 174,  /* lambda_parameter_clause  */
  YYSYMBOL_trailing_return_opt = 175,      /* trailing_return_opt  */
  YYSYMBOL_lambda_capture_clause = 176,    /* lambda_capture_clause  */
  YYSYMBOL_capture_list = 177              /* capture_list  */
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
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2060

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  261
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  432

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
       0,    64,    64,    65,    66,    67,    71,    72,    73,    74,
      75,    76,    77,    78,    82,    83,    84,    85,    86,    87,
      88,    89,    93,    94,    98,    99,   100,   101,   102,   103,
     104,   105,   109,   110,   111,   112,   113,   114,   118,   119,
     120,   121,   122,   123,   124,   125,   129,   130,   134,   135,
     139,   140,   144,   145,   149,   150,   154,   155,   156,   157,
     161,   162,   163,   167,   168,   169,   173,   174,   175,   176,
     177,   181,   182,   183,   187,   188,   192,   193,   197,   198,
     202,   203,   207,   208,   212,   213,   217,   218,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   236,
     237,   241,   245,   246,   250,   251,   252,   253,   254,   255,
     259,   260,   264,   265,   269,   270,   271,   275,   276,   277,
     278,   279,   280,   281,   282,   286,   287,   291,   292,   296,
     297,   301,   302,   306,   307,   308,   312,   313,   314,   315,
     316,   317,   318,   322,   323,   327,   331,   332,   336,   340,
     341,   342,   343,   347,   351,   352,   356,   357,   358,   359,
     360,   361,   362,   366,   367,   368,   369,   373,   374,   378,
     382,   383,   387,   388,   389,   393,   394,   398,   399,   403,
     404,   405,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   421,   422,   423,   427,   428,   432,   433,   434,   435,
     436,   437,   438,   442,   443,   447,   451,   452,   453,   454,
     458,   462,   463,   467,   468,   469,   473,   474,   475,   476,
     480,   481,   485,   486,   490,   491,   492,   496,   497,   498,
     499,   500,   504,   505,   509,   510,   511,   512,   513,   517,
     518,   522,   523,   524,   528,   529,   533,   534,   538,   539,
     543,   547,   548,   552,   553,   557,   558,   559,   560,   561,
     565,   566
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
  "DOT", "QUESTION_MARK", "TILDE", "IF", "ELSE", "SWITCH", "CASE",
  "DEFAULT", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN",
  "UNTIL", "SIZEOF", "VOID", "INT", "DOUBLE", "CHAR", "BOOL", "STRING",
  "LONG", "TRUE", "FALSE", "NULLPTR", "AUTO", "STATIC", "CONST", "CLASS",
  "STRUCT", "PUBLIC", "PRIVATE", "PROTECTED", "DELETE", "NEW", "CIN",
  "COUT", "ENDL", "IDENTIFIER", "DECIMAL_LITERAL", "DOUBLE_LITERAL",
  "EXPONENT_LITERAL", "CHARACTER_LITERAL", "STRING_LITERAL",
  "LOWER_THAN_ELSE", "$accept", "primary_expression", "constant",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "new_expression", "pointer_opt", "scalar_new_init_opt",
  "new_declarator", "delete_expression", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_class_specifier",
  "struct_or_class", "struct_or_class_member_list",
  "struct_or_class_member", "access_specifier_label", "member_declaration",
  "constructor_definition", "destructor_definition",
  "struct_declarator_list", "struct_declarator",
  "specifier_qualifier_list", "type_qualifier", "declarator",
  "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "statement", "io_statement", "cout_expression", "insertion_list",
  "cin_expression", "extraction_list", "labeled_statement",
  "compound_statement", "statement_list", "expression_statement",
  "selection_statement", "iteration_statement", "for_init_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "declaration_list", "function_definition", "lambda_expression",
  "lambda_declarator", "lambda_parameter_clause", "trailing_return_opt",
  "lambda_capture_clause", "capture_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-274)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     194,  -274,  -274,    15,     9,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,    30,
     515,   515,    17,   -20,   515,    36,   162,     2,   639,  -274,
    -274,  -274,  -274,    15,    45,  -274,    49,  -274,    47,  -274,
    -274,  -274,    85,  -274,   349,  -274,   240,  1032,   162,  -274,
    -274,  -274,  -274,  -274,  -274,     9,  1087,  -274,  1913,  -274,
    -274,  -274,  1637,  1637,  -274,  -274,   603,  -274,    31,  -274,
    -274,    93,   101,  1692,   100,   119,   889,   133,    75,   148,
     165,  1142,   168,  1747,  -274,  -274,  -274,  1802,   565,   189,
     209,   180,  -274,  -274,  -274,  -274,  -274,  -274,  -274,   117,
     437,  1692,  -274,  -274,  -274,   258,   231,   251,   302,   269,
     220,   224,   232,   249,    32,  -274,  -274,   110,  -274,    30,
    -274,  -274,   241,   253,  -274,  -274,   713,  -274,  -274,  -274,
    -274,   439,  -274,  -274,  -274,     7,   254,   244,  -274,    25,
    -274,  -274,  -274,  -274,   270,  -274,   316,  1087,  -274,  -274,
    -274,   247,   293,   294,   297,   305,   154,   301,  1874,  -274,
    -274,  -274,  -274,  -274,    39,   154,  1692,  -274,  -274,    26,
      62,   308,   303,  -274,   307,   311,  1692,  1692,   313,   889,
    1692,   304,   529,   318,  -274,  -274,  -274,   122,  1692,   603,
    -274,     5,  -274,    98,  1692,   340,  1197,   342,   889,  -274,
    -274,   278,  1252,  1692,   279,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  1692,  -274,  1692,  1692,
    1692,  1692,  1692,  1692,  1692,  1692,  1692,  1692,  1692,  1692,
    1692,  1692,  1692,  1692,  1692,  1692,  1692,  -274,  1692,  -274,
    -274,  -274,  -274,  -274,  -274,   801,  1838,  1307,  -274,   -12,
    -274,   213,  -274,   515,  -274,   280,  -274,  -274,    44,   332,
    -274,  -274,  -274,  1794,  -274,  -274,  -274,  -274,  -274,  -274,
     171,  -274,    47,  -274,  -274,  1960,   215,  -274,  1692,   285,
     188,    34,    27,    40,   889,  -274,    42,   335,  -274,  -274,
    1362,  -274,  -274,    81,   336,  1692,  -274,  1417,  1692,   238,
    -274,   246,  -274,  1692,  -274,  -274,  1472,  -274,  -274,  -274,
     103,  -274,    66,  -274,  -274,  -274,  -274,  -274,   258,   258,
     231,   231,   251,   251,   251,   251,   302,   302,   269,   220,
     224,   232,   249,   250,  -274,  -274,  -274,   337,   338,  -274,
     339,   213,  1945,  1527,  -274,  -274,  -274,   977,   344,    36,
     114,  -274,     9,  -274,  -274,   333,  1983,  -274,    36,   354,
    -274,  -274,   889,   889,  -274,   889,  1692,  1582,   889,  -274,
    -274,  -274,  -274,   124,    68,  -274,   246,  1692,  -274,  -274,
    -274,  -274,  -274,  1692,  -274,  1692,  -274,  -274,  -274,  -274,
     345,  -274,   343,  -274,  -274,    36,  -274,    36,  -274,   298,
    -274,   195,  -274,   565,  -274,   330,  -274,  -274,   201,   889,
     203,  -274,  -274,  -274,  -274,    87,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,   889,   348,  -274,   889,  -274,  -274,
    -274,  -274
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   114,   124,   163,     0,   117,   119,   121,   118,   122,
     123,   120,   116,   115,   153,   128,   127,   156,   243,     0,
     104,   106,     0,     0,   108,     0,   155,     0,     0,   239,
     241,   167,   165,   164,     0,   102,     0,   110,   112,   105,
     107,   242,   126,   109,     0,   247,     0,     0,   154,     1,
     240,   168,   166,   157,   103,     0,     0,   246,     0,    34,
      35,    33,     0,     0,    32,    37,     0,   216,   255,   222,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,    11,     0,     0,     0,
       0,     2,     6,    10,     9,     7,     8,    14,     3,    24,
      54,     0,    31,    30,    56,    60,    63,    66,    71,    74,
      76,    78,    80,    82,    84,    86,    99,     0,   244,     0,
     220,   202,     0,     0,   196,   197,     0,   198,   199,   200,
     201,     0,     5,   162,   175,   174,     0,   169,   170,     0,
     159,     2,    54,   101,     0,   111,   112,     0,   191,   113,
     140,     0,     0,     0,     0,     0,   150,     0,     0,   129,
     131,   132,   141,   142,     0,   152,     0,    25,    26,     0,
     177,     0,   256,   260,     0,   257,     0,     0,     0,     0,
       0,     0,     0,     0,   235,   236,   237,     0,     0,     0,
      28,     0,    53,    45,     0,   210,     0,   205,     0,    20,
      21,     0,     0,     0,     0,    88,    92,    93,    89,    90,
      91,    96,    98,    97,    94,    95,     0,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   223,     0,   203,
     204,   217,   221,   218,   245,     0,     0,     0,   172,   179,
     173,   180,   160,     0,   161,     0,   158,   194,     0,     0,
     133,   134,   135,     0,   149,   139,   125,   130,   137,   148,
       0,   146,   112,   151,     4,     0,   179,   178,     0,     0,
       0,     0,     0,     0,     0,   215,     0,     0,   233,   232,
       0,   234,   238,     0,     0,     0,    47,     0,     0,    42,
      44,    43,   211,     0,   207,   206,     0,   213,    19,    16,
       0,    22,     0,    18,    87,    57,    58,    59,    61,    62,
      64,    65,    68,    67,    69,    70,    72,    73,    75,    77,
      79,    81,    83,     0,   100,   219,   187,     0,     0,   183,
       0,   181,     0,     0,   171,   176,   192,     0,     0,     0,
       0,   136,     0,   138,    55,   259,     0,   249,     0,   253,
     258,   261,     0,     0,   214,     0,     0,     0,     0,    29,
      52,    46,    48,     0,     0,    40,    41,     0,    39,   212,
     208,   209,    17,     0,    15,     0,   188,   182,   184,   189,
       0,   185,     0,   193,   195,     0,   144,     0,   147,     0,
     251,     0,   248,     0,   250,   224,   226,   227,     0,     0,
       0,   228,    49,    50,    38,     0,    23,    85,   190,   186,
     145,   143,   252,   254,     0,     0,   230,     0,    51,   225,
     229,   231
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -274,  -274,  -274,  -274,    92,   -44,  -274,  -274,   102,  -273,
      96,  -274,   -67,    91,    99,   104,   108,   166,   164,   196,
     167,   192,  -274,   -43,    -2,  -274,   -41,   -51,   -33,    35,
    -274,   -50,  -274,   -56,   -34,  -274,  -274,   272,  -274,  -274,
    -274,  -274,  -274,    76,   -45,    50,    33,   -19,     3,  -274,
     -39,  -249,   178,  -274,   260,   -71,  -205,  -135,  -274,   -75,
    -274,  -274,  -274,  -274,  -274,  -274,   -25,   319,  -173,  -274,
    -274,  -274,  -274,  -274,   408,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,   174
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    97,    98,    99,   310,   100,   101,   102,   299,   300,
     301,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   216,   117,   144,    18,   135,
      36,    37,    20,    21,    22,    23,   158,   159,   160,   161,
     162,   163,   270,   271,   164,    24,   146,    26,    27,    33,
     337,   137,   138,   139,   171,   338,   251,   149,   258,   120,
     121,   122,   197,   123,   195,   124,   125,   126,   127,   128,
     129,   290,   130,    28,    29,   131,    30,   132,   358,   359,
     404,   174,   175
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,   181,   156,   142,   143,   145,    32,   136,    48,   289,
     156,   118,   257,    57,   350,     3,   172,     3,   167,   168,
     192,   170,   178,     3,   157,   169,   375,   246,   378,   142,
     143,   247,   193,    25,   217,    19,    52,    34,     3,   190,
     187,     4,   172,   142,   341,   360,   246,     3,     4,   295,
     247,   242,    38,    31,   148,    39,    40,   142,    56,    43,
     235,    25,    41,    19,   250,   254,   274,   362,    42,     4,
       3,   341,   255,   238,   238,    35,    17,    44,     4,   119,
     363,   236,   365,    51,   268,    53,   346,   238,    44,   238,
      17,   347,    14,   173,    54,    17,    55,    17,   244,   277,
     156,   275,   156,   414,   285,   247,   296,   401,   165,   156,
     384,   264,   413,   238,   269,   238,   165,   367,    17,   173,
     273,   368,   361,   307,   157,   169,    58,    17,   238,   199,
     200,   428,   176,   156,   238,   282,   283,   297,   249,   286,
     177,   298,   201,   382,   170,   148,   179,   293,   169,   288,
     383,   315,   316,   317,   397,   237,   202,   238,   180,     2,
     203,   253,   312,   183,   412,   204,   119,   292,   248,   238,
     242,   383,   182,   276,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   302,   184,   305,   333,   340,   272,     1,     2,
     311,    46,     3,   142,   143,    47,   165,   188,   165,   364,
     185,   354,   394,   194,   314,   165,   351,   119,   352,     5,
       6,     7,     8,     9,    10,    11,   198,   356,   370,    44,
      48,    14,   196,     4,   142,   422,   334,   221,   222,   165,
     231,   425,   253,   427,     1,     2,   232,   353,   238,   249,
     238,   142,   342,   233,   275,   357,   343,   374,   247,     5,
       6,     7,     8,     9,    10,    11,   218,   219,   220,    12,
      13,    14,    15,    16,   223,   224,   234,   297,   276,    34,
     133,   298,    17,   229,   230,   297,   239,   405,   406,   377,
     407,   253,   392,   411,   252,   311,   385,   238,   240,   142,
     143,   379,   269,   390,   381,     5,     6,     7,     8,     9,
      10,    11,   318,   319,   256,    12,    13,    14,   225,   226,
     227,   228,   320,   321,   396,   408,   410,    56,   134,   322,
     323,   324,   325,   402,   426,   259,   415,   326,   327,   260,
     261,   142,   417,   262,   263,   148,   265,   423,   278,   429,
     279,   280,   431,     1,     2,    59,    60,    61,   281,   284,
     287,    62,    63,   291,   303,   306,   308,   313,   345,    64,
     420,   348,   421,   173,   366,    65,   369,   386,   387,   403,
     399,   416,   424,   388,   395,   418,   361,   419,    66,   373,
      44,    67,    68,   430,    69,   376,   329,   328,   371,    70,
      71,   331,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     5,     6,     7,     8,     9,    10,
      11,    84,    85,    86,    12,    13,    14,   332,   398,   330,
     267,   344,    87,    88,    89,    90,    50,    91,    92,    93,
      94,    95,    96,     1,     2,    59,    60,    61,   205,   294,
     245,    62,    63,   355,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,    65,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,     0,     0,    66,     0,
      44,   243,    68,     0,    69,     0,     0,     0,     0,    70,
      71,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     5,     6,     7,     8,     9,    10,
      11,    84,    85,    86,    12,    13,    14,     0,     0,     1,
       2,     0,    87,    88,    89,    90,     0,    91,    92,    93,
      94,    95,    96,     1,     2,    59,    60,    61,     0,     0,
       0,    62,    63,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
       2,     0,    68,     0,    69,     0,     0,     0,     0,    70,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
      12,    13,    14,    83,     5,     6,     7,     8,     9,    10,
      11,    84,    85,    86,    12,    13,    14,     0,     2,    59,
      60,    61,    87,    88,     0,    62,    63,   141,    92,    93,
      94,    95,    96,    64,     0,     0,     0,     0,     0,    65,
       5,     6,     7,     8,     9,    10,    11,     0,     0,    49,
       0,     0,    66,     1,     2,     0,    68,     3,     0,     0,
       0,     0,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     5,     6,
       7,     8,     9,    10,    11,    84,    85,    86,     4,     0,
      14,     0,     0,     0,     0,     0,    87,    88,     0,     0,
       0,   141,    92,    93,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,    12,    13,    14,    15,    16,    59,
      60,    61,     0,     0,     0,    62,    63,    17,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,    44,   241,    68,     0,    69,     0,
       0,     0,     0,    70,    71,     0,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     0,     0,
       0,     0,     0,     0,     0,    84,    85,    86,     0,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    89,    90,
       0,    91,    92,    93,    94,    95,    96,    59,    60,    61,
       0,     0,     0,    62,    63,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,     0,    44,   335,    68,     0,    69,     0,     0,     0,
       0,    70,    71,     0,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     0,     0,     0,     0,
       0,     0,     0,    84,    85,    86,     0,     0,     0,     0,
       0,     0,     0,     0,    87,    88,    89,    90,     0,    91,
      92,    93,    94,    95,    96,    59,    60,    61,     0,     0,
       0,    62,    63,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
      44,     0,    68,     0,    69,     0,     0,     0,     0,    70,
      71,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,     0,     0,     0,     0,     0,     0,
       0,    84,    85,    86,     0,     0,     0,     0,     0,     0,
       0,     0,    87,    88,    89,    90,     0,    91,    92,    93,
      94,    95,    96,    59,    60,    61,     0,     0,     0,    62,
      63,     0,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,   147,   393,
      68,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    83,     0,     0,    62,    63,     0,     0,     0,    84,
      85,    86,    64,     0,     0,     0,     0,     0,    65,     0,
      87,    88,     0,     0,     0,   141,    92,    93,    94,    95,
      96,    66,     0,     0,     0,    68,   140,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    60,    61,    83,     0,     0,    62,
      63,     0,     0,     0,    84,    85,    86,    64,     0,     0,
       0,     0,     0,    65,     0,    87,    88,     0,     0,     0,
     141,    92,    93,    94,    95,    96,    66,     0,   147,     0,
      68,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    83,     0,     0,    62,    63,     0,     0,     0,    84,
      85,    86,    64,     0,     0,     0,     0,     0,    65,     0,
      87,    88,     0,     0,     0,   141,    92,    93,    94,    95,
      96,    66,     0,     0,     0,    68,     0,   186,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    60,    61,    83,     0,     0,    62,
      63,     0,     0,     0,    84,    85,    86,    64,     0,     0,
       0,     0,     0,    65,     0,    87,    88,     0,     0,     0,
     141,    92,    93,    94,    95,    96,    66,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    83,     0,     0,    62,    63,     0,     0,     0,    84,
      85,    86,    64,     0,     0,     0,     0,     0,    65,     0,
      87,    88,     0,     0,   304,   141,    92,    93,    94,    95,
      96,    66,   309,     0,     0,    68,     0,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    60,    61,    83,     0,     0,    62,
      63,     0,     0,     0,    84,    85,    86,    64,     0,     0,
       0,     0,     0,    65,     0,    87,    88,     0,     0,     0,
     141,    92,    93,    94,    95,    96,    66,     0,     0,     0,
      68,   339,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    83,     0,     0,    62,    63,     0,     0,     0,    84,
      85,    86,    64,     0,     0,     0,     0,     0,    65,     0,
      87,    88,     0,     0,     0,   141,    92,    93,    94,    95,
      96,    66,     0,     0,     0,    68,     0,    69,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    60,    61,    83,     0,     0,    62,
      63,     0,     0,     0,    84,    85,    86,    64,     0,     0,
       0,     0,     0,    65,     0,    87,    88,     0,     0,     0,
     141,    92,    93,    94,    95,    96,    66,   372,     0,     0,
      68,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    83,     0,     0,    62,    63,     0,     0,     0,    84,
      85,    86,    64,     0,     0,     0,     0,     0,    65,     0,
      87,    88,     0,     0,     0,   141,    92,    93,    94,    95,
      96,    66,     0,     0,     0,    68,     0,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    60,    61,    83,     0,     0,    62,
      63,     0,     0,     0,    84,    85,    86,    64,     0,     0,
       0,     0,     0,    65,     0,    87,    88,     0,     0,   380,
     141,    92,    93,    94,    95,    96,    66,     0,     0,     0,
      68,   391,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    83,     0,     0,    62,    63,     0,     0,     0,    84,
      85,    86,    64,     0,     0,     0,     0,     0,    65,     0,
      87,    88,     0,     0,     0,   141,    92,    93,    94,    95,
      96,    66,   409,     0,     0,    68,     0,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    60,    61,    83,     0,     0,    62,
      63,     0,     0,     0,    84,    85,    86,    64,     0,     0,
       0,     0,     0,    65,     0,    87,    88,     0,     0,     0,
     141,    92,    93,    94,    95,    96,   166,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    83,     0,     0,    62,    63,     0,     0,     0,    84,
      85,    86,    64,     0,     0,     0,     0,     0,    65,     0,
      87,    88,     0,     0,     0,   141,    92,    93,    94,    95,
      96,    66,     0,     0,     0,    68,     0,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    59,    60,    61,    83,     0,     0,    62,
      63,     0,     0,     0,    84,    85,    86,    64,     0,     0,
       0,     0,     0,    65,     0,    87,    88,     0,     0,     0,
     141,    92,    93,    94,    95,    96,   189,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,    70,     1,     2,
       0,     0,     0,     0,     0,     0,     0,     0,    59,    60,
      61,    83,     0,     0,    62,    63,     0,     0,     0,    84,
      85,    86,    64,     0,     0,     0,     0,     0,    65,     0,
      87,    88,     0,     0,   349,   141,    92,    93,    94,    95,
      96,    66,     1,     2,     0,   191,     3,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,    83,     0,     0,    12,
      13,    14,     0,     0,    84,    85,    86,   246,   336,     2,
       0,   247,     0,     0,     0,    87,    88,     0,     0,     0,
     141,    92,    93,    94,    95,    96,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,    12,    13,    14,   266,     0,     2,   150,
       0,     0,     0,     0,   151,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,     1,
       2,    14,    15,    16,   152,   153,   154,     0,   150,     0,
       0,     0,   155,   151,     1,     2,     0,     0,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,   389,     0,     1,     2,     0,
      14,    15,    16,   152,   153,   154,     0,     0,     0,   275,
     336,   155,     0,   247,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
      12,    13,    14,   400,     0,     5,     6,     7,     8,     9,
      10,    11,     0,     0,     0,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,     0,     0,     0,    12,    13,
      14
};

static const yytype_int16 yycheck[] =
{
      25,    76,    58,    47,    47,    55,     3,    46,    27,   182,
      66,    44,   147,    38,   263,     8,    11,     8,    62,    63,
      87,    66,    73,     8,    58,    66,   299,    39,   301,    73,
      73,    43,    88,     0,   101,     0,    33,     4,     8,    83,
      81,    39,    11,    87,   249,    11,    39,     8,    39,    44,
      43,   126,    19,     3,    56,    20,    21,   101,    11,    24,
      28,    28,    45,    28,   135,    40,    40,    40,    88,    39,
       8,   276,    47,    47,    47,    45,    88,    41,    39,    44,
      40,    49,    40,    33,    45,    40,    42,    47,    41,    47,
      88,    47,    77,    88,    45,    88,    47,    88,   131,   170,
     156,    39,   158,   376,   179,    43,     8,   356,    58,   165,
      44,   156,    44,    47,   164,    47,    66,   290,    88,    88,
     165,    40,    88,   198,   158,   166,    41,    88,    47,    12,
      13,    44,    39,   189,    47,   176,   177,    39,   135,   180,
      39,    43,    25,    40,   189,   147,    46,   188,   189,   182,
      47,   218,   219,   220,    40,    45,    39,    47,    39,     5,
      43,    47,   203,    88,    40,    48,   131,    45,   135,    47,
     245,    47,    39,   170,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   194,    45,   196,   236,   247,   164,     4,     5,
     202,    39,     8,   247,   247,    43,   156,    39,   158,   284,
      45,   278,   347,    24,   216,   165,    45,   182,    47,    65,
      66,    67,    68,    69,    70,    71,    46,    39,   295,    41,
     249,    77,    23,    39,   278,    40,   238,     6,     7,   189,
      20,    40,    47,    40,     4,     5,    22,   272,    47,   246,
      47,   295,    39,    21,    39,   280,    43,   298,    43,    65,
      66,    67,    68,    69,    70,    71,     8,     9,    10,    75,
      76,    77,    78,    79,    23,    24,    27,    39,   275,   246,
      40,    43,    88,    14,    15,    39,    45,   362,   363,    43,
     365,    47,   343,   368,    40,   297,    46,    47,    45,   343,
     343,   303,   352,   342,   306,    65,    66,    67,    68,    69,
      70,    71,   221,   222,    44,    75,    76,    77,    16,    17,
      18,    19,   223,   224,   349,   366,   367,    11,    88,   225,
     226,   227,   228,   358,   409,    88,   377,   229,   230,    46,
      46,   385,   385,    46,    39,   347,    45,   403,    40,   424,
      47,    44,   427,     4,     5,     6,     7,     8,    47,    46,
      56,    12,    13,    45,    24,    23,    88,    88,    88,    20,
     395,    39,   397,    88,    39,    26,    40,    40,    40,    25,
      47,   383,    52,    44,    40,    40,    88,    44,    39,   297,
      41,    42,    43,    45,    45,   299,   232,   231,   296,    50,
      51,   234,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,   235,   352,   233,
     158,   253,    83,    84,    85,    86,    28,    88,    89,    90,
      91,    92,    93,     4,     5,     6,     7,     8,    11,   189,
     131,    12,    13,   279,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    39,    -1,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,    -1,     4,
       5,    -1,    83,    84,    85,    86,    -1,    88,    89,    90,
      91,    92,    93,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
       5,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      65,    66,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    76,    77,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,     5,     6,
       7,     8,    83,    84,    -1,    12,    13,    88,    89,    90,
      91,    92,    93,    20,    -1,    -1,    -1,    -1,    -1,    26,
      65,    66,    67,    68,    69,    70,    71,    -1,    -1,     0,
      -1,    -1,    39,     4,     5,    -1,    43,     8,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    39,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    83,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    -1,    -1,    -1,    75,    76,    77,    78,    79,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    88,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    41,    42,    43,    -1,    45,    -1,
      -1,    -1,    -1,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,    86,
      -1,    88,    89,    90,    91,    92,    93,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    84,    85,    86,    -1,    88,
      89,    90,    91,    92,    93,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      51,    -1,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    85,    86,    -1,    88,    89,    90,
      91,    92,    93,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    39,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,
      13,    -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    39,    -1,    41,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    39,    -1,    -1,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,
      13,    -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    87,    88,    89,    90,    91,    92,
      93,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,
      13,    -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    39,    -1,    -1,    -1,
      43,    44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    39,    -1,    -1,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,
      13,    -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    39,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,
      13,    -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    83,    84,    -1,    -1,    87,
      88,    89,    90,    91,    92,    93,    39,    -1,    -1,    -1,
      43,    44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,
      13,    -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,
      13,    -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,     4,     5,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,
       8,    64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,
      73,    74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      83,    84,    -1,    -1,    40,    88,    89,    90,    91,    92,
      93,    39,     4,     5,    -1,    43,     8,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    64,    -1,    -1,    75,
      76,    77,    -1,    -1,    72,    73,    74,    39,    40,     5,
      -1,    43,    -1,    -1,    -1,    83,    84,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    75,    76,    77,    42,    -1,     5,    45,
      -1,    -1,    -1,    -1,    50,    -1,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    -1,    -1,    -1,     4,
       5,    77,    78,    79,    80,    81,    82,    -1,    45,    -1,
      -1,    -1,    88,    50,     4,     5,    -1,    -1,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    40,    -1,     4,     5,    -1,
      77,    78,    79,    80,    81,    82,    -1,    -1,    -1,    39,
      40,    88,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    76,    77,    40,    -1,    65,    66,    67,    68,    69,
      70,    71,    -1,    -1,    -1,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    -1,    -1,    -1,    75,    76,
      77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     8,    39,    65,    66,    67,    68,    69,
      70,    71,    75,    76,    77,    78,    79,    88,   123,   124,
     127,   128,   129,   130,   140,   141,   142,   143,   168,   169,
     171,   140,   143,   144,   141,    45,   125,   126,   141,   124,
     124,    45,    88,   124,    41,   161,    39,    43,   142,     0,
     169,   140,   143,    40,    45,    47,    11,   161,    41,     6,
       7,     8,    12,    13,    20,    26,    39,    42,    43,    45,
      50,    51,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    72,    73,    74,    83,    84,    85,
      86,    88,    89,    90,    91,    92,    93,    96,    97,    98,
     100,   101,   102,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   121,   123,   124,
     154,   155,   156,   158,   160,   161,   162,   163,   164,   165,
     167,   170,   172,    40,    88,   124,   145,   146,   147,   148,
      44,    88,   100,   118,   122,   126,   141,    41,   119,   152,
      45,    50,    80,    81,    82,    88,   128,   129,   131,   132,
     133,   134,   135,   136,   139,   140,    39,   100,   100,   121,
     139,   149,    11,    88,   176,   177,    39,    39,   122,    46,
      39,   154,    39,    88,    45,    45,    45,   121,    39,    39,
     100,    43,   107,   128,    24,   159,    23,   157,    46,    12,
      13,    25,    39,    43,    48,    11,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   120,   107,     8,     9,
      10,     6,     7,    23,    24,    16,    17,    18,    19,    14,
      15,    20,    22,    21,    27,    28,    49,    45,    47,    45,
      45,    42,   154,    42,   123,   162,    39,    43,   141,   143,
     150,   151,    40,    47,    40,    47,    44,   152,   153,    88,
      46,    46,    46,    39,   139,    45,    42,   132,    45,   126,
     137,   138,   141,   139,    40,    39,   143,   150,    40,    47,
      44,    47,   121,   121,    46,   154,   121,    56,   123,   163,
     166,    45,    45,   121,   149,    44,     8,    39,    43,   103,
     104,   105,   119,    24,    87,   119,    23,   154,    88,    40,
      99,   119,   121,    88,   119,   107,   107,   107,   108,   108,
     109,   109,   110,   110,   110,   110,   111,   111,   112,   113,
     114,   115,   116,   121,   119,    42,    40,   145,   150,    44,
     122,   151,    39,    43,   147,    88,    42,    47,    39,    40,
     146,    45,    47,   161,   107,   177,    39,   161,   173,   174,
      11,    88,    40,    40,   154,    40,    39,   163,    40,    40,
     107,   103,    40,    99,   121,   104,   105,    43,   104,   119,
      87,   119,    40,    47,    44,    46,    40,    40,    44,    40,
     145,    44,   122,    42,   152,    40,   161,    40,   138,    47,
      40,   146,   161,    25,   175,   154,   154,   154,   121,    40,
     121,   154,    40,    44,   104,   121,   119,   118,    40,    44,
     161,   161,    40,   128,    52,    40,   154,    40,    44,   154,
      45,   154
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    97,    97,    97,    98,    98,    98,    98,    98,    98,
      98,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   101,   101,   101,   101,   101,   102,   102,
     102,   102,   102,   102,   102,   102,   103,   103,   104,   104,
     105,   105,   106,   106,   107,   107,   108,   108,   108,   108,
     109,   109,   109,   110,   110,   110,   111,   111,   111,   111,
     111,   112,   112,   112,   113,   113,   114,   114,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   119,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   122,   123,   123,   124,   124,   124,   124,   124,   124,
     125,   125,   126,   126,   127,   127,   127,   128,   128,   128,
     128,   128,   128,   128,   128,   129,   129,   130,   130,   131,
     131,   132,   132,   133,   133,   133,   134,   134,   134,   134,
     134,   134,   134,   135,   135,   136,   137,   137,   138,   139,
     139,   139,   139,   140,   141,   141,   142,   142,   142,   142,
     142,   142,   142,   143,   143,   143,   143,   144,   144,   145,
     146,   146,   147,   147,   147,   148,   148,   149,   149,   150,
     150,   150,   151,   151,   151,   151,   151,   151,   151,   151,
     151,   152,   152,   152,   153,   153,   154,   154,   154,   154,
     154,   154,   154,   155,   155,   156,   157,   157,   157,   157,
     158,   159,   159,   160,   160,   160,   161,   161,   161,   161,
     162,   162,   163,   163,   164,   164,   164,   165,   165,   165,
     165,   165,   166,   166,   167,   167,   167,   167,   167,   168,
     168,   169,   169,   169,   170,   170,   171,   171,   172,   172,
     173,   174,   174,   175,   175,   176,   176,   176,   176,   176,
     177,   177
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     4,
       4,     4,     3,     3,     3,     2,     2,     1,     2,     3,
       3,     4,     4,     2,     1,     4,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     3,     1,     2,     1,     2,     1,     2,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     2,     1,     1,     1,
       2,     1,     1,     2,     2,     2,     3,     2,     3,     2,
       1,     1,     1,     5,     4,     5,     1,     3,     1,     2,
       1,     2,     1,     1,     2,     1,     1,     3,     4,     3,
       4,     4,     3,     1,     2,     2,     3,     1,     2,     1,
       1,     3,     2,     2,     1,     1,     3,     1,     2,     1,
       1,     2,     3,     2,     3,     3,     4,     2,     3,     3,
       4,     1,     3,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     3,     3,
       2,     2,     3,     3,     4,     3,     2,     3,     3,     4,
       1,     2,     1,     2,     5,     7,     5,     5,     5,     7,
       6,     7,     1,     1,     3,     2,     2,     2,     3,     1,
       2,     1,     2,     1,     1,     2,     3,     2,     5,     4,
       2,     2,     3,     0,     2,     0,     1,     1,     3,     3,
       1,     3
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

#line 1916 "cpp.tab.c"

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

#line 570 "cpp.y"


int main(){
    return 0;
}
