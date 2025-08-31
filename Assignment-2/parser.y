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
    int count_const = 0;

    char data_type[10];

    struct symbol_table_struct {
        string identifier_name; 
        string datatype;
        string type;
        int lineno;
    }; 

    struct const_table_struct {
        string constant_value;
        string constant_type;
        int lineno;
    };
    
	struct argument_list {
        string arg[MAX_ARGS];
        int count;
    } arg_list;

    vector<const_table_struct> constant_table;
    vector<symbol_table_struct> symbol_table;

    int search_symbol_table(string id_name) {
        for(auto& x : symbol_table) {
            if(x.identifier_name == id_name) {
                return 1;
                break;
            }
        }
        return 0;
    }

    void yyerror(const char *s) {
        cerr<<"Error at line "<<yylineno<<": "<<s<<endl;
    }

    void assign_type(char *str) {
        strcpy(data_type, str);
    }

    void insert_symbol_table(char c,const char *yytext) {
        if(yytext == NULL) return;
        int lineno;
        string identifier_name, datatype, type;
        if (search_symbol_table(yytext) == 0) {
            identifier_name = yytext;
            lineno = yylineno;

            switch (c) {
                case 'H' :
                    datatype = data_type;
                    type = "HEADER";
                    break;
                case 'K' : 
                    datatype = yytext;
                    type = "KEYWORD";
                    break;
                case 'V' :
                    datatype = data_type;
                    type = "VARIABLE";
                    break;
                case 'C' : 
                    datatype = "CONST";
                    type = "CONSTANT";
                    break;
                case 'F' :
                    datatype = data_type;
                    type = "FUNCTION";
                    break;
                case 'G' :
                    datatype = "GOTO";
                    type = "LABEL";
                    break;
                case 'P' :
                    datatype = data_type;
                    type = "POINTER";
                    break;
                case 'f' :
                    datatype = data_type;
                    type = "POINTER";
                    break;
            }
        }

        symbol_table.push_back({identifier_name, datatype, type, lineno});
    }
    
    void insert_const_symbol_table(char c,const char *yytext) {
        if(yytext == NULL) return;

        string constant_value = yytext;
        int lineno = yylineno;
        string constant_type;

        switch (c) {
            case 'I' : 
                constant_type = "INTEGER_CONST";
                break;
            case 'D' :
                constant_type = "DOUBLE_CONST";
                break;
            case 'B' :
                constant_type = "BOOLEAN_CONST";
                break;
            case 'E' :
                constant_type = "EXPONENTIAL_CONST";
                break;
            case 'N' :
                constant_type = "NULLPTR_CONST";
                break;
            case 'S' :
                constant_type = "STRING_CONST";
                break;
            case 'C' :
                constant_type = "CHARACTER_CONST";
        }

        constant_table.push_back({constant_value, constant_type, lineno});
    }

    void str_type(char *return_type, char *given_type) {
        if (given_type == "int") {
            return_type = "INT";
        }
        else if (given_type == "bool") {
            return_type = "BOOL";
        }
        else if (given_type == "double") {
            return_type = "DOUBLE";
        }
        else if (given_type == "char") {
            return_type = "CHAR";
        } 
        else if (given_type == "long") {
            return_type = "LONG";
        }
        else if (given_type == "void") {
            return_type = "VOID";	
        }
        else if (given_type == "string") {
            return_type = "STRING";
        }
        else if (given_type == "struct") {
            return_type = "STRUCT";
        }
        else if (given_type == "class") {
            return_type = "CLASS";
        }
        else if (given_type == "function") {
            return_type = "FUNCTION";
        }
        else {
            return_type = "UNKNOWN";
        }
    }

    void print_symbol_table() {
        cout << "\nSYMBOL TABLE\n";
        cout << "-----------------------------------------------------------------\n";
        cout << "| " << left << setw(15) << "Identifier"
            << " | " << setw(20) << "Type"
            << " | " << setw(10) << "Data Type"
            << " | Line No |\n";
        cout << "-----------------------------------------------------------------\n";

        for (const auto &sym : symbol_table) {
            cout << "| " << setw(15) << sym.identifier_name
                << " | " << setw(20) << sym.type
                << " | " << setw(10) << sym.datatype
                << " | " << setw(7) << sym.lineno << " |\n";
        }

        cout << "-----------------------------------------------------------------\n";
    }

    void print_constant_table() {
        cout << "\nConstant Symbol Table:\n";
        cout << "-----------------------------------------------------------------\n";
        cout << "| " << left << setw(27) << "Constant Value"
            << " | " << setw(20) << "Constant Type"
            << " | Line no. |\n";
        cout << "-----------------------------------------------------------------\n";

        for (const auto &con : constant_table) {
            cout << "| " << setw(27) << con.constant_value
                << " | " << setw(20) << con.constant_type
                << " | " << setw(8) << con.lineno << " |\n";
        }

        cout << "-----------------------------------------------------------------\n";
    }

%}

%union {
    char *str;
}


%token<str> PLUS MINUS STAR DIVIDE MODULUS ASSIGN INCREMENT DECREMENT
%token<str> EQUAL NOT_EQUAL LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL
%token<str> BITWISE_AND BITWISE_OR BITWISE_XOR TILDE LEFT_SHIFT RIGHT_SHIFT
%token<str> LOGICAL_NOT LOGICAL_OR LOGICAL_AND
%token<str> PLUS_EQUAL MINUS_EQUAL STAR_EQUAL DIV_EQUAL MOD_EQUAL
%token<str> AND_EQUAL OR_EQUAL XOR_EQUAL LEFT_SHIFT_EQ RIGHT_SHIFT_EQ
%token<str> LEFT_CURLY RIGHT_CURLY LEFT_SQUARE RIGHT_SQUARE LEFT_ROUND RIGHT_ROUND
%token<str> DOT COMMA COLON SEMICOLON ARROW QUESTION_MARK
%token<str> RETURN SIZEOF IF ELIF ELSE CASE SWITCH DEFAULT
%token<str> FOR WHILE DO UNTIL BREAK CONTINUE GOTO
%token<str> INT BOOL CHAR DOUBLE LONG STRING VOID CONST FUNCTION AUTO
%token<str> STATIC CLASS STRUCT PUBLIC PRIVATE PROTECTED
%token<str> COUT CIN ENDL NEW DELETE
%token<str> NULLPTR TRUE FALSE INVALID_IDENTIFIER INCLUDE
%token<str> IDENTIFIER DECIMAL_LITERAL EXPONENT_LITERAL DOUBLE_LITERAL STRING_LITERAL CHARACTER_LITERAL

%type<str> translation_unit external_declaration declaration declaration_specifiers
%type<str> storage_specifier type_specifier type_qualifier init_declarator_list init_declarator
%type<str> declarator direct_declarator pointer function_definition parameter_type_list_opt
%type<str> parameter_type_list parameter_list parameter_declaration class_specifier
%type<str> member_specification member_declaration member_declarator_list member_declarator
%type<str> access_specifier_label compound_statement declaration_list statement_list
%type<str> statement labelled_statement expression_statement selection_statement if_rest
%type<str> iteration_statement for_init_statement for_cond_opt for_iter_opt jump_statement
%type<str> expression_opt io_statement insertion_list extraction_list insertion_item
%type<str> extraction_item expression assignment_expression assignment_operator
%type<str> conditional_expression logical_or_expression logical_and_expression inclusive_or_expression
%type<str> exclusive_or_expression and_expression equality_expression relational_expression
%type<str> shift_expression additive_expression multiplicative_expression cast_expression
%type<str> unary_expression unary_operator postfix_expression primary_expression
%type<str> argument_expression_list_opt argument_expression_list constant_expression_opt
%type<str> constant_expression type_name abstract_declarator_opt abstract_declarator
%type<str> direct_abstract_declarator new_expression new_initializer_opt delete_expression
%type<str> lambda_expression initializer initializer_list constant

%start translation_unit
%%  

translation_unit:
    /* empty */
    | translation_unit external_declaration
    ;

external_declaration:
      declaration
    | function_definition
    | class_specifier
    ;

declaration:
      declaration_specifiers SEMICOLON
    | declaration_specifiers init_declarator_list SEMICOLON
    ;

declaration_specifiers:
      storage_specifier
    | type_specifier
    | type_qualifier
    | declaration_specifiers storage_specifier
    | declaration_specifiers type_specifier
    | declaration_specifiers type_qualifier
    ;

storage_specifier:
      AUTO
    | STATIC
    ;

type_specifier:
      VOID
    | CHAR
    | INT
    | LONG
    | BOOL
    | DOUBLE
    | STRING
    | CLASS IDENTIFIER
    | STRUCT IDENTIFIER
    | IDENTIFIER
    | FUNCTION
    ;

type_qualifier:
      CONST
    ;

init_declarator_list:
      init_declarator
    | init_declarator_list COMMA init_declarator
    ;

init_declarator:
      declarator
    | declarator ASSIGN initializer
    ;

declarator:
      direct_declarator
    | pointer declarator
    ;

direct_declarator:
      IDENTIFIER
    | LEFT_ROUND declarator RIGHT_ROUND
    | direct_declarator LEFT_SQUARE DECIMAL_LITERAL RIGHT_SQUARE
    | direct_declarator LEFT_ROUND parameter_type_list_opt RIGHT_ROUND
    ;

pointer:
      STAR
    | BITWISE_AND
    | STAR pointer
    ;

/* Functions and parameters */
function_definition:
      declaration_specifiers declarator compound_statement
    | declaration_specifiers declarator declaration_list compound_statement
    ;

parameter_type_list_opt:
      /* empty */
    | parameter_type_list
    ;

parameter_type_list:
      parameter_list
    ;

parameter_list:
      parameter_declaration
    | parameter_list COMMA parameter_declaration
    ;

parameter_declaration:
      declaration_specifiers declarator
    | declaration_specifiers
    ;

/* Class / Struct */
class_specifier:
      CLASS IDENTIFIER LEFT_CURLY member_specification RIGHT_CURLY
    | STRUCT IDENTIFIER LEFT_CURLY member_specification RIGHT_CURLY
    ;

member_specification:
      /* empty */
    | member_specification member_declaration
    | member_specification access_specifier_label
    ;

member_declaration:
      declaration_specifiers member_declarator_list SEMICOLON
    | declaration_specifiers SEMICOLON
    ;

member_declarator_list:
      member_declarator
    | member_declarator_list COMMA member_declarator
    ;

member_declarator:
      declarator
    | declarator ASSIGN constant_expression
    ;

access_specifier_label:
      PUBLIC COLON
    | PRIVATE COLON
    | PROTECTED COLON
    ;

/* Statements */
compound_statement:
      LEFT_CURLY RIGHT_CURLY
    | LEFT_CURLY statement_list RIGHT_CURLY
    | LEFT_CURLY declaration_list RIGHT_CURLY
    | LEFT_CURLY declaration_list statement_list RIGHT_CURLY
    ;

declaration_list:
      declaration
    | declaration_list declaration
    ;

statement_list:
      statement
    | statement_list statement
    ;

statement:
      expression_statement
    | compound_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | io_statement
    | labelled_statement
    ;

labelled_statement:
      CASE constant_expression COLON statement
    | DEFAULT COLON statement
    ;

expression_statement:
      SEMICOLON
    | expression SEMICOLON
    ;

selection_statement:
      IF LEFT_ROUND expression RIGHT_ROUND statement if_rest
    | SWITCH LEFT_ROUND expression RIGHT_ROUND statement
    ;

if_rest:
        /* empty */
    | ELIF LEFT_ROUND expression RIGHT_ROUND statement if_rest
    | ELSE statement
    ;

iteration_statement:
      WHILE LEFT_ROUND expression RIGHT_ROUND statement
    | UNTIL LEFT_ROUND expression RIGHT_ROUND statement
    | DO statement WHILE LEFT_ROUND expression RIGHT_ROUND SEMICOLON
    | FOR LEFT_ROUND for_init_statement for_cond_opt for_iter_opt RIGHT_ROUND statement
    ;

for_init_statement:
      SEMICOLON
    | expression_statement
    | declaration
    ;

for_cond_opt:
      /* empty */
    | expression
    ;

for_iter_opt:
      /* empty */
    | expression
    ;

jump_statement:
      GOTO IDENTIFIER SEMICOLON
    | CONTINUE SEMICOLON
    | BREAK SEMICOLON
    | RETURN expression_opt SEMICOLON
    ;

expression_opt:
      /* empty */
    | expression
    ;

/* IO */
io_statement:
      COUT insertion_list SEMICOLON
    | CIN extraction_list SEMICOLON
    ;

insertion_list:
      insertion_item
    | insertion_list LEFT_SHIFT insertion_item
    ;

extraction_list:
      extraction_item
    | extraction_list RIGHT_SHIFT extraction_item
    ;

insertion_item:
      expression
    | ENDL
    | IDENTIFIER
    ;

extraction_item:
      IDENTIFIER
    ;

/* Expressions */
expression:
      assignment_expression
    | expression COMMA assignment_expression
    ;

assignment_expression:
      conditional_expression        {$$ = strdup($1);}
    | unary_expression assignment_operator assignment_expression
    ;

assignment_operator:
      ASSIGN
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

conditional_expression:
      logical_or_expression
    | logical_or_expression QUESTION_MARK expression COLON conditional_expression
    ;

logical_or_expression:
      logical_and_expression
    | logical_or_expression LOGICAL_OR logical_and_expression
    ;

logical_and_expression:
      inclusive_or_expression
    | logical_and_expression LOGICAL_AND inclusive_or_expression
    ;

inclusive_or_expression:
      exclusive_or_expression
    | inclusive_or_expression BITWISE_OR exclusive_or_expression
    ;

exclusive_or_expression:
      and_expression
    | exclusive_or_expression BITWISE_XOR and_expression
    ;

and_expression:
      equality_expression
    | and_expression BITWISE_AND equality_expression
    ;

equality_expression:
      relational_expression
    | equality_expression EQUAL relational_expression
    | equality_expression NOT_EQUAL relational_expression
    ;

relational_expression:
      shift_expression
    | relational_expression LESS_THAN shift_expression
    | relational_expression GREATER_THAN shift_expression
    | relational_expression LESS_EQUAL shift_expression
    | relational_expression GREATER_EQUAL shift_expression
    ;

shift_expression:
      additive_expression
    | shift_expression LEFT_SHIFT additive_expression
    | shift_expression RIGHT_SHIFT additive_expression
    ;

additive_expression:
      multiplicative_expression
    | additive_expression PLUS multiplicative_expression
    | additive_expression MINUS multiplicative_expression
    ;

multiplicative_expression:
      cast_expression
    | multiplicative_expression STAR cast_expression
    | multiplicative_expression DIVIDE cast_expression
    | multiplicative_expression MODULUS cast_expression
    ;

cast_expression:
      unary_expression
    | LEFT_ROUND type_name RIGHT_ROUND cast_expression
    ;

unary_expression:
      postfix_expression
    | INCREMENT unary_expression
    | DECREMENT unary_expression
    | unary_operator cast_expression
    | SIZEOF unary_expression
    | SIZEOF LEFT_ROUND type_name RIGHT_ROUND
    | new_expression
    | delete_expression
    ;

unary_operator:
      PLUS
    | MINUS
    | TILDE
    | LOGICAL_NOT
    | BITWISE_AND
    | STAR
    ;

postfix_expression:
      primary_expression
    | postfix_expression LEFT_SQUARE expression RIGHT_SQUARE
    | postfix_expression LEFT_ROUND argument_expression_list_opt RIGHT_ROUND
    {
        assign_type("UNKNOWN");
        insert_symbol_table('F',$1);
    }
    | postfix_expression DOT IDENTIFIER
    | postfix_expression ARROW IDENTIFIER
    | postfix_expression INCREMENT
    | postfix_expression DECREMENT
    ;

primary_expression:
      IDENTIFIER
    | constant
    | LEFT_ROUND expression RIGHT_ROUND
    | lambda_expression
    ;

constant:
      DECIMAL_LITERAL       {insert_const_symbol_table('I',$1);}
    | CHARACTER_LITERAL     {insert_const_symbol_table('C',$1);}
    | STRING_LITERAL        {insert_const_symbol_table('S',$1);}
    | EXPONENT_LITERAL      {insert_const_symbol_table('E',$1);}
    | DOUBLE_LITERAL        {insert_const_symbol_table('D',$1);}
    | NULLPTR               {insert_const_symbol_table('N',$1);}
    | TRUE                  {insert_const_symbol_table('B',$1);}
    | FALSE                 {insert_const_symbol_table('B',$1);}
    ;

/* Arguments */
argument_expression_list_opt:
      /* empty */
    | argument_expression_list
    ;

argument_expression_list:
      assignment_expression
    | argument_expression_list COMMA assignment_expression
    ;

constant_expression_opt:
      /* empty */
    | constant_expression
    ;

/* Constants */
constant_expression:
      conditional_expression
    ;

/* Type names */
type_name:
      declaration_specifiers abstract_declarator_opt
    ;

abstract_declarator_opt:
      /* empty */
    | abstract_declarator
    ;

abstract_declarator:
	  pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator:
	  LEFT_ROUND abstract_declarator RIGHT_ROUND
	| LEFT_SQUARE constant_expression_opt RIGHT_SQUARE
	| direct_abstract_declarator LEFT_SQUARE constant_expression_opt RIGHT_SQUARE
	| LEFT_ROUND parameter_type_list_opt RIGHT_ROUND
	| direct_abstract_declarator LEFT_ROUND parameter_type_list_opt RIGHT_ROUND
	;


/* New/Delete */
new_expression:
      NEW type_name new_initializer_opt
    ;

new_initializer_opt:
      /* empty */
    | LEFT_ROUND argument_expression_list_opt RIGHT_ROUND
    ;

/* Delete */
delete_expression:
      DELETE cast_expression
    ;


lambda_expression:
      FUNCTION IDENTIFIER ASSIGN LEFT_ROUND parameter_type_list_opt RIGHT_ROUND compound_statement
    | FUNCTION IDENTIFIER ASSIGN LEFT_ROUND parameter_type_list_opt RIGHT_ROUND ARROW type_name compound_statement
    ;

/* Misc */
initializer:
      assignment_expression
    | LEFT_CURLY initializer_list RIGHT_CURLY
    ;

initializer_list:
      initializer
    | initializer_list COMMA initializer
    ;

%%

int main() {
    yyparse();
    print_symbol_table();
    cout<<endl;
    print_constant_table();
}