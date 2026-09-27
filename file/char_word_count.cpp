#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    string filename;
    string line;
    
    int characters = 0;
    int words = 0;
    int lines = 0;

    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "File cannot be opened.";
        return 0;
    }

    while (getline(file, line))
    {
        // Count lines
        lines++;

        // Count characters
        characters += line.length();

        // Count words
        string word;
        stringstream ss(line);

        while (ss >> word)
        {
            words++;
        }
    }

    file.close();

    cout << "\nNumber of characters = " << characters << endl;
    cout << "Number of words = " << words << endl;
    cout << "Number of lines = " << lines << endl;

    return 0;
}