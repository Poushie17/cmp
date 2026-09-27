#include <iostream>
#include <string>
using namespace std;

int main()
{
    string line;
    bool inComment = false;

    cout << "Enter code (press Ctrl+Z then Enter on Windows,\n";
    cout << "or Ctrl+D on Linux/macOS to finish):\n\n";

    while (getline(cin, line))
    {
        if (inComment)
        {
            if (line.find("*/") != string::npos)
            {
                inComment = false;
            }

            continue;
        }

        if (line.substr(0, 2) == "//")
        {
            cout << "It is a comment";
        }

        else if (line.substr(0, 2) == "/*")
        {
            cout << "It is a comment";

            if (line.find("*/") == string::npos)
            {
                inComment = true;
            }
        }

        else
        {
            cout << "It is not a comment";
        }

        cout << endl;
    }

    return 0;
}