#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string str;

    cout << "Enter a token: ";
    cin >> str;

   

    int state = 0;

    // q0 -> q1 for letter or _
    if (isalpha(str[0]) || str[0] == '_')
    {
        state = 1;

        // q1 -> q1 for letter, digit or _
        for (int i = 1; i < str.length(); i++)
        {
            if (isalpha(str[i]) || isdigit(str[i]) || str[i] == '_')
                state = 1;
            else
            {
                state = -1;
                break;
            }
        }

        if (state == 1)
        {
            cout << "Identifier";
            return 0;
        }
    }

    // ---------------- CONSTANT ----------------

    state = 0;

    // q0 -> q2 for digit
    if (isdigit(str[0]))
    {
        state = 2;

        // q2 -> q2 for digit
        for (int i = 1; i < str.length(); i++)
        {
            if (isdigit(str[i]))
                state = 2;
            else
            {
                state = -1;
                break;
            }
        }

        if (state == 2)
        {
            cout << "Constant";
            return 0;
        }
    }

    // ---------------- OPERATOR ----------------

    if (str == "+" || str == "-" ||
        str == "*" || str == "/" ||
        str == "%" || str == "=" ||
        str == "==" || str == "!=" ||
        str == "<" || str == ">" ||
        str == "<=" || str == ">=" ||
        str == "&&" || str == "||" ||
        str == "!")
    {
        cout << "Operator";
        return 0;
    }

    cout << "Invalid Token";

    return 0;
}