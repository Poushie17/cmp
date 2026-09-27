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
        cout << "File cannot be opened." << endl;
        return 1;
    }

    string line;
    bool inComment = false;

    while (getline(file, line))    
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

        // Check for multi-line comment
        else if (line.substr(0, 2) == "/*")
        {
            cout << "It is a comment";

            // Check if comment ends on the same line
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

    file.close();   // optional — destructor closes it anyway

    return 0;
}