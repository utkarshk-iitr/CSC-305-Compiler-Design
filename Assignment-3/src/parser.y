%{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <unordered_map>
    #include <map>
    #include <cstdlib>
    using namespace std;

    struct Node {
        vector<string> code;
        string place;
        string type;
        string kind;
        int argCount = 0;
        Node() : place(""), type("") , kind("") {}
        Node(const Node &n) : code(n.code), place(n.place), type(n.type), kind(n.kind), argCount(n.argCount) {}
        Node(string p, string t, string k) : place(p), type(t), kind(k) {}
    };

    struct Symbol {
        string name;
        string type;
        string kind;
        bool isFunction = false;
        int paramCount = 0;
        bool isDeclared = true;
        Symbol() : name(""), type(""), kind(""), isFunction(false), paramCount(0), isDeclared(true) {}
        Symbol(const Symbol &s) : name(s.name), type(s.type), kind(s.kind), isFunction(s.isFunction), paramCount(s.paramCount), isDeclared(s.isDeclared) {}
        Symbol(string n, string t, string k, bool f, int p) : name(n), type(t), kind(k), isFunction(f), paramCount(p) {}
    };

    vector< unordered_map<string, Symbol> > symStack;
    vector<string> errors;
    static string currentFunction = "global";
    static int globalTemp = 0, globalLabel = 0;
    static int localTemp = 0, localLabel = 0;
    static string lastDeclType = "int";
    static string lastUsage = "rvalue";

    Node* finalRoot = nullptr;

    string newTemp() {
        if (currentFunction == "global") {
            return "global.t" + to_string(++globalTemp);
        } else {
            return currentFunction + ".t" + to_string(++localTemp);
        }
    }
    string newLabel() {
        if (currentFunction == "global") {
            return "global.L" + to_string(++globalLabel);
        } else {
            return currentFunction + ".L" + to_string(++localLabel);
        }
    }

    void pushScope() {
        symStack.emplace_back();
    }
    void popScope() {
        if (!symStack.empty()) symStack.pop_back();
    }

    Symbol* lookupSymbol(const string &name) {
        for (int i = (int)symStack.size()-1; i >= 0; --i) {
            auto &m = symStack[i];
            auto it = m.find(name);
            if (it != m.end()) return &it->second;
        }
        return nullptr;
    }

    bool declareSymbol(const string &name, const string &type, bool isFunc=false, int params=0) {
        if (symStack.empty()) pushScope();
        auto &cur = symStack.back();
        if (cur.find(name) != cur.end()) {
            return false;
        }
        Symbol s; s.name = name; s.type = type; s.isFunction = isFunc; s.paramCount = params; s.isDeclared = true;
        cur[name] = s;
        return true;
    }

    bool is_type_name(const string &name) {
        for (int i = (int)symStack.size()-1; i >= 0; --i){
            auto &m = symStack[i];
            auto it = m.find(name);
            if (it != m.end() && it->second.isDeclared) 
                return true;
        }
        return false;
    }

    extern int yylineno;
    void yyerror(const char *s) {
        errors.push_back(string("Error at line ") + to_string(yylineno) + " : " + s);
    }

    void check_access(Symbol* sym) {
        if(contains(sym->kind,"private")){
            yyerror("Can't access private member '" + sym->name + "'.");
        }
        else if(contains(sym->kind,"protected")){
            yyerror("Can't access protected member '" + sym->name + "'.");
        }
    }

    extern int yylex();
    extern int yyparse();

%}

%union {
    char* str;
    Node* node;
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
%token<str> TILDE FUNCTION

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

/* declare types for nonterminals */
%type<node> struct_or_class_specifier struct_or_class struct_or_class_member_list struct_or_class_member
%type<node> access_specifier_label member_declaration constructor_definition destructor_definition
%type<node> struct_declarator_list struct_declarator specifier_qualifier_list type_qualifier
%type<node> declarator direct_declarator pointer type_qualifier_list parameter_type_list parameter_list
%type<node> parameter_declaration identifier_list type_name abstract_declarator direct_abstract_declarator
%type<node> initializer initializer_list statement compound_statement statement_list labeled_statement
%type<node> selection_statement iteration_statement jump_statement io_statement cout_expression
%type<node> insertion_list cin_expression extraction_list external_declaration 
%type<node> function_definition lambda_expression lambda_declarator lambda_parameter_clause
%type<node> trailing_return_opt lambda_capture_clause capture_list primary_expression
%type<node> postfix_expression argument_expression_list unary_expression cast_expression
%type<node> multiplicative_expression additive_expression shift_expression relational_expression
%type<node> equality_expression and_expression exclusive_or_expression inclusive_or_expression
%type<node> logical_and_expression logical_or_expression conditional_expression block_item
%type<node> assignment_expression expression constant_expression declaration init_declarator
%type<node> init_declarator_list constant new_expression pointer_opt new_declarator delete_expression  
%type<node> scalar_new_init_opt unary_operator assignment_operator declaration_specifiers
%type<node> storage_class_specifier type_specifier expression_statement translation_unit for_init_statement;


%start translation_unit

%%

primary_expression
	: IDENTIFIER {
          Node* n = new Node();
          string name = string($1);
          n->place = name;
          Symbol* sym = lookupSymbol(name);
          if (!sym) {
              yyerror("Use of undeclared identifier '" + name + "'.");
          } else {
              check_access(sym);
              n->kind = sym->kind;
              n->type = sym->type;
          }
          $$ = n;
      }
	| constant { $$ = $1; }
	| LROUND expression RROUND { $$ = $2; }
    | lambda_expression { $$ = $1; }
	;

constant
    : DECIMAL_LITERAL       {
          Node* n = new Node(string($1), "int", "constant");
          $$ = n;
      }
    | CHARACTER_LITERAL     {
          Node* n = new Node(string($1), "char", "constant");
          $$ = n;
      }
    | STRING_LITERAL        {
          Node* n = new Node(string($1), "string", "constant");
          $$ = n;
      }
    | EXPONENT_LITERAL      {
          Node* n = new Node(string($1), "double", "constant");
          $$ = n;
      }
    | DOUBLE_LITERAL        {
          Node* n = new Node(string($1), "double", "constant");
          $$ = n;
      }
    | NULLPTR               {
          Node* n = new Node("0", "nullptr", "constant");
          $$ = n;
      }
    | TRUE                  {
          Node* n = new Node("1", "bool", "constant");
          $$ = n;
      }
    | FALSE                 {
          Node* n = new Node("0", "bool", "constant");
          $$ = n;
      }
    ;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression LSQUARE expression RSQUARE {
          Node* base = $1; Node* idx = $3;
          if(base->kind!="array" && base->kind!="pointer"){
              yyerror("Subscripted value is not an array or pointer.");
          }
          if(idx->type!="int"){
              yyerror("Index is not an integer.");
          }

          Node* n = new Node();
          n->code = base->code;
          n->code.insert(n->code.end(), idx->code.begin(), idx->code.end());

          if(lastUsage=="lvalue"){
            n->place = base->place + "[" + idx->place + "]";
          }
          else{
            n->place = newTemp();
            n->code.push_back(n->place + " = " + base->place + "[" + idx->place + "];");
          }
          n->type = base->type;
          n->kind = lastUsage;          
          
          $$ = n;
      }
	| postfix_expression LROUND RROUND {
            Node* fun = $1;
            Symbol* s = lookupSymbol(fun->place);
            check_access(s);
            if(!s || !s->isFunction){
                yyerror("Call to non-function '" + fun->place + "'.");
            }
            if(s->isFunction && s->paramCount != 0){
                yyerror("Call to function '" + fun->place + "' with incorrect number of arguments.");
            }
            Node* n = new Node();
            n->code = fun->code;
            n->type = fun->type;

            if(fun->type=="void"){
                n->code.push_back("call " + fun->place + ", 0;");
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = call " + fun->place + ", 0;");
            }
            $$ = n;
        }
	| postfix_expression LROUND argument_expression_list RROUND {
            Node* fun = $1; Node* args = $3;
            Symbol* s = lookupSymbol(fun->place);
            check_access(s);
            if(!s || !s->isFunction){
                yyerror("Call to non-function '" + fun->place + "'.");
            }
            if (s->isFunction && s->paramCount != args->argCount) {
                yyerror("Call to function '" + fun->place + "' with incorrect number of arguments.");
            }
            Node* n = new Node();
            n->code = fun->code;
            n->type = fun->type;
            n->code.insert(n->code.end(), args->code.begin(), args->code.end());
            if(fun->type=="void"){
                n->code.push_back("call " + fun->place + ", " + to_string(args->argCount) + ";");
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = call " + fun->place + ", " + to_string(args->argCount) + ";");
            }
            $$ = n;
      }
	| postfix_expression DOT IDENTIFIER {
            Node* obj = $1;
            if(obj->kind=="pointer"){
                yyerror("Member access through pointer must use '->' operator.");
            }
            Symbol* s = lookupSymbol(obj->type + "." + string($3));
            if(!s){
                yyerror("No member named '" + string($3) + "' in '" + obj->type + "'.");
            }
            check_access(s);
            Node* n = new Node();
            n->code = obj->code;

            if(lastUsage=="lvalue"){
                n->place = obj->place + "." + string($3);
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = " + obj->place + "." + string($3) + ";");
            }
            n->type = s->type;
            $$ = n;
      }
	| postfix_expression ARROW IDENTIFIER {
          Node* obj = $1;
          Symbol* s = lookupSymbol(obj->type + "." + string($3));
            if(!s){
                yyerror("No member named '" + string($3) + "' in '" + obj->type + "'.");
            }
            check_access(s);
          Node* n = new Node();
          n->code = obj->code;
          if(lastUsage=="lvalue"){
              n->place = obj->place + "->" + string($3);
          }
          else{
              n->place = newTemp();
              n->code.push_back(n->place + " = " + obj->place + "->" + string($3) + ";");
          }
          n->type = s->type;
          $$ = n;
      }
	| postfix_expression INCREMENT {
          Node* v = $1;
          if(v->kind!="lvalue"){
              yyerror("Lvalue required as increment operand.");
          }
          if(v->type=="bool" || v->type=="nullptr" || v->type=="string" || v->type=="char"){
              yyerror("Invalid type '" + v->type + "' for increment.");
          }
          Node* n = new Node();
          n->code = v->code;
          string old = newTemp();
            n->code.push_back(old + " = " + v->addr + ";");          // load old value from address
            n->code.push_back(v->addr + " = " + old + " + 1;");      // store back incremented value

            n->place = old;
          n->type = v->type;
          n->kind = "rvalue";
          $$ = n;
      }
	| postfix_expression DECREMENT { 
          Node* v = $1;
            if(v->kind!="lvalue"){
                yyerror("Lvalue required as decrement operand.");
            }
            if(v->type=="bool" || v->type=="nullptr" || v->type=="string" || v->type=="char"){
                yyerror("Invalid type '" + v->type + "' for decrement.");
            }
          Node* n = new Node();
          n->code = v->code;
          string old = newTemp();
            n->code.push_back(old + " = " + v->addr + ";");          // load old value from address
            n->code.push_back(v->addr + " = " + old + " - 1;");      // store back incremented value

            n->place = old;
          n->type = v->type;
          n->kind = "rvalue";
          $$ = n;
      }    
	;

argument_expression_list
	: assignment_expression {
          Node* e = $1;
          if(e->place.empty()){
              yyerror("Void expression cannot be used as function argument.");
          }
          Node* n = new Node();
          n->code = e->code;
          n->argCount = 1;
          n->code.push_back("param " + e->place + ";");
          $$ = n;
      }
	| argument_expression_list COMMA assignment_expression {
            Node* e = $3;
            if(e->place.empty()){
                yyerror("Void expression cannot be used as function argument.");
            }
          Node* n = $1;
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->argCount = n->argCount + 1;
          n->code.push_back("param " + e->place + ";");
          $$ = n;
      }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INCREMENT unary_expression {
          Node* v = $2;
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " + 1;");
          $$ = n;
      }
	| DECREMENT unary_expression {
          Node* v = $2;
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " - 1;");
          $$ = n;
      }
	| unary_operator cast_expression {
          Node* rhs = $2;
          Node* n = new Node();
          n->code = rhs->code;
          string op = string($1);
          if (op == "&") {
              n->place = newTemp();
              n->code.push_back(n->place + " = &" + rhs->place + ";");
              n->type = rhs->type + "*";
          } else if (op == "*") {
              n->place = newTemp();
              n->code.push_back(n->place + " = *" + rhs->place + ";");
              n->type = rhs->type;
          } else if (op == "+") {
              n->place = rhs->place;
              n->type = rhs->type;
          } else if (op == "-") {
              n->place = newTemp();
              n->code.push_back(n->place + " = 0 - " + rhs->place + ";");
              n->type = rhs->type;
          } else if (op == "~") {
              n->place = newTemp();
              n->code.push_back(n->place + " = ~" + rhs->place + ";");
              n->type = rhs->type;
          } else if (op == "!") {
              n->place = newTemp();
              n->code.push_back(n->place + " = !" + rhs->place + ";");
              n->type = "bool";
          }
          $$ = n;
      }
	| SIZEOF unary_expression {
          Node* n = new Node(); n->place = "sizeof"; $$ = n;
      }
	| SIZEOF LROUND type_name RROUND {
          Node* n = new Node(); n->place = "sizeof"; $$ = n;
      }
	| delete_expression { $$ = $1; }
	| new_expression { $$ = $1; }
	;

unary_operator
	: BITWISE_AND { $$ = $1; }
	| STAR { $$ = $1; }
	| PLUS { $$ = $1; }
	| MINUS { $$ = $1; }
	| TILDE { $$ = $1; }
	| LOGICAL_NOT { $$ = $1; }
	;

new_expression 
	: NEW type_specifier pointer_opt new_declarator scalar_new_init_opt {
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          $$ = n;
      }
	| NEW type_specifier new_declarator scalar_new_init_opt {
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          $$ = n;
      }
	| NEW type_specifier pointer_opt scalar_new_init_opt {
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          $$ = n;
      }
	| NEW type_specifier pointer_opt new_declarator {
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          $$ = n;
      }
	| NEW type_specifier pointer_opt {
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          $$ = n;
      }
	| NEW type_specifier new_declarator {
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          $$ = n;
      }
	| NEW type_specifier scalar_new_init_opt {
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          $$ = n;
      }
	| NEW type_specifier {
          Node* n = new Node();
          n->place = newTemp();
          n->code.push_back(n->place + " = alloc " + lastDeclType + ";");
          n->type = lastDeclType + "*";
          $$ = n;
      }
	;

pointer_opt 
	: STAR pointer_opt { $$ = nullptr; }
	| STAR { $$ = nullptr; }
	;

new_declarator 
	: LSQUARE expression RSQUARE { $$ = $2; }
	| new_declarator LSQUARE expression RSQUARE { $$ = $3; }
	;

scalar_new_init_opt 
	: LROUND RROUND { $$ = nullptr; }
	| LROUND argument_expression_list RROUND { $$ = $2; }
	;

delete_expression
	: DELETE LSQUARE RSQUARE cast_expression {
          Node* n = new Node();
          n->code = $4->code;
          n->code.push_back("free " + $4->place + ";");
          $$ = n;
      }
	| DELETE cast_expression {
          Node* n = new Node();
          n->code = $2->code;
          n->code.push_back("free " + $2->place + ";");
          $$ = n;
      }
	;

cast_expression
	: unary_expression { $$ = $1; }
	| LROUND type_name RROUND cast_expression {
          $$ = $4;
      }
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression STAR cast_expression {
          Node* a = $1; Node* b = $3;
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " * " + b->place + ";");
          n->type = a->type;
          $$ = n;
      }
	| multiplicative_expression DIVIDE cast_expression {
          Node* a = $1; Node* b = $3;
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " / " + b->place + ";");
          n->type = a->type;
          $$ = n;
      }
	| multiplicative_expression MODULUS cast_expression {
          Node* a = $1; Node* b = $3;
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " % " + b->place + ";");
          n->type = a->type;
          $$ = n;
      }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression PLUS multiplicative_expression {
          Node* a = $1; Node* b = $3;
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " + " + b->place + ";");
          n->type = a->type;
          $$ = n;
      }
	| additive_expression MINUS multiplicative_expression {
          Node* a = $1; Node* b = $3;
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " - " + b->place + ";");
          n->type = a->type;
          $$ = n;
      }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_SHIFT additive_expression {
          Node* a = $1; Node* b = $3;
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " << " + b->place + ";");
          n->type = a->type; $$ = n;
      }
	| shift_expression RIGHT_SHIFT additive_expression {
          Node* a = $1; Node* b = $3;
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " >> " + b->place + ";");
          n->type = a->type; $$ = n;
      }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression GREATER_THAN shift_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " > " + b->place + ";");
          n->type = "bool"; $$ = n;
      }
	| relational_expression LESS_THAN shift_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " < " + b->place + ";");
          n->type = "bool"; $$ = n;
      }
	| relational_expression LESS_EQUAL shift_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " <= " + b->place + ";");
          n->type = "bool"; $$ = n;
      }
	| relational_expression GREATER_EQUAL shift_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " >= " + b->place + ";");
          n->type = "bool"; $$ = n;
      }
	;

equality_expression
	: relational_expression { $$ = $1; }
	| equality_expression EQUAL relational_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " == " + b->place + ";");
          n->type = "bool"; $$ = n;
      }
	| equality_expression NOT_EQUAL relational_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " != " + b->place + ";");
          n->type = "bool"; $$ = n;
      }
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression BITWISE_AND equality_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " & " + b->place + ";");
          $$ = n;
      }
	;

exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression BITWISE_XOR and_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " ^ " + b->place + ";");
          $$ = n;
      }
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression BITWISE_OR exclusive_or_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " | " + b->place + ";");
          $$ = n;
      }
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression LOGICAL_AND inclusive_or_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " && " + b->place + ";");
          n->type = "bool"; $$ = n;
      }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression LOGICAL_OR logical_and_expression {
          Node* a=$1; Node* b=$3; Node* n=new Node();
          n->code=a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); n->code.push_back(n->place + " = " + a->place + " || " + b->place + ";");
          n->type = "bool"; $$ = n;
      }
	;

conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression QUESTION_MARK expression COLON conditional_expression {
          Node* cond = $1; Node* e1 = $3; Node* e2 = $5;
          Node* n = new Node();
          string Lfalse = newLabel();
          string Lend = newLabel();
          n->code = cond->code;
          n->place = newTemp();
          n->code.push_back("ifFalse " + cond->place + " goto " + Lfalse + ";");
          n->code.insert(n->code.end(), e1->code.begin(), e1->code.end());
          n->code.push_back(n->place + " = " + e1->place + ";");
          n->code.push_back("goto " + Lend + ";");
          n->code.push_back(Lfalse + ":");
          n->code.insert(n->code.end(), e2->code.begin(), e2->code.end());
          n->code.push_back(n->place + " = " + e2->place + ";");
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression assignment_operator assignment_expression {
          Node* left = $1; Node* right = $3;
          Node* n = new Node();
          n->code = left->code; n->code.insert(n->code.end(), right->code.begin(), right->code.end());
          string op = string($2);
          if (!left->type.empty() && !right->type.empty() && left->type != right->type) {
              yyerror("Type mismatch in assignment to '" + left->place + "' (" + left->type + " = " + right->type + ").");
          }
          if (op == "=") {
              n->code.push_back(left->place + " = " + right->place + ";");
          } else {
              string baseop;
              if (op == "+=") baseop = "+";
              else if (op == "-=") baseop = "-";
              else if (op == "*=") baseop = "*";
              else if (op == "/=") baseop = "/";
              else if (op == "%=") baseop = "%";
              else if (op == "&=") baseop = "&";
              else if (op == "|=") baseop = "|";
              else if (op == "^=") baseop = "^";
              else if (op == "<<=") baseop = "<<";
              else if (op == ">>=") baseop = ">>";
              else baseop = "";
              if (baseop.empty()) n->code.push_back("// unknown compound assignment " + op);
              else n->code.push_back(left->place + " = " + left->place + " " + baseop + " " + right->place + ";");
          }
          $$ = n;
      }
	;

assignment_operator
	: ASSIGN { $$ = $1; }
	| STAR_EQUAL { $$ = $1; }
	| DIV_EQUAL { $$ = $1; }
	| MOD_EQUAL { $$ = $1; }
	| PLUS_EQUAL { $$ = $1; }
	| MINUS_EQUAL { $$ = $1; }
	| LEFT_SHIFT_EQ { $$ = $1; }
	| RIGHT_SHIFT_EQ { $$ = $1; }
	| AND_EQUAL { $$ = $1; }
	| XOR_EQUAL { $$ = $1; }
	| OR_EQUAL { $$ = $1; }
	;

expression
	: assignment_expression { $$ = $1; }
	| expression COMMA assignment_expression {
          Node* n = $1;
          Node* e = $3;
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->place = e->place;
          $$ = n;
      }
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

declaration
	: declaration_specifiers SEMICOLON {
          Node* n = new Node();
          $$ = n;
      }
	| declaration_specifiers init_declarator_list SEMICOLON {
          $$ = $2;
      }
    | error SEMICOLON {yyerrok;}
    ;

declaration_specifiers
	: storage_class_specifier { $$ = new Node(); }
	| storage_class_specifier declaration_specifiers { $$ = $2; }
	| type_specifier { lastDeclType = string($1); $$ = new Node(); }
	| type_specifier declaration_specifiers { lastDeclType = string($1); $$ = $2; }
	| type_qualifier { $$ = new Node(); }
	| type_qualifier declaration_specifiers { $$ = $2; }
	;

init_declarator_list
	: init_declarator { $$ = $1; }
	| init_declarator_list COMMA init_declarator {
          Node* n = $1;
          n->code.insert(n->code.end(), $3->code.begin(), $3->code.end());
          $$ = n;
      }
	;

init_declarator
	: declarator {
          Node* n = new Node();
          if ($1) {
              string name = $1->place;
              bool ok = declareSymbol(name, lastDeclType);
              if (!ok) {
                  yyerror("Duplicate declaration of '" + name + "' in same scope.");
              }
              n->place = name; n->type = lastDeclType;
          }
          $$ = n;
      }
	| declarator ASSIGN initializer {
          Node* lhs = $1;
          Node* rhs = $3;
          Node* n = new Node();
          n->code = rhs->code;
          string name = lhs->place;
          bool ok = declareSymbol(name, lastDeclType);
          if (!ok) yyerror("Duplicate declaration of '" + name + "' in same scope.");
          n->code.push_back(name + " = " + rhs->place + ";");
          n->place = name; n->type = lastDeclType;
          if (!rhs->type.empty() && rhs->type != lastDeclType) {
              yyerror("Initializing '" + name + "' of type " + lastDeclType + " with incompatible type " + rhs->type + ".");
          }
          $$ = n;
      }
    ;

storage_class_specifier
	: TYPEDEF { $$ = new Node(); }
	| STATIC { $$ = new Node(); }
	| AUTO { $$ = new Node(); }
	;

type_specifier
	: VOID   { $$ = strdup("void"); lastDeclType = "void"; }
	| CHAR   { $$ = strdup("char"); lastDeclType = "char"; }
	| INT    { $$ = strdup("int"); lastDeclType = "int"; }
	| LONG   { $$ = strdup("long"); lastDeclType = "long"; }
	| DOUBLE { $$ = strdup("double"); lastDeclType = "double"; }
	| BOOL   { $$ = strdup("bool"); lastDeclType = "bool"; }
	| STRING { $$ = strdup("string"); lastDeclType = "string"; }
	| TYPE_NAME { $$ = $1; lastDeclType = string($1); }
	;

struct_or_class_specifier
	: struct_or_class IDENTIFIER LCURLY struct_or_class_member_list RCURLY { Node* n = new Node(); $$ = n; }
	| struct_or_class IDENTIFIER { Node* n = new Node(); $$ = n; }
	;

struct_or_class
	: STRUCT { $$ = new Node(); }
	| CLASS { $$ = new Node(); }
	;

struct_or_class_member_list
	: struct_or_class_member { $$ = $1; }
	| struct_or_class_member_list struct_or_class_member { Node* n = $1; if ($2) n->code.insert(n->code.end(), $2->code.begin(), $2->code.end()); $$ = n; }
	;

struct_or_class_member
	: access_specifier_label { $$ = $1; }
	| member_declaration { $$ = $1; }
	;

access_specifier_label
	: PUBLIC COLON { Node* n=new Node(); $$ = n; }
	| PRIVATE COLON { Node* n=new Node(); $$ = n; }
	| PROTECTED COLON { Node* n=new Node(); $$ = n; }
	;

member_declaration
	: specifier_qualifier_list struct_declarator_list SEMICOLON { Node* n=new Node(); $$ = n; }
	| specifier_qualifier_list SEMICOLON { Node* n=new Node(); $$ = n; }
	| specifier_qualifier_list declarator compound_statement { Node* n=new Node(); $$ = n; }
	| struct_or_class_specifier SEMICOLON { Node* n=new Node(); $$ = n; }
	| SEMICOLON { Node* n=new Node(); $$ = n; }
	| constructor_definition { $$ = $1; }
	| destructor_definition { $$ = $1; }
	;

constructor_definition
	: IDENTIFIER LROUND parameter_list RROUND compound_statement {
          Node* n = new Node(); $$ = n;
      }
	| IDENTIFIER LROUND RROUND compound_statement {
          Node* n = new Node(); $$ = n;
      }
	;

destructor_definition
	: TILDE IDENTIFIER LROUND RROUND compound_statement {
          Node* n = new Node(); $$ = n;
      }
	;

struct_declarator_list
	: struct_declarator { $$ = $1; }
	| struct_declarator_list COMMA struct_declarator { Node* n = $1; if ($3) n->code.insert(n->code.end(), $3->code.begin(), $3->code.end()); $$ = n; }
	;

struct_declarator
	: init_declarator { $$ = $1; }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list { $$ = new Node(); }
	| type_specifier { $$ = new Node(); }
	| type_qualifier specifier_qualifier_list { $$ = new Node(); }
	| type_qualifier { $$ = new Node(); }
	;

type_qualifier
	: CONST { $$ = new Node(); }
	;

declarator
	: pointer direct_declarator { $$ = $2; }
	| direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER {
          Node* n = new Node();
          n->place = string($1);
          $$ = n;
      }
	| LROUND declarator RROUND { $$ = $2; }
	| direct_declarator LSQUARE constant_expression RSQUARE { $$ = $1; }
	| direct_declarator LSQUARE RSQUARE { $$ = $1; }
	| direct_declarator LROUND parameter_type_list RROUND { $$ = $1; }
	| direct_declarator LROUND identifier_list RROUND { $$ = $1; }
	| direct_declarator LROUND RROUND { $$ = $1; }
	;

pointer
	: STAR { $$ = new Node(); }
	| STAR type_qualifier_list { $$ = new Node(); }
	| STAR pointer { $$ = new Node(); }
	| STAR type_qualifier_list pointer { $$ = new Node(); }
	;

type_qualifier_list
	: type_qualifier { $$ = new Node(); }
	| type_qualifier_list type_qualifier { $$ = new Node(); }
	;

parameter_type_list
	: parameter_list { $$ = $1; }
	;

parameter_list
	: parameter_declaration { $$ = $1; }
	| parameter_list COMMA parameter_declaration {
          Node* n = $1; $$ = n;
      }
	;

parameter_declaration
	: declaration_specifiers declarator {
          Node* n = new Node();
          n->place = $2->place;
          n->type = lastDeclType;
          $$ = n;
      }
	| declaration_specifiers abstract_declarator { Node* n = new Node(); $$ = n; }
	| declaration_specifiers { Node* n = new Node(); $$ = n; }
	;

identifier_list
	: IDENTIFIER { $$ = nullptr; }
	| identifier_list COMMA IDENTIFIER { $$ = nullptr; }
	;

type_name
	: specifier_qualifier_list { $$ = new Node(); }
	| specifier_qualifier_list abstract_declarator { $$ = new Node(); }
	;

abstract_declarator
	: pointer { $$ = new Node(); }
	| direct_abstract_declarator { $$ = new Node(); }
	| pointer direct_abstract_declarator { $$ = new Node(); }
	;

direct_abstract_declarator
	: LROUND abstract_declarator RROUND { $$ = new Node(); }
	| LSQUARE RSQUARE { $$ = new Node(); }
	| LSQUARE constant_expression RSQUARE { $$ = new Node(); }
	| direct_abstract_declarator LSQUARE RSQUARE { $$ = new Node(); }
	| direct_abstract_declarator LSQUARE constant_expression RSQUARE { $$ = new Node(); }
	| LROUND RROUND { $$ = new Node(); }
	| LROUND parameter_type_list RROUND { $$ = new Node(); }
	| direct_abstract_declarator LROUND RROUND { $$ = new Node(); }
	| direct_abstract_declarator LROUND parameter_type_list RROUND { $$ = new Node(); }
	;

initializer
	: assignment_expression { $$ = $1; }
	| LCURLY initializer_list RCURLY { $$ = $2; }
	| LCURLY initializer_list COMMA RCURLY { $$ = $2; }
	;

initializer_list
	: initializer { $$ = $1; }
	| initializer_list COMMA initializer {
          Node* n = $1; n->code.insert(n->code.end(), $3->code.begin(), $3->code.end()); $$ = n;
      }
	;

statement
	: labeled_statement { $$ = $1; }
	| compound_statement { $$ = $1; }
	| expression_statement { $$ = $1; }
	| selection_statement { $$ = $1; }
	| iteration_statement { $$ = $1; }
	| jump_statement { $$ = $1; }
	| io_statement { $$ = $1; }
    ;

io_statement
    : cout_expression SEMICOLON { $$ = $1; }
    | cin_expression SEMICOLON  { $$ = $1; }
    ;

cout_expression
    : COUT insertion_list { $$ = $2; }
    ;

insertion_list
    : LEFT_SHIFT assignment_expression {
          Node* e = $2;
          Node* n = new Node();
          n->code = e->code; n->code.push_back("print " + e->place + ";"); $$ = n;
      }
	| LEFT_SHIFT ENDL {
          Node* n = new Node();
          n->code.push_back("print endl;"); $$ = n;
      }
	| insertion_list LEFT_SHIFT ENDL {
          Node* n = $1; n->code.push_back("print endl;"); $$ = n;
      }
	| insertion_list LEFT_SHIFT assignment_expression {
          Node* n = $1; Node* e = $3;
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("print " + e->place + ";"); $$ = n;
      }
	;

cin_expression
    : CIN extraction_list { $$ = $2; }
    ;

extraction_list
    : RIGHT_SHIFT assignment_expression {
          Node* e = $2; Node* n = new Node();
          n->code = e->code; n->code.push_back("read " + e->place + ";"); $$ = n;
      }
    | extraction_list RIGHT_SHIFT assignment_expression {
          Node* n = $1; Node* e = $3;
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("read " + e->place + ";"); $$ = n;
      }
    ;

labeled_statement
	: IDENTIFIER COLON statement {
          Node* s = $3;
          s->code.insert(s->code.begin(), string($1) + ":");
          $$ = s;
      }
	| CASE constant_expression COLON statement {
          Node* s = $4;
          s->code.insert(s->code.begin(), string("case ") + $2->place + ":");
          $$ = s;
      }
	| DEFAULT COLON statement {
          Node* s = $3;
          s->code.insert(s->code.begin(), string("default:"));
          $$ = s;
      }
	;

compound_statement
	: LCURLY RCURLY {
          pushScope();
          Node* n = new Node();
          popScope();
          $$ = n;
      }
	| LCURLY statement_list RCURLY {
          pushScope();
          Node* n = $2;
          popScope();
          $$ = n;
      }
	;

statement_list
	: block_item { $$ = $1; }
	| statement_list block_item {
          Node* n = $1;
          if ($2) n->code.insert(n->code.end(), $2->code.begin(), $2->code.end());
          $$ = n;
      }
	;

block_item
    : statement { $$ = $1; }
    | declaration { $$ = $1; }
    | error RCURLY { yyerrok;}
    ;

expression_statement
	: SEMICOLON { Node* n = new Node(); $$ = n; }
	| expression SEMICOLON { $$ = $1; }
    ;

selection_statement
	: IF LROUND expression RROUND statement %prec LOWER_THAN_ELSE {
          Node* cond = $3; Node* thenS = $5;
          Node* n = new Node();
          string Lend = newLabel();
          n->code = cond->code;
          n->code.push_back("ifFalse " + cond->place + " goto " + Lend + ";");
          n->code.insert(n->code.end(), thenS->code.begin(), thenS->code.end());
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	| IF LROUND expression RROUND statement ELSE statement {
          Node* cond = $3; Node* thenS = $5; Node* elseS = $7;
          Node* n = new Node();
          string Lelse = newLabel(); string Lend = newLabel();
          n->code = cond->code;
          n->code.push_back("ifFalse " + cond->place + " goto " + Lelse + ";");
          n->code.insert(n->code.end(), thenS->code.begin(), thenS->code.end());
          n->code.push_back("goto " + Lend + ";");
          n->code.push_back(Lelse + ":");
          n->code.insert(n->code.end(), elseS->code.begin(), elseS->code.end());
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	| SWITCH LROUND expression RROUND statement {
          Node* n = $5; $$ = n;
      }
    ;

iteration_statement
	: WHILE LROUND expression RROUND statement {
          Node* cond = $3; Node* body = $5;
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back(Lbegin + ":");
          n->code.push_back("ifFalse " + cond->place + " goto " + Lend + ";");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.push_back("goto " + Lbegin + ";");
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	| UNTIL LROUND expression RROUND statement {
          Node* cond = $3; Node* body = $5;
          Node* n = new Node();
          string Lbegin = newLabel();
          n->code.push_back(Lbegin + ":");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back("ifTrue " + cond->place + " goto " + Lbegin + ";");
          $$ = n;
      }
	| DO statement WHILE LROUND expression RROUND SEMICOLON {
          Node* body = $2; Node* cond = $5;
          Node* n = new Node();
          string Lbegin = newLabel();
          n->code.push_back(Lbegin + ":");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back("ifTrue " + cond->place + " goto " + Lbegin + ";");
          $$ = n;
      }
	| FOR LROUND for_init_statement expression_statement RROUND statement {
          Node* init = $3; Node* cond = $4; Node* body = $6;
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
          n->code.push_back(Lbegin + ":");
          if (cond) {
              n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
              n->code.push_back("ifFalse " + cond->place + " goto " + Lend + ";");
          }
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.push_back("goto " + Lbegin + ";");
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	| FOR LROUND for_init_statement expression_statement expression RROUND statement {
          Node* init = $3; Node* cond = $4; Node* iter = $5; Node* body = $7;
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
          n->code.push_back(Lbegin + ":");
          if (cond) {
              n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
              n->code.push_back("ifFalse " + cond->place + " goto " + Lend + ";");
          }
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          if (iter) n->code.insert(n->code.end(), iter->code.begin(), iter->code.end());
          n->code.push_back("goto " + Lbegin + ";");
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	;
    
for_init_statement
	: expression_statement { $$ = $1; }
	| declaration { $$ = $1; }
    ;

jump_statement
	: GOTO IDENTIFIER SEMICOLON {
          Node* n = new Node();
          n->code.push_back("goto " + string($2) + ";");
          $$ = n;
      }
	| CONTINUE SEMICOLON {
          Node* n = new Node(); n->code.push_back("continue;"); $$ = n;
      }
	| BREAK SEMICOLON {
          Node* n = new Node(); n->code.push_back("break;"); $$ = n;
      }
	| RETURN SEMICOLON {
          Node* n = new Node(); n->code.push_back("return;"); $$ = n;
      }
	| RETURN expression SEMICOLON {
          Node* expr = $2;
          Node* n = new Node();
          n->code = expr->code;
          n->code.push_back("return " + expr->place + ";");
          $$ = n;
      }
    ;

translation_unit
	: external_declaration { finalRoot = $1; $$ = $1; }
	| translation_unit external_declaration {
          Node* a = $1; Node* b = $2;
          if (a) { a->code.insert(a->code.end(), b->code.begin(), b->code.end()); finalRoot = a; $$ = a; }
          else { finalRoot = b; $$ = b; }
      }
    | error { yyerrok;}
	;

external_declaration
	: function_definition { $$ = $1; }
	| struct_or_class_specifier SEMICOLON { Node* n = new Node(); $$ = n; }
	| declaration { $$ = $1; }
    ;

function_definition
	: declaration_specifiers declarator compound_statement {
          string fname = $2->place;
          if (fname.empty()) fname = "anon";
          Symbol* s = lookupSymbol(fname);
          if (s && s->isFunction) yyerror("Function redeclaration: " + fname);
          else declareSymbol(fname, "function", true, 0);
          currentFunction = fname;
          localTemp = 0; localLabel = 0;
          Node* n = new Node();
          n->code.push_back(fname + ":");
          if ($3) { pushScope(); n->code.insert(n->code.end(), $3->code.begin(), $3->code.end()); popScope(); }
          finalRoot = n;
          $$ = n;
      }
	| declarator compound_statement {
          string fname = $1->place;
          if (fname.empty()) fname = "anon";
          Symbol* s = lookupSymbol(fname);
          if (s && s->isFunction) yyerror("Function redeclaration: " + fname);
          else declareSymbol(fname, "function", true, 0);
          currentFunction = fname; localTemp = 0; localLabel = 0;
          Node* n = new Node();
          n->code.push_back(fname + ":");
          if ($2) { pushScope(); n->code.insert(n->code.end(), $2->code.begin(), $2->code.end()); popScope(); }
          finalRoot = n;
          $$ = n;
      }
    | error RCURLY { yyerrok;}
	;

lambda_expression
    : LSQUARE lambda_capture_clause RSQUARE lambda_declarator compound_statement { Node* n=new Node(); $$ = n; }
    | LSQUARE lambda_capture_clause RSQUARE compound_statement { Node* n=new Node(); $$ = n; }
    ;

lambda_declarator
    : lambda_parameter_clause trailing_return_opt { $$ = $1; }
    ;

lambda_parameter_clause
    : LROUND RROUND { $$ = new Node(); }
    | LROUND parameter_list RROUND { $$ = $2; }
    ;

trailing_return_opt
    :  { $$ = nullptr; }
    | ARROW type_name { $$ = $2; }
    ;

lambda_capture_clause
    : ASSIGN { $$ = new Node(); }
    | capture_list { $$ = $1; }
    | capture_list COMMA ASSIGN { $$ = $1; }
    | ASSIGN COMMA capture_list { $$ = $3; }
    ;

capture_list
    : IDENTIFIER { Node* n=new Node(); $$ = n; }
    | capture_list COMMA IDENTIFIER { Node* n=$1; $$ = n; }
    ;

%%


#include <cstdio>

void yyerror(const char *s);

int main(int argc, char** argv){
    pushScope();
    
    if (yyparse() == 0) {
        cerr << "Parsing completed successfully.\n";
    } else {
        cerr << "Parsing failed.\n";
    }

    if (!errors.empty()) {
        cout << "---- Errors found ----\n";
        for (auto &e : errors) 
            cout << e << "\n";

        return 1;
    }

    cerr<< "No errors found.\n";
    cerr<< "Generating three-address code:\n";

    if (finalRoot) {
        for (size_t i = 0; i < finalRoot->code.size(); ++i) {
            cout << (i+1) << ": " << finalRoot->code[i] << "\n";
        }
    }

    return 0;
}

