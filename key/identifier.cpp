#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string id;

    cout << "Enter an identifier: ";
    cin >> id;

    bool valid = true;

    // First character must be a letter or _
    if (!(isalpha(id[0]) || id[0] == '_'))
    {
        valid = false;
    }

    // Remaining characters must be letter, digit or _
    for (int i = 1; i < id.length(); i++)
    {
        if (!(isalpha(id[i]) || isdigit(id[i]) || id[i] == '_'))
        {
            valid = false;
            break;
        }
    }

    if (valid)
        cout << "Valid Identifier";
    else
        cout << "Invalid Identifier";

    return 0;
}