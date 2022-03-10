#include <iostream>
#include <fstream>
#include <string>
#include "Scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"


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
    //TODO: prevent scanner from entering coments into token vector
    string filename(argv[1]);
    string file_contents;
//
    input1 = readFileIntoString(filename/*"../input1.txt"*/);
//
    Scanner s = Scanner(input1);
    s.scannAllTokens();
    vector<Token> tokens = s.getTokens();
    /*for(int i = 0; i<(int)(tokens.size()); i++){
        cout << tokens.at(i).toString()<<endl;
    }*/
    Parser p = Parser(tokens);
    /*
    vector<string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
    }*/


   /* vector<string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    Relation relation("student", scheme);

    vector<string> values[] = {
            {"'42'", "'Ann'", "'CS'"},
            {"'32'", "'Bob'", "'CS'"},
            {"'64'", "'Ned'", "'EE'"},
            {"'16'", "'Jim'", "'EE'"},
    };

    for (auto& value : values) {
        Tuple tuple(value);
        cout << tuple.toString(scheme) << endl;
        relation.addTuple(tuple);
    }

    cout << "relation:" << endl;
    cout << relation.toString();

    Relation result = relation.select(2, "'CS'");

    cout << "select Major='CS' result:" << endl;
    cout << result.toString();*/
    return 0;

}

