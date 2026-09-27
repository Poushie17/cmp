#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string str;

    cout << "Enter an identifier: ";
    cin >> str;

    // q0 = initial state
    // q1 = final state

    int state = 0;

    for (int i = 0; i < str.length(); i++)
    {
        char ch = str[i];

        if (state == 0)
        {
            // First character must be a letter or _
            if (isalpha(ch) || ch == '_')
                state = 1;
            else
                state = -1;
        }
        else if (state == 1)
        {
           
            if (isalpha(ch) || isdigit(ch) || ch == '_')
                state = 1;
            else
                state = -1;
        }
    }

    if (state == 1)
        cout << "Valid Identifier";
    else
        cout << "Invalid Identifier";

    return 0;
}