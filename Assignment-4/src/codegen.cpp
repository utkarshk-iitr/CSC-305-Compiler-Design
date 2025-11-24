#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdint>
#include <iomanip>
#include <limits>

using namespace std;

class CodeGenerator
{
private:
    vector<string> tac;
    vector<string> x86Code;
    unordered_map<string, int> labelMap;
    int tempCounter = 0;
    int pendingFloatExtraBytes = 0;

    enum class ValueType
    {
        Unknown,
        Int,
        Float,
        Pointer,
        Bool
    };

    unordered_map<string, ValueType> valueTypes;

    // Helper: Check if operand is a register
    bool isRegister(const string &s)
    {
        return s == "eax" || s == "ebx" || s == "ecx" || s == "edx" ||
               s == "esi" || s == "edi" || s == "esp" || s == "ebp" ||
               s == "al" || s == "bl" || s == "cl" || s == "dl";
    }

    // Helper: Check if operand is a memory reference
    bool isMemoryReference(const string &s)
    {
        return s.find("[") != string::npos && s.find("]") != string::npos;
    }

    // Helper: Check if operand is an immediate value
    bool isImmediate(const string &s)
    {
        if (s.empty())
            return false;

        // Check for character literal
        if (s.length() >= 3 && s[0] == '\'' && s[2] == '\'')
            return true;

        // Check for negative numbers
        size_t start = 0;
        if (s[0] == '-')
            start = 1;

        if (start >= s.length())
            return false;

        for (size_t i = start; i < s.length(); i++)
        {
            if (!isdigit(s[i]))
                return false;
        }
        return true;
    }

    // Helper: Trim whitespace from string
    string trim(const string &str)
    {
        size_t first = str.find_first_not_of(" \t\n\r");
        if (first == string::npos)
            return "";
        size_t last = str.find_last_not_of(" \t\n\r");
        string result = str.substr(first, last - first + 1);

        // Remove trailing semicolon if present
        if (!result.empty() && result.back() == ';')
        {
            result = result.substr(0, result.length() - 1);
            last = result.find_last_not_of(" \t\n\r");
            if (last != string::npos)
            {
                result = result.substr(0, last + 1);
            }
        }

        return result;
    }

    bool isAddressOperand(const string &s)
    {
        string trimmed = trim(s);
        return !trimmed.empty() && trimmed[0] == '&';
    }

    void loadAddressIntoRegister(const string &operand, const string &reg)
    {
        string trimmed = trim(operand);
        if (!trimmed.empty() && trimmed[0] == '&')
        {
            trimmed = trim(trimmed.substr(1));
        }

        string targetExpr;

        if (isMemoryReference(trimmed))
        {
            targetExpr = normalizeMemRef(trimmed);
        }
        else
        {
            string cleaned;
            for (char c : trimmed)
            {
                if (!isspace(static_cast<unsigned char>(c)))
                {
                    cleaned += c;
                }
            }

            if (cleaned.empty())
            {
                cleaned = trimmed;
            }

            if (!cleaned.empty() && cleaned.front() != '[')
            {
                targetExpr = "[" + cleaned + "]";
            }
            else
            {
                targetExpr = cleaned;
            }
        }

        emit("lea " + reg + ", " + targetExpr);
    }

    // Helper: Split string by delimiter
    vector<string> split(const string &str, char delimiter)
    {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimiter))
        {
            tokens.push_back(trim(token));
        }
        return tokens;
    }

    // Emit an instruction with proper indentation
    void emit(const string &instruction)
    {
        x86Code.push_back("    " + instruction);
    }

    // Emit a label (no indentation)
    void emitLabel(const string &label)
    {
        x86Code.push_back(label + ":");
    }

    // Emit a comment
    void emitComment(const string &comment)
    {
        x86Code.push_back("    ; " + comment);
    }

    // Process escape sequences in string literals for proper NASM syntax
    string processEscapeSequences(const string &str)
    {
        string result = str;

        // NASM escape sequence handling:
        // - Strings with backticks (`) support C-style escape sequences: \n, \t, \r, \\, etc.
        // - Strings with quotes (") do NOT interpret escape sequences
        // - We need to convert "string" to `string` for escape sequences to work

        // Find and replace string declarations
        size_t dbPos = result.find(" db ");
        if (dbPos != string::npos)
        {
            size_t start = result.find('"', dbPos);
            if (start != string::npos)
            {
                size_t end = result.find('"', start + 1);
                if (end != string::npos)
                {
                    // Check if the string contains escape sequences
                    string content = result.substr(start + 1, end - start - 1);
                    if (content.find('\\') != string::npos)
                    {
                        // Replace double quotes with backticks for escape sequence support
                        result[start] = '`';
                        result[end] = '`';
                    }
                }
            }
        }

        return result;
    }

    // Normalize memory reference: ensure proper format [base+offset] or [base-offset]
    string normalizeMemRef(const string &memRef)
    {
        string s = trim(memRef);
        if (!isMemoryReference(s))
            return s;

        // Extract content between brackets
        size_t start = s.find('[');
        size_t end = s.find(']');
        if (start == string::npos || end == string::npos)
            return s;

        string inside = s.substr(start + 1, end - start - 1);

        // Remove all spaces
        string result = "[";
        for (size_t i = 0; i < inside.length(); i++)
        {
            if (inside[i] != ' ' && inside[i] != '\t')
            {
                result += inside[i];
            }
        }
        result += "]";

        return result;
    }

    string canonicalizeOperand(const string &operand)
    {
        string trimmed = trim(operand);
        if (trimmed.empty())
            return trimmed;

        if (trimmed[0] == '*')
        {
            return "*" + canonicalizeOperand(trimmed.substr(1));
        }

        if (trimmed[0] == '&')
        {
            return "&" + canonicalizeOperand(trimmed.substr(1));
        }

        if (isMemoryReference(trimmed))
        {
            return normalizeMemRef(trimmed);
        }

        return trimmed;
    }

    bool isFloatLiteral(const string &value)
    {
        string trimmedValue = trim(value);
        if (trimmedValue.empty())
            return false;

        bool hasDecimal = trimmedValue.find('.') != string::npos;
        bool hasExponent = trimmedValue.find('e') != string::npos || trimmedValue.find('E') != string::npos;
        bool hasSuffix = !trimmedValue.empty() && (trimmedValue.back() == 'f' || trimmedValue.back() == 'F');

        if (!(hasDecimal || hasExponent || hasSuffix))
            return false;

        string candidate = trimmedValue;
        if (hasSuffix)
        {
            candidate.pop_back();
        }

        try
        {
            size_t processed = 0;
            stof(candidate, &processed);
            return processed == candidate.size();
        }
        catch (...)
        {
            return false;
        }
    }

    string floatLiteralToHex(const string &literal)
    {
        string trimmedValue = trim(literal);
        string candidate = trimmedValue;
        if (!candidate.empty() && (candidate.back() == 'f' || candidate.back() == 'F'))
        {
            candidate.pop_back();
        }

        float floatValue = 0.0f;
        try
        {
            floatValue = stof(candidate);
        }
        catch (...)
        {
            floatValue = 0.0f;
        }

        uint32_t bits = 0;
        memcpy(&bits, &floatValue, sizeof(float));

        stringstream ss;
        ss << "0x" << uppercase << hex << setw(8) << setfill('0') << bits;
        return ss.str();
    }

    ValueType detectLiteralType(const string &value)
    {
        string trimmedValue = trim(value);
        if (trimmedValue.empty())
            return ValueType::Unknown;

        if (trimmedValue == "true" || trimmedValue == "false")
            return ValueType::Bool;

        if (trimmedValue == "nullptr")
            return ValueType::Pointer;

        if (!trimmedValue.empty() && trimmedValue.front() == '\'' && trimmedValue.back() == '\'' && trimmedValue.size() >= 3)
            return ValueType::Int;

        if (isFloatLiteral(trimmedValue))
            return ValueType::Float;

        bool isNumeric = true;
        size_t start = (trimmedValue[0] == '-' || trimmedValue[0] == '+') ? 1 : 0;
        for (size_t i = start; i < trimmedValue.size(); i++)
        {
            if (!isdigit(static_cast<unsigned char>(trimmedValue[i])))
            {
                isNumeric = false;
                break;
            }
        }

        if (isNumeric && !trimmedValue.empty())
            return ValueType::Int;

        return ValueType::Unknown;
    }

    ValueType mergeTypes(ValueType existing, ValueType incoming)
    {
        if (incoming == ValueType::Unknown)
            return existing;
        if (existing == ValueType::Unknown)
            return incoming;
        if (existing == incoming)
            return existing;
        if (incoming == ValueType::Float)
            return ValueType::Float;
        return existing;
    }

    void setValueType(const string &operand, ValueType type)
    {
        if (type == ValueType::Unknown)
            return;

        string key = canonicalizeOperand(operand);
        if (key.empty())
            return;

        auto it = valueTypes.find(key);
        if (it == valueTypes.end())
        {
            valueTypes[key] = type;
        }
        else
        {
            it->second = mergeTypes(it->second, type);
        }
    }

    ValueType getValueType(const string &operand)
    {
        string key = canonicalizeOperand(operand);
        auto it = valueTypes.find(key);
        if (it != valueTypes.end())
            return it->second;

        if (!key.empty())
        {
            ValueType literalType = detectLiteralType(key);
            if (literalType != ValueType::Unknown)
                return literalType;
        }

        return ValueType::Unknown;
    }

    bool isFloatType(ValueType type)
    {
        return type == ValueType::Float;
    }

    void loadFloatIntoXmm(const string &operand, const string &xmmReg)
    {
        string trimmed = trim(operand);

        if (!trimmed.empty() && trimmed[0] == '*')
        {
            string addrOperand = trim(trimmed.substr(1));
            string normAddr = normalizeMemRef(addrOperand);
            emit("mov eax, " + normAddr);
            emit("movss " + xmmReg + ", [eax]");
            return;
        }

        string normOperand = normalizeMemRef(trimmed);

        if (isImmediate(normOperand) || detectLiteralType(normOperand) == ValueType::Float || isFloatLiteral(normOperand))
        {
            string hexValue = floatLiteralToHex(normOperand);
            emit("mov eax, " + hexValue);
            emit("movd " + xmmReg + ", eax");
        }
        else if (isMemoryReference(normOperand))
        {
            emit("movss " + xmmReg + ", " + normOperand);
        }
        else if (isRegister(normOperand))
        {
            emit("movd " + xmmReg + ", " + normOperand);
        }
        else
        {
            emit("movss " + xmmReg + ", [" + normOperand + "]");
        }
    }

    void storeXmmToOperand(const string &operand, const string &xmmReg)
    {
        string trimmed = trim(operand);

        if (!trimmed.empty() && trimmed[0] == '*')
        {
            string addrOperand = trim(trimmed.substr(1));
            string normAddr = normalizeMemRef(addrOperand);
            emit("mov eax, " + normAddr);
            emit("movss [eax], " + xmmReg);
            return;
        }

        string normDest = normalizeMemRef(trimmed);
        if (isMemoryReference(normDest))
        {
            emit("movss " + normDest + ", " + xmmReg);
        }
        else if (isRegister(normDest))
        {
            emit("movd " + normDest + ", " + xmmReg);
        }
        else
        {
            emit("movss [" + normDest + "], " + xmmReg);
        }
    }

    ValueType determineBinaryResultType(const string &operation, ValueType lhs, ValueType rhs)
    {
        if ((operation == "+" || operation == "-" || operation == "*" || operation == "/") &&
            (lhs == ValueType::Float || rhs == ValueType::Float))
        {
            return ValueType::Float;
        }

        if ((operation == "+" || operation == "-") &&
            ((lhs == ValueType::Pointer && rhs == ValueType::Int) ||
             (lhs == ValueType::Int && rhs == ValueType::Pointer)))
        {
            return ValueType::Pointer;
        }

        if (operation == "&&" || operation == "||" || operation == "==" || operation == "!=" ||
            operation == "<" || operation == ">" || operation == "<=" || operation == ">=")
        {
            return ValueType::Bool;
        }

        return ValueType::Int;
    }

    ValueType valueTypeFromName(const string &typeName)
    {
        string base = typeName;
        if (base.empty())
            return ValueType::Unknown;

        if (base.back() == '*')
            return ValueType::Pointer;

        if (base == "float")
            return ValueType::Float;
        if (base == "double")
            return ValueType::Float;
        if (base == "bool")
            return ValueType::Bool;

        return ValueType::Int;
    }

    bool classifyDataDeclaration(const string &trimmedLine, bool &isUninitialized)
    {
        if (trimmedLine.empty() || trimmedLine.back() == ':')
            return false;

        istringstream iss(trimmedLine);
        string symbol;
        string directive;
        if (!(iss >> symbol >> directive))
            return false;

        string directiveLower = directive;
        transform(directiveLower.begin(), directiveLower.end(), directiveLower.begin(), [](unsigned char c)
                  { return static_cast<char>(tolower(c)); });

        if (directiveLower.rfind("res", 0) == 0)
        {
            isUninitialized = true;
            return true;
        }

        static const vector<string> initializedDirectives = {"db", "dd", "dq", "dw"};
        if (find(initializedDirectives.begin(), initializedDirectives.end(), directiveLower) != initializedDirectives.end())
        {
            isUninitialized = false;
            return true;
        }

        return false;
    }

    // Handle mov instruction, dealing with memory-to-memory moves
    void handleMov(const string &dest, const string &src, const string &sizeHint = "dword")
    {
        ValueType destType = getValueType(dest);
        ValueType srcType = getValueType(src);

        if (isFloatType(destType) || isFloatType(srcType) || detectLiteralType(src) == ValueType::Float)
        {
            handleFloatMov(dest, src);
            return;
        }

        string normDest = normalizeMemRef(dest);
        string normSrc = normalizeMemRef(src);

        // Memory to memory - use eax as intermediate
        if (isMemoryReference(normDest) && isMemoryReference(normSrc))
        {
            emit("mov eax, " + normSrc);
            emit("mov " + normDest + ", eax");
        }
        else if (isMemoryReference(normDest) && !isRegister(normSrc) && !isImmediate(normSrc))
        {
            // Move to memory from non-register/non-immediate
            emit("mov eax, " + normSrc);
            emit("mov " + normDest + ", eax");
        }
        else if (isMemoryReference(normDest) && isImmediate(normSrc))
        {
            // Moving immediate to memory - need size specifier
            emit("mov " + sizeHint + " " + normDest + ", " + normSrc);
        }
        else
        {
            emit("mov " + normDest + ", " + normSrc);
        }
    }

    void handleFloatMov(const string &dest, const string &src)
    {
        string trimmedDest = trim(dest);
        string normDest = normalizeMemRef(trimmedDest);

        bool destIsDeref = !trimmedDest.empty() && trimmedDest[0] == '*';

        bool srcIsLiteral = detectLiteralType(src) == ValueType::Float || isFloatLiteral(src);

        if (srcIsLiteral)
        {
            string hexValue = floatLiteralToHex(src);
            if (destIsDeref)
            {
                string addrOperand = trim(trimmedDest.substr(1));
                string normAddr = normalizeMemRef(addrOperand);
                emit("mov eax, " + normAddr);
                emit("mov dword [eax], " + hexValue);
            }
            else if (isMemoryReference(normDest))
            {
                emit("mov dword " + normDest + ", " + hexValue);
            }
            else if (isRegister(normDest))
            {
                emit("mov eax, " + hexValue);
                emit("movd " + normDest + ", eax");
            }
            else
            {
                emit("mov dword [" + normDest + "], " + hexValue);
            }
            return;
        }

        loadFloatIntoXmm(src, "xmm0");
        storeXmmToOperand(dest, "xmm0");
    }

    void handleFloatBinaryOp(const string &dest, const string &op1,
                             const string &operation, const string &op2)
    {
        loadFloatIntoXmm(op1, "xmm0");
        loadFloatIntoXmm(op2, "xmm1");

        if (operation == "+")
        {
            emit("addss xmm0, xmm1");
        }
        else if (operation == "-")
        {
            emit("subss xmm0, xmm1");
        }
        else if (operation == "*")
        {
            emit("mulss xmm0, xmm1");
        }
        else if (operation == "/")
        {
            emit("divss xmm0, xmm1");
        }
        else
        {
            emitComment("Unsupported float operation: " + operation);
        }

        storeXmmToOperand(dest, "xmm0");
    }

    // Handle binary arithmetic/logical operations
    void handleBinaryOp(const string &dest, const string &op1,
                        const string &operation, const string &op2)
    {
        ValueType destType = getValueType(dest);
        ValueType op1Type = getValueType(op1);
        ValueType op2Type = getValueType(op2);

        if (isFloatType(destType) || isFloatType(op1Type) || isFloatType(op2Type))
        {
            handleFloatBinaryOp(dest, op1, operation, op2);
            return;
        }

        string normDest = normalizeMemRef(dest);
        string normOp1 = normalizeMemRef(op1);
        string normOp2 = normalizeMemRef(op2);

        if (operation == "+")
        {
            bool op1Address = isAddressOperand(op1);
            bool op2Address = isAddressOperand(op2);

            if (op1Address && op2Address)
            {
                loadAddressIntoRegister(op1, "eax");
                loadAddressIntoRegister(op2, "ebx");
                emit("add eax, ebx");
                handleMov(normDest, "eax");
                return;
            }
            else if (op1Address || op2Address)
            {
                bool baseIsOp1 = op1Address;
                const string &baseOperand = baseIsOp1 ? op1 : op2;
                string otherOperand = baseIsOp1 ? normOp2 : normOp1;

                loadAddressIntoRegister(baseOperand, "eax");

                if (!otherOperand.empty())
                {
                    if (isMemoryReference(otherOperand))
                    {
                        emit("mov ebx, " + otherOperand);
                        emit("add eax, ebx");
                    }
                    else
                    {
                        emit("add eax, " + otherOperand);
                    }
                }

                handleMov(normDest, "eax");
                return;
            }

            if (normOp1 == normDest)
            {
                if (isMemoryReference(normOp2))
                {
                    emit("mov ebx, " + normOp2);
                    if (isMemoryReference(normDest))
                    {
                        emit("add dword " + normDest + ", ebx");
                    }
                    else
                    {
                        emit("add " + normDest + ", ebx");
                    }
                }
                else if (isMemoryReference(normDest) && isImmediate(normOp2))
                {
                    emit("add dword " + normDest + ", " + normOp2);
                }
                else
                {
                    emit("add " + normDest + ", " + normOp2);
                }
            }
            else
            {
                // Load op1 into eax, do the operation, then store to dest
                emit("mov eax, " + normOp1);
                if (isMemoryReference(normOp2))
                {
                    emit("mov ebx, " + normOp2);
                    emit("add eax, ebx");
                }
                else
                {
                    emit("add eax, " + normOp2);
                }
                handleMov(normDest, "eax");
            }
        }
        else if (operation == "-")
        {
            if (normOp1 == normDest)
            {
                if (isMemoryReference(normOp2))
                {
                    emit("mov ebx, " + normOp2);
                    if (isMemoryReference(normDest))
                    {
                        emit("sub dword " + normDest + ", ebx");
                    }
                    else
                    {
                        emit("sub " + normDest + ", ebx");
                    }
                }
                else if (isMemoryReference(normDest) && isImmediate(normOp2))
                {
                    emit("sub dword " + normDest + ", " + normOp2);
                }
                else
                {
                    emit("sub " + normDest + ", " + normOp2);
                }
            }
            else
            {
                // Load op1 into eax, do the operation, then store to dest
                emit("mov eax, " + normOp1);
                if (isMemoryReference(normOp2))
                {
                    emit("mov ebx, " + normOp2);
                    emit("sub eax, ebx");
                }
                else
                {
                    emit("sub eax, " + normOp2);
                }
                handleMov(normDest, "eax");
            }
        }
        else if (operation == "*")
        {
            // Use imul for signed multiplication
            if (isImmediate(normOp2))
            {
                handleMov("eax", normOp1);
                emit("imul eax, eax, " + normOp2);
                handleMov(normDest, "eax");
            }
            else
            {
                handleMov("eax", normOp1);
                if (isMemoryReference(normOp2) || isRegister(normOp2))
                {
                    emit("imul eax, " + normOp2);
                }
                else
                {
                    handleMov("ebx", normOp2);
                    emit("imul eax, ebx");
                }
                handleMov(normDest, "eax");
            }
        }
        else if (operation == "/")
        {
            // idiv: quotient in eax
            handleMov("eax", normOp1);
            emit("cdq");
            if (isMemoryReference(normOp2) || isRegister(normOp2))
            {
                emit("idiv " + normOp2);
            }
            else
            {
                handleMov("ebx", normOp2);
                emit("idiv ebx");
            }
            handleMov(normDest, "eax");
        }
        else if (operation == "%")
        {
            // idiv: remainder in edx
            handleMov("eax", normOp1);
            emit("cdq");
            if (isMemoryReference(normOp2) || isRegister(normOp2))
            {
                emit("idiv " + normOp2);
            }
            else
            {
                handleMov("ebx", normOp2);
                emit("idiv ebx");
            }
            handleMov(normDest, "edx");
        }
        else if (operation == "&")
        {
            if (normOp1 == normDest)
            {
                emit("and " + normDest + ", " + normOp2);
            }
            else
            {
                handleMov(normDest, normOp1);
                emit("and " + normDest + ", " + normOp2);
            }
        }
        else if (operation == "|")
        {
            if (normOp1 == normDest)
            {
                emit("or " + normDest + ", " + normOp2);
            }
            else
            {
                handleMov(normDest, normOp1);
                emit("or " + normDest + ", " + normOp2);
            }
        }
        else if (operation == "^")
        {
            if (normOp1 == normDest)
            {
                emit("xor " + normDest + ", " + normOp2);
            }
            else
            {
                handleMov(normDest, normOp1);
                emit("xor " + normDest + ", " + normOp2);
            }
        }
        else if (operation == "<<")
        {
            handleMov(normDest, normOp1);
            if (isImmediate(normOp2))
            {
                emit("shl " + normDest + ", " + normOp2);
            }
            else
            {
                handleMov("ecx", normOp2);
                emit("shl " + normDest + ", cl");
            }
        }
        else if (operation == ">>")
        {
            handleMov(normDest, normOp1);
            if (isImmediate(normOp2))
            {
                emit("sar " + normDest + ", " + normOp2);
            }
            else
            {
                handleMov("ecx", normOp2);
                emit("sar " + normDest + ", cl");
            }
        }
        else if (operation == "==" || operation == "!=" ||
                 operation == "<" || operation == ">" ||
                 operation == "<=" || operation == ">=")
        {
            handleMov("eax", normOp1);
            if (isMemoryReference(normOp2))
            {
                emit("mov ebx, " + normOp2);
                emit("cmp eax, ebx");
            }
            else
            {
                emit("cmp eax, " + normOp2);
            }

            string setInstr;
            if (operation == "==")
                setInstr = "sete";
            else if (operation == "!=")
                setInstr = "setne";
            else if (operation == "<")
                setInstr = "setl";
            else if (operation == ">")
                setInstr = "setg";
            else if (operation == "<=")
                setInstr = "setle";
            else if (operation == ">=")
                setInstr = "setge";

            emit(setInstr + " al");
            emit("movzx eax, al");
            handleMov(normDest, "eax");
        }
        else if (operation == "&&")
        {
            // Logical AND
            handleMov("eax", normOp1);
            emit("test eax, eax");
            emit("setne al");
            handleMov("ebx", normOp2);
            emit("test ebx, ebx");
            emit("setne bl");
            emit("and al, bl");
            emit("movzx eax, al");
            handleMov(normDest, "eax");
        }
        else if (operation == "||")
        {
            // Logical OR
            handleMov("eax", normOp1);
            emit("test eax, eax");
            emit("setne al");
            handleMov("ebx", normOp2);
            emit("test ebx, ebx");
            emit("setne bl");
            emit("or al, bl");
            emit("movzx eax, al");
            handleMov(normDest, "eax");
        }
    }

    // Handle unary operations
    void handleUnaryOp(const string &line)
    {
        string trimmedLine = trim(line);

        // Negation: dest = -src or dest = 0 - src
        if (trimmedLine.find(" = -") != string::npos || trimmedLine.find(" = 0 - ") != string::npos)
        {
            size_t eqPos = trimmedLine.find(" = ");
            string destRaw = trim(trimmedLine.substr(0, eqPos));
            string rhs = trim(trimmedLine.substr(eqPos + 3));

            if (rhs.find(" - ") != string::npos)
            {
                // Format: dest = 0 - src
                size_t minusPos = rhs.find(" - ");
                string srcRaw = trim(rhs.substr(minusPos + 3));
                ValueType destType = getValueType(destRaw);
                ValueType srcType = getValueType(srcRaw);

                if (srcType != ValueType::Unknown)
                {
                    setValueType(destRaw, srcType);
                    destType = mergeTypes(destType, srcType);
                }

                if (isFloatType(destType) || isFloatType(srcType) || detectLiteralType(srcRaw) == ValueType::Float)
                {
                    loadFloatIntoXmm(srcRaw, "xmm0");
                    emit("mov eax, 0x80000000");
                    emit("movd xmm1, eax");
                    emit("xorps xmm0, xmm1");
                    storeXmmToOperand(destRaw, "xmm0");
                }
                else
                {
                    string dest = normalizeMemRef(destRaw);
                    string src = normalizeMemRef(srcRaw);
                    handleMov(dest, src);
                    emit("neg " + dest);
                }
            }
            else if (rhs[0] == '-')
            {
                // Format: dest = -src
                string srcRaw = trim(rhs.substr(1));
                ValueType destType = getValueType(destRaw);
                ValueType srcType = getValueType(srcRaw);

                if (srcType != ValueType::Unknown)
                {
                    setValueType(destRaw, srcType);
                    destType = mergeTypes(destType, srcType);
                }

                if (isFloatType(destType) || isFloatType(srcType) || detectLiteralType(srcRaw) == ValueType::Float)
                {
                    loadFloatIntoXmm(srcRaw, "xmm0");
                    emit("mov eax, 0x80000000");
                    emit("movd xmm1, eax");
                    emit("xorps xmm0, xmm1");
                    storeXmmToOperand(destRaw, "xmm0");
                }
                else
                {
                    string dest = normalizeMemRef(destRaw);
                    string src = normalizeMemRef(srcRaw);
                    handleMov(dest, src);
                    emit("neg " + dest);
                }
            }
        }
        // Bitwise NOT: dest = ~src
        else if (trimmedLine.find(" = ~") != string::npos)
        {
            size_t eqPos = trimmedLine.find(" = ~");
            string dest = normalizeMemRef(trim(trimmedLine.substr(0, eqPos)));
            string src = normalizeMemRef(trim(trimmedLine.substr(eqPos + 4)));

            handleMov(dest, src);
            emit("not " + dest);
        }
        // Logical NOT: dest = !src
        else if (trimmedLine.find(" = !") != string::npos)
        {
            size_t eqPos = trimmedLine.find(" = !");
            string dest = normalizeMemRef(trim(trimmedLine.substr(0, eqPos)));
            string src = normalizeMemRef(trim(trimmedLine.substr(eqPos + 4)));

            handleMov("eax", src);
            emit("test eax, eax");
            emit("sete al");
            emit("movzx eax, al");
            handleMov(dest, "eax");
        }
    }

    // Handle type conversion: dest = type1_to_type2 src
    void handleTypeConversion(const string &line)
    {
        string trimmedLine = trim(line);
        size_t eqPos = trimmedLine.find(" = ");
        if (eqPos == string::npos)
            return;

        string destRaw = trim(trimmedLine.substr(0, eqPos));
        string rhs = trim(trimmedLine.substr(eqPos + 3));

        // Find the conversion pattern: type1_to_type2 src
        size_t spacePos = rhs.find(' ');
        if (spacePos == string::npos)
            return;

        string conversion = trim(rhs.substr(0, spacePos));
        string srcRaw = trim(rhs.substr(spacePos + 1));
        string dest = normalizeMemRef(destRaw);
        string src = normalizeMemRef(srcRaw);

        size_t arrowPos = conversion.find("_to_");
        string fromType = arrowPos != string::npos ? conversion.substr(0, arrowPos) : "";
        string toType = arrowPos != string::npos ? conversion.substr(arrowPos + 4) : "";

        ValueType targetType = valueTypeFromName(toType);
        ValueType sourceType = valueTypeFromName(fromType);
        if (targetType != ValueType::Unknown)
            setValueType(destRaw, targetType);
        if (sourceType != ValueType::Unknown)
            setValueType(srcRaw, sourceType);

        if (!toType.empty() && toType.back() == '*')
        {
            string baseTypeName = toType;
            while (!baseTypeName.empty() && baseTypeName.back() == '*')
            {
                baseTypeName.pop_back();
            }
            ValueType elementType = valueTypeFromName(baseTypeName);
            if (elementType != ValueType::Unknown)
            {
                setValueType("*" + canonicalizeOperand(destRaw), elementType);
            }
        }

        // For now, simple conversions just move the value
        // char_to_int: sign-extend byte to dword
        if (conversion.find("char_to_int") != string::npos)
        {
            handleMov("al", src);
            emit("movsx eax, al");
            handleMov(dest, "eax");
        }
        else if (conversion.find("int_to_float") != string::npos)
        {
            handleMov("eax", src);
            emit("cvtsi2ss xmm0, eax");
            storeXmmToOperand(destRaw, "xmm0");
        }
        else if (conversion.find("float_to_int") != string::npos)
        {
            loadFloatIntoXmm(srcRaw, "xmm0");
            emit("cvttss2si eax, xmm0");
            handleMov(dest, "eax");
        }
        else
        {
            // Default: just move
            handleMov(dest, src);
        }
    }

    // Handle address-of: dest = &src
    void handleAddressOf(const string &dest, const string &src)
    {
        string normDest = normalizeMemRef(dest);
        string trimmedSrc = trim(src);

        if (!trimmedSrc.empty() && trimmedSrc[0] == '*')
        {
            string inner = trim(trimmedSrc.substr(1));
            string normInner = normalizeMemRef(inner);

            handleMov("eax", normInner);
            handleMov(normDest, "eax");
            setValueType(dest, ValueType::Pointer);

            ValueType elementType = getValueType(trimmedSrc);
            if (elementType != ValueType::Unknown)
            {
                setValueType("*" + canonicalizeOperand(dest), elementType);
            }
            return;
        }

        string addrSrc = trimmedSrc;

        // If src is a memory reference, extract the address expression
        if (isMemoryReference(trimmedSrc))
        {
            size_t start = trimmedSrc.find('[');
            size_t end = trimmedSrc.find(']');
            if (start != string::npos && end != string::npos)
            {
                addrSrc = trimmedSrc.substr(start + 1, end - start - 1);
                // Remove all spaces
                string cleaned;
                for (char c : addrSrc)
                {
                    if (c != ' ' && c != '\t')
                        cleaned += c;
                }
                addrSrc = cleaned;
            }
        }

        emit("lea eax, [" + addrSrc + "]");
        handleMov(normDest, "eax");
        setValueType(dest, ValueType::Pointer);
    }

    // Handle dereference: dest = *src
    void handleDereference(const string &dest, const string &src)
    {
        string destRaw = trim(dest);
        string srcRaw = trim(src);
        string normSrc = normalizeMemRef(srcRaw);
        ValueType destType = getValueType(destRaw);
        ValueType pointerValueType = getValueType("*" + srcRaw);
        if (pointerValueType != ValueType::Unknown)
        {
            setValueType(destRaw, pointerValueType);
            destType = mergeTypes(destType, pointerValueType);
        }

        handleMov("eax", normSrc);

        if (isFloatType(destType))
        {
            emit("movss xmm0, [eax]");
            storeXmmToOperand(destRaw, "xmm0");
        }
        else
        {
            emit("mov eax, [eax]");
            handleMov(normalizeMemRef(destRaw), "eax");
        }
    }

    // Handle conditional jumps
    void handleConditionalJump(const string &line)
    {
        string trimmedLine = trim(line);

        // ifFalse condition goto label
        if (trimmedLine.find("ifFalse") == 0)
        {
            size_t gotoPos = trimmedLine.find(" goto ");
            if (gotoPos == string::npos)
                return;

            string condition = normalizeMemRef(trim(trimmedLine.substr(8, gotoPos - 8)));
            string label = trim(trimmedLine.substr(gotoPos + 6));

            handleMov("eax", condition);
            emit("test eax, eax");
            emit("jz " + label);
        }
        // if condition == value goto label
        else if (trimmedLine.find("if ") == 0 && trimmedLine.find(" == ") != string::npos)
        {
            size_t eqPos = trimmedLine.find(" == ");
            size_t gotoPos = trimmedLine.find(" goto ");
            if (gotoPos == string::npos)
                return;

            string condition = normalizeMemRef(trim(trimmedLine.substr(3, eqPos - 3)));
            string value = normalizeMemRef(trim(trimmedLine.substr(eqPos + 4, gotoPos - eqPos - 4)));
            string label = trim(trimmedLine.substr(gotoPos + 6));

            handleMov("eax", condition);
            emit("cmp eax, " + value);
            emit("je " + label);
        }
        // if condition goto label (for "until" loops)
        else if (trimmedLine.find("if ") == 0 && trimmedLine.find(" goto ") != string::npos)
        {
            size_t gotoPos = trimmedLine.find(" goto ");
            string condition = normalizeMemRef(trim(trimmedLine.substr(3, gotoPos - 3)));
            string label = trim(trimmedLine.substr(gotoPos + 6));

            handleMov("eax", condition);
            emit("test eax, eax");
            emit("jnz " + label);
        }
    }

    // Handle function calls
    void handleFunctionCall(const string &line)
    {
        string trimmedLine = trim(line);

        // Find where "call" appears
        size_t callPos = trimmedLine.find(" call ");
        bool startsWithCall = (trimmedLine.find("call ") == 0);

        if (callPos == string::npos && !startsWithCall)
            return;

        bool hasReturn = (callPos != string::npos && callPos > 0);
        string dest;
        string destRaw;

        if (hasReturn)
        {
            size_t eqPos = trimmedLine.find(" = ");
            destRaw = trim(trimmedLine.substr(0, eqPos));
            dest = normalizeMemRef(destRaw);
            callPos = trimmedLine.find(" call ");
        }
        else
        {
            callPos = 0; // Position where "call " starts
        }

        // Extract function name
        size_t funcStart;
        if (hasReturn)
        {
            funcStart = callPos + 6; // After " call " (6 characters: space+call+space)
        }
        else
        {
            funcStart = 5; // After "call "
        }

        size_t commaPos = trimmedLine.find(",", funcStart);
        size_t semicolonPos = trimmedLine.find(";", funcStart);

        string funcName;
        if (commaPos != string::npos)
        {
            funcName = trimmedLine.substr(funcStart, commaPos - funcStart);
        }
        else if (semicolonPos != string::npos)
        {
            funcName = trimmedLine.substr(funcStart, semicolonPos - funcStart);
        }
        else
        {
            funcName = trimmedLine.substr(funcStart);
        }

        funcName = trim(funcName);

        emit("call " + funcName);

        if (hasReturn && !dest.empty())
        {
            if (getValueType(destRaw) == ValueType::Unknown)
            {
                setValueType(destRaw, ValueType::Int);
            }
            handleMov(dest, "eax");
        }
    }

    // Handle parameter passing
    void handleParam(const string &line)
    {
        string trimmedLine = trim(line);

        // Pattern: param dest, value
        if (trimmedLine.find("param") == 0)
        {
            size_t commaPos = trimmedLine.find(",");
            if (commaPos == string::npos)
                return;

            string dest = normalizeMemRef(trim(trimmedLine.substr(6, commaPos - 6)));
            string valueRaw = trim(trimmedLine.substr(commaPos + 1));

            // Handle dereference in parameter: *[ebp - offset]
            if (valueRaw.length() > 0 && valueRaw[0] == '*')
            {
                string addrRaw = trim(valueRaw.substr(1));
                string addr = normalizeMemRef(addrRaw);
                string canonicalAddr = canonicalizeOperand(addrRaw);
                string pointerKey = "*" + canonicalAddr;
                ValueType derefType = getValueType(valueRaw);
                if (derefType == ValueType::Unknown)
                {
                    derefType = getValueType(pointerKey);
                }
                if (derefType == ValueType::Unknown)
                {
                    ValueType basePointerType = getValueType(canonicalAddr);
                    if (basePointerType == ValueType::Pointer || basePointerType == ValueType::Unknown)
                    {
                        derefType = ValueType::Float;
                        setValueType(valueRaw, ValueType::Float);
                        setValueType(pointerKey, ValueType::Float);
                    }
                }

                handleMov("eax", addr);

                if (isFloatType(derefType))
                {
                    emit("sub esp, 8");
                    emit("movss xmm0, [eax]");
                    emit("cvtss2sd xmm0, xmm0");
                    emit("movsd [esp], xmm0");
                    pendingFloatExtraBytes += 4;
                }
                else
                {
                    emit("mov eax, [eax]");
                    emit("push eax");
                }
                return;
            }

            ValueType valueType = getValueType(valueRaw);
            bool treatAsFloat = isFloatType(valueType) || detectLiteralType(valueRaw) == ValueType::Float || isFloatLiteral(valueRaw);

            string value = normalizeMemRef(valueRaw);

            if (treatAsFloat)
            {
                emit("sub esp, 8");
                loadFloatIntoXmm(valueRaw, "xmm0");
                emit("cvtss2sd xmm0, xmm0");
                emit("movsd [esp], xmm0");
                pendingFloatExtraBytes += 4;
            }
            else
            {
                // Push parameter onto stack
                if (isImmediate(value) || isRegister(value))
                {
                    emit("push " + value);
                }
                else
                {
                    handleMov("eax", value);
                    emit("push eax");
                }
            }
        }
    }

    // Handle lea instruction
    void handleLea(const string &line)
    {
        string trimmedLine = trim(line);

        // Pattern: lea dest, src
        if (trimmedLine.find("lea ") != 0)
            return;

        size_t commaPos = trimmedLine.find(",");
        if (commaPos == string::npos)
            return;

        string dest = trim(trimmedLine.substr(4, commaPos - 4));
        string src = trim(trimmedLine.substr(commaPos + 1));

        // Normalize the source memory reference
        src = normalizeMemRef(src);

        emit("lea " + dest + ", " + src);
    }

    // Find operator position outside of brackets
    int findOperatorOutsideBrackets(const string &str, const string &op)
    {
        int bracketDepth = 0;

        for (size_t i = 0; i < str.length(); i++)
        {
            if (str[i] == '[')
                bracketDepth++;
            else if (str[i] == ']')
                bracketDepth--;
            else if (bracketDepth == 0 && i + op.length() <= str.length())
            {
                if (str.substr(i, op.length()) == op)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    // Parse simple assignment: dest = src (no operators outside brackets)
    bool parseSimpleAssignment(const string &line, string &dest, string &src)
    {
        size_t eqPos = line.find(" = ");
        if (eqPos == string::npos)
            return false;

        dest = trim(line.substr(0, eqPos));
        src = trim(line.substr(eqPos + 3));

        // Check if there are operators outside of brackets
        vector<string> operators = {" + ", " - ", " * ", " / ", " % ", " & ", " | ", " ^ ",
                                    " << ", " >> ", " == ", " != ", " < ", " > ", " <= ", " >= ",
                                    " && ", " || ", "_to_"};

        for (const auto &op : operators)
        {
            if (findOperatorOutsideBrackets(src, op) >= 0)
            {
                return false;
            }
        }

        return true;
    }

    // Parse binary operation: dest = op1 operator op2
    bool parseBinaryOp(const string &line, string &dest, string &op1,
                       string &operation, string &op2)
    {
        size_t eqPos = line.find(" = ");
        if (eqPos == string::npos)
            return false;

        dest = trim(line.substr(0, eqPos));
        string rhs = trim(line.substr(eqPos + 3));

        // Check for various operators (longer operators first)
        vector<string> operators = {" == ", " != ", " <= ", " >= ", " << ", " >> ",
                                    " && ", " || ",
                                    " < ", " > ", " + ", " - ", " * ", " / ", " % ",
                                    " & ", " | ", " ^ "};

        for (const auto &op : operators)
        {
            int opPos = findOperatorOutsideBrackets(rhs, op);
            if (opPos >= 0)
            {
                op1 = trim(rhs.substr(0, opPos));
                operation = trim(op);
                op2 = trim(rhs.substr(opPos + op.length()));

                // Make sure we got valid operands
                if (!op1.empty() && !op2.empty())
                {
                    return true;
                }
            }
        }

        return false;
    }

    // Process a single TAC line
    void processLine(const string &line)
    {
        string trimmedLine = trim(line);

        if (trimmedLine.empty())
            return;

        // Labels
        if (trimmedLine.back() == ':')
        {
            emitLabel(trimmedLine.substr(0, trimmedLine.length() - 1));
            return;
        }

        // Data section declarations
        if ((trimmedLine.find(" db ") != string::npos ||
             trimmedLine.find(" resd ") != string::npos ||
             trimmedLine.find(" resb ") != string::npos ||
             trimmedLine.find(" resq ") != string::npos ||
             trimmedLine.find(" dd ") != string::npos) &&
            trimmedLine.back() != ':')
        {
            // Process escape sequences in string literals
            string processedLine = processEscapeSequences(trimmedLine);
            x86Code.push_back("    " + processedLine);
            return;
        }

        // Direct x86 instructions
        if (trimmedLine.find("push") == 0 || trimmedLine.find("pop") == 0 ||
            trimmedLine.find("mov ebp") == 0 || trimmedLine.find("mov esp") == 0)
        {
            emit(trimmedLine);
            return;
        }

        // Stack adjustment
        if (trimmedLine.find("add esp") == 0)
        {
            size_t commaPos = trimmedLine.find(",");
            int amount = 0;
            if (commaPos != string::npos)
            {
                string amountStr = trim(trimmedLine.substr(commaPos + 1));
                amount = stoi(amountStr);
            }
            amount += pendingFloatExtraBytes;
            emit("add esp, " + to_string(amount));
            pendingFloatExtraBytes = 0;
            return;
        }

        if (trimmedLine.find("sub esp") == 0)
        {
            emit(trimmedLine);
            return;
        }

        // lea instruction
        if (trimmedLine.find("lea ") == 0)
        {
            handleLea(trimmedLine);
            return;
        }

        // Return statement
        if (trimmedLine.find("return") == 0)
        {
            string retVal = trim(trimmedLine.substr(6));
            if (!retVal.empty() && retVal != "0")
            {
                handleMov("eax", retVal);
            }
            else if (retVal == "0")
            {
                emit("xor eax, eax");
            }
            emit("mov esp, ebp");
            emit("pop ebp");
            emit("ret");
            return;
        }

        // Goto statement
        if (trimmedLine.find("goto") == 0)
        {
            string label = trim(trimmedLine.substr(4));
            emit("jmp " + label);
            return;
        }

        // Conditional jumps
        if (trimmedLine.find("ifFalse") == 0 ||
            (trimmedLine.find("if ") == 0 && trimmedLine.find(" goto ") != string::npos))
        {
            handleConditionalJump(trimmedLine);
            return;
        }

        // Parameter passing
        if (trimmedLine.find("param") == 0)
        {
            handleParam(trimmedLine);
            return;
        }

        // Function calls
        if (trimmedLine.find(" call ") != string::npos || trimmedLine.find("call ") == 0)
        {
            handleFunctionCall(trimmedLine);
            return;
        }

        // Assignment operations
        string dest, src, op1, operation, op2;

        // Check for dereference assignment: *ptr = value
        if (trimmedLine.length() > 0 && trimmedLine[0] == '*')
        {
            size_t eqPos = trimmedLine.find(" = ");
            if (eqPos != string::npos)
            {
                // Extract pointer and value
                string ptrOperand = trim(trimmedLine.substr(1, eqPos - 1));
                string ptrAddr = normalizeMemRef(ptrOperand);
                string value = trim(trimmedLine.substr(eqPos + 3));

                // Load the address from ptrAddr
                handleMov("eax", ptrAddr);

                // Load or prepare the value
                ValueType valueType = getValueType(value);
                ValueType literalType = detectLiteralType(value);
                ValueType storedType = literalType != ValueType::Unknown ? literalType : valueType;
                string canonicalPtr = canonicalizeOperand(ptrOperand);
                if (storedType != ValueType::Unknown)
                {
                    setValueType("*" + canonicalPtr, storedType);
                    setValueType("*" + canonicalizeOperand(ptrAddr), storedType);
                }

                if (literalType == ValueType::Float || isFloatType(valueType))
                {
                    if (literalType == ValueType::Float)
                    {
                        string hexValue = floatLiteralToHex(value);
                        emit("mov dword [eax], " + hexValue);
                    }
                    else
                    {
                        loadFloatIntoXmm(value, "xmm0");
                        emit("movss [eax], xmm0");
                    }
                }
                else if (isImmediate(value))
                {
                    emit("mov dword [eax], " + value);
                }
                else
                {
                    string normValue = normalizeMemRef(value);
                    handleMov("ebx", normValue);
                    emit("mov [eax], ebx");
                }
                return;
            }
        }

        // Address-of: dest = &src
        if (trimmedLine.find(" = &") != string::npos)
        {
            size_t eqPos = trimmedLine.find(" = &");
            string afterAmp = trim(trimmedLine.substr(eqPos + 4));

            vector<string> opsToCheck = {" + ", " - ", " * ", " / ", " % ", " & ", " | ", " ^ ",
                                         " << ", " >> ", " == ", " != ", " < ", " > ", " <= ", " >= ",
                                         " && ", " || "};

            bool simpleAddress = true;
            for (const auto &op : opsToCheck)
            {
                if (findOperatorOutsideBrackets(afterAmp, op) >= 0)
                {
                    simpleAddress = false;
                    break;
                }
            }

            if (simpleAddress)
            {
                dest = trim(trimmedLine.substr(0, eqPos));
                src = afterAmp;
                handleAddressOf(dest, src);
                return;
            }
        }

        // Dereference: dest = *src (but not multiplication)
        if (trimmedLine.find(" = *") != string::npos)
        {
            size_t eqPos = trimmedLine.find(" = *");
            string afterEq = trim(trimmedLine.substr(eqPos + 4));

            // Check if it's actually a dereference (not multiplication)
            // If there's a space after *, it's likely multiplication
            if (afterEq.find(" ") == string::npos || afterEq.find("*") == string::npos)
            {
                dest = trim(trimmedLine.substr(0, eqPos));
                src = afterEq;
                handleDereference(dest, src);
                return;
            }
        }

        // Type conversion: dest = type1_to_type2 src
        if (trimmedLine.find("_to_") != string::npos)
        {
            handleTypeConversion(trimmedLine);
            return;
        }

        // Unary operations: negation, NOT, etc.
        if ((trimmedLine.find(" = -") != string::npos && findOperatorOutsideBrackets(trimmedLine, " - ") < 0) ||
            trimmedLine.find(" = 0 - ") != string::npos ||
            trimmedLine.find(" = ~") != string::npos ||
            trimmedLine.find(" = !") != string::npos)
        {
            handleUnaryOp(trimmedLine);
            return;
        }

        // Binary operations
        if (parseBinaryOp(trimmedLine, dest, op1, operation, op2))
        {
            ValueType op1Type = getValueType(op1);
            ValueType op2Type = getValueType(op2);
            ValueType resultType = determineBinaryResultType(operation, op1Type, op2Type);
            setValueType(dest, resultType);
            if (resultType == ValueType::Pointer)
            {
                ValueType pointedType = getValueType("*" + canonicalizeOperand(op1));
                if (pointedType == ValueType::Unknown)
                {
                    pointedType = getValueType("*" + canonicalizeOperand(op2));
                }
                if (pointedType != ValueType::Unknown)
                {
                    setValueType("*" + canonicalizeOperand(dest), pointedType);
                }
            }
            handleBinaryOp(dest, op1, operation, op2);
            return;
        }

        // Simple assignment
        if (parseSimpleAssignment(trimmedLine, dest, src))
        {
            ValueType srcType = getValueType(src);
            if (srcType == ValueType::Unknown)
            {
                srcType = detectLiteralType(src);
            }
            setValueType(dest, srcType);
            if (srcType == ValueType::Pointer)
            {
                ValueType elementType = getValueType("*" + canonicalizeOperand(src));
                if (elementType != ValueType::Unknown)
                {
                    setValueType("*" + canonicalizeOperand(dest), elementType);
                }
            }
            handleMov(dest, src);
            return;
        }

        // If we can't parse it, emit as comment for debugging
        emitComment("Unparsed: " + trimmedLine);
    }

public:
    CodeGenerator(const vector<string> &tacCode) : tac(tacCode) {}

    void generate()
    {
        vector<string> uninitializedGlobals;
        vector<string> initializedGlobals;

        // First pass: collect data declarations
        for (const auto &line : tac)
        {
            string trimmedLine = trim(line);
            if (trimmedLine.empty())
                continue;

            bool isUninitialized = false;
            if (classifyDataDeclaration(trimmedLine, isUninitialized))
            {
                string processedLine = processEscapeSequences(trimmedLine);
                if (isUninitialized)
                {
                    uninitializedGlobals.push_back(processedLine);
                }
                else
                {
                    initializedGlobals.push_back(processedLine);
                }
            }
        }

        bool hasBss = !uninitializedGlobals.empty();
        bool hasData = !initializedGlobals.empty();

        if (hasBss)
        {
            x86Code.push_back("section .bss");
            for (const auto &line : uninitializedGlobals)
            {
                x86Code.push_back("    " + line);
            }
        }

        if (hasData)
        {
            if (hasBss)
            {
                x86Code.push_back("");
            }
            x86Code.push_back("section .data");
            for (const auto &line : initializedGlobals)
            {
                x86Code.push_back("    " + line);
            }
        }
        else if (!hasBss)
        {
            x86Code.push_back("section .data");
            x86Code.push_back("    ; No global data");
        }

        // Add text section
        x86Code.push_back("");
        x86Code.push_back("section .text");
        x86Code.push_back("    global main");
        x86Code.push_back("    extern printf");
        x86Code.push_back("    extern scanf");
        x86Code.push_back("    extern malloc");
        x86Code.push_back("    extern free");
        x86Code.push_back("    extern nullptr");
        x86Code.push_back("");

        // Second pass: emit code section
        vector<string> paramStack; // Collect parameters to push in reverse

        for (size_t i = 0; i < tac.size(); i++)
        {
            string trimmedLine = trim(tac[i]);

            // Skip data declarations in code section
            bool isUninitialized = false;
            if (classifyDataDeclaration(trimmedLine, isUninitialized))
            {
                continue;
            }

            // Skip "sub esp" if followed by param (directly or after more sub esp)
            if (trimmedLine.find("sub esp") == 0)
            {
                // Look ahead to see if there's a param coming
                bool foundParam = false;
                for (size_t j = i + 1; j < tac.size() && j < i + 10; j++)
                {
                    string lookAhead = trim(tac[j]);
                    if (lookAhead.find("param") == 0)
                    {
                        foundParam = true;
                        break;
                    }
                    // Stop looking if we hit something that's not sub esp
                    if (lookAhead.find("sub esp") != 0 && !lookAhead.empty())
                    {
                        break;
                    }
                }

                if (foundParam)
                {
                    continue; // Skip this sub esp (don't track amount)
                }
            }

            // Collect parameters until we hit a call instruction
            if (trimmedLine.find("param") == 0)
            {
                // Store parameter for later (will push in reverse order)
                paramStack.push_back(tac[i]);
                continue;
            }

            // When we hit a call, push all collected params in reverse order
            if (trimmedLine.find(" call ") != string::npos || trimmedLine.find("call ") == 0)
            {
                // Push parameters in reverse order (right-to-left for x86)
                for (int j = paramStack.size() - 1; j >= 0; j--)
                {
                    processLine(paramStack[j]);
                }
                paramStack.clear();

                // Now process the call
                processLine(tac[i]);
                continue;
            }

            processLine(tac[i]);
        }
    }

    void writeToFile(const string &filename)
    {
        ofstream outFile(filename);
        if (!outFile.is_open())
        {
            cerr << "Error: Cannot open output file " << filename << endl;
            return;
        }

        for (const auto &line : x86Code)
        {
            outFile << line << endl;
        }

        outFile.close();
        cout << "x86 assembly code generated successfully: " << filename << endl;
    }

    void printCode()
    {
        for (const auto &line : x86Code)
        {
            cout << line << endl;
        }
    }
};

extern "C"
{
    void run_code_gen(vector<string> &tacCode);
}

void run_code_gen(vector<string> &tacCode)
{
    CodeGenerator codeGen(tacCode);
    codeGen.generate();
    codeGen.printCode();
}

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//     {
//         cerr << "Usage: " << argv[0] << " <input_tac_file> [output_asm_file]" << endl;
//         return 1;
//     }

//     string inputFile = argv[1];
//     string outputFile = (argc >= 3) ? argv[2] : "output.asm";

//     // Read TAC file
//     ifstream inFile(inputFile);
//     if (!inFile.is_open())
//     {
//         cerr << "Error: Cannot open input file " << inputFile << endl;
//         return 1;
//     }

//     vector<string> tacCode;
//     string line;
//     while (getline(inFile, line))
//     {
//         tacCode.push_back(line);
//     }
//     inFile.close();

//     // Generate x86 code
//     CodeGenerator codeGen(tacCode);
//     codeGen.generate();
//     codeGen.writeToFile(outputFile);

//     return 0;
// }