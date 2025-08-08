%option noyywrap yylineno
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
        int line;
        entry(string lex_v, string token_v, int line_v) : lexeme(lex_v), token(token_v), line(line_v) {}
    };

    #define pb push_back    
    vector<entry> table;
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
LSQUARE         "]"
RSQUARE       	"["
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

{INCLUDE}             { string txt(yytext,yyleng);
                        if(!txt.empty() && txt.back()=='\n') txt.pop_back();
                        table.pb(entry(txt,"INCLUDE",yylineno-1));}

{PLUS}                {table.pb(entry(yytext,"PLUS",yylineno));}
{MINUS}               {table.pb(entry(yytext,"MINUS",yylineno));}
{STAR}                {table.pb(entry(yytext,"STAR",yylineno));}
{DIVIDE}              {table.pb(entry(yytext,"DIVIDE",yylineno));}
{MODULUS}             {table.pb(entry(yytext,"MODULUS",yylineno));}
{ASSIGN}              {table.pb(entry(yytext,"ASSIGN",yylineno));}
{INCREMENT}           {table.pb(entry(yytext,"INCREMENT",yylineno));}
{DECREMENT}           {table.pb(entry(yytext,"DECREMENT",yylineno));}

{EQUAL}               {table.pb(entry(yytext,"EQUAL",yylineno));}
{NOT_EQUAL}           {table.pb(entry(yytext,"NOT_EQUAL",yylineno));}
{LESS_THAN}           {table.pb(entry(yytext,"LESS_THAN",yylineno));}
{GREATER_THAN}        {table.pb(entry(yytext,"GREATER_THAN",yylineno));}
{LESS_EQUAL}          {table.pb(entry(yytext,"LESS_EQUAL",yylineno));}
{GREATER_EQUAL}       {table.pb(entry(yytext,"GREATER_EQUAL",yylineno));}

{BITWISE_AND}         {table.pb(entry(yytext,"BITWISE_AND",yylineno));}
{BITWISE_OR}          {table.pb(entry(yytext,"BITWISE_OR",yylineno));}
{BITWISE_XOR}         {table.pb(entry(yytext,"BITWISE_XOR",yylineno));}
{TILDE}               {table.pb(entry(yytext,"TILDE",yylineno));}
{LEFT_SHIFT}          {table.pb(entry(yytext,"LEFT_SHIFT",yylineno));}
{RIGHT_SHIFT}         {table.pb(entry(yytext,"RIGHT_SHIFT",yylineno));} 

{LOGICAL_NOT}         {table.pb(entry(yytext,"LOGICAL_NOT",yylineno));}
{LOGICAL_OR}          {table.pb(entry(yytext,"LOGICAL_OR",yylineno));}
{LOGICAL_AND}         {table.pb(entry(yytext,"LOGICAL_AND",yylineno));}

{PLUS_EQUAL}          {table.pb(entry(yytext,"PLUS_EQUAL",yylineno));}
{MINUS_EQUAL}         {table.pb(entry(yytext,"MINUS_EQUAL",yylineno));}
{STAR_EQUAL}          {table.pb(entry(yytext,"STAR_EQUAL",yylineno));}
{DIV_EQUAL}           {table.pb(entry(yytext,"DIV_EQUAL",yylineno));}
{MOD_EQUAL}           {table.pb(entry(yytext,"MOD_EQUAL",yylineno));}
{AND_EQUAL}           {table.pb(entry(yytext,"AND_EQUAL",yylineno));}
{OR_EQUAL}            {table.pb(entry(yytext,"OR_EQUAL",yylineno));}
{XOR_EQUAL}           {table.pb(entry(yytext,"XOR_EQUAL",yylineno));}
{LEFT_SHIFT_EQ}       {table.pb(entry(yytext,"LEFT_SHIFT_EQ",yylineno));}
{RIGHT_SHIFT_EQ}      {table.pb(entry(yytext,"RIGHT_SHIFT_EQ",yylineno));}

{LCURLY}              {table.pb(entry(yytext,"LEFT_CURLY",yylineno));}
{RCURLY}              {table.pb(entry(yytext,"RIGHT_CURLY",yylineno));}
{LSQUARE}             {table.pb(entry(yytext,"LEFT_SQUARE",yylineno));}
{RSQUARE}             {table.pb(entry(yytext,"RIGHT_SQUARE",yylineno));}
{LROUND}              {table.pb(entry(yytext,"LEFT_ROUND",yylineno));}
{RROUND}              {table.pb(entry(yytext,"RIGHT_ROUND",yylineno));}

{DOT}                 {table.pb(entry(yytext,"DOT",yylineno));}
{COMMA}               {table.pb(entry(yytext,"COMMA",yylineno));}
{COLON}               {table.pb(entry(yytext,"COLON",yylineno));}
{SEMICOLON}           {table.pb(entry(yytext,"SEMICOLON",yylineno));}
{ARROW}               {table.pb(entry(yytext,"ARROW",yylineno));}
{QUESTION_MARK}       {table.pb(entry(yytext,"QUESTION_MARK",yylineno));}

{SCOMMENT}            {table.pb(entry(yytext,"SINGLE_COMMENT",yylineno));}
{RETURN}              {table.pb(entry(yytext,"RETURN",yylineno));}
{SIZEOF}              {table.pb(entry(yytext,"SIZEOF",yylineno));}

{IF}                  {table.pb(entry(yytext,"IF",yylineno));}
{ELIF}                {table.pb(entry(yytext,"ELIF",yylineno));}
{ELSE}                {table.pb(entry(yytext,"ELSE",yylineno));}
{CASE}                {table.pb(entry(yytext,"CASE",yylineno));}
{SWITCH}              {table.pb(entry(yytext,"SWITCH",yylineno));}
{DEFAULT}             {table.pb(entry(yytext,"DEFAULT",yylineno));}
 
{FOR}                 {table.pb(entry(yytext,"FOR",yylineno));}
{WHILE}               {table.pb(entry(yytext,"WHILE",yylineno));}
{DO}                  {table.pb(entry(yytext,"DO",yylineno));}
{UNTIL}               {table.pb(entry(yytext,"UNTIL",yylineno));}
{BREAK}               {table.pb(entry(yytext,"BREAK",yylineno));}
{CONTINUE}            {table.pb(entry(yytext,"CONTINUE",yylineno));}
{GOTO}                {table.pb(entry(yytext,"GOTO",yylineno));}
 
{INT}                 {table.pb(entry(yytext,"INT",yylineno));}
{BOOL}                {table.pb(entry(yytext,"BOOL",yylineno));}
{CHAR}                {table.pb(entry(yytext,"CHAR",yylineno));}
{DOUBLE}              {table.pb(entry(yytext,"DOUBLE",yylineno));}
{LONG}                {table.pb(entry(yytext,"LONG",yylineno));}
{STRING}              {table.pb(entry(yytext,"STRING",yylineno));}
{VOID}                {table.pb(entry(yytext,"VOID",yylineno));}
{CONST}               {table.pb(entry(yytext,"CONST",yylineno));}
{NULL}                {table.pb(entry(yytext,"NULL",yylineno));}
{NULLPTR}             {table.pb(entry(yytext,"NULLPTR",yylineno));}
{FUNCTION}            {table.pb(entry(yytext,"FUNCTION",yylineno));}
{AUTO}                {table.pb(entry(yytext,"AUTO",yylineno));}
{TRUE}                {table.pb(entry(yytext,"TRUE",yylineno));}
{FALSE}               {table.pb(entry(yytext,"FALSE",yylineno));}
{STATIC}              {table.pb(entry(yytext,"STATIC",yylineno));}
 
{CLASS}               {table.pb(entry(yytext,"CLASS",yylineno));}
{STRUCT}              {table.pb(entry(yytext,"STRUCT",yylineno));}
{PUBLIC}              {table.pb(entry(yytext,"PUBLIC",yylineno));}
{PRIVATE}             {table.pb(entry(yytext,"PRIVATE",yylineno));}
{PROTECTED}           {table.pb(entry(yytext,"PROTECTED",yylineno));}
 
{COUT}                {table.pb(entry(yytext,"COUT",yylineno));}
{CIN}                 {table.pb(entry(yytext,"CIN",yylineno));}
{ENDL}                {table.pb(entry(yytext,"ENDL",yylineno));}
 
{NEW}                 {table.pb(entry(yytext,"NEW",yylineno));}
{DELETE}              {table.pb(entry(yytext,"DELETE",yylineno));}
 
{IDENTIFIER}          {table.pb(entry(yytext,"IDENTIFIER",yylineno));}
{DECIMAL_LITERAL}     {table.pb(entry(yytext,"DECIMAL_LITERAL",yylineno));}
{EXPONENT_LITERAL}    {table.pb(entry(yytext,"EXPONENT_LITERAL",yylineno));}
{DOUBLE_LITERAL}      {table.pb(entry(yytext,"DOUBLE_LITERAL",yylineno));}
{STRING_LITERAL}      {table.pb(entry(yytext,"STRING_LITERAL",yylineno));}
{CHARACTER_LITERAL}   {table.pb(entry(yytext,"CHARACTER_LITERAL",yylineno));}
{INVALID_IDENTIFIER}  {table.pb(entry(yytext,"INVALID_IDENTIFIER",yylineno));}

%%

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    string in_file = argv[1];
    string out_file = argv[2];

    ifstream inputFile(in_file);
    if (!inputFile)
    {
        cerr << "Error opening file: " << in_file << endl;
        return 1;
    }

    ofstream file(out_file);
    if (!file)
    {
        cerr << "Error creating output file: " << out_file << endl;
        return 1;
    }

    yyin = fopen(argv[1], "r");
    yylex();

    file << "+---------+---------------------+--------------------------+\n";
    file << "| Line No | Lexeme              | Token                    |\n";
    file << "+---------+---------------------+--------------------------+\n";

    for (auto &t : table)
    {
        file << "| " << left << setw(8) << t.line << "| "
             << left << setw(20) << t.lexeme << "| "
             << left << setw(25) << t.token << "|\n";
        file << "+---------+---------------------+--------------------------+\n";
    }

    file.close();
    return 0;
}
