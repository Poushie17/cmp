#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string filename;
    string line;

    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "File cannot be opened";
        return 0;
    }

    while (getline(file, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            // Check 3-character operators
            if (i + 2 < line.length())
            {
                string op = line.substr(i, 3);

                if (op == "<<=" || op == ">>=" ||
                    op == "->*" || op == "...")
                {
                    cout << op << " : Valid" << endl;
                    i += 2;
                    continue;
                }
            }

            // Check 2-character operators
            if (i + 1 < line.length())
            {
                string op = line.substr(i, 2);

                if (op == "++" || op == "--" ||
                    op == "==" || op == "!=" ||
                    op == "<=" || op == ">=" ||
                    op == "&&" || op == "||" ||
                    op == "+=" || op == "-=" ||
                    op == "*=" || op == "/=" ||
                    op == "%=" || op == "&=" ||
                    op == "|=" || op == "^=" ||
                    op == "<<" || op == ">>" ||
                    op == "->" || op == ".*" ||
                    op == "::")
                {
                    cout << op << " : Valid" << endl;
                    i++;
                    continue;
                }
            }

            // Check 1-character operators
            if (line[i] == '+' || line[i] == '-' ||
                line[i] == '*' || line[i] == '/' ||
                line[i] == '%' || line[i] == '=' ||
                line[i] == '<' || line[i] == '>' ||
                line[i] == '!' || line[i] == '&' ||
                line[i] == '|' || line[i] == '^' ||
                line[i] == '~' || line[i] == '?' ||
                line[i] == ':' || line[i] == '.' ||
                line[i] == ',')
            {
                cout << line[i] << " : Valid" << endl;
            }
        }
    }

    file.close();

    return 0;
}