#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "File cannot be opened." << endl;
        return 1;
    }

    string id;

    while (file >> id)
    {
        bool valid = true;

        if (!(isalpha((unsigned char)id[0]) || id[0] == '_'))
        {
            valid = false;
        }

        for (int i = 1; i < (int)id.length(); i++)
        {
            if (!(isalpha((unsigned char)id[i]) ||
                  isdigit((unsigned char)id[i]) ||
                  id[i] == '_'))
            {
                valid = false;
                break;
            }
        }

        cout << id << " -> ";
        if (valid)
            cout << "Valid Identifier";
        else
            cout << "Invalid Identifier";
        cout << endl;
    }

    file.close();

    return 0;
}