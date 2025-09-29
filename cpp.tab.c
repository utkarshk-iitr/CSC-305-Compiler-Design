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
  YYSYMBOL_PLUS = 5,                       /* PLUS  */
  YYSYMBOL_MINUS = 6,                      /* MINUS  */
  YYSYMBOL_STAR = 7,                       /* STAR  */
  YYSYMBOL_DIVIDE = 8,                     /* DIVIDE  */
  YYSYMBOL_MODULUS = 9,                    /* MODULUS  */
  YYSYMBOL_ASSIGN = 10,                    /* ASSIGN  */
  YYSYMBOL_INCREMENT = 11,                 /* INCREMENT  */
  YYSYMBOL_DECREMENT = 12,                 /* DECREMENT  */
  YYSYMBOL_EQUAL = 13,                     /* EQUAL  */
  YYSYMBOL_NOT_EQUAL = 14,                 /* NOT_EQUAL  */
  YYSYMBOL_LESS_THAN = 15,                 /* LESS_THAN  */
  YYSYMBOL_GREATER_THAN = 16,              /* GREATER_THAN  */
  YYSYMBOL_LESS_EQUAL = 17,                /* LESS_EQUAL  */
  YYSYMBOL_GREATER_EQUAL = 18,             /* GREATER_EQUAL  */
  YYSYMBOL_BITWISE_AND = 19,               /* BITWISE_AND  */
  YYSYMBOL_BITWISE_OR = 20,                /* BITWISE_OR  */
  YYSYMBOL_BITWISE_XOR = 21,               /* BITWISE_XOR  */
  YYSYMBOL_LEFT_SHIFT = 22,                /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 23,               /* RIGHT_SHIFT  */
  YYSYMBOL_ARROW = 24,                     /* ARROW  */
  YYSYMBOL_LOGICAL_NOT = 25,               /* LOGICAL_NOT  */
  YYSYMBOL_LOGICAL_AND = 26,               /* LOGICAL_AND  */
  YYSYMBOL_LOGICAL_OR = 27,                /* LOGICAL_OR  */
  YYSYMBOL_PLUS_EQUAL = 28,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 29,               /* MINUS_EQUAL  */
  YYSYMBOL_STAR_EQUAL = 30,                /* STAR_EQUAL  */
  YYSYMBOL_DIV_EQUAL = 31,                 /* DIV_EQUAL  */
  YYSYMBOL_MOD_EQUAL = 32,                 /* MOD_EQUAL  */
  YYSYMBOL_AND_EQUAL = 33,                 /* AND_EQUAL  */
  YYSYMBOL_OR_EQUAL = 34,                  /* OR_EQUAL  */
  YYSYMBOL_XOR_EQUAL = 35,                 /* XOR_EQUAL  */
  YYSYMBOL_LEFT_SHIFT_EQ = 36,             /* LEFT_SHIFT_EQ  */
  YYSYMBOL_RIGHT_SHIFT_EQ = 37,            /* RIGHT_SHIFT_EQ  */
  YYSYMBOL_LROUND = 38,                    /* LROUND  */
  YYSYMBOL_RROUND = 39,                    /* RROUND  */
  YYSYMBOL_LCURLY = 40,                    /* LCURLY  */
  YYSYMBOL_RCURLY = 41,                    /* RCURLY  */
  YYSYMBOL_LSQUARE = 42,                   /* LSQUARE  */
  YYSYMBOL_RSQUARE = 43,                   /* RSQUARE  */
  YYSYMBOL_SEMICOLON = 44,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 45,                     /* COLON  */
  YYSYMBOL_COMMA = 46,                     /* COMMA  */
  YYSYMBOL_DOT = 47,                       /* DOT  */
  YYSYMBOL_QUESTION_MARK = 48,             /* QUESTION_MARK  */
  YYSYMBOL_TILDE = 49,                     /* TILDE  */
  YYSYMBOL_IF = 50,                        /* IF  */
  YYSYMBOL_ELSE = 51,                      /* ELSE  */
  YYSYMBOL_SWITCH = 52,                    /* SWITCH  */
  YYSYMBOL_CASE = 53,                      /* CASE  */
  YYSYMBOL_DEFAULT = 54,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 55,                     /* WHILE  */
  YYSYMBOL_DO = 56,                        /* DO  */
  YYSYMBOL_FOR = 57,                       /* FOR  */
  YYSYMBOL_GOTO = 58,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 59,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 60,                     /* BREAK  */
  YYSYMBOL_RETURN = 61,                    /* RETURN  */
  YYSYMBOL_UNTIL = 62,                     /* UNTIL  */
  YYSYMBOL_SIZEOF = 63,                    /* SIZEOF  */
  YYSYMBOL_VOID = 64,                      /* VOID  */
  YYSYMBOL_INT = 65,                       /* INT  */
  YYSYMBOL_DOUBLE = 66,                    /* DOUBLE  */
  YYSYMBOL_CHAR = 67,                      /* CHAR  */
  YYSYMBOL_BOOL = 68,                      /* BOOL  */
  YYSYMBOL_STRING = 69,                    /* STRING  */
  YYSYMBOL_LONG = 70,                      /* LONG  */
  YYSYMBOL_TRUE = 71,                      /* TRUE  */
  YYSYMBOL_FALSE = 72,                     /* FALSE  */
  YYSYMBOL_NULLPTR = 73,                   /* NULLPTR  */
  YYSYMBOL_AUTO = 74,                      /* AUTO  */
  YYSYMBOL_STATIC = 75,                    /* STATIC  */
  YYSYMBOL_CONST = 76,                     /* CONST  */
  YYSYMBOL_CLASS = 77,                     /* CLASS  */
  YYSYMBOL_STRUCT = 78,                    /* STRUCT  */
  YYSYMBOL_PUBLIC = 79,                    /* PUBLIC  */
  YYSYMBOL_PRIVATE = 80,                   /* PRIVATE  */
  YYSYMBOL_PROTECTED = 81,                 /* PROTECTED  */
  YYSYMBOL_DELETE = 82,                    /* DELETE  */
  YYSYMBOL_NEW = 83,                       /* NEW  */
  YYSYMBOL_CIN = 84,                       /* CIN  */
  YYSYMBOL_COUT = 85,                      /* COUT  */
  YYSYMBOL_ENDL = 86,                      /* ENDL  */
  YYSYMBOL_IDENTIFIER = 87,                /* IDENTIFIER  */
  YYSYMBOL_DECIMAL_LITERAL = 88,           /* DECIMAL_LITERAL  */
  YYSYMBOL_DOUBLE_LITERAL = 89,            /* DOUBLE_LITERAL  */
  YYSYMBOL_EXPONENT_LITERAL = 90,          /* EXPONENT_LITERAL  */
  YYSYMBOL_CHARACTER_LITERAL = 91,         /* CHARACTER_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 92,            /* STRING_LITERAL  */
  YYSYMBOL_FUNCTION = 93,                  /* FUNCTION  */
  YYSYMBOL_CONSTANT = 94,                  /* CONSTANT  */
  YYSYMBOL_YYACCEPT = 95,                  /* $accept  */
  YYSYMBOL_primary_expression = 96,        /* primary_expression  */
  YYSYMBOL_constant = 97,                  /* constant  */
  YYSYMBOL_postfix_expression = 98,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 99,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 100,         /* unary_expression  */
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
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1831

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  95
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  234
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  389

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
       0,    47,    47,    48,    49,    50,    54,    55,    56,    57,
      58,    59,    60,    61,    65,    66,    67,    68,    69,    70,
      71,    72,    76,    77,    81,    82,    83,    84,    85,    86,
      90,    91,    92,    93,    94,    95,    99,   100,   104,   105,
     106,   107,   111,   112,   113,   117,   118,   119,   123,   124,
     125,   126,   127,   131,   132,   133,   137,   138,   142,   143,
     147,   148,   152,   153,   157,   158,   162,   163,   167,   168,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   186,   187,   191,   195,   196,   200,   201,   202,   203,
     204,   205,   209,   210,   214,   215,   219,   220,   221,   225,
     226,   227,   228,   229,   230,   231,   232,   236,   237,   241,
     242,   246,   247,   251,   252,   256,   257,   258,   262,   263,
     264,   265,   266,   267,   268,   269,   273,   274,   278,   282,
     283,   287,   291,   292,   293,   294,   298,   302,   303,   307,
     308,   309,   310,   311,   312,   313,   314,   318,   319,   320,
     321,   325,   326,   330,   334,   335,   339,   340,   341,   345,
     346,   350,   351,   355,   356,   357,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   373,   374,   375,   379,   380,
     384,   385,   386,   387,   388,   389,   410,   411,   412,   416,
     417,   418,   419,   423,   424,   428,   429,   433,   434,   435,
     439,   440,   441,   442,   443,   447,   448,   452,   453,   454,
     455,   456,   460,   461,   465,   466,   467,   471,   472,   476,
     477,   481,   482,   486,   490,   491,   495,   496,   500,   501,
     502,   503,   504,   508,   509
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
  "PLUS", "MINUS", "STAR", "DIVIDE", "MODULUS", "ASSIGN", "INCREMENT",
  "DECREMENT", "EQUAL", "NOT_EQUAL", "LESS_THAN", "GREATER_THAN",
  "LESS_EQUAL", "GREATER_EQUAL", "BITWISE_AND", "BITWISE_OR",
  "BITWISE_XOR", "LEFT_SHIFT", "RIGHT_SHIFT", "ARROW", "LOGICAL_NOT",
  "LOGICAL_AND", "LOGICAL_OR", "PLUS_EQUAL", "MINUS_EQUAL", "STAR_EQUAL",
  "DIV_EQUAL", "MOD_EQUAL", "AND_EQUAL", "OR_EQUAL", "XOR_EQUAL",
  "LEFT_SHIFT_EQ", "RIGHT_SHIFT_EQ", "LROUND", "RROUND", "LCURLY",
  "RCURLY", "LSQUARE", "RSQUARE", "SEMICOLON", "COLON", "COMMA", "DOT",
  "QUESTION_MARK", "TILDE", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT",
  "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "UNTIL",
  "SIZEOF", "VOID", "INT", "DOUBLE", "CHAR", "BOOL", "STRING", "LONG",
  "TRUE", "FALSE", "NULLPTR", "AUTO", "STATIC", "CONST", "CLASS", "STRUCT",
  "PUBLIC", "PRIVATE", "PROTECTED", "DELETE", "NEW", "CIN", "COUT", "ENDL",
  "IDENTIFIER", "DECIMAL_LITERAL", "DOUBLE_LITERAL", "EXPONENT_LITERAL",
  "CHARACTER_LITERAL", "STRING_LITERAL", "FUNCTION", "CONSTANT", "$accept",
  "primary_expression", "constant", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
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

#define YYPACT_NINF (-233)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1533,  -233,    28,    39,   -61,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,    20,
    1753,  1753,    31,   -32,  1753,    46,    42,    -5,  1454,  -233,
    -233,  -233,  -233,    28,    58,  -233,  -233,   184,  -233,    14,
    -233,  -233,  -233,  -233,    74,  -233,   310,  -233,  1557,   913,
      42,  -233,  -233,  -233,  -233,  -233,  -233,    39,   968,  -233,
    1642,  -233,  -233,  -233,  1353,  1353,  -233,  -233,   784,  -233,
       3,  -233,  -233,    82,    95,  1408,    94,   104,   710,   112,
      60,   135,   140,  1023,   152,  1463,  -233,  -233,  -233,   161,
    -233,  -233,  -233,  -233,  -233,  -233,  -233,   191,   308,  1408,
    -233,   189,   151,   235,   203,   253,   192,   195,   194,   201,
      22,  -233,  -233,   190,  -233,    20,  -233,  -233,  -233,   562,
    -233,  -233,  -233,  -233,   399,  -233,  -233,  -233,    29,   196,
     185,  -233,     2,  -233,  -233,  -233,  -233,   208,  -233,   243,
     968,  -233,  -233,  -233,   174,   219,   228,   233,   247,   178,
     242,  1598,  -233,  -233,  -233,  -233,  -233,    30,   178,    46,
    1408,  -233,  -233,    11,    24,   248,   244,  -233,   245,   246,
    1408,  1408,   250,   710,  1408,   234,   488,   249,  -233,  -233,
    -233,   193,  1408,   784,  -233,   710,  -233,  -233,   204,  1078,
    1408,   210,  -233,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,  -233,  1408,  -233,  1408,  1408,  1408,  1408,  1408,
    1408,  1408,  1408,  1408,  1408,  1408,  1408,  1408,  1408,  1408,
    1408,  1408,  1408,  1408,  -233,  1408,  -233,  -233,  -233,  -233,
     636,  1500,  1133,  -233,    45,  -233,   167,  -233,  1753,  -233,
     212,  -233,  -233,   -16,   264,  -233,  -233,  -233,  1666,  -233,
    -233,  -233,  -233,  -233,  -233,   206,  -233,    14,  -233,  -233,
    -233,  1686,   170,  -233,  1408,   216,    23,    12,    73,    79,
     710,  -233,    89,   266,  -233,  -233,  1188,  -233,  -233,    90,
     267,  -233,  -233,  -233,    91,  -233,    63,  -233,  -233,  -233,
    -233,  -233,   189,   189,   151,   151,   235,   235,   235,   235,
     203,   203,   253,   192,   195,   194,   201,   223,  -233,  -233,
    -233,   271,   272,  -233,   269,   167,  1709,  1243,  -233,  -233,
    -233,   858,   274,    46,    92,  -233,    39,  -233,  -233,   273,
    1733,  -233,    46,   296,  -233,  -233,   710,   710,  -233,   710,
    1408,  1298,   710,  -233,  -233,  1408,  -233,  1408,  -233,  -233,
    -233,  -233,   284,  -233,   281,  -233,  -233,    46,  -233,    46,
    -233,   238,  -233,   105,  -233,   450,  -233,   275,  -233,  -233,
     106,   710,   109,  -233,  -233,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,   710,   283,  -233,   710,  -233,  -233,  -233
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    96,   147,     0,     0,    99,   101,   103,   100,   104,
     105,   102,    98,    97,   136,   110,   109,   139,   216,     0,
      86,    88,   106,     0,    90,     0,   138,     0,     0,   212,
     214,   151,   149,   148,     0,   140,    84,     0,    92,    94,
      87,   106,    89,   215,   108,    91,     0,   220,     0,     0,
     137,     1,   213,   152,   150,   141,    85,     0,     0,   219,
       0,    32,    33,    31,     0,     0,    30,    35,     0,   189,
     228,   195,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    13,    11,     2,
       6,    10,     9,     7,     8,    14,     3,    24,    36,     0,
      38,    42,    45,    48,    53,    56,    58,    60,    62,    64,
      66,    68,    81,     0,   217,     0,   193,   180,   181,     0,
     182,   183,   184,   185,     0,     5,   146,   159,   158,     0,
     153,   154,     0,   143,     2,    36,    83,     0,    93,    94,
       0,   175,    95,   123,     0,     0,     0,     0,   139,   133,
     106,     0,   111,   113,   114,   124,   125,     0,   135,     0,
       0,    25,    26,     0,   161,     0,   229,   233,     0,   230,
       0,     0,     0,     0,     0,     0,     0,     0,   208,   209,
     210,     0,     0,     0,    28,     0,    20,    21,     0,     0,
       0,     0,    70,    74,    75,    71,    72,    73,    78,    80,
      79,    76,    77,     0,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   196,     0,   190,   194,   191,   218,
       0,     0,     0,   156,   163,   157,   164,   144,     0,   145,
       0,   142,   178,     0,   140,   115,   116,   117,     0,   132,
     122,   107,   112,   119,   131,     0,   129,    94,   134,   120,
       4,     0,   163,   162,     0,     0,     0,     0,     0,     0,
       0,   188,     0,     0,   206,   205,     0,   207,   211,     0,
       0,   186,    19,    16,     0,    22,     0,    18,    69,    39,
      40,    41,    43,    44,    46,    47,    50,    49,    51,    52,
      54,    55,    57,    59,    61,    63,    65,     0,    82,   192,
     171,     0,     0,   167,     0,   165,     0,     0,   155,   160,
     176,     0,     0,     0,     0,   118,     0,   121,    37,   232,
       0,   222,     0,   226,   231,   234,     0,     0,   187,     0,
       0,     0,     0,    29,    17,     0,    15,     0,   172,   166,
     168,   173,     0,   169,     0,   177,   179,     0,   127,     0,
     130,     0,   224,     0,   221,     0,   223,   197,   199,   200,
       0,     0,     0,   201,    23,    67,   174,   170,   128,   126,
     225,   227,     0,     0,   203,     0,   198,   202,   204
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -233,  -233,  -233,  -233,  -233,   -47,  -233,   -84,    68,    70,
      10,    66,   110,   111,   113,   125,   127,  -233,   -46,   -49,
    -233,    17,   -54,   -35,    19,  -233,   -52,  -233,   -56,    32,
    -233,  -233,   180,  -233,  -233,  -233,  -233,  -233,    21,   -34,
      43,    53,   -21,    18,  -233,   -41,  -232,   115,  -233,   172,
    -105,  -161,  -132,  -233,   -77,  -233,   -25,   232,  -166,  -233,
    -233,  -233,  -233,  -233,   333,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,   124
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    95,    96,    97,   284,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     203,   113,   137,    18,   128,    37,    38,    20,    21,    41,
      23,   151,   152,   153,   154,   155,   156,   255,   256,   157,
      24,   139,    26,    27,    33,   311,   130,   131,   132,   165,
     312,   236,   142,   243,   116,   117,   118,   119,   120,   121,
     122,   276,   123,    28,    29,   124,    30,   125,   332,   333,
     366,   168,   169
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,   175,   135,   136,   149,   138,    50,   129,   242,   141,
     275,   114,   149,   166,    59,   204,   324,   161,   162,    19,
      32,   172,   334,   235,    58,   320,    35,     2,   135,   136,
     321,     2,    22,     3,   164,     2,     2,     2,   184,    40,
      42,   239,   227,    45,     4,    31,     2,    19,   240,   222,
     260,    54,   135,    25,    46,    44,    34,   225,     3,   263,
      22,   330,   261,    46,    36,   115,   232,   231,     3,     4,
     223,   232,    39,   315,   253,    43,    53,     3,     4,     4,
      48,    25,    17,   231,    49,   163,    46,   232,     4,   229,
     167,   141,   150,   149,     4,   149,   271,    55,   363,   335,
     181,   315,   149,   158,    14,   254,   346,    17,   281,   225,
     341,   158,   336,   159,    60,   249,    17,    17,   337,   225,
     170,   289,   290,   291,   258,   225,    17,   149,   339,   342,
     344,   359,    17,   171,   259,   225,   225,   345,   238,   173,
     285,   274,   174,   115,   380,   383,   234,   177,   385,   164,
     176,   238,   225,   227,   288,   225,   208,   209,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   308,   163,   314,   178,
     328,   233,   262,   150,   179,   135,   136,   268,   269,   356,
     182,   272,   158,   338,   158,   115,   205,   206,   207,   279,
     163,   158,   186,   187,   159,   316,   185,   286,   261,   317,
     257,   218,   232,    50,   220,   188,   219,   135,   212,   213,
     214,   215,   296,   297,   298,   299,   158,   221,    56,   189,
      57,   238,   327,   190,   224,   237,   225,   278,   191,   225,
     307,   331,     5,     6,     7,     8,     9,    10,    11,   234,
     325,   241,   326,    58,    14,    15,    16,   210,   211,   367,
     368,   244,   369,   354,   245,   373,   216,   217,   347,   225,
     135,   136,   141,   246,   254,   352,   292,   293,   247,   262,
     294,   295,   300,   301,    34,   248,   250,   264,   266,   273,
     265,   282,   267,   277,   384,   270,   374,   287,   358,   319,
     135,   375,   322,   167,   340,   386,   343,   364,   388,   381,
     348,   349,   350,   357,     1,    61,    62,    63,   192,   361,
     365,    64,    65,   376,   377,   335,   382,   387,   302,    66,
     303,   252,   378,   304,   379,    67,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   305,   360,    68,   306,
      46,    69,    70,   318,    71,   280,   230,   370,   372,    72,
      73,    52,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,     5,     6,     7,     8,     9,    10,
      11,    86,    87,    88,    12,    13,    14,    15,    16,   329,
       0,     0,     0,     0,     0,     0,     0,    89,    90,    91,
      92,    93,    94,     1,    61,    62,    63,     0,     0,     0,
      64,    65,     0,     0,     0,     0,     0,     0,    66,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,     0,    46,
     228,    70,     0,    71,     0,     0,     0,     0,    72,    73,
       0,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,     5,     6,     7,     8,     9,    10,    11,
      86,    87,    88,    12,    13,    14,    15,    16,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    90,    91,    92,
      93,    94,     1,    61,    62,    63,     0,     0,     0,    64,
      65,     0,     0,     0,     0,     0,     0,    66,     0,     0,
       0,     0,     0,    67,     5,     6,     7,     8,     9,    10,
      11,     0,     0,     0,     0,     0,    68,    15,    16,     0,
      70,     0,    71,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    85,     5,     6,     7,     8,     9,    10,    11,    86,
      87,    88,    12,    13,    14,    15,    16,    61,    62,    63,
       0,     0,     0,    64,    65,   134,    90,    91,    92,    93,
      94,    66,     0,     0,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      68,     0,    46,   226,    70,     0,    71,     0,     0,     0,
       0,    72,    73,     0,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,     0,     0,     0,     0,
       0,     0,     0,    86,    87,    88,     0,     0,     0,     0,
       0,    61,    62,    63,     0,     0,     0,    64,    65,    89,
      90,    91,    92,    93,    94,    66,     0,     0,     0,     0,
       0,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    68,     0,    46,   309,    70,     0,
      71,     0,     0,     0,     0,    72,    73,     0,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
       0,     0,     0,     0,     0,     0,     0,    86,    87,    88,
       0,     0,     0,     0,     0,    61,    62,    63,     0,     0,
       0,    64,    65,    89,    90,    91,    92,    93,    94,    66,
       0,     0,     0,     0,     0,    67,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,     0,
      46,     0,    70,     0,    71,     0,     0,     0,     0,    72,
      73,     0,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,     0,     0,     0,     0,     0,     0,
       0,    86,    87,    88,     0,     0,     0,     0,     0,    61,
      62,    63,     0,     0,     0,    64,    65,    89,    90,    91,
      92,    93,    94,    66,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    68,     0,     0,     0,    70,     0,     0,     0,
       0,     0,     0,    72,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    85,     5,     6,
       7,     8,     9,    10,    11,    86,    87,    88,     0,     0,
      14,    15,    16,    61,    62,    63,     0,     0,     0,    64,
      65,   134,    90,    91,    92,    93,    94,    66,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    68,     0,   140,   355,
      70,     0,     0,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    85,     0,     0,    64,    65,     0,     0,     0,    86,
      87,    88,    66,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,     0,   134,    90,    91,    92,    93,
      94,    68,     0,     0,     0,    70,   133,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    85,     0,     0,    64,
      65,     0,     0,     0,    86,    87,    88,    66,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
     134,    90,    91,    92,    93,    94,    68,     0,   140,     0,
      70,     0,     0,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    85,     0,     0,    64,    65,     0,     0,     0,    86,
      87,    88,    66,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,     0,   134,    90,    91,    92,    93,
      94,    68,     0,     0,     0,    70,     0,   180,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    85,     0,     0,    64,
      65,     0,     0,     0,    86,    87,    88,    66,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
     134,    90,    91,    92,    93,    94,    68,   283,     0,     0,
      70,     0,     0,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    85,     0,     0,    64,    65,     0,     0,     0,    86,
      87,    88,    66,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,     0,   134,    90,    91,    92,    93,
      94,    68,     0,     0,     0,    70,   313,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    85,     0,     0,    64,
      65,     0,     0,     0,    86,    87,    88,    66,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
     134,    90,    91,    92,    93,    94,    68,     0,     0,     0,
      70,     0,    71,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    85,     0,     0,    64,    65,     0,     0,     0,    86,
      87,    88,    66,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,     0,   134,    90,    91,    92,    93,
      94,    68,     0,     0,     0,    70,   353,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    85,     0,     0,    64,
      65,     0,     0,     0,    86,    87,    88,    66,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
     134,    90,    91,    92,    93,    94,    68,   371,     0,     0,
      70,     0,     0,     0,     0,     0,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    85,     0,     0,    64,    65,     0,     0,     0,    86,
      87,    88,    66,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,     0,     0,   134,    90,    91,    92,    93,
      94,   160,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    85,     0,     0,    64,
      65,     0,     0,     0,    86,    87,    88,    66,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
     134,    90,    91,    92,    93,    94,    68,     0,     0,     0,
      70,     0,     0,     0,    51,     0,     0,    72,     1,     0,
       0,     2,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    85,     0,     0,    64,    65,     0,     0,     0,    86,
      87,    88,    66,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     3,     0,     0,   134,    90,    91,    92,    93,
      94,   183,     0,     4,     1,    70,     0,     2,     0,     0,
       0,     0,    72,     0,     0,     0,     0,     0,     5,     6,
       7,     8,     9,    10,    11,     0,    85,     0,    12,    13,
      14,    15,    16,     0,    86,    87,    88,     1,   231,   310,
       2,    17,   232,     0,     0,     0,     0,     0,     0,     4,
     134,    90,    91,    92,    93,    94,     0,     0,     0,     0,
       0,     1,     0,     0,     5,     6,     7,     8,     9,    10,
      11,     3,     0,     0,    12,    13,    14,    15,    16,     0,
       0,     0,     4,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,     0,   126,     5,     6,     7,
       8,     9,    10,    11,     0,     2,     0,    12,    13,    14,
      15,    16,     0,     0,     0,     0,     0,     0,     0,     0,
      17,     5,     6,     7,     8,     9,    10,    11,     0,     0,
       0,    12,    13,    14,    15,    16,     3,     0,     0,   251,
       0,     0,   143,     0,   127,     0,     0,   144,     0,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     8,     9,    10,    11,     0,
       1,     0,     0,     0,    14,    15,    16,   145,   146,   147,
       3,     0,     0,     0,     0,   148,   143,     0,     0,     0,
       1,   144,     0,     2,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   323,     5,     6,     7,     8,
       9,    10,    11,     1,     0,     0,     0,     0,    14,    15,
      16,   145,   146,   147,   261,   310,     0,     0,   232,   148,
       5,     6,     7,     8,     9,    10,    11,     1,     0,     0,
      12,    13,    14,    15,    16,     0,     0,     0,   351,     0,
       5,     6,     7,     8,     9,    10,    11,     1,     0,     0,
      12,    13,    14,    15,    16,     0,     0,     0,     0,     0,
       0,     0,   362,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,    12,    13,    14,    15,    16,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,    12,    13,    14,
      15,    16,     0,     0,     0,     0,     0,     5,     6,     7,
       8,     9,    10,    11,     0,     0,     0,    12,    13,    14,
      15,    16
};

static const yytype_int16 yycheck[] =
{
      25,    78,    49,    49,    60,    57,    27,    48,   140,    58,
     176,    46,    68,    10,    39,    99,   248,    64,    65,     0,
       2,    75,    10,   128,    10,    41,    87,     7,    75,    75,
      46,     7,     0,    38,    68,     7,     7,     7,    85,    20,
      21,    39,   119,    24,    49,     2,     7,    28,    46,    27,
      39,    33,    99,     0,    40,    87,     3,    46,    38,   164,
      28,    38,    38,    40,    44,    46,    42,    38,    38,    49,
      48,    42,    19,   234,    44,    44,    33,    38,    49,    49,
      38,    28,    87,    38,    42,    68,    40,    42,    49,   124,
      87,   140,    60,   149,    49,   151,   173,    39,   330,    87,
      83,   262,   158,    60,    76,   157,    43,    87,   185,    46,
     276,    68,    39,    60,    40,   149,    87,    87,    39,    46,
      38,   205,   206,   207,   158,    46,    87,   183,    39,    39,
      39,    39,    87,    38,   159,    46,    46,    46,    46,    45,
     189,   176,    38,   124,    39,    39,   128,    87,    39,   183,
      38,    46,    46,   230,   203,    46,     5,     6,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   225,   160,   232,    44,
     264,   128,   164,   151,    44,   232,   232,   170,   171,   321,
      38,   174,   149,   270,   151,   176,     7,     8,     9,   182,
     183,   158,    11,    12,   151,    38,    45,   190,    38,    42,
     157,    19,    42,   234,    20,    24,    21,   264,    15,    16,
      17,    18,   212,   213,   214,   215,   183,    26,    44,    38,
      46,    46,   257,    42,    44,    39,    46,    44,    47,    46,
     223,   266,    64,    65,    66,    67,    68,    69,    70,   231,
      44,    43,    46,    10,    76,    77,    78,    22,    23,   336,
     337,    87,   339,   317,    45,   342,    13,    14,    45,    46,
     317,   317,   321,    45,   326,   316,   208,   209,    45,   261,
     210,   211,   216,   217,   231,    38,    44,    39,    43,    55,
      46,    87,    46,    44,   371,    45,   345,    87,   323,    87,
     347,   347,    38,    87,    38,   382,    39,   332,   385,   365,
      39,    39,    43,    39,     4,     5,     6,     7,    10,    46,
      24,    11,    12,    39,    43,    87,    51,    44,   218,    19,
     219,   151,   357,   220,   359,    25,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,   221,   326,    38,   222,
      40,    41,    42,   238,    44,   183,   124,   340,   341,    49,
      50,    28,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,   265,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,
      90,    91,    92,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    -1,    49,    50,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,
      91,    92,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
      -1,    -1,    -1,    25,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    38,    77,    78,    -1,
      42,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     5,     6,     7,
      -1,    -1,    -1,    11,    12,    87,    88,    89,    90,    91,
      92,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,     5,     6,     7,    -1,    -1,    -1,    11,    12,    87,
      88,    89,    90,    91,    92,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    -1,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,     5,     6,     7,    -1,    -1,
      -1,    11,    12,    87,    88,    89,    90,    91,    92,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      40,    -1,    42,    -1,    44,    -1,    -1,    -1,    -1,    49,
      50,    -1,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,     5,
       6,     7,    -1,    -1,    -1,    11,    12,    87,    88,    89,
      90,    91,    92,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      76,    77,    78,     5,     6,     7,    -1,    -1,    -1,    11,
      12,    87,    88,    89,    90,    91,    92,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,    63,    -1,    -1,    11,    12,    -1,    -1,    -1,    71,
      72,    73,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    91,
      92,    38,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,     6,     7,    63,    -1,    -1,    11,
      12,    -1,    -1,    -1,    71,    72,    73,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    91,    92,    38,    -1,    40,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,    63,    -1,    -1,    11,    12,    -1,    -1,    -1,    71,
      72,    73,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    91,
      92,    38,    -1,    -1,    -1,    42,    -1,    44,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,     6,     7,    63,    -1,    -1,    11,
      12,    -1,    -1,    -1,    71,    72,    73,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    91,    92,    38,    39,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,    63,    -1,    -1,    11,    12,    -1,    -1,    -1,    71,
      72,    73,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    91,
      92,    38,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,     6,     7,    63,    -1,    -1,    11,
      12,    -1,    -1,    -1,    71,    72,    73,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    91,    92,    38,    -1,    -1,    -1,
      42,    -1,    44,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,    63,    -1,    -1,    11,    12,    -1,    -1,    -1,    71,
      72,    73,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    91,
      92,    38,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,     6,     7,    63,    -1,    -1,    11,
      12,    -1,    -1,    -1,    71,    72,    73,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    91,    92,    38,    39,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,    63,    -1,    -1,    11,    12,    -1,    -1,    -1,    71,
      72,    73,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    88,    89,    90,    91,
      92,    38,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,     6,     7,    63,    -1,    -1,    11,
      12,    -1,    -1,    -1,    71,    72,    73,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    89,    90,    91,    92,    38,    -1,    -1,    -1,
      42,    -1,    -1,    -1,     0,    -1,    -1,    49,     4,    -1,
      -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,    63,    -1,    -1,    11,    12,    -1,    -1,    -1,    71,
      72,    73,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    38,    -1,    -1,    87,    88,    89,    90,    91,
      92,    38,    -1,    49,     4,    42,    -1,     7,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    70,    -1,    63,    -1,    74,    75,
      76,    77,    78,    -1,    71,    72,    73,     4,    38,    39,
       7,    87,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      87,    88,    89,    90,    91,    92,    -1,    -1,    -1,    -1,
      -1,     4,    -1,    -1,    64,    65,    66,    67,    68,    69,
      70,    38,    -1,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    64,    65,    66,
      67,    68,    69,    70,    -1,     7,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    64,    65,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    38,    -1,    -1,    41,
      -1,    -1,    44,    -1,    87,    -1,    -1,    49,    -1,     7,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    69,    70,    -1,
       4,    -1,    -1,    -1,    76,    77,    78,    79,    80,    81,
      38,    -1,    -1,    -1,    -1,    87,    44,    -1,    -1,    -1,
       4,    49,    -1,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    64,    65,    66,    67,
      68,    69,    70,     4,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    38,    39,    -1,    -1,    42,    87,
      64,    65,    66,    67,    68,    69,    70,     4,    -1,    -1,
      74,    75,    76,    77,    78,    -1,    -1,    -1,    39,    -1,
      64,    65,    66,    67,    68,    69,    70,     4,    -1,    -1,
      74,    75,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    64,    65,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    74,    75,    76,
      77,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     7,    38,    49,    64,    65,    66,    67,    68,
      69,    70,    74,    75,    76,    77,    78,    87,   118,   119,
     122,   123,   124,   125,   135,   136,   137,   138,   158,   159,
     161,   135,   138,   139,   136,    87,    44,   120,   121,   136,
     119,   124,   119,    44,    87,   119,    40,   151,    38,    42,
     137,     0,   159,   135,   138,    39,    44,    46,    10,   151,
      40,     5,     6,     7,    11,    12,    19,    25,    38,    41,
      42,    44,    49,    50,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    71,    72,    73,    87,
      88,    89,    90,    91,    92,    96,    97,    98,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   116,   118,   119,   149,   150,   151,   152,
     153,   154,   155,   157,   160,   162,    39,    87,   119,   140,
     141,   142,   143,    43,    87,   100,   113,   117,   121,   136,
      40,   114,   147,    44,    49,    79,    80,    81,    87,   123,
     124,   126,   127,   128,   129,   130,   131,   134,   135,   136,
      38,   100,   100,   116,   134,   144,    10,    87,   166,   167,
      38,    38,   117,    45,    38,   149,    38,    87,    44,    44,
      44,   116,    38,    38,   100,    45,    11,    12,    24,    38,
      42,    47,    10,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,   115,   102,     7,     8,     9,     5,     6,
      22,    23,    15,    16,    17,    18,    13,    14,    19,    21,
      20,    26,    27,    48,    44,    46,    41,   149,    41,   118,
     152,    38,    42,   136,   138,   145,   146,    39,    46,    39,
      46,    43,   147,   148,    87,    45,    45,    45,    38,   134,
      44,    41,   127,    44,   121,   132,   133,   136,   134,   151,
      39,    38,   138,   145,    39,    46,    43,    46,   116,   116,
      45,   149,   116,    55,   118,   153,   156,    44,    44,   116,
     144,   149,    87,    39,    99,   114,   116,    87,   114,   102,
     102,   102,   103,   103,   104,   104,   105,   105,   105,   105,
     106,   106,   107,   108,   109,   110,   111,   116,   114,    41,
      39,   140,   145,    43,   117,   146,    38,    42,   142,    87,
      41,    46,    38,    39,   141,    44,    46,   151,   102,   167,
      38,   151,   163,   164,    10,    87,    39,    39,   149,    39,
      38,   153,    39,    39,    39,    46,    43,    45,    39,    39,
      43,    39,   140,    43,   117,    41,   147,    39,   151,    39,
     133,    46,    39,   141,   151,    24,   165,   149,   149,   149,
     116,    39,   116,   149,   114,   113,    39,    43,   151,   151,
      39,   123,    51,    39,   149,    39,   149,    44,   149
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    95,    96,    96,    96,    96,    97,    97,    97,    97,
      97,    97,    97,    97,    98,    98,    98,    98,    98,    98,
      98,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     101,   101,   101,   101,   101,   101,   102,   102,   103,   103,
     103,   103,   104,   104,   104,   105,   105,   105,   106,   106,
     106,   106,   106,   107,   107,   107,   108,   108,   109,   109,
     110,   110,   111,   111,   112,   112,   113,   113,   114,   114,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   116,   116,   117,   118,   118,   119,   119,   119,   119,
     119,   119,   120,   120,   121,   121,   122,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   128,   129,   129,
     129,   129,   129,   129,   129,   129,   130,   130,   131,   132,
     132,   133,   134,   134,   134,   134,   135,   136,   136,   137,
     137,   137,   137,   137,   137,   137,   137,   138,   138,   138,
     138,   139,   139,   140,   141,   141,   142,   142,   142,   143,
     143,   144,   144,   145,   145,   145,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   147,   147,   147,   148,   148,
     149,   149,   149,   149,   149,   149,   150,   150,   150,   151,
     151,   151,   151,   152,   152,   153,   153,   154,   154,   154,
     155,   155,   155,   155,   155,   156,   156,   157,   157,   157,
     157,   157,   158,   158,   159,   159,   159,   160,   160,   161,
     161,   162,   162,   163,   164,   164,   165,   165,   166,   166,
     166,   166,   166,   167,   167
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     5,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     2,     3,     1,     2,     1,     2,
       1,     2,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     2,     1,
       1,     1,     2,     1,     1,     2,     2,     2,     3,     2,
       2,     3,     2,     1,     1,     1,     5,     4,     5,     1,
       3,     1,     2,     1,     2,     1,     1,     2,     1,     1,
       2,     3,     4,     3,     4,     4,     3,     1,     2,     2,
       3,     1,     2,     1,     1,     3,     2,     2,     1,     1,
       3,     1,     2,     1,     1,     2,     3,     2,     3,     3,
       4,     2,     3,     3,     4,     1,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     2,
       3,     3,     4,     1,     2,     1,     2,     5,     7,     5,
       5,     5,     7,     6,     7,     1,     1,     3,     2,     2,
       2,     3,     1,     2,     1,     2,     1,     1,     2,     3,
       2,     5,     4,     2,     2,     3,     0,     2,     0,     1,
       1,     3,     3,     1,     3
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

#line 1830 "cpp.tab.c"

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

#line 513 "cpp.y"


int main(){
    return 0;
}
