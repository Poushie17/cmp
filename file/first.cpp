#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>

using namespace std;

struct Production {
    string lhs;
    vector<string> rhs;
};

vector<string> tokenize(const string &s) {
    vector<string> tokens;
    int i = 0;
    while (i < (int)s.size()) {
        if (i + 1 < (int)s.size() && s.substr(i, 2) == "id") {
            tokens.push_back("id");
            i += 2;
        }
        else if (i + 6 < (int)s.size() && s.substr(i, 7) == "epsilon") {
            tokens.push_back("epsilon");
            i += 7;
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

bool isTerminal(const string &sym, const vector<Production> &grammar) {
    for (const Production &p : grammar)
        if (p.lhs == sym) return false;
    return true;
}

set<string> findFirst(const string &symbol,
                      const vector<Production> &grammar,
                      set<string> &visited)
{
    set<string> result;

    if (isTerminal(symbol, grammar)) {
        result.insert(symbol);
        return result;
    }

    if (visited.count(symbol)) return result;
    visited.insert(symbol);

    for (const Production &p : grammar) {
        if (p.lhs != symbol) continue;

        for (const string &rule : p.rhs) {
            if (rule == "epsilon") {
                result.insert("epsilon");
                continue;
            }

            vector<string> tokens = tokenize(rule);

            bool allNullable = true;
            for (const string &tok : tokens) {
                set<string> firstTok = findFirst(tok, grammar, visited);

                for (const string &x : firstTok)
                    if (x != "epsilon") result.insert(x);

                if (!firstTok.count("epsilon")) {
                    allNullable = false;
                    break;
                }
            }

            if (allNullable) result.insert("epsilon");
        }
    }

    return result;
}

set<string> findFirst(const string &symbol,
                      const vector<Production> &grammar)
{
    set<string> visited;
    return findFirst(symbol, grammar, visited);
}

int main()
{
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file) {
        cout << "File cannot be opened.\n";
        return 1;
    }

    vector<Production> grammar;
    string input;

    while (getline(file, input)) {
        string cleaned = "";
        for (char c : input)
            if (!isspace((unsigned char)c)) cleaned += c;

        if (cleaned.empty()) continue;

        int pos = cleaned.find("->");
        if (pos == (int)string::npos) continue;

        string lhs = cleaned.substr(0, pos);
        string rhs = cleaned.substr(pos + 2);

        vector<string> alternatives;
        string temp;
        stringstream ss(rhs);
        while (getline(ss, temp, '|'))
            alternatives.push_back(temp);

        grammar.push_back({lhs, alternatives});
    }

    file.close();

    if (grammar.empty()) {
        cout << "No productions found.\n";
        return 1;
    }

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