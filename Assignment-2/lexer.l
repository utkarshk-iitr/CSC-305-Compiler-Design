%option noyywrap yylineno
%{
    #include <iostream>
    #include <iomanip>
    #include <cstdio> 
    #include <vector>
    #include <string>
    #include <fstream>
    #include "parser.tab.h"

    extern "C" int yylex();
    using namespace std;
%}

%option yylineno

/* Arithmetic */
PLUS            "+"
MINUS           "-"
STAR      	    "*"
DIVIDE        	"/"
MODULUS        	"%"
ASSIGN        	"="
INCREMENT      	"++"
DECREMENT      	"--"

/* Comparision */
EQUAL       	"=="
NOT_EQUAL     	"!="
LESS_THAN      	"<"
GREATER_THAN   	">"
LESS_EQUAL    	"<="
GREATER_EQUAL 	">="

/* Bitwise */
BITWISE_AND    	"&"
BITWISE_OR     	"|"
BITWISE_XOR    	"\^"
TILDE          	"~"
LEFT_SHIFT     	"<<"
RIGHT_SHIFT    	">>"

/* Logical */
LOGICAL_NOT    	"!"
LOGICAL_OR      "||"
LOGICAL_AND     "&&"

/* With Equals */
PLUS_EQUAL   	"+="
MINUS_EQUAL   	"-="
STAR_EQUAL    	"*="
DIV_EQUAL     	"/="
MOD_EQUAL    	"%="
AND_EQUAL     	"&="
OR_EQUAL      	"|="
XOR_EQUAL    	"^="
LEFT_SHIFT_EQ  	"<<="
RIGHT_SHIFT_EQ 	">>="

/* Brackets */
RCURLY         	"}"
LCURLY          "{"
LSQUARE         "["
RSQUARE       	"]"
LROUND       	"("
RROUND     	    ")"

/* Punctuation */
DOT            	"\."
COMMA          	","
COLON          	":"
SEMICOLON      	";"
ARROW           "->"
QUESTION_MARK  	"?"

/* Extras */
DELIMITER       [ \n\t]
WHITESPACE      {DELIMITER}+
INCLUDE         ^#include.*\n
SCOMMENT        "\/\/.*"
RETURN          "return"
SIZEOF         	"sizeof"

/* Conditionals */
IF             	"if"
ELIF            "elif"
ELSE           	"else"
CASE           	"case"
SWITCH         	"switch"
DEFAULT        	"default"

/* Loops */
FOR            	"for"
WHILE          	"while"
DO             	"do"
UNTIL           "until"
BREAK         	"break"
CONTINUE       	"continue"
GOTO           	"goto"

/* Data Types */
INT       	    "int"
BOOL			"bool"
CHAR            "char"
DOUBLE         	"double"
LONG            "long"  
STRING          "string"
VOID            "void"
CONST           "const"
NULL            "null"
NULLPTR         "nullptr"
FUNCTION        "function"
AUTO            "auto"
TRUE            "true"
FALSE           "false"
STATIC         	"static"

/* Classes and Structs */
CLASS           "class"
STRUCT          "struct"
PUBLIC          "public"
PRIVATE         "private"
PROTECTED       "protected"

/* IO */
COUT            "cout"
CIN             "cin"
ENDL            "endl"

/* Dynamic Allocation */
NEW             "new"
DELETE          "delete"

/* Regex */
DIGIT               [0-9]
LETTER              [A-Za-z]
EXPONENT            [Ee][+-]?{DIGIT}+

IDENTIFIER          ({LETTER}|_)({LETTER}|_|{DIGIT})*
DECIMAL_LITERAL     {DIGIT}+
EXPONENT_LITERAL    {DIGIT}+[Ee][+-]?{DIGIT}+
DOUBLE_LITERAL      {DIGIT}+"."{DIGIT}+({EXPONENT})?
STRING_LITERAL      \"(\\.|[^\\"])*\"
CHARACTER_LITERAL   '((\\.)|[^'\\])'
INVALID_IDENTIFIER  ({DIGIT}+({LETTER}|_)+({DIGIT}|{LETTER}|_)*(\.{DIGIT}*)?)


%%
{WHITESPACE}          {}
{SCOMMENT}            {}
{INCLUDE}             {yylval.str = strdup(yytext); return INCLUDE;}

{PLUS}                {return PLUS;}
{MINUS}               {return MINUS;}
{STAR}                {return STAR;}
{DIVIDE}              {return DIVIDE;}
{MODULUS}             {return MODULUS;}
{ASSIGN}              {return ASSIGN;}
{INCREMENT}           {return INCREMENT;}
{DECREMENT}           {return DECREMENT;}
{EQUAL}               {return EQUAL;}
{NOT_EQUAL}           {return NOT_EQUAL;}
{LESS_THAN}           {return LESS_THAN;}
{GREATER_THAN}        {return GREATER_THAN;}
{LESS_EQUAL}          {return LESS_EQUAL;}
{GREATER_EQUAL}       {return GREATER_EQUAL;}
{BITWISE_AND}         {return BITWISE_AND;}
{BITWISE_OR}          {return BITWISE_OR;}
{BITWISE_XOR}         {return BITWISE_XOR;}
{TILDE}               {return TILDE;}
{LEFT_SHIFT}          {return LEFT_SHIFT;}
{RIGHT_SHIFT}         {return RIGHT_SHIFT;} 
{LOGICAL_NOT}         {return LOGICAL_NOT;}
{LOGICAL_OR}          {return LOGICAL_OR;}
{LOGICAL_AND}         {return LOGICAL_AND;}
{PLUS_EQUAL}          {return PLUS_EQUAL;}
{MINUS_EQUAL}         {return MINUS_EQUAL;}
{STAR_EQUAL}          {return STAR_EQUAL;}
{DIV_EQUAL}           {return DIV_EQUAL;}
{MOD_EQUAL}           {return MOD_EQUAL;}
{AND_EQUAL}           {return AND_EQUAL;}
{OR_EQUAL}            {return OR_EQUAL;}
{XOR_EQUAL}           {return XOR_EQUAL;}
{LEFT_SHIFT_EQ}       {return LEFT_SHIFT_EQ;}
{RIGHT_SHIFT_EQ}      {return RIGHT_SHIFT_EQ;}
{LCURLY}              {return LEFT_CURLY;}
{RCURLY}              {return RIGHT_CURLY;}
{LSQUARE}             {return LEFT_SQUARE;}
{RSQUARE}             {return RIGHT_SQUARE;}
{LROUND}              {return LEFT_ROUND;}
{RROUND}              {return RIGHT_ROUND;}
{DOT}                 {return DOT;}
{COMMA}               {return COMMA;}
{COLON}               {return COLON;}
{SEMICOLON}           {return SEMICOLON;}
{ARROW}               {return ARROW;}
{QUESTION_MARK}       {return QUESTION_MARK;}

{RETURN}              {yylval.str = strdup(yytext); return RETURN;}
{SIZEOF}              {yylval.str = strdup(yytext); return SIZEOF;}
{IF}                  {yylval.str = strdup(yytext); return IF;}
{ELIF}                {yylval.str = strdup(yytext); return ELIF;}
{ELSE}                {yylval.str = strdup(yytext); return ELSE;}
{CASE}                {yylval.str = strdup(yytext); return CASE;}
{SWITCH}              {yylval.str = strdup(yytext); return SWITCH;}
{DEFAULT}             {yylval.str = strdup(yytext); return DEFAULT;}
{FOR}                 {yylval.str = strdup(yytext); return FOR;}
{WHILE}               {yylval.str = strdup(yytext); return WHILE;}
{DO}                  {yylval.str = strdup(yytext); return DO;}
{UNTIL}               {yylval.str = strdup(yytext); return UNTIL;}
{BREAK}               {yylval.str = strdup(yytext); return BREAK;}
{CONTINUE}            {yylval.str = strdup(yytext); return CONTINUE;}
{GOTO}                {yylval.str = strdup(yytext); return GOTO;}
 
{INT}                 {yylval.str = strdup(yytext); return INT;}
{BOOL}                {yylval.str = strdup(yytext); return BOOL;}
{CHAR}                {yylval.str = strdup(yytext); return CHAR;}
{DOUBLE}              {yylval.str = strdup(yytext); return DOUBLE;}
{LONG}                {yylval.str = strdup(yytext); return LONG;}
{STRING}              {yylval.str = strdup(yytext); return STRING;}
{VOID}                {yylval.str = strdup(yytext); return VOID;}
{CONST}               {yylval.str = strdup(yytext); return CONST;}
{NULL}                {yylval.str = strdup(yytext); return NULL;}
{NULLPTR}             {yylval.str = strdup(yytext); return NULLPTR;}
{FUNCTION}            {yylval.str = strdup(yytext); return FUNCTION;}
{AUTO}                {yylval.str = strdup(yytext); return AUTO;}
{TRUE}                {yylval.str = strdup(yytext); return TRUE;}
{FALSE}               {yylval.str = strdup(yytext); return FALSE;}
{STATIC}              {yylval.str = strdup(yytext); return STATIC;}
 
{CLASS}               {yylval.str = strdup(yytext); return CLASS;}
{STRUCT}              {yylval.str = strdup(yytext); return STRUCT;}
{PUBLIC}              {yylval.str = strdup(yytext); return PUBLIC;}
{PRIVATE}             {yylval.str = strdup(yytext); return PRIVATE;}
{PROTECTED}           {yylval.str = strdup(yytext); return PROTECTED;}
{COUT}                {yylval.str = strdup(yytext); return COUT;}
{CIN}                 {yylval.str = strdup(yytext); return CIN;}
{ENDL}                {yylval.str = strdup(yytext); return ENDL;}
{NEW}                 {yylval.str = strdup(yytext); return NEW;}
{DELETE}              {yylval.str = strdup(yytext); return DELETE;}
 
{IDENTIFIER}          {yylval.str = strdup(yytext); return IDENTIFIER;}
{DECIMAL_LITERAL}     {yylval.str = strdup(yytext); return DECIMAL_LITERAL;}
{EXPONENT_LITERAL}    {yylval.str = strdup(yytext); return EXPONENT_LITERAL;}
{DOUBLE_LITERAL}      {yylval.str = strdup(yytext); return DOUBLE_LITERAL;}
{STRING_LITERAL}      {yylval.str = strdup(yytext); return STRING_LITERAL;}
{CHARACTER_LITERAL}   {yylval.str = strdup(yytext); return CHARACTER_LITERAL;}
{INVALID_IDENTIFIER}  {fprintf(stderr,"Invalid identifier: %s at line %d\n",yytext,yylineno); return INVALID_IDENTIFIER;}
.                     {fprintf(stderr,"Invalid token: %s at line %d\n",yytext,yylineno); return yytext[0];}  

%%