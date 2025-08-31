/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INCLUDE = 258,
     PLUS = 259,
     MINUS = 260,
     STAR = 261,
     DIVIDE = 262,
     MODULUS = 263,
     ASSIGN = 264,
     INCREMENT = 265,
     DECREMENT = 266,
     EQUAL = 267,
     NOT_EQUAL = 268,
     LESS_THAN = 269,
     GREATER_THAN = 270,
     LESS_EQUAL = 271,
     GREATER_EQUAL = 272,
     BITWISE_AND = 273,
     BITWISE_OR = 274,
     BITWISE_XOR = 275,
     LEFT_SHIFT = 276,
     RIGHT_SHIFT = 277,
     ARROW = 278,
     LOGICAL_NOT = 279,
     LOGICAL_AND = 280,
     LOGICAL_OR = 281,
     PLUS_EQUAL = 282,
     MINUS_EQUAL = 283,
     STAR_EQUAL = 284,
     DIV_EQUAL = 285,
     MOD_EQUAL = 286,
     AND_EQUAL = 287,
     OR_EQUAL = 288,
     XOR_EQUAL = 289,
     LEFT_SHIFT_EQ = 290,
     RIGHT_SHIFT_EQ = 291,
     LROUND = 292,
     RROUND = 293,
     LCURLY = 294,
     RCURLY = 295,
     LSQUARE = 296,
     RSQUARE = 297,
     SEMICOLON = 298,
     COLON = 299,
     COMMA = 300,
     DOT = 301,
     QUESTION_MARK = 302,
     TILDE = 303,
     IF = 304,
     ELSE = 305,
     SWITCH = 306,
     CASE = 307,
     DEFAULT = 308,
     WHILE = 309,
     DO = 310,
     FOR = 311,
     GOTO = 312,
     CONTINUE = 313,
     BREAK = 314,
     RETURN = 315,
     UNTIL = 316,
     SIZEOF = 317,
     VOID = 318,
     INT = 319,
     DOUBLE = 320,
     CHAR = 321,
     BOOL = 322,
     STRING = 323,
     LONG = 324,
     TRUE = 325,
     FALSE = 326,
     NULLPTR = 327,
     AUTO = 328,
     STATIC = 329,
     CONST = 330,
     CLASS = 331,
     STRUCT = 332,
     PUBLIC = 333,
     PRIVATE = 334,
     PROTECTED = 335,
     DELETE = 336,
     NEW = 337,
     CIN = 338,
     COUT = 339,
     ENDL = 340,
     TYPE_NAME = 341,
     IDENTIFIER = 342,
     DECIMAL_LITERAL = 343,
     DOUBLE_LITERAL = 344,
     EXPONENT_LITERAL = 345,
     CHARACTER_LITERAL = 346,
     STRING_LITERAL = 347,
     FUNCTION = 348,
     INVALID_IDENTIFIER = 349
   };
#endif
/* Tokens.  */
#define INCLUDE 258
#define PLUS 259
#define MINUS 260
#define STAR 261
#define DIVIDE 262
#define MODULUS 263
#define ASSIGN 264
#define INCREMENT 265
#define DECREMENT 266
#define EQUAL 267
#define NOT_EQUAL 268
#define LESS_THAN 269
#define GREATER_THAN 270
#define LESS_EQUAL 271
#define GREATER_EQUAL 272
#define BITWISE_AND 273
#define BITWISE_OR 274
#define BITWISE_XOR 275
#define LEFT_SHIFT 276
#define RIGHT_SHIFT 277
#define ARROW 278
#define LOGICAL_NOT 279
#define LOGICAL_AND 280
#define LOGICAL_OR 281
#define PLUS_EQUAL 282
#define MINUS_EQUAL 283
#define STAR_EQUAL 284
#define DIV_EQUAL 285
#define MOD_EQUAL 286
#define AND_EQUAL 287
#define OR_EQUAL 288
#define XOR_EQUAL 289
#define LEFT_SHIFT_EQ 290
#define RIGHT_SHIFT_EQ 291
#define LROUND 292
#define RROUND 293
#define LCURLY 294
#define RCURLY 295
#define LSQUARE 296
#define RSQUARE 297
#define SEMICOLON 298
#define COLON 299
#define COMMA 300
#define DOT 301
#define QUESTION_MARK 302
#define TILDE 303
#define IF 304
#define ELSE 305
#define SWITCH 306
#define CASE 307
#define DEFAULT 308
#define WHILE 309
#define DO 310
#define FOR 311
#define GOTO 312
#define CONTINUE 313
#define BREAK 314
#define RETURN 315
#define UNTIL 316
#define SIZEOF 317
#define VOID 318
#define INT 319
#define DOUBLE 320
#define CHAR 321
#define BOOL 322
#define STRING 323
#define LONG 324
#define TRUE 325
#define FALSE 326
#define NULLPTR 327
#define AUTO 328
#define STATIC 329
#define CONST 330
#define CLASS 331
#define STRUCT 332
#define PUBLIC 333
#define PRIVATE 334
#define PROTECTED 335
#define DELETE 336
#define NEW 337
#define CIN 338
#define COUT 339
#define ENDL 340
#define TYPE_NAME 341
#define IDENTIFIER 342
#define DECIMAL_LITERAL 343
#define DOUBLE_LITERAL 344
#define EXPONENT_LITERAL 345
#define CHARACTER_LITERAL 346
#define STRING_LITERAL 347
#define FUNCTION 348
#define INVALID_IDENTIFIER 349




/* Copy the first part of user declarations.  */
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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 170 "src/parser.y"
{ 
    char *str; 
}
/* Line 193 of yacc.c.  */
#line 457 "src/parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 470 "src/parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

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
/* YYNRULES -- Number of states.  */
#define YYNSTATES  344

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   349

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    11,    13,    15,    17,
      18,    22,    23,    28,    30,    32,    35,    38,    40,    42,
      44,    46,    48,    50,    52,    54,    56,    58,    60,    62,
      64,    66,    70,    72,    76,    79,    81,    83,    87,    92,
      95,    97,    99,   102,   104,   108,   113,   117,   122,   124,
     126,   130,   131,   135,   137,   143,   149,   150,   153,   156,
     159,   162,   163,   168,   171,   173,   177,   179,   180,   185,
     186,   190,   192,   195,   200,   204,   208,   213,   215,   217,
     219,   221,   223,   226,   228,   231,   235,   237,   240,   242,
     244,   250,   258,   264,   268,   271,   273,   277,   280,   286,
     292,   300,   310,   311,   313,   316,   320,   323,   326,   329,
     333,   335,   339,   341,   345,   347,   349,   351,   353,   355,
     357,   359,   361,   363,   365,   367,   369,   375,   377,   381,
     383,   387,   389,   393,   395,   399,   401,   405,   407,   411,
     415,   417,   421,   425,   429,   433,   435,   439,   443,   445,
     449,   453,   455,   459,   463,   467,   469,   474,   476,   479,
     482,   485,   488,   491,   494,   497,   500,   503,   508,   510,
     515,   519,   524,   528,   532,   535,   538,   541,   544,   546,
     548,   550,   554,   558,   562,   564,   566,   568,   572,   573,
     575,   577,   581,   586,   588,   592,   594,   596,   598,   600,
     602,   604,   606
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      96,     0,    -1,    -1,    96,    97,    -1,   121,    -1,    98,
      -1,   115,    -1,     3,    -1,    93,    -1,    -1,   101,    99,
      43,    -1,    -1,   101,   100,   104,    43,    -1,   103,    -1,
     102,    -1,   102,   101,    -1,   103,   101,    -1,    73,    -1,
      74,    -1,    75,    -1,    63,    -1,    64,    -1,    69,    -1,
      65,    -1,    66,    -1,    67,    -1,    68,    -1,    86,    -1,
      77,    -1,    76,    -1,   105,    -1,   104,    45,   105,    -1,
     106,    -1,   106,     9,   158,    -1,   109,   107,    -1,   107,
      -1,    87,    -1,    37,   106,    38,    -1,   107,    41,   157,
      42,    -1,   109,   110,    -1,   110,    -1,     6,    -1,     6,
     109,    -1,    87,    -1,    37,   108,    38,    -1,   110,    37,
     111,    38,    -1,   110,    37,    38,    -1,   110,    41,   157,
      42,    -1,   112,    -1,   113,    -1,   112,    45,   113,    -1,
      -1,   101,   114,   108,    -1,   101,    -1,    76,    87,    39,
     116,    40,    -1,    77,    87,    39,   116,    40,    -1,    -1,
     116,   117,    -1,    78,    44,    -1,    79,    44,    -1,    80,
      44,    -1,    -1,   101,   118,   119,    43,    -1,   101,    43,
      -1,   120,    -1,   119,    45,   120,    -1,   106,    -1,    -1,
     101,   124,   122,   127,    -1,    -1,   124,   123,   127,    -1,
     125,    -1,   109,   124,    -1,    87,    37,   111,    38,    -1,
      87,    37,    38,    -1,    37,   124,    38,    -1,   125,    41,
     157,    42,    -1,   127,    -1,   130,    -1,   134,    -1,   137,
      -1,   136,    -1,   138,    43,    -1,    43,    -1,    39,    40,
      -1,    39,   128,    40,    -1,   129,    -1,   128,   129,    -1,
      98,    -1,   126,    -1,    49,    37,   138,    38,   126,    -1,
      49,    37,   138,    38,   126,    50,   126,    -1,    51,    37,
     138,    38,   131,    -1,    39,   132,    40,    -1,   132,   133,
      -1,   133,    -1,    52,   160,   126,    -1,    53,   126,    -1,
      54,    37,   138,    38,   126,    -1,    61,    37,   138,    38,
     126,    -1,    55,   126,    54,    37,   138,    38,    43,    -1,
      56,    37,   135,    43,   135,    43,   135,    38,   126,    -1,
      -1,   138,    -1,    87,    44,    -1,    57,    87,    43,    -1,
      58,    43,    -1,    59,    43,    -1,    60,    43,    -1,    60,
     138,    43,    -1,   139,    -1,   138,    45,   139,    -1,   141,
      -1,   153,   140,   139,    -1,     9,    -1,    27,    -1,    28,
      -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,
      -1,    34,    -1,    35,    -1,    36,    -1,   142,    -1,   142,
      47,   138,    44,   141,    -1,   143,    -1,   142,    26,   143,
      -1,   144,    -1,   143,    25,   144,    -1,   145,    -1,   144,
      19,   145,    -1,   146,    -1,   145,    20,   146,    -1,   147,
      -1,   146,    18,   147,    -1,   148,    -1,   147,    12,   148,
      -1,   147,    13,   148,    -1,   149,    -1,   148,    14,   149,
      -1,   148,    15,   149,    -1,   148,    16,   149,    -1,   148,
      17,   149,    -1,   150,    -1,   149,    21,   150,    -1,   149,
      22,   150,    -1,   151,    -1,   150,     4,   151,    -1,   150,
       5,   151,    -1,   152,    -1,   151,     6,   152,    -1,   151,
       7,   152,    -1,   151,     8,   152,    -1,   153,    -1,    37,
     103,    38,   152,    -1,   154,    -1,    10,   153,    -1,    11,
     153,    -1,     4,   153,    -1,     5,   153,    -1,     6,   153,
      -1,    18,   153,    -1,    24,   153,    -1,    48,   153,    -1,
      62,   153,    -1,    62,    37,   103,    38,    -1,   155,    -1,
     154,    41,   138,    42,    -1,   154,    37,    38,    -1,   154,
      37,   156,    38,    -1,   154,    46,    87,    -1,   154,    23,
      87,    -1,   154,    10,    -1,   154,    11,    -1,    82,   103,
      -1,    81,   153,    -1,    87,    -1,   160,    -1,    92,    -1,
      37,   138,    38,    -1,    84,    21,   156,    -1,    83,    22,
      87,    -1,    85,    -1,    94,    -1,   139,    -1,   156,    45,
     139,    -1,    -1,   139,    -1,   139,    -1,    39,   159,    40,
      -1,    39,   159,    45,    40,    -1,   158,    -1,   159,    45,
     158,    -1,    88,    -1,    91,    -1,    92,    -1,    90,    -1,
      89,    -1,    72,    -1,    70,    -1,    71,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   228,   228,   230,   234,   235,   236,   237,   238,   243,
     243,   245,   245,   252,   253,   254,   255,   259,   260,   261,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     279,   280,   284,   285,   289,   290,   295,   296,   297,   311,
     312,   316,   317,   322,   323,   324,   325,   326,   330,   334,
     335,   339,   339,   341,   345,   346,   349,   351,   355,   356,
     357,   358,   358,   361,   365,   366,   370,   376,   375,   385,
     384,   394,   395,   399,   400,   401,   402,   407,   408,   409,
     410,   411,   412,   413,   417,   418,   422,   423,   427,   428,
     433,   434,   435,   439,   443,   444,   448,   449,   454,   455,
     456,   457,   460,   462,   467,   471,   472,   473,   474,   475,
     480,   481,   485,   486,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   504,   505,   509,   510,   514,
     515,   519,   520,   524,   525,   529,   530,   534,   535,   536,
     540,   541,   542,   543,   544,   548,   549,   550,   554,   555,
     556,   560,   561,   562,   563,   567,   568,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   586,   587,
     588,   589,   590,   591,   592,   593,   594,   595,   599,   600,
     601,   602,   603,   604,   605,   606,   615,   616,   619,   621,
     630,   631,   632,   636,   637,   642,   643,   644,   645,   646,
     647,   648,   649
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INCLUDE", "PLUS", "MINUS", "STAR",
  "DIVIDE", "MODULUS", "ASSIGN", "INCREMENT", "DECREMENT", "EQUAL",
  "NOT_EQUAL", "LESS_THAN", "GREATER_THAN", "LESS_EQUAL", "GREATER_EQUAL",
  "BITWISE_AND", "BITWISE_OR", "BITWISE_XOR", "LEFT_SHIFT", "RIGHT_SHIFT",
  "ARROW", "LOGICAL_NOT", "LOGICAL_AND", "LOGICAL_OR", "PLUS_EQUAL",
  "MINUS_EQUAL", "STAR_EQUAL", "DIV_EQUAL", "MOD_EQUAL", "AND_EQUAL",
  "OR_EQUAL", "XOR_EQUAL", "LEFT_SHIFT_EQ", "RIGHT_SHIFT_EQ", "LROUND",
  "RROUND", "LCURLY", "RCURLY", "LSQUARE", "RSQUARE", "SEMICOLON", "COLON",
  "COMMA", "DOT", "QUESTION_MARK", "TILDE", "IF", "ELSE", "SWITCH", "CASE",
  "DEFAULT", "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN",
  "UNTIL", "SIZEOF", "VOID", "INT", "DOUBLE", "CHAR", "BOOL", "STRING",
  "LONG", "TRUE", "FALSE", "NULLPTR", "AUTO", "STATIC", "CONST", "CLASS",
  "STRUCT", "PUBLIC", "PRIVATE", "PROTECTED", "DELETE", "NEW", "CIN",
  "COUT", "ENDL", "TYPE_NAME", "IDENTIFIER", "DECIMAL_LITERAL",
  "DOUBLE_LITERAL", "EXPONENT_LITERAL", "CHARACTER_LITERAL",
  "STRING_LITERAL", "FUNCTION", "INVALID_IDENTIFIER", "$accept",
  "translation_unit", "external_declaration", "declaration", "@1", "@2",
  "declaration_specifiers", "storage_class_specifier", "type_specifier",
  "init_declarator_list_no_func", "init_declarator_no_func",
  "declarator_no_func", "direct_declarator_no_func", "declarator",
  "pointer", "direct_declarator", "parameter_type_list", "parameter_list",
  "parameter_declaration", "@3", "class_specifier", "member_specification",
  "member_declaration", "@4", "member_declarator_list",
  "member_declarator", "function_definition", "@5", "@6",
  "function_declarator", "direct_function_declarator", "statement",
  "compound_statement", "block_item_list", "block_item",
  "selection_statement", "switch_body", "case_list", "case_label",
  "iteration_statement", "expression_opt", "label", "jump_statement",
  "expression", "assignment_expression", "assignment_operator",
  "conditional_expression", "logical_or_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "cast_expression", "unary_expression",
  "postfix_expression", "primary_expression", "argument_expression_list",
  "constant_expression_opt", "initializer", "initializer_list", "constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
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

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
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

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    21,   133,    36,    37,    50,    24,    25,    57,
      58,    59,    60,   209,    61,   211,    51,    52,    53,   110,
      27,   108,   205,   271,   296,   297,    28,    62,    44,    29,
      30,   135,   136,   137,   138,   139,   320,   329,   330,   140,
     283,   141,   142,   143,   144,   192,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   240,   106,   217,   277,   107
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -292
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

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -54
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

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
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

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:
#line 243 "src/parser.y"
    { curr_decl_spec = (yyvsp[(1) - (1)].str); pending_role = "IDENTIFIER"; pending_ids.clear(); ;}
    break;

  case 11:
#line 245 "src/parser.y"
    { curr_decl_spec = (yyvsp[(1) - (1)].str); pending_role = "IDENTIFIER"; pending_ids.clear(); ;}
    break;

  case 12:
#line 247 "src/parser.y"
    { flush_pending(curr_decl_spec, pending_role); ;}
    break;

  case 13:
#line 252 "src/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 14:
#line 253 "src/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 15:
#line 254 "src/parser.y"
    { (yyval.str) = cat2((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 16:
#line 255 "src/parser.y"
    { (yyval.str) = cat2((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 17:
#line 259 "src/parser.y"
    { (yyval.str) = sdup("AUTO"); ;}
    break;

  case 18:
#line 260 "src/parser.y"
    { (yyval.str) = sdup("STATIC"); ;}
    break;

  case 19:
#line 261 "src/parser.y"
    { (yyval.str) = sdup("CONST"); ;}
    break;

  case 20:
#line 265 "src/parser.y"
    { (yyval.str) = sdup("VOID"); ;}
    break;

  case 21:
#line 266 "src/parser.y"
    { (yyval.str) = sdup("INT"); ;}
    break;

  case 22:
#line 267 "src/parser.y"
    { (yyval.str) = sdup("LONG"); ;}
    break;

  case 23:
#line 268 "src/parser.y"
    { (yyval.str) = sdup("DOUBLE"); ;}
    break;

  case 24:
#line 269 "src/parser.y"
    { (yyval.str) = sdup("CHAR"); ;}
    break;

  case 25:
#line 270 "src/parser.y"
    { (yyval.str) = sdup("BOOL"); ;}
    break;

  case 26:
#line 271 "src/parser.y"
    { (yyval.str) = sdup("STRING"); ;}
    break;

  case 27:
#line 272 "src/parser.y"
    { (yyval.str) = sdup((yyvsp[(1) - (1)].str)); ;}
    break;

  case 28:
#line 273 "src/parser.y"
    { (yyval.str) = sdup("STRUCT"); ;}
    break;

  case 29:
#line 274 "src/parser.y"
    { (yyval.str) = sdup("CLASS"); ;}
    break;

  case 32:
#line 284 "src/parser.y"
    { push_id((yyvsp[(1) - (1)].str)); ;}
    break;

  case 33:
#line 285 "src/parser.y"
    { push_id((yyvsp[(1) - (3)].str)); ;}
    break;

  case 34:
#line 289 "src/parser.y"
    { last_declarator_pointer = (yyvsp[(1) - (2)].str); curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 35:
#line 290 "src/parser.y"
    { last_declarator_pointer = NULL; curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 39:
#line 311 "src/parser.y"
    { last_declarator_pointer = (yyvsp[(1) - (2)].str); curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 40:
#line 312 "src/parser.y"
    { last_declarator_pointer = NULL; curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 41:
#line 316 "src/parser.y"
    { (yyval.str) = sdup("pointer"); ;}
    break;

  case 42:
#line 317 "src/parser.y"
    { (yyval.str) = cat2((yyvsp[(2) - (2)].str), "pointer"); ;}
    break;

  case 43:
#line 322 "src/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 44:
#line 323 "src/parser.y"
    { (yyval.str) = (yyvsp[(2) - (3)].str); ;}
    break;

  case 45:
#line 324 "src/parser.y"
    { (yyval.str) = (yyvsp[(1) - (4)].str); ;}
    break;

  case 46:
#line 325 "src/parser.y"
    { (yyval.str) = (yyvsp[(1) - (3)].str); ;}
    break;

  case 47:
#line 326 "src/parser.y"
    { (yyval.str) = (yyvsp[(1) - (4)].str); ;}
    break;

  case 51:
#line 339 "src/parser.y"
    { curr_param_spec = (yyvsp[(1) - (1)].str); ;}
    break;

  case 52:
#line 340 "src/parser.y"
    { insert_symbol_table((yyvsp[(3) - (3)].str), curr_param_spec ? curr_param_spec : "", "PARAM"); ;}
    break;

  case 54:
#line 345 "src/parser.y"
    { insert_symbol_table((yyvsp[(2) - (5)].str), sdup("CLASS"), "TYPE"); ;}
    break;

  case 55:
#line 346 "src/parser.y"
    { insert_symbol_table((yyvsp[(2) - (5)].str), sdup("STRUCT"), "TYPE"); ;}
    break;

  case 61:
#line 358 "src/parser.y"
    { curr_decl_spec = (yyvsp[(1) - (1)].str); pending_role = "MEMBER"; pending_ids.clear(); ;}
    break;

  case 62:
#line 360 "src/parser.y"
    { flush_pending(curr_decl_spec, pending_role); ;}
    break;

  case 66:
#line 370 "src/parser.y"
    { push_id((yyvsp[(1) - (1)].str)); ;}
    break;

  case 67:
#line 376 "src/parser.y"
    { /* remember return-spec and record function-name lineno here */
          curr_func_spec = (yyvsp[(1) - (2)].str);
          curr_decl_lineno = last_ident_lineno;
        ;}
    break;

  case 68:
#line 381 "src/parser.y"
    { insert_symbol_table((yyvsp[(2) - (4)].str), curr_func_spec ? curr_func_spec : "", "FUNCTION");
          curr_func_spec = NULL;
        ;}
    break;

  case 69:
#line 385 "src/parser.y"
    { /* no explicit return-specifiers; record function-name lineno */
          curr_decl_lineno = last_ident_lineno;
        ;}
    break;

  case 70:
#line 389 "src/parser.y"
    { insert_symbol_table((yyvsp[(1) - (3)].str), "INT", "FUNCTION"); ;}
    break;

  case 71:
#line 394 "src/parser.y"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 72:
#line 395 "src/parser.y"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 73:
#line 399 "src/parser.y"
    { curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[(1) - (4)].str); ;}
    break;

  case 74:
#line 400 "src/parser.y"
    { curr_decl_lineno = last_ident_lineno; (yyval.str) = (yyvsp[(1) - (3)].str); ;}
    break;

  case 75:
#line 401 "src/parser.y"
    { (yyval.str) = (yyvsp[(2) - (3)].str); ;}
    break;

  case 76:
#line 402 "src/parser.y"
    { (yyval.str) = (yyvsp[(1) - (4)].str); ;}
    break;

  case 104:
#line 467 "src/parser.y"
    { insert_symbol_table((yyvsp[(1) - (2)].str), sdup("LABEL"), "IDENTIFIER");   ;}
    break;

  case 180:
#line 601 "src/parser.y"
    { insert_const_symbol_table('S',(yyvsp[(1) - (1)].str)); ;}
    break;

  case 195:
#line 642 "src/parser.y"
    { insert_const_symbol_table('I',(yyvsp[(1) - (1)].str)); ;}
    break;

  case 196:
#line 643 "src/parser.y"
    { insert_const_symbol_table('C',(yyvsp[(1) - (1)].str)); ;}
    break;

  case 197:
#line 644 "src/parser.y"
    { insert_const_symbol_table('S',(yyvsp[(1) - (1)].str)); ;}
    break;

  case 198:
#line 645 "src/parser.y"
    { insert_const_symbol_table('E',(yyvsp[(1) - (1)].str)); ;}
    break;

  case 199:
#line 646 "src/parser.y"
    { insert_const_symbol_table('D',(yyvsp[(1) - (1)].str)); ;}
    break;

  case 200:
#line 647 "src/parser.y"
    { insert_const_symbol_table('N',(yyvsp[(1) - (1)].str)); ;}
    break;

  case 201:
#line 648 "src/parser.y"
    { insert_const_symbol_table('B',(yyvsp[(1) - (1)].str)); ;}
    break;

  case 202:
#line 649 "src/parser.y"
    { insert_const_symbol_table('B',(yyvsp[(1) - (1)].str)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2496 "src/parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 652 "src/parser.y"


int main() {
    yyparse();
    print_symbol_table();
    cout << endl;
    print_constant_table();
    print_error();
    return 0;
}

