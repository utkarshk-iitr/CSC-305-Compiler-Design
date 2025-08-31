%{
    #include <iostream>
    #include <string.h>
    #include <iomanip>
    #include <vector>
    #include <string>
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

    void print_symbol_table() {
        cout<<"---------------------------------------------------------\n";
        cout<<left<<setw(15)<<"NAME"<<setw(15)<<"DATATYPE"<<setw(15)<<"TYPE"<<setw(10)<<"LINE\n";
        cout<<"---------------------------------------------------------\n";
        for(int i=0;i<count_symbol;i++) {
            cout<<left<<setw(15)<<symbol_table[i].id_name
                <<setw(15)<<symbol_table[i].data_type
                <<setw(15)<<symbol_table[i].type
                <<setw(10)<<symbol_table[i].line_no<<"\n";
        }
        cout<<"---------------------------------------------------------\n";
    }

    void print_constant_table() {
        cout<<"---------------------------------------------------------\n";
        cout<<left<<setw(20)<<"VALUE"<<setw(15)<<"TYPE"<<setw(10)<<"LINE\n";
        cout<<"---------------------------------------------------------\n";
        for(int i=0;i<count_const;i++) {
            cout<<left<<setw(20)<<const_table[i].value
                <<setw(15)<<const_table[i].type
                <<setw(10)<<const_table[i].line_no<<"\n";
        }
        cout<<"---------------------------------------------------------\n";
    }

    void insert_symbol_table (char* yytext, const char* data_type, const char* type) {
        symbol_table[count_symbol].id_name   = yytext;
        symbol_table[count_symbol].data_type = data_type;
        symbol_table[count_symbol].type      = type;
        symbol_table[count_symbol].line_no   = yylineno;
        count_symbol++;
    }

    void insert_const_symbol_table(char ch, char* yytext) {
        string type;
        switch(ch) {
            case 'I': type = "INT";     break;
            case 'D': type = "DOUBLE";  break;
            case 'E': type = "EXP";     break;
            case 'C': type = "CHAR";    break;
            case 'S': type = "STRING";  break;
            case 'B': type = "BOOL";    break;
            case 'N': type = "NULLPTR"; break;
            default:  type = "UNKNOWN"; break;
        }
        const_table[count_const].value  = yytext;
        const_table[count_const].type   = type;
        const_table[count_const].line_no= yylineno;
        count_const++;
    }

    void yyerror(const char *s) {
        cerr << "Error: " << s << " at line " << yylineno << " near '" << yytext << "'" << endl;
    }

    string data_type = "";
%}

%union { 
    char *str; 
}

/* ===== Tokens from your lexer.l (canonical set) ===== */
%token<str> INCLUDE
%token<str> PLUS MINUS STAR DIVIDE MODULUS ASSIGN
%token<str> INCREMENT DECREMENT
%token<str> EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%token<str> BITWISE_AND BITWISE_OR BITWISE_XOR
%token<str> LEFT_SHIFT RIGHT_SHIFT ARROW
%token<str> LOGICAL_NOT LOGICAL_AND LOGICAL_OR
%token<str> PLUS_EQUAL MINUS_EQUAL STAR_EQUAL DIV_EQUAL MOD_EQUAL
%token<str> AND_EQUAL OR_EQUAL XOR_EQUAL
%token<str> LEFT_SHIFT_EQ RIGHT_SHIFT_EQ

%token<str> LROUND RROUND LCURLY RCURLY LSQUARE RSQUARE
%token<str> SEMICOLON COLON COMMA DOT QUESTION_MARK 
%token<str> TILDE

%token<str> IF ELSE ELIF SWITCH CASE DEFAULT WHILE DO FOR GOTO CONTINUE BREAK RETURN UNTIL
%token<str> SIZEOF

%token<str> VOID INT DOUBLE CHAR BOOL STRING LONG
%token<str> TRUE FALSE NULLPTR
%token<str> AUTO STATIC CONST
%token<str> CLASS STRUCT PUBLIC PRIVATE PROTECTED
%token<str> DELETE NEW CIN COUT ENDL

%token<str> IDENTIFIER
%token<str> DECIMAL_LITERAL DOUBLE_LITERAL EXPONENT_LITERAL CHARACTER_LITERAL STRING_LITERAL
%token<str> FUNCTION
%token<str> INVALID_IDENTIFIER

/* Types for nonterminals that carry strings */
%type<str> translation_unit external_declaration declaration declaration_specifiers init_declarator_list init_declarator
%type<str> declarator direct_declarator pointer constant initializer initializer_list assignment_operator
%type<str> statement compound_statement block_item_list block_item expression assignment_expression
%type<str> conditional_expression logical_or_expression logical_and_expression inclusive_or_expression
%type<str> exclusive_or_expression and_expression equality_expression relational_expression
%type<str> shift_expression additive_expression multiplicative_expression cast_expression unary_expression
%type<str> postfix_expression primary_expression argument_expression_list argument_expression_list_opt
%type<str> selection_statement iteration_statement jump_statement
%type<str> class_specifier member_specification member_declaration member_declarator_list member_declarator
%type<str> parameter_type_list parameter_list parameter_declaration
%type<str> type_specifier storage_class_specifier
%type<str> initializer_opt constant_expression_opt
%type<str> expression_opt

%start translation_unit

%%

translation_unit
    : /* empty */
    | translation_unit external_declaration
    ;

external_declaration
    : declaration
    | function_definition
    | class_specifier
    | INCLUDE
    | FUNCTION                 /* harmless if your lexer emits it */
    ;

/* ---------- Declarations ---------- */
declaration
    : declaration_specifiers SEMICOLON
    | declaration_specifiers init_declarator_list SEMICOLON
    ;

declaration_specifiers
    : storage_class_specifier
    | storage_class_specifier declaration_specifiers 
    | type_specifier
    | type_specifier declaration_specifiers
    ;

storage_class_specifier
    : AUTO
    | STATIC
    | CONST
    ;

type_specifier
    : VOID      { data_type = "VOID"; }
    | INT       { data_type = "INT"; }
    | LONG      { data_type = "LONG"; }
    | DOUBLE    { data_type = "DOUBLE"; }
    | CHAR      { data_type = "CHAR"; }
    | BOOL      { data_type = "BOOL"; }
    | STRING    { data_type = "STRING"; }
    | STRUCT    { data_type = "STRUCT"; }
    | CLASS     { data_type = "CLASS"; }
    ;

init_declarator_list
    : init_declarator
    | init_declarator_list COMMA init_declarator
    ;

init_declarator
    : declarator                           { insert_symbol_table($1, data_type.c_str(), "IDENTIFIER"); }
    | declarator ASSIGN initializer        { insert_symbol_table($1, data_type.c_str(), "IDENTIFIER"); }
    ;

declarator
    : pointer direct_declarator            { $$ = $2; }
    | direct_declarator                    { $$ = $1; }
    ;

pointer
    : STAR
    | STAR pointer
    ;

direct_declarator
    : IDENTIFIER                           { $$ = $1; }
    | LROUND declarator RROUND                     { $$ = $2; }
    | direct_declarator LROUND parameter_type_list RROUND
    | direct_declarator LROUND RROUND
    | direct_declarator LSQUARE constant_expression_opt RSQUARE
    ;

parameter_type_list
    : parameter_list
    ;

parameter_list
    : parameter_declaration
    | parameter_list COMMA parameter_declaration
    ;

parameter_declaration
    : declaration_specifiers declarator    { insert_symbol_table($2, data_type.c_str(), "PARAM"); }
    | declaration_specifiers               /* e.g., void */
    ;

/* ---------- Class / Struct ---------- */
class_specifier
    : CLASS  IDENTIFIER LCURLY member_specification RCURLY
    | STRUCT IDENTIFIER LCURLY member_specification RCURLY
    ;

member_specification
    : /* empty */
    | member_specification member_declaration
    ;

member_declaration
    : PUBLIC COLON
    | PRIVATE COLON
    | PROTECTED COLON
    | declaration_specifiers member_declarator_list SEMICOLON
    | declaration_specifiers SEMICOLON
    ;

member_declarator_list
    : member_declarator
    | member_declarator_list COMMA member_declarator
    ;

member_declarator
    : declarator                            { insert_symbol_table($1, data_type.c_str(), "MEMBER"); }
    ;

/* ---------- Function definitions ---------- */
function_definition
    : type_specifier declarator compound_statement { insert_symbol_table($2, data_type.c_str(), "FUNCTION"); }
    | declarator compound_statement
    ;

/* ---------- Statements ---------- */
statement
    : compound_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | expression SEMICOLON
    | SEMICOLON
    ;

compound_statement
    : LCURLY RCURLY
    | LCURLY block_item_list RCURLY
    ;

block_item_list
    : block_item
    | block_item_list block_item
    ;

block_item
    : declaration
    | statement
    ;

/* Selection */
selection_statement
    : IF LROUND expression RROUND statement
    | IF LROUND expression RROUND statement ELSE statement
    | SWITCH LROUND expression RROUND statement
    ;

/* Iteration */
iteration_statement
    : WHILE LROUND expression RROUND statement
    | DO statement WHILE LROUND expression RROUND SEMICOLON
    | FOR LROUND expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RROUND statement
    ;

expression_opt
    : /* empty */
    | expression
    ;

/* Jump */
jump_statement
    : GOTO IDENTIFIER SEMICOLON
    | CONTINUE SEMICOLON
    | BREAK SEMICOLON
    | RETURN SEMICOLON
    | RETURN expression SEMICOLON
    ;

/* ---------- Expressions ---------- */
expression
    : assignment_expression
    | expression COMMA assignment_expression
    ;

assignment_expression
    : conditional_expression
    | unary_expression assignment_operator assignment_expression
    ;

assignment_operator
    : ASSIGN
    | PLUS_EQUAL
    | MINUS_EQUAL
    | STAR_EQUAL
    | DIV_EQUAL
    | MOD_EQUAL
    | AND_EQUAL
    | OR_EQUAL
    | XOR_EQUAL
    | LEFT_SHIFT_EQ
    | RIGHT_SHIFT_EQ
    ;

conditional_expression
    : logical_or_expression
    | logical_or_expression QUESTION_MARK expression COLON conditional_expression
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression LOGICAL_OR logical_and_expression
    ;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression LOGICAL_AND inclusive_or_expression
    ;

inclusive_or_expression
    : exclusive_or_expression
    | inclusive_or_expression BITWISE_OR exclusive_or_expression
    ;

exclusive_or_expression
    : and_expression
    | exclusive_or_expression BITWISE_XOR and_expression
    ;

and_expression
    : equality_expression
    | and_expression BITWISE_AND equality_expression
    ;

equality_expression
    : relational_expression
    | equality_expression EQUAL relational_expression
    | equality_expression NOT_EQUAL relational_expression
    ;

relational_expression
    : shift_expression
    | relational_expression LESS_THAN shift_expression
    | relational_expression GREATER_THAN shift_expression
    | relational_expression LESS_EQUAL shift_expression
    | relational_expression GREATER_EQUAL shift_expression
    ;

shift_expression
    : additive_expression
    | shift_expression LEFT_SHIFT  additive_expression
    | shift_expression RIGHT_SHIFT additive_expression
    ;

additive_expression
    : multiplicative_expression
    | additive_expression PLUS  multiplicative_expression
    | additive_expression MINUS multiplicative_expression
    ;

multiplicative_expression
    : cast_expression
    | multiplicative_expression STAR   cast_expression
    | multiplicative_expression DIVIDE cast_expression
    | multiplicative_expression MODULUS cast_expression
    ;

cast_expression
    : unary_expression
    | LROUND type_specifier RROUND cast_expression
    ;

unary_expression
    : postfix_expression
    | INCREMENT unary_expression
    | DECREMENT unary_expression
    | PLUS  unary_expression
    | MINUS unary_expression
    | LOGICAL_NOT unary_expression
    | TILDE unary_expression
    | SIZEOF unary_expression
    | SIZEOF LROUND type_specifier RROUND
    ;

postfix_expression
    : primary_expression
    | postfix_expression LSQUARE expression RSQUARE
    | postfix_expression LROUND RROUND
    | postfix_expression LROUND argument_expression_list RROUND
    | postfix_expression DOT IDENTIFIER
    | postfix_expression ARROW IDENTIFIER
    | postfix_expression INCREMENT
    | postfix_expression DECREMENT
    | NEW type_specifier
    | DELETE unary_expression
    ;

primary_expression
    : IDENTIFIER
    | constant
    | STRING_LITERAL                      { insert_const_symbol_table('S',$1); }
    | LROUND expression RROUND
    | COUT LEFT_SHIFT argument_expression_list
    | CIN  RIGHT_SHIFT IDENTIFIER         { insert_symbol_table($3, "IO", "IO"); }
    | ENDL
    | INVALID_IDENTIFIER                  /* token exists; ignore semantically */
    ;

argument_expression_list_opt
    : /* empty */
    | argument_expression_list
    ;

argument_expression_list
    : assignment_expression
    | argument_expression_list COMMA assignment_expression
    ;

constant_expression_opt
    : /* empty */
    | assignment_expression
    ;

initializer_opt
    : /* empty */
    | initializer
    ;

initializer
    : assignment_expression
    | LCURLY initializer_list RCURLY
    | LCURLY initializer_list COMMA RCURLY
    ;

initializer_list
    : initializer
    | initializer_list COMMA initializer
    ;

/* ---------- Constants (as produced by your lexer) ---------- */
constant
    : DECIMAL_LITERAL       { insert_const_symbol_table('I',$1); }
    | CHARACTER_LITERAL     { insert_const_symbol_table('C',$1); }
    | STRING_LITERAL        { insert_const_symbol_table('S',$1); }
    | EXPONENT_LITERAL      { insert_const_symbol_table('E',$1); }
    | DOUBLE_LITERAL        { insert_const_symbol_table('D',$1); }
    | NULLPTR               { insert_const_symbol_table('N',$1); }
    | TRUE                  { insert_const_symbol_table('B',$1); }
    | FALSE                 { insert_const_symbol_table('B',$1); }
    ;

%%

int main() {
    yyparse();
    print_symbol_table();
    cout << endl;
    print_constant_table();
    return 0;
}
