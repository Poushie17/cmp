#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Production
{
    string lhs;
    vector<vector<string>> rhs;
};

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
            string symbol = "";
            symbol += rule[i];
            symbol += '\'';
            symbols.push_back(symbol);
            i++;
        }
        else
        {
            string symbol = "";
            symbol += rule[i];
            symbols.push_back(symbol);
        }
    }

    return symbols;
}

string makeString(vector<string> symbols)
{
    string result = "";
    for (string symbol : symbols)
        result += symbol;
    return result;
}

bool nameExists(string name, vector<Production> &grammar)
{
    for (Production &p : grammar)
        if (p.lhs == name) return true;
    return false;
}

string makeUniqueName(string base, vector<Production> &grammar)
{
    string name = base;
    while (nameExists(name, grammar))
        name += "'";
    return name;
}

int main()
{
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "File cannot be opened" << endl;
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
        cout << "No productions found" << endl;
        return 1;
    }

    cout << "\nOriginal Grammar:\n";

    for (Production &p : grammar)
    {
        cout << p.lhs << " -> ";
        for (int i = 0; i < (int)p.rhs.size(); i++)
        {
            cout << makeString(p.rhs[i]);
            if (i != (int)p.rhs.size() - 1) cout << " | ";
        }
        cout << endl;
    }

    cout << "\nGrammar after eliminating left recursion:\n";

    vector<Production> result;

    for (Production &p : grammar)
    {
        vector<vector<string>> alpha;
        vector<vector<string>> beta;

        for (vector<string> rule : p.rhs)
        {
            if (rule.size() > 0 && rule[0] == p.lhs)
            {
                vector<string> remaining;
                for (int i = 1; i < (int)rule.size(); i++)
                    remaining.push_back(rule[i]);
                alpha.push_back(remaining);
            }
            else
            {
                beta.push_back(rule);
            }
        }

        if (alpha.empty())
        {
            result.push_back(p);
        }
        else
        {
            string newNT = makeUniqueName(p.lhs + "'", result);

            Production newP;
            newP.lhs = p.lhs;

            if (beta.empty())
            {
                vector<string> rule;
                rule.push_back(newNT);
                newP.rhs.push_back(rule);
            }
            else
            {
                for (vector<string> b : beta)
                {
                    vector<string> rule = b;
                    rule.push_back(newNT);
                    newP.rhs.push_back(rule);
                }
            }

            result.push_back(newP);

            Production newNTProd;
            newNTProd.lhs = newNT;

            for (vector<string> a : alpha)
            {
                vector<string> rule = a;
                rule.push_back(newNT);
                newNTProd.rhs.push_back(rule);
            }

            vector<string> epsilonRule;
            epsilonRule.push_back("epsilon");
            newNTProd.rhs.push_back(epsilonRule);

            result.push_back(newNTProd);
        }
    }

    for (Production &p : result)
    {
        cout << p.lhs << " -> ";
        for (int i = 0; i < (int)p.rhs.size(); i++)
        {
            cout << makeString(p.rhs[i]);
            if (i != (int)p.rhs.size() - 1) cout << " | ";
        }
        cout << endl;
    }

    return 0;
}