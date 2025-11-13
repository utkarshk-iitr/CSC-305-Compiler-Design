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
        string printName;
        vector<string> syn;
        string place;
        string type;
        string kind;
        int argCount = 0;
        Node() : place(""), type("") , kind("") {}
        Node(string p, string t, string k) : place(p), type(t), kind(k) {}
    };

    struct Symbol {
        string printName;
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
        string printName;
        string place;
        string original;
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
    unordered_map<string,string> typeDefTable;

    unordered_map<string,int> typeSize = {
        {"int", 4}, {"char", 1}, {"bool", 1}, {"double", 8}, {"long", 8}, {"nullptr", 8}
    };
    
    vector<string> errors;
    static string currentFunction = "";
    static int globalTemp = 0, globalLabel = 0;
    static int localTemp = 0, localLabel = 0;
    static int classOffset = 0;
    static int functionOffset = 0;
    static string lastDeclType = "int";
    static string lastClassType = "";
    static string lastUsage = "";
    static string lastFnType = "int";
    static string currentScope = "";
    static string switchType = "";
    static string switchVar = "";
    static bool inloop = false;
    static bool inFunction = false;
    static bool funcOnce = false;

    vector<string> globalCode;
    vector<int> offset;

    Node* finalRoot = nullptr;


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

    memberInfo* lookupClassMember(const string& c,const string& m){
        auto it = classTable.find(c);
        if(it!=classTable.end()){
            auto y = it->second.find(m);
            if(y!=it->second.end()){
                return &(y->second);
            }
            return nullptr;
        }
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

    string newTemp(string type="int") {
        if(type.back()=='*'){
            type = "nullptr";
        }
        if (currentFunction == "") {
            string s = "global.t" + to_string(++globalTemp);
            declareSymbol(s, type, "temp");
            auto sym = lookupSymbol(s);
            if(lastClassType != "" && currentFunction == "")
            {
                string w = "[this + " + to_string(classOffset) + "]";
                classOffset += typeSize[type];
                classTable[lastClassType][s].offset = classOffset;
                classTable[lastClassType][s].type = type;
                classTable[lastClassType][s].kind = "temp";
                sym->printName = w;
                sym->name = w;
            }
            else
            {
                functionOffset += typeSize[type];
                int p = functionOffset;
                for(int i = 0; i < offset.size(); i++)
                    p += offset[i];
                string w = "[ebp - " + to_string(p) + "]";
                sym->printName = w;
                sym->name = w;
            }
            return sym->printName;
        } else {
            string s = "global.t" + to_string(++globalTemp);
            declareSymbol(s, type, "temp");
            auto sym = lookupSymbol(s);
            functionOffset += typeSize[type];
            int p = functionOffset;
            for(int i = 0; i < offset.size(); i++)
                p += offset[i];
            string w = "[ebp - " + to_string(p) + "]";
            sym->printName = w;
            sym->name = w;
            return w;
        }
    }

    string newLabel() {
        if (currentFunction == "") {
            return "global.L" + to_string(++globalLabel);
        } else {
            return currentFunction + ".L" + to_string(++localLabel);
        }
    }
    extern int yylineno;
    void yyerror(string s) {
        errors.push_back(string("Error at line ") + to_string(yylineno) + " : " + s);
    }

    vector<int> makeList(int index) {
        vector<int> list;
        list.push_back(index);
        return list;
    }

    void backpatch(vector<string>& code, vector<int> list, string label) {
        for(int i : list) {
            // Replace the placeholder with the actual label
            size_t pos = code[i].find("__");
            if(pos != string::npos) {
                code[i].replace(pos, 2, label);
            }
        }
    }

    vector<int> merge(vector<int> list1, vector<int> list2) {
        vector<int> result = list1;
        result.insert(result.end(), list2.begin(), list2.end());
        return result;
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
        if(from.back()=='*' && to=="bool") return true;
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
%token<str> LEFT_SHIFT RIGHT_SHIFT
%token<str> LOGICAL_NOT LOGICAL_AND LOGICAL_OR
%token<str> PLUS_EQUAL MINUS_EQUAL STAR_EQUAL DIV_EQUAL MOD_EQUAL
%token<str> AND_EQUAL OR_EQUAL XOR_EQUAL
%token<str> LEFT_SHIFT_EQ RIGHT_SHIFT_EQ

%token<str> LROUND RROUND LCURLY RCURLY LSQUARE RSQUARE
%token<str> SEMICOLON COLON COMMA DOT QUESTION_MARK 

%token<str> IF ELSE SWITCH CASE DEFAULT WHILE DO FOR GOTO CONTINUE BREAK RETURN UNTIL

%token<str> VOID INT DOUBLE CHAR BOOL LONG
%token<str> TRUE FALSE NULLPTR TILDE
%token<str> STATIC CONST SIZEOF STRING_LITERAL
%token<str> CLASS STRUCT PUBLIC PRIVATE PROTECTED

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
%type<node> parameter_list for_start
%type<node> parameter_declaration
%type<node> initializer initializer_list statement compound_statement statement_list labeled_statement
%type<node> selection_statement iteration_statement jump_statement external_declaration 
%type<node> function_definition primary_expression 
/* %type<node> trailing_return_opt lambda_capture_clause capture_list lambda_expression lambda_declarator lambda_parameter_clause */
%type<node> postfix_expression argument_expression_list unary_expression cast_expression
%type<node> multiplicative_expression additive_expression shift_expression relational_expression
%type<node> equality_expression and_expression exclusive_or_expression inclusive_or_expression
%type<node> logical_and_expression logical_or_expression conditional_expression block_item
%type<node> assignment_expression expression constant_expression declaration init_declarator
%type<node> init_declarator_list constant 
%type<node> function_header
%type<node> expression_statement translation_unit for_init_statement;
%type<str> type_specifier assignment_operator unary_operator return_type pointer_opt pointer_list static_opt const_opt
%type<str> cast_type cast_type_specifier
%type<str> declaration_specifiers
%type<node> square_list members external declare 
%type<node> switch_head case_list case_item external_declare

%start translation_unit

%%

// Done
primary_expression
	: IDENTIFIER 
    {
        dbg("primary_expression -> IDENTIFIER");
        Node* n = new Node();
        string name = string($1);
        dbg(name);
        Symbol* sym = lookupSymbol(name);
        dbg("");
        dbg("Looking up symbol: " + name);
        dbg("");
        if (!sym) {
            if(name=="printf" || name=="scanf" || name=="malloc" || name=="free"){
                n->place = name;
                n->printName = name;
            }
            else{
                dbg("Symbol not found: " + name);
                yyerror("Use of undeclared identifier '" + name + "'.");
            }
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
            n->place = sym->name;
            n->printName = sym->printName;
            // if(sym->printName.find("this")!=string::npos)
            // {
            //     string temp = newTemp(n->type + string("*"));
            //     n->code.push_back(temp + " = &" + sym->printName);
            // }
            dbg(n->printName + " " + sym->printName);
        }
        // dbg("n->place is " + n->place + ", n->name is " + name);
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
    | STRING_LITERAL        
    {
        dbg("constant -> STRING_LITERAL");
        $$ = new Node(string($1), "char*", "rvalue");
    }
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
        n->kind = "rvalue";
        n->printName = string($1);
        $$ = n;
    }
    | CHARACTER_LITERAL     
    {
        dbg("constant -> CHARACTER_LITERAL");
        Node* n = new Node(string($1), "char", "const");
        dbg("");
        dbg("Character constant value: " + string(1, $1[1]));
        dbg("");
        n->printName = string(1, $1[1]);
        n->kind = "rvalue";
        $$ = n;
    }
    | EXPONENT_LITERAL      
    {
        dbg("constant -> EXPONENT_LITERAL");
        Node* n = new Node(string($1), "double", "const");
        n->kind = "rvalue";
        n->printName = string($1);
        $$ = n;
    }
    | DOUBLE_LITERAL       
    {
        dbg("constant -> DOUBLE_LITERAL");
        Node* n = new Node(string($1), "double", "const");
        n->kind = "rvalue";
        n->printName = string($1);
        $$ = n;
    }
    | NULLPTR               
    {
        dbg("constant -> NULLPTR");
        Node* n = new Node("0", "void*", "const");
        n->kind = "rvalue";
        n->printName = "nullptr";
        $$ = n;
    }
    | TRUE                  
    {
        dbg("constant -> TRUE");
        Node* n = new Node("1", "bool", "const");
        n->kind = "rvalue";
        n->printName = "true";
        $$ = n;
    }
    | FALSE                 
    {
        dbg("constant -> FALSE");
        Node* n = new Node("0", "bool", "const");
        n->kind = "rvalue";
        n->printName = "false";
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
        else
        {
            if(base->type.back()!='*'){
                yyerror("Subscripted value is not an array or pointer.");
            }
            if(idx->type!="int"){
                yyerror("Index is not an integer.");
            }
            if(base->kind.find("const")!=string::npos){
                yyerror("Cannot modify a const value.");
            }
            
            n->code = base->code;
            n->code.insert(n->code.end(), idx->code.begin(), idx->code.end());
            
            string type = base->type.substr(0, base->type.size()-base->syn.size());
            string offset = newTemp(type);
            
            // Handle array parameters (which don't have dimension info in syn)
            if(base->syn.empty()){
                type = type.substr(0,type.size()-1);
                // For arrays passed as parameters, just do simple pointer arithmetic
                n->code.push_back(offset + " = " + idx->printName + " * " + to_string(typeSize[type]));
                n->place = newTemp(type);
                n->printName = n->place;
                n->code.push_back(n->place + " = " + base->printName + " + " + offset);
                n->type = type;
                n->kind = base->kind;
                n->place = "*" + n->place;
                n->printName = "*" + n->printName;
            }
            // Handle regular arrays with dimension information
            else {
                int p = 1;
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
                n->code.push_back(offset + " = " + idx->printName + " * " + to_string(p));
                n->code.push_back(offset + " = " + offset +" * "+to_string(typeSize[type]));
                n->type = base->type.substr(0,base->type.size()-1);
                n->place = newTemp(n->type);
                n->printName = n->place;
                n->code.push_back(n->place + " = " + base->printName + " + " + offset);
                n->kind = base->kind;
                n->syn = vector<string>(base->syn.begin()+1, base->syn.end());
                
                if(n->syn.empty()){
                    n->place = "*" + n->place;
                    n->printName = "*" + n->printName;
                }
            }
        }   
        $$ = n;
    }
	| postfix_expression LROUND RROUND 
    {
        dbg("postfix_expression -> postfix_expression ( )");
        Node* fun = $1;
        dbg("2123");
        dbg(fun->place);

        string funcName = fun->place;
        
        funcInfo* s = lookupFunction(funcName);
        check_func_access(s);
        Node* n = new Node();
        if(!s){
            yyerror("Call to non-function '" + funcName + "'.");
        }
        if(s)
        {
            if(s->paramCount != 0){
                yyerror("Call to function '" + funcName + "' with incorrect number of arguments.");
            }

            n->code = fun->code;
            n->type = s->returnType;
            string pname = funcTable[funcName].printName;
            int i = 0;
            while(i<pname.size() && pname[i] != '.') i++;
            bool flg = false;
            dbg(to_string(i));
            if(i<pname.size()){
                flg = true;
                pname = funcName;
                i = 0;
                while(i<pname.size() && pname[i] != '.') i++;
                pname = pname.substr(0,i);
                dbg("pname is: " + pname);
                Symbol* sybl = lookupSymbol(pname);
                // if(sybl){
                //     string w = newTemp(n->type);
                //     n->code.push_back(w + " = &" + sybl->printName);
                //     n->code.push_back("param " + w);
                // }
            }

            if(fun->type=="void"){
                if(flg)
                    n->code.push_back("call " + funcTable[funcName].printName + ", 1;");
                else
                    n->code.push_back("call " + funcTable[funcName].printName + ", 0;");
            }
            else{
                n->place = newTemp(n->type);
                if(flg)
                    n->code.push_back(n->place + " = call " + funcTable[funcName].printName + ", 1;");
                else
                    n->code.push_back(n->place + " = call " + funcTable[funcName].printName + ", 0;");
            }
        }
        n->kind = "rvalue";
        $$ = n;
    }
	| postfix_expression LROUND argument_expression_list RROUND 
    {
        dbg("postfix_expression -> postfix_expression ( argument_expression_list )");
        Node* fun = $1;
        dbg("133");
        dbg(fun->place);
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
        check_func_access(s);
        Node* n = new Node();
        if(!s)
        {
            if(original!="printf" && original!="scanf" && original!="malloc" && original!="free")
                yyerror("Function '" + original + "' with given argument types not found.");
            else{
                n->code = fun->code;
                n->type = "int";
                n->code.insert(n->code.end(), args->code.begin(), args->code.end());
                n->argCount = args->argCount;
                if(original=="malloc"){
                    if(args->argCount!=1 || args->syn[0]!="int"){
                        yyerror("malloc expects a single integer argument.");
                    }
                    n->place = newTemp(n->type);
                    n->code.push_back(n->place + " = call malloc, " + to_string(args->argCount));
                    n->type = "void*";
                }
                else if(original=="free"){
                    if(args->argCount!=1 || args->syn[0].back()!='*'){
                        yyerror("free expects a single pointer argument.");
                    }
                    n->code.push_back("call free, " + to_string(args->argCount));
                    n->type = "void";
                }
                else{
                    n->place = newTemp(s->returnType);
                    n->code.push_back(n->place + " = call " + original + ", " + to_string(args->argCount));
                }
            }
        }
        else
        {
            if (s->paramCount != args->argCount) {
                yyerror("Call to function '" + original + "' with incorrect number of arguments.");
            }
            for(int i=0; i<args->argCount; i++){
                if(s->paramTypes[i]!=args->syn[i]){
                    yyerror("Type mismatch in argument " + to_string(i+1) + " of function '" + original + "'.");
                }
            }
            dbg(funcTable[name].printName);
            n->code = fun->code;
            n->type = s->returnType;
            string pname = funcTable[name].printName;
            int i = 0;
            while(i<pname.size() && pname[i] != '.') i++;
            bool flg = false;
            dbg(to_string(i));
            if(i<pname.size()){
                flg = true;
                pname = name;
                i = 0;
                while(i<pname.size() && pname[i] != '.') i++;
                pname = pname.substr(0,i);
                dbg("pname is: " + pname);
                Symbol* sybl = lookupSymbol(pname);
                if(sybl){
                    // string w = newTemp(n->type);
                    n->code.push_back("lea ecx , " + sybl->printName);
                }
            }
            n->code.insert(n->code.end(), args->code.begin(), args->code.end());
            
            if(s->returnType=="void") {
                n->type = "";
                if(flg)
                    n->code.push_back("call " + funcTable[name].printName + ", " + to_string(args->argCount + 1));
                else
                    n->code.push_back("call " + funcTable[name].printName + ", " + to_string(args->argCount));
            }
            else{
                dbg(to_string(functionOffset) + " poi");
                n->place = newTemp(s->returnType);
                dbg(to_string(functionOffset) + " poi");
                n->kind = "rvalue";
                dbg("mnb");
                dbg(funcTable[name].printName);
                if(flg)
                    n->code.push_back(n->place + " = call " + funcTable[name].printName + ", " + to_string(args->argCount + 1));
                else
                    n->code.push_back(n->place + " = call " + funcTable[name].printName + ", " + to_string(args->argCount));
            }
        }
        int argsum = 0;
        for(int i=0;i<args->argCount;i++){
            argsum += typeSize[args->syn[i]];
        }
        n->code.push_back("add esp, " + to_string(argsum));
        // functionOffset -= argsum;
        n->kind = "rvalue";
        n->printName = n->place;
        $$ = n;
    }
	| postfix_expression DOT IDENTIFIER {
        dbg("postfix_expression -> postfix_expression . IDENTIFIER");
        Node* obj = $1;
        Node* n = new Node();
        if(obj)
        {
            string currentType = obj->type;
            dbg("currentname is " + obj->printName);
            if(classTable.find(currentType) == classTable.end()){
                yyerror("Dot operator can not be applied here.");
            }

            // int idx=0;
            // for(int i=0;i<obj->place.size();i++){
            //     if(obj->place[i]=='$') idx = i;
            // }
            // obj->place.erase(0,idx+1);

            string stars = "";
            int i=0;
            dbg("currentType is " + currentType);
            while(i<obj->printName.size() && obj->printName[i]=='*'){
                stars += '*';
                i++;
            }
            string nm = stars + obj->place + "." + string($3);

            dbg("2ss12121");
            dbg(nm);
            dbg("");
            Symbol* s = lookupSymbol(nm);
            funcInfo* f = lookupFunction(nm);
            memberInfo* m = lookupClassMember(currentType,string($3));

            if(!s)
                dbg("YES");

            if(s) 
            {
                if(s->isFunction)
                {
                    dbg("function");
                    n->place = nm;
                }
                else
                {
                    check_access(s);
                    n->printName = s->printName;
                    n->place = s->name;
                    n->type = s->type;
                    n->kind = s->kind;
                }
            }

            // else if(m){
            //     n->type = m->type;
            //     n->kind = m->kind;
            //     n->place = nm;
            //     n->printName = m->printName;
            // }
            else{
                yyerror("No member or function named '" + nm+"'.");
            }

            n->code = obj->code;
            dbg("1");
        }// n->code.push_back(n->place + " = " + nm);
        $$ = n;
    }
	/* | postfix_expression ARROW IDENTIFIER {
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
            // n->code.push_back(n->place + " = " + tmp + "." + string($3));
            $$ = n;
      } */
	| postfix_expression INCREMENT 
    {
        dbg("postfix_expression -> postfix_expression ++");
        Node* v = $1;
        if(v->kind.find("rvalue")!=string::npos){
            yyerror("Cannot apply increment to rvalue.");
        }
        if(!check_unary_comp(v->type,"++")){
            yyerror("Invalid type '" + v->type + "' for increment.");
        }
        if(v->kind.find("const")!=string::npos){
            yyerror("Cannot modify a const value.");
        }
        Node* n = new Node();
        n->code = v->code;
        string old = newTemp(v->type);
        n->code.push_back(old + " = " + v->printName);          // load old value from address
        n->code.push_back(v->printName + " = " + old + " + 1;");      // store back incremented value
        n->place = old;
        n->type = v->type;
        n->kind = "rvalue";
        $$ = n;
    }
	| postfix_expression DECREMENT 
    { 
        dbg("postfix_expression -> postfix_expression --");
        Node* v = $1;

        if(v->kind.find("rvalue")!=string::npos){
            yyerror("Cannot apply decrement to rvalue.");
        }
        if(!check_unary_comp(v->type,"--")){
            yyerror("Invalid type '" + v->type + "' for decrement.");
        }
        if(v->kind.find("const")!=string::npos){
            yyerror("Cannot modify a const value.");
        }
        Node* n = new Node();
        n->code = v->code;
        string old = newTemp(v->type);
        n->code.push_back(old + " = " + v->printName);          // load old value from address
        n->code.push_back(v->printName + " = " + old + " - 1;");      // store back incremented value
        n->place = old;
        n->type = v->type;
        n->kind = "rvalue";
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
        if(e->kind == "rvalue"){
            // functionOffset += typeSize[e->type];
            n->code.push_back("sub esp, " + to_string(typeSize[e->type]));
            n->code.push_back("param esp , " + e->place);
        }
        else{
            // functionOffset += typeSize[e->type];
            n->code.push_back("sub esp, " + to_string(typeSize[e->type]));
            n->code.push_back("param esp , " + e->printName);
        }
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
        if(e->kind == "rvalue"){
            // functionOffset += typeSize[e->type];
            n->code.push_back("sub esp, " + to_string(typeSize[e->type]));
            n->code.push_back("param esp , " + e->place);
        }
        else{
            // functionOffset += typeSize[e->type];
            n->code.push_back("sub esp, " + to_string(typeSize[e->type]));
            n->code.push_back("param esp , " + e->printName);
        }
        dbg("argcount is " + to_string(n->argCount) + ", type is " + e->type);
        dbg(e->place+"-"+e->printName);
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
          if(v->kind.find("rvalue")!=string::npos){
              yyerror("Cannot apply increment to rvalue.");
          }
          if(!check_unary_comp(v->type,"++")){
              yyerror("Invalid type '" + v->type + "' for increment.");
          }
          if(v->kind.find("const")!=string::npos){
              yyerror("Cannot modify a const value.");
          }
          Node* n = new Node();
          n->code = v->code;
          n->place = v->place;
          n->code.push_back(v->printName + " = " + v->printName + " + 1;");
          $$ = n;
      }
	| DECREMENT unary_expression 
    {
        dbg("unary_expression -> -- unary_expression");
        Node* v = $2;
        if(v->kind.find("rvalue")!=string::npos){
            yyerror("Cannot apply decrement to rvalue.");
        }
        if(!check_unary_comp(v->type,"--")){
            yyerror("Invalid type '" + v->type + "' for decrement.");
        }
        if(v->kind.find("const")!=string::npos){
            yyerror("Cannot modify a const value.");
        }
        Node* n = new Node();
        n->code = v->code;
        n->place = v->place;
        n->code.push_back(v->printName + " = " + v->printName + " - 1;");
        $$ = n;
    }
	| unary_operator cast_expression 
    {
        dbg("unary_expression -> unary_operator cast_expression");
        Node* rhs = $2;
        Node* n = new Node();
        n->code = rhs->code;
        string op = string($1);
        if(!check_unary_comp(rhs->type,op)){
            yyerror("Invalid operation '" + op + "' on type '" + rhs->type + "'.");
        }
        if (op == "&") {
            if(rhs->kind.find("rvalue")!=string::npos){
                  yyerror("Cannot take address of rvalue.");
              }
            n->place = newTemp("nullptr");
            n->code.push_back(n->place + " = &" + rhs->printName);
            n->type = rhs->type + "*";
            n->kind = "rvalue";
            n->printName = n->place;
        } else if (op == "*") 
        {
            n = $2;
            if(n->kind.find("rvalue")!=string::npos){
                yyerror("Cannot dereference a rvalue.");
            }
            n->type = rhs->type.substr(0, rhs->type.size() - 1);
            n->place = rhs->place;
            n->printName = "*" + rhs->printName;
        } else if (op == "+") {
            n->place = rhs->place;
            n->type = rhs->type;
            n->kind = "rvalue";
        } else if (op == "-") {
            n->place = newTemp(rhs->type);
            dbg(rhs->place+"---"+rhs->printName);
            n->code.push_back(n->place + " = 0 - " + rhs->printName);
            n->type = rhs->type;
            n->printName = n->place;
            n->kind = "rvalue";
        } else if (op == "~") {
            n->place = newTemp(rhs->type);
            n->code.push_back(n->place + " = ~" + rhs->printName);
            n->type = rhs->type;
            n->kind = "rvalue";
        } else if (op == "!") {
            n->place = newTemp("bool");
            n->code.push_back(n->place + " = !" + rhs->printName);
            n->type = "bool";
            n->kind = "rvalue";
        }
        $$ = n;
    }
	| SIZEOF LROUND unary_expression RROUND
    {
        dbg("unary_expression -> sizeof ( unary_expression )");
        Node* n = new Node(); 
        n->place = newTemp($3->type); 
        n->code = $3->code;
        string t = $3->type;
        if(t.back()=='*') t = "nullptr";
        n->code.push_back(n->place + " = " + to_string(typeSize[t]));
        
        n->type = $3->type;
        n->kind = "rvalue";
        n->printName = n->place;
        $$ = n;
    }
	| SIZEOF LROUND cast_type RROUND 
    {
        dbg("unary_expression -> sizeof ( type_name )");
        Node* n = new Node(); 
        n->place = newTemp($3); 
        string t = $3;
        if(t.back()=='*') t = "nullptr";
        n->code.push_back(n->place + " = " + to_string(typeSize[t]));
        n->type = $3;
        n->kind = "rvalue";
        n->printName = n->place;
        $$ = n;
    }
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
cast_expression
	: unary_expression { 
        dbg("cast_expression -> unary_expression");
        dbg(lastDeclType);
        $$ = $1; }
	| LROUND cast_type RROUND cast_expression 
    {
        dbg("cast_expression -> ( cast_type ) cast_expression");
        string a = $2; Node* b = $4;
        dbg("ww");
        dbg("Casting from " + b->type + " to " + a);
        if(!check_casting(b->type,a)){
            yyerror("Unable to cast from '" + b->type + "' to '" + a + "'.");
        }
        Node* n = new Node();
        n->code = b->code;
        n->place = newTemp(a);
        n->printName = n->place;
        n->code.push_back(n->place + " = " + b->type + "_to_"+ a +" "+ b->printName);
        n->type = a;
        n->kind = "rvalue";
        $$ = n;
    }
	;

cast_type
    : cast_type_specifier pointer_opt 
    { 
        dbg("return_type -> type_specifier pointer_opt");
        $$ = strdup( (string($1) + string($2)).c_str() );
    }
    ;

cast_type_specifier
	: VOID   { 
        dbg("cast_type_specifier -> VOID");
        $$ = strdup("void"); }
	| CHAR   { 
        dbg("cast_type_specifier -> CHAR");
        $$ = strdup("char"); }
	| INT    { 
        dbg("cast_type_specifier -> INT");
        $$ = strdup("int"); }
	| LONG   { 
        dbg("cast_type_specifier -> LONG");
        $$ = strdup("long"); }
	| DOUBLE { 
        dbg("cast_type_specifier -> DOUBLE");
        $$ = strdup("double"); }
	| BOOL   { 
        dbg("cast_type_specifier -> BOOL");
        $$ = strdup("bool"); }
	| TYPE_NAME 
    { 
        dbg("cast_type_specifier -> TYPE_NAME");
        $$ = $1; 
        if(typeDefTable.find(string($1)) != typeDefTable.end()){
            $$ = strdup(typeDefTable[string($1)].c_str());
            dbg("Typedef found: " + string($$));
        }
        else if(typeSize.find(string($1)) != typeSize.end()){
            dbg("User defined type found: " + string($1));
        }
        else
        {
            yyerror("Unknown type '" + string($1) + "'.");    
        }
    }
	;

// Done
multiplicative_expression
	: cast_expression { 
        dbg("multiplicative_expression -> cast_expression");
        $$ = $1; }
	| multiplicative_expression STAR cast_expression 
    {
        dbg("multiplicative_expression -> multiplicative_expression * cast_expression");
        Node* a = $1; Node* b = $3;
        if(!check_compatibility(a->type,b->type,"*")){
            yyerror("Type incompatibility in multiply.");
        }
        Node* n = new Node();
        n->code = a->code; n->code.insert(n->code.end(), b->code.begin(), b->code.end());
        n->place = newTemp(a->type);
        n->code.push_back(n->place + " = " + a->printName + " * " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        $$ = n;
    }
	| multiplicative_expression DIVIDE cast_expression 
    {
        dbg("multiplicative_expression -> multiplicative_expression / cast_expression");
        Node* a = $1; Node* b = $3;
        if(!check_compatibility(a->type,b->type,"/")){
            yyerror("Type incompatibility in divide.");
        }
        Node* n = new Node();
        n->code = a->code; 
        n->code.insert(n->code.end(), b->code.begin(), b->code.end());
        n->place = newTemp(a->type);
        n->code.push_back(n->place + " = " + a->printName + " / " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        $$ = n;
    }
	| multiplicative_expression MODULUS cast_expression 
    {
        dbg("multiplicative_expression -> multiplicative_expression % cast_expression");
        Node* a = $1; Node* b = $3;
        if(!check_compatibility(a->type,b->type,"%")){
        yyerror("Type incompatibility in modulus.");
        }
        Node* n = new Node();
        n->code = a->code; 
        n->code.insert(n->code.end(), b->code.begin(), b->code.end());
        n->place = newTemp(a->type);
        n->code.push_back(n->place + " = " + a->printName + " % " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        $$ = n;
    }
	;

// Done
additive_expression
	: multiplicative_expression { 
        dbg("additive_expression -> multiplicative_expression");
        $$ = $1; }
	| additive_expression PLUS multiplicative_expression 
    {
        dbg("additive_expression -> additive_expression + multiplicative_expression");
        Node* a = $1; Node* b = $3;
        if(!check_compatibility(a->type,b->type,"+")){
            yyerror("Type incompatibility in plus.");
        }
        Node* n = new Node();
        n->code = a->code; 
        n->code.insert(n->code.end(), b->code.begin(), b->code.end());
        n->place = newTemp(a->type);
        n->code.push_back(n->place + " = " + a->printName + " + " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
        if(n->type.back()=='*'){
            n->kind = "pointer";
        }
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
        n->place = newTemp(a->type);
        n->code.push_back(n->place + " = " + a->printName + " - " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
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
          n->place = newTemp(a->type);
          n->code.push_back(n->place + " = " + a->printName + " << " + b->printName);
          n->type = a->type; 
        n->printName = n->place;
          n->kind = "rvalue";
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
          n->place = newTemp(a->type);
          n->code.push_back(n->place + " = " + a->printName + " >> " + b->printName);
          n->type = a->type; 
        n->printName = n->place;
        n->kind = "rvalue";
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
          n->place=newTemp("bool"); 
          n->code.push_back(n->place + " = " + a->printName + " > " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
          n->kind = "rvalue";
          $$ = n;
      }
	| relational_expression LESS_THAN shift_expression {
          dbg("relational_expression -> relational_expression < shift_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
            if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp("bool"); 
          n->code.push_back(n->place + " = " + a->printName + " < " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
            n->kind = "rvalue";
          $$ = n;
      }
	| relational_expression LESS_EQUAL shift_expression {
            dbg("relational_expression -> relational_expression <= shift_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
          if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp("bool"); 
          n->code.push_back(n->place + " = " + a->printName + " <= " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
          n->kind = "rvalue";
          $$ = n;
      }
	| relational_expression GREATER_EQUAL shift_expression {
            dbg("relational_expression -> relational_expression >= shift_expression");
          Node* a=$1; Node* b=$3; Node* n=new Node();
          if(a->type != b->type){
                yyerror("Type incompatibility in relational expression.");
            }
          n->code=a->code; 
          n->code.insert(n->code.end(), b->code.begin(), b->code.end());
          n->place=newTemp("bool"); 
          n->code.push_back(n->place + " = " + a->printName + " >= " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
            n->kind = "rvalue";
          $$ = n;
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
          n->place=newTemp("bool"); 
          n->code.push_back(n->place + " = " + a->printName + " == " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
          n->kind = "rvalue";
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
          n->place=newTemp("bool"); 
          n->code.push_back(n->place + " = " + a->printName + " != " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
            n->kind = "rvalue";
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
          n->place=newTemp(a->type); 
          n->code.push_back(n->place + " = " + a->printName + " & " + b->printName);
          n->type = a->type;
        n->printName = n->place;
          n->kind = "rvalue";
          $$ = n;
      }
	;

// Done
exclusive_or_expression
	: and_expression { 
        dbg("exclusive_or_expression -> and_expression");
        $$ = $1; }
	| exclusive_or_expression BITWISE_XOR and_expression 
    {
        dbg("exclusive_or_expression -> exclusive_or_expression ^ and_expression");
        Node* a=$1; Node* b=$3; Node* n=new Node();
        if(!check_compatibility(a->type,b->type,"^")){
            yyerror("Type incompatibility in bitwise XOR expression.");
        }
        n->code=a->code; 
        n->code.insert(n->code.end(), b->code.begin(), b->code.end());
        n->place=newTemp(a->type); 
        n->code.push_back(n->place + " = " + a->printName + " ^ " + b->printName);
        n->type = a->type;
        n->printName = n->place;
        n->kind = "rvalue";
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
          n->place=newTemp(a->type); 
          n->code.push_back(n->place + " = " + a->printName + " | " + b->printName);
            n->type = a->type;
        n->printName = n->place;
            n->kind = "rvalue";
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
          n->place=newTemp("bool"); 
          n->code.push_back(n->place + " = " + a->printName + " && " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
          n->kind = "rvalue";
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
          n->place=newTemp("bool"); 
          n->code.push_back(n->place + " = " + a->printName + " || " + b->printName);
          n->type = "bool"; 
        n->printName = n->place;
            n->kind = "rvalue";
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
        Node* cond = $1; 
        Node* e1 = $3; 
        Node* e2 = $5;
        Node* n = new Node();

        if(e1->type != e2->type){
            yyerror("Type incompatibility in conditional expression.");
        }
        
        n->code = cond->code;
        n->place = newTemp(e1->type);
        
        int condJumpIndex = n->code.size();
        n->code.push_back("ifFalse " + cond->place + " goto __");
        vector<int> falseList = makeList(condJumpIndex);
        
        n->code.insert(n->code.end(), e1->code.begin(), e1->code.end());
        n->code.push_back(n->place + " = " + e1->place);
        
        int endJumpIndex = n->code.size();
        n->code.push_back("goto __");
        vector<int> nextList = makeList(endJumpIndex);
        
        string Lfalse = newLabel();
        n->code.push_back(Lfalse + ":");
        backpatch(n->code, falseList, Lfalse);
        
        n->code.insert(n->code.end(), e2->code.begin(), e2->code.end());
        n->code.push_back(n->place + " = " + e2->place);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, nextList, Lend);
        n->type = e1->type;
        n->printName = n->place;
        $$ = n;
    }
    ;

// Done
assignment_expression
	: conditional_expression 
    { 
        dbg("assignment_expression -> conditional_expression");
        Node* n = $1;
        $$ = n;
    }
	| unary_expression assignment_operator assignment_expression 
    {
        dbg("assignment_expression -> unary_expression assignment_operator assignment_expression");
        Node* left = $1; 
        Node* right = $3;
        Node* n = new Node();
        if(right && left)
        {
            n->code = left->code; 
            n->code.insert(n->code.end(),right->code.begin(),right->code.end());
            string op = string($2);
            string baseop = op.substr(0,op.size()-1);
            dbg("11:"+baseop);
            if (!check_compatibility(left->type,right->type,baseop)) {
                yyerror("Type incompatibility in assignment to '" + left->place + "'.");
            }
            if(left->kind.find("const")!=string::npos){
                yyerror("Cannot assign to const variable '" + left->place + "'.");
            }
            if(left->kind == "rvalue"){
                yyerror("Left side of assignment must be an lvalue.");
            }
            dbg("abcdefgh");
            if (op == "=") {
                if(right->kind == "rvalue"){
                    dbg(left->printName);
                    n->code.push_back(left->printName + " = " + right->place);
                }
                else{
                    n->code.push_back(left->printName + " = " + right->printName);
                }
            } 
            else {
                if(right->kind == "rvalue"){
                n->code.push_back(left->printName + " = " + left->printName + " " + baseop + " " + right->place);
                }
                else{
                n->code.push_back(left->printName + " = " + left->printName + " " + baseop + " " + right->printName);
                }
            }
            n->printName = left->printName;
            n->place = left->place;
            n->type = left->type;
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
        dbg(lastDeclType);
        if(lastDeclType.find("static")!=string::npos){ 
            globalCode.insert(globalCode.end(), $2->code.begin(), $2->code.end());
            $$ = new Node();
        }
        else{
            $$ = $2;
        }
    }
    ;
    
// Done
declaration_specifiers
    : type_specifier 
    {
        dbg("declaration_specifiers -> type_specifier");
        lastDeclType = string($1);
        dbg(lastDeclType);
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
        dbg(lastDeclType);
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
        dbg("flf");
        if(n->type == lastClassType){
            yyerror("Variable '" + n->place + "' cannot be of its own class type.");
        }
        n->argCount = 0;
        dbg("333"+n->place);
        bool ok = declareSymbol(n->place, n->type, n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }

        Symbol* sym = lookupSymbol(n->place);
        string w;
        // if(lastClassType=="")
        //     w = lastClassType+currentFunction+currentScope+n->place;
        // else if(lastClassType!="" && currentFunction!="")
        //     w = lastClassType+"."+currentFunction+currentScope+n->place;
        // else
        //     w = "obj."+currentScope+n->place;

        
        if(lastClassType != "" && currentFunction == "")
        {
            dbg("12" + n->place);
            dbg(currentFunction);
            dbg("13");
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } else 
            {
                w = "[ecx + " + to_string(classOffset) + "]";
                classTable[lastClassType][n->place].offset = classOffset;
                dbg("offset of " + n->place + " is " + to_string(classOffset));
                classOffset += typeSize[n->type];
                sym->printName = w;
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }
        else
        {
            functionOffset += typeSize[n->type];
            int p = functionOffset;
            for(int i = 0; i < offset.size(); i++)
                p += offset[i];
            w = "[ebp - " + to_string(p) + "]";
            sym->printName = w;
        }

        dbg("");
        dbg("Declared variable is: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");

        if(n->type == "void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            // string w1 = newTemp(n->type + "*");
            // n->code.push_back(w1 + " = &" + w + ";");
            // n->code.push_back("param " + w1 + ";");
            // n->code.push_back("call " + n->type + ", 1;");
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else if(member.second.kind.find("static") == string::npos)
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = currentFunction + currentScope + name;
                    sym->printName = "[ebp - " + to_string(functionOffset - member.second.offset) + "]";

                    dbg("offset of " + name + " is " + to_string(member.second.offset));

                    dbg("mmm");
                    dbg(w);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
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

        if(lastDeclType == lastClassType){
            yyerror("Variable '" + n->place + "' cannot be of its own class type.");
        }

        bool ok = declareSymbol(n->place, n->type, n->kind, n->syn);
        if (!ok) {
            yyerror("Duplicate declaration of '" + n->place + "' in same scope.");
        }
        
        Symbol* sym = lookupSymbol(n->place);
        string w;
        // if(lastClassType=="")
        //     w = lastClassType+currentFunction+currentScope+n->place;
        // else if(lastClassType!="" && currentFunction!="")
        //     w = lastClassType+"."+currentFunction+currentScope+n->place;
        // else
        //     w = "obj."+currentScope+n->place;

        sym->printName = w;
        

        if(lastClassType != "" && currentFunction == "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                w = "[ecx + " + to_string(classOffset) + "]";
                int p = 1;
                for(int i = 0; i < n->argCount; i++)
                {
                    p *= stoi(n->syn[i]);
                }
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += p * typeSize[n->type.substr(0, n->type.size() - n->argCount)];
                sym->printName = w;
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }
        else
        {
            int q = 1;
            for(int i = 0; i < n->argCount; i++)
            {
                q *= stoi(n->syn[i]);
            }
            functionOffset += q * typeSize[n->type.substr(0, n->type.size() - n->argCount)];
            int p = functionOffset;
            for(int i = 0; i < offset.size(); i++)
                p += offset[i];
            w = "[ebp - " + to_string(p) + "]";
            sym->printName = w;
        }

        dbg("");
        dbg("Declared array: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        for(int i = 0; i < n->argCount; i++)
        {
            dbg("Dimension " + to_string(i+1) + ": " + n->syn[i]);
        }
        dbg("");

        if(n->type =="void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zaz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else if(member.second.kind.find("static") == string::npos)
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = currentFunction + currentScope + name;

                    sym->printName = "[ebp - " + to_string(functionOffset - member.second.offset) + "]";

                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
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

        Symbol* sym = lookupSymbol(n->place);
        string w;
        // if(lastClassType=="")
        //     w = lastClassType+currentFunction+currentScope+n->place;
        // else if(lastClassType!="" && currentFunction!="")
        //     w = lastClassType+"."+currentFunction+currentScope+n->place;
        // else
        //     w = "obj."+currentScope+n->place;
        sym->printName = w;
       
        if(lastClassType != "" && currentFunction == "")
        {
            if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
                yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            } 
            else 
            {
                w = "[ecx + " + to_string(classOffset) + "]";
                sym->printName = w;
                classTable[lastClassType][n->place].offset = classOffset;
                classOffset += typeSize["nullptr"];
                classTable[lastClassType][n->place].type = n->type;
                classTable[lastClassType][n->place].kind = lastUsage;
            }
        }
        else
        {
            int p = functionOffset;
            for(int i = 0; i < offset.size(); i++)
                p += offset[i];
            functionOffset += typeSize["nullptr"];
            w = "[ebp - " + to_string(p + typeSize["nullptr"]) + "]";
            sym->printName = w;
        }

        dbg("");
        dbg("Declared pointer: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");

        if(n->type =="void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        if(classTable.find(lastDeclType) != classTable.end())
        {
            // string w1 = newTemp();
            // n->code.push_back(w1 + " = " + w + ";");
            // n->code.push_back("param " + w1 + ";");
            // n->code.push_back("call " + lastDeclType + ", 1;");
            for(const auto& member : classTable[lastDeclType])
            {
                if(member.second.kind == "function")
                {
                    string name = stars + n->place + "." + member.first;
                    string original = stars + n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = stars + n->place + "." + f.place;
                    dbg("zzw");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else if(member.second.kind.find("static") == string::npos)
                {
                    string name = stars + n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = lastClassType+currentFunction+currentScope + name;
                    sym->printName = "[ebp - " + to_string(functionOffset - member.second.offset) + "]";
                    dbg("mmm");
                    dbg(w);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
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

        dbg(lastDeclType);
        dbg("333"+n->place);

        if(n->type.find("static")!=string::npos){
            n->type.erase(0,6);
            n->kind += "static";
        }
        if(n->type.find("const")!=string::npos){
            n->type.erase(0,5);
            n->kind += "const";
        }
        dbg("Type of assignment expression: " + $3->type);
        dbg("Type of variable: " + n->type);
        if(n->type != $3->type){
            yyerror("Type mismatch in initialization of '" + name + "'.");
        }

        if(n->type == lastClassType){
            yyerror("Variable '" + n->place + "' cannot be of its own class type.");
        }

        bool ok = declareSymbol(n->place,n->type,n->kind);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }
        Symbol* sym = lookupSymbol(n->place);
        string w;
        // if(lastClassType=="")
        //     w = lastClassType+currentFunction+currentScope+n->place;
        // else if(lastClassType!="" && currentFunction!="")
        //     w = lastClassType+"."+currentFunction+currentScope+n->place;
        // else
        //     w = "obj."+currentScope+n->place;
        sym->printName = w;
        
        if(lastClassType != "" && currentFunction == "")
        {
            yyerror("class member initialization not supported");
            // if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
            //     yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            // } else 
            // {
            //     w = "[this + " + to_string(classOffset) + "]";
            //     classTable[lastClassType][n->place].offset = classOffset;
            //     classOffset += typeSize[n->type];
            //     string s = newTemp(n->type + "*");
            //     n->code.push_back(s + " = " + w + ";");
            //     if($3->kind == "rvalue"){
            //         n->code.push_back("*" + s + " = " + $3->place + ";");
            //     }
            //     else{
            //         n->code.push_back("*" + s + " = " + $3->printName + ";");
            //     }
            //     sym->printName = w;
            //     classTable[lastClassType][n->place].type = n->type;
            //     classTable[lastClassType][n->place].kind = lastUsage;
            // }
        }
        else
        {
            functionOffset += typeSize[n->type];
            int p = functionOffset;
            for(int i = 0; i < offset.size(); i++)
                p += offset[i];
            w = "[ebp - " + to_string(p) + "]";
            sym->printName = w;
            if($3->kind == "rvalue"){
                n->code.push_back(w + " = " + $3->place);
            }
            else{
                n->code.push_back(w + " = " + $3->printName);
            }
        }

        dbg("");
        dbg("Declared variable: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");

        if(n->type =="void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("nmnmn");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else if(member.second.kind.find("static") == string::npos)
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = lastClassType+currentFunction+currentScope+name;

                    sym->printName = "[ebp - " + to_string(functionOffset - member.second.offset) + "]";

                    dbg("mmm");
                    dbg(w);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
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

        Symbol* sym = lookupSymbol(n->place);
        string w;
        // if(lastClassType=="")
        //     w = lastClassType+currentFunction+currentScope+n->place;
        // else if(lastClassType!="" && currentFunction!="")
        //     w = lastClassType+"."+currentFunction+currentScope+n->place;
        // else
        //     w = "obj."+currentScope+n->place;
        sym->printName = w;
       
        if(lastClassType != "" && currentFunction == "")
        {
            yyerror("class member initialization not supported");
            // if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
            //     yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            // } 
            // else 
            // {
            //     w = "[this + " + to_string(classOffset) + "]";
            //     sym->printName = w;
            //     classTable[lastClassType][n->place].offset = classOffset;
            //     classOffset += typeSize["nullptr"];
            //     classTable[lastClassType][n->place].type = n->type;
            //     classTable[lastClassType][n->place].kind = lastUsage;
            // }
        }
        else
        {
            functionOffset += typeSize["nullptr"];
            int p = functionOffset;
            for(int i = 0; i < offset.size(); i++)
                p += offset[i];
            w = "[ebp - " + to_string(p) + "]";
            sym->printName = w;
        }
        n->code.push_back(w + " = " + $4->printName);

        dbg("");
        dbg("Declared pointer: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        dbg("");

        if(n->type =="void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(lastDeclType) != classTable.end())
        {
            for(const auto& member : classTable[lastDeclType])
            {
                if(member.second.kind == "function")
                {
                    string name = stars + n->place + "." + member.first;
                    string original = stars + n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = stars + n->place + "." + f.place;
                    dbg("zzw");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else if(member.second.kind.find("static") == string::npos)
                {
                    string name = stars + n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = lastClassType+currentFunction+currentScope + name;
                    sym->printName = "[ebp - " + to_string(functionOffset - member.second.offset) + "]";

                    dbg("mmm");
                    dbg(w);
                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
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

        if(lastDeclType == lastClassType){
            yyerror("Variable '" + n->place + "' cannot be of its own class type.");
        }
        if(p < $4->argCount){
            yyerror("Number of elements in initializer is greater than array size for '" + name + "'.");
        }

        bool ok = declareSymbol(n->place,n->type,n->kind,n->syn);
        if (!ok) {
            yyerror("Duplicate declaration of '" + name + "' in same scope.");
        }

        Symbol* sym = lookupSymbol(n->place);
        string w;
        // if(lastClassType=="")
        //     w = lastClassType+currentFunction+currentScope+n->place;
        // else if(lastClassType!="" && currentFunction!="")
        //     w = lastClassType+"."+currentFunction+currentScope+n->place;
        // else
        //     w = "obj."+currentScope+n->place;
        sym->printName = w;

       
        if(lastClassType != "" && currentFunction == "")
        {
            yyerror("class member initialization not supported");
            // if(classTable[lastClassType].find(n->place) != classTable[lastClassType].end()){
            //     yyerror("Duplicate declaration of member '" + n->place + "' in class '" + lastClassType + "'.");
            // } 
            // else 
            // {
            //     w = "this + " + to_string(classOffset);
            //     sym->printName = w;
            //     classTable[lastClassType][n->place].offset = classOffset;
            //     int p = 1;
            //     for(int i = 0; i < n->argCount; i++)
            //     {
            //         p *= stoi(n->syn[i]);
            //     }
            //     classOffset += p * typeSize[n->type.substr(0, n->type.size() - n->argCount)];
            //     classTable[lastClassType][n->place].type = n->type;
            //     classTable[lastClassType][n->place].kind = lastUsage;
            // }
        }
        else
        {
            int q = 1;
            for(int i = 0; i < n->argCount; i++)
            {
                q *= stoi(n->syn[i]);
            }
            functionOffset += q * typeSize[n->type.substr(0, n->type.size() - n->argCount)];
            int p = functionOffset;
            for(int i = 0; i < offset.size(); i++)
                p += offset[i];
            w = "[ebp - " + to_string(p) + "]";
            sym->printName = w;
        }
        dbg("fff");
        string tmp = newTemp("nullptr");
        dbg("ccv" + to_string(functionOffset));
        n->code.push_back(tmp + " = &" + sym->printName);
        for(int i = 0; i < $4->argCount; i++)
        {
            n->code.push_back("*" + tmp + " = " + $4->syn[i]);
            n->code.push_back(tmp + " = " + tmp + " + " + to_string(typeSize[$4->type]));
        }

        dbg("");
        dbg("Declared array: " + n->place + " of type: " + n->type + " and kind: " + n->kind);
        for(int i = 0; i < n->argCount; i++)
        {
            dbg("Dimension " + to_string(i+1) + ": " + n->syn[i]);
        }
        dbg("");
        if(n->type =="void"){
            yyerror("Variable '" + n->place + "' cannot be of type void.");
        }

        dbg("");
        if(classTable.find(n->type) != classTable.end())
        {
            for(const auto& member : classTable[n->type])
            {
                if(member.second.kind == "function")
                {
                    string name = n->place + "." + member.first;
                    string original = n->place + "." + member.second.method.original;
                    if(lookupSymbol(original) == nullptr)
                        declareSymbol(original, "function","function",vector<string>(),true);
                    dbg(original);
                    funcInfo f = member.second.method;
                    f.place = n->place + "." + f.place;
                    dbg("zz");
                    dbg(f.place);
                    funcTable[name] = f;
                    dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                }
                else if(member.second.kind.find("static") == string::npos)
                {
                    string name = n->place + "." + member.first;
                    bool ok = declareSymbol(name, member.second.type, member.second.kind);

                    if (!ok) {
                        yyerror("Duplicate declaration of '" + name + "' in same scope.");
                    }

                    Symbol* sym = lookupSymbol(name);
                    string w = currentFunction + currentScope + name;
                    sym->printName = "[ebp - " + to_string(functionOffset - member.second.offset) + "]";

                    dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                }
            }
        }
        dbg("");
        n->place = w;
        $$ = n;
    }
    /* | pointer_list IDENTIFIER square_list ASSIGN initializer
    {
        dbg("init_declarator -> pointer_list IDENTIFIER square_list = initializer ");
        Node* n = new Node();
        string name = string($2);return
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
        if(n->place == ""){
            yyerror("Initializer type incorrect.");
        }
        n->syn.push_back(n->place);
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
        if($3->place == ""){
            yyerror("Initializer type incorrect.");
        }
        n->syn.push_back($3->place);
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
        if(typeDefTable.find(string($1)) != typeDefTable.end()){
            lastDeclType = typeDefTable[string($1)];
            $$ = strdup(lastDeclType.c_str());
        }
        else if(typeSize.find(string($1)) != typeSize.end()){
            lastDeclType = string($1);
            dbg("User defined type found: " + string($1));
            $$ = strdup(lastDeclType.c_str());
        }
        else
        {
            yyerror("Unknown type '" + string($1) + "'.");    
        }
    }
	;

// Done
translation_unit
	: external_declaration 
    { 
        dbg("translation_unit -> external_declaration");
        finalRoot = $1; $$ = $1; 
    }
	| translation_unit external_declaration 
    {
        dbg("translation_unit -> translation_unit external_declaration");
        Node* a = $1; Node* b = $2;
        if (b) 
        { 
            a->code.insert(a->code.end(), b->code.begin(), b->code.end()); 
            finalRoot = a; $$ = a; 
        }
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
        vector<string> cd;
        // cd.push_back(lastClassType + ":");
        cd.insert(cd.end(), $5->code.begin(), $5->code.end());
        $$ = $5;
        $$->code = cd;
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
	| external_declare 
    {
        dbg("struct_or_class_member -> external_declare");
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
        currentFunction = "";
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
            dbg("Parameter: " + string($2) + " of type which is: " + string($1));
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
	| LCURLY 
    {
        currentScope += ".";
        if(funcOnce == false)
        {
            pushScope();
        }
        else
            funcOnce = false;
        offset.push_back(functionOffset);
        dbg("12qwr");
        dbg(to_string(functionOffset));
        functionOffset = 0;
    } statement_list RCURLY 
    {
        dbg("compound_statement -> { statement_list }");
        Node* n = $3;
        popScope();
        currentScope.pop_back();
        vector<string> cd;
        cd.push_back("sub esp, " + to_string(functionOffset));
        cd.insert(cd.end(), n->code.begin(), n->code.end());
        if(cd.back().find("return") != string::npos)
        {
            cd.insert(cd.end()-1, "add esp, " + to_string(functionOffset));
        }
        else
        {
            cd.push_back("add esp, " + to_string(functionOffset));
        }
        $$ = n;
        $$->code = cd;
        if(!inloop)
        { 
            for(size_t i = 0; i < n->code.size(); i++) {
                if(n->code[i]=="break"){
                    yyerror("Incorrect usage of 'break'");
                }
                if(n->code[i]=="continue"){
                    yyerror("Incorrect usage of 'continue'");
                }
            }
        }
        if(!offset.empty())
        functionOffset = offset.back();
        else functionOffset = 0;
        offset.pop_back();
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
          Node* e = $3;
          if(e->type != "bool"){
              yyerror("Condition expression must be of type bool.");
          }
          Node* s1 = $5;
          Node* n = new Node();
          
          n->code = e->code;
          int falseJumpIndex = n->code.size();
          n->code.push_back("ifFalse " + e->place + " goto __");
          vector<int> falseList = makeList(falseJumpIndex);
          
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          
          string Lend = newLabel();
          n->code.push_back(Lend + ":");
          backpatch(n->code, falseList, Lend);
          
          $$ = n;
      }
    | IF LROUND expression RROUND statement ELSE statement {
          dbg("selection_statement -> if ( expression ) statement else statement");
          Node* e = $3;
            if(e->type != "bool"){
                yyerror("Condition expression must be of type bool.");
            }
          Node* s1 = $5;
          Node* s2 = $7;
          Node* n = new Node();
          
          n->code = e->code;
          
          int falseJumpIndex = n->code.size();
          n->code.push_back("ifFalse " + e->place + " goto __");
          vector<int> falseList = makeList(falseJumpIndex);
          
          n->code.insert(n->code.end(), s1->code.begin(), s1->code.end());
          
          int endJumpIndex = n->code.size();
          n->code.push_back("goto __");
          vector<int> endList = makeList(endJumpIndex);
          
          string Lfalse = newLabel();
          n->code.push_back(Lfalse + ":");
          backpatch(n->code, falseList, Lfalse);
          
          n->code.insert(n->code.end(), s2->code.begin(), s2->code.end());
          
          string Lend = newLabel();
          n->code.push_back(Lend + ":");
          backpatch(n->code, endList, Lend);
          $$ = n;
      }
    | switch_head LCURLY case_list RCURLY {
        dbg("selection_statement -> switch_head { case_list }");
        Node* switchExpr = $1;
        Node* cases = $3;
        Node* n = new Node();
        
        n->code = switchExpr->code;
        n->code.insert(n->code.end(), cases->syn.begin(), cases->syn.end());
        n->code.push_back("goto __");
        n->code.insert(n->code.end(), cases->code.begin(), cases->code.end());
        
        string exitLabel = newLabel();
        n->code.push_back(exitLabel + ":");

        vector<int> exitList;
        for(size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "goto __") {
                exitList.push_back(i);
            }
        }

        backpatch(n->code,exitList,exitLabel);
        $$ = n;
        inloop=false;
      }
    ;

switch_head
    : SWITCH{inloop=true;} LROUND assignment_expression RROUND {
        dbg("switch_head -> SWITCH ( expression )");
        Node* e = $4;
        Node* n = new Node();
        n->code = e->code;
        n->place = e->place;
        switchType = e->type;
        switchVar = e->printName;
        $$ = n;
      }
    ;

case_list
    :  {
        dbg("case_list -> <empty>");
        Node* n = new Node();
        $$ = n;
      }
    | case_list case_item {
        dbg("case_list -> case_list case_item");
        Node* prev = $1;
        Node* curr = $2;
        prev->syn.insert(prev->syn.end(), curr->syn.begin(), curr->syn.end());
        prev->code.insert(prev->code.end(), curr->code.begin(), curr->code.end());
        $$ = prev;
      }
    ;

case_item
    : CASE constant_expression statement {
        dbg("case_item -> CASE constant_expression : statement");
        Node* caseVal = $2;

        if(caseVal->type != switchType){
            yyerror("Type mismatch in case label.");
        }
        Node* stmt = $3;
        Node* n = new Node();
        
        string caseLabel = newLabel();
        if(!caseVal->code.empty()){
            n->syn.insert(n->syn.end(), caseVal->code.begin(), caseVal->code.end());
        }
        n->syn.push_back("if " + switchVar + " == " + caseVal->place + " goto " + caseLabel);
        n->code.push_back(caseLabel + ":");
        n->code.insert(n->code.end(), stmt->code.begin(), stmt->code.end());
        
        for (size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
            }
        }
        
        $$ = n;
      }
    | DEFAULT statement {
        dbg("case_item -> DEFAULT : statement");
        Node* stmt = $2;
        Node* n = new Node();
        
        string defaultLabel = newLabel();
        n->syn.push_back("goto " + defaultLabel);
        
        n->code.push_back(defaultLabel + ":");
        n->code.insert(n->code.end(), stmt->code.begin(), stmt->code.end());
        
        for (size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
            }
        }
        // n->code.push_back("goto __");        
        $$ = n;
      }
    ;

// Done
iteration_statement
    : WHILE LROUND expression RROUND {inloop=true;}statement {
        dbg("iteration_statement -> WHILE ( expression ) statement");
        Node* cond = $3; 
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* body = $6;
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
        int jumpIndex = n->code.size();
        n->code.push_back("ifFalse " + cond->place + " goto __");
        vector<int> falseList = makeList(jumpIndex);
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);

        for(size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
                falseList.push_back(i);
            }
            if (n->code[i] == "continue") {
                n->code[i] = "goto " + Lbegin;
            }
        }
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, falseList, Lend);
        $$ = n;
        inloop=false;
    }
    | UNTIL LROUND expression RROUND {inloop=true;}statement {
        dbg("iteration_statement -> UNTIL ( expression ) statement");
        Node* cond = $3; 
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* body = $6;
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
        int jumpIndex = n->code.size();
        n->code.push_back("if " + cond->place + " goto __");
        vector<int> falseList = makeList(jumpIndex);
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);

        for(size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
                falseList.push_back(i);
                dbg("Found break at line " + to_string(i));
            }
            if (n->code[i] == "continue") {
                n->code[i] = "goto " + Lbegin;
            }
        }
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, falseList, Lend);
        $$ = n;
        inloop=false;
    }
    | DO{inloop=true;} statement WHILE LROUND expression RROUND SEMICOLON {
        dbg("iteration_statement -> DO statement WHILE ( expression ) ;");
        Node* body = $3;
        Node* cond = $6;
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* n = new Node();
        
        string Lbegin = newLabel();
        n->code.push_back(Lbegin + ":");
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());

        vector<int> falseList;
        for(size_t i = 0; i < n->code.size(); i++) {
            if (n->code[i] == "break") {
                n->code[i] = "goto __";
                falseList.push_back(i);
            }
            if (n->code[i] == "continue") {
                n->code[i] = "goto " + Lbegin;
            }
        }
        
        int jumpIndex = n->code.size();
        n->code.push_back("if " + cond->place + " goto " + Lbegin);

        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code, falseList, Lend);
        $$ = n;
        inloop=false;
    }
    | for_start LROUND for_init_statement expression_statement RROUND{inloop=true;} statement {
        dbg("iteration_statement -> FOR ( for_init_statement expression_statement ) statement");
        Node* init = $3;
        Node* cond = $4;
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* body = $7;
        Node* n = new Node();
        
        string Lbegin = newLabel();
        if(init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
        n->code.push_back(Lbegin + ":");
        
        vector<int> falseList;
        if (cond && cond->place != "") {
            n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
            int jumpIndex = n->code.size();
            n->code.push_back("ifFalse " + cond->place + " goto __");
            falseList = makeList(jumpIndex);
        }

        for(size_t i = 0; i < body->code.size(); i++) {
            if (body->code[i] == "break") {
                body->code[i] = "goto __";
                falseList.push_back(n->code.size() + i);
            }
            if (body->code[i] == "continue") {
                body->code[i] = "goto " + Lbegin;
            }
        }
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        n->code.push_back("goto " + Lbegin);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        backpatch(n->code,falseList,Lend);
        $$ = n;
        inloop=false;
        popScope();
    }
    | for_start LROUND for_init_statement expression_statement expression RROUND{inloop=true;}statement {
        dbg("iteration_statement -> FOR ( for_init_statement expression_statement expression ) statement");
        Node* init = $3;
        Node* cond = $4;
        if(cond->type != "bool"){
            yyerror("Condition expression must be of type bool.");
        }
        Node* iter = $5;
        Node* body = $8;
        Node* n = new Node();
        
        string Lbegin = newLabel();
        if (init) n->code.insert(n->code.end(), init->code.begin(), init->code.end());
        n->code.push_back(Lbegin + ":");
        
        vector<int> falseList;
        if (cond && cond->place != "") {
            n->code.insert(n->code.end(), cond->code.begin(), cond->code.end());
            int jumpIndex = n->code.size();
            n->code.push_back("ifFalse " + cond->place + " goto __");
            falseList = makeList(jumpIndex);
        }

        for(size_t i = 0; i < body->code.size(); i++) {
            if (body->code[i] == "break") {
                body->code[i] = "goto __";
                falseList.push_back(n->code.size() + i);
            }
            if (body->code[i] == "continue") {
                body->code[i] = "goto " + Lbegin;
            }
        }
        
        n->code.insert(n->code.end(), body->code.begin(), body->code.end());
        if (iter) n->code.insert(n->code.end(), iter->code.begin(), iter->code.end());
        n->code.push_back("goto " + Lbegin);
        
        string Lend = newLabel();
        n->code.push_back(Lend + ":");
        if (!falseList.empty())
            backpatch(n->code, falseList, Lend);
        $$ = n;
        inloop=false;
        popScope();
    }
    ;

for_start
    : FOR {
        dbg("for_start -> FOR");
        pushScope();
        Node* n = new Node();
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
          n->code.push_back("continue"); 
          $$ = n;
      }
	| BREAK SEMICOLON {
            dbg("jump_statement -> BREAK ;");
          Node* n = new Node(); 
          n->code.push_back("break"); 
          $$ = n;
      }
	| RETURN SEMICOLON {
            dbg("jump_statement -> RETURN ;");
          Node* n = new Node(); 
          if(lastFnType != "void")
              yyerror("Return statement must return a value.");
          n->code.push_back("return"); 
          $$ = n;
      }
	| RETURN expression SEMICOLON 
    {
        dbg("jump_statement -> RETURN expression ;");
        Node* expr = $2;
        Node* n = new Node();
        if(expr == nullptr)
            yyerror("Return statement must return a value.");
        else{
            if(lastClassType == "")
            {
                dbg("Return type: " + expr->type + ", Expected type: " + funcTable[currentFunction].returnType);

                dbg("");
                dbg("lastDeclType: " + lastDeclType);
                dbg("currentFunction: " + currentFunction);
                dbg("");
                if(expr->type != funcTable[currentFunction].returnType){
                    yyerror("Return type mismatch in function '" + currentFunction + "'.");
                }
                dbg("Function '" + currentFunction + "' has return statement returning '" + expr->place + "'.");
                n->code = expr->code;
                n->code.push_back("return " + expr->printName);
            }
            else
            {
                dbg("3");
                dbg(currentFunction);
                dbg("Return type: " + expr->type + ", Expected type: " + classTable[lastClassType][currentFunction].method.returnType);
                if(expr->type != classTable[lastClassType][currentFunction].method.returnType){
                    yyerror("Return type mismatch in method '" + currentFunction + "'.");
                }
                dbg("Method '" + currentFunction + "' has return statement returning '" + expr->place + "'.");
                n->code = expr->code;
                n->code.push_back("return " + expr->printName);
            }
        }
        $$ = n;
    }
    ;

// Done
external_declare
    : type_specifier
    {
        dbg("external_declare -> type_specifier");
        lastDeclType = string($1);
        dbg("lastDeclType in external_declare: " + lastDeclType);
        lastFnType = lastDeclType;
    } 
    external 
    { 
        dbg("external_declare -> type_specifier external");
        $$ = $3; 
    }
    | type_specifier pointer_list
    {
        dbg("external_declare -> type_specifier pointer_list");
        lastDeclType = string($1)+string($2);
        lastFnType = lastDeclType;
        dbg("");
        dbg("lastDeclType in external_declare: " + lastDeclType);
        dbg("");
    } 
    external 
    { 
        dbg("external_declare -> type_specifier pointer_list external");
        $$ = $4; 
    }
    | CONST type_specifier 
    {
        dbg("external_declare -> const type_specifier");
        lastDeclType = string($1)+string($2);
    } 
    init_declarator_list SEMICOLON
    {
        dbg("external_declare -> const type_specifier init_declarator_list ;");
        $$ = $4;
    }
    ; 

external_declaration
	: type_specifier
    {
        dbg("external_declaration -> type_specifier");
        lastDeclType = string($1);
        dbg("lastDeclType in external_declaration: " + lastDeclType);
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
    | struct_or_class_specifier SEMICOLON 
    { 
        dbg("external_declaration -> struct_or_class_specifier ;");
        classOffset = 0;
        $$ = $1; 
    } 
    | TYPEDEF return_type IDENTIFIER SEMICOLON {
        dbg("external_declaration -> TYPEDEF return_type IDENTIFIER ;");
        typeSize[string($3)] = typeSize[string($2)];
        typeDefTable[string($3)] = string($2);
        $$ = new Node();
    }
    | declare {
        dbg("external_declaration -> declare");
        globalCode.insert(globalCode.begin(),$1->code.begin(),$1->code.end());
        $$ = new Node();
    }
    ;

declare
    : CONST type_specifier 
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
	;

external 
    : IDENTIFIER LROUND RROUND 
    {
        dbg("");
        dbg("lastFnType in external: " + lastFnType);
        dbg("");
        dbg("external -> IDENTIFIER ( )");
        string fname = string($1);

        inFunction = true;
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
            funcTable[fname].printName = fname;
            dbg("Function '" + fname + "' with return type '" + funcTable[fname].returnType + "' declared.");
        }// dbg("Function '" + fname + "' with " + to_string(funcTable[fname].paramCount) + " parameters declared.");
        else
        {
            if(classTable[lastClassType].find(string($1)) != classTable[lastClassType].end())
                yyerror("Method redeclaration: " + fname);
            classTable[lastClassType][string($1)].kind = "function";
            classTable[lastClassType][string($1)].type = lastFnType;
            classTable[lastClassType][string($1)].place = string($1);
            funcInfo f;
            f.place = string($1);
            f.returnType = lastFnType;
            f.paramCount = 0;
            f.original = string($1);
            f.printName = lastClassType + "." + string($1);
            if(string(lastFnType) == "void") f.hasReturn = false;
            else f.hasReturn = true;
            classTable[lastClassType][string($1)].method = f;
            dbg("1");
            dbg("Method '" + fname + "' with return type '" + f.returnType + "' declared.");
            dbg("2");
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
        if($5->code.empty() || $5->code.back().substr(0,6) != "return")
        {
            yyerror("Missing return statement in function '" + fname + "'.");
        }
        n->code.push_back(fname + ":");
        n->code.push_back("push ebp");
        n->code.push_back("mov ebp, esp");
        if($5) n->code.insert(n->code.end(),$5->code.begin(),$5->code.end());
        popScope();
        n->code.push_back("");
        currentFunction = "";
        lastFnType="int";
        inFunction = false;
        $$ = n;
    }
    | IDENTIFIER LROUND parameter_list RROUND 
    {
        dbg("");
        dbg("lastDeclType in external: " + lastFnType);
        dbg("");
        dbg("external -> IDENTIFIER ( parameter_list )");
        string fname = string($1);
        inFunction = true;
        
        if(lastClassType == "")
        {
            if(lookupSymbol(fname) == nullptr)
                declareSymbol(fname,"function","function",vector<string>(),true);
            
            for (int i=0;i<$3->syn.size();i+=2)
            {
                fname += "_" + $3->syn[i];
            }

            if(funcTable.find(fname) != funcTable.end())
                yyerror("Function redeclaration: " + fname);
            
            if(string(lastFnType) == "void") funcTable[fname].hasReturn = false;
            else funcTable[fname].hasReturn = true;

            funcTable[fname].returnType = string(lastFnType); 
            funcTable[fname].paramCount = $3->syn.size()/2;
            funcTable[fname].printName = fname;
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
            for (int i=0;i<$3->syn.size();i+=2)
            {
                fname += "_" + $3->syn[i];
            }
            string methodName = fname;
            if(classTable[lastClassType].find(methodName) != classTable[lastClassType].end())
                yyerror("Method redeclaration: " + lastClassType + "." + methodName);
            classTable[lastClassType][methodName].kind = "function";
            classTable[lastClassType][methodName].type = lastFnType;
            classTable[lastClassType][methodName].place = methodName;

            funcInfo f;
            f.place = methodName;
            f.original = string($1);
            f.returnType = lastFnType;
            f.paramCount = $3->syn.size()/2;
            f.printName = lastClassType + "." + methodName;
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
        funcOnce = true;
        int argoffset = 0;
        for (int i=0;i<$3->syn.size();i+=2){
            argoffset += typeSize[$3->syn[i]];
        }


        for(int i=1;i<$3->syn.size();i+=2)
        {
            string pname = $3->syn[i];
            // string pname = "[ebp+" + to_string(8 + argoffset + getTypeSize($3->syn[i-1])) + "]";
            string ptype = $3->syn[i-1];
            bool ok = declareSymbol(pname,ptype);
            Symbol* sym = lookupSymbol(pname);
            argoffset -= typeSize[$3->syn[i-1]];
            string prname = "[ebp + " + to_string(8 + argoffset) + "]";

            sym->printName = prname;
            dbg("Parameter declare: " + pname + " of type " + ptype);
            dbg(lastDeclType);

            string stars = "";
            string q = "";
            for(char c : ptype)
            {
                if(c == '*')
                    stars += '*';
                else
                    q += c;
            }
            dbg("q: " + q);
            dbg("stars: " + stars);
            if(classTable.find(q) != classTable.end())
            {
                dbg("abcd");
                for(const auto& member : classTable[q])
                {
                    if(member.second.kind == "function")
                    {
                        string name = stars + pname + "." + member.first;
                        string original = stars + pname + "." + member.second.method.original;
                        if(lookupSymbol(original) == nullptr)
                            declareSymbol(original, "function","function",vector<string>(),true);
                        dbg(original);
                        funcInfo f = member.second.method;
                        f.place = stars + pname + "." + f.place;
                        dbg("zz");
                        dbg(f.place);
                        funcTable[name] = f;
                        dbg("Function '" + name + "' with return type '" + funcTable[name].returnType + "' declared.");
                    }
                    else
                    {
                        string name = stars + pname + "." + member.first;
                        bool ok = declareSymbol(name, member.second.type, member.second.kind);

                        if (!ok) {
                            yyerror("Duplicate declaration of '" + name + "' in same scope.");
                        }

                        Symbol* sym = lookupSymbol(name);

                        // string w;
                        // if(lastClassType == "")
                        //     w = currentFunction + currentScope + "." + name;
                        // else
                        //     w = lastClassType + "." + currentFunction + currentScope + "." + name;
                        sym->printName = "[ebp + " + to_string(8 + argoffset + member.second.offset) + "]";

                        dbg("mmm");
                        // dbg(w);
                        dbg("Variable '" + name + "' with type '" + member.second.type + "' declared.");
                    }
                }
            }
            string w;
            // // if(lastClassType == "")
            // //     w = currentFunction + currentScope + "." + pname;
            // // else
            // //     w = lastClassType + "." + currentFunction + currentScope + "." + pname;
            // sym->printName = w;
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
        // popScope(); 

        if(lastClassType != "")
            fname = lastClassType + "." + fname;

        dbg("");
        dbg("fname: " + fname);
        dbg("lastFnType in external: " + lastFnType);
        dbg("");

        if($6->code.empty() || $6->code.back().substr(0,6) != "return")
        {
            yyerror("Missing return statement in function '" + fname + "'.");
        }
        n->code.push_back(fname + ":");
        n->code.push_back("push ebp");
        n->code.push_back("mov ebp, esp");

        if($6) n->code.insert(n->code.end(),$6->code.begin(),$6->code.end());
        finalRoot = n;
        n->code.push_back("");
        currentFunction = "";
        inFunction = false;

        lastFnType="int";
        $$ = n;
    }
    | init_declarator_list SEMICOLON 
    { 
        dbg("external -> init_declarator_list ;");
        Node* n = new Node();
        if(lastClassType == "")
            globalCode.insert(globalCode.begin(),$1->code.begin(),$1->code.end());
        else
        {
            n->code.insert(n->code.end(),$1->code.begin(),$1->code.end());
            n->code.push_back("");
        } 
        $$ = n;
    }
    ;

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
                // fname += "_" + $4->syn[i];
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
        currentFunction = "";
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
        globalCode.push_back("");
        finalRoot->code.insert(finalRoot->code.begin(),globalCode.begin(),globalCode.end());
        string indent="";
        for(int i=0;i<finalRoot->code.size();i++) {
            if(finalRoot->code[i].back()==':') indent="";
            else indent="    ";
            cout<<indent<<finalRoot->code[i]<<"\n";
        }
    }

    return 0;
}

