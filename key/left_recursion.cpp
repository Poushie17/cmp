#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Production
{
    string lhs;
    vector<vector<string>> rhs;
};


// ==========================================
// TOKENIZE RHS
// ==========================================

vector<string> tokenize(string rule)
{
    vector<string> symbols;

    for (int i = 0; i < rule.length(); i++)
    {
        // id
        if (rule.substr(i, 2) == "id")
        {
            symbols.push_back("id");
            i++;
        }

        // epsilon
        else if (rule.substr(i, 7) == "epsilon")
        {
            symbols.push_back("epsilon");
            i += 6;
        }

        // E', T', F', etc.
        else if (i + 1 < rule.length() &&
                 rule[i + 1] == '\'')
        {
            string symbol = "";

            symbol += rule[i];
            symbol += '\'';

            symbols.push_back(symbol);

            i++;
        }

        // Normal symbol
        else
        {
            string symbol = "";

            symbol += rule[i];

            symbols.push_back(symbol);
        }
    }

    return symbols;
}


// ==========================================
// CONVERT VECTOR OF SYMBOLS TO STRING
// ==========================================

string makeString(vector<string> symbols)
{
    string result = "";

    for (string symbol : symbols)
    {
        result += symbol;
    }

    return result;
}


// ==========================================
// MAIN
// ==========================================

int main()
{
    int n;

    cout << "Enter number of productions: ";
    cin >> n;

    vector<Production> grammar;

    cout << "Enter productions:\n";


    // ==========================================
    // INPUT
    // ==========================================

    for (int i = 0; i < n; i++)
    {
        string input;

        cin >> input;

        // Find ->
        int pos = input.find("->");

        // Get LHS
        string lhs = input.substr(0, pos);

        // Get RHS
        string rhs = input.substr(pos + 2);


        // Split using |
        vector<vector<string>> alternatives;

        string temp;

        stringstream ss(rhs);

        while (getline(ss, temp, '|'))
        {
            alternatives.push_back(
                tokenize(temp)
            );
        }


        // Store production
        grammar.push_back({
            lhs,
            alternatives
        });
    }


    // ==========================================
    // ORIGINAL GRAMMAR
    // ==========================================

    cout << "\nOriginal Grammar:\n";

    for (Production &p : grammar)
    {
        cout << p.lhs << " -> ";

        for (int i = 0;
             i < p.rhs.size();
             i++)
        {
            cout << makeString(p.rhs[i]);

            if (i != p.rhs.size() - 1)
            {
                cout << " | ";
            }
        }

        cout << endl;
    }


    // ==========================================
    // LEFT RECURSION
    // ==========================================

    cout << "\nGrammar after eliminating left recursion:\n";


    for (Production &p : grammar)
    {
        vector<vector<string>> alpha;
        vector<vector<string>> beta;


        // ======================================
        // Separate alpha and beta
        // ======================================

        for (vector<string> rule : p.rhs)
        {
            // Check if first symbol is same as LHS
            if (rule.size() > 0 &&
                rule[0] == p.lhs)
            {
                // A -> A alpha

                vector<string> remaining;

                for (int i = 1;
                     i < rule.size();
                     i++)
                {
                    remaining.push_back(rule[i]);
                }

                alpha.push_back(remaining);
            }

            else
            {
                // A -> beta

                beta.push_back(rule);
            }
        }


        // ======================================
        // NO LEFT RECURSION
        // ======================================

        if (alpha.empty())
        {
            cout << p.lhs << " -> ";

            for (int i = 0;
                 i < beta.size();
                 i++)
            {
                cout << makeString(beta[i]);

                if (i != beta.size() - 1)
                {
                    cout << " | ";
                }
            }

            cout << endl;
        }


        // ======================================
        // LEFT RECURSION EXISTS
        // ======================================

        else
        {
            string newNT = p.lhs + "'";


            // ----------------------------------
            // A -> beta A'
            // ----------------------------------

            cout << p.lhs << " -> ";

            for (int i = 0;
                 i < beta.size();
                 i++)
            {
                cout << makeString(beta[i])
                     << newNT;

                if (i != beta.size() - 1)
                {
                    cout << " | ";
                }
            }

            cout << endl;


    

            cout << newNT << " -> ";

            for (int i = 0;
                 i < alpha.size();
                 i++)
            {
                cout << makeString(alpha[i])
                     << newNT;

                if (i != alpha.size() - 1)
                {
                    cout << " | ";
                }
            }

            cout << " | epsilon" << endl;
        }
    }


    return 0;
}