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
  YYSYMBOL_YYACCEPT = 94,                  /* $accept  */
  YYSYMBOL_primary_expression = 95,        /* primary_expression  */
  YYSYMBOL_constant = 96,                  /* constant  */
  YYSYMBOL_postfix_expression = 97,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 98,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 99,          /* unary_expression  */
  YYSYMBOL_delete_expression = 100,        /* delete_expression  */
  YYSYMBOL_unary_operator = 101,           /* unary_operator  */
  YYSYMBOL_cast_expression = 102,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 103, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 104,      /* additive_expression  */
  YYSYMBOL_shift_expression = 105,         /* shift_expression  */
  YYSYMBOL_relational_expression = 106,    /* relational_expression  */
  YYSYMBOL_equality_expression = 107,      /* equality_expression  */
  YYSYMBOL_and_expression = 108,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 109,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 110,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 111,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 112,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 113,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 114,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 115,      /* assignment_operator  */
  YYSYMBOL_expression = 116,               /* expression  */
  YYSYMBOL_constant_expression = 117,      /* constant_expression  */
  YYSYMBOL_declaration = 118,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 119,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 120,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 121,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 122,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 123,           /* type_specifier  */
  YYSYMBOL_struct_or_class_specifier = 124, /* struct_or_class_specifier  */
  YYSYMBOL_struct_or_class = 125,          /* struct_or_class  */
  YYSYMBOL_struct_or_class_member_list = 126, /* struct_or_class_member_list  */
  YYSYMBOL_struct_or_class_member = 127,   /* struct_or_class_member  */
  YYSYMBOL_access_specifier_label = 128,   /* access_specifier_label  */
  YYSYMBOL_member_declaration = 129,       /* member_declaration  */
  YYSYMBOL_constructor_definition = 130,   /* constructor_definition  */
  YYSYMBOL_destructor_definition = 131,    /* destructor_definition  */
  YYSYMBOL_struct_declarator_list = 132,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 133,        /* struct_declarator  */
  YYSYMBOL_specifier_qualifier_list = 134, /* specifier_qualifier_list  */
  YYSYMBOL_type_qualifier = 135,           /* type_qualifier  */
  YYSYMBOL_declarator = 136,               /* declarator  */
  YYSYMBOL_direct_declarator = 137,        /* direct_declarator  */
  YYSYMBOL_pointer = 138,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 139,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 140,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 141,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 142,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 143,          /* identifier_list  */
  YYSYMBOL_type_name = 144,                /* type_name  */
  YYSYMBOL_abstract_declarator = 145,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 146, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 147,              /* initializer  */
  YYSYMBOL_initializer_list = 148,         /* initializer_list  */
  YYSYMBOL_statement = 149,                /* statement  */
  YYSYMBOL_labeled_statement = 150,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 151,       /* compound_statement  */
  YYSYMBOL_statement_list = 152,           /* statement_list  */
  YYSYMBOL_expression_statement = 153,     /* expression_statement  */
  YYSYMBOL_selection_statement = 154,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 155,      /* iteration_statement  */
  YYSYMBOL_for_init_statement = 156,       /* for_init_statement  */
  YYSYMBOL_jump_statement = 157,           /* jump_statement  */
  YYSYMBOL_translation_unit = 158,         /* translation_unit  */
  YYSYMBOL_external_declaration = 159,     /* external_declaration  */
  YYSYMBOL_declaration_list = 160,         /* declaration_list  */
  YYSYMBOL_function_definition = 161,      /* function_definition  */
  YYSYMBOL_lambda_expression = 162,        /* lambda_expression  */
  YYSYMBOL_lambda_declarator = 163,        /* lambda_declarator  */
  YYSYMBOL_lambda_parameter_clause = 164,  /* lambda_parameter_clause  */
  YYSYMBOL_trailing_return_opt = 165,      /* trailing_return_opt  */
  YYSYMBOL_lambda_capture_clause = 166,    /* lambda_capture_clause  */
  YYSYMBOL_capture_list = 167              /* capture_list  */
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
#define YYLAST   1815

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  235
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  391

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   348


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
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    60,    60,    61,    62,    63,    67,    68,    69,    70,
      71,    72,    73,    74,    78,    79,    80,    81,    82,    83,
      84,    85,    89,    90,    94,    95,    96,    97,    98,    99,
     100,   120,   121,   125,   126,   127,   128,   129,   130,   134,
     135,   139,   140,   141,   142,   146,   147,   148,   152,   153,
     154,   158,   159,   160,   161,   162,   166,   167,   168,   172,
     173,   177,   178,   182,   183,   187,   188,   192,   193,   197,
     198,   202,   203,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   221,   222,   226,   230,   231,   235,
     236,   237,   238,   239,   240,   244,   245,   249,   250,   254,
     255,   256,   260,   261,   262,   263,   264,   265,   266,   267,
     271,   272,   276,   277,   281,   282,   286,   287,   291,   292,
     293,   297,   298,   299,   300,   301,   302,   303,   307,   308,
     312,   316,   317,   321,   325,   326,   327,   328,   332,   336,
     337,   341,   342,   343,   344,   345,   346,   347,   351,   352,
     353,   354,   358,   359,   363,   367,   368,   372,   373,   374,
     378,   379,   383,   384,   388,   389,   390,   394,   395,   396,
     397,   398,   399,   400,   401,   402,   406,   407,   408,   412,
     413,   417,   418,   419,   420,   421,   422,   427,   428,   429,
     433,   434,   435,   436,   440,   441,   445,   446,   450,   451,
     452,   456,   457,   458,   459,   460,   464,   465,   469,   470,
     471,   472,   473,   477,   478,   482,   483,   484,   488,   489,
     493,   494,   498,   499,   503,   507,   508,   512,   513,   517,
     518,   519,   520,   521,   525,   526
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
  "EXPONENT_LITERAL", "CHARACTER_LITERAL", "STRING_LITERAL", "$accept",
  "primary_expression", "constant", "postfix_expression",
  "argument_expression_list", "unary_expression", "delete_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
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
  "statement", "labeled_statement", "compound_statement", "statement_list",
  "expression_statement", "selection_statement", "iteration_statement",
  "for_init_statement", "jump_statement", "translation_unit",
  "external_declaration", "declaration_list", "function_definition",
  "lambda_expression", "lambda_declarator", "lambda_parameter_clause",
  "trailing_return_opt", "lambda_capture_clause", "capture_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-236)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1517,  -236,  -236,    12,    26,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,    24,
    1738,  1738,    17,   -20,  1738,    59,    47,   -16,   569,  -236,
    -236,  -236,  -236,    12,    83,  -236,    61,  -236,    34,  -236,
    -236,  -236,    93,  -236,   311,  -236,  1602,   920,    47,  -236,
    -236,  -236,  -236,  -236,  -236,    26,   975,  -236,   178,  -236,
    -236,  -236,  1360,  1360,  -236,  -236,   533,  -236,     4,  -236,
    -236,   110,   149,  1415,    98,   158,   791,   161,   119,   176,
     182,  1030,   180,  1470,  -236,  -236,  -236,  1525,   186,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,   174,   384,  -236,  1415,
    -236,   230,   205,   192,   187,    35,   216,   220,   240,   237,
      36,  -236,  -236,    75,  -236,    24,  -236,  -236,  -236,   643,
    -236,  -236,  -236,  -236,   385,  -236,  -236,  -236,    27,   227,
     222,  -236,    44,  -236,  -236,  -236,  -236,   229,  -236,   265,
     975,  -236,  -236,  -236,   195,   239,   241,   242,   247,   226,
     244,  1615,  -236,  -236,  -236,  -236,  -236,    28,   226,  1415,
    -236,  -236,    58,    39,   250,   253,  -236,   260,   263,  1415,
    1415,   261,   791,  1415,   257,   459,   276,  -236,  -236,  -236,
     114,  1415,   533,  -236,    16,  -236,   791,  -236,  -236,   232,
    1085,  1415,   234,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,  1415,  -236,  1415,  1415,  1415,  1415,
    1415,  1415,  1415,  1415,  1415,  1415,  1415,  1415,  1415,  1415,
    1415,  1415,  1415,  1415,  1415,  -236,  1415,  -236,  -236,  -236,
    -236,   717,  1561,  1140,  -236,    -1,  -236,   115,  -236,  1738,
    -236,   238,  -236,  -236,    32,   286,  -236,  -236,  -236,  1670,
    -236,  -236,  -236,  -236,  -236,  -236,   179,  -236,    34,  -236,
    -236,  1648,   159,  -236,  1415,   245,    42,    11,    77,    78,
     791,  -236,    81,   288,  -236,  -236,  1195,  -236,  -236,    91,
     289,  1415,  -236,  -236,  -236,   100,  -236,    -7,  -236,  -236,
    -236,  -236,  -236,   230,   230,   205,   205,   192,   192,   192,
     192,   187,   187,    35,   216,   220,   240,   237,   183,  -236,
    -236,  -236,   290,   292,  -236,   284,   115,  1694,  1250,  -236,
    -236,  -236,   865,   295,    59,   103,  -236,    26,  -236,  -236,
     291,  1716,  -236,    59,   322,  -236,  -236,   791,   791,  -236,
     791,  1415,  1305,   791,  -236,  -236,  -236,  1415,  -236,  1415,
    -236,  -236,  -236,  -236,   308,  -236,   305,  -236,  -236,    59,
    -236,    59,  -236,   267,  -236,   105,  -236,   275,  -236,   299,
    -236,  -236,   108,   791,   113,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,   791,   312,  -236,   791,  -236,  -236,
    -236
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    99,   109,   148,     0,   102,   104,   106,   103,   107,
     108,   105,   101,   100,   138,   113,   112,   141,   217,     0,
      89,    91,     0,     0,    93,     0,   140,     0,     0,   213,
     215,   152,   150,   149,     0,    87,     0,    95,    97,    90,
      92,   216,   111,    94,     0,   221,     0,     0,   139,     1,
     214,   153,   151,   142,    88,     0,     0,   220,     0,    35,
      36,    34,     0,     0,    33,    38,     0,   190,   229,   196,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    12,    13,    11,     0,     2,     6,
      10,     9,     7,     8,    14,     3,    24,    39,    30,     0,
      41,    45,    48,    51,    56,    59,    61,    63,    65,    67,
      69,    71,    84,     0,   218,     0,   194,   181,   182,     0,
     183,   184,   185,   186,     0,     5,   147,   160,   159,     0,
     154,   155,     0,   144,     2,    39,    86,     0,    96,    97,
       0,   176,    98,   125,     0,     0,     0,     0,     0,   135,
       0,     0,   114,   116,   117,   126,   127,     0,   137,     0,
      25,    26,     0,   162,     0,   230,   234,     0,   231,     0,
       0,     0,     0,     0,     0,     0,     0,   209,   210,   211,
       0,     0,     0,    28,     0,    31,     0,    20,    21,     0,
       0,     0,     0,    73,    77,    78,    74,    75,    76,    81,
      83,    82,    79,    80,     0,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   197,     0,   191,   195,   192,
     219,     0,     0,     0,   157,   164,   158,   165,   145,     0,
     146,     0,   143,   179,     0,     0,   118,   119,   120,     0,
     134,   124,   110,   115,   122,   133,     0,   131,    97,   136,
       4,     0,   164,   163,     0,     0,     0,     0,     0,     0,
       0,   189,     0,     0,   207,   206,     0,   208,   212,     0,
       0,     0,   187,    19,    16,     0,    22,     0,    18,    72,
      42,    43,    44,    46,    47,    49,    50,    53,    52,    54,
      55,    57,    58,    60,    62,    64,    66,    68,     0,    85,
     193,   172,     0,     0,   168,     0,   166,     0,     0,   156,
     161,   177,     0,     0,     0,     0,   121,     0,   123,    40,
     233,     0,   223,     0,   227,   232,   235,     0,     0,   188,
       0,     0,     0,     0,    29,    32,    17,     0,    15,     0,
     173,   167,   169,   174,     0,   170,     0,   178,   180,     0,
     129,     0,   132,     0,   225,     0,   222,     0,   224,   198,
     200,   201,     0,     0,     0,   202,    23,    70,   175,   171,
     130,   128,   226,   228,     0,     0,   204,     0,   199,   203,
     205
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -236,  -236,  -236,  -236,  -236,   -44,  -236,  -236,   -71,    25,
      60,    38,    64,   139,   140,   138,   141,   173,  -236,   -43,
      -8,  -236,   -40,   -48,   -36,    33,  -236,   -50,  -236,   -56,
     -41,  -236,  -236,   255,  -236,  -236,  -236,  -236,  -236,    80,
     -55,    43,    52,   -21,    18,  -236,   -39,  -235,   169,  -236,
     228,  -104,  -204,  -131,  -236,   -75,  -236,   -25,   285,  -163,
    -236,  -236,  -236,  -236,  -236,   395,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,   147
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    94,    95,    96,   285,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   204,   113,   137,    18,   128,    36,    37,    20,    21,
      22,    23,   151,   152,   153,   154,   155,   156,   256,   257,
     157,    24,   139,    26,    27,    33,   312,   130,   131,   132,
     164,   313,   237,   142,   244,   116,   117,   118,   119,   120,
     121,   122,   276,   123,    28,    29,   124,    30,   125,   333,
     334,   368,   167,   168
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,   174,   149,   135,   136,   138,    48,   129,   114,   243,
     149,   163,   275,    57,   325,   165,   185,   150,   160,   161,
       3,    32,   335,     4,   236,   171,   162,   165,   205,   135,
     136,   316,     3,    19,     3,     3,     3,   348,   232,   183,
     226,   180,   233,   135,   228,    56,    31,     3,   141,   217,
     218,    52,    25,    39,    40,   135,    34,    43,   316,   263,
     281,    19,    41,     4,   223,     4,   232,     4,    42,    35,
     233,    38,    17,   254,   321,    44,    51,   115,   261,   322,
      25,   331,   233,    44,   240,   224,    46,    17,   230,    14,
      47,   241,   166,   149,   250,   149,   365,   271,   260,   336,
      44,   158,   149,   259,   166,   226,    54,   255,    55,   158,
     150,   282,    17,   342,    17,    17,    17,   337,   338,   162,
     225,   340,   226,    53,   226,   226,   149,   163,   226,   268,
     269,   343,   141,   272,    58,   290,   291,   292,   226,   274,
     346,   279,   162,   361,   172,   382,   235,   347,   385,   169,
     239,   287,   239,   387,   317,   226,   228,   115,   318,   278,
     226,   226,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     234,   262,   286,     2,   308,   315,   187,   188,   170,   135,
     136,   358,   158,   329,   158,   339,   289,   173,   261,   189,
     175,   158,   233,   213,   214,   215,   216,   176,   115,   258,
     345,   209,   210,   190,    48,   211,   212,   191,   309,   181,
     135,   177,   192,   143,   326,   158,   327,   178,   144,   349,
     226,     2,   186,   328,   293,   294,   219,   135,   206,   207,
     208,   332,   220,     5,     6,     7,     8,     9,    10,    11,
     235,   297,   298,   299,   300,    14,    15,    16,   145,   146,
     147,   221,   369,   370,   222,   371,   148,   238,   375,   239,
     356,   295,   296,   242,   135,   136,    56,   255,   354,   262,
       2,   301,   302,   245,    34,   246,   249,   247,   248,   251,
     264,     5,     6,     7,     8,     9,    10,    11,   386,   360,
     265,   372,   374,    14,   266,   135,   377,   270,   366,   388,
     267,   383,   390,   273,   141,     1,     2,    59,    60,    61,
     283,   277,   288,    62,    63,   323,   320,   341,   352,   344,
     350,    64,   351,   166,   380,   359,   381,    65,   363,   376,
       5,     6,     7,     8,     9,    10,    11,   367,   378,   379,
      66,   384,    44,    67,    68,   336,    69,   389,   303,   305,
     304,    70,    71,   306,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     5,     6,     7,     8,
       9,    10,    11,    84,    85,    86,    12,    13,    14,     1,
       2,    59,    60,    61,    87,   193,   307,    62,    63,    88,
      89,    90,    91,    92,    93,    64,   253,   362,   319,   231,
     280,    65,   330,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,    50,    66,     0,    44,   229,    68,     0,
      69,     0,     0,     0,     0,    70,    71,     0,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       5,     6,     7,     8,     9,    10,    11,    84,    85,    86,
      12,    13,    14,     1,     2,    59,    60,    61,    87,     0,
       0,    62,    63,    88,    89,    90,    91,    92,    93,    64,
       0,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,     0,
       0,     0,    68,     0,    69,     0,     0,     0,     0,    70,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    83,     5,     6,     7,     8,     9,    10,
      11,    84,    85,    86,    12,    13,    14,     0,     2,    59,
      60,    61,    87,     0,     0,    62,    63,   134,    89,    90,
      91,    92,    93,    64,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,    66,     1,     2,     0,    68,     3,     0,     0,
       0,     0,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     5,     6,
       7,     8,     9,    10,    11,    84,    85,    86,     4,     0,
      14,     0,     0,     0,     0,     0,    87,     0,     0,     0,
       0,   134,    89,    90,    91,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,    12,    13,    14,    15,    16,    59,
      60,    61,     0,     0,     0,    62,    63,    17,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,    65,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     0,    44,   227,    68,     0,    69,     0,
       0,     0,     0,    70,    71,     0,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,     0,     0,
       0,     0,     0,     0,     0,    84,    85,    86,     0,     0,
       0,     0,     0,    59,    60,    61,    87,     0,     0,    62,
      63,    88,    89,    90,    91,    92,    93,    64,     0,     0,
       0,     0,     0,    65,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,    44,   310,
      68,     0,    69,     0,     0,     0,     0,    70,    71,     0,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,     0,     0,     0,     0,     0,     0,     0,    84,
      85,    86,     0,     0,     0,     0,     0,    59,    60,    61,
      87,     0,     0,    62,    63,    88,    89,    90,    91,    92,
      93,    64,     0,     0,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,     0,    44,     0,    68,     0,    69,     0,     0,     0,
       0,    70,    71,     0,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     0,     0,     0,     0,
       0,     0,     0,    84,    85,    86,     0,     0,     0,     0,
       0,    59,    60,    61,    87,     0,     0,    62,    63,    88,
      89,    90,    91,    92,    93,    64,     0,     0,     0,     0,
       0,    65,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,     0,   140,   357,    68,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,    61,    83,
       0,     0,    62,    63,     0,     0,     0,    84,    85,    86,
      64,     0,     0,     0,     0,     0,    65,     0,    87,     0,
       0,     0,     0,   134,    89,    90,    91,    92,    93,    66,
       0,     0,     0,    68,   133,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,    61,    83,     0,     0,    62,    63,     0,
       0,     0,    84,    85,    86,    64,     0,     0,     0,     0,
       0,    65,     0,    87,     0,     0,     0,     0,   134,    89,
      90,    91,    92,    93,    66,     0,   140,     0,    68,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,    61,    83,
       0,     0,    62,    63,     0,     0,     0,    84,    85,    86,
      64,     0,     0,     0,     0,     0,    65,     0,    87,     0,
       0,     0,     0,   134,    89,    90,    91,    92,    93,    66,
       0,     0,     0,    68,     0,   179,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,    61,    83,     0,     0,    62,    63,     0,
       0,     0,    84,    85,    86,    64,     0,     0,     0,     0,
       0,    65,     0,    87,     0,     0,     0,     0,   134,    89,
      90,    91,    92,    93,    66,   284,     0,     0,    68,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,    61,    83,
       0,     0,    62,    63,     0,     0,     0,    84,    85,    86,
      64,     0,     0,     0,     0,     0,    65,     0,    87,     0,
       0,     0,     0,   134,    89,    90,    91,    92,    93,    66,
       0,     0,     0,    68,   314,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,    61,    83,     0,     0,    62,    63,     0,
       0,     0,    84,    85,    86,    64,     0,     0,     0,     0,
       0,    65,     0,    87,     0,     0,     0,     0,   134,    89,
      90,    91,    92,    93,    66,     0,     0,     0,    68,     0,
      69,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,    61,    83,
       0,     0,    62,    63,     0,     0,     0,    84,    85,    86,
      64,     0,     0,     0,     0,     0,    65,     0,    87,     0,
       0,     0,     0,   134,    89,    90,    91,    92,    93,    66,
       0,     0,     0,    68,   355,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,    61,    83,     0,     0,    62,    63,     0,
       0,     0,    84,    85,    86,    64,     0,     0,     0,     0,
       0,    65,     0,    87,     0,     0,     0,     0,   134,    89,
      90,    91,    92,    93,    66,   373,     0,     0,    68,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,    61,    83,
       0,     0,    62,    63,     0,     0,     0,    84,    85,    86,
      64,     0,     0,     0,     0,     0,    65,     0,    87,     0,
       0,     0,     0,   134,    89,    90,    91,    92,    93,   159,
       0,     0,     0,    68,     0,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    59,    60,    61,    83,     0,     0,    62,    63,     0,
       0,     0,    84,    85,    86,    64,     0,     0,     0,     0,
       0,    65,     0,    87,     0,     0,     0,     0,   134,    89,
      90,    91,    92,    93,    66,     0,     0,     0,    68,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    60,    61,    83,
       0,     0,    62,    63,     0,     0,     0,    84,    85,    86,
      64,     0,     0,     0,     0,     0,    65,     0,    87,     0,
       0,     0,     0,   134,    89,    90,    91,    92,    93,   182,
       0,     0,     0,    68,     0,     0,     0,     0,     0,     0,
      70,     1,     2,     0,     0,     3,     0,     0,     0,     0,
       0,    59,    60,    61,    83,     0,     0,    62,    63,     0,
       0,     0,    84,    85,    86,    64,     0,     0,     0,     0,
       0,    65,     0,    87,     0,     0,     4,     0,   134,    89,
      90,    91,    92,    93,    66,     1,     2,     0,   184,     3,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     8,     9,    10,    11,    83,
       0,     0,    12,    13,    14,    15,    16,    84,    85,    86,
     232,   311,     0,     0,   233,    17,     1,     2,    87,     0,
       0,     0,     0,   134,    89,    90,    91,    92,    93,     0,
       2,     0,     0,     0,     0,     0,     5,     6,     7,     8,
       9,    10,    11,     0,     0,     0,    12,    13,    14,     0,
       0,     0,   126,     0,     0,     0,     0,     0,     0,    17,
       0,     0,     1,     2,     0,     0,     3,   252,     0,     0,
     143,     0,     0,     0,     0,   144,     0,     5,     6,     7,
       8,     9,    10,    11,     1,     2,     0,    12,    13,    14,
       5,     6,     7,     8,     9,    10,    11,   261,   311,     0,
     127,   233,    14,    15,    16,   145,   146,   147,     1,     2,
       0,     0,     0,   148,     0,     0,     0,     0,     0,     0,
     324,     0,     0,     5,     6,     7,     8,     9,    10,    11,
       1,     2,     0,    12,    13,    14,     0,     0,     0,     0,
       0,     0,     0,     0,   353,     5,     6,     7,     8,     9,
      10,    11,     1,     2,     0,    12,    13,    14,     0,     0,
       0,     0,     0,     0,     0,     0,   364,     0,     0,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,    12,
      13,    14,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,    12,    13,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,    12,    13,    14
};

static const yytype_int16 yycheck[] =
{
      25,    76,    58,    47,    47,    55,    27,    46,    44,   140,
      66,    66,   175,    38,   249,    11,    87,    58,    62,    63,
       8,     3,    11,    39,   128,    73,    66,    11,    99,    73,
      73,   235,     8,     0,     8,     8,     8,    44,    39,    83,
      47,    81,    43,    87,   119,    11,     3,     8,    56,    14,
      15,    33,     0,    20,    21,    99,     4,    24,   262,   163,
      44,    28,    45,    39,    28,    39,    39,    39,    88,    45,
      43,    19,    88,    45,    42,    41,    33,    44,    39,    47,
      28,    39,    43,    41,    40,    49,    39,    88,   124,    77,
      43,    47,    88,   149,   149,   151,   331,   172,    40,    88,
      41,    58,   158,   158,    88,    47,    45,   157,    47,    66,
     151,   186,    88,   276,    88,    88,    88,    40,    40,   159,
      45,    40,    47,    40,    47,    47,   182,   182,    47,   169,
     170,    40,   140,   173,    41,   206,   207,   208,    47,   175,
      40,   181,   182,    40,    46,    40,   128,    47,    40,    39,
      47,   191,    47,    40,    39,    47,   231,   124,    43,    45,
      47,    47,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     128,   163,   190,     5,   224,   233,    12,    13,    39,   233,
     233,   322,   149,   264,   151,   270,   204,    39,    39,    25,
      39,   158,    43,    16,    17,    18,    19,    88,   175,   157,
     281,     6,     7,    39,   235,    23,    24,    43,   226,    39,
     264,    45,    48,    45,    45,   182,    47,    45,    50,    46,
      47,     5,    46,   258,   209,   210,    20,   281,     8,     9,
      10,   266,    22,    65,    66,    67,    68,    69,    70,    71,
     232,   213,   214,   215,   216,    77,    78,    79,    80,    81,
      82,    21,   337,   338,    27,   340,    88,    40,   343,    47,
     318,   211,   212,    44,   318,   318,    11,   327,   317,   261,
       5,   217,   218,    88,   232,    46,    39,    46,    46,    45,
      40,    65,    66,    67,    68,    69,    70,    71,   373,   324,
      47,   341,   342,    77,    44,   349,   349,    46,   333,   384,
      47,   367,   387,    56,   322,     4,     5,     6,     7,     8,
      88,    45,    88,    12,    13,    39,    88,    39,    44,    40,
      40,    20,    40,    88,   359,    40,   361,    26,    47,   347,
      65,    66,    67,    68,    69,    70,    71,    25,    40,    44,
      39,    52,    41,    42,    43,    88,    45,    45,   219,   221,
     220,    50,    51,   222,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,     4,
       5,     6,     7,     8,    83,    11,   223,    12,    13,    88,
      89,    90,    91,    92,    93,    20,   151,   327,   239,   124,
     182,    26,   265,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    28,    39,    -1,    41,    42,    43,    -1,
      45,    -1,    -1,    -1,    -1,    50,    51,    -1,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     4,     5,     6,     7,     8,    83,    -1,
      -1,    12,    13,    88,    89,    90,    91,    92,    93,    20,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    -1,     5,     6,
       7,     8,    83,    -1,    -1,    12,    13,    88,    89,    90,
      91,    92,    93,    20,    -1,    -1,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,
      -1,    -1,    39,     4,     5,    -1,    43,     8,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    39,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,    -1,
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
      -1,    -1,    -1,     6,     7,     8,    83,    -1,    -1,    12,
      13,    88,    89,    90,    91,    92,    93,    20,    -1,    -1,
      -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    -1,    50,    51,    -1,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,
      83,    -1,    -1,    12,    13,    88,    89,    90,    91,    92,
      93,    20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,
      -1,    50,    51,    -1,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    83,    -1,    -1,    12,    13,    88,
      89,    90,    91,    92,    93,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,    64,
      -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,    74,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    39,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    64,    -1,    -1,    12,    13,    -1,
      -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    83,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    39,    -1,    41,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,    64,
      -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,    74,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    39,
      -1,    -1,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    64,    -1,    -1,    12,    13,    -1,
      -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    83,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    39,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,    64,
      -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,    74,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    39,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    64,    -1,    -1,    12,    13,    -1,
      -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    83,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    39,    -1,    -1,    -1,    43,    -1,
      45,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,    64,
      -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,    74,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    39,
      -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    64,    -1,    -1,    12,    13,    -1,
      -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    83,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    39,    40,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,    64,
      -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,    74,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    39,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    64,    -1,    -1,    12,    13,    -1,
      -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    83,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    39,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     6,     7,     8,    64,
      -1,    -1,    12,    13,    -1,    -1,    -1,    72,    73,    74,
      20,    -1,    -1,    -1,    -1,    -1,    26,    -1,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    39,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,     4,     5,    -1,    -1,     8,    -1,    -1,    -1,    -1,
      -1,     6,     7,     8,    64,    -1,    -1,    12,    13,    -1,
      -1,    -1,    72,    73,    74,    20,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    83,    -1,    -1,    39,    -1,    88,    89,
      90,    91,    92,    93,    39,     4,     5,    -1,    43,     8,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    68,    69,    70,    71,    64,
      -1,    -1,    75,    76,    77,    78,    79,    72,    73,    74,
      39,    40,    -1,    -1,    43,    88,     4,     5,    83,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
       5,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    70,    71,    -1,    -1,    -1,    75,    76,    77,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    -1,     4,     5,    -1,    -1,     8,    42,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    50,    -1,    65,    66,    67,
      68,    69,    70,    71,     4,     5,    -1,    75,    76,    77,
      65,    66,    67,    68,    69,    70,    71,    39,    40,    -1,
      88,    43,    77,    78,    79,    80,    81,    82,     4,     5,
      -1,    -1,    -1,    88,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
       4,     5,    -1,    75,    76,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    65,    66,    67,    68,    69,
      70,    71,     4,     5,    -1,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    -1,    -1,    -1,    75,
      76,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    -1,    -1,
      -1,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    68,    69,    70,    71,
      -1,    -1,    -1,    75,    76,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     5,     8,    39,    65,    66,    67,    68,    69,
      70,    71,    75,    76,    77,    78,    79,    88,   118,   119,
     122,   123,   124,   125,   135,   136,   137,   138,   158,   159,
     161,   135,   138,   139,   136,    45,   120,   121,   136,   119,
     119,    45,    88,   119,    41,   151,    39,    43,   137,     0,
     159,   135,   138,    40,    45,    47,    11,   151,    41,     6,
       7,     8,    12,    13,    20,    26,    39,    42,    43,    45,
      50,    51,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    72,    73,    74,    83,    88,    89,
      90,    91,    92,    93,    95,    96,    97,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   116,   118,   119,   149,   150,   151,   152,
     153,   154,   155,   157,   160,   162,    40,    88,   119,   140,
     141,   142,   143,    44,    88,    99,   113,   117,   121,   136,
      41,   114,   147,    45,    50,    80,    81,    82,    88,   123,
     124,   126,   127,   128,   129,   130,   131,   134,   135,    39,
      99,    99,   116,   134,   144,    11,    88,   166,   167,    39,
      39,   117,    46,    39,   149,    39,    88,    45,    45,    45,
     116,    39,    39,    99,    43,   102,    46,    12,    13,    25,
      39,    43,    48,    11,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,   115,   102,     8,     9,    10,     6,
       7,    23,    24,    16,    17,    18,    19,    14,    15,    20,
      22,    21,    27,    28,    49,    45,    47,    42,   149,    42,
     118,   152,    39,    43,   136,   138,   145,   146,    40,    47,
      40,    47,    44,   147,   148,    88,    46,    46,    46,    39,
     134,    45,    42,   127,    45,   121,   132,   133,   136,   134,
      40,    39,   138,   145,    40,    47,    44,    47,   116,   116,
      46,   149,   116,    56,   118,   153,   156,    45,    45,   116,
     144,    44,   149,    88,    40,    98,   114,   116,    88,   114,
     102,   102,   102,   103,   103,   104,   104,   105,   105,   105,
     105,   106,   106,   107,   108,   109,   110,   111,   116,   114,
      42,    40,   140,   145,    44,   117,   146,    39,    43,   142,
      88,    42,    47,    39,    40,   141,    45,    47,   151,   102,
     167,    39,   151,   163,   164,    11,    88,    40,    40,   149,
      40,    39,   153,    40,    40,   102,    40,    47,    44,    46,
      40,    40,    44,    40,   140,    44,   117,    42,   147,    40,
     151,    40,   133,    47,    40,   141,   151,    25,   165,   149,
     149,   149,   116,    40,   116,   149,   114,   113,    40,    44,
     151,   151,    40,   123,    52,    40,   149,    40,   149,    45,
     149
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    95,    95,    96,    96,    96,    96,
      96,    96,    96,    96,    97,    97,    97,    97,    97,    97,
      97,    97,    98,    98,    99,    99,    99,    99,    99,    99,
      99,   100,   100,   101,   101,   101,   101,   101,   101,   102,
     102,   103,   103,   103,   103,   104,   104,   104,   105,   105,
     105,   106,   106,   106,   106,   106,   107,   107,   107,   108,
     108,   109,   109,   110,   110,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   116,   116,   117,   118,   118,   119,
     119,   119,   119,   119,   119,   120,   120,   121,   121,   122,
     122,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     128,   129,   129,   129,   129,   129,   129,   129,   130,   130,
     131,   132,   132,   133,   134,   134,   134,   134,   135,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   138,   138,
     138,   138,   139,   139,   140,   141,   141,   142,   142,   142,
     143,   143,   144,   144,   145,   145,   145,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   147,   147,   147,   148,
     148,   149,   149,   149,   149,   149,   149,   150,   150,   150,
     151,   151,   151,   151,   152,   152,   153,   153,   154,   154,
     154,   155,   155,   155,   155,   155,   156,   156,   157,   157,
     157,   157,   157,   158,   158,   159,   159,   159,   160,   160,
     161,   161,   162,   162,   163,   164,   164,   165,   165,   166,
     166,   166,   166,   166,   167,   167
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     2,     3,     1,
       2,     1,     2,     1,     2,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     2,     1,     1,     1,     2,     1,     1,     2,     2,
       2,     3,     2,     3,     2,     1,     1,     1,     5,     4,
       5,     1,     3,     1,     2,     1,     2,     1,     1,     2,
       1,     1,     3,     4,     3,     4,     4,     3,     1,     2,
       2,     3,     1,     2,     1,     1,     3,     2,     2,     1,
       1,     3,     1,     2,     1,     1,     2,     3,     2,     3,
       3,     4,     2,     3,     3,     4,     1,     3,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     4,     3,
       2,     3,     3,     4,     1,     2,     1,     2,     5,     7,
       5,     5,     5,     7,     6,     7,     1,     1,     3,     2,
       2,     2,     3,     1,     2,     1,     2,     1,     1,     2,
       3,     2,     5,     4,     2,     2,     3,     0,     2,     0,
       1,     1,     3,     3,     1,     3
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

#line 1829 "cpp.tab.c"

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

#line 530 "cpp.y"


int main(){
    return 0;
}
