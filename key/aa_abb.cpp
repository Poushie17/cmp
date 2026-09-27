#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str;

    cout << "Enter a string: ";
    cin >> str;


    // =========================
    // Pattern: a
    // =========================

    if (str == "a")
    {
        cout << "Accepted";
    }


    // =========================
    // Pattern: abb
    // =========================

    else if (str == "abb")
    {
        cout << "Accepted";
    }


    // =========================
    // Pattern: a*b+
    // =========================

    else
    {
        int i = 0;

        // Read zero or more 'a'
        while (i < str.length() &&
               str[i] == 'a')
        {
            i++;
        }


        // There must be at least one 'b'
        if (i < str.length() &&
            str[i] == 'b')
        {
            // Read one or more 'b'
            while (i < str.length() &&
                   str[i] == 'b')
            {
                i++;
            }


            // If we reached the end,
            // the string matches a*b+
            if (i == str.length())
            {
                cout << "Accepted";
            }
            else
            {
                cout << "Rejected";
            }
        }
        else
        {
            cout << "Rejected";
        }
    }


    return 0;
}