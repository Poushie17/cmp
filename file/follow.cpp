#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>

using namespace std;

struct Production {
    string lhs;
    vector<vector<string>> rhs;
};

bool isNonTerminal(string symbol, vector<Production> &grammar)
{
    for (Production &p : grammar)
        if (p.lhs == symbol) return true;
    return false;
}

void addToSet(vector<string> &s, string x)
{
    for (string y : s) if (y == x) return;
    s.push_back(x);
}

vector<string> tokenize(string rule)
{
    vector<string> symbols;

    for (int i = 0; i < (int)rule.length(); i++)
    {
        if (i + 1 < (int)rule.length() && rule.substr(i, 2) == "id")
        {
            symbols.push_back("id");
            i++;
        }
        else if (i + 6 < (int)rule.length() && rule.substr(i, 7) == "epsilon")
        {
            symbols.push_back("epsilon");
            i += 6;
        }
        else if (i + 1 < (int)rule.length() && rule[i + 1] == '\'')
        {
            string s = "";
            s += rule[i];
            s += '\'';
            symbols.push_back(s);
            i++;
        }
        else
        {
            string s = "";
            s += rule[i];
            symbols.push_back(s);
        }
    }
    return symbols;
}

int findIndex(string symbol, vector<Production> &grammar)
{
    for (int i = 0; i < (int)grammar.size(); i++)
        if (grammar[i].lhs == symbol) return i;
    return -1;
}

int main()
{
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "File cannot be opened." << endl;
        return 1;
    }

    vector<Production> grammar;
    string input;

    while (getline(file, input))
    {
        string cleaned = "";
        for (char c : input)
            if (!isspace((unsigned char)c)) cleaned += c;

        if (cleaned.empty()) continue;

        int pos = cleaned.find("->");
        if (pos == (int)string::npos) continue;

        string lhs = cleaned.substr(0, pos);
        string rhs = cleaned.substr(pos + 2);

        vector<vector<string>> alternatives;
        string temp;
        stringstream ss(rhs);

        while (getline(ss, temp, '|'))
            alternatives.push_back(tokenize(temp));

        grammar.push_back({lhs, alternatives});
    }

    file.close();

    if (grammar.empty())
    {
        cout << "No productions found." << endl;
        return 1;
    }

    cout << "\nOriginal Grammar:\n";
    for (Production &p : grammar)
    {
        cout << p.lhs << " -> ";
        for (int i = 0; i < (int)p.rhs.size(); i++)
        {
            for (string s : p.rhs[i]) cout << s;
            if (i != (int)p.rhs.size() - 1) cout << " | ";
        }
        cout << "\n";
    }

    int N = grammar.size();

    map<string, set<string>> FIRST;
    set<string> NULLABLE;

    for (Production &p : grammar)
        FIRST[p.lhs];

    bool changed = true;
    while (changed)
    {
        changed = false;

        for (Production &p : grammar)
        {
            for (vector<string> &rule : p.rhs)
            {
                bool allNullable = true;

                for (string sym : rule)
                {
                    if (sym == "epsilon")
                        continue;

                    if (!isNonTerminal(sym, grammar))
                    {
                        if (FIRST[p.lhs].insert(sym).second) changed = true;
                        allNullable = false;
                        break;
                    }
                    else
                    {
                        for (string f : FIRST[sym])
                        {
                            if (f == "epsilon") continue;
                            if (FIRST[p.lhs].insert(f).second) changed = true;
                        }

                        if (!NULLABLE.count(sym))
                        {
                            allNullable = false;
                            break;
                        }
                    }
                }

                if (allNullable)
                {
                    if (FIRST[p.lhs].insert("epsilon").second) changed = true;
                    if (NULLABLE.insert(p.lhs).second) changed = true;
                }
            }
        }
    }

    vector<vector<string>> follow(N);

    addToSet(follow[0], "$");

    changed = true;
    while (changed)
    {
        changed = false;

        for (int i = 0; i < N; i++)
        {
            string lhs = grammar[i].lhs;

            for (vector<string> &rule : grammar[i].rhs)
            {
                for (int j = 0; j < (int)rule.size(); j++)
                {
                    string B = rule[j];

                    if (!isNonTerminal(B, grammar)) continue;

                    int bIdx = findIndex(B, grammar);
                    bool tailNullable = true;

                    for (int k = j + 1; k < (int)rule.size(); k++)
                    {
                        string sym = rule[k];

                        if (sym == "epsilon") continue;

                        if (!isNonTerminal(sym, grammar))
                        {
                            int before = follow[bIdx].size();
                            addToSet(follow[bIdx], sym);
                            if ((int)follow[bIdx].size() != before) changed = true;

                            tailNullable = false;
                            break;
                        }
                        else
                        {
                            for (string f : FIRST[sym])
                            {
                                if (f == "epsilon") continue;

                                int before = follow[bIdx].size();
                                addToSet(follow[bIdx], f);
                                if ((int)follow[bIdx].size() != before) changed = true;
                            }

                            if (!NULLABLE.count(sym))
                            {
                                tailNullable = false;
                                break;
                            }
                        }
                    }

                    if (tailNullable)
                    {
                        for (string f : follow[i])
                        {
                            int before = follow[bIdx].size();
                            addToSet(follow[bIdx], f);
                            if ((int)follow[bIdx].size() != before) changed = true;
                        }
                    }
                }
            }
        }
    }

    cout << "\nFIRST sets:\n";
    for (Production &p : grammar)
    {
        cout << "FIRST(" << p.lhs << ") = { ";
        bool first = true;
        for (string s : FIRST[p.lhs])
        {
            if (!first) cout << ", ";
            cout << s;
            first = false;
        }
        cout << " }\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (int i = 0; i < N; i++)
    {
        cout << "FOLLOW(" << grammar[i].lhs << ") = { ";
        for (int j = 0; j < (int)follow[i].size(); j++)
        {
            cout << follow[i][j];
            if (j != (int)follow[i].size() - 1) cout << ", ";
        }
        cout << " }\n";
    }

    return 0;
}
