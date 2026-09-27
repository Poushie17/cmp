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




vector<string> tokenize(string rule)
{
    vector<string> symbols;

    for (int i = 0; i < rule.length(); i++)
    {
        
        if (rule.substr(i, 2) == "id")
        {
            symbols.push_back("id");
            i++;
        }

      
        else if (rule.substr(i, 7) == "epsilon")
        {
            symbols.push_back("epsilon");
            i += 6;
        }

       
        else if (i + 1 < rule.length() &&
                 rule[i + 1] == '\'')
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
    {
        result += symbol;
    }

    return result;
}


vector<string> findCommonPrefix(
    vector<string> a,
    vector<string> b)
{
    vector<string> common;

    int i = 0;

    while (i < a.size() &&
           i < b.size() &&
           a[i] == b[i])
    {
        common.push_back(a[i]);

        i++;
    }

    return common;
}


int main()
{
    int n;

    cout << "Enter number of productions: ";
    cin >> n;

    vector<Production> grammar;


    cout << "Enter productions:\n";

    for (int i = 0; i < n; i++)
    {
        string input;

        cin >> input;

       
        int pos = input.find("->");

      
        string lhs = input.substr(0, pos);

        
        string rhs = input.substr(pos + 2);

        vector<vector<string>> alternatives;

        string temp;

        stringstream ss(rhs);

        while (getline(ss, temp, '|'))
        {
            alternatives.push_back(tokenize(temp));
        }


        grammar.push_back({lhs, alternatives});
    }


    cout << "\nOriginal Grammar:\n";

    for (Production &p : grammar)
    {
        cout << p.lhs << " -> ";

        for (int i = 0; i < p.rhs.size(); i++)
        {
            cout << makeString(p.rhs[i]);

            if (i != p.rhs.size() - 1)
            {
                cout << " | ";
            }
        }

        cout << endl;
    }



    cout << "\nGrammar after Left Factoring:\n";



    vector<Production> result = grammar;

  for (int p = 0; p < result.size(); p++)
    {
        bool changed = true;

        while (changed)
        {
            changed = false;


        
            for (int i = 0;
                 i < result[p].rhs.size();
                 i++)
            {
                for (int j = i + 1;
                     j < result[p].rhs.size();
                     j++)
                {
                    vector<string> common =
                        findCommonPrefix(
                            result[p].rhs[i],
                            result[p].rhs[j]
                        );


                   
                    if (common.empty())
                    {
                        continue;
                    }


                    
                    changed = true;


                    string newNT =
                        result[p].lhs + "'";


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


                    // common + newNT
                    for (string x : common)
                    {
                        newRule1.push_back(x);
                    }

                    newRule1.push_back(newNT);


                    
                    vector<vector<string>> newAlternatives;


                    for (int x = 0;
                         x < result[p].rhs.size();
                         x++)
                    {
                        if (x == i)
                        {
                            newAlternatives.push_back(
                                newRule1
                            );
                        }
                        else if (x == j)
                        {
                           
                        }
                        else
                        {
                            newAlternatives.push_back(
                                result[p].rhs[x]
                            );
                        }
                    }


                    result[p].rhs =
                        newAlternatives;


                   
                    vector<string> restA;

                    for (int x = common.size();
                         x < grammar[p].rhs[i].size();
                         x++)
                    {
                        restA.push_back(
                            grammar[p].rhs[i][x]
                        );
                    }


                    vector<string> restB;

                    for (int x = common.size();
                         x < grammar[p].rhs[j].size();
                         x++)
                    {
                        restB.push_back(
                            grammar[p].rhs[j][x]
                        );
                    }


                    // Empty suffix = epsilon
                    if (restA.empty())
                    {
                        restA.push_back("epsilon");
                    }

                    if (restB.empty())
                    {
                        restB.push_back("epsilon");
                    }


                    Production newProduction;

                    newProduction.lhs = newNT;

                    newProduction.rhs.push_back(restA);
                    newProduction.rhs.push_back(restB);


                    result.push_back(newProduction);


                    break;
                }

                if (changed)
                {
                    break;
                }
            }
        }
    }



    for (Production &p : result)
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


    return 0;
}