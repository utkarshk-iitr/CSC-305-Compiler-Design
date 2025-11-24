#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct VarInfo {
    bool live = false;
    int nextUse = -1;
};

struct Instruction {
    enum class Kind {
        Binary,
        Unary,
        Copy,
        Print,
        If,
        Goto,
        Return,
        Label,
        Other
    };

    std::string original;
    std::string result;
    std::vector<std::string> uses;
    Kind kind = Kind::Other;
    bool dead = false;

    bool isAssignment() const {
        return kind == Kind::Binary || kind == Kind::Unary || kind == Kind::Copy;
    }
};

struct Annotation {
    std::vector<std::pair<std::string, VarInfo>> vars;
};

static std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

static bool isNumber(const std::string &token) {
    if (token.empty())
        return false;
    size_t idx = (token[0] == '-') ? 1 : 0;
    if (idx == token.size())
        return false;
    for (; idx < token.size(); ++idx) {
        if (!std::isdigit(static_cast<unsigned char>(token[idx])))
            return false;
    }
    return true;
}

static std::vector<std::string> split(const std::string &s) {
    std::vector<std::string> tokens;
    std::istringstream iss(s);
    std::string tok;
    while (iss >> tok) {
        tokens.push_back(tok);
    }
    return tokens;
}

static Instruction parseInstruction(const std::string &line) {
    Instruction inst;
    inst.original = line;
    std::string trimmed = trim(line);

    if (trimmed.empty()) {
        return inst;
    }

    if (trimmed.back() == ':') {
        inst.kind = Instruction::Kind::Label;
        return inst;
    }

    if (trimmed.rfind("goto", 0) == 0) {
        inst.kind = Instruction::Kind::Goto;
        return inst;
    }

    if (trimmed.rfind("return", 0) == 0) {
        inst.kind = Instruction::Kind::Return;
        auto tokens = split(trimmed);
        if (tokens.size() > 1) {
            inst.uses.push_back(tokens[1]);
        }
        return inst;
    }

    if (trimmed.rfind("print", 0) == 0) {
        inst.kind = Instruction::Kind::Print;
        auto tokens = split(trimmed);
        for (size_t i = 1; i < tokens.size(); ++i) {
            inst.uses.push_back(tokens[i]);
        }
        return inst;
    }

    if (trimmed.rfind("if", 0) == 0) {
        inst.kind = Instruction::Kind::If;
        auto tokens = split(trimmed);
        for (size_t i = 1; i < tokens.size(); ++i) {
            if (tokens[i] == "goto")
                break;
            if (tokens[i] == "<" || tokens[i] == ">" || tokens[i] == "<=" || tokens[i] == ">=" ||
                tokens[i] == "==" || tokens[i] == "!=" || tokens[i] == "&&" || tokens[i] == "||")
                continue;
            inst.uses.push_back(tokens[i]);
        }
        return inst;
    }

    size_t eqPos = trimmed.find('=');
    if (eqPos == std::string::npos) {
        inst.kind = Instruction::Kind::Other;
        return inst;
    }

    std::string lhs = trim(trimmed.substr(0, eqPos));
    std::string rhs = trim(trimmed.substr(eqPos + 1));
    inst.result = lhs;

    auto tokens = split(rhs);
    if (tokens.empty()) {
        inst.kind = Instruction::Kind::Other;
        return inst;
    }

    if (tokens.size() == 1) {
        inst.kind = Instruction::Kind::Copy;
        inst.uses.push_back(tokens[0]);
    } else if (tokens.size() == 2) {
        inst.kind = Instruction::Kind::Unary;
        inst.uses.push_back(tokens[1]);
    } else if (tokens.size() >= 3) {
        inst.kind = Instruction::Kind::Binary;
        inst.uses.push_back(tokens[0]);
        inst.uses.push_back(tokens[2]);
    }

    return inst;
}

class TACOptimizer {
public:
    explicit TACOptimizer(std::vector<std::string> tacLines) {
        instructions.reserve(tacLines.size());
        for (const auto &line : tacLines) {
            instructions.push_back(parseInstruction(line));
        }
        annotations.resize(instructions.size());
    }

    void analyze() {
        std::unordered_map<std::string, VarInfo> table;
        for (int i = static_cast<int>(instructions.size()) - 1; i >= 0; --i) {
            Instruction &inst = instructions[i];
            Annotation ann;
            std::unordered_set<std::string> seen;

            auto capture = [&](const std::string &var) {
                if (var.empty() || isNumber(var) || seen.count(var))
                    return;
                auto it = table.find(var);
                VarInfo info = (it != table.end()) ? it->second : VarInfo{};
                ann.vars.emplace_back(var, info);
                seen.insert(var);
            };

            capture(inst.result);
            for (const auto &use : inst.uses) {
                capture(use);
            }
            annotations[i] = ann;

            bool isDeadAssign = false;
            if (inst.isAssignment() && !inst.result.empty() && !isNumber(inst.result)) {
                auto it = table.find(inst.result);
                VarInfo info = (it != table.end()) ? it->second : VarInfo{};
                if (!info.live && info.nextUse == -1) {
                    isDeadAssign = true;
                    inst.dead = true;
                }
            }

            if (inst.dead)
                continue;

            if (inst.isAssignment() && !inst.result.empty() && !isNumber(inst.result)) {
                table[inst.result] = VarInfo{false, -1};
            }

            auto markUse = [&](const std::string &var) {
                if (var.empty() || isNumber(var))
                    return;
                table[var] = VarInfo{true, i};
            };

            if (inst.kind == Instruction::Kind::Print || inst.kind == Instruction::Kind::If ||
                inst.kind == Instruction::Kind::Return || inst.isAssignment()) {
                for (const auto &var : inst.uses) {
                    markUse(var);
                }
            }
        }
    }

    void printAnnotated() const {
        std::cout << "Annotated TAC (before optimization):\n";
        for (size_t i = 0; i < instructions.size(); ++i) {
            const auto &inst = instructions[i];
            std::cout << i << ": " << inst.original;
            if (inst.dead)
                std::cout << "    ; dead";
            if (!annotations[i].vars.empty()) {
                std::cout << "    ; ";
                for (size_t j = 0; j < annotations[i].vars.size(); ++j) {
                    const auto &[var, info] = annotations[i].vars[j];
                    std::cout << var << "(live=" << (info.live ? "true" : "false")
                              << ", next=" << info.nextUse << ")";
                    if (j + 1 < annotations[i].vars.size())
                        std::cout << ", ";
                }
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    std::vector<std::string> optimized() const {
        std::vector<std::string> result;
        result.reserve(instructions.size());
        for (const auto &inst : instructions) {
            if (!inst.dead)
                result.push_back(inst.original);
        }
        return result;
    }

private:
    std::vector<Instruction> instructions;
    std::vector<Annotation> annotations;
};

int main() {
    std::vector<std::string> tac = {
        "t1 = a + b",
        "t2 = t1 * c",
        "t3 = t2 - d",
        "print t3",
        "t4 = t1 + t2",
        "t5 = t4 + 1",
        "if t2 > b goto L1",
        "t6 = t5 + t3",
        "L1:",
        "t7 = t3 + 0",
        "return t3"
    };

    TACOptimizer optimizer(tac);
    optimizer.analyze();
    optimizer.printAnnotated();

    auto optimizedTac = optimizer.optimized();
    std::cout << "Optimized TAC:\n";
    for (const auto &line : optimizedTac) {
        std::cout << line << '\n';
    }
    return 0;
}
