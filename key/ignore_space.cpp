#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    char ch;

    cout << "Enter a line of code:" << endl;

    while (getline(cin, str))
    {
        for (int i = 0; i < str.length(); i++)
        {
            // Check for single-line comment
            if (str[i] == '/' && i + 1 < str.length() && str[i + 1] == '/')
            {
                break;  // Ignore everything after //
            }

            // Check for multi-line comment
            if (str[i] == '/' && i + 1 < str.length() && str[i + 1] == '*')
            {
                i += 2;

                while (i < str.length() &&
                       !(str[i] == '*' && i + 1 < str.length() && str[i + 1] == '/'))
                {
                    i++;
                }

                i++;  // Skip '/'
                continue;
            }

            // Ignore spaces and tabs
            if (str[i] == ' ' || str[i] == '\t')
            {
                continue;
            }

            // Print remaining characters
            cout << str[i];
        }

        cout << endl;
    }

    return 0;
}