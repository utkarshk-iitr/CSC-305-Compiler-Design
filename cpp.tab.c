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
  YYSYMBOL_new_expression = 101,           /* new_expression  */
  YYSYMBOL_scalar_new_init_opt = 102,      /* scalar_new_init_opt  */
  YYSYMBOL_new_declarator = 103,           /* new_declarator  */
  YYSYMBOL_delete_expression = 104,        /* delete_expression  */
  YYSYMBOL_unary_operator = 105,           /* unary_operator  */
  YYSYMBOL_cast_expression = 106,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 107, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 108,      /* additive_expression  */
  YYSYMBOL_shift_expression = 109,         /* shift_expression  */
  YYSYMBOL_relational_expression = 110,    /* relational_expression  */
  YYSYMBOL_equality_expression = 111,      /* equality_expression  */
  YYSYMBOL_and_expression = 112,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 113,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 114,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 115,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 116,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 117,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 118,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 119,      /* assignment_operator  */
  YYSYMBOL_expression = 120,               /* expression  */
  YYSYMBOL_constant_expression = 121,      /* constant_expression  */
  YYSYMBOL_declaration = 122,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 123,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 124,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 125,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 126,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 127,           /* type_specifier  */
  YYSYMBOL_struct_or_class_specifier = 128, /* struct_or_class_specifier  */
  YYSYMBOL_struct_or_class = 129,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 130, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 131,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 132,   /* access_specifier_label  */
  YYSYMBOL_member_declaration = 133,       /* member_declaration  */
  YYSYMBOL_constructor_definition = 134,   /* constructor_definition  */
  YYSYMBOL_destructor_definition = 135,    /* destructor_definition  */
  YYSYMBOL_struct_declarator_list = 136,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 137,        /* struct_declarator  */
  YYSYMBOL_specifier_qualifier_list = 138, /* specifier_qualifier_list  */
  YYSYMBOL_type_qualifier = 139,           /* type_qualifier  */
  YYSYMBOL_declarator = 140,               /* declarator  */
  YYSYMBOL_direct_declarator = 141,        /* direct_declarator  */
  YYSYMBOL_pointer = 142,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 143,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 144,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 145,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 146,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 147,          /* identifier_list  */
  YYSYMBOL_type_name = 148,                /* type_name  */
  YYSYMBOL_abstract_declarator = 149,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 150, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 151,              /* initializer  */
  YYSYMBOL_initializer_list = 152,         /* initializer_list  */
  YYSYMBOL_statement = 153,                /* statement  */
  YYSYMBOL_io_statement = 154,             /* io_statement  */
  YYSYMBOL_cout_expression = 155,          /* cout_expression  */
  YYSYMBOL_insertion_list = 156,           /* insertion_list  */
  YYSYMBOL_cin_expression = 157,           /* cin_expression  */
  YYSYMBOL_extraction_list = 158,          /* extraction_list  */
  YYSYMBOL_labeled_statement = 159,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 160,       /* compound_statement  */
  YYSYMBOL_statement_list = 161,           /* statement_list  */
  YYSYMBOL_expression_statement = 162,     /* expression_statement  */
  YYSYMBOL_selection_statement = 163,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 164,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 165,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 166,           /* jump_statement  */
  YYSYMBOL_translation_unit = 167,         /* translation_unit  */
  YYSYMBOL_external_declaration = 168,     /* external_declaration  */
  YYSYMBOL_declaration_list = 169,         /* declaration_list  */
  YYSYMBOL_function_definition = 170,      /* function_definition  */
  YYSYMBOL_lambda_expression = 171,        /* lambda_expression  */
  YYSYMBOL_lambda_declarator = 172,        /* lambda_declarator  */
  YYSYMBOL_lambda_parameter_clause = 173,  /* lambda_parameter_clause  */
  YYSYMBOL_trailing_return_opt = 174,      /* trailing_return_opt  */
  YYSYMBOL_lambda_capture_clause = 175,    /* lambda_capture_clause  */
  YYSYMBOL_capture_list = 176              /* capture_list  */
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
#define YYLAST   2042

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  253
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  425

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
     104,   105,   109,   113,   114,   115,   119,   120,   124,   125,
     129,   130,   131,   132,   133,   134,   138,   139,   143,   144,
     145,   146,   150,   151,   152,   156,   157,   158,   162,   163,
     164,   165,   166,   170,   171,   172,   176,   177,   181,   182,
     186,   187,   191,   192,   196,   197,   201,   202,   206,   207,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   225,   226,   230,   234,   235,   239,   240,   241,   242,
     243,   244,   248,   249,   253,   254,   258,   259,   260,   264,
     265,   266,   267,   268,   269,   270,   271,   275,   276,   280,
     281,   285,   286,   290,   291,   295,   296,   297,   301,   302,
     303,   304,   305,   306,   307,   311,   312,   316,   320,   321,
     325,   329,   330,   331,   332,   336,   340,   341,   345,   346,
     347,   348,   349,   350,   351,   355,   356,   357,   358,   362,
     363,   367,   371,   372,   376,   377,   378,   382,   383,   387,
     388,   392,   393,   394,   398,   399,   400,   401,   402,   403,
     404,   405,   406,   410,   411,   412,   416,   417,   421,   422,
     423,   424,   425,   426,   427,   431,   432,   436,   440,   441,
     442,   443,   447,   451,   452,   456,   457,   458,   462,   463,
     464,   465,   469,   470,   474,   475,   479,   480,   481,   485,
     486,   487,   488,   489,   493,   494,   498,   499,   500,   501,
     502,   506,   507,   511,   512,   513,   517,   518,   522,   523,
     527,   528,   532,   536,   537,   541,   542,   546,   547,   548,
     549,   550,   554,   555
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
  "new_expression", "scalar_new_init_opt", "new_declarator",
  "delete_expression", "unary_operator", "cast_expression",
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

#define YYPACT_NINF (-248)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1788,  -248,  -248,    42,    59,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,    29,
     509,   509,   -22,   -33,   509,    37,    69,   -24,   633,  -248,
    -248,  -248,  -248,    42,    50,  -248,    81,  -248,    13,  -248,
    -248,  -248,    58,  -248,   343,  -248,  1873,  1026,    69,  -248,
    -248,  -248,  -248,  -248,  -248,    59,  1081,  -248,  1886,  -248,
    -248,  -248,  1631,  1631,  -248,  -248,   597,  -248,    23,  -248,
    -248,    67,   104,  1686,    17,   129,   883,   134,   108,    85,
     167,  1136,   193,  1741,  -248,  -248,  -248,  1796,   308,   234,
     215,   219,  -248,  -248,  -248,  -248,  -248,  -248,  -248,   119,
     431,  -248,  -248,  1686,  -248,   267,   195,   256,   224,   212,
     253,   260,   264,   261,    24,  -248,  -248,   203,  -248,    29,
    -248,  -248,   249,   252,  -248,  -248,   707,  -248,  -248,  -248,
    -248,   433,  -248,  -248,  -248,    48,   259,   272,  -248,     0,
    -248,  -248,  -248,  -248,   281,  -248,   316,  1081,  -248,  -248,
    -248,   240,   285,   286,   290,   298,   201,   293,    15,  -248,
    -248,  -248,  -248,  -248,   127,   201,  1686,  -248,  -248,    30,
      33,   300,   295,  -248,   299,   305,  1686,  1686,   307,   883,
    1686,   289,   523,   301,  -248,  -248,  -248,   209,  1686,   597,
    -248,    22,  -248,   311,  1686,   333,  1191,   335,   883,  -248,
    -248,   271,  1246,  1686,   273,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  1686,  -248,  1686,  1686,
    1686,  1686,  1686,  1686,  1686,  1686,  1686,  1686,  1686,  1686,
    1686,  1686,  1686,  1686,  1686,  1686,  1686,  -248,  1686,  -248,
    -248,  -248,  -248,  -248,  -248,   795,  1832,  1301,  -248,    36,
    -248,   126,  -248,   509,  -248,   277,  -248,  -248,    87,   327,
    -248,  -248,  -248,   241,  -248,  -248,  -248,  -248,  -248,  -248,
     214,  -248,    13,  -248,  -248,  1919,   194,  -248,  1686,   280,
     223,    27,    78,   106,   883,  -248,   152,   331,  -248,  -248,
    1356,  -248,  -248,   153,   332,  1686,  1686,   196,   324,  1686,
    -248,   324,  1411,  -248,  -248,  -248,   170,  -248,   101,  -248,
    -248,  -248,  -248,  -248,   267,   267,   195,   195,   256,   256,
     256,   256,   224,   224,   212,   253,   260,   264,   261,   255,
    -248,  -248,  -248,   340,   341,  -248,   339,   126,  1941,  1466,
    -248,  -248,  -248,   971,   347,    37,   174,  -248,    59,  -248,
    -248,   342,  1965,  -248,    37,   365,  -248,  -248,   883,   883,
    -248,   883,  1686,  1521,   883,  -248,  -248,   107,  1576,  1686,
    -248,   324,  -248,   324,  -248,  1686,  -248,  1686,  -248,  -248,
    -248,  -248,   351,  -248,   348,  -248,  -248,    37,  -248,    37,
    -248,   334,  -248,   176,  -248,   308,  -248,   369,  -248,  -248,
     178,   883,   182,  -248,  -248,  -248,   184,   205,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,   883,   350,  -248,   883,
    -248,  -248,  -248,  -248,  -248
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   106,   116,   155,     0,   109,   111,   113,   110,   114,
     115,   112,   108,   107,   145,   120,   119,   148,   235,     0,
      96,    98,     0,     0,   100,     0,   147,     0,     0,   231,
     233,   159,   157,   156,     0,    94,     0,   102,   104,    97,
      99,   234,   118,   101,     0,   239,     0,     0,   146,     1,
     232,   160,   158,   149,    95,     0,     0,   238,     0,    42,
      43,    41,     0,     0,    40,    45,     0,   208,   247,   214,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,    11,     0,     0,     0,
       0,     2,     6,    10,     9,     7,     8,    14,     3,    24,
      46,    31,    30,     0,    48,    52,    55,    58,    63,    66,
      68,    70,    72,    74,    76,    78,    91,     0,   236,     0,
     212,   194,     0,     0,   188,   189,     0,   190,   191,   192,
     193,     0,     5,   154,   167,   166,     0,   161,   162,     0,
     151,     2,    46,    93,     0,   103,   104,     0,   183,   105,
     132,     0,     0,     0,     0,     0,   142,     0,     0,   121,
     123,   124,   133,   134,     0,   144,     0,    25,    26,     0,
     169,     0,   248,   252,     0,   249,     0,     0,     0,     0,
       0,     0,     0,     0,   227,   228,   229,     0,     0,     0,
      28,     0,    39,     0,     0,   202,     0,   197,     0,    20,
      21,     0,     0,     0,     0,    80,    84,    85,    81,    82,
      83,    88,    90,    89,    86,    87,     0,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   215,     0,   195,
     196,   209,   213,   210,   237,     0,     0,     0,   164,   171,
     165,   172,   152,     0,   153,     0,   150,   186,     0,     0,
     125,   126,   127,     0,   141,   131,   117,   122,   129,   140,
       0,   138,   104,   143,     4,     0,   171,   170,     0,     0,
       0,     0,     0,     0,     0,   207,     0,     0,   225,   224,
       0,   226,   230,     0,     0,     0,     0,    33,   203,     0,
     199,   198,     0,   205,    19,    16,     0,    22,     0,    18,
      79,    49,    50,    51,    53,    54,    56,    57,    60,    59,
      61,    62,    64,    65,    67,    69,    71,    73,    75,     0,
      92,   211,   179,     0,     0,   175,     0,   173,     0,     0,
     163,   168,   184,     0,     0,     0,     0,   128,     0,   130,
      47,   251,     0,   241,     0,   245,   250,   253,     0,     0,
     206,     0,     0,     0,     0,    29,    38,     0,     0,     0,
      32,   204,   200,   201,    17,     0,    15,     0,   180,   174,
     176,   181,     0,   177,     0,   185,   187,     0,   136,     0,
     139,     0,   243,     0,   240,     0,   242,   216,   218,   219,
       0,     0,     0,   220,    36,    34,     0,     0,    23,    77,
     182,   178,   137,   135,   244,   246,     0,     0,   222,     0,
      35,    37,   217,   221,   223
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -248,  -248,  -248,  -248,    56,   -44,  -248,  -248,  -248,  -248,
    -248,   -59,    83,    91,    65,    92,   192,   198,   210,   191,
     213,  -248,   -43,    -8,  -248,   -39,   -52,   -30,    25,  -248,
     -50,  -248,   -56,   -36,  -248,  -248,   291,  -248,  -248,  -248,
    -248,  -248,    96,   -49,    55,     7,   -21,    28,  -248,   -38,
    -247,   197,  -248,   258,   -99,  -187,  -138,  -248,   -75,  -248,
    -248,  -248,  -248,  -248,  -248,   -25,   320,  -170,  -248,  -248,
    -248,  -248,  -248,   424,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,   175
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    97,    98,    99,   306,   100,   101,   370,   297,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   216,   117,   144,    18,   135,    36,
      37,    20,    21,    22,    23,   158,   159,   160,   161,   162,
     163,   270,   271,   164,    24,   146,    26,    27,    33,   333,
     137,   138,   139,   171,   334,   251,   149,   258,   120,   121,
     122,   197,   123,   195,   124,   125,   126,   127,   128,   129,
     290,   130,    28,    29,   131,    30,   132,   354,   355,   396,
     174,   175
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,   181,   156,   142,   143,   145,    48,    25,   136,   257,
     156,    34,   289,    57,   118,     4,   346,   170,   167,   168,
       2,   178,   157,    41,    56,    19,    38,   169,   192,   142,
     143,    32,   193,   172,   172,    25,   250,     3,   356,   190,
     254,     3,   187,   142,   217,    39,    40,   255,   148,    43,
       3,   242,   235,    19,    44,    42,     3,   266,    31,   142,
     150,    52,   337,   179,    17,   151,   295,     3,     4,   119,
     274,   277,   275,   236,    35,   246,   247,   238,    44,   247,
       5,     6,     7,     8,     9,    10,    11,   246,    51,   337,
      53,   247,    14,    15,    16,   152,   153,   154,     4,    58,
     156,   244,   156,   155,   285,   393,   176,   264,    46,   156,
     173,   173,    47,   165,   269,   357,   273,    17,   358,    14,
     363,   165,   157,   303,    17,   238,    54,   169,    55,   342,
     184,   199,   200,   156,   343,     3,    17,   282,   283,   148,
     170,   286,   248,   177,   201,   376,   359,    17,   238,   293,
     169,   404,   288,   238,   238,   298,   119,   301,   202,   311,
     312,   313,   203,   249,   308,   338,     4,   204,   180,   339,
     242,   272,   268,   182,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   361,   364,   307,   336,   183,   329,   276,   238,
     238,   221,   222,   142,   143,   386,     2,   119,   310,   360,
     374,   165,   185,   165,   389,    17,   414,   375,   417,   350,
     165,   253,   419,   253,   420,   238,   229,   230,    48,   238,
     330,   375,   188,   275,   142,   368,   366,   247,   196,   369,
     225,   226,   227,   228,   165,     1,     2,   349,   237,   421,
     238,   142,   238,    34,   292,   353,   238,   367,   194,   347,
     371,   348,   352,   373,    44,   198,     5,     6,     7,     8,
       9,    10,    11,   231,   249,   218,   219,   220,    14,   223,
     224,   345,   232,   397,   398,   233,   399,   384,   234,   403,
     318,   319,   320,   321,   239,   142,   143,   240,   269,   252,
     382,   377,   238,   276,   314,   315,     5,     6,     7,     8,
       9,    10,    11,     2,   316,   317,    12,    13,    14,   253,
     388,   322,   323,   400,   402,   256,   418,    56,   259,   394,
     407,   260,   261,   142,   409,   148,   262,   263,   265,   415,
     278,   422,   279,   280,   424,   287,   291,     1,     2,    59,
      60,    61,   281,   284,   296,    62,    63,   299,   302,   304,
     307,   309,   412,    64,   413,   341,   344,   408,   173,    65,
     362,   238,   365,     5,     6,     7,     8,     9,    10,    11,
     378,   379,    66,   380,    44,    67,    68,   387,    69,   391,
     395,   410,   411,    70,    71,   423,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     5,     6,
       7,     8,     9,    10,    11,    84,    85,    86,    12,    13,
      14,   416,   357,   324,   406,   327,    87,    88,    89,    90,
     325,    91,    92,    93,    94,    95,    96,     1,     2,    59,
      60,    61,   205,   326,   390,    62,    63,   294,   328,   267,
     340,   245,    50,    64,   351,     0,     0,     0,     0,    65,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
       0,     0,    66,     0,    44,   243,    68,     0,    69,     0,
       0,     0,     0,    70,    71,     0,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     5,     6,
       7,     8,     9,    10,    11,    84,    85,    86,    12,    13,
      14,     0,     0,     1,     2,     0,    87,    88,    89,    90,
       0,    91,    92,    93,    94,    95,    96,     1,     2,    59,
      60,    61,     0,     0,     0,    62,    63,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,    68,     0,    69,     0,
       0,     0,     0,    70,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,    12,    13,    14,    83,     5,     6,
       7,     8,     9,    10,    11,    84,    85,    86,    12,    13,
      14,     0,     2,    59,    60,    61,    87,    88,     0,    62,
      63,   141,    92,    93,    94,    95,    96,    64,     0,     0,
       0,     0,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,     0,     0,    66,     1,     2,     0,
      68,     3,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    83,     5,     6,     7,     8,     9,    10,    11,    84,
      85,    86,     4,     0,    14,     0,     0,     0,     0,     0,
      87,    88,     0,     0,     0,   141,    92,    93,    94,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,     0,     0,     0,    12,    13,
      14,    15,    16,    59,    60,    61,     0,     0,     0,    62,
      63,    17,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,    44,   241,
      68,     0,    69,     0,     0,     0,     0,    70,    71,     0,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     0,     0,     0,     0,     0,     0,     0,    84,
      85,    86,     0,     0,     0,     0,     0,     0,     0,     0,
      87,    88,    89,    90,     0,    91,    92,    93,    94,    95,
      96,    59,    60,    61,     0,     0,     0,    62,    63,     0,
       0,     0,     0,     0,     0,    64,     0,     0,     0,     0,
       0,    65,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,     0,    44,   331,    68,     0,
      69,     0,     0,     0,     0,    70,    71,     0,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       0,     0,     0,     0,     0,     0,     0,    84,    85,    86,
       0,     0,     0,     0,     0,     0,     0,     0,    87,    88,
      89,    90,     0,    91,    92,    93,    94,    95,    96,    59,
      60,    61,     0,     0,     0,    62,    63,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,    44,     0,    68,     0,    69,     0,
       0,     0,     0,    70,    71,     0,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     0,     0,
       0,     0,     0,     0,     0,    84,    85,    86,     0,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    89,    90,
       0,    91,    92,    93,    94,    95,    96,    59,    60,    61,
       0,     0,     0,    62,    63,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,     0,   147,   385,    68,     0,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    61,    83,     0,     0,    62,    63,
       0,     0,     0,    84,    85,    86,    64,     0,     0,     0,
       0,     0,    65,     0,    87,    88,     0,     0,     0,   141,
      92,    93,    94,    95,    96,    66,     0,     0,     0,    68,
     140,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      83,     0,     0,    62,    63,     0,     0,     0,    84,    85,
      86,    64,     0,     0,     0,     0,     0,    65,     0,    87,
      88,     0,     0,     0,   141,    92,    93,    94,    95,    96,
      66,     0,   147,     0,    68,     0,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    61,    83,     0,     0,    62,    63,
       0,     0,     0,    84,    85,    86,    64,     0,     0,     0,
       0,     0,    65,     0,    87,    88,     0,     0,     0,   141,
      92,    93,    94,    95,    96,    66,     0,     0,     0,    68,
       0,   186,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      83,     0,     0,    62,    63,     0,     0,     0,    84,    85,
      86,    64,     0,     0,     0,     0,     0,    65,     0,    87,
      88,     0,     0,     0,   141,    92,    93,    94,    95,    96,
      66,     0,     0,     0,    68,     0,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    61,    83,     0,     0,    62,    63,
       0,     0,     0,    84,    85,    86,    64,     0,     0,     0,
       0,     0,    65,     0,    87,    88,     0,     0,   300,   141,
      92,    93,    94,    95,    96,    66,   305,     0,     0,    68,
       0,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      83,     0,     0,    62,    63,     0,     0,     0,    84,    85,
      86,    64,     0,     0,     0,     0,     0,    65,     0,    87,
      88,     0,     0,     0,   141,    92,    93,    94,    95,    96,
      66,     0,     0,     0,    68,   335,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    61,    83,     0,     0,    62,    63,
       0,     0,     0,    84,    85,    86,    64,     0,     0,     0,
       0,     0,    65,     0,    87,    88,     0,     0,     0,   141,
      92,    93,    94,    95,    96,    66,     0,     0,     0,    68,
       0,    69,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      83,     0,     0,    62,    63,     0,     0,     0,    84,    85,
      86,    64,     0,     0,     0,     0,     0,    65,     0,    87,
      88,     0,     0,     0,   141,    92,    93,    94,    95,    96,
      66,     0,     0,     0,    68,     0,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    61,    83,     0,     0,    62,    63,
       0,     0,     0,    84,    85,    86,    64,     0,     0,     0,
       0,     0,    65,     0,    87,    88,     0,     0,   372,   141,
      92,    93,    94,    95,    96,    66,     0,     0,     0,    68,
     383,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      83,     0,     0,    62,    63,     0,     0,     0,    84,    85,
      86,    64,     0,     0,     0,     0,     0,    65,     0,    87,
      88,     0,     0,     0,   141,    92,    93,    94,    95,    96,
      66,   401,     0,     0,    68,     0,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    61,    83,     0,     0,    62,    63,
       0,     0,     0,    84,    85,    86,    64,     0,     0,     0,
       0,     0,    65,     0,    87,    88,     0,     0,     0,   141,
      92,    93,    94,    95,    96,    66,   405,     0,     0,    68,
       0,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      83,     0,     0,    62,    63,     0,     0,     0,    84,    85,
      86,    64,     0,     0,     0,     0,     0,    65,     0,    87,
      88,     0,     0,     0,   141,    92,    93,    94,    95,    96,
     166,     0,     0,     0,    68,     0,     0,     0,     0,     0,
       0,    70,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,    61,    83,     0,     0,    62,    63,
       0,     0,     0,    84,    85,    86,    64,     0,     0,     0,
       0,     0,    65,     0,    87,    88,     0,     0,     0,   141,
      92,    93,    94,    95,    96,    66,     0,     0,     0,    68,
       0,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    59,    60,    61,
      83,     0,     0,    62,    63,     0,     0,     0,    84,    85,
      86,    64,     0,     0,     0,     0,     0,    65,     0,    87,
      88,     0,     0,     0,   141,    92,    93,    94,    95,    96,
     189,     0,     0,     0,    68,     0,     0,     0,     0,     0,
       0,    70,     1,     2,     0,     0,     3,     0,     0,     0,
       0,     0,    59,    60,    61,    83,     0,     0,    62,    63,
       0,     0,     0,    84,    85,    86,    64,     0,     0,     0,
       0,     0,    65,     0,    87,    88,     0,     4,     0,   141,
      92,    93,    94,    95,    96,    66,     1,     2,     0,   191,
       3,     0,     0,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
      83,     0,     0,    12,    13,    14,    15,    16,    84,    85,
      86,   246,   332,     0,     0,   247,    17,     1,     2,    87,
      88,     0,     0,     0,   141,    92,    93,    94,    95,    96,
       0,     2,     0,     0,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,    12,    13,    14,
       0,     0,     0,   133,     0,     0,     0,     0,     0,     0,
      17,     0,     0,     1,     2,     0,     0,     3,     0,     0,
       0,   150,     0,     0,     0,     0,   151,     0,     5,     6,
       7,     8,     9,    10,    11,     1,     2,     0,    12,    13,
      14,     5,     6,     7,     8,     9,    10,    11,   275,   332,
       0,   134,   247,    14,    15,    16,   152,   153,   154,     1,
       2,     0,     0,     0,   155,     0,     0,     0,     0,     0,
       0,   381,     0,     0,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,    12,    13,    14,     0,     0,     0,
       0,     0,     0,     0,     0,   392,     5,     6,     7,     8,
       9,    10,    11,     0,     0,     0,    12,    13,    14,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
      12,    13,    14
};

static const yytype_int16 yycheck[] =
{
      25,    76,    58,    47,    47,    55,    27,     0,    46,   147,
      66,     4,   182,    38,    44,    39,   263,    66,    62,    63,
       5,    73,    58,    45,    11,     0,    19,    66,    87,    73,
      73,     3,    88,    11,    11,    28,   135,     8,    11,    83,
      40,     8,    81,    87,   103,    20,    21,    47,    56,    24,
       8,   126,    28,    28,    41,    88,     8,    42,     3,   103,
      45,    33,   249,    46,    88,    50,    44,     8,    39,    44,
      40,   170,    39,    49,    45,    39,    43,    47,    41,    43,
      65,    66,    67,    68,    69,    70,    71,    39,    33,   276,
      40,    43,    77,    78,    79,    80,    81,    82,    39,    41,
     156,   131,   158,    88,   179,   352,    39,   156,    39,   165,
      88,    88,    43,    58,   164,    88,   165,    88,    40,    77,
     290,    66,   158,   198,    88,    47,    45,   166,    47,    42,
      45,    12,    13,   189,    47,     8,    88,   176,   177,   147,
     189,   180,   135,    39,    25,    44,    40,    88,    47,   188,
     189,    44,   182,    47,    47,   194,   131,   196,    39,   218,
     219,   220,    43,   135,   203,    39,    39,    48,    39,    43,
     245,   164,    45,    39,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,    40,    40,   202,   247,    88,   236,   170,    47,
      47,     6,     7,   247,   247,   343,     5,   182,   216,   284,
      40,   156,    45,   158,    40,    88,    40,    47,    40,   278,
     165,    47,    40,    47,    40,    47,    14,    15,   249,    47,
     238,    47,    39,    39,   278,    39,   295,    43,    23,    43,
      16,    17,    18,    19,   189,     4,     5,   272,    45,    44,
      47,   295,    47,   246,    45,   280,    47,   296,    24,    45,
     299,    47,    39,   302,    41,    46,    65,    66,    67,    68,
      69,    70,    71,    20,   246,     8,     9,    10,    77,    23,
      24,    40,    22,   358,   359,    21,   361,   339,    27,   364,
     225,   226,   227,   228,    45,   339,   339,    45,   348,    40,
     338,    46,    47,   275,   221,   222,    65,    66,    67,    68,
      69,    70,    71,     5,   223,   224,    75,    76,    77,    47,
     345,   229,   230,   362,   363,    44,   401,    11,    88,   354,
     369,    46,    46,   377,   377,   343,    46,    39,    45,   395,
      40,   416,    47,    44,   419,    56,    45,     4,     5,     6,
       7,     8,    47,    46,    43,    12,    13,    24,    23,    88,
     368,    88,   387,    20,   389,    88,    39,   375,    88,    26,
      39,    47,    40,    65,    66,    67,    68,    69,    70,    71,
      40,    40,    39,    44,    41,    42,    43,    40,    45,    47,
      25,    40,    44,    50,    51,    45,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    52,    88,   231,   368,   234,    83,    84,    85,    86,
     232,    88,    89,    90,    91,    92,    93,     4,     5,     6,
       7,     8,    11,   233,   348,    12,    13,   189,   235,   158,
     253,   131,    28,    20,   279,    -1,    -1,    -1,    -1,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    39,    -1,    41,    42,    43,    -1,    45,    -1,
      -1,    -1,    -1,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,    -1,     4,     5,    -1,    83,    84,    85,    86,
      -1,    88,    89,    90,    91,    92,    93,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    -1,    45,    -1,
      -1,    -1,    -1,    50,    65,    66,    67,    68,    69,    70,
      71,    -1,    -1,    -1,    75,    76,    77,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    -1,     5,     6,     7,     8,    83,    84,    -1,    12,
      13,    88,    89,    90,    91,    92,    93,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     0,    -1,    -1,    39,     4,     5,    -1,
      43,     8,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    39,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      83,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,    71,    -1,    -1,    -1,    75,    76,
      77,    78,    79,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    88,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    -1,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    84,    85,    86,    -1,    88,    89,    90,    91,    92,
      93,     6,     7,     8,    -1,    -1,    -1,    12,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    41,    42,    43,    -1,
      45,    -1,    -1,    -1,    -1,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      85,    86,    -1,    88,    89,    90,    91,    92,    93,     6,
       7,     8,    -1,    -1,    -1,    12,    13,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    41,    -1,    43,    -1,    45,    -1,
      -1,    -1,    -1,    50,    51,    -1,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,    86,
      -1,    88,    89,    90,    91,    92,    93,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,    13,
      -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    39,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,
      74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      39,    -1,    41,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,    13,
      -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    39,    -1,    -1,    -1,    43,
      -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,
      74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,    13,
      -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    83,    84,    -1,    -1,    87,    88,
      89,    90,    91,    92,    93,    39,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,
      74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      39,    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,    13,
      -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    39,    -1,    -1,    -1,    43,
      -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,
      74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,    13,
      -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    83,    84,    -1,    -1,    87,    88,
      89,    90,    91,    92,    93,    39,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,
      74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      39,    40,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,    13,
      -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    39,    40,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,
      74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,    13,
      -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    83,    84,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    39,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      64,    -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,
      74,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    50,     4,     5,    -1,    -1,     8,    -1,    -1,    -1,
      -1,    -1,     6,     7,     8,    64,    -1,    -1,    12,    13,
      -1,    -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,
      -1,    -1,    26,    -1,    83,    84,    -1,    39,    -1,    88,
      89,    90,    91,    92,    93,    39,     4,     5,    -1,    43,
       8,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      64,    -1,    -1,    75,    76,    77,    78,    79,    72,    73,
      74,    39,    40,    -1,    -1,    43,    88,     4,     5,    83,
      84,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      68,    69,    70,    71,    -1,    -1,    -1,    75,    76,    77,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,     4,     5,    -1,    -1,     8,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    65,    66,
      67,    68,    69,    70,    71,     4,     5,    -1,    75,    76,
      77,    65,    66,    67,    68,    69,    70,    71,    39,    40,
      -1,    88,    43,    77,    78,    79,    80,    81,    82,     4,
       5,    -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    -1,    -1,    -1,    75,    76,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    65,    66,    67,    68,
      69,    70,    71,    -1,    -1,    -1,    75,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    70,    71,    -1,    -1,    -1,
      75,    76,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     8,    39,    65,    66,    67,    68,    69,
      70,    71,    75,    76,    77,    78,    79,    88,   122,   123,
     126,   127,   128,   129,   139,   140,   141,   142,   167,   168,
     170,   139,   142,   143,   140,    45,   124,   125,   140,   123,
     123,    45,    88,   123,    41,   160,    39,    43,   141,     0,
     168,   139,   142,    40,    45,    47,    11,   160,    41,     6,
       7,     8,    12,    13,    20,    26,    39,    42,    43,    45,
      50,    51,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    72,    73,    74,    83,    84,    85,
      86,    88,    89,    90,    91,    92,    93,    96,    97,    98,
     100,   101,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   120,   122,   123,
     153,   154,   155,   157,   159,   160,   161,   162,   163,   164,
     166,   169,   171,    40,    88,   123,   144,   145,   146,   147,
      44,    88,   100,   117,   121,   125,   140,    41,   118,   151,
      45,    50,    80,    81,    82,    88,   127,   128,   130,   131,
     132,   133,   134,   135,   138,   139,    39,   100,   100,   120,
     138,   148,    11,    88,   175,   176,    39,    39,   121,    46,
      39,   153,    39,    88,    45,    45,    45,   120,    39,    39,
     100,    43,   106,   127,    24,   158,    23,   156,    46,    12,
      13,    25,    39,    43,    48,    11,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   119,   106,     8,     9,
      10,     6,     7,    23,    24,    16,    17,    18,    19,    14,
      15,    20,    22,    21,    27,    28,    49,    45,    47,    45,
      45,    42,   153,    42,   122,   161,    39,    43,   140,   142,
     149,   150,    40,    47,    40,    47,    44,   151,   152,    88,
      46,    46,    46,    39,   138,    45,    42,   131,    45,   125,
     136,   137,   140,   138,    40,    39,   142,   149,    40,    47,
      44,    47,   120,   120,    46,   153,   120,    56,   122,   162,
     165,    45,    45,   120,   148,    44,    43,   103,   120,    24,
      87,   120,    23,   153,    88,    40,    99,   118,   120,    88,
     118,   106,   106,   106,   107,   107,   108,   108,   109,   109,
     109,   109,   110,   110,   111,   112,   113,   114,   115,   120,
     118,    42,    40,   144,   149,    44,   121,   150,    39,    43,
     146,    88,    42,    47,    39,    40,   145,    45,    47,   160,
     106,   176,    39,   160,   172,   173,    11,    88,    40,    40,
     153,    40,    39,   162,    40,    40,   106,   120,    39,    43,
     102,   120,    87,   120,    40,    47,    44,    46,    40,    40,
      44,    40,   144,    44,   121,    42,   151,    40,   160,    40,
     137,    47,    40,   145,   160,    25,   174,   153,   153,   153,
     120,    40,   120,   153,    44,    40,    99,   120,   118,   117,
      40,    44,   160,   160,    40,   127,    52,    40,   153,    40,
      40,    44,   153,    45,   153
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    97,    97,    97,    98,    98,    98,    98,    98,    98,
      98,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   101,   102,   102,   102,   103,   103,   104,   104,
     105,   105,   105,   105,   105,   105,   106,   106,   107,   107,
     107,   107,   108,   108,   108,   109,   109,   109,   110,   110,
     110,   110,   110,   111,   111,   111,   112,   112,   113,   113,
     114,   114,   115,   115,   116,   116,   117,   117,   118,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   120,   120,   121,   122,   122,   123,   123,   123,   123,
     123,   123,   124,   124,   125,   125,   126,   126,   126,   127,
     127,   127,   127,   127,   127,   127,   127,   128,   128,   129,
     129,   130,   130,   131,   131,   132,   132,   132,   133,   133,
     133,   133,   133,   133,   133,   134,   134,   135,   136,   136,
     137,   138,   138,   138,   138,   139,   140,   140,   141,   141,
     141,   141,   141,   141,   141,   142,   142,   142,   142,   143,
     143,   144,   145,   145,   146,   146,   146,   147,   147,   148,
     148,   149,   149,   149,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   151,   151,   151,   152,   152,   153,   153,
     153,   153,   153,   153,   153,   154,   154,   155,   156,   156,
     156,   156,   157,   158,   158,   159,   159,   159,   160,   160,
     160,   160,   161,   161,   162,   162,   163,   163,   163,   164,
     164,   164,   164,   164,   165,   165,   166,   166,   166,   166,
     166,   167,   167,   168,   168,   168,   169,   169,   170,   170,
     171,   171,   172,   173,   173,   174,   174,   175,   175,   175,
     175,   175,   176,   176
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     4,     0,     2,     3,     3,     4,     4,     2,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     5,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     3,     1,     2,     1,     2,
       1,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     2,     1,
       1,     1,     2,     1,     1,     2,     2,     2,     3,     2,
       3,     2,     1,     1,     1,     5,     4,     5,     1,     3,
       1,     2,     1,     2,     1,     1,     2,     1,     1,     3,
       4,     3,     4,     4,     3,     1,     2,     2,     3,     1,
       2,     1,     1,     3,     2,     2,     1,     1,     3,     1,
       2,     1,     1,     2,     3,     2,     3,     3,     4,     2,
       3,     3,     4,     1,     3,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     2,
       3,     3,     2,     2,     3,     3,     4,     3,     2,     3,
       3,     4,     1,     2,     1,     2,     5,     7,     5,     5,
       5,     7,     6,     7,     1,     1,     3,     2,     2,     2,
       3,     1,     2,     1,     2,     1,     1,     2,     3,     2,
       5,     4,     2,     2,     3,     0,     2,     0,     1,     1,
       3,     3,     1,     3
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

#line 1905 "cpp.tab.c"

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

#line 559 "cpp.y"


int main(){
    return 0;
}
