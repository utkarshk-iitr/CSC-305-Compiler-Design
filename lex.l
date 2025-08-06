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
{INCLUDE}             {table.push_back(entry(yytext,"INCLUDE"));}

{PLUS}                {table.push_back(entry(yytext,"PLUS"));}
{MINUS}               {table.push_back(entry(yytext,"MINUS"));}
{STAR}                {table.push_back(entry(yytext,"STAR"));}
{DIVIDE}              {table.push_back(entry(yytext,"DIVIDE"));}
{MODULUS}             {table.push_back(entry(yytext,"MODULUS"));}
{ASSIGN}              {table.push_back(entry(yytext,"ASSIGN"));}
{INCREMENT}           {table.push_back(entry(yytext,"INCREMENT"));}
{DECREMENT}           {table.push_back(entry(yytext,"DECREMENT"));}

{EQUAL}               {table.push_back(entry(yytext,"EQUAL"));}
{NOT_EQUAL}           {table.push_back(entry(yytext,"NOT_EQUAL"));}
{LESS_THAN}           {table.push_back(entry(yytext,"LESS_THAN"));}
{GREATER_THAN}        {table.push_back(entry(yytext,"GREATER_THAN"));}
{LESS_EQUAL}          {table.push_back(entry(yytext,"LESS_EQUAL"));}
{GREATER_EQUAL}       {table.push_back(entry(yytext,"GREATER_EQUAL"));}

{BITWISE_AND}         {table.push_back(entry(yytext,"BITWISE_AND"));}
{BITWISE_OR}          {table.push_back(entry(yytext,"BITWISE_OR"));}
{BITWISE_XOR}         {table.push_back(entry(yytext,"BITWISE_XOR"));}
{TILDE}               {table.push_back(entry(yytext,"TILDE"));}
{LEFT_SHIFT}          {table.push_back(entry(yytext,"LEFT_SHIFT"));}
{RIGHT_SHIFT}         {table.push_back(entry(yytext,"RIGHT_SHIFT"));} 

{LOGICAL_NOT}         {table.push_back(entry(yytext,"LOGICAL_NOT"));}
{LOGICAL_OR}          {table.push_back(entry(yytext,"LOGICAL_OR"));}
{LOGICAL_AND}         {table.push_back(entry(yytext,"LOGICAL_AND"));}

{PLUS_EQUAL}          {table.push_back(entry(yytext,"PLUS_EQUAL"));}
{MINUS_EQUAL}         {table.push_back(entry(yytext,"MINUS_EQUAL"));}
{STAR_EQUAL}          {table.push_back(entry(yytext,"STAR_EQUAL"));}
{DIV_EQUAL}           {table.push_back(entry(yytext,"DIV_EQUAL"));}
{MOD_EQUAL}           {table.push_back(entry(yytext,"MOD_EQUAL"));}
{AND_EQUAL}           {table.push_back(entry(yytext,"AND_EQUAL"));}
{OR_EQUAL}            {table.push_back(entry(yytext,"OR_EQUAL"));}
{XOR_EQUAL}           {table.push_back(entry(yytext,"XOR_EQUAL"));}
{LEFT_SHIFT_EQ}       {table.push_back(entry(yytext,"LEFT_SHIFT_EQ"));}
{RIGHT_SHIFT_EQ}      {table.push_back(entry(yytext,"RIGHT_SHIFT_EQ"));}

{LCURLY}              {table.push_back(entry(yytext,"LEFT_CURLY"));}
{RCURLY}              {table.push_back(entry(yytext,"RIGHT_CURLY"));}
{LSQUARE}             {table.push_back(entry(yytext,"LEFT_SQUARE"));}
{RSQUARE}             {table.push_back(entry(yytext,"RIGHT_SQUARE"));}
{LROUND}              {table.push_back(entry(yytext,"LEFT_ROUND"));}
{RROUND}              {table.push_back(entry(yytext,"RIGHT_ROUND"));}

{DOT}                 {table.push_back(entry(yytext,"DOT"));}
{COMMA}               {table.push_back(entry(yytext,"COMMA"));}
{COLON}               {table.push_back(entry(yytext,"COLON"));}
{SEMICOLON}           {table.push_back(entry(yytext,"SEMICOLON"));}
{ARROW}               {table.push_back(entry(yytext,"ARROW"));}
{QUESTION_MARK}       {table.push_back(entry(yytext,"QUESTION_MARK"));}

{SCOMMENT}            {table.push_back(entry(yytext,"SINGLE_COMMENT"));}
{RETURN}              {table.push_back(entry(yytext,"RETURN"));}
{SIZEOF}              {table.push_back(entry(yytext,"SIZEOF"));}

{IF}                 {table.push_back(entry(yytext,"IF"));}
{ELIF}               {table.push_back(entry(yytext,"ELIF"));}
{ELSE}               {table.push_back(entry(yytext,"ELSE"));}
{CASE}               {table.push_back(entry(yytext,"CASE"));}
{SWITCH}             {table.push_back(entry(yytext,"SWITCH"));}
{DEFAULT}            {table.push_back(entry(yytext,"DEFAULT"));}

{FOR}                {table.push_back(entry(yytext,"FOR"));}
{WHILE}              {table.push_back(entry(yytext,"WHILE"));}
{DO}                 {table.push_back(entry(yytext,"DO"));}
{UNTIL}              {table.push_back(entry(yytext,"UNTIL"));}
{BREAK}              {table.push_back(entry(yytext,"BREAK"));}
{CONTINUE}           {table.push_back(entry(yytext,"CONTINUE"));}
{GOTO}               {table.push_back(entry(yytext,"GOTO"));}

{INT}                {table.push_back(entry(yytext,"INT"));}
{BOOL}               {table.push_back(entry(yytext,"BOOL"));}
{CHAR}               {table.push_back(entry(yytext,"CHAR"));}
{DOUBLE}             {table.push_back(entry(yytext,"DOUBLE"));}
{LONG}               {table.push_back(entry(yytext,"LONG"));}
{STRING}             {table.push_back(entry(yytext,"STRING"));}
{VOID}               {table.push_back(entry(yytext,"VOID"));}
{CONST}              {table.push_back(entry(yytext,"CONST"));}
{NULL}               {table.push_back(entry(yytext,"NULL"));}
{NULLPTR}            {table.push_back(entry(yytext,"NULLPTR"));}
{FUNCTION}           {table.push_back(entry(yytext,"FUNCTION"));}
{AUTO}               {table.push_back(entry(yytext,"AUTO"));}
{TRUE}               {table.push_back(entry(yytext,"TRUE"));}
{FALSE}              {table.push_back(entry(yytext,"FALSE"));}
{STATIC}             {table.push_back(entry(yytext,"STATIC"));}

{CLASS}              {table.push_back(entry(yytext,"CLASS"));}
{STRUCT}             {table.push_back(entry(yytext,"STRUCT"));}
{PUBLIC}             {table.push_back(entry(yytext,"PUBLIC"));}
{PRIVATE}            {table.push_back(entry(yytext,"PRIVATE"));}
{PROTECTED}          {table.push_back(entry(yytext,"PROTECTED"));}

{COUT}               {table.push_back(entry(yytext,"COUT"));}
{CIN}                {table.push_back(entry(yytext,"CIN"));}
{NEW}                {table.push_back(entry(yytext,"NEW"));}
{DELETE}             {table.push_back(entry(yytext,"DELETE"));}

{IDENTIFIER}         {table.push_back(entry(yytext,"IDENTIFIER"));}
{DECIMAL_LITERAL}    {table.push_back(entry(yytext,"DECIMAL_LITERAL"));}
{EXPONENT_LITERAL}   {table.push_back(entry(yytext,"EXPONENT_LITERAL"));}
{DOUBLE_LITERAL}     {table.push_back(entry(yytext,"DOUBLE_LITERAL"));}
{STRING_LITERAL}     {table.push_back(entry(yytext,"STRING_LITERAL"));}
{CHARACTER_LITERAL}  {table.push_back(entry(yytext,"CHARACTER_LITERAL"));}

%%

int main(int argc,char** argv){
    if(argc<3){
        cerr<<"Usage: "<<argv[0]<<" <input_file> <output_file>"<<endl;
        return 1;
    }

    string in_file = argv[1];
    string out_file = argv[2];

    ifstream inputFile(in_file);
    if(!inputFile){
        cerr<<"Error opening file: "<<in_file<<endl;
        return 1;
    }

    system("mkdir -p output");
    ofstream file(out_file);
    if(!file){
        cerr<<"Error creating output file: "<<out_file<<endl;
        return 1;
    }

    yyin = fopen(argv[1],"r");
    yylex();

    file<<"Tokens generated are \n\n";
    file << "+----------------+--------------------------+\n";
    file << "| Lexeme         | Token Type               |\n";
    file << "+----------------+--------------------------+\n";

    for(auto &t:tokens){
        file<<"| "<<left<<setw(15)<<t.lexeme<<"| "<<left<<setw(25)<<t.token<<"|\n";
        file<<"+----------------+--------------------------+\n";
    }

    file.close();
    return 0;
}
