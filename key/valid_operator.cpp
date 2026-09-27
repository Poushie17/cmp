#include <iostream>
#include <string>
using namespace std;

int main()
{
    string line;

    cout << "Enter code (press Ctrl+Z then Enter on Windows,\n";
    cout << "or Ctrl+D on Linux/macOS to finish):\n\n";

    while (getline(cin, line))
    {
        for (int i = 0; i < (int)line.length(); i++)
        {
            if (i + 2 < (int)line.length())
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

            if (i + 1 < (int)line.length())
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

    return 0;
}