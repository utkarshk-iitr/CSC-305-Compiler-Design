%debug

%code requires {
    struct Node;
    struct Symbol;
}

%{
    #include <bits/stdc++.h>
    #include <fstream>
    #include <string>
    #include <cstring>
    #include <vector>
    #include <unordered_map>
    #include <map>
    #include <cstdlib>
    using namespace std;


    struct Node {
        vector<string> code;
        vector<string> syn;
        string place;
        string type;
        string kind;
        int argCount = 0;
        Node() : place(""), type("") , kind("") {}
        Node(string p, string t, string k) : place(p), type(t), kind(k) {}
    };

    struct Symbol {
        string name;
        string type;
        string kind;
        bool isFunction = false;
        int paramCount = 0;
        vector<string> dim;
        bool isDeclared = true;
        Symbol() : name(""), type(""), kind(""), isFunction(false), paramCount(0), isDeclared(true) {}
        Symbol(string n, string t, string k,vector<string> s, bool f=false, int p=0) : name(n), type(t), kind(k),dim(s), isFunction(f), paramCount(p) {}
    };

    struct funcInfo {
        string place;
        string kind;
        string returnType;
        bool hasReturn = false;
        vector<string> paramTypes;
        int paramCount = 0;
        funcInfo() : returnType("void"), hasReturn(false) {}
    };

    struct memberInfo {
        int offset = 0;
        string place;
        string type;
        string kind;
        funcInfo method;
    };

    unordered_map<string, funcInfo> funcTable;
    unordered_map<string, unordered_map<string,memberInfo>> classTable;
    vector< unordered_map<string, Symbol> > symStack;

    unordered_map<string,int> typeSize = {
        {"int", 4}, {"char", 1}, {"bool", 1}, {"double", 8}, {"string", 8}, {"nullptr", 8}
    };
    
    vector<string> errors;
    static string currentFunction = "global";
    static int globalTemp = 0, globalLabel = 0;
    static int localTemp = 0, localLabel = 0;
    static int classOffset = 0;
    static string lastDeclType = "int";
    static string lastClassType = "";
    static string lastUsage = "rvalue";
    static string lastFnType = "int";

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

    ofstream dbgfile("debug.txt");
    void dbg(const string &msg) {
        dbgfile << "Debug: " << msg << endl;
    }

    extern bool is_type_name(char const* s) {
        return typeSize.find(s) != typeSize.end();
    }

    void pushScope() {
        symStack.emplace_back();
    }
    void popScope() {
        if (!symStack.empty()) 
            symStack.pop_back();
    }

    Symbol* lookupSymbol(const string &name) {
        for (int i = (int)symStack.size()-1; i >= 0; --i) {
            auto &m = symStack[i];
            auto it = m.find(name);
            if (it != m.end()) return &it->second;
        }
        return nullptr;
    }

    funcInfo* lookupFunction(const string &name) {
        auto it = funcTable.find(name);
        if (it != funcTable.end()) return &(it->second);
        return nullptr;
    }   
    
    bool declareSymbol(const string &name, const string &type, const string k="",vector<string> syn=vector<string>(),bool isFunc=false, int params=0) {
        if (symStack.empty()) pushScope();
        auto &cur = symStack.back();
        if (cur.find(name) != cur.end()) {
            return false;
        }
        Symbol s; 
        s.name = name; s.type = type; s.kind = k; 
        s.dim = syn;
        s.isFunction = isFunc;
        s.paramCount = params;
        s.isDeclared = true;
        cur[name] = s;
        return true;
    }

    extern int yylineno;
    void yyerror(string s) {
        errors.push_back(string("Error at line ") + to_string(yylineno) + " : " + s);
    }

    void check_access(Symbol* sym) {
        if(sym==nullptr) return;
        if(sym->kind.find("private") != string::npos){
            yyerror("Can't access private member '" + sym->name + "'.");
        }
        else if(sym->kind.find("protected") != string::npos){
            yyerror("Can't access protected member '" + sym->name + "'.");
        }
    }

    void check_func_access(funcInfo* sym) {
        if(sym==nullptr) return;
        if(sym->kind.find("private") != string::npos){
            yyerror("Can't access private member function '" + sym->place + "'.");
        }
        else if(sym->kind.find("protected") != string::npos){
            yyerror("Can't access protected member function '" + sym->place + "'.");
        }
    }

    bool check_compatibility(const string &t1, const string &t2, const string &baseop) {
        if(baseop==""){
            return t1==t2;
        }
        
        if(baseop=="*" || baseop=="/"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            if(t1=="double" && t2=="double") return true;
            return false;
        }

        if(baseop=="%" || baseop=="<<" || baseop==">>"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            return false;
        }

        if(baseop=="&" || baseop=="^" || baseop=="|"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            if(t1=="bool" && t2=="bool") return true;
            return false;
        }

        if(baseop=="+"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            if(t1=="double" && t2=="double") return true;
            if(t1=="string" && t2=="string") return true;
            if(t1.back()=='*' && t2=="int") return true;
            return false;
        }

        if(baseop=="-"){
            if(t1=="int" && t2=="int") return true;
            if(t1=="long" && t2=="long") return true;
            if(t1=="double" && t2=="double") return true;
            if(t1.back()=='*' && t2=="int") return true;
            return false;
        }
        return false;
    }

    bool check_unary_comp(const string &t, const string &op) {
        if(op=="&") return true;
        if(op=="*"){
            if(t.back()=='*') return true;
            return false;
        }
        if(op=="+" || op=="-"){
            if(t=="int" || t=="long" || t=="double") return true;
            return false;
        }
        if(op=="~"){
            if(t=="int" || t=="long") return true;
            return false;
        }
        if(op=="!"){
            if(t=="bool") return true;
            return false;
        }
        if(op=="++" || op=="--"){
            if(t=="int" || t=="long" || t=="double") return true;
            return false;
        }
        return true;
    }

    bool check_casting(const string &from, const string &to, const string &s="") {
        if(from==to) return true;
        if(from=="int"){
            if(to=="double" || to=="char" || to=="bool" || to=="string" || to=="long") return true;
            return false;
        } 
        if(from=="double"){
            if(to=="int" || to=="char" || to=="bool" || to=="string" || to=="long") return true;
            return false;
        }
        if(from=="long"){
            if(to=="int" || to=="char" || to=="bool" || to=="string" || to=="double") return true;
            return false;
        }
        if(from=="char"){
            if(to=="int" || to=="bool" || to=="string" || to=="double" || to=="long") return true;
            return false;
        }   
        if(from=="bool"){
            if(to=="int" || to=="char" || to=="string" || to=="double" || to=="long") return true;
            return false;
        }
        if(from=="string"){
            if(to=="int"){
                try {
                    size_t pos;
                    stoi(s, &pos);
                    return pos == s.size();
                } 
                catch (...) {
                    return false;
                }
            }
            if(to=="double"){
                try {
                    size_t pos;
                    stod(s, &pos);
                    return pos == s.size();
                } 
                catch (...) {
                    return false;
                }
            }
            if(to=="long"){
                try {
                    size_t pos;
                    stol(s, &pos);
                    return pos == s.size();
                } 
                catch (...) {
                    return false;
                }
            }
            if(to=="char") return false;
            if(to=="bool") return true;
            return false;
        }
        
        if(from.back()=='*' && to.back()=='*') return true;
        return false;
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

%token<str> VOID INT DOUBLE CHAR BOOL LONG
%token<str> TRUE FALSE NULLPTR
%token<str> AUTO STATIC CONST
%token<str> CLASS STRUCT PUBLIC PRIVATE PROTECTED
%token<str> DELETE NEW CIN COUT ENDL

%token<str> IDENTIFIER INVALID_IDENTIFIER
%token<str> DECIMAL_LITERAL DOUBLE_LITERAL EXPONENT_LITERAL CHARACTER_LITERAL

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
%type<node> access_specifier_label member_declaration
%type<node> struct_declarator_list struct_declarator
%type<node> parameter_list
%type<node> parameter_declaration
%type<node> initializer initializer_list statement compound_statement statement_list labeled_statement
%type<node> selection_statement iteration_statement jump_statement io_statement cout_expression
%type<node> insertion_list cin_expression extraction_list external_declaration 
%type<node> function_definition primary_expression 
/* %type<node> trailing_return_opt lambda_capture_clause capture_list lambda_expression lambda_declarator lambda_parameter_clause */
%type<node> postfix_expression argument_expression_list unary_expression cast_expression
%type<node> multiplicative_expression additive_expression shift_expression relational_expression
%type<node> equality_expression and_expression exclusive_or_expression inclusive_or_expression
%type<node> logical_and_expression logical_or_expression conditional_expression block_item
%type<node> assignment_expression expression constant_expression declaration init_declarator
%type<node> init_declarator_list constant new_expression new_square delete_expression  
%type<node> function_header
%type<node> expression_statement translation_unit for_init_statement
%type<str> type_specifier assignment_operator unary_operator return_type pointer_opt pointer_list static_opt const_opt
%type<str> declaration_specifiers
<<<<<<< HEAD
%type<node> square_list members external
=======
%type<node> square_list default_label case_label case_list switch_block
>>>>>>> f20b7f7f09f370d3630bcfd92726a1942d8f6f10
/* %type<node> switch_head switch_statement case_item */

%start translation_unit

%%

// Done
primary_expression
	: IDENTIFIER 
    {
        dbg("primary_expression -> IDENTIFIER");
        Node* n = new Node();
        string name = string($1);
        n->place = name;
        Symbol* sym = lookupSymbol(name);
        dbg("");
        dbg("Looking up symbol: " + name);
        dbg("");
        if (!sym) {
            dbg("Symbol not found: " + name);
            yyerror("Use of undeclared identifier '" + name + "'.");
            n = nullptr;
        } 
        else{
            check_access(sym);
            dbg("");
            dbg("Found symbol: " + name);
            dbg("Type: " + sym->type);
            dbg("Kind: " + sym->kind);
            dbg("Dimensions: " + to_string(sym->dim.size()));
            for (const auto& d : sym->dim) {
                dbg(" - " + d);
            }
            dbg("");
            n->kind = sym->kind;
            n->type = sym->type;
            n->syn = sym->dim;
        }
        $$ = n;
    }
	| constant 
    { 
        dbg("primary_expression -> constant");
        $$ = $1;
    }
	| LROUND expression RROUND 
    {
        dbg("primary_expression -> ( expression )");
        $$ = $2;
    }
    /* | lambda_expression {
        dbg("primary_expression -> lambda_expression");
        $$ = $1; } */
	;

// Done
constant
    : DECIMAL_LITERAL       
    {
        dbg("constant -> DECIMAL_LITERAL");
        Node* n = new Node(string($1), "int", "const");
        n->argCount = stoi(string($1));
        dbg("");
        dbg("Integer constant value: " + to_string(n->argCount));
        dbg("");
        $$ = n;
    }
    | CHARACTER_LITERAL     
    {
        dbg("constant -> CHARACTER_LITERAL");
        Node* n = new Node(string($1), "char", "const");
        dbg("");
        dbg("Character constant value: " + string(1, $1[1]));
        dbg("");
        $$ = n;
    }
    /* | STRING_LITERAL        
    {
        dbg("constant -> STRING_LITERAL");
        Node* n = new Node(string($1), "char*", "const");
        $$ = n;
    } */
    | EXPONENT_LITERAL      
    {
        dbg("constant -> EXPONENT_LITERAL");
        Node* n = new Node(string($1), "double", "const");
        $$ = n;
    }
    | DOUBLE_LITERAL       
    {
        dbg("constant -> DOUBLE_LITERAL");
        Node* n = new Node(string($1), "double", "const");
        $$ = n;
    }
    | NULLPTR               
    {
        dbg("constant -> NULLPTR");
        Node* n = new Node("0", "nullptr", "const");
        $$ = n;
    }
    | TRUE                  
    {
        dbg("constant -> TRUE");
        Node* n = new Node("1", "bool", "const");
        $$ = n;
    }
    | FALSE                 
    {
        dbg("constant -> FALSE");
        Node* n = new Node("0", "bool", "const");
        $$ = n;
    }
    ;

postfix_expression
	: primary_expression 
    { 
        dbg("postfix_expression -> primary_expression");
        $$ = $1; 
    }
	| postfix_expression LSQUARE expression RSQUARE 
    {
        dbg("postfix_expression -> postfix_expression [ expression ]");
        Node* base = $1; 
        Node* idx = $3;
        Node* n = new Node();

        if(!base || !idx) {
            yyerror("Invalid array subscript operation.");
        }
        else{

        if(base->type.back()!='*'){
            yyerror("Subscripted value is not an array or pointer.");
        }
        if(idx->type!="int"){
            yyerror("Index is not an integer.");
        }
        if(base->kind.find("const")!=string::npos){
            yyerror("Cannot modify a const value.");
        }
        if(base->syn.empty()){
            yyerror("Too many dimensions for array.");
        }
        n->code = base->code;
        n->code.insert(n->code.end(), idx->code.begin(), idx->code.end());

        int p=1;
        dbg("");
        dbg("Array dimensions: ");
        dbg(to_string(base->syn.size()));

        for(auto x:base->syn)
        { 
            dbg("Dimension size: " + x);
            p = p * stoi(x);
        }
        dbg("");
        
        p /= stoi(base->syn.front());
        string offset = newTemp();
        
        string type = base->type.substr(0,base->type.size()-base->syn.size());
        
        n->code.push_back(offset + " = " + idx->place + " * " + to_string(p));
        n->code.push_back(offset + " = " + offset +" * "+to_string(typeSize[type]));
        n->place = newTemp();
        n->code.push_back(n->place + " = " + base->place + " + " + offset);
        n->type = base->type.substr(0,base->type.size()-1);
        n->kind = base->kind;
        n->syn = vector<string>(base->syn.begin()+1, base->syn.end());
        
        if(n->syn.empty()){
            n->place = "*" + n->place;
        }
        }
        $$ = n;
    }
	| postfix_expression LROUND RROUND 
    {
        dbg("postfix_expression -> postfix_expression ( )");
        Node* fun = $1;
        funcInfo* s = lookupFunction(fun->place);
        check_func_access(s);
        if(!s){
            yyerror("Call to non-function '" + fun->place + "'.");
        }
        if(s->paramCount != 0){
            yyerror("Call to function '" + fun->place + "' with incorrect number of arguments.");
        }

        Node* n = new Node();
        n->code = fun->code;
        n->type = s->returnType;

        if(fun->type=="void"){
            n->code.push_back("call " + fun->place + ", 0;");
        }
        else{
            n->place = newTemp();
            n->code.push_back(n->place + " = call " + fun->place + ", 0;");
        }
        $$ = n;
    }
	| postfix_expression LROUND argument_expression_list RROUND 
    {
        dbg("postfix_expression -> postfix_expression ( argument_expression_list )");
        Node* fun = $1;
        string name = fun->place;
        string original = fun->place;
        Node* args = $3;

        dbg("");
        dbg("argCount is:" + to_string(args->argCount));
        for(int i = 0; i < args->argCount;i++)
        {
            dbg("type is " + args->syn[i]);
            name += "_" + args->syn[i];
            
        }
        dbg("name is: " + name);

        funcInfo* s = lookupFunction(name);
        if(s)
            dbg("YES");
        dbg("");
        check_func_access(s);
        Node* n = new Node();
        if(!s){
            yyerror("Function '" + original + "' with given argument types not found.");
        }
        else if (s->paramCount != args->argCount) {
            yyerror("Call to function '" + original + "' with incorrect number of arguments.");
        }
        if(s)
        {
            for(int i=0; i<args->argCount; i++){
                if(s->paramTypes[i]!=args->syn[i]){
                    yyerror("Type mismatch in argument " + to_string(i+1) + " of function '" + original + "'.");
                }
            }
            n->code = fun->code;
            n->type = s->returnType;
            n->code.insert(n->code.end(), args->code.begin(), args->code.end());
            
            if(s->returnType=="void") {
                n->type = "";
                n->code.push_back("call " + original + ", " + to_string(args->argCount));
            }
            else{
                n->place = newTemp();
                n->code.push_back(n->place + " = call " + original + ", " + to_string(args->argCount));
            }
        }
        $$ = n;
    }
	| postfix_expression DOT IDENTIFIER {
        dbg("postfix_expression -> postfix_expression . IDENTIFIER");
            Node* obj = $1;
            if(obj->type!="struct" && obj->type!="class"){
                yyerror("Dot operator can only be applied to struct or class.");
            }
            string nm = obj->place + "." + string($3);
            Symbol* s = lookupSymbol(nm);
            funcInfo* f = lookupFunction(nm);

            Node* n = new Node();
            if(s){
                check_access(s);
                n->type = s->type;
                n->kind = s->kind;
            }
            else if(f){
                check_func_access(f);
                n->type = f->returnType;
            }
            else{
                yyerror("No member or function named '" + nm+"'.");
            }
            n->code = obj->code;
            n->place = newTemp();
            n->code.push_back(n->place + " = " + nm);
            $$ = n;
      }
	| postfix_expression ARROW IDENTIFIER {
        dbg("postfix_expression -> postfix_expression ARROW IDENTIFIER");
          Node* obj = $1;
          if(obj->type.back()!='*'){
              yyerror("Arrow operator can only be applied to pointer.");
          }

            Symbol* sym = lookupSymbol(obj->type.substr(0,obj->type.size()-1));
            if(!sym){
                yyerror("Pointer must be to struct or class.");
            }
            if(sym->type!="struct" && sym->type!="class"){
                yyerror("Pointer must be to struct or class.");
            }

            Node* n = new Node();
            n->code = obj->code;
            string tmp = newTemp();
            n->code.push_back(tmp + " = *" + obj->place);
            string nm = obj->place + "->" + string($3);
            Symbol* s = lookupSymbol(nm);
            funcInfo* f = lookupFunction(nm);
            n->code = obj->code;
            if(s){
                check_access(s);
                n->type = s->type;
                n->kind = s->kind;
                // string offset = newTemp();
                // n->code.push_back(offset + " = " + n->place + " + " + to_string(paramCount));
            }
            else if(f){
                check_func_access(f);
                n->type = f->returnType;
            }
            else{
                yyerror("No member or function named '" + nm+"'.");
            }
            n->place = newTemp();
            n->code.push_back(n->place + " = " + tmp + "." + string($3));
            $$ = n;
      }
	| postfix_expression INCREMENT {
          dbg("postfix_expression -> postfix_expression ++");
          Node* v = $1;
          if(check_unary_comp(v->type,"++")){
              yyerror("Invalid type '" + v->type + "' for increment.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          string old = newTemp();
            n->code.push_back(old + " = " + v->place);          // load old value from address
            n->code.push_back(v->place + " = " + old + " + 1;");      // store back incremented value
            n->place = old;
          n->type = v->type;
          n->kind = "rvalue";
          $$ = n;
      }
	| postfix_expression DECREMENT { 
            dbg("postfix_expression -> postfix_expression --");
          Node* v = $1;
          if(check_unary_comp(v->type,"--")){
              yyerror("Invalid type '" + v->type + "' for decrement.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          string old = newTemp();
            n->code.push_back(old + " = " + v->place);          // load old value from address
            n->code.push_back(v->place + " = " + old + " - 1;");      // store back incremented value
            n->place = old;
          n->type = v->type;
          $$ = n;
      }    
	;

// Done
argument_expression_list
	: assignment_expression 
    {
        dbg("argument_expression_list -> assignment_expression");
        Node* e = $1;
        if(e->place.empty()) {
            yyerror("Void expression cannot be used as function argument.");
        }
        Node* n = new Node();
        n->code = e->code;
        n->syn.push_back(e->type);
        n->argCount = 1;
        n->code.push_back("param " + e->place);
        n->type = e->type;
        dbg("");
        dbg("argcount is "+ to_string(n->argCount)+", type is "+n->type);
        dbg("");
        $$ = n;
    }
	| argument_expression_list COMMA assignment_expression 
    {
        dbg("argument_expression_list -> argument_expression_list , assignment_expression");
        Node* e = $3;
        if(e->place.empty()){
            yyerror("Void expression cannot be used as function argument.");
        }
        Node* n = $1;
        n->code.insert(n->code.end(), e->code.begin(), e->code.end());
        n->argCount = n->argCount + 1;
        n->syn.push_back(e->type);
        n->code.push_back("param " + e->place);
        dbg("");
        dbg("argcount is " + to_string(n->argCount) + ", type is " + e->type);
        dbg("");
        $$ = n;
    }
	;

// Done
unary_expression
	: postfix_expression { 
        dbg("unary_expression -> postfix_expression");
        $$ = $1; }
	| INCREMENT unary_expression {
          dbg("unary_expression -> ++ unary_expression");
          Node* v = $2;
          if(!check_unary_comp(v->type,"++")){
              yyerror("Invalid type '" + v->type + "' for increment.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " + 1;");
          $$ = n;
      }
	| DECREMENT unary_expression {
            dbg("unary_expression -> -- unary_expression");
          Node* v = $2;
          if(!check_unary_comp(v->type,"--")){
              yyerror("Invalid type '" + v->type + "' for decrement.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->place + " = " + v->place + " - 1;");
          $$ = n;
      }
	| unary_operator cast_expression {
            dbg("unary_expression -> unary_operator cast_expression");
          Node* rhs = $2;
          Node* n = new Node();
          n->code = rhs->code;
          string op = string($1);
          if(!check_unary_comp(rhs->type,op)){
              yyerror("Invalid operation '" + op + "' on type '" + rhs->type + "'.");
            }
          if (op == "&") {
              n->place = newTemp();
              n->code.push_back(n->place + " = &" + rhs->place);
              n->type = rhs->type + "*";
          } else if (op == "*") {
              n->place = newTemp();
              n->code.push_back(n->place + " = *" + rhs->place);
              n->type = rhs->type.substr(0, rhs->type.size() - 1);
          } else if (op == "+") {
              n->place = rhs->place;
              n->type = rhs->type;
          } else if (op == "-") {
              n->place = newTemp();
              n->code.push_back(n->place + " = 0 - " + rhs->place);
              n->type = rhs->type;
          } else if (op == "~") {
              n->place = newTemp();
              n->code.push_back(n->place + " = ~" + rhs->place);
              n->type = rhs->type;
          } else if (op == "!") {
              n->place = newTemp();
              n->code.push_back(n->place + " = !" + rhs->place);
              n->type = "bool";
          }
          $$ = n;
      }
	| SIZEOF LROUND unary_expression RROUND{
          dbg("unary_expression -> sizeof ( unary_expression )");
          Node* n = new Node(); 
          n->place = newTemp(); 
            n->code = $3->code;
            string t = $3->type;
            if(t.back()=='*') t = "nullptr";
          n->code.push_back(n->place + " = " + to_string(typeSize[t]));
            n->type = "int";
          $$ = n;
      }
	| SIZEOF LROUND return_type RROUND {
            dbg("unary_expression -> sizeof ( type_name )");
          Node* n = new Node(); 
          n->place = newTemp(); 
            string t = $3;
            if(t.back()=='*') t = "nullptr";
          n->code.push_back(n->place + " = " + to_string(typeSize[t]));
            n->type = "int";
          $$ = n;
      }
	| delete_expression { 
        dbg("unary_expression -> delete_expression");
        $$ = $1; }
	| new_expression { 
        dbg("unary_expression -> new_expression");
        $$ = $1; }
	;

// Done
unary_operator
	: BITWISE_AND { 
        dbg("unary_operator -> &");
        $$ = strdup($1); }
	| STAR { 
        dbg("unary_operator -> *");
        $$ = strdup($1); }
	| PLUS { 
        dbg("unary_operator -> +");
        $$ = strdup($1); }
	| MINUS { 
        dbg("unary_operator -> -");
        $$ = strdup($1); }
	| TILDE { 
        dbg("unary_operator -> ~");
        $$ = strdup($1); }
	| LOGICAL_NOT { 
        dbg("unary_operator -> !");
        $$ = strdup($1); }
	;

// Done
new_expression 
	: NEW return_type new_square {
            dbg("new_expression -> NEW type_specifier pointer_opt new_square");
          Node* n = new Node();
            string tmp = newTemp();
            string w = string($2);
            if(string($2).back()=='*') w = "nullptr";
            n->code = $3->code;
            n->place = newTemp();
            n->code.push_back(tmp+ " = " + $3->place + " * " + to_string(typeSize[w]));
            n->code.push_back(n->place + " = call malloc, "+tmp);
            n->type = string($2) + $3->type + "*";
          $$ = n;
      }
	| NEW return_type {
            dbg("new_expression -> NEW return_type");
          Node* n = new Node();
          n->place = newTemp();
          string w = string($2);
          if(string($2).back()=='*') w = "nullptr";
          n->code.push_back(n->place + " = call malloc, "+to_string(typeSize[w]));
          n->type = string($2) + "*";
          $$ = n;
      }
	;

// Done
new_square 
	: LSQUARE expression RSQUARE { 
            dbg("new_square -> [ expression ]");
            Node* n = new Node();
            n->code = $2->code;
            n->place = $2->place;
            n->type = "*";
            n->argCount = 1;
            $$ = n; 
        }
	| new_square LSQUARE expression RSQUARE { 
            dbg("new_square -> new_square [ expression ]");
            Node* n = $1; Node* e = $3;
            n->code.insert(n->code.end(), e->code.begin(), e->code.end());
            string temp1 = newTemp();
            n->code.push_back(temp1 + " = " + n->place + " * "+e->place);
            n->place = temp1;
            n->type = n->type + "*";
            n->argCount = n->argCount + 1;
            $$ = n;
          }
	;

// Done
delete_expression
	: DELETE LSQUARE RSQUARE cast_expression {
          dbg("delete_expression -> DELETE [ ] cast_expression");
          Node* n = new Node();
          n->code = $4->code;
          n->code.push_back("call free, " + $4->place);
          $$ = n;
      }
	| DELETE cast_expression {
            dbg("delete_expression -> DELETE cast_expression");
          Node* n = new Node();
          n->code = $2->code;
          n->code.push_back("call free, " + $2->place);
          $$ = n;
      }
	;

// Done
cast_expression
	: unary_expression { 
        dbg("cast_expression -> unary_expression");
        $$ = $1; }
	| LROUND return_type RROUND cast_expression {
            dbg("cast_expression -> ( type_name ) cast_expression");
            string a = $2; Node* b = $4;
            if(!check_casting(b->type,a)){
                yyerror("Unable to cast from '" + b->type + "' to '" + a + "'.");
            }
            Node* n = new Node();
            n->code = b->code;
            n->place = newTemp();
            n->code.push_back(n->place + " = " + b->type + "_to_"+ a +" "+ b->place);
            n->type = a;
          $$ = n;
      }
	;

// Done
multiplicative_expression
	: cast_expression { 
        dbg("multiplicative_expression -> cast_expression");
        $$ = $1; }
	| multiplicative_expression STAR cast_expression {
        dbg("multiplicative_expression -> multiplicative_expression * cast_expression");
          Node* a = $1; Node* b = $3;
          if(!check_compatibility(a->type,b->type,"*")){
            yyerror("Type incompatibility in multiply.");
          }
          Node* n = new Node();
          n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " * " + b->place);
          n->type = a->type;
          $$ = n;
      }
	| multiplicative_expression DIVIDE cast_expression {
        dbg("multiplicative_expression -> multiplicative_expression / cast_expression");
          Node* a = $1; Node* b = $3;
          if(!check_compatibility(a->type,b->type,"/")){
            yyerror("Type incompatibility in divide.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " / " + b->place);
          n->type = a->type;
          $$ = n;
      }
	| multiplicative_expression MODULUS cast_expression {
        dbg("multiplicative_expression -> multiplicative_expression % cast_expression");
          Node* a = $1; Node* b = $3;
          if(!check_compatibility(a->type,b->type,"%")){
            yyerror("Type incompatibility in modulus.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " % " + b->place);
          n->type = a->type;
          $$ = n;
      }
	;

// Done
additive_expression
	: multiplicative_expression { 
        dbg("additive_expression -> multiplicative_expression");
        $$ = $1; }
	| additive_expression PLUS multiplicative_expression {
            dbg("additive_expression -> additive_expression + multiplicative_expression");
          Node* a = $1; Node* b = $3;
          if(!check_compatibility(a->type,b->type,"+")){
            yyerror("Type incompatibility in plus.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " + " + b->place);
          n->type = a->type;
          $$ = n;
      }
	| additive_expression MINUS multiplicative_expression {
            dbg("additive_expression -> additive_expression - multiplicative_expression");
          Node* a = $1; Node* b = $3;
          if(!check_compatibility(a->type,b->type,"-")){
            yyerror("Type incompatibility in minus.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " - " + b->place);
          n->type = a->type;
          $$ = n;
      }
	;

// Done
shift_expression
	: additive_expression { 
        dbg("shift_expression -> additive_expression");
        $$ = $1; }
	| shift_expression LEFT_SHIFT additive_expression {
            dbg("shift_expression -> shift_expression << additive_expression");
          Node* a = $1; Node* b = $3;
          if(!check_compatibility(a->type,b->type,"<<")){
            yyerror("Type incompatibility in left shift.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " << " + b->place);
          n->type = a->type; 
          $$ = n;
      }
	| shift_expression RIGHT_SHIFT additive_expression {
            dbg("shift_expression -> shift_expression >> additive_expression");
          Node* a = $1; Node* b = $3;
          if(!check_compatibility(a->type,b->type,">>")){
            yyerror("Type incompatibility in right shift.");
          }
          Node* n = new Node();
          n->code = a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place = newTemp();
          n->code.push_back(n->place + " = " + a->place + " >> " + b->place);
          n->type = a->type; 
          $$ = n;
      }
	;

// Done
relational_expression
	: shift_expression { 
        dbg("relational_expression -> shift_expression");
        $$ = $1; }
	| relational_expression GREATER_THAN shift_expression {
          dbg("relational_expression -> relational_expression > shift_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " > " + b->place);
          n->type = "bool"; $$ = n;
      }
	| relational_expression LESS_THAN shift_expression {
          dbg("relational_expression -> relational_expression < shift_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " < " + b->place);
          n->type = "bool"; $$ = n;
      }
	| relational_expression LESS_EQUAL shift_expression {
            dbg("relational_expression -> relational_expression <= shift_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
          if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " <= " + b->place);
          n->type = "bool"; $$ = n;
      }
	| relational_expression GREATER_EQUAL shift_expression {
            dbg("relational_expression -> relational_expression >= shift_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
          if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " >= " + b->place);
          n->type = "bool"; $$ = n;
      }
	;

// Done
equality_expression
	: relational_expression { 
        dbg("equality_expression -> relational_expression");
        $$ = $1; }
	| equality_expression EQUAL relational_expression {
            dbg("equality_expression -> equality_expression == relational_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in equality expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " == " + b->place);
          n->type = "bool"; 
          $$ = n;
      }
	| equality_expression NOT_EQUAL relational_expression {
            dbg("equality_expression -> equality_expression != relational_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
          if(a->type != b->type){
              yyerror("Type incompatibility in equality expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " != " + b->place);
          n->type = "bool"; 
          $$ = n;
      }
	;

// Done
and_expression
	: equality_expression { 
        dbg("and_expression -> equality_expression");
        $$ = $1; }
	| and_expression BITWISE_AND equality_expression {
            dbg("and_expression -> and_expression & equality_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
            if(!check_compatibility(a->type,b->type,"&")){
                yyerror("Type incompatibility in bitwise AND expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " & " + b->place);
          n->type = a->type;
          $$ = n;
      }
	;

// Done
exclusive_or_expression
	: and_expression { 
        dbg("exclusive_or_expression -> and_expression");
        $$ = $1; }
	| exclusive_or_expression BITWISE_XOR and_expression {
            dbg("exclusive_or_expression -> exclusive_or_expression ^ and_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
            if(!check_compatibility(a->type,b->type,"^")){
                yyerror("Type incompatibility in bitwise XOR expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " ^ " + b->place);
            n->type = a->type;
          $$ = n;
      }
	;

// Done
inclusive_or_expression
	: exclusive_or_expression { 
        dbg("inclusive_or_expression -> exclusive_or_expression");
        $$ = $1; }
	| inclusive_or_expression BITWISE_OR exclusive_or_expression {
            dbg("inclusive_or_expression -> inclusive_or_expression | exclusive_or_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
          if(!check_compatibility(a->type,b->type,"|")){
              yyerror("Type incompatibility in bitwise OR expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " | " + b->place);
            n->type = a->type;
          $$ = n;
      }
	;

// Done
logical_and_expression
	: inclusive_or_expression { 
        dbg("logical_and_expression -> inclusive_or_expression");
        $$ = $1; }
	| logical_and_expression LOGICAL_AND inclusive_or_expression {
            dbg("logical_and_expression -> logical_and_expression && inclusive_or_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
            if(a->type!="bool" || b->type!="bool"){
                yyerror("Type incompatibility in logical AND expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " && " + b->place);
          n->type = "bool"; 
          $$ = n;
      }
	;

// Done
logical_or_expression
	: logical_and_expression { 
        dbg("logical_or_expression -> logical_and_expression");
        $$ = $1; }
	| logical_or_expression LOGICAL_OR logical_and_expression {
            dbg("logical_or_expression -> logical_or_expression || logical_and_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
          if(a->type!="bool" || b->type!="bool"){
              yyerror("Type incompatibility in logical OR expression.");
          }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp(); 
          n->code.push_back(n->place + " = " + a->place + " || " + b->place);
          n->type = "bool"; 
          $$ = n;
      }
	;

conditional_expression
	: logical_or_expression 
    { 
        dbg("conditional_expression -> logical_or_expression");
        $$ = $1; 
    }
	| logical_or_expression QUESTION_MARK expression COLON conditional_expression {
            dbg("conditional_expression -> logical_or_expression ? expression : conditional_expression");
          Node* cond = $1; Node* e1 = $3; Node* e2 = $5;
          Node* n = new Node();
          string Lfalse = newLabel();
          string Lend = newLabel();
          n->code = cond->code;
          n->place = newTemp();
          n->code.push_back("ifFalse " + cond->place + " goto " + Lfalse);
          n->code.insert(n->code.end(), e1->code.begin(), e1->code.end());
          n->code.push_back(n->place + " = " + e1->place);
          n->code.push_back("goto " + Lend);
          n->code.push_back(Lfalse + ":");
          n->code.insert(n->code.end(), e2->code.begin(), e2->code.end());
          n->code.push_back(n->place + " = " + e2->place);
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	;

// Done
assignment_expression
	: conditional_expression { 
        dbg("assignment_expression -> conditional_expression");
        $$ = $1; }
	| unary_expression assignment_operator assignment_expression {
            dbg("assignment_expression -> unary_expression assignment_operator assignment_expression");
          Node* left = $1; 
          Node* right = $3;
          Node* n = new Node();
          n->code = left->code; 
          n->code.insert(n->code.end(),right->code.begin(),right->code.end());
          string op = string($2);
            string baseop = op.substr(0,op.size()-1);
          if (!check_compatibility(left->type,right->type,baseop)) {
              yyerror("Type incompatibility in assignment to '" + left->place + "'.");
          }
          if(left->kind.find("const")!=string::npos){
              yyerror("Cannot assign to const variable '" + left->place + "'.");
          }
          if (op == "=") {
              n->code.push_back(left->place + " = " + right->place);
          } 
          else {
              n->code.push_back(left->place + " = " + left->place + " " + baseop + " " + right->place);
          }
          $$ = n;
      }
	;


// Done
assignment_operator
	: ASSIGN { 
        dbg("assignment_operator -> =");
        $$ = strdup($1); }
	| STAR_EQUAL { 
        dbg("assignment_operator -> *=");
        $$ = strdup($1); }
	| DIV_EQUAL { 
        dbg("assignment_operator -> /=");
        $$ = strdup($1); }
	| MOD_EQUAL { 
        dbg("assignment_operator -> %=");
        $$ = strdup($1); }
	| PLUS_EQUAL { 
        dbg("assignment_operator -> +=");
        $$ = strdup($1); }
	| MINUS_EQUAL { 
        dbg("assignment_operator -> -=");
        $$ = strdup($1); }
	| LEFT_SHIFT_EQ { 
        dbg("assignment_operator -> <<=");
        $$ = strdup($1); }
	| RIGHT_SHIFT_EQ { 
        dbg("assignment_operator -> >>=");
        $$ = strdup($1); }
	| AND_EQUAL { 
        dbg("assignment_operator -> &=");
        $$ = strdup($1); }
	| XOR_EQUAL { 
        dbg("assignment_operator -> ^=");
        $$ = strdup($1); }
	| OR_EQUAL { 
        dbg("assignment_operator -> |=");
        $$ = strdup($1); }
	;

// Done
expression
	: assignment_expression 
    { 
        dbg("expression -> assignment_expression");
        $$ = $1; 
    }
	| expression COMMA assignment_expression
        {
            dbg("expression -> expression , assignment_expression");
            Node* n = new Node();
            n->code = $1->code;
            n->code.insert(n->code.end(), $3->code.begin(), $3->code.end());
            n->place = $3->place;
            $$ = n;
        }
	;

// Done
constant_expression
	: conditional_expression 
    { 
        dbg("constant_expression -> conditional_expression");
        $$ = $1; 
    }
	;

// Done
declaration
	: declaration_specifiers init_declarator_list SEMICOLON
    {
        dbg("declaration -> declaration_specifiers init_declarator_list ;");
        $$ = $2;
    }
    ;
    
// Done
declaration_specifiers
    : type_specifier {
        dbg("declaration_specifiers -> type_specifier");
        lastDeclType = string($1);
        $$ = strdup(lastDeclType.c_str());
	}
    | STATIC type_specifier {
        dbg("declaration_specifiers -> static type_specifier");
        lastDeclType = string($1)+string($2);
        $$ = strdup(lastDeclType.c_str());
    }
    | CONST type_specifier {
        dbg("declaration_specifiers -> const type_specifier");
        lastDeclType = string($1)+string($2);
        $$ = strdup(lastDeclType.c_str());
	}
    | STATIC CONST type_specifier {
        dbg("declaration_specifiers -> static const type_specifier");
        lastDeclType = string($1)+string($2)+string($3);
        $$ = strdup(lastDeclType.c_str());
    }
	;

// Done
init_declarator_list
	: init_declarator 
    {
        dbg("init_declarator_list -> init_declarator");
        $$ = $1; 
    }
	| init_declarator_list COMMA init_declarator 
    {
        dbg("init_declarator_list -> init_declarator_list , init_declarator");
        Node* n = $1;
        n->code.insert(n->code.end(), $3->code.begin(), $3->code.end());
        $$ = n;
    }
	;

// Done
pointer_opt
    : pointer_list
    {
        dbg("pointer_opt -> pointer_list");
        $$ = $1;
    }
    | 
    {
        dbg("pointer_opt -> <empty>");
        $$ = strdup("");
    }
    ;

// Done
pointer_list
    : pointer_list STAR
    {
        dbg("pointer_list -> pointer_list *");
        $$ = strdup((string("*")+string($1)).c_str());
    }
    | STAR
    {
        dbg("pointer_list -> *");
        $$ = strdup("*");
    }
    ;

// Done
init_declarator
    : IDENTIFIER
    {
        dbg("init_declarator -> IDENTIFIER ");

        if(lastDeclType.find("const")!=string::npos){
            yyerror("Const variable '" + string($1) + "' must be initialized.");
        }
        Node* n = new Node();
        n->place = string($1);
        // n->code = {n->place + " = " + '0'};
        n->type = lastDeclType;
        n->kind = "";

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        
        n->argCount = 0;
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }
        
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize[n->type];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared variable is: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");

        $$ = n;
    }
    | IDENTIFIER square_list 
    {    
        dbg("init_declarator -> IDENTIFIER square_list ");
        if(lastDeclType.find("const")!=string::npos){
            yyerror("Const variable '" + string($1) + "' must be initialized.");
        }
        Node* n = new Node();
        n->place = string($1);
        n->code = $2->code;
        n->argCount = $2->argCount;
        n->type = lastDeclType;
        n->kind = "array";
        n->syn = $2->syn;

        dbg("");
        dbg("Array dimensions: ");
        for (const auto& dim : n->syn) {
            dbg(" - " + dim);
        }
        dbg("");
        if(n->type.find("static")!=string::npos){
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        for(int i = 0; i < $2->argCount; i++)
        {
            n->type += "*";
        }

        bool ok = declareSymbol(n->place, n->type, n->kind, n->syn);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }
        
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                int p = 1;
                for(int i = 0; i < n->argCount; i++)
                {
                    p *= stoi(n->syn[i]);
                }
                classOffset += p * typeSize[n->type.substr(0, n->type.size() - n->argCount)];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared array: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        for(int i = 0; i < n->argCount; i++)
        {
            dbg("Dimension " + to_string(i+1) + ": " + n->syn[i]);
        }
        dbg("");
        $$ = n;
    }
	| pointer_list IDENTIFIER
    {    
        dbg("init_declarator -> pointer_list IDENTIFIER ");

        if(lastDeclType.find("const")!=string::npos){
            yyerror("Const variable '" + string($1) + "' must be initialized.");
        }

        Node* n = new Node();
        n->place = string($2);
        n->code = {};
        n->argCount = 0;
        string stars = string($1);
        n->type = lastDeclType + stars;
        n->kind = "pointer";

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }
       
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize["nullptr"];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared pointer: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");
        $$ = n;
    }
    // not array, not pointer
    | IDENTIFIER ASSIGN assignment_expression 
    {
        dbg("init_declarator -> IDENTIFIER = assignment_expression ");
        Node* n = new Node();
        string name = string($1);
        n->place = name;
        n->type = lastDeclType;
        n->code = $3->code;
        n->argCount = 0;
        n->kind = "";

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        n->code.push_back(n->place + " = " + $3->place);

        if(n->type != $3->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
        
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize[n->type];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared variable: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");
        $$ = n;
    }
    // pointer not array
    | pointer_list IDENTIFIER ASSIGN assignment_expression 
    {
        dbg("init_declarator -> pointer_list IDENTIFIER = assignment_expression ");
        Node* n = new Node();
        string name = string($2);
        n->place = name;
        string stars = string($1);
        
        n->type = lastDeclType + stars;
        n->code = $4->code;
        n->code.push_back(n->place + " = " + $4->place);
        n->argCount = 0;
        n->kind = "pointer";

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,7);
            n->kind += " static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,6);
            n->kind += " const";
        }
        
        if ($4->type!=n->type){
            yyerror("Type mismatch in initialization of '" + name + "'."); 
        }

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
       
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize["nullptr"];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared pointer: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");
        $$ = n;
    }
    // array not pointer
    | IDENTIFIER square_list ASSIGN initializer
    {
        dbg("init_declarator -> IDENTIFIER square_list = initializer ");
        Node* n = new Node();
        string name = string($1);
        n->place = name;
        n->type = lastDeclType;
        n->kind = "array";
        n->syn = $2->syn;
        n->argCount = $2->argCount;
        n->code = $2->code;
        n->code.insert(n->code.end(), $4->code.begin(), $4->code.end());
        
        if(n->type.find("static")!=string::npos){
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }

        int p = 1;
        for(int i = 0; i < n->argCount; i++)
        {
            n->type += "*";
            p = p * stoi($2->syn[i]);
        }

        if(lastDeclType != $4->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        if(p < $4->argCount){
            yyerror("Number of elements in initializer is greater than array size for '" + name + "'.");
        }

        bool ok = declareSymbol(n->place,n->type,n->kind,n->syn);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
       
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += p * typeSize[n->type.substr(0, n->type.size() - n->argCount)];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared array: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        for(int i = 0; i < n->argCount; i++)
        {
            dbg("Dimension " + to_string(i+1) + ": " + n->syn[i]);
        }
        dbg("");
        $$ = n;
    }
    /* | pointer_list IDENTIFIER square_list ASSIGN initializer
    {
        dbg("init_declarator -> pointer_list IDENTIFIER square_list = initializer ");
        Node* n = new Node();
        string name = string($2);
        n->place = name;
        string stars = string($1);
        n->type = lastDeclType + stars;
        n->kind = "pointer array";
        n->syn = $3->syn;
        n->argCount = $3->argCount;
        n->code = $3->code;
        n->code.insert(n->code.end(), $5->code.begin(), $5->code.end());

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,7);
            n->kind += " static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,6);
            n->kind += " const";
        }

        int p = 1;
        for(int i = 0; i < n->argCount; i++)
        {
            n->type += "*";
            p = p * stoi($3->syn[i]);
        }

        if(lastDeclType != $5->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        if(p < $5->argCount){
            yyerror("Number of elements in initializer is greater than array size for '" + name + "'.");
        }

        bool ok = declareSymbol(n->place,n->type,n->kind,n->syn);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
       
        if(lastClassType != "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += p * typeSize["nullptr"];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }

        dbg("");
        dbg("Declared pointer array: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        for(int i = 0; i < n->argCount; i++)
        {
            dbg("Dimension " + to_string(i+1) + ": " + n->syn[i]);
        }
        dbg("");
        $$ = n;
    } */
    ;


// Done
initializer
	: LCURLY initializer_list RCURLY 
    { 
        dbg("initializer -> { initializer_list }");
        $$ = $2;
    }
	;

// Done
initializer_list
	: assignment_expression 
    { 
        dbg("initializer_list -> assignment_expression");
        Node * n = $1;
        n->argCount = 1;
        $$ = n;
    }
	| initializer_list COMMA assignment_expression 
    {
        dbg("initializer_list -> initializer_list , assignment_expression");
        Node* n = $1; 

        if(n->type != $3->type)
        {
            yyerror("Type mismatch in initializer list.");
        }

        n->code.insert(n->code.end(), $3->code.begin(), $3->code.end());
        n->argCount = n->argCount + 1;
        $$ = n;
    }
	;

// Done
square_list
    : square_list LSQUARE constant_expression RSQUARE
    {
        dbg("square_list -> square_list [ constant_expression ]");
        Node* n = $1;
        n->argCount = n->argCount + 1;
        n->code.insert(n->code.end(),$3->code.begin(),$3->code.end());
        n->syn.push_back(to_string($3->argCount));

        if($3->type!="int"){
            yyerror("Array size must be of type int.");
        }

        $$ = n;
    }
    | LSQUARE constant_expression RSQUARE
    {
        dbg("square_opt -> [ constant_expression ]");
        Node* n = new Node();
        n->argCount = 1;
        n->code = $2->code;
        n->syn.push_back(to_string($2->argCount));

        if($2->type!="int"){
            yyerror("Array size must be of type int.");
        }
        $$ = n;
    }
    ;


// Done
static_opt
	: STATIC { 
        dbg("static_opt -> STATIC");
        $$ = strdup("static"); }
    |  { 
        dbg("static_opt -> <empty>");
        $$ = strdup(""); }
	;

// Done
type_specifier
	: VOID   { 
        dbg("type_specifier -> VOID");
        $$ = strdup("void"); lastDeclType = "void"; }
	| CHAR   { 
        dbg("type_specifier -> CHAR");
        $$ = strdup("char"); lastDeclType = "char"; }
	| INT    { 
        dbg("type_specifier -> INT");
        $$ = strdup("int"); lastDeclType = "int"; }
	| LONG   { 
        dbg("type_specifier -> LONG");
        $$ = strdup("long"); lastDeclType = "long"; }
	| DOUBLE { 
        dbg("type_specifier -> DOUBLE");
        $$ = strdup("double"); lastDeclType = "double"; }
	| BOOL   { 
        dbg("type_specifier -> BOOL");
        $$ = strdup("bool"); lastDeclType = "bool"; }
	/* | STRING { 
        dbg("type_specifier -> STRING");
        $$ = strdup("string"); lastDeclType = "string"; } */
	| TYPE_NAME 
    { 
        dbg("type_specifier -> TYPE_NAME");
        $$ = $1; 
        lastDeclType = string($1); 
        if(typeSize.find(lastDeclType) == typeSize.end()){
            yyerror("Unknown type '" + lastDeclType + "'.");    
        }
        else
        {
            dbg("User defined type found: " + lastDeclType);
        }
    }
	;

// Done
translation_unit
	: external_declaration { 
        dbg("translation_unit -> external_declaration");
        finalRoot = $1; $$ = $1; }
	| translation_unit external_declaration {
            dbg("translation_unit -> translation_unit external_declaration");
          Node* a = $1; Node* b = $2;
          if (a) { 
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; $$ = a; }
          else { finalRoot = b; $$ = b; }
      }
	;

// Done
struct_or_class_specifier
	: struct_or_class IDENTIFIER LCURLY 
    { 
        lastClassType = string($2); 
        if(typeSize.find(lastClassType) != typeSize.end()){
            yyerror("Redefinition of class/struct '" + lastClassType + "'.");
        }
        typeSize[lastClassType] = 0;
        dbg("named struct/class: " + lastClassType);
        classOffset = 0;
        pushScope();
    } 
    struct_or_class_member_list RCURLY 
    { 
        dbg("struct_or_class_specifier -> struct_or_class IDENTIFIER { struct_or_class_member_list }");
        popScope();
        $$ = $5; 
        typeSize[lastClassType] = classOffset;   // NEW: store computed size
      lastClassType.clear(); 
    }
    ;

// Done
struct_or_class
	: STRUCT 
    { 
        dbg("struct_or_class -> STRUCT");
        $$ = new Node(); 
        lastUsage = "public";
    }
	| CLASS 
    { 
        dbg("struct_or_class -> CLASS");
        $$ = new Node(); 
        lastUsage = "private";
    }
	;

// Done
struct_or_class_member_list
	:  
    { 
        dbg("struct_or_class_member_list -> <empty>");
        dbg("lastClassType: " + lastClassType);
        $$ = new Node(); 
    }
	| struct_or_class_member_list struct_or_class_member 
    { 
        dbg("struct_or_class_member_list -> struct_or_class_member_list struct_or_class_member");
        dbg("lastClassType: " + lastClassType);
        Node* n = $1; 
        n->code.insert(n->code.end(), $2->code.begin(), $2->code.end()); 
        $$ = n; 
    }
	;

struct_or_class_member
	: access_specifier_label 
    { 
        dbg("struct_or_class_member -> access_specifier_label");
        dbg("lastClassType: " + lastClassType);
        lastUsage = string($1->place);
        $$ = $1; 
    }
	| external_declaration 
    { 
        dbg("struct_or_class_member -> member_declaration");
        dbg("lastClassType: " + lastClassType);
        dbg("");
        $$ = $1; 
    }
	;

access_specifier_label
	: PUBLIC COLON 
    { 
        dbg("access_specifier_label -> PUBLIC :");
        dbg("lastClassType: " + lastClassType);
        Node* n=new Node(); 
        n->place = "public";
        $$ = n; 
    }
	| PRIVATE COLON 
    { 
        dbg("access_specifier_label -> PRIVATE :");
        Node* n=new Node(); 
        n->place = "private";
        $$ = n; 
    }
	| PROTECTED COLON 
    { 
        dbg("access_specifier_label -> PROTECTED :");
        Node* n=new Node(); 
        n->place = "protected";
        $$ = n; 
    }
	;

member_declaration
	: CONST return_type 
    {
        dbg("lastClassType: " + lastClassType);
        lastDeclType = string($1) + string($2);
        dbg("lastDeclType in member_declaration: " + lastDeclType);
    } 
    struct_declarator_list SEMICOLON 
    { 
        dbg("member_declaration -> const_opt return_type struct_declarator_list ;");
        dbg("lastClassType: " + lastClassType);
        $$ = $4; 
    }
    | return_type { lastDeclType = string($1); } members
    {
        dbg("member_declaration -> return_type members");
        $$ = $3;
    }
    /* {
        dbg("lastClassType: " + lastClassType);
        lastDeclType = string($2)+string($3);
        dbg("lastDeclType in member_declaration: " + lastDeclType);
    } struct_declarator_list SEMICOLON 
    { 
        dbg("member_declaration -> const_opt return_type struct_declarator_list ;");
        dbg("lastClassType: " + lastClassType);
        $$ = $5; 
    }
	| {dbg("2");} function_header compound_statement 
    { 
        dbg("member_declaration -> function_header compound_statement");
        Node* n = $2;
        n->code.push_back(lastClassType + "." + n->place + ":");
        n->code.insert(n->code.end(), $3->code.begin(), $3->code.end());
        $$ = n;
    } */
	/* | struct_or_class_specifier SEMICOLON { 
        dbg("member_declaration -> struct_or_class_specifier ;");
        Node* n=new Node(); $$ = n; } */
	;

members
    : struct_declarator_list SEMICOLON 
    { 
        dbg("members -> struct_declarator_list ;");
        $$ = $1; 
    }
    | IDENTIFIER LROUND RROUND 
    { 
        dbg("members -> IDENTIFIER ( ) compound_statement");
        string funcName = lastClassType + "." + string($1);
        
        if(funcTable.find(funcName) != funcTable.end()){
            yyerror("Redefinition of method '" + funcName + "'.");
        }
        currentFunction = funcName;
        pushScope();

        dbg("Defining method: " + funcName + " of return type: " + lastDeclType);
        classTable[lastClassType][string($1)].kind = "function";
        classTable[lastClassType][string($1)].type = lastDeclType;
        classTable[lastClassType][string($1)].place = funcName;

        if(string($1) == "void") funcTable[funcName].hasReturn = false;
        else funcTable[funcName].hasReturn = true;

        funcTable[funcName].returnType = lastDeclType;
        funcTable[funcName].paramCount = 0;
        
        if(lookupSymbol(funcName) == nullptr){
            declareSymbol(funcName, "function", "function", vector<string>(), true);
        }
    }
    compound_statement
    {
        dbg("members -> IDENTIFIER ( ) compound_statement");
        Node* n = new Node();
        n->place = string($1);
        string funcName = lastClassType + "." + string($1);

        n->type = lastDeclType;
        n->code.push_back(funcName + ":");
        n->argCount = 0;
        n->kind = "function";
        if($5)
            n->code.insert(n->code.end(), $5->code.begin(), $5->code.end());
        popScope();
        currentFunction = "global";
        $$ = n;
    }
    | IDENTIFIER LROUND parameter_list RROUND compound_statement 
    { 
        // dbg("members -> IDENTIFIER ( parameter_list ) compound_statement");
        // Node* n = $1;
        // n->code.push_back(lastClassType + "." + n->place + ":");
        // n->code.insert(n->code.end(), $2->code.begin(), $2->code.end());
        // $$ = n;
    } 
    /* | struct_or_class_specifier SEMICOLON { 
        dbg("members -> struct_or_class_specifier ;");
        Node* n=new Node(); $$ = n; }  */
    ;

struct_declarator_list
	: struct_declarator 
    { 
        dbg("struct_declarator_list -> struct_declarator");
        $$ = $1; 
    }
	| struct_declarator_list COMMA struct_declarator 
    { 
        dbg("struct_declarator_list -> struct_declarator_list , struct_declarator");
        Node* n = $1; 
        if ($3) n->code.insert(n->code.end(), $3->code.begin(), $3->code.end()); 
        $$ = n; 
    }
	;

struct_declarator
	: init_declarator 
    { 
        dbg("struct_declarator -> init_declarator");
        $$ = $1; 
    }
	;

// Done
const_opt
	: CONST { 
        dbg("const_opt -> CONST");
        $$ = strdup("const"); 
        }
    |  {
        dbg("const_opt -> <empty>");
        $$ = strdup(""); 
        }
	;

// Done
parameter_list
	: parameter_declaration { 
            dbg("parameter_list -> parameter_declaration");
            $$ = $1; 
        }
	| parameter_list COMMA parameter_declaration 
        {
            dbg("parameter_list -> parameter_list , parameter_declaration");
            Node* n = $1;
            n->syn.insert(n->syn.end(), $3->syn.begin(), $3->syn.end()); 
            $$ = n;
        }
	;

// Done
parameter_declaration
	: return_type IDENTIFIER 
        {
            dbg("parameter_declaration -> return_type IDENTIFIER");
            Node* n = new Node();
            n->syn.push_back(string($1)); 
            n->syn.push_back(string($2));
            $$ = n;
        }
	;

// Done
statement
	: labeled_statement { 
        dbg("statement -> labeled_statement");
        $$ = $1; }
	| compound_statement { 
        dbg("statement -> compound_statement");
        $$ = $1; }
	| expression_statement { 
        dbg("statement -> expression_statement");
        $$ = $1; }
	| selection_statement { 
        dbg("statement -> selection_statement");
        $$ = $1; }
	| iteration_statement { 
        dbg("statement -> iteration_statement");
        $$ = $1; }
	| jump_statement { 
        dbg("statement -> jump_statement");
        $$ = $1; }
	| io_statement { 
        dbg("statement -> io_statement");
        $$ = $1; }
    ;

// Done
io_statement
    : cout_expression SEMICOLON { 
        dbg("io_statement -> cout_expression ;");
        $$ = $1; }
    | cin_expression SEMICOLON  { 
        dbg("io_statement -> cin_expression ;");
        $$ = $1; }
    ;

// Done
cout_expression
    : COUT insertion_list { 
        dbg("cout_expression -> COUT insertion_list");
        $$ = $2; }
    ;

// Done
insertion_list
    : LEFT_SHIFT assignment_expression {
          dbg("insertion_list -> LEFT_SHIFT assignment_expression");
          Node* e = $2;
          Node* n = new Node();
          n->code = e->code;
          n->code.push_back("print " + e->place); 
          $$ = n;
      }
	| LEFT_SHIFT ENDL {
            dbg("insertion_list -> LEFT_SHIFT ENDL");
          Node* n = new Node();
          n->code.push_back("print newline"); 
          $$ = n;
      }
	| insertion_list LEFT_SHIFT ENDL {
            dbg("insertion_list -> insertion_list LEFT_SHIFT ENDL");
          Node* n = $1; 
          n->code.push_back("print newline"); 
          $$ = n;
      }
	| insertion_list LEFT_SHIFT assignment_expression {
            dbg("insertion_list -> insertion_list LEFT_SHIFT assignment_expression");
          Node* n = $1; Node* e = $3;
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("print " + e->place); $$ = n;
      }
	;

// Done
cin_expression
    : CIN extraction_list { 
        dbg("cin_expression -> CIN extraction_list");
        $$ = $2; }
    ;

// Done
extraction_list
    : RIGHT_SHIFT assignment_expression {
            dbg("extraction_list -> RIGHT_SHIFT assignment_expression");
          Node* e = $2; 
          Node* n = new Node();
          n->code = e->code; 
          n->code.push_back("read " + e->place); 
          $$ = n;
      }
    | extraction_list RIGHT_SHIFT assignment_expression {
            dbg("extraction_list -> extraction_list RIGHT_SHIFT assignment_expression");
          Node* n = $1; 
          Node* e = $3;
          n->code.insert(n->code.end(), e->code.begin(), e->code.end());
          n->code.push_back("read " + e->place); 
          $$ = n;
      }
    ;

// Done
labeled_statement
	: IDENTIFIER COLON {
            dbg("labeled_statement -> IDENTIFIER :");
            if(!declareSymbol(string($1),string("label"))){
                yyerror("Duplicate '" + string($1) + "' in same function.");
            }
            Node* s = new Node();
            string label = string($1);
            s->code.push_back(label + ":");
          $$ = s;
        }
	;

// Done
compound_statement
	: LCURLY RCURLY {
            dbg("compound_statement -> { }");
          Node* n = new Node();
          $$ = n;
      }
	| LCURLY { pushScope();} statement_list RCURLY {
            dbg("compound_statement -> { statement_list }");
          Node* n = $3;
          popScope();
          $$ = n;
      }
	;

// Done
statement_list
	: block_item { 
        dbg("statement_list -> block_item");
        $$ = $1; }
	| statement_list block_item {
            dbg("statement_list -> statement_list block_item");
          Node* n = $1;
          if ($2) n->code.insert(n->code.end(), $2->code.begin(), $2->code.end());
          $$ = n;
      }
	;

// Done
block_item
    : statement { 
        dbg("block_item -> statement");
        $$ = $1; }
    | declaration { 
        dbg("block_item -> declaration");
        $$ = $1; }
    ;
// Done
expression_statement
	: SEMICOLON { 
        dbg("expression_statement -> ;");
        Node* n = new Node(); $$ = n; }
	| expression SEMICOLON { 
        dbg("expression_statement -> expression ;");
        $$ = $1; }
    ;

selection_statement
	: IF LROUND expression RROUND statement %prec LOWER_THAN_ELSE {
          dbg("selection_statement -> if ( expression ) statement");
          string Ltrue = newLabel();
          string Lend  = newLabel();
          Node* e = $3;
          Node* s1 = $5;
          Node* n = new Node();
          n->code = e->code;
          n->code.push_back("if " + e->place + " goto " + Ltrue);
          n->code.push_back("goto " + Lend);
          n->code.push_back(Ltrue + ":");
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	| IF LROUND expression RROUND statement ELSE statement {
            dbg("selection_statement -> if ( expression ) statement else statement");

          string Ltrue = newLabel();
          string Lfalse = newLabel();
          string Lend  = newLabel();

          Node* e = $3;
          Node* s1 = $5;
          Node* s2 = $7;

          Node* n = new Node();
          n->code = e->code;
          n->code.push_back("if " + e->place + " goto " + Ltrue);
          n->code.push_back("goto " + Lfalse);

          n->code.push_back(Ltrue + ":");
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          n->code.push_back("goto " + Lend);
    
          n->code.push_back(Lfalse + ":");
          n->code.insert(n->code.end(), s2->code.begin(), s2->code.end());
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	| SWITCH LROUND expression RROUND switch_block
    ;

switch_block
    : LCURLY case_list RCURLY {
            dbg("switch_block -> { case_list }");
          Node* n = $2; $$ = n;
      }
    ;

case_list
    : case_list case_label statement_list
    | case_list default_label statement_list
    | case_label statement_list
    | default_label statement_list
    ;

case_label
    : CASE constant_expression COLON
    ;

default_label
    : DEFAULT COLON
    ;

iteration_statement
	: WHILE LROUND expression RROUND statement {
          dbg("iteration_statement -> WHILE ( expression ) statement");
          Node* cond = $3; Node* body = $5;
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back(Lbegin + ":");
          n->code.push_back("ifFalse " + cond->place + " goto " + Lend);
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.push_back("goto " + Lbegin);
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	| UNTIL LROUND expression RROUND statement {
            dbg("iteration_statement -> UNTIL ( expression ) statement");
          Node* cond = $3; Node* body = $5;
          Node* n = new Node();
          string Lbegin = newLabel();
          n->code.push_back(Lbegin + ":");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back("ifTrue " + cond->place + " goto " + Lbegin);
          $$ = n;
      }
	| DO statement WHILE LROUND expression RROUND SEMICOLON {
            dbg("iteration_statement -> DO statement WHILE ( expression ) ;");
          Node* body = $2; Node* cond = $5;
          Node* n = new Node();
          string Lbegin = newLabel();
          n->code.push_back(Lbegin + ":");
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
          n->code.push_back("ifTrue " + cond->place + " goto " + Lbegin);
          $$ = n;
      }
	| FOR LROUND for_init_statement expression_statement RROUND statement {
            dbg("iteration_statement -> FOR ( for_init_statement expression_statement ) statement");
          Node* init = $3; Node* cond = $4; Node* body = $6;
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
          n->code.push_back(Lbegin + ":");
          if (cond) {
              n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
              n->code.push_back("ifFalse " + cond->place + " goto " + Lend);
          }
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          n->code.push_back("goto " + Lbegin);
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	| FOR LROUND for_init_statement expression_statement expression RROUND statement {
            dbg("iteration_statement -> FOR ( for_init_statement expression_statement expression ) statement");
          Node* init = $3; Node* cond = $4; Node* iter = $5; Node* body = $7;
          Node* n = new Node();
          string Lbegin = newLabel(), Lend = newLabel();
          if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
          n->code.push_back(Lbegin + ":");
          if (cond) {
              n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
              n->code.push_back("ifFalse " + cond->place + " goto " + Lend);
          }
          n->code.insert(n->code.end(), body->code.begin(), body->code.end());
          if (iter) n->code.insert(n->code.end(), iter->code.begin(), iter->code.end());
          n->code.push_back("goto " + Lbegin);
          n->code.push_back(Lend + ":");
          $$ = n;
      }
	;
    
for_init_statement
	: expression_statement { 
        dbg("for_init_statement -> expression_statement");
        $$ = $1; }
	| declaration 
    { 
        dbg("for_init_statement -> declaration");
        $$ = $1; }
    ;

// Done
jump_statement
	: GOTO IDENTIFIER SEMICOLON {
            dbg("jump_statement -> GOTO IDENTIFIER ;");
          Node* n = new Node();
          n->code.push_back("goto " + string($2));
          $$ = n;
      }
	| CONTINUE SEMICOLON {
            dbg("jump_statement -> CONTINUE ;");
          Node* n = new Node(); 
          n->code.push_back("continue;"); 
          $$ = n;
      }
	| BREAK SEMICOLON {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); 
          n->code.push_back("break;"); 
          $$ = n;
      }
	| RETURN SEMICOLON {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); 
          n->code.push_back("return;"); 
          $$ = n;
      }
	| RETURN expression SEMICOLON 
    {
        dbg("jump_statement -> RETURN expression ;");
        Node* expr = $2;
        if(expr == nullptr)
            yyerror("Return statement must return a value.");
        dbg("Return type: " + expr->type + ", Expected type: " + funcTable[currentFunction].returnType);

        dbg("");
        dbg("lastDeclType: " + lastDeclType);
        dbg("currentFunction: " + currentFunction);
        dbg("");
        if(expr->type != funcTable[currentFunction].returnType){
            yyerror("Return type mismatch in function '" + currentFunction + "'.");
        }
        dbg("Function '" + currentFunction + "' has return statement returning '" + expr->place + "'.");
        Node* n = new Node();
        n->code = expr->code;
        n->code.push_back("return " + expr->place);
        $$ = n;
    }
    ;

// Done
external_declaration
	: type_specifier
    {
        dbg("external_declaration -> type_specifier");
        lastDeclType = string($1);
        lastFnType = lastDeclType;
    } 
    external 
    { 
        dbg("external_declaration -> type_specifier external");
        $$ = $3; 
    }
    | type_specifier pointer_list
    {
        dbg("external_declaration -> type_specifier pointer_list");
        lastDeclType = string($1)+string($2);
        lastFnType = lastDeclType;
        dbg("");
        dbg("lastDeclType in external_declaration: " + lastDeclType);
        dbg("");
    } 
    external 
    { 
        dbg("external_declaration -> type_specifier pointer_list external");
        $$ = $4; 
    }  
    | STATIC type_specifier 
    {
        dbg("declaration_specifiers -> static type_specifier");
        lastDeclType = string($1)+string($2);
    }
    init_declarator_list SEMICOLON 
    {
        dbg("declaration_specifiers -> static type_specifier init_declarator_list ;");
        $$ = $4;
    }
    | CONST type_specifier 
    {
        dbg("declaration_specifiers -> const type_specifier");
        lastDeclType = string($1)+string($2);
    } 
    init_declarator_list SEMICOLON
    {
        dbg("declaration_specifiers -> const type_specifier init_declarator_list ;");
        $$ = $4;
    }
    | STATIC CONST type_specifier 
    {
        dbg("declaration_specifiers -> static const type_specifier");
        lastDeclType = string($1)+string($2)+string($3);
    }
    init_declarator_list SEMICOLON
    {
        dbg("declaration_specifiers -> static const type_specifier init_declarator_list ;");
        $$ = $5;
    }
	| struct_or_class_specifier SEMICOLON 
    { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        $$ = $1; 
    }
    | TYPEDEF return_type IDENTIFIER SEMICOLON {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string($3)] = typeSize[string($2)];
        $$ = new Node();
    }  
    ;

external 
    : IDENTIFIER LROUND RROUND 
    {
        dbg("");
        dbg("lastFnType in external: " + lastFnType);
        dbg("");
        dbg("external -> IDENTIFIER ( )");
        string fname = string($1);

        if(lastClassType == "")
        {
            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            
            if(funcTable.find(fname) != funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string(lastFnType) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;

            funcTable[fname].returnType = string(lastFnType);
            funcTable[fname].paramCount = 0;
            dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");
        }// dbg("Function '" + fname + "' with " + to_string(funcTable[fname].paramCount) + " parameters declared.");
        else
        {
            fname = lastClassType + "." + fname;

            if(classTable[lastClassType].find(string($1)) != classTable[lastClassType].end())
                yyerror("Method redeclaration: " + fname);
            classTable[lastClassType][string($1)].kind = "function";
            classTable[lastClassType][string($1)].type = lastFnType;
            classTable[lastClassType][string($1)].place = string($1);
            funcInfo f;
            f.place = string($1);
            f.returnType = lastFnType;
            f.paramCount = 0;
            if(string(lastFnType) == "void") f.hasReturn = false;
            else f.hasReturn = true;
            classTable[lastClassType][string($1)].method = f;
        }
        currentFunction = fname;
        localTemp = 0; localLabel = 0;

        pushScope();
    }
    compound_statement
    {
        dbg("external -> IDENTIFIER ( ) compound_statement");
        Node* n = new Node();
        n->place = string($1);
        n->type = lastFnType;
        n->argCount = 0;
        n->kind = "function";
        string fname = string($1);
        if(lastClassType != "")
            fname = lastClassType + "." + fname;
        n->code.push_back(fname + ":");
        if($5) n->code.insert(n->code.end(),$5->code.begin(),$5->code.end());
        popScope();
        currentFunction = "global";
        lastFnType="int";
        $$ = n;
    }
    | IDENTIFIER LROUND parameter_list RROUND 
    {
        dbg("");
        dbg("lastDeclType in external: " + lastFnType);
        dbg("");
        dbg("external -> IDENTIFIER ( parameter_list )");
        string fname = string($1);
        
        for (int i=0;i<$3->syn.size();i+=2)
        {
            fname += "_" + $3->syn[i];
        }
        if(lastClassType == "")
        {
            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            if(funcTable.find(fname) != funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string(lastFnType) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;

            funcTable[fname].returnType = string(lastFnType); 
            funcTable[fname].paramCount = $3->syn.size()/2;
            dbg("");
            dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");

            for (int i=0;i<$3->syn.size();i+=2){
                funcTable[fname].paramTypes.push_back($3->syn[i]);
                dbg("Parameter: " + $3->syn[i+1] + " of type " + $3->syn[i]);
            }
            dbg("");
        }
        else
        {
            string methodName = fname;
            if(classTable[lastClassType].find(methodName) != classTable[lastClassType].end())
                yyerror("Method redeclaration: " + lastClassType + "." + methodName);
            classTable[lastClassType][methodName].kind = "function";
            classTable[lastClassType][methodName].type = lastFnType;
            classTable[lastClassType][methodName].place = methodName;

            funcInfo f;
            f.place = methodName;
            f.returnType = lastFnType;
            f.paramCount = $3->syn.size()/2;
            if(string(lastFnType) == "void") f.hasReturn = false;
            else f.hasReturn = true;

            for (int i=0;i<$3->syn.size();i+=2)
            {
                f.paramTypes.push_back($3->syn[i]);
                dbg("Parameter: " + $3->syn[i+1] + " of type " + $3->syn[i]);
            }
            classTable[lastClassType][methodName].method = f;
        }
        currentFunction = fname;
        localTemp = 0; localLabel = 0;
        pushScope();

        for(int i=1;i<$3->syn.size();i+=2)
        {
            string pname = $3->syn[i];
            string ptype = $3->syn[i-1];
            bool ok = declareSymbol(pname,ptype);
            if(!ok) yyerror("Duplicate parameter name '" + pname + "' in function '" + fname + "'.");
        }
    }
    compound_statement
    {
        dbg("external -> IDENTIFIER ( parameter_list ) compound_statement");
        Node* n = new Node();
        string fname = string($1);
        for (int i=0;i<$3->syn.size();i+=2)
        {
            fname += "_" + $3->syn[i];
        }

        n->place = fname;
        n->type = lastFnType;

        n->argCount = $3->syn.size()/2;
        n->kind = "function";
        popScope(); 

        if(lastClassType != "")
            fname = lastClassType + "." + string($1);
        n->code.push_back(fname + ":");

        if($6) n->code.insert(n->code.end(),$6->code.begin(),$6->code.end());
        finalRoot = n;
        currentFunction = "global";

        lastFnType="int";
        $$ = n;
    }
    | init_declarator_list SEMICOLON 
    { 
        dbg("external -> init_declarator_list ;");
        $$ = $1; 
    }

// Done
function_header
	: return_type IDENTIFIER LROUND RROUND 
        {
            dbg("function_header -> return_type IDENTIFIER ( )");
            string fname = string($2);

            if(funcTable.find(fname)!=funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string($1) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;

            funcTable[fname].returnType = string($1);
            funcTable[fname].paramCount = 0;
            // dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");
            // dbg("Function '" + fname + "' with " + to_string(funcTable[fname].paramCount) + " parameters declared.");
            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            currentFunction = fname;
            localTemp = 0; localLabel = 0;
            Node* n = new Node();
            n->code.push_back(fname + ":");

            pushScope(); 
            $$ = n;
        }

    | return_type IDENTIFIER LROUND parameter_list RROUND 
        {
            dbg("function_definition -> return_type IDENTIFIER ( parameter_list ) compound_statement");
            string fname = string($2);

            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            for (int i=0;i<$4->syn.size();i+=2)
            {
                fname += "_" + $4->syn[i];
            }

            if(funcTable.find(fname) != funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string($1) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;
                       
            funcTable[fname].returnType = string($1); 
            funcTable[fname].paramCount = $4->syn.size()/2;
            dbg("");
            dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");

            for (int i=0;i<$4->syn.size();i+=2){
                funcTable[fname].paramTypes.push_back($4->syn[i]);
                dbg("Parameter: " + $4->syn[i+1] + " of type " + $4->syn[i]);
            }
            dbg("");
            
            currentFunction = fname;
            localTemp = 0; localLabel = 0;
            Node* n = new Node();            
            n->code.push_back(fname + ":");
            pushScope(); 

            for(int i=1;i<$4->syn.size();i+=2){
                string pname = $4->syn[i];
                string ptype = $4->syn[i-1];
                bool ok = declareSymbol(pname,ptype);
                if(!ok) yyerror("Duplicate parameter name '" + pname + "' in function '" + fname + "'.");
            }
            $$ = n;
        }
	;

// Done
function_definition
    : function_header compound_statement
    {
        dbg("function_definition -> function_header compound_statement");
        Node* n = $1;
        if($2) n->code.insert(n->code.end(),$2->code.begin(),$2->code.end()); 
        popScope(); 
        finalRoot = n;
        currentFunction = "global";
        $$ = n;
    }
    ;

// Done
return_type
    : type_specifier pointer_opt 
    { 
        dbg("return_type -> type_specifier pointer_opt");
        $$ = strdup( (string($1) + string($2)).c_str() );
    }
    ;

%%


#include <cstdio>
#include "parser.tab.h"
extern int yydebug;
void yyerror(const char *s);

int main(int argc, char** argv){
    yydebug = 0;
    pushScope();
    if(yyparse()) cerr << "Parsing failed.\n";
    else cerr << "Parsing completed successfully.\n"; 

    if(!errors.empty()){
        cout<<"---- Errors found ----\n";
        for(auto &e:errors) cout<<e<<"\n";
        return 1;
    }

    if(finalRoot){
        for(int i=0;i<finalRoot->code.size();i++) {
            cout<<"["<<(i+1)<<"] "<<finalRoot->code[i]<<"\n";
        }
    }

    return 0;
}
