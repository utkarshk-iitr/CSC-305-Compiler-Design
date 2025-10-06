// #ifndef ENHANCED_TYPE_CONVERSION_H
// #define ENHANCED_TYPE_CONVERSION_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

enum Type {
    INT, DOUBLE, CHAR, BOOL, STRING, VOID,
    INT_PTR, DOUBLE_PTR, CHAR_PTR, BOOL_PTR, STRING_PTR, VOID_PTR, NULL_PTR
};

enum ConversionOp {
    ITOD, ITOC, ITOB, ITOS, DTOI, DTOC, DTOB, DTOS,
    CTOI, CTOD, CTOB, CTOS, BTOI, BTOD, BTOC, BTOS,
    STOI, STOD, STOC, STOB, ITOP, PTOI, PTOB, PTOP,
    STOP, PTOS, NTOP
};

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        return hash<T1>()(p.first) ^ hash<T2>()(p.second);
    }
};

class TypeConvHandler {
private:
    int tempCount;
    unordered_map<pair<Type, Type>, ConversionOp, pair_hash> convMap;
    unordered_map<Type, unordered_set<Type>> validConv;

    void initConvMaps() {
        validConv[INT] = {DOUBLE, CHAR, BOOL, STRING, INT_PTR, VOID_PTR};
        validConv[DOUBLE] = {INT, CHAR, BOOL, STRING};
        validConv[CHAR] = {INT, DOUBLE, BOOL, STRING};
        validConv[BOOL] = {INT, DOUBLE, CHAR, STRING};
        validConv[STRING] = {INT, DOUBLE, CHAR, BOOL, CHAR_PTR};
        validConv[INT_PTR] = {VOID_PTR, INT, BOOL};
        validConv[DOUBLE_PTR] = {VOID_PTR, INT, BOOL};
        validConv[CHAR_PTR] = {VOID_PTR, INT, BOOL, STRING};
        validConv[BOOL_PTR] = {VOID_PTR, INT, BOOL};
        validConv[STRING_PTR] = {VOID_PTR, INT, BOOL};
        validConv[VOID_PTR] = {INT_PTR, DOUBLE_PTR, CHAR_PTR, BOOL_PTR, STRING_PTR, INT, BOOL};
        validConv[NULL_PTR] = {INT_PTR, DOUBLE_PTR, CHAR_PTR, BOOL_PTR, STRING_PTR, VOID_PTR, BOOL};
        initBasicConv();
        initPtrConv();
    }

    void initBasicConv() {
        convMap[{INT, DOUBLE}] = ITOD; convMap[{INT, CHAR}] = ITOC; convMap[{INT, BOOL}] = ITOB; convMap[{INT, STRING}] = ITOS;
        convMap[{DOUBLE, INT}] = DTOI; convMap[{DOUBLE, CHAR}] = DTOC; convMap[{DOUBLE, BOOL}] = DTOB; convMap[{DOUBLE, STRING}] = DTOS;
        convMap[{CHAR, INT}] = CTOI; convMap[{CHAR, DOUBLE}] = CTOD; convMap[{CHAR, BOOL}] = CTOB; convMap[{CHAR, STRING}] = CTOS;
        convMap[{BOOL, INT}] = BTOI; convMap[{BOOL, DOUBLE}] = BTOD; convMap[{BOOL, CHAR}] = BTOC; convMap[{BOOL, STRING}] = BTOS;
        convMap[{STRING, INT}] = STOI; convMap[{STRING, DOUBLE}] = STOD; convMap[{STRING, CHAR}] = STOC; convMap[{STRING, BOOL}] = STOB;
    }

    void initPtrConv() {
        convMap[{INT, INT_PTR}] = ITOP; convMap[{INT, VOID_PTR}] = ITOP;
        convMap[{INT_PTR, INT}] = PTOI; convMap[{DOUBLE_PTR, INT}] = PTOI; convMap[{CHAR_PTR, INT}] = PTOI;
        convMap[{BOOL_PTR, INT}] = PTOI; convMap[{STRING_PTR, INT}] = PTOI; convMap[{VOID_PTR, INT}] = PTOI;
        convMap[{INT_PTR, BOOL}] = PTOB; convMap[{DOUBLE_PTR, BOOL}] = PTOB; convMap[{CHAR_PTR, BOOL}] = PTOB;
        convMap[{BOOL_PTR, BOOL}] = PTOB; convMap[{STRING_PTR, BOOL}] = PTOB; convMap[{VOID_PTR, BOOL}] = PTOB;
        convMap[{INT_PTR, VOID_PTR}] = PTOP; convMap[{DOUBLE_PTR, VOID_PTR}] = PTOP; convMap[{CHAR_PTR, VOID_PTR}] = PTOP;
        convMap[{BOOL_PTR, VOID_PTR}] = PTOP; convMap[{STRING_PTR, VOID_PTR}] = PTOP;
        convMap[{VOID_PTR, INT_PTR}] = PTOP; convMap[{VOID_PTR, DOUBLE_PTR}] = PTOP; convMap[{VOID_PTR, CHAR_PTR}] = PTOP;
        convMap[{VOID_PTR, BOOL_PTR}] = PTOP; convMap[{VOID_PTR, STRING_PTR}] = PTOP;
        convMap[{STRING, CHAR_PTR}] = STOP; convMap[{CHAR_PTR, STRING}] = PTOS;
        convMap[{NULL_PTR, INT_PTR}] = NTOP; convMap[{NULL_PTR, DOUBLE_PTR}] = NTOP; convMap[{NULL_PTR, CHAR_PTR}] = NTOP;
        convMap[{NULL_PTR, BOOL_PTR}] = NTOP; convMap[{NULL_PTR, STRING_PTR}] = NTOP; convMap[{NULL_PTR, VOID_PTR}] = NTOP;
    }

    string getOpcode(Type from, Type to) {
        auto it = convMap.find({from, to});
        if (it == convMap.end()) return "unknown";
        switch (it->second) {
            case ITOD: return "int_to_double"; case ITOC: return "int_to_char"; case ITOB: return "int_to_bool"; case ITOS: return "int_to_string";
            case DTOI: return "double_to_int"; case DTOC: return "double_to_char"; case DTOB: return "double_to_bool"; case DTOS: return "double_to_string";
            case CTOI: return "char_to_int"; case CTOD: return "char_to_double"; case CTOB: return "char_to_bool"; case CTOS: return "char_to_string";
            case BTOI: return "bool_to_int"; case BTOD: return "bool_to_double"; case BTOC: return "bool_to_char"; case BTOS: return "bool_to_string";
            case STOI: return "string_to_int"; case STOD: return "string_to_double"; case STOC: return "string_to_char"; case STOB: return "string_to_bool";
            case ITOP: return "int_to_ptr"; case PTOI: return "ptr_to_int"; case PTOB: return "ptr_to_bool"; case PTOP: return "ptr_to_ptr";
            case STOP: return "string_to_char_ptr"; case PTOS: return "char_ptr_to_string"; case NTOP: return "null_to_ptr";
            default: return "unknown";
        }
    }

public:
    TypeConvHandler() : tempCount(0) { initConvMaps(); }

    bool isPtr(Type t) { return t == INT_PTR || t == DOUBLE_PTR || t == CHAR_PTR || t == BOOL_PTR || t == STRING_PTR || t == VOID_PTR || t == NULL_PTR; }

    bool isValid(Type from, Type to) {
        if (from == to) return true;
        auto it = validConv.find(from);
        return it != validConv.end() && it->second.count(to) > 0;
    }

    string newTemp() { return "t" + to_string(++tempCount); }

    struct ConvResult {
        string resVar;
        vector<string> instr;
        vector<string> warn;
    };

    ConvResult genConv(const string& var, Type from, Type to, bool explicitCast = false) {
        ConvResult res;
        if (!isValid(from, to)) throw runtime_error("Invalid conversion");
        if (from == to) { res.resVar = var; return res; }
        if (!explicitCast) res.warn.push_back("Implicit conversion may be unsafe");
        res.resVar = newTemp();
        res.instr.push_back(res.resVar + " = " + getOpcode(from, to) + " " + var);
        return res;
    }

    vector<string> genAssign(const string& target, Type targetType, const string& src, Type srcType, bool explicitCast = false) {
        vector<string> instr;
        ConvResult conv = genConv(src, srcType, targetType, explicitCast);
        instr.insert(instr.end(), conv.instr.begin(), conv.instr.end());
        instr.push_back(target + " = " + conv.resVar);
        for (const auto& w : conv.warn) cerr << w << endl;
        return instr;
    }
};

// #endif // ENHANCED_TYPE_CONVERSION_H
