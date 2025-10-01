%{
    #include <iostream>
    #include <string.h>
    #include <iomanip>
    #include <vector>
    #include <string>
    #include <cstdlib>
    using namespace std;
%}

%union { 
    char* str; 
}


%token<str> INCLUDE TYPEDEF TYPE_NAME
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

%token<str> IF ELSE SWITCH CASE DEFAULT WHILE DO FOR GOTO CONTINUE BREAK RETURN UNTIL
%token<str> SIZEOF

%token<str> VOID INT DOUBLE CHAR BOOL STRING LONG
%token<str> TRUE FALSE NULLPTR
%token<str> AUTO STATIC CONST
%token<str> CLASS STRUCT PUBLIC PRIVATE PROTECTED
%token<str> DELETE NEW CIN COUT ENDL

%token<str> IDENTIFIER
%token<str> DECIMAL_LITERAL DOUBLE_LITERAL EXPONENT_LITERAL CHARACTER_LITERAL STRING_LITERAL

%left LOGICAL_OR
%left LOGICAL_AND
%left BITWISE_OR
%left BITWISE_XOR
%left BITWISE_AND
%left EQUAL NOT_EQUAL
%left LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%left LEFT_SHIFT RIGHT_SHIFT
%left PLUS MINUS
%left STAR DIVIDE MODULUS

%right ASSIGN PLUS_EQUAL MINUS_EQUAL STAR_EQUAL DIV_EQUAL MOD_EQUAL
%right AND_EQUAL OR_EQUAL XOR_EQUAL LEFT_SHIFT_EQ RIGHT_SHIFT_EQ

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start translation_unit
%%

primary_expression
	: IDENTIFIER
	| constant
	| LROUND expression RROUND
    | lambda_expression
	;

constant
    : DECIMAL_LITERAL       
    | CHARACTER_LITERAL     
    | STRING_LITERAL        
    | EXPONENT_LITERAL      
    | DOUBLE_LITERAL        
    | NULLPTR               
    | TRUE                  
    | FALSE                 
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
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list COMMA assignment_expression
	;

unary_expression
	: postfix_expression
	| INCREMENT unary_expression
	| DECREMENT unary_expression
	| unary_operator cast_expression 
	| SIZEOF unary_expression
	| SIZEOF LROUND type_name RROUND
	| delete_expression
	| new_expression
	;

unary_operator
	: BITWISE_AND
	| STAR
	| PLUS
	| MINUS
	| TILDE
	| LOGICAL_NOT
	;

new_expression
    : NEW type_specifier pointer_opt new_declarator scalar_new_init_opt
    | NEW type_specifier new_declarator scalar_new_init_opt
    | NEW type_specifier pointer_opt scalar_new_init_opt
    | NEW type_specifier pointer_opt new_declarator
    | NEW type_specifier pointer_opt 
    | NEW type_specifier new_declarator 
    | NEW type_specifier scalar_new_init_opt
    | NEW type_specifier
    ;

pointer_opt
	: STAR pointer_opt
	| STAR
	;

scalar_new_init_opt
    : LROUND RROUND
    | LROUND argument_expression_list RROUND
    ;

new_declarator
	: LSQUARE expression RSQUARE
    | new_declarator LSQUARE expression RSQUARE
    ;

delete_expression
    : DELETE LSQUARE RSQUARE cast_expression
    | DELETE cast_expression
    ;

cast_expression
	: unary_expression
	| LROUND type_name RROUND cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression STAR cast_expression
	| multiplicative_expression DIVIDE cast_expression
	| multiplicative_expression MODULUS cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression PLUS multiplicative_expression
	| additive_expression MINUS multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_SHIFT additive_expression
	| shift_expression RIGHT_SHIFT additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression GREATER_THAN shift_expression
	| relational_expression LESS_THAN shift_expression
	| relational_expression LESS_EQUAL shift_expression
	| relational_expression GREATER_EQUAL shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQUAL relational_expression
	| equality_expression NOT_EQUAL relational_expression
	;

and_expression
	: equality_expression
	| and_expression BITWISE_AND equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression BITWISE_XOR and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression BITWISE_OR exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression LOGICAL_AND inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression LOGICAL_OR logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression QUESTION_MARK expression COLON conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression 
	;

assignment_operator
	: ASSIGN
	| STAR_EQUAL
	| DIV_EQUAL
	| MOD_EQUAL
	| PLUS_EQUAL
	| MINUS_EQUAL
	| LEFT_SHIFT_EQ
	| RIGHT_SHIFT_EQ
	| AND_EQUAL
	| XOR_EQUAL
	| OR_EQUAL
	;

expression
	: assignment_expression
	| expression COMMA assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers SEMICOLON
	| declaration_specifiers init_declarator_list SEMICOLON
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list COMMA init_declarator
	;

init_declarator
	: declarator
	| declarator ASSIGN initializer
	;

storage_class_specifier
	: TYPEDEF
	| STATIC
	| AUTO
	;

type_specifier
	: VOID
	| CHAR
	| INT
	| LONG
	| DOUBLE
	| BOOL
	| STRING
	| TYPE_NAME
	;

struct_or_class_specifier
	: struct_or_class IDENTIFIER LCURLY struct_or_class_member_list RCURLY
	| struct_or_class IDENTIFIER
	;

struct_or_class
	: STRUCT
	| CLASS
	;

struct_or_class_member_list
	: struct_or_class_member
	| struct_or_class_member_list struct_or_class_member
	;

struct_or_class_member
	: access_specifier_label
	| member_declaration
	;

access_specifier_label
	: PUBLIC COLON
	| PRIVATE COLON
	| PROTECTED COLON
	;

member_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON
	| specifier_qualifier_list SEMICOLON
	| specifier_qualifier_list declarator compound_statement
	| struct_or_class_specifier SEMICOLON
	| SEMICOLON
	| constructor_definition
	| destructor_definition
	;

constructor_definition
	: IDENTIFIER LROUND parameter_list RROUND compound_statement
	| IDENTIFIER LROUND RROUND compound_statement
	;

destructor_definition
	: TILDE IDENTIFIER LROUND RROUND compound_statement
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list COMMA struct_declarator
	;
	
struct_declarator
	: init_declarator
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

type_qualifier
	: CONST
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: IDENTIFIER
	| LROUND declarator RROUND
	| direct_declarator LSQUARE constant_expression RSQUARE
	| direct_declarator LSQUARE RSQUARE
	| direct_declarator LROUND parameter_type_list RROUND
	| direct_declarator LROUND identifier_list RROUND
	| direct_declarator LROUND RROUND
	;

pointer
	: STAR
	| STAR type_qualifier_list
	| STAR pointer
	| STAR type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
	: parameter_list
	;

parameter_list
	: parameter_declaration
	| parameter_list COMMA parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list COMMA IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: LROUND abstract_declarator RROUND
	| LSQUARE RSQUARE
	| LSQUARE constant_expression RSQUARE
	| direct_abstract_declarator LSQUARE RSQUARE
	| direct_abstract_declarator LSQUARE constant_expression RSQUARE
	| LROUND RROUND
	| LROUND parameter_type_list RROUND
	| direct_abstract_declarator LROUND RROUND
	| direct_abstract_declarator LROUND parameter_type_list RROUND
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

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	| io_statement
	;

io_statement
    : cout_expression SEMICOLON
    | cin_expression SEMICOLON
    ;

cout_expression
    : COUT insertion_list
    ;

insertion_list
    : LEFT_SHIFT assignment_expression
	| LEFT_SHIFT ENDL
	| insertion_list LEFT_SHIFT ENDL
    | insertion_list LEFT_SHIFT assignment_expression
    ;

cin_expression
    : CIN extraction_list
    ;

extraction_list
    : RIGHT_SHIFT assignment_expression
    | extraction_list RIGHT_SHIFT assignment_expression
    ;

labeled_statement
	: IDENTIFIER COLON statement
	| CASE constant_expression COLON statement
	| DEFAULT COLON statement
	;

compound_statement
	: LCURLY RCURLY
	| LCURLY statement_list RCURLY
	| LCURLY declaration_list RCURLY
	| LCURLY declaration_list statement_list RCURLY
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: SEMICOLON
	| expression SEMICOLON
	;

selection_statement
	: IF LROUND expression RROUND statement %prec LOWER_THAN_ELSE
	| IF LROUND expression RROUND statement ELSE statement
	| SWITCH LROUND expression RROUND statement
	;

iteration_statement
	: WHILE LROUND expression RROUND statement
	| UNTIL LROUND expression RROUND statement
	| DO statement WHILE LROUND expression RROUND SEMICOLON
	| FOR LROUND for_init_statement expression_statement RROUND statement
	| FOR LROUND for_init_statement expression_statement expression RROUND statement
	;

for_init_statement
	: expression_statement
	| declaration
	;

jump_statement
	: GOTO IDENTIFIER SEMICOLON
	| CONTINUE SEMICOLON
	| BREAK SEMICOLON
	| RETURN SEMICOLON
	| RETURN expression SEMICOLON
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| struct_or_class_specifier SEMICOLON
	| declaration
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

function_definition
	: declaration_specifiers declarator compound_statement
	| declarator compound_statement
	;
	
lambda_expression
  : LSQUARE lambda_capture_clause RSQUARE lambda_declarator compound_statement
  | LSQUARE lambda_capture_clause RSQUARE compound_statement
  ;

lambda_declarator
  : lambda_parameter_clause trailing_return_opt
  ;

lambda_parameter_clause
  : LROUND RROUND
  | LROUND parameter_list RROUND
  ;

trailing_return_opt
  : 
  | ARROW type_specifier
  ;

lambda_capture_clause
  : 
  | ASSIGN
  | capture_list
  | capture_list COMMA ASSIGN
  | ASSIGN COMMA capture_list
  ;

capture_list
  : IDENTIFIER
  | capture_list COMMA IDENTIFIER
  ;


%%

int main(){
    return 0;
}