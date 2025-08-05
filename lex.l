%option noyywrap
%{
    #include <iostream>
    #include <iomanip>
    #include <cstdio> 
    #include <vector>
    #include <string>
    #include <fstream>

    extern "C" int yylex();
    using namespace std;

    class entry
    {
    public:
        string token;
        string lexeme;
        entry(string lex_v,string token_v) : lexeme(lex_v), token(token_v) {}
    };

    vector<entry> table;
    // vector<string> errors;
%}

%option yylineno

// Arithmetic
PLUS            "+"
MINUS           "-"
STAR      	    "*"
DIVIDE        	"/"
MODULUS        	"%"
ASSIGN        	"="
INCREMENT      	"++"
DECREMENT      	"--"

// Comparision
EQUAL       	"=="
NOT_EQUAL     	"!="
LESS_THAN      	"<"
GREATER_THAN   	">"
LESS_EQUAL    	"<="
GREATER_EQUAL 	">="

// Bitwise
BITWISE_AND    	"&"
BITWISE_OR     	"|"
BITWISE_XOR    	"\^"
TILDE          	"~"
LEFT_SHIFT     	"<<"
RIGHT_SHIFT    	">>"

// Logical
LOGICAL_NOT    	"!"
LOGICAL_OR      "||"
LOGICAL_AND     "&&"

// With Equals
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

// Brackets
RCURLY         	"}"
LCURLY          "{"
LSQUARE         "]"
RSQUARE       	"["
LROUND       	"("
RROUND     	    ")"

// Punctuation
DOT            	"\."
COMMA          	","
COLON          	":"
SEMICOLON      	";"
ARROW           "->"
QUESTION_MARK  	"?"

// Extras
DELIMITER       [ \n\t]
WHITESPACE      {DELIMITER}+

INCLUDE         ^#include.*\n
SCOMMENT        "\/\/.*"
RETURN          "return"
SIZEOF         	"sizeof"

// Conditionals
IF             	"if"
ELIF            "elif"
ELSE           	"else"
CASE           	"case"
SWITCH         	"switch"
DEFAULT        	"default"

// Loops
FOR            	"for"
WHILE          	"while"
DO             	"do"
UNTIL           "until"
BREAK         	"break"
CONTINUE       	"continue"
GOTO           	"goto"

// Data Types
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

// Classes and Structs
CLASS           "class"
STRUCT          "struct"
PUBLIC          "public"
PRIVATE         "private"
PROTECTED       "protected"

// IO
COUT            "cout"
CIN             "cin"

// Dynamic Allocation
NEW             "new"
DELETE          "delete"

// Regex
DIGIT               [0-9]
LETTER              [A-Za-z]
NOTLETTER           [^A-Za-z_]
EXPONENT            [Ee][+-]?{DIGIT}+

IDENTIFIER          ({LETTER}|_)({LETTER}|_|{DIGIT})*

DECIMAL_LITERAL     {DIGIT}+

EXPONENT_LITERAL    {DIGIT}+[Ee][+-]?{DIGIT}+

DOUBLE_LITERAL      {DIGIT}+"."{DIGIT}+({EXPONENT})?

STRING_LITERAL      \"(\\.|[^\\"])*\"

CHARACTER_LITERAL   '((\\.)|[^'\\])'

INVALID_IDENTIFIER  ({DIGIT}+({LETTER}|_)+({DIGIT}|{LETTER}|_)*(\.{DIGIT}*)?)

