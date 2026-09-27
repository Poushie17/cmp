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

vector<string> findCommonPrefix(vector<string> a, vector<string> b)
{
    vector<string> common;
    int i = 0;
    while (i < (int)a.size() && i < (int)b.size() && a[i] == b[i])
    {
        common.push_back(a[i]);
        i++;
    }
    return common;
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

    cout << "\nGrammar after Left Factoring:\n";

    vector<Production> result = grammar;

    for (int p = 0; p < (int)result.size(); p++)
    {
        bool changed = true;

        while (changed)
        {
            changed = false;

            for (int i = 0; i < (int)result[p].rhs.size(); i++)
            {
                for (int j = i + 1; j < (int)result[p].rhs.size(); j++)
                {
                    vector<string> altI = result[p].rhs[i];
                    vector<string> altJ = result[p].rhs[j];

                    vector<string> common = findCommonPrefix(altI, altJ);

                    if (common.empty()) continue;

                    changed = true;

                    string newNT = result[p].lhs + "'";

                    bool exists = true;
                    while (exists)
                    {
                        exists = false;
                        for (Production &x : result)
                        {
                            if (x.lhs == newNT)
                            {
                                exists = true;
                                newNT += "'";
                                break;
                            }
                        }
                    }

                    vector<string> newRule1;
                    for (string x : common) newRule1.push_back(x);
                    newRule1.push_back(newNT);

                    vector<vector<string>> newAlternatives;

                    for (int x = 0; x < (int)result[p].rhs.size(); x++)
                    {
                        if (x == i)
                            newAlternatives.push_back(newRule1);
                        else if (x == j)
                            ;
                        else
                            newAlternatives.push_back(result[p].rhs[x]);
                    }

                    result[p].rhs = newAlternatives;

                    vector<string> restA;
                    for (int x = (int)common.size(); x < (int)altI.size(); x++)
                        restA.push_back(altI[x]);

                    vector<string> restB;
                    for (int x = (int)common.size(); x < (int)altJ.size(); x++)
                        restB.push_back(altJ[x]);

                    if (restA.empty()) restA.push_back("epsilon");
                    if (restB.empty()) restB.push_back("epsilon");

                    Production newProduction;
                    newProduction.lhs = newNT;
                    newProduction.rhs.push_back(restA);
                    newProduction.rhs.push_back(restB);

                    result.push_back(newProduction);

                    break;
                }

                if (changed) break;
            }
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