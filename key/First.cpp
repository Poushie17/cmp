#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

struct Production {
    string lhs;
    vector<string> rhs;   // each alternative is a token sequence, e.g. "E+T"
};

// ---------------------------------------------------------
// Tokenize a RHS string into symbols (handles multi-char like "id")
// ---------------------------------------------------------
vector<string> tokenize(const string &s) {
    vector<string> tokens;
    int i = 0;
    while (i < (int)s.size()) {
        // multi-char terminal "id"
        if (i + 1 < (int)s.size() && s.substr(i, 2) == "id") {
            tokens.push_back("id");
            i += 2;
        }
        // epsilon keyword
        else if (s.substr(i, 7) == "epsilon") {   // simple guard
            tokens.push_back("epsilon");
            i += 5;
        }
        else if (i + 1 < (int)s.size() && s[i + 1] == '\'') {
            tokens.push_back(s.substr(i, 2));
            i += 2;
}
else {
    tokens.push_back(string(1, s[i]));
    i++;
}
    }
    return tokens;
}

// ---------------------------------------------------------
// Check if a symbol is a terminal
// ---------------------------------------------------------
bool isTerminal(const string &sym, const vector<Production> &grammar) {
    for (const Production &p : grammar)
        if (p.lhs == sym) return false;
    return true;   // not a LHS anywhere => terminal
}

// ---------------------------------------------------------
// Compute FIRST(symbol) with ε-propagation and recursion guard
// ---------------------------------------------------------
set<string> findFirst(const string &symbol,
                      const vector<Production> &grammar,
                      set<string> &visited)
{
    set<string> result;

    // Base case: terminal
    if (isTerminal(symbol, grammar)) {
        result.insert(symbol);
        return result;
    }
 
    // Cycle guard (handles left recursion)
    if (visited.count(symbol)) return result;
    visited.insert(symbol);

    // Find production(s) with this LHS
    for (const Production &p : grammar) {
        if (p.lhs != symbol) continue;

        for (const string &rule : p.rhs) {
            if (rule == "epsilon" || rule == "ε") {
                result.insert("epsilon");
                continue;
            }

            vector<string> tokens = tokenize(rule);

            // Walk through RHS applying ε-propagation
            bool allNullable = true;
            for (const string &tok : tokens) {
                set<string> firstTok = findFirst(tok, grammar, visited);

                // Add everything except ε
                for (const string &x : firstTok)
                    if (x != "epsilon") result.insert(x);

                // If tok cannot be ε, stop here
                if (!firstTok.count("epsilon")) {
                    allNullable = false;
                    break;
                }
                // else: continue to next symbol (ε-propagation)
            }

            // If every symbol in RHS is nullable, the rule is nullable
            if (allNullable) result.insert("epsilon");
        }
    }

    return result;
}

// ---------------------------------------------------------
// Wrapper so caller doesn't manage the visited set
// ---------------------------------------------------------
set<string> findFirst(const string &symbol,
                      const vector<Production> &grammar)
{
    set<string> visited;
    return findFirst(symbol, grammar, visited);
}

// ---------------------------------------------------------
int main()
{
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    vector<Production> grammar;

    cout << "Enter productions (e.g. E->E+T|T):\n";

    for (int i = 0; i < n; i++) {
        string input;
        cin >> input;

        int pos = input.find("->");
        string lhs = input.substr(0, pos);
        string rhs = input.substr(pos + 2);

        vector<string> alternatives;
        string temp;
        stringstream ss(rhs);
        while (getline(ss, temp, '|'))
            alternatives.push_back(temp);

        grammar.push_back({lhs, alternatives});
    }

    // ---- Print original grammar ----
    // cout << "\nOriginal Grammar:\n";
    // for (const Production &p : grammar) {
    //     cout << p.lhs << " -> ";
    //     for (size_t i = 0; i < p.rhs.size(); i++) {
    //         cout << p.rhs[i];
    //         if (i + 1 != p.rhs.size()) cout << " | ";
    //     }
    //     cout << "\n";
    // }

    // ---- Compute and print FIRST sets ----
    cout << "\nFIRST sets:\n";
    for (const Production &p : grammar) {
        set<string> first = findFirst(p.lhs, grammar);

        cout << "FIRST(" << p.lhs << ") = { ";
        bool firstItem = true;
        for (const string &x : first) {
            if (!firstItem) cout << ", ";
            cout << x;
            firstItem = false;
        }
        cout << " }\n";
    }

    return 0;
}