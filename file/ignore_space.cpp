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
    bool inComment = false;

    while (getline(file, line))
    {
        for (int i = 0; i < (int)line.length(); i++)
        {
            if (inComment)
            {
                if (line[i] == '*' && i + 1 < (int)line.length() && line[i + 1] == '/')
                {
                    inComment = false;
                    i++;
                }
                continue;
            }

            if (line[i] == '/' && i + 1 < (int)line.length() && line[i + 1] == '/')
            {
                break;
            }

            if (line[i] == '/' && i + 1 < (int)line.length() && line[i + 1] == '*')
            {
                inComment = true;
                i++;
                continue;
            }

            if (line[i] == ' ' || line[i] == '\t')
            {
                continue;
            }

            cout << line[i];
        }

        cout << endl;
    }

    file.close();

    return 0;
}