#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    int count = 0;

    cout << "Enter a string: ";
    getline(cin, str);

    for (int i = 0; i < str.length(); i++)
    {
        // Check for two-character operators
        if (i + 1 < str.length())
        {
            string two = str.substr(i, 2);

            if (two == "++" || two == "--" ||
                two == "==" || two == "!=" ||
                two == "<=" || two == ">=" ||
                two == "&&" || two == "||" ||
                two == "+=" || two == "-=" ||
                two == "*=" || two == "/=" ||
                two == "%=")
            {
                count++;
                i++;   // skip the second character
                continue;
            }
        }

        // Check for one-character operators
        if (str[i] == '+' || str[i] == '-' ||
            str[i] == '*' || str[i] == '/' ||
            str[i] == '%' || str[i] == '=' ||
            str[i] == '<' || str[i] == '>' ||
            str[i] == '!' || str[i] == '&' ||
            str[i] == '|' || str[i] == '^')
        {
            count++;
        }
    }

    cout << "Number of operators = " << count << endl;

    return 0;
}