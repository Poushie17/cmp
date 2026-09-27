#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

    string line;
    int count = 0;

    while (getline(file, line))
    {
        for (int i = 0; i < (int)line.length(); i++)
        {
            if (i + 1 < (int)line.length())
            {
                string two = line.substr(i, 2);

                if (two == "++" || two == "--" ||
                    two == "==" || two == "!=" ||
                    two == "<=" || two == ">=" ||
                    two == "&&" || two == "||" ||
                    two == "+=" || two == "-=" ||
                    two == "*=" || two == "/=" ||
                    two == "%=")
                {
                    count++;
                    i++;
                    continue;
                }
            }

            if (line[i] == '+' || line[i] == '-' ||
                line[i] == '*' || line[i] == '/' ||
                line[i] == '%' || line[i] == '=' ||
                line[i] == '<' || line[i] == '>' ||
                line[i] == '!' || line[i] == '&' ||
                line[i] == '|' || line[i] == '^')
            {
                count++;
            }
        }
    }

    file.close();

    cout << "Number of operators = " << count << endl;

    return 0;
}