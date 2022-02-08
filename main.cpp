#include <iostream>
#include <fstream>
#include <string>
#include "Scanner.h"


string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

int main(int argc, char *argv[]) {
    string input1;

    //string filename(argv[1]);
    string file_contents;

    input1 = readFileIntoString(/*filename*/"../input1.txt");

    Scanner s = Scanner(input1);
    s.scannAllTokens();
    //Token t = s.scanToken();
    //cout << t.toString() << endl;
    return 0;

}

