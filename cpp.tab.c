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
	

#line 82 "cpp.tab.c"

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
  YYSYMBOL_DECIMAL_LITERAL = 90,           /* DECIMAL_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 91,            /* DOUBLE_LITERAL  */
  YYSYMBOL_EXPONENT_LITERAL = 92,          /* EXPONENT_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 93,         /* CHARACTER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 94,            /* STRING_LITERAL  */
  YYSYMBOL_LOWER_THAN_ELSE = 95,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 96,                  /* $accept  */
  YYSYMBOL_primary_expression = 97,        /* primary_expression  */
  YYSYMBOL_constant = 98,                  /* constant  */
  YYSYMBOL_postfix_expression = 99,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 100, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 101,         /* unary_expression  */
  YYSYMBOL_unary_operator = 102,           /* unary_operator  */
  YYSYMBOL_new_expression = 103,           /* new_expression  */
  YYSYMBOL_pointer_opt = 104,              /* pointer_opt  */
  YYSYMBOL_new_declarator = 105,           /* new_declarator  */
  YYSYMBOL_scalar_new_init = 106,          /* scalar_new_init  */
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
  YYSYMBOL_init_declarator = 127,          /* init_declarator  */
  YYSYMBOL_static_opt = 128,               /* static_opt  */
  YYSYMBOL_big_data_type = 129,            /* big_data_type  */
  YYSYMBOL_small_data_type = 130,          /* small_data_type  */
  YYSYMBOL_basic_data_type = 131,          /* basic_data_type  */
  YYSYMBOL_struct_or_class_specifier = 132, /* struct_or_class_specifier  */
  YYSYMBOL_struct_or_class = 133,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 134, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 135,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 136,   /* access_specifier_label  */
  YYSYMBOL_member_declaration = 137,       /* member_declaration  */
  YYSYMBOL_constructor_definition = 138,   /* constructor_definition  */
  YYSYMBOL_destructor_definition = 139,    /* destructor_definition  */
  YYSYMBOL_struct_declarator_list = 140,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 141,        /* struct_declarator  */
  YYSYMBOL_declarator = 142,               /* declarator  */
  YYSYMBOL_direct_declarator = 143,        /* direct_declarator  */
  YYSYMBOL_pointer = 144,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 145,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 146,      /* parameter_type_list  */
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
  YYSYMBOL_expression_statement = 164,     /* expression_statement  */
  YYSYMBOL_selection_statement = 165,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 166,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 167,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 168,           /* jump_statement  */
  YYSYMBOL_translation_unit = 169,         /* translation_unit  */
  YYSYMBOL_external_declaration = 170,     /* external_declaration  */
  YYSYMBOL_declaration_list = 171,         /* declaration_list  */
  YYSYMBOL_function_definition = 172,      /* function_definition  */
  YYSYMBOL_lambda_expression = 173,        /* lambda_expression  */
  YYSYMBOL_lambda_declarator = 174,        /* lambda_declarator  */
  YYSYMBOL_lambda_parameter_clause = 175,  /* lambda_parameter_clause  */
  YYSYMBOL_trailing_return_opt = 176,      /* trailing_return_opt  */
  YYSYMBOL_lambda_capture_clause = 177,    /* lambda_capture_clause  */
  YYSYMBOL_capture_list = 178              /* capture_list  */
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
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1833

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  249
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  423

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   350


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
      95
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    64,    64,    65,    66,    67,    71,    72,    73,    74,
      75,    76,    77,    78,    82,    83,    84,    85,    86,    87,
      88,    89,    93,    94,    98,    99,   100,   101,   102,   103,
     104,   105,   109,   110,   111,   112,   113,   114,   118,   119,
     120,   121,   125,   126,   130,   131,   135,   136,   140,   141,
     145,   146,   150,   151,   152,   153,   157,   158,   159,   163,
     164,   165,   169,   170,   171,   172,   173,   177,   178,   179,
     183,   184,   188,   189,   193,   194,   198,   199,   203,   204,
     208,   209,   213,   214,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   232,   233,   237,   241,   242,
     246,   247,   251,   252,   256,   257,   261,   262,   266,   270,
     274,   275,   276,   277,   278,   279,   280,   281,   285,   286,
     290,   291,   295,   296,   300,   301,   305,   306,   307,   311,
     312,   313,   314,   315,   316,   317,   321,   322,   326,   330,
     331,   335,   339,   340,   344,   345,   346,   347,   348,   349,
     350,   354,   355,   356,   357,   361,   362,   366,   370,   371,
     375,   376,   377,   381,   382,   386,   387,   391,   392,   393,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   409,
     410,   411,   415,   416,   420,   421,   422,   423,   424,   425,
     426,   430,   431,   435,   439,   440,   441,   442,   446,   450,
     451,   455,   456,   457,   461,   462,   463,   464,   468,   469,
     473,   474,   478,   479,   480,   484,   485,   486,   487,   488,
     492,   493,   497,   498,   499,   500,   501,   505,   506,   510,
     511,   512,   516,   517,   521,   522,   526,   527,   531,   535,
     536,   540,   541,   545,   546,   547,   548,   549,   553,   554
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
  "CIN", "COUT", "ENDL", "IDENTIFIER", "DECIMAL_LITERAL", "DOUBLE_LITERAL",
  "EXPONENT_LITERAL", "CHARACTER_LITERAL", "STRING_LITERAL",
  "LOWER_THAN_ELSE", "$accept", "primary_expression", "constant",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "new_expression", "pointer_opt", "new_declarator",
  "scalar_new_init", "delete_expression", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "static_opt", "big_data_type", "small_data_type", "basic_data_type",
  "struct_or_class_specifier", "struct_or_class",
  "struct_or_class_member_list", "struct_or_class_member",
  "access_specifier_label", "member_declaration", "constructor_definition",
  "destructor_definition", "struct_declarator_list", "struct_declarator",
  "declarator", "direct_declarator", "pointer", "type_qualifier_list",
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

#define YYPACT_NINF (-245)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,    32,    40,  -245,   -52,  -245,  -245,  -245,  -245,    50,
     243,  -245,    -1,    24,    60,   122,   -15,    43,  -245,  -245,
    -245,  -245,    38,   111,  -245,  -245,    36,  -245,    34,  -245,
    -245,  -245,  -245,  -245,  -245,  -245,  -245,  -245,   151,  -245,
     128,   342,  -245,    98,   955,   122,  -245,  -245,  -245,  -245,
    -245,  -245,    40,  1011,  -245,   151,  -245,   519,  -245,  -245,
    -245,  1571,  1571,  -245,  -245,   843,  -245,    23,  -245,  -245,
     125,   207,  1627,   189,   210,   698,   249,   174,   247,   251,
    1067,   260,  1683,  -245,  -245,  -245,  1739,   -52,   302,   312,
     291,  -245,  -245,  -245,  -245,  -245,  -245,  -245,   219,   287,
    1627,  -245,  -245,  -245,    83,    54,   175,   257,   224,   318,
     317,   320,   316,    41,  -245,  -245,   221,  -245,    50,  -245,
    -245,   299,   301,  -245,  -245,   520,  -245,  -245,  -245,  -245,
     431,  -245,  -245,  -245,    20,   307,   304,  -245,     2,  -245,
    -245,  -245,  -245,   308,  -245,   345,  1011,  -245,  -245,  -245,
    -245,   264,   311,   313,   314,   319,    63,   321,   764,  -245,
    -245,  -245,  -245,  -245,  1627,  -245,  -245,    37,    25,   323,
    -245,   322,  -245,   326,   325,  1627,  1627,   315,   698,  1627,
     310,   787,   328,  -245,  -245,  -245,   236,  1627,   843,  -245,
      28,  -245,   154,  1627,   340,  1123,   352,   698,  -245,  -245,
     276,  1179,  1627,   288,  -245,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,  1627,  -245,  1627,  1627,  1627,
    1627,  1627,  1627,  1627,  1627,  1627,  1627,  1627,  1627,  1627,
    1627,  1627,  1627,  1627,  1627,  1627,  -245,  1627,  -245,  -245,
    -245,  -245,  -245,  -245,   609,   117,  1235,  -245,    11,  -245,
     208,  -245,   193,  -245,   289,  -245,  -245,    31,   341,  -245,
    -245,  -245,    56,  -245,  -245,   244,  -245,    34,  -245,  -245,
    -245,  -245,   123,   217,  -245,  1627,   290,   254,    15,    96,
     102,   698,  -245,   108,   343,  -245,  -245,  1291,  -245,  -245,
     130,   346,  1627,  1347,  1627,   222,  -245,  -245,  1627,  -245,
    -245,  1403,  -245,  -245,  -245,   143,  -245,    93,  -245,  -245,
    -245,  -245,  -245,    83,    83,    54,    54,   175,   175,   175,
     175,   257,   257,   224,   318,   317,   320,   316,   258,  -245,
    -245,  -245,   348,   349,  -245,   347,   208,    95,  1459,  -245,
    -245,  -245,   899,   350,    60,   156,  -245,    40,  -245,  -245,
     361,   114,  -245,    60,   368,  -245,  -245,   698,   698,  -245,
     698,  1627,  1515,   698,  -245,  -245,  -245,   162,   135,  1627,
    -245,  -245,  -245,  -245,  -245,  1627,  -245,  1627,  -245,  -245,
    -245,  -245,   369,  -245,   366,  -245,  -245,    60,  -245,    60,
    -245,   324,  -245,   190,  -245,   193,  -245,   358,  -245,  -245,
     194,   698,   196,  -245,  -245,  -245,   163,  -245,  -245,  -245,
    -245,  -245,  -245,  -245,  -245,   698,   367,  -245,   698,  -245,
    -245,  -245,  -245
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     106,   151,     0,   107,   106,   121,   120,   144,   231,     0,
       0,   100,     0,     0,     0,   142,     0,   106,   227,   229,
     155,   153,   152,     0,   101,    98,     0,   102,   104,   117,
     110,   112,   114,   111,   115,   116,   113,   108,    42,   230,
     119,   106,   235,   106,     0,   143,     1,   228,   156,   154,
     145,    99,     0,     0,   234,    42,   109,   106,    34,    35,
      33,     0,     0,    32,    37,   106,   204,     0,   210,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    12,    13,    11,     0,   106,     0,     0,
       2,     6,    10,     9,     7,     8,    14,     3,    24,    50,
       0,    31,    30,    52,    56,    59,    62,    67,    70,    72,
      74,    76,    78,    80,    82,    95,     0,   232,     0,   208,
     190,     0,     0,   184,   185,     0,   186,   187,   188,   189,
     106,     5,   150,   163,   162,     0,   157,   158,     0,   147,
       2,    50,    97,     0,   103,   104,     0,   179,   105,    43,
     133,     0,     0,     0,     0,     0,     0,     0,   106,   122,
     124,   125,   134,   135,     0,    25,    26,     0,   165,     0,
     243,   244,   248,     0,   245,     0,     0,     0,     0,     0,
       0,   106,     0,   223,   224,   225,     0,     0,   106,    28,
       0,    49,    41,     0,   198,     0,   193,     0,    20,    21,
       0,     0,     0,     0,    84,    88,    89,    85,    86,    87,
      92,    94,    93,    90,    91,     0,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   211,     0,   191,   192,
     205,   209,   206,   233,     0,   106,     0,   160,   167,   161,
     168,   148,   106,   149,     0,   146,   182,     0,     0,   126,
     127,   128,   106,   130,   141,     0,   139,   104,   132,   118,
     123,     4,   106,   167,   166,     0,     0,     0,     0,     0,
       0,     0,   203,     0,     0,   221,   220,     0,   222,   226,
       0,     0,     0,     0,     0,    39,    40,   199,     0,   195,
     194,     0,   201,    19,    16,     0,    22,     0,    18,    83,
      53,    54,    55,    57,    58,    60,    61,    64,    63,    65,
      66,    68,    69,    71,    73,    75,    77,    79,     0,    96,
     207,   175,     0,     0,   171,     0,   169,   106,     0,   159,
     164,   180,     0,     0,     0,     0,   129,     0,   131,    51,
     247,   106,   237,     0,   241,   246,   249,     0,     0,   202,
       0,     0,     0,     0,    29,    48,    46,     0,     0,     0,
      38,   200,   196,   197,    17,     0,    15,     0,   176,   170,
     172,   177,     0,   173,     0,   181,   183,     0,   137,     0,
     140,     0,   239,     0,   236,   106,   238,   212,   214,   215,
       0,     0,     0,   216,    47,    44,     0,    23,    81,   178,
     174,   138,   136,   240,   242,     0,     0,   218,     0,    45,
     213,   217,   219
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -245,  -245,  -245,  -245,   121,    -6,  -245,  -245,   363,  -245,
     126,  -245,   -33,    86,   107,    53,   105,   192,   199,   191,
     209,   206,  -245,   -41,   -48,  -245,   -61,   -66,   -31,     0,
    -245,   -45,  -245,    19,  -245,  -245,   -30,  -245,  -245,   266,
    -245,  -245,  -245,  -245,  -245,    78,    12,     4,    10,  -245,
     -34,  -244,   195,  -245,  -166,   -98,  -211,  -138,  -245,   -73,
    -245,  -245,  -245,  -245,  -245,  -245,   -13,   329,  -168,  -245,
    -245,  -245,  -245,  -245,   424,  -245,  -245,  -245,  -245,  -245,
    -245,  -245,   169
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    96,    97,    98,   305,    99,   100,   101,    56,   295,
     296,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   215,   116,   143,     8,   134,
      26,    27,    10,    11,    37,    38,    12,    13,   158,   159,
     160,   161,   162,   163,   265,   266,   145,    15,    16,    22,
     332,   136,   137,   138,   169,   333,   250,   148,   257,   119,
     120,   121,   196,   122,   194,   123,   124,   125,   126,   127,
     128,   287,   129,    17,    18,   130,    19,   131,   353,   354,
     396,   173,   174
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       9,    42,   180,   142,   167,   147,   177,   144,   256,   135,
     117,    21,    14,   286,    23,    54,     1,     9,   345,   186,
      45,    28,   291,    24,     2,     3,   355,   157,     1,    14,
     170,   142,    49,     1,   171,   170,   249,   336,   141,   171,
       1,   118,   253,    46,    39,    53,     1,     2,     1,   254,
     245,     1,   241,   191,   246,   165,   166,   156,     1,   245,
     220,   221,   336,   246,   272,   168,   141,   216,   246,   234,
     274,     1,   292,   341,     7,    41,   189,   271,   342,     2,
     141,    51,     2,    52,   237,     3,     4,     5,     6,     2,
     235,   217,   218,   219,   141,    25,   344,     7,   147,   243,
       7,    41,     2,   167,   356,   282,   192,   393,   263,     7,
      20,   264,   172,    40,   279,   280,    48,   172,   283,   362,
       3,     4,     5,     6,   302,     1,   290,   167,   157,     7,
     118,     1,     7,     3,     4,   381,   357,   376,   132,     7,
     237,   307,   358,   237,   248,   297,   247,   300,   360,   237,
     285,    50,     7,   306,   392,   237,   245,   331,   156,    55,
     246,    43,   272,   331,   175,    44,   246,   309,   267,    57,
     363,   241,     3,     4,   328,     3,     4,   237,   273,   405,
     335,   118,   237,   374,   310,   311,   312,   133,   168,   329,
     375,     3,     4,   293,     3,     4,   389,   294,   222,   223,
       3,     4,   404,   252,   386,   142,     7,   419,   359,   375,
     237,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   414,
     413,   198,   199,   368,   416,   178,   418,   252,   228,   229,
     141,   237,   349,   237,   200,   306,   176,   337,    29,   179,
     371,   338,    45,   373,   348,   248,   272,    23,   201,   365,
     246,   293,   202,   182,   352,   369,   236,   203,   237,   141,
       3,     4,   384,   224,   225,   226,   227,   317,   318,   319,
     320,   289,   273,   237,   397,   398,   141,   399,   181,   346,
     403,   347,   183,   351,   147,    41,   184,   142,   204,   187,
     400,   402,   264,   382,   377,   237,   313,   314,   406,    30,
      31,    32,    33,    34,    35,    36,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   193,   407,   417,   315,
     316,   388,   141,   321,   322,   195,   408,   197,   230,   231,
     394,   232,   420,   233,   238,   422,   239,   251,    58,    59,
      60,   252,   255,   258,    61,    62,    53,   259,   262,   260,
     261,   281,    63,   275,   298,   303,   268,   284,    64,   276,
     277,   141,   278,   288,   411,   301,   412,   308,   340,   172,
     343,    65,   361,    41,    66,    67,   364,    68,   378,   379,
     387,   380,    69,   395,    70,   168,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,   391,   409,
     410,   415,   421,   356,   367,    83,    84,    85,   149,     3,
       4,   370,   323,   325,   270,   390,    86,    87,    88,    89,
     324,    90,    91,    92,    93,    94,    95,    58,    59,    60,
     327,    47,   326,    61,    62,   350,     0,   339,     0,     0,
       0,    63,     0,     0,     0,     0,     0,    64,     0,   244,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,     0,    41,   242,    67,     0,    68,     0,     0,     0,
       0,    69,     0,    70,     0,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     0,     0,     0,
       0,     0,     0,     0,    83,    84,    85,     0,     3,     4,
       0,     0,     0,     0,     0,    86,    87,    88,    89,     0,
      90,    91,    92,    93,    94,    95,    58,    59,    60,     0,
       0,     0,    61,    62,     0,     0,     0,     0,     0,     0,
      63,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
       0,    41,   240,    67,   150,    68,     0,     0,     0,   151,
      69,     0,    70,     0,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,     0,     0,     0,
       0,     0,     0,    83,    84,    85,     3,     4,     5,     6,
     152,   153,   154,     0,    86,    87,    88,    89,   155,    90,
      91,    92,    93,    94,    95,    58,    59,    60,     0,     0,
       0,    61,    62,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    65,     0,
      41,   330,    67,     0,    68,     0,     0,     0,     0,    69,
       0,    70,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     0,     0,     0,     0,     0,
       0,     0,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,    86,    87,    88,    89,     0,    90,    91,
      92,    93,    94,    95,    58,    59,    60,     0,     0,     0,
      61,    62,     0,     0,     0,     0,     0,     0,    63,     0,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,     0,    41,
       0,    67,     0,    68,     0,     0,     0,     0,    69,     0,
      70,     0,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,     0,     0,     0,     0,
       0,    83,    84,    85,     0,     0,     0,     0,     0,     0,
       0,     0,    86,    87,    88,    89,     0,    90,    91,    92,
      93,    94,    95,    58,    59,    60,     0,     0,     0,    61,
      62,     0,     0,     0,     0,     0,   269,    63,     0,   150,
       0,     0,     0,    64,   151,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,     0,     0,     0,
      67,     0,    68,     0,     0,     0,     0,    69,     0,     0,
       0,     3,     4,     5,     6,   152,   153,   154,     0,    58,
      59,    60,    82,   155,     0,    61,    62,     0,     0,     0,
      83,    84,    85,    63,     3,     4,     0,     0,     0,    64,
       0,    86,    87,     0,     0,     0,   140,    91,    92,    93,
      94,    95,    65,     0,     0,     0,    67,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    82,     0,
       0,    61,    62,     0,     0,     0,    83,    84,    85,    63,
       3,     4,     0,     0,     0,    64,     0,    86,    87,     0,
       0,     0,   140,    91,    92,    93,    94,    95,    65,     0,
     146,   385,    67,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,    59,    60,    82,     0,     0,    61,    62,     0,
       0,     0,    83,    84,    85,    63,     0,     0,     0,     0,
       0,    64,     0,    86,    87,     0,     0,     0,   140,    91,
      92,    93,    94,    95,    65,     0,     0,     0,    67,   139,
       0,     0,     0,     0,     0,    69,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,    59,    60,
      82,     0,     0,    61,    62,     0,     0,     0,    83,    84,
      85,    63,     0,     0,     0,     0,     0,    64,     0,    86,
      87,     0,     0,     0,   140,    91,    92,    93,    94,    95,
      65,     0,   146,     0,    67,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    59,    60,    82,     0,     0,    61,
      62,     0,     0,     0,    83,    84,    85,    63,     0,     0,
       0,     0,     0,    64,     0,    86,    87,     0,     0,     0,
     140,    91,    92,    93,    94,    95,    65,     0,     0,     0,
      67,     0,   185,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      59,    60,    82,     0,     0,    61,    62,     0,     0,     0,
      83,    84,    85,    63,     0,     0,     0,     0,     0,    64,
       0,    86,    87,     0,     0,     0,   140,    91,    92,    93,
      94,    95,    65,     0,     0,     0,    67,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    82,     0,
       0,    61,    62,     0,     0,     0,    83,    84,    85,    63,
       0,     0,     0,     0,     0,    64,     0,    86,    87,     0,
       0,   299,   140,    91,    92,    93,    94,    95,    65,   304,
       0,     0,    67,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,    59,    60,    82,     0,     0,    61,    62,     0,
       0,     0,    83,    84,    85,    63,     0,     0,     0,     0,
       0,    64,     0,    86,    87,     0,     0,     0,   140,    91,
      92,    93,    94,    95,    65,     0,     0,     0,    67,   334,
       0,     0,     0,     0,     0,    69,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,    59,    60,
      82,     0,     0,    61,    62,     0,     0,     0,    83,    84,
      85,    63,     0,     0,     0,     0,     0,    64,     0,    86,
      87,     0,     0,     0,   140,    91,    92,    93,    94,    95,
      65,     0,     0,     0,    67,     0,    68,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    59,    60,    82,     0,     0,    61,
      62,     0,     0,     0,    83,    84,    85,    63,     0,     0,
       0,     0,     0,    64,     0,    86,    87,     0,     0,     0,
     140,    91,    92,    93,    94,    95,    65,   366,     0,     0,
      67,     0,     0,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      59,    60,    82,     0,     0,    61,    62,     0,     0,     0,
      83,    84,    85,    63,     0,     0,     0,     0,     0,    64,
       0,    86,    87,     0,     0,     0,   140,    91,    92,    93,
      94,    95,    65,     0,     0,     0,    67,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    82,     0,
       0,    61,    62,     0,     0,     0,    83,    84,    85,    63,
       0,     0,     0,     0,     0,    64,     0,    86,    87,     0,
       0,   372,   140,    91,    92,    93,    94,    95,    65,     0,
       0,     0,    67,   383,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,    59,    60,    82,     0,     0,    61,    62,     0,
       0,     0,    83,    84,    85,    63,     0,     0,     0,     0,
       0,    64,     0,    86,    87,     0,     0,     0,   140,    91,
      92,    93,    94,    95,    65,   401,     0,     0,    67,     0,
       0,     0,     0,     0,     0,    69,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,    59,    60,
      82,     0,     0,    61,    62,     0,     0,     0,    83,    84,
      85,    63,     0,     0,     0,     0,     0,    64,     0,    86,
      87,     0,     0,     0,   140,    91,    92,    93,    94,    95,
     164,     0,     0,     0,    67,     0,     0,     0,     0,     0,
       0,    69,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,    59,    60,    82,     0,     0,    61,
      62,     0,     0,     0,    83,    84,    85,    63,     0,     0,
       0,     0,     0,    64,     0,    86,    87,     0,     0,     0,
     140,    91,    92,    93,    94,    95,    65,     0,     0,     0,
      67,     0,     0,     0,     0,     0,     0,    69,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
      59,    60,    82,     0,     0,    61,    62,     0,     0,     0,
      83,    84,    85,    63,     0,     0,     0,     0,     0,    64,
       0,    86,    87,     0,     0,     0,   140,    91,    92,    93,
      94,    95,   188,     0,     0,     0,    67,     0,     0,     0,
       0,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    58,    59,    60,    82,     0,
       0,    61,    62,     0,     0,     0,    83,    84,    85,    63,
       0,     0,     0,     0,     0,    64,     0,    86,    87,     0,
       0,     0,   140,    91,    92,    93,    94,    95,    65,     0,
       0,     0,   190,     0,     0,     0,     0,     0,     0,    69,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,     0,     0,     0,
       0,     0,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,    86,    87,     0,     0,     0,   140,    91,
      92,    93,    94,    95
};

static const yytype_int16 yycheck[] =
{
       0,    14,    75,    44,    65,    53,    72,    52,   146,    43,
      41,     1,     0,   181,     2,    28,     8,    17,   262,    80,
      16,     9,   188,     4,    39,    77,    11,    57,     8,    17,
       7,    72,    22,     8,    11,     7,   134,   248,    44,    11,
       8,    41,    40,     0,    45,    11,     8,    39,     8,    47,
      39,     8,   125,    86,    43,    61,    62,    57,     8,    39,
       6,     7,   273,    43,    39,    65,    72,   100,    43,    28,
     168,     8,    44,    42,    89,    41,    82,    40,    47,    39,
      86,    45,    39,    47,    47,    77,    78,    79,    80,    39,
      49,     8,     9,    10,   100,    45,    40,    89,   146,   130,
      89,    41,    39,   164,    89,   178,    87,   351,    45,    89,
      78,   156,    89,    89,   175,   176,    78,    89,   179,   287,
      77,    78,    79,    80,   197,     8,   187,   188,   158,    89,
     130,     8,    89,    77,    78,    40,    40,    44,    40,    89,
      47,   202,    40,    47,   134,   193,   134,   195,    40,    47,
     181,    40,    89,   201,    40,    47,    39,    40,   158,     8,
      43,    39,    39,    40,    39,    43,    43,   215,   156,    41,
      40,   244,    77,    78,   235,    77,    78,    47,   168,    44,
     246,   181,    47,    40,   217,   218,   219,    89,   188,   237,
      47,    77,    78,    39,    77,    78,    40,    43,    23,    24,
      77,    78,    40,    47,   342,   246,    89,    44,   281,    47,
      47,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   395,
      40,    12,    13,   294,    40,    46,    40,    47,    14,    15,
     246,    47,   275,    47,    25,   293,    39,    39,     5,    39,
     298,    43,   248,   301,   267,   245,    39,   245,    39,   292,
      43,    39,    43,    89,   277,    43,    45,    48,    47,   275,
      77,    78,   338,    16,    17,    18,    19,   224,   225,   226,
     227,    45,   272,    47,   357,   358,   292,   360,    39,    45,
     363,    47,    45,    39,   342,    41,    45,   338,    11,    39,
     361,   362,   347,   337,    46,    47,   220,   221,   369,    66,
      67,    68,    69,    70,    71,    72,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    24,   375,   401,   222,
     223,   344,   338,   228,   229,    23,   377,    46,    20,    22,
     353,    21,   415,    27,    45,   418,    45,    40,     6,     7,
       8,    47,    44,    89,    12,    13,    11,    46,    39,    46,
      46,    46,    20,    40,    24,    89,    45,    57,    26,    47,
      44,   377,    47,    45,   387,    23,   389,    89,    89,    89,
      39,    39,    39,    41,    42,    43,    40,    45,    40,    40,
      40,    44,    50,    25,    52,   395,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    47,    40,
      44,    53,    45,    89,   293,    73,    74,    75,    55,    77,
      78,   295,   230,   232,   158,   347,    84,    85,    86,    87,
     231,    89,    90,    91,    92,    93,    94,     6,     7,     8,
     234,    17,   233,    12,    13,   276,    -1,   252,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,   130,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    50,    -1,    52,    -1,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    74,    75,    -1,    77,    78,
      -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,
      89,    90,    91,    92,    93,    94,     6,     7,     8,    -1,
      -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    41,    42,    43,    45,    45,    -1,    -1,    -1,    50,
      50,    -1,    52,    -1,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    77,    78,    79,    80,
      81,    82,    83,    -1,    84,    85,    86,    87,    89,    89,
      90,    91,    92,    93,    94,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      -1,    52,    -1,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    86,    87,    -1,    89,    90,
      91,    92,    93,    94,     6,     7,     8,    -1,    -1,    -1,
      12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    41,
      -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,
      52,    -1,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    85,    86,    87,    -1,    89,    90,    91,
      92,    93,    94,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    -1,    -1,    -1,    -1,    -1,    42,    20,    -1,    45,
      -1,    -1,    -1,    26,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    77,    78,    79,    80,    81,    82,    83,    -1,     6,
       7,     8,    65,    89,    -1,    12,    13,    -1,    -1,    -1,
      73,    74,    75,    20,    77,    78,    -1,    -1,    -1,    26,
      -1,    84,    85,    -1,    -1,    -1,    89,    90,    91,    92,
      93,    94,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,     7,     8,    65,    -1,
      -1,    12,    13,    -1,    -1,    -1,    73,    74,    75,    20,
      77,    78,    -1,    -1,    -1,    26,    -1,    84,    85,    -1,
      -1,    -1,    89,    90,    91,    92,    93,    94,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    65,    -1,    -1,    12,    13,    -1,
      -1,    -1,    73,    74,    75,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    84,    85,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    39,    -1,    -1,    -1,    43,    44,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      65,    -1,    -1,    12,    13,    -1,    -1,    -1,    73,    74,
      75,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    84,
      85,    -1,    -1,    -1,    89,    90,    91,    92,    93,    94,
      39,    -1,    41,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    65,    -1,    -1,    12,
      13,    -1,    -1,    -1,    73,    74,    75,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    84,    85,    -1,    -1,    -1,
      89,    90,    91,    92,    93,    94,    39,    -1,    -1,    -1,
      43,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,
       7,     8,    65,    -1,    -1,    12,    13,    -1,    -1,    -1,
      73,    74,    75,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    84,    85,    -1,    -1,    -1,    89,    90,    91,    92,
      93,    94,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,     7,     8,    65,    -1,
      -1,    12,    13,    -1,    -1,    -1,    73,    74,    75,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    84,    85,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    39,    40,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    65,    -1,    -1,    12,    13,    -1,
      -1,    -1,    73,    74,    75,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    84,    85,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    39,    -1,    -1,    -1,    43,    44,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      65,    -1,    -1,    12,    13,    -1,    -1,    -1,    73,    74,
      75,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    84,
      85,    -1,    -1,    -1,    89,    90,    91,    92,    93,    94,
      39,    -1,    -1,    -1,    43,    -1,    45,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    65,    -1,    -1,    12,
      13,    -1,    -1,    -1,    73,    74,    75,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    84,    85,    -1,    -1,    -1,
      89,    90,    91,    92,    93,    94,    39,    40,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,
       7,     8,    65,    -1,    -1,    12,    13,    -1,    -1,    -1,
      73,    74,    75,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    84,    85,    -1,    -1,    -1,    89,    90,    91,    92,
      93,    94,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,     7,     8,    65,    -1,
      -1,    12,    13,    -1,    -1,    -1,    73,    74,    75,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    84,    85,    -1,
      -1,    88,    89,    90,    91,    92,    93,    94,    39,    -1,
      -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    65,    -1,    -1,    12,    13,    -1,
      -1,    -1,    73,    74,    75,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    84,    85,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94,    39,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      65,    -1,    -1,    12,    13,    -1,    -1,    -1,    73,    74,
      75,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    84,
      85,    -1,    -1,    -1,    89,    90,    91,    92,    93,    94,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,     7,     8,    65,    -1,    -1,    12,
      13,    -1,    -1,    -1,    73,    74,    75,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    84,    85,    -1,    -1,    -1,
      89,    90,    91,    92,    93,    94,    39,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,
       7,     8,    65,    -1,    -1,    12,    13,    -1,    -1,    -1,
      73,    74,    75,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    84,    85,    -1,    -1,    -1,    89,    90,    91,    92,
      93,    94,    39,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     6,     7,     8,    65,    -1,
      -1,    12,    13,    -1,    -1,    -1,    73,    74,    75,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    84,    85,    -1,
      -1,    -1,    89,    90,    91,    92,    93,    94,    39,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    85,    -1,    -1,    -1,    89,    90,
      91,    92,    93,    94
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    39,    77,    78,    79,    80,    89,   124,   125,
     128,   129,   132,   133,   142,   143,   144,   169,   170,   172,
      78,   144,   145,   142,   129,    45,   126,   127,   142,     5,
      66,    67,    68,    69,    70,    71,    72,   130,   131,    45,
      89,    41,   162,    39,    43,   143,     0,   170,    78,   144,
      40,    45,    47,    11,   162,     8,   104,    41,     6,     7,
       8,    12,    13,    20,    26,    39,    42,    43,    45,    50,
      52,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    73,    74,    75,    84,    85,    86,    87,
      89,    90,    91,    92,    93,    94,    97,    98,    99,   101,
     102,   103,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   122,   124,   125,   155,
     156,   157,   159,   161,   162,   163,   164,   165,   166,   168,
     171,   173,    40,    89,   125,   146,   147,   148,   149,    44,
      89,   101,   119,   123,   127,   142,    41,   120,   153,   104,
      45,    50,    81,    82,    83,    89,   125,   132,   134,   135,
     136,   137,   138,   139,    39,   101,   101,   122,   125,   150,
       7,    11,    89,   177,   178,    39,    39,   123,    46,    39,
     155,    39,    89,    45,    45,    45,   122,    39,    39,   101,
      43,   108,   129,    24,   160,    23,   158,    46,    12,    13,
      25,    39,    43,    48,    11,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,   121,   108,     8,     9,    10,
       6,     7,    23,    24,    16,    17,    18,    19,    14,    15,
      20,    22,    21,    27,    28,    49,    45,    47,    45,    45,
      42,   155,    42,   124,   163,    39,    43,   142,   144,   151,
     152,    40,    47,    40,    47,    44,   153,   154,    89,    46,
      46,    46,    39,    45,   127,   140,   141,   142,    45,    42,
     135,    40,    39,   144,   151,    40,    47,    44,    47,   122,
     122,    46,   155,   122,    57,   124,   164,   167,    45,    45,
     122,   150,    44,    39,    43,   105,   106,   120,    24,    88,
     120,    23,   155,    89,    40,   100,   120,   122,    89,   120,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   111,
     111,   112,   112,   113,   114,   115,   116,   117,   122,   120,
      42,    40,   146,   151,    44,   123,   152,    39,    43,   148,
      89,    42,    47,    39,    40,   147,    45,    47,   162,   108,
     178,    39,   162,   174,   175,    11,    89,    40,    40,   155,
      40,    39,   164,    40,    40,   108,    40,   100,   122,    43,
     106,   120,    88,   120,    40,    47,    44,    46,    40,    40,
      44,    40,   146,    44,   123,    42,   153,    40,   162,    40,
     141,    47,    40,   147,   162,    25,   176,   155,   155,   155,
     122,    40,   122,   155,    40,    44,   122,   120,   119,    40,
      44,   162,   162,    40,   150,    53,    40,   155,    40,    44,
     155,    45,   155
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    96,    97,    97,    97,    97,    98,    98,    98,    98,
      98,    98,    98,    98,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   101,   101,   101,   101,   101,   101,
     101,   101,   102,   102,   102,   102,   102,   102,   103,   103,
     103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     108,   108,   109,   109,   109,   109,   110,   110,   110,   111,
     111,   111,   112,   112,   112,   112,   112,   113,   113,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   118,   118,
     119,   119,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   122,   122,   123,   124,   124,
     125,   125,   126,   126,   127,   127,   128,   128,   129,   130,
     131,   131,   131,   131,   131,   131,   131,   131,   132,   132,
     133,   133,   134,   134,   135,   135,   136,   136,   136,   137,
     137,   137,   137,   137,   137,   137,   138,   138,   139,   140,
     140,   141,   142,   142,   143,   143,   143,   143,   143,   143,
     143,   144,   144,   144,   144,   145,   145,   146,   147,   147,
     148,   148,   148,   149,   149,   150,   150,   151,   151,   151,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   153,
     153,   153,   154,   154,   155,   155,   155,   155,   155,   155,
     155,   156,   156,   157,   158,   158,   158,   158,   159,   160,
     160,   161,   161,   161,   162,   162,   162,   162,   163,   163,
     164,   164,   165,   165,   165,   166,   166,   166,   166,   166,
     167,   167,   168,   168,   168,   168,   168,   169,   169,   170,
     170,   170,   171,   171,   172,   172,   173,   173,   174,   175,
     175,   176,   176,   177,   177,   177,   177,   177,   178,   178
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     3,
       3,     2,     0,     2,     3,     4,     2,     3,     4,     2,
       1,     4,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     5,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     2,     3,
       1,     2,     1,     3,     1,     3,     0,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     2,
       1,     1,     1,     2,     1,     1,     2,     2,     2,     3,
       2,     3,     2,     1,     1,     1,     5,     4,     5,     1,
       3,     1,     1,     2,     1,     3,     4,     3,     4,     4,
       3,     1,     2,     2,     3,     1,     2,     1,     1,     3,
       2,     2,     1,     1,     3,     1,     2,     1,     1,     2,
       3,     2,     3,     3,     4,     2,     3,     3,     4,     1,
       3,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     3,     3,     2,     2,
       3,     3,     4,     3,     2,     3,     3,     4,     1,     2,
       1,     2,     5,     7,     5,     5,     5,     7,     6,     7,
       1,     1,     3,     2,     2,     2,     3,     1,     2,     1,
       2,     1,     1,     2,     3,     2,     5,     4,     2,     2,
       3,     0,     2,     1,     1,     1,     3,     3,     1,     3
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

#line 1863 "cpp.tab.c"

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

#line 558 "cpp.y"


	int main(){
		return 0;
	}
