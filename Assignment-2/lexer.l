%option noyywrap yylineno
%{
    #include <iostream>
    #include "parser.tab.h"

    extern int yylineno;
    extern int yylex();
    extern YYSTYPE yylval;
    using namespace std;
%}

/* ===================== Macros (Definitions Section) ===================== */

/* Arithmetic */
PLUS             "+"
MINUS            "-"
STAR             "*"
DIVIDE           "/"
MODULUS          "%"
ASSIGN           "="
INCREMENT        "++"
DECREMENT        "--"

/* Comparison */
EQUAL            "=="
NOT_EQUAL        "!="
LESS_THAN        "<"
GREATER_THAN     ">"
LESS_EQUAL       "<="
GREATER_EQUAL    ">="

/* Bitwise */
BITWISE_AND      "&"
BITWISE_OR       "|"
BITWISE_XOR      "\^"
TILDE            "~"
LEFT_SHIFT       "<<"
RIGHT_SHIFT      ">>"

/* Logical */
LOGICAL_NOT      "!"
LOGICAL_OR       "||"
LOGICAL_AND      "&&"

/* With Equals (compound assignment) */
PLUS_EQUAL       "+="
MINUS_EQUAL      "-="
STAR_EQUAL       "*="
DIV_EQUAL        "/="
MOD_EQUAL        "%="
AND_EQUAL        "&="
OR_EQUAL         "|="
XOR_EQUAL        "^="
LEFT_SHIFT_EQ    "<<="
RIGHT_SHIFT_EQ   ">>="

/* Brackets / Delimiters */
RCURLY           "}"
LCURLY           "{"
LSQUARE          "["
RSQUARE          "]"
LROUND           "("
RROUND           ")"

/* Punctuation */
DOT              "\."
COMMA            ","
COLON            ":"
SEMICOLON        ";"
ARROW            "->"
QUESTION_MARK    "?"

/* Preprocessor and misc */
INCLUDE          ^#include.*\n
SCOMMENT         "//".*
RETURN           "return"
SIZEOF           "sizeof"

/* Conditionals */
IF               "if"
ELIF             "elif"
ELSE             "else"
CASE             "case"
SWITCH           "switch"
DEFAULT          "default"

/* Loops */
FOR              "for"
WHILE            "while"
DO               "do"
UNTIL            "until"
BREAK            "break"
CONTINUE         "continue"
GOTO             "goto"

/* Data Types & keywords */
INT              "int"
BOOL             "bool"
CHAR             "char"
DOUBLE           "double"
LONG             "long"
STRING           "string"
VOID             "void"
CONST            "const"
NULLPTR          "nullptr"
FUNCTION         "function"
AUTO             "auto"
TRUE             "true"
FALSE            "false"
STATIC           "static"

/* Classes and Structs */
CLASS            "class"
STRUCT           "struct"
PUBLIC           "public"
PRIVATE          "private"
PROTECTED        "protected"

/* IO */
COUT             "cout"
CIN              "cin"
ENDL             "endl"

/* Dynamic Allocation */
NEW              "new"
DELETE           "delete"

/* Regex building blocks */
DIGIT            [0-9]
LETTER           [A-Za-z]
EXPONENT         [Ee][+-]?{DIGIT}+

IDENTIFIER       ({LETTER}|_)({LETTER}|_|{DIGIT})*
DECIMAL_LITERAL  {DIGIT}+
EXPONENT_LITERAL {DIGIT}+[Ee][+-]?{DIGIT}+
DOUBLE_LITERAL   {DIGIT}+"."{DIGIT}+({EXPONENT})?
STRING_LITERAL   \"(\\.|[^\\"])*\"
CHARACTER_LITERAL '((\\.)|[^'\\])'
INVALID_IDENTIFIER ({DIGIT}+({LETTER}|_)+({DIGIT}|{LETTER}|_)*(\.{DIGIT}*)?)


%%  
[ \t\r\n]+             ;
{SCOMMENT}             ;
\/\*([^*]|\*+[^*/])*\*+\/   ;

{INCLUDE}              { yylval.str = strdup(yytext); return INCLUDE; }

{PLUS}                 { yylval.str = strdup(yytext); return PLUS; }
{MINUS}                { yylval.str = strdup(yytext); return MINUS; }
{STAR}                 { yylval.str = strdup(yytext); return STAR; }
{DIVIDE}               { yylval.str = strdup(yytext); return DIVIDE; }
{MODULUS}              { yylval.str = strdup(yytext); return MODULUS; }
{ASSIGN}               { yylval.str = strdup(yytext); return ASSIGN; }

{INCREMENT}            { yylval.str = strdup(yytext); return INCREMENT; }
{DECREMENT}            { yylval.str = strdup(yytext); return DECREMENT; }
{EQUAL}                { yylval.str = strdup(yytext); return EQUAL; }
{NOT_EQUAL}            { yylval.str = strdup(yytext); return NOT_EQUAL; }
{LESS_THAN}            { yylval.str = strdup(yytext); return LESS_THAN; }
{GREATER_THAN}         { yylval.str = strdup(yytext); return GREATER_THAN; }
{LESS_EQUAL}           { yylval.str = strdup(yytext); return LESS_EQUAL; }
{GREATER_EQUAL}        { yylval.str = strdup(yytext); return GREATER_EQUAL; }

{BITWISE_AND}          { yylval.str = strdup(yytext); return BITWISE_AND; }
{BITWISE_OR}           { yylval.str = strdup(yytext); return BITWISE_OR; }
{BITWISE_XOR}          { yylval.str = strdup(yytext); return BITWISE_XOR; }
{TILDE}                { yylval.str = strdup(yytext); return TILDE; }
{LEFT_SHIFT}           { yylval.str = strdup(yytext); return LEFT_SHIFT; }
{RIGHT_SHIFT}          { yylval.str = strdup(yytext); return RIGHT_SHIFT; }
{LOGICAL_NOT}          { yylval.str = strdup(yytext); return LOGICAL_NOT; }
{LOGICAL_OR}           { yylval.str = strdup(yytext); return LOGICAL_OR; }
{LOGICAL_AND}          { yylval.str = strdup(yytext); return LOGICAL_AND; }

{PLUS_EQUAL}           { yylval.str = strdup(yytext); return PLUS_EQUAL; }
{MINUS_EQUAL}          { yylval.str = strdup(yytext); return MINUS_EQUAL; }
{STAR_EQUAL}           { yylval.str = strdup(yytext); return STAR_EQUAL; }
{DIV_EQUAL}            { yylval.str = strdup(yytext); return DIV_EQUAL; }
{MOD_EQUAL}            { yylval.str = strdup(yytext); return MOD_EQUAL; }
{AND_EQUAL}            { yylval.str = strdup(yytext); return AND_EQUAL; }
{OR_EQUAL}             { yylval.str = strdup(yytext); return OR_EQUAL; }
{XOR_EQUAL}            { yylval.str = strdup(yytext); return XOR_EQUAL; }
{LEFT_SHIFT_EQ}        { yylval.str = strdup(yytext); return LEFT_SHIFT_EQ; }
{RIGHT_SHIFT_EQ}       { yylval.str = strdup(yytext); return RIGHT_SHIFT_EQ; }

{LCURLY}               { yylval.str = strdup(yytext); return LCURLY; }
{RCURLY}               { yylval.str = strdup(yytext); return RCURLY; }
{LSQUARE}              { yylval.str = strdup(yytext); return LSQUARE; }
{RSQUARE}              { yylval.str = strdup(yytext); return RSQUARE; }
{LROUND}               { yylval.str = strdup(yytext); return LROUND; }
{RROUND}               { yylval.str = strdup(yytext); return RROUND; }
{DOT}                  { yylval.str = strdup(yytext); return DOT; }
{COMMA}                { yylval.str = strdup(yytext); return COMMA; }
{COLON}                { yylval.str = strdup(yytext); return COLON; }
{SEMICOLON}            { yylval.str = strdup(yytext); return SEMICOLON; }
{ARROW}                { yylval.str = strdup(yytext); return ARROW; }
{QUESTION_MARK}        { yylval.str = strdup(yytext); return QUESTION_MARK; }

{RETURN}               { yylval.str = strdup(yytext); return RETURN; }
{SIZEOF}               { yylval.str = strdup(yytext); return SIZEOF; }
{IF}                   { yylval.str = strdup(yytext); return IF; }
{ELIF}                 { yylval.str = strdup(yytext); return ELIF; }
{ELSE}                 { yylval.str = strdup(yytext); return ELSE; }
{CASE}                 { yylval.str = strdup(yytext); return CASE; }
{SWITCH}               { yylval.str = strdup(yytext); return SWITCH; }
{DEFAULT}              { yylval.str = strdup(yytext); return DEFAULT; }
{FOR}                  { yylval.str = strdup(yytext); return FOR; }
{WHILE}                { yylval.str = strdup(yytext); return WHILE; }
{DO}                   { yylval.str = strdup(yytext); return DO; }
{UNTIL}                { yylval.str = strdup(yytext); return UNTIL; }
{BREAK}                { yylval.str = strdup(yytext); return BREAK; }
{CONTINUE}             { yylval.str = strdup(yytext); return CONTINUE; }
{GOTO}                 { yylval.str = strdup(yytext); return GOTO; }

{INT}                  { yylval.str = strdup(yytext); return INT; }
{BOOL}                 { yylval.str = strdup(yytext); return BOOL; }
{CHAR}                 { yylval.str = strdup(yytext); return CHAR; }
{DOUBLE}               { yylval.str = strdup(yytext); return DOUBLE; }
{LONG}                 { yylval.str = strdup(yytext); return LONG; }
{STRING}               { yylval.str = strdup(yytext); return STRING; }
{VOID}                 { yylval.str = strdup(yytext); return VOID; }
{CONST}                { yylval.str = strdup(yytext); return CONST; }
{NULLPTR}              { yylval.str = strdup(yytext); return NULLPTR; }
{FUNCTION}             { yylval.str = strdup(yytext); return FUNCTION; }
{AUTO}                 { yylval.str = strdup(yytext); return AUTO; }
{TRUE}                 { yylval.str = strdup(yytext); return TRUE; }
{FALSE}                { yylval.str = strdup(yytext); return FALSE; }
{STATIC}               { yylval.str = strdup(yytext); return STATIC; }

{CLASS}                { yylval.str = strdup(yytext); return CLASS; }
{STRUCT}               { yylval.str = strdup(yytext); return STRUCT; }
{PUBLIC}               { yylval.str = strdup(yytext); return PUBLIC; }
{PRIVATE}              { yylval.str = strdup(yytext); return PRIVATE; }
{PROTECTED}            { yylval.str = strdup(yytext); return PROTECTED; }

{COUT}                 { yylval.str = strdup(yytext); return COUT; }
{CIN}                  { yylval.str = strdup(yytext); return CIN; }
{ENDL}                 { yylval.str = strdup(yytext); return ENDL; }
{NEW}                  { yylval.str = strdup(yytext); return NEW; }
{DELETE}               { yylval.str = strdup(yytext); return DELETE; }

{IDENTIFIER}           { yylval.str = strdup(yytext); return IDENTIFIER; }
{DECIMAL_LITERAL}      { yylval.str = strdup(yytext); return DECIMAL_LITERAL; }
{EXPONENT_LITERAL}     { yylval.str = strdup(yytext); return EXPONENT_LITERAL; }
{DOUBLE_LITERAL}       { yylval.str = strdup(yytext); return DOUBLE_LITERAL; }
{STRING_LITERAL}       { yylval.str = strdup(yytext); return STRING_LITERAL; }
{CHARACTER_LITERAL}    { yylval.str = strdup(yytext); return CHARACTER_LITERAL; }

{INVALID_IDENTIFIER}   { cerr << "Invalid identifier: " << yytext << " at line " << yylineno << endl; return INVALID_IDENTIFIER; }
.                      { cerr << "Invalid token: " << yytext << " at line " << yylineno << endl; return yytext[0]; }

%%
