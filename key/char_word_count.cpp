#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    string line;

    int characters = 0;
    int words = 0;
    int lines = 0;

    cout << "Enter text (press Ctrl+Z then Enter on Windows,\n";
    while (getline(cin, line))
    {
        lines++;

        characters += line.length();

        string word;
        stringstream ss(line);

        while (ss >> word)
        {
            words++;
        }
    }

    cout << "\nNumber of characters = " << characters << endl;
    cout << "Number of words = " << words << endl;
    cout << "Number of lines = " << lines << endl;

    return 0;
}